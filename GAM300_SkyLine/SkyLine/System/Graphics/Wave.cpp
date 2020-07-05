#include "Wave.h"
#include <time.h> 

glm::vec2 Wave::k_vec(const unsigned& n, const unsigned& m) const
{
	return glm::vec2(2 * PI * (n - N / 2) / width_, 2 * PI * (m - M / 2) / depth_);
}


Wave::Wave(int N, int M, float width, float depth, glm::vec2 omega, float V, float A, float lambda)
	:
	N(N), M(M),
	omega_hat(normalize(omega)),
	V(V), width_(width), depth_(depth),
	A(A),
	lambda(lambda)
{
	generator.seed(time(NULL));
	kNum = N * M;


	heightField = new glm::vec3[kNum];
	normalField = new glm::vec3[kNum];

	value_h_twiddle_0 = new std::complex<float>[kNum];
	value_h_twiddle_0_conj = new std::complex<float>[kNum];
	value_h_twiddle = new std::complex<float>[kNum];


	// Initialize value_h_twiddle_0 and value_h_twiddle_0_conj in Eq26
	for (int n = 0; n < N; ++n)
	{
		for (int m = 0; m < M; ++m)
		{
			int index = m * N + n;
			glm::vec2 k = k_vec(n, m);
			value_h_twiddle_0[index] = func_h_twiddle_0(k);
			value_h_twiddle_0_conj[index] = conj(func_h_twiddle_0(k));
		}
	}



	// Eq20 ikh_twiddle
	slope_x_term = new std::complex<float>[kNum];
	slope_z_term = new std::complex<float>[kNum];

	// Eq29 
	D_x_term = new std::complex<float>[kNum];
	D_z_term = new std::complex<float>[kNum];



	// Prepare fft input and output
	in_height = (fftwf_complex*)value_h_twiddle;
	in_slope_x = (fftwf_complex*)slope_x_term;
	in_slope_z = (fftwf_complex*)slope_z_term;
	in_D_x = (fftwf_complex*)D_x_term;
	in_D_z = (fftwf_complex*)D_z_term;

	out_height = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * kNum);
	out_slope_x = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * kNum);
	out_slope_z = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * kNum);
	out_D_x = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * kNum);
	out_D_z = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * kNum);
}


Wave::~Wave()
{

	// Free
	delete[] slope_x_term;
	delete[] slope_z_term;
	delete[] D_x_term;
	delete[] D_z_term;
	fftwf_free(out_height);
	fftwf_free(out_slope_x);
	fftwf_free(out_slope_z);
	fftwf_free(out_D_x);
	fftwf_free(out_D_z);



	delete[] heightField;
	delete[] normalField;

	delete[] value_h_twiddle_0;
	delete[] value_h_twiddle;
	delete[] value_h_twiddle_0_conj;
}

float Wave::func_omega(float k) const
{
	return sqrt(g*k);
}


// Eq23 Phillips spectrum 
inline float Wave::func_P_h(glm::vec2 vec_k) const
{
	if (vec_k == glm::vec2(0.0f, 0.0f))
		return 0.0f;

	float L = V * V / g; // Largest possible waves arising from a continuous wind of speed V

	float k = length(vec_k);
	glm::vec2 k_hat = normalize(vec_k);

	float dot_k_hat_omega_hat = dot(k_hat, omega_hat);
	float result = A * exp(-1 / (k*L*k*L)) / pow(k, 4) * pow(dot_k_hat_omega_hat, 2);

	result *= exp(-k * k*l*l);  // Eq24

	return result;
}


// Eq25
std::complex<float> Wave::func_h_twiddle_0(glm::vec2 vec_k)
{
	float xi_r = normal_dist(generator);
	float xi_i = normal_dist(generator);
	return sqrt(0.5f) * std::complex<float>(xi_r, xi_i) * sqrt(func_P_h(vec_k));
}

// Eq26
std::complex<float> Wave::func_h_twiddle(int kn, int km, float t) const
{
	int index = km * N + kn;
	float k = glm::length(k_vec(kn, km));
	std::complex<float> term1 = value_h_twiddle_0[index] * exp(std::complex<float>(0.0f, func_omega(k)*t));
	std::complex<float> term2 = value_h_twiddle_0_conj[index] * exp(std::complex<float>(0.0f, -func_omega(k)*t));
	return term1 + term2;
}



//Eq19
void Wave::buildField(float time)
{

	for (int n = 0; n < N; n++)
		for (int m = 0; m < M; m++)
		{
			int index = m * N + n;

			value_h_twiddle[index] = func_h_twiddle(n, m, time);

			glm::vec2 kVec = k_vec(n, m);
			float kLength = length(kVec);
			glm::vec2 kVecNormalized = kLength == 0 ? kVec : normalize(kVec);

			slope_x_term[index] = std::complex<float>(0, kVec.x) * value_h_twiddle[index];
			slope_z_term[index] = std::complex<float>(0, kVec.y) * value_h_twiddle[index];
			D_x_term[index] = std::complex<float>(0, -kVecNormalized.x) * value_h_twiddle[index];
			D_z_term[index] = std::complex<float>(0, -kVecNormalized.y) * value_h_twiddle[index];
		}

	p_height = fftwf_plan_dft_2d(N, M, in_height, out_height, FFTW_BACKWARD, FFTW_ESTIMATE);
	p_slope_x = fftwf_plan_dft_2d(N, M, in_slope_x, out_slope_x, FFTW_BACKWARD, FFTW_ESTIMATE);
	p_slope_z = fftwf_plan_dft_2d(N, M, in_slope_z, out_slope_z, FFTW_BACKWARD, FFTW_ESTIMATE);
	p_D_x = fftwf_plan_dft_2d(N, M, in_D_x, out_D_x, FFTW_BACKWARD, FFTW_ESTIMATE);
	p_D_z = fftwf_plan_dft_2d(N, M, in_D_z, out_D_z, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftwf_execute(p_height);
	fftwf_execute(p_slope_x);
	fftwf_execute(p_slope_z);
	fftwf_execute(p_D_x);
	fftwf_execute(p_D_z);

	for (int n = 0; n < N; n++)
		for (int m = 0; m < M; m++)
		{
			int index = m * N + n;
			float sign = 1;

			// Flip the sign
			if ((m + n) % 2) sign = -1;

			normalField[index] = normalize(glm::vec3(
				sign * out_slope_x[index][0],
				-1,
				sign * out_slope_z[index][0]));

			heightField[index] = glm::vec3(
				(n - N / 2) * width_ / N - sign * lambda * out_D_x[index][0],
				sign * out_height[index][0],
				(m - M / 2) * depth_ / M - sign * lambda * out_D_z[index][0]);
		}

	fftwf_destroy_plan(p_height);
	fftwf_destroy_plan(p_slope_x);
	fftwf_destroy_plan(p_slope_z);
	fftwf_destroy_plan(p_D_x);
	fftwf_destroy_plan(p_D_z);
}


glm::vec3* Wave::getHeightField()
{
	return heightField;
}
glm::vec3* Wave::getNormalField()
{
	return normalField;
}
#pragma once
#include "glm/glm.hpp"
#include <complex>
#include <random>
#include "fftw3.h"

#define PI 3.1415926535897932384

class Wave
{
	
public:
	Wave(int N, int M, float width, float depth, glm::vec2 omega, float V, float A, float lambda);
	~Wave();
	void buildField(float time);

	glm::vec3* getHeightField();
	glm::vec3* getNormalField();

private:
	glm::vec2 k_vec(const unsigned& n, const unsigned& m) const;

	glm::vec3* heightField;
	glm::vec3* normalField;

	std::complex<float> *value_h_twiddle_0 = NULL;
	std::complex<float> *value_h_twiddle_0_conj = NULL;
	std::complex<float> *value_h_twiddle = NULL;

	std::default_random_engine generator;
	std::normal_distribution<float> normal_dist;


	const float pi = float(PI);
	const float g = 9.8f; // Gravitational constant
	const float l = 0.1;
	float A;
	float V;
	int N, M;
	int kNum;
	glm::vec2 omega_hat;
	float lambda;
	float width_, depth_;

	float func_omega(float k) const;
	float func_P_h(glm::vec2 vec_k) const;
	std::complex<float> func_h_twiddle_0(glm::vec2 vec_k);
	std::complex<float> func_h_twiddle(int kn, int km, float t) const;



	fftwf_complex *in_height, *in_slope_x, *in_slope_z, *in_D_x, *in_D_z;
	fftwf_complex *out_height, *out_slope_x, *out_slope_z, *out_D_x, *out_D_z;

	fftwf_plan p_height, p_slope_x, p_slope_z, p_D_x, p_D_z;

	// Eq20 ikh_twiddle
	std::complex<float>* slope_x_term;
	std::complex<float>* slope_z_term;

	// Eq29 				
	std::complex<float>* D_x_term;
	std::complex<float>* D_z_term;
};


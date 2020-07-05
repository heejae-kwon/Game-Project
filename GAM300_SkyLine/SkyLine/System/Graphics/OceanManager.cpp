#include "OceanManager.h"



OceanManager::OceanManager(unsigned power = 6, unsigned width = 10000, unsigned depth = 10000)
	:
	N_(1<<power),
	M_(1<<power),
	width_(width),
	depth_(depth),
	A_((3e-7f) / 16.0f),
	V_(30),
	omega_(glm::vec2(1,1)),
	modelScale_(1.0f),
	modelScaleMult_(1.0f),
	time_(0.0f),
	wave_(nullptr)
{
	init();	
	wave_ = new Wave(N_, M_, width_, depth_, omega_, V_, A_, 1);
}

void OceanManager::init()
{
	indexSize_ = (N_ - 1) * (M_ - 1) * 6; // calculate size
	indices_ = new unsigned[indexSize_];  // make the array of indexs

	unsigned position = 0;
	for (int j = 0; j < N_ - 1; ++j)
	{
		for (int i = 0; i < M_ - 1; ++i)
		{
			indices_[position++] = i + j * N_;
			indices_[position++] = (i + 1) + j * N_;
			indices_[position++] = i + (j + 1) * N_;


			indices_[position++] = (i + 1) + j * N_;
			indices_[position++] = (i + 1) + (j + 1) * N_;
			indices_[position++] = i + (j + 1) * N_;
		}
	}

	// EBO stuff
	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize_ * sizeof(GLuint), indices_, GL_STATIC_DRAW);

	//delete[] indices_; //MOVED TO DTOR
}


OceanManager::~OceanManager()
{
	delete[] indices_;

	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
}




void OceanManager::makeWave(float dt)
{
	int nVertex = N_ * M_;

	wave_->buildField(time_);
	glm::vec3* heightField = wave_->getHeightField();
	glm::vec3* normalField = wave_->getNormalField();


	//std::vector<ValueType> vec(a, a + n);
	std::vector<glm::vec3> VectorHeightField(heightField, heightField + nVertex);
	//VectorHeightField.reserve(N*M);

	std::vector<glm::vec3> VectorNormalField(normalField, normalField + nVertex);
	//VectorNormalField.reserve(N*M);

	unsigned vecsizee = sizeof(std::vector<glm::vec3>) + (sizeof(glm::vec3) * VectorNormalField.size());

	int p = 0;

	for (int i = 0; i < N_; i++)
		for (int j = 0; j < M_; j++)
		{
			int index = j * N_ + i;

			if (heightField[index].y > heightMax) heightMax = heightField[index].y;
			else if (heightField[index].y < heightMin) heightMin = heightField[index].y;
		}


	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	int fieldArraySize = sizeof(glm::vec3) * nVertex;
	glBufferData(GL_ARRAY_BUFFER, fieldArraySize * 2, NULL, GL_STATIC_DRAW);

	// Copy height to buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, fieldArraySize, heightField);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Copy normal to buffer
	glBufferSubData(GL_ARRAY_BUFFER, fieldArraySize, fieldArraySize, normalField);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)fieldArraySize);
	glEnableVertexAttribArray(1);
}
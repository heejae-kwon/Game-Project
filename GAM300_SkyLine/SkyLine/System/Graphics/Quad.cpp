#include "Quad.h"
#include <SOIL2/SOIL2.h>
//namespace QuadVertices
//{
//	// vertices xyzrgba
//	float vertices[] =
//	{
//		// pos                // colors  rgba       
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,  // top right
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f   // top left 
//	};
//
//	unsigned int indices[] =
//	{
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//}

Quad::Quad(const glm::vec3& position)
	:position_(position),
	scale_(glm::vec3(1.0f,1.0f,1.0f)), 
	rotate_(glm::vec3(1.0f,1.0f,1.0f))
{
	

	bindMesh();
}

void Quad::bindMesh()
{
	//unsigned int textureID;
	glGenTextures(1, &texture_);

	int width, height;// , nrComponents;
	unsigned char *data = SOIL_load_image("Assets/Textures/cloud2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	if (data)
	{

		glBindTexture(GL_TEXTURE_2D, texture_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SOIL_free_image_data(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	//// vertices xyzrgba
	//float vertices[] =
	//{
	//	// pos                // colors  rgba       
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f   // top left 
	//};
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);//xyz,3 floats, vertex: 3 floats + 4floats
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

		// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Quad::draw()
{

}

Quad::~Quad()
{

}

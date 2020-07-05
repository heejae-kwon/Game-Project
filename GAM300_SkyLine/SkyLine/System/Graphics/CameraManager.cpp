#include "CameraManager.h"

#include "Application.hpp"

CameraManager::CameraManager()
{
	cameras.push_back(new QuaternionCamera());
	float FOV = 65;
	float SCR_WIDTH = 1920;
	float SCR_HEIGHT = 1080;
	float ratio = SCR_WIDTH / SCR_HEIGHT;
	float near = 0.1f;
	float far = 1000.0f;

	projection_ = glm::perspective(glm::radians(FOV), ratio, near, far);

	activeCamera = cameras[0];
	cameras[0]->proj_ = projection_;
}

glm::mat4 CameraManager::getProjection()
{
	return projection_;
}


CameraManager::~CameraManager()
{
	delete activeCamera;
}

Camera * CameraManager::getCamera()
{
	return activeCamera;
}

glm::mat4 CameraManager::getViewMatrix()
{
	return activeCamera->GetViewMatrix();
}

void CameraManager::update(float dt)
{
	for (std::vector<Camera*>::iterator it = cameras.begin(); it != cameras.end(); ++it)
	{
		(*it)->update(dt);
	}
}
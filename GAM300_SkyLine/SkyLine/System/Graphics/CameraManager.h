#pragma once

#include <vector>
#include "QuaternionCamera.h"

typedef QuaternionCamera Camera;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	
	Camera* getCamera();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjection();

	void update(float dt);

private:
  Camera * activeCamera;

  glm::mat4 projection_;
  std::vector<Camera*> cameras;
};


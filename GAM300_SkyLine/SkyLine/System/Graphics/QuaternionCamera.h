#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/normal.hpp>

struct CameraParent
{
	CameraParent();
	glm::quat parentQuaternion;
	glm::vec3 parentPosition;
	glm::vec3 parentOffset;
	bool parented;
};

class QuaternionCamera
{
public:
	QuaternionCamera(
		glm::vec3 position  = glm::vec3(0.0f, 0.0f,  0.0f), // default at origin
		glm::vec3 TargetPos = glm::vec3(0.0f, 0.0f, -1.0f)  // look at NEGATIVE Z (-Z)
		//glm::vec3 RelUp     = glm::vec3(0.0f, 1.0f,  0.0f)  // up is UP
	);
	virtual ~QuaternionCamera();

	// make it look at a dircection
	virtual void lookAt(glm::vec3 direction); // make the camera look at

	// Translation
	virtual void translate(const glm::vec3 &v); //offset by an amount
	virtual void goTo(const glm::vec3 &v);      //teleport a location

	// ROTATION
	  // orientation quat  is rotated about an angle
	virtual void rotate(float angle, const glm::vec3 &axis);
	virtual void yaw(float angle);
	virtual void pitch(float angle);
	virtual void roll(float angle);

	// USE
	// gets the quaternion representing the orientation and virew matrix
	virtual glm::quat viewQ() const;//use for 
	// gets view matrix from quaternion orientation
	virtual glm::mat4 viewM() const;
	virtual glm::mat4 GetViewMatrix() const;// use for MVP matrice multiplication


	virtual void update(float dt);
	virtual void parent(const glm::quat &pQuaternion,const glm::vec3 &pPosition,const glm::vec3 &pOffset);
	virtual void unParent();

public:
	glm::quat Orientation_;   // main way of storing orientation
	glm::mat4 OrientationMat_;// debug use

	  // Camera Attributes
	glm::vec3 Position_;  // location of camera in world space
	glm::vec3 WorldUp_;   // 0,1,0 UP
	glm::vec3 Front_;     // vector the camera is looking at
	glm::vec3 Up_;        // up vector of the camera
	glm::vec3 Right_;     // right vector of the camera
	CameraParent Parent_; //parent of camera
	bool Active_;		  // is the camera active

	glm::mat4 proj_;

	virtual void updateCameraVectors();


};

namespace QuaternionUtils
{
	// helper functions to get the vectors out of a quaternion
	glm::vec3 getFront(const glm::quat& orient);
	glm::vec3 getRight(const glm::quat& orient);
	glm::vec3 getUP(const glm::quat& orient);


	glm::quat RotateTowards(glm::quat q1, glm::quat q2, float  maxAngle);
}
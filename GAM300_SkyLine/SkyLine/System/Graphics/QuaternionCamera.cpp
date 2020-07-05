#include "QuaternionCamera.h"
QuaternionCamera::QuaternionCamera(
	glm::vec3 position,
	glm::vec3 TargetPos
	//	glm::vec3 RelUp
)
	:
	Position_(position),
	WorldUp_(glm::vec3(0.0f, 1.0f, 0.0f)),
	Front_(glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, -1.0f))),
	Right_(glm::normalize(glm::cross(Front_, glm::vec3(0.0f, 1.0f, 0.0f)))),  // set local Right
	Up_(glm::normalize(glm::cross(Right_, Front_))
	)
{
	Active_ = true;
	//glm::vec3 test = glm::normalize(START_POS - TARGET_POS);
	Orientation_ = glm::toQuat(glm::lookAt(Position_, Position_ + Front_, WorldUp_));
	//OrientationMat_ = glm::lookAt(Position_, Position_ + Front_, WorldUp_);
	   
	updateCameraVectors();
	Position_ = position;

	//glm::vec3 dir = Position - TargetPos;
	glm::vec3 dir = TargetPos - Position_;

	lookAt(dir);
}
//QuaternionCamera::QuaternionCamera(
//	glm::vec3 position, 
//	glm::vec3 TargetPos 
////	glm::vec3 RelUp
//	)
//	:
//	Position_(position),
//	WorldUp_(glm::vec3(0.0f,1.0f,0.0f)),
//	Front_(glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, -1.0f))),
//	Right_(glm::normalize(glm::cross(Front_,glm::vec3( 0.0f, 1.0f, 0.0f)))),  // set local Right
//	Up_(glm::normalize(glm::cross(Right_, Front_))
//	)
//{							
//	Active_ = true;
//	//glm::vec3 test = glm::normalize(START_POS - TARGET_POS);
//	Orientation_ = glm::toQuat(glm::lookAt(Position_, Position_ + Front_, WorldUp_));
//	OrientationMat_ = glm::lookAt(Position_, Position_ + Front_, WorldUp_);
//
//	Orientation_ = glm::conjugate(Orientation_);// fixes it so it faces the correct direction
//
//
//	updateCameraVectors();
//	Position_ = position;
//
//	//glm::vec3 dir = Position - TargetPos;
//	glm::vec3 dir = TargetPos - Position_;
//
//	lookAt(dir);
//}								       

QuaternionCamera::~QuaternionCamera()
{
}

void QuaternionCamera::update(float /*dt*/)
{
	if (Parent_.parented)
	{		
		this->lookAt(QuaternionUtils::getFront(Parent_.parentQuaternion));
		Position_ = Parent_.parentPosition + Parent_.parentOffset;
	}
}

void QuaternionCamera::parent(const glm::quat& pQuaternion,const glm::vec3& pPosition,const glm::vec3& pOffset)
{
	Parent_.parented = true;
	Parent_.parentOffset = pOffset;
	Parent_.parentPosition = pPosition;
	Parent_.parentQuaternion = pQuaternion;
}
void QuaternionCamera::unParent()
{
	Parent_.parented = false;
}




// Calculates the front vector from the Camera's (updated) Eular Angles
void QuaternionCamera::updateCameraVectors()
{
	Front_ = glm::vec3(
		-(2.0f * (Orientation_.x * Orientation_.z + Orientation_.w * Orientation_.y)),
		-(2.0f * (Orientation_.y * Orientation_.z - Orientation_.w * Orientation_.x)),
		-(1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.y * Orientation_.y))
	);

	Up_ = glm::vec3(
		2.0f * (Orientation_.x * Orientation_.y - Orientation_.w * Orientation_.z),
		1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.z * Orientation_.z),
		2.0f * (Orientation_.y * Orientation_.z + Orientation_.w * Orientation_.x)
	);

	Right_ = glm::vec3(
		(1.0f - 2.0f * (Orientation_.y * Orientation_.y + Orientation_.z * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.y + Orientation_.w * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.z - Orientation_.w * Orientation_.y))
	);
}



glm::vec3 QuaternionUtils::getFront(const glm::quat& orient)
{
	return glm::vec3(
		      -( 2.0f * (orient.x * orient.z + orient.w * orient.y)),
		       -(2.0f * (orient.y * orient.z - orient.w * orient.x)),
		-(1.0f - 2.0f * (orient.x * orient.x + orient.y * orient.y))
	);


}
glm::vec3 QuaternionUtils::getRight(const glm::quat& orient)
{
	return glm::vec3(
		(1.0f - 2.0f * (orient.y * orient.y + orient.z * orient.z)),
		       (2.0f * (orient.x * orient.y + orient.w * orient.z)),
		       (2.0f * (orient.x * orient.z - orient.w * orient.y))
	);
}
glm::vec3 QuaternionUtils::getUP(const glm::quat& orient)
{
	return glm::vec3(
		       2.0f * (orient.x * orient.y - orient.w * orient.z),
		1.0f - 2.0f * (orient.x * orient.x + orient.z * orient.z),
		       2.0f * (orient.y * orient.z + orient.w * orient.x)
	);


}


//translate by vector
// pos = translation vec * orrientation quaternion
void QuaternionCamera::translate(const glm::vec3 &v)
{
	// pos += translation vec * orrientation quaternion
	//Position += v * Orientation;
	Position_ += v;// *Orientation;

	//std::cout << "P: " << Position.x  << " "<<Position.y << " " << Position.z << "   " << "FRONT " << Front.x << " " << Front.y << " " << Front.z<<std::endl;
}

void QuaternionCamera::goTo(const glm::vec3 &v)
{
	Position_ = v;
}

// orientation quat  is rotated about an angle
void QuaternionCamera::rotate(float angle, const glm::vec3 &axis)
{
	// orientation quat *= uhhhhhh
	Orientation_ *= glm::angleAxis(angle, axis * Orientation_);
	updateCameraVectors();
}


void QuaternionCamera::yaw(float angle)
{
	//rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	rotate(angle, Up_);
} // rotate about y axis

void QuaternionCamera::pitch(float angle)
{
	//rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
	rotate(angle, Right_);
}// rotate about x axis


void QuaternionCamera::roll(float angle)
{
	// rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	//rotate(100.0f*glm::radians(angle), Front_);
	rotate(glm::radians(angle), Front_);
}// rotate about z axis



void QuaternionCamera::lookAt(glm::vec3 direction)
{
	glm::vec3 start = glm::normalize(Front_);// start vect, this case the front
	glm::vec3 dest = glm::normalize(direction);  // destination, vector we want to look at


	// check if same
	if (start == dest)
		return;


	float cosTheta = glm::dot(start, dest); // cos(theta)/(1*1)
	glm::vec3 rotationAxis;                 // axis we rotate about

	// case if vectors are in opposite directions
	if (cosTheta < -1.0f + 0.001f)          //
	{
		// get perp vector
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 0.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // worst case
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);//again

		rotationAxis = normalize(rotationAxis);//normalize axis

		Orientation_ *= glm::conjugate(glm::angleAxis(glm::radians(180.0f), rotationAxis* Orientation_));
		updateCameraVectors();
		return;
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt((1.0f + cosTheta) * 2.0f);
	float invs = 1.0f / s;

	//Orientation *= glm::conjugate( glm::angleAxis(glm::radians(180.0f), rotationAxis* Orientation));
	Orientation_ = glm::conjugate(glm::quat(
		s*0.5f,                // W
		rotationAxis.x * invs, // X
		rotationAxis.y * invs, // Y
		rotationAxis.z * invs  // Z
	));
	updateCameraVectors();
	return;
}

// gets view matrix freom quaternion
glm::mat4 QuaternionCamera::viewM() const
{
	return glm::translate(glm::mat4_cast(Orientation_), Position_);
}

// gets the quaternion representing the orientation and virew matrix
glm::quat QuaternionCamera::viewQ() const
{
	return glm::quat_cast(viewM());
}


glm::quat QuaternionUtils::RotateTowards(glm::quat q1, glm::quat q2, float  maxAngle)
{
	maxAngle = glm::radians(maxAngle);

	// too small to rotate
	if (maxAngle < 0.001f)
		return q1;

	float cosTheta = glm::dot(q1, q2);

	// already there REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	if (cosTheta > 0.9999f)
		return q2;

	// go the short way
	if (cosTheta < 0.0f)
	{
		q1 = q1 * -1.0f;
		cosTheta *= -1.0f;
	}

	float angle = acos(cosTheta);

	if (angle < maxAngle)
		return q2;

	float ft = maxAngle / angle;
	angle = maxAngle;


	glm::quat res = (sin((1.0f - ft) * angle) * q1 + sin(ft * angle) * q2) / sin(angle);
	res = glm::normalize(res);
	return res;


}

// gets vieew matrix from axis vectors
glm::mat4 QuaternionCamera::GetViewMatrix() const
{

	//return glm::lookAt(Position, Position + Front, WorldUp);

	//return glm::translate(glm::mat4_cast(glm::conjugate(Orientation)), Position);
	glm::vec3 t = glm::vec3(-Position_.x, -Position_.y, -Position_.z);
	return glm::translate(glm::mat4_cast(glm::conjugate(Orientation_)), t);


	//return glm::translate(glm::mat4_cast((Orientation_)), Position_);
	////return glm::translate(glm::mat4_cast(glm::conjugate(Orientation_)), Position_);
	
}


CameraParent::CameraParent()
	:
	parented(false),
	parentPosition(0.0f,0.0f,0.0f),
	parentOffset(0.0f, 0.0f, 0.0f)
{
}
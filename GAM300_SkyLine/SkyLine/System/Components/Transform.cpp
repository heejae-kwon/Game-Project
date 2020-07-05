#include "Transform.hpp"
#include "Actor.hpp"
#include <imgui.h>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>


Component::Transform::Transform(Actor * owner_)
	:parentTransform_(nullptr)
{
	m_hashId = identifier;
	m_type = Type::TRANSFORM;
	m_owner = owner_;

	//glm::vec3 test;
	//glm::vec3 test1 = glm::vec3(0.1f,0.2f,0.3f);
	//glm::vec3 test2;
	//test2.x = 0.1f;
	//test2.y = 0.2f;
	//test2.z = 0.3f;

	position_ = glm::vec3(0.0f,0.0f,0.0f);
	scale_ = glm::vec3(1.0f, 1.0f, 1.0f);

	front_ = glm::vec3(0.0f, 0.0f,-1.0f);
	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	right_ = glm::vec3(1.0f, 0.0f, 0.0f);

	// w x y z
	Orientation_ = ( glm::quat(0.0f,0.0f,1.0f,0.0f));
	updateVectors();

	//Orientation_ = glm::conjugate(glm::quat(0.0f,1.0f,0.0f,0.0f));
	//Orientation_ = (glm::quat(0.0f, 1.0f, 0.0f, 0.0f));
	//glm::mat4 mat = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f));
	lookAt(glm::vec3(0.0f, 0.0f, -1.0f));
	//updateVectors();
}

Component::Transform::~Transform()
{
}

void Component::Transform::getData(Json::Value & data_)
{
	    std::string componentField = Component::TypeStr[Component::TRANSFORM];
    Json::Value componentData = data_["Actors"][m_owner->name][componentField];

//    position = JsonReader::getFieldAsVec3(componentData["position"]);
 //   size = JsonReader::getFieldAsVec2(componentData["size"]);
  //  scale = JsonReader::getFieldAsVec2(componentData["scale"]);
  //  rotation = JsonReader::getFieldAsFloat(componentData["rotation"]);
}

void Component::Transform::writeData(Json::Value & data_)
{
	    std::string componentField = Component::TypeStr[Component::TRANSFORM];

    std::vector<float> posArray = { position_.x, position_.y, position_.z };
    JsonWriter::addFloatArray(data_["Actors"][m_owner->name][componentField]["position"], posArray);

    std::vector<float> scaleArray = { scale_.x, scale_.y };
    JsonWriter::addFloatArray(data_["Actors"][m_owner->name][componentField]["scale"], scaleArray);

    std::vector<float> orientArray = { Orientation_.x, Orientation_.y, Orientation_.z,Orientation_.w };
    JsonWriter::addFloatArray(data_["Actors"][m_owner->name][componentField]["orientation"], orientArray);
    //std::vector<float> scaleArray = { scale.x, scale.y };
    //JsonWriter::addFloatArray(data_["Actors"][m_owner->name][componentField]["scale"], scaleArray);

  //  JsonWriter::addValue(data_["Actors"][m_owner->name][componentField]["rotation"], rotation);
}

void Component::Transform::drawData()
{
	if (ImGui::CollapsingHeader("Transform Component"))
	{
		ImGui::PushItemWidth(160);
		{
			ImGui::InputFloat("Position X", &position_.x, 1.f, 10.f, 2);
			ImGui::InputFloat("Position Y", &position_.y, 1.f, 10.f, 2);
			ImGui::InputFloat("Position Z", &position_.z, 1.f, 10.f, 2);
			ImGui::InputFloat("Scale X", &scale_.x, 0.05f, 0.2f, 2);
			ImGui::InputFloat("Scale Y", &scale_.y, 0.05f, 0.2f, 2);
		}
		ImGui::PopItemWidth();
	}
}

void Component::Transform::setParent(const Transform* parentTransform) 
{
	parentTransform_ = parentTransform;
	if (parentTransform_ != NULL)
	{
		Orientation_ = parentTransform->Orientation_ * Orientation_;//this might be buggy i didnt test
		updateVectors();
	}
}

glm::quat Component::Transform::getOrientation()
{
	return Orientation_;
}

void Component::Transform::Update(float /*dt*/)
{
	if (parentTransform_ != nullptr) 
	{
		Orientation_ = parentTransform_->Orientation_ * Orientation_;//this might be buggy i didnt test
		updateVectors();
	}
}

void Component::Transform::updateVectors()
{
	front_ = glm::vec3(
		-(2.0f * (Orientation_.x * Orientation_.z + Orientation_.w * Orientation_.y)),
		-(2.0f * (Orientation_.y * Orientation_.z - Orientation_.w * Orientation_.x)),
		-(1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.y * Orientation_.y))
	);

	up_ = glm::vec3(
		2.0f * (Orientation_.x * Orientation_.y - Orientation_.w * Orientation_.z),
		1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.z * Orientation_.z),
		2.0f * (Orientation_.y * Orientation_.z + Orientation_.w * Orientation_.x)
	);

	right_ = glm::vec3(
		(1.0f - 2.0f * (Orientation_.y * Orientation_.y + Orientation_.z * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.y + Orientation_.w * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.z - Orientation_.w * Orientation_.y))
	);



}

glm::vec3 Component::Transform::getPosition()
{
	return position_;
}

glm::vec3 Component::Transform::getScale()
{
	return scale_;
}

void  Component::Transform::setScale(const glm::vec3& vec3)
{
	scale_ = vec3;
}

// make it look at a dircection
void Component::Transform::lookAt(glm::vec3 direction) 
{
	glm::vec3 start = glm::normalize(front_);// start vect, this case the front
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
		updateVectors();
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
	updateVectors();
	return;
}

// Translation
void Component::Transform::translate(const glm::vec3 &v)//offset by an amount
{
	position_ += v;
}
void Component::Transform::goTo(const glm::vec3 &v)      //teleport a location
{
	position_ = v;
}

// ROTATION
  // orientation quat  is rotated about an angle
void Component::Transform::rotate(float angle, const glm::vec3 &axis) 
{
	Orientation_ *= glm::angleAxis(angle, axis * Orientation_);
	updateVectors();
}

void Component::Transform::yaw(float angle)
{
	rotate(angle, up_);
}
void Component::Transform::pitch(float angle)
{
	rotate(angle, right_);
}
void Component::Transform::roll(float angle)
{
	rotate(glm::radians(angle), front_);
}

void Component::Transform::setOrientation(const glm::quat & q)
{
	Orientation_ = q;
  updateVectors();
}

glm::vec3 Component::Transform::getFront()
{

	return glm::vec3(
		-(2.0f * (Orientation_.x * Orientation_.z + Orientation_.w * Orientation_.y)),
		-(2.0f * (Orientation_.y * Orientation_.z - Orientation_.w * Orientation_.x)),
		-(1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.y * Orientation_.y)));

}
glm::vec3 Component::Transform::getRight()
{

	return glm::vec3(
		(1.0f - 2.0f * (Orientation_.y * Orientation_.y + Orientation_.z * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.y + Orientation_.w * Orientation_.z)),
		(2.0f * (Orientation_.x * Orientation_.z - Orientation_.w * Orientation_.y)));

}
glm::vec3 Component::Transform::getUP()
{
	return glm::vec3(
		2.0f * (Orientation_.x * Orientation_.y - Orientation_.w * Orientation_.z),
		1.0f - 2.0f * (Orientation_.x * Orientation_.x + Orientation_.z * Orientation_.z),
		2.0f * (Orientation_.y * Orientation_.z + Orientation_.w * Orientation_.x)
	);
}

void Component::Transform::RotateTowards(glm::quat q2, float  maxAngle)
{
	Orientation_ = RotateTowards(Orientation_,q2,maxAngle);
}

glm::quat Component::Transform::RotateTowards(glm::quat q1, glm::quat q2, float  maxAngle)
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



void Component::Transform::RotateTowards(glm::vec3 dest)
{
	Orientation_ = RotationBetweenVectors(front_,dest) * Orientation_;
	updateVectors();
}

glm::quat Component::Transform::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}
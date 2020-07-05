#include "Rigidbody.hpp"
#include <imgui.h>
#include "PhysicsCore.hpp"
#include "Actor.hpp"

Component::Rigidbody::Rigidbody(Actor * owner_) : Component::BaseComponent(owner_)
{
  m_type = Component::Type::RIGIDBODY;
  m_hashId = identifier;
}

Component::Rigidbody::~Rigidbody()
{
  //PhysicsCore::instance()->getPhysics()->removeRigidbody(*this);
}

void Component::Rigidbody::Initialize()
{
  if (m_owner->getComponent<Component::Transform>() == nullptr)
  {
    std::cout << "Actor with Rigidbody has no Transform component!!!" << std::endl;
    return;
  }

  transform_ = m_owner->getComponent<Component::Transform>();
}

float pitchSpeed = 2.0f;
float yawSpeed = 1.0f;
float rollSpeed = 100.0f;

// Update transform 
void Component::Rigidbody::Update(float dt)
{
  if (transform_ == nullptr)
    return;

  (void)dt;

  //glm::vec3 force = transform_->getFront() * 10.0f;
  //btVector3 bt_force(force.x, force.y, force.z);
  //collisionObject_->applyCentralForce(bt_force);
  //btVector3 torque(0.0f, 0.0f, -1.0f);
  //collisionObject_->applyTorque(torque * actualPitchSpeed);

  // Grab transform data from Bullet's motion state for this bulletObject
  btTransform rb_transform;// = collisionObject_->getWorldTransform();
  
  collisionObject_->getMotionState()->getWorldTransform(rb_transform);
  
  //btVector3 rb_velocity = collisionObject_->getLinearVelocity();
  //btVector3 rb_velocity = collisionObject_->getInterpolationLinearVelocity();
  //btVector3 rb_velocity = collisionObject_->
  //std::cout << "Rigidbody velocity: " << rb_velocity.getX() << ", " << rb_velocity.getY() << ", " << rb_velocity.getZ() << std::endl;
     
  // Get new origin and rotation
  btVector3 rb_translation = rb_transform.getOrigin();
  btQuaternion rb_rotation = rb_transform.getRotation();

  float translationX = rb_translation.getX();
  float translationY = rb_translation.getY();
  float translationZ = rb_translation.getZ();

 // std::cout << "Rigidbody position: " << translationX << ", " << translationY << ", " << translationZ << std::endl;

  float rotationX = rb_rotation.getX();
  float rotationY = rb_rotation.getY();
  float rotationZ = rb_rotation.getZ();
  float rotationW = rb_rotation.getW();

  //std::cout << "Rotation from Rigidbody" << rotationX << ", " << rotationY << ", " << rotationZ << ", " << rotationW << std::endl;

  // Set actual transform
  // TO DO: Fix super jerky movement...
  transform_->goTo(glm::vec3(translationX, translationY, translationZ));

  //glm::vec3 newPosition(translationX, translationY, translationZ);
  //transform_->translate(newPosition - transform_->getPosition());

  //glm::vec3 velocity(rb_velocity.getX(), rb_velocity.getY(), rb_velocity.getZ());
  //transform_->translate(velocity);
  transform_->setOrientation(glm::quat(rotationW, rotationX, rotationY, rotationZ));
 
  //std::cout << "Transform position: " << transform_->getPosition().x << ", " << transform_->getPosition().y << ", " << transform_->getPosition().z << std::endl;
}

void Component::Rigidbody::applyTorque(glm::vec3 torque)
{
  btVector3 bt_torque(torque.x, torque.y, torque.z);
  collisionObject_->applyTorque(bt_torque);
}

void Component::Rigidbody::applyForce(glm::vec3 force)
{
  btVector3 bt_force(force.x, force.y, force.z);
  //collisionObject_->applyCentralForce(bt_force); //Uncomment this and set linear dampening in Physics.cpp to use proper physics
  collisionObject_->setLinearVelocity(bt_force);
}

void Component::Rigidbody::getData(Json::Value& data_)
{
  (void)data_;
}

void Component::Rigidbody::writeData(Json::Value& data_)
{
  (void)data_;
}

void Component::Rigidbody::drawData()
{
	if (ImGui::CollapsingHeader("Rigidbody Component"))
	{

	}
}

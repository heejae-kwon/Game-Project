#pragma once
#include "BaseComponent.hpp"
#include <memory.h>
#include <btBulletDynamicsCommon.h>
#include "CollisionShape.hpp"
#include "Transform.hpp"

class Physics;

class RigidbodyKey {
  friend class Physics;
  RigidbodyKey() {}
};

namespace Component
{
  // Please note, it's VERY important that a GameObject (Actor) with a Rigidbody ALSO has a Transform component
  // Any and all Actors SHOULD have a Transform component on them anyways, so this shouldn't be a problem
  class Rigidbody : public BaseComponent
  {
  public:
    COMPONENT_HASH(Rigidbody)
    Rigidbody(Actor* owner_);

    void Initialize();

    // ***ONLY CALL THIS ONCE***
    // ---Depth and radius are only used for SPHERE and BOX shaped colliders. Read below for further details---
    // -SPHERES: Ignore width, height, and depth. Make sure to set radius to a non-zero value.
    // -BOXES:   Ignore radius. Make sure to set depth to a non-zero value.
    // -STATIC PLANES: Only care about position, everything else can be ignored.
    // -ALL OTHER SHAPES: Ignore depth and radius.
    /*void Initialize(CollisionShape shape, glm::vec3& position, float width, float height, float depth, float radius,
                       float mass, float drag, float angularDrag, bool useGravity, bool isKinematic);*/

    ~Rigidbody();
    virtual void Update(float dt);

    void    getData(Json::Value& data_)     final;
    void    writeData(Json::Value& data_)   final;
    void drawData()  final;
    
    // Applying forces
    void applyTorque(glm::vec3 torque);
    void applyForce(glm::vec3 force);
    
    // Setters
    void setMass(float mass) { mass_ = mass; }
    void setDrag(float drag) { drag_ = drag; }
    void setAngularDrag(float angularDrag) { angularDrag_ = angularDrag; }

    void enableGravity(bool enableGravity) { useGravity_ = enableGravity; }
    void isKinematic(bool isKinematic) { isKinematic_ = isKinematic; }
  
    void setCollisionShape(CollisionShape shape) { shape_ = shape; }
    
    // Getters
    float getMass() { return mass_; }
    float getDrag() { return drag_; }
    float getAngularDrag() { angularDrag_; }

    bool isGravityEnabled() { return useGravity_; }
    bool isKinematic() { return isKinematic_; }

    CollisionShape getCollisionShape() { return shape_; }
    
    // Don't use this, in fact you can't, only Physics can. Go awai.
    void setCollider(btRigidBody* btRB, RigidbodyKey) { collisionObject_ = btRB; }

  private:
    float mass_ = 1.0f; // mass of object
    float drag_ = 0.0f; // air resistance when moving from force
    float angularDrag_ = 0.0f; // air resistance while rotating from torque

    bool useGravity_ = true; // is this object affected by gravity
    bool isKinematic_ = false; // Object has zero mass and cannot be affected by other objects, but can affect other objects

    CollisionShape shape_;

    // Rigid body component should always be used in conjunction with a Transform component
    Transform* transform_; // Pointer to owner's transform

    btRigidBody* collisionObject_; // pointer to the actual object used by Bullet
    //std::shared_ptr<
  };

}

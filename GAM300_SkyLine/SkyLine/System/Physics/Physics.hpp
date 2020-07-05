#pragma once
#include <btBulletDynamicsCommon.h>
#include "Rigidbody.hpp"


// TO DO:
// Move btRigidBody ownership from Component::Rigidbodies to Physics
// Handle removing btRigidBody objects from Bullet's world simulator
class Physics {
  public:
    Physics() = delete;
    // Make sure you set gravity to a negative float, unless you want weird gravity for some raisin
    Physics(float gravity);
    ~Physics();

    void Initialize();

    void Update(float dt);

    void addRigidbody(Component::Rigidbody& rb);
    std::vector<Component::Rigidbody*>& getRigidBodies() { return rigidBodies_; }

    btRigidBody* add_RB_Box(float width, float height, float depth, float x, float y, float z, float mass);
    btRigidBody* add_RB_Sphere(float rad, float x, float y, float z, float mass);

    btRigidBody* add_RB_Cylinder(float d, float h, float x, float y, float z, float mass);
    btRigidBody* add_RB_Cone(float d, float h, float x, float y, float z, float mass);

    btRigidBody* add_RB_StaticPlane(float x, float y, float z);

  private:

    float timeStepAccumulator_ = 0.0f;

    std::vector<Component::Rigidbody*> rigidBodies_;

    // Bullet specific stuff below
    // This is simply holds configuration options
    btDefaultCollisionConfiguration * collisionConfig_;

    // CollisionDispatcher iterates over each pair and uses the appropriate collision algorithm to compute contact points
    // TLDR: Bullet uses this to calculate WHERE and HOW two objects are colliding
    btCollisionDispatcher * collisionDispatcher_;

    // Broadphase is basically a fast "initial" algorithm pass to reject pairs of objects
    // Broadphase adds and removes overlapping pairs from a pair cache
    // Bullet has three different algorithms available all inheriting from the base btBroadPhaseInterface type:
    // btBroadphaseInterface foobar = 
    // 1) btDbvtBroadphase : a fast dynamic bounding volume hierarchy based on AABB tree (Axis aligned bounding boxes)
    // 2) btAxisSweep3     : incremental 3D sweep and prune
    // 3) btCudaBroadphase : fast uniform grid using GPU hardware
    // For our purposes we will be using 1)
    btBroadphaseInterface* broadphaseInterface_;

    btSequentialImpulseConstraintSolver* constraintSolver_;

    // The actual world simulator
    btDiscreteDynamicsWorld* dynamicWorld_;

    // Bullet has its own array type to handle its collision objects
    // This is only here because we need to delete these ourselves
    btAlignedObjectArray<btRigidBody*> bodies_;
};
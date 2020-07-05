#include "Physics.hpp"
#include "CollisionShape.hpp"
#include "PhysicsCore.hpp"
#include "Transform.hpp"
#include "Actor.hpp"
#include "GraphicsCore.hpp"
#include "ObjectManager.hpp"

Physics::Physics(float gravity)
{
  // Default setup for the config
  collisionConfig_ = new btDefaultCollisionConfiguration;

  // Default collision dispatcher
  collisionDispatcher_ = new btCollisionDispatcher(collisionConfig_);

  // dbvt is a general purpose broadphase
  broadphaseInterface_ = new btDbvtBroadphase();

  // default constraint solver
  constraintSolver_ = new btSequentialImpulseConstraintSolver;

  // Create the actual simulation world with a downward gravity
  dynamicWorld_ = new btDiscreteDynamicsWorld(collisionDispatcher_, broadphaseInterface_, constraintSolver_, collisionConfig_);
  dynamicWorld_->setGravity(btVector3(0, gravity, 0));
}

Physics::~Physics()
{
  delete dynamicWorld_;
  delete collisionConfig_;
  delete collisionDispatcher_;
  delete broadphaseInterface_;
  delete constraintSolver_;

  // delete collision shapes
  for (int i = 0; i < bodies_.size(); ++i)
  {
    btRigidBody* shape = bodies_[i];
    bodies_[i] = nullptr;
    delete shape;
  }

  // Optional, clears array (the array's destructor will also call this)
  bodies_.clear();
}

void Physics::Initialize()
{
  // Should initialize Rigidbodies here after serialization is finished
  /*for (auto rigidBody : rigidBodies_)
  {
    rigidBody->Initialize();
  }*/
}


void Physics::Update(float dt)
{
  dynamicWorld_->stepSimulation(dt); // comment this and uncomment the other stuff for the alternative way, not sure what

  // Update rigidbodies, change later
  for (auto rigidBody : rigidBodies_)
  {
    rigidBody->Update(dt);
  }

  GraphicsCore * GC = GraphicsCore::instance();
  Camera *camera = GC->getCameraManager()->getCamera();

  Actor* player = ObjectManager::instance()->FindActorbyName("Player");

  Component::Transform * playerTransform = player->getComponent<Component::Transform>();

  // Make offset respect orientation. !!!This is a very important step!!!
  float xOffset = 0.0f;
  float yOffset = 4.0f;
  float zOffset = 30.0f;
  glm::vec3 offset = camera->Orientation_ * glm::vec3(xOffset, yOffset, zOffset);

  glm::vec3 newPosition = playerTransform->getPosition() + offset;

  camera->goTo( glm::mix(glm::vec3(camera->Position_), newPosition, 2.5f * dt) );
  //camera->goTo(glm::vec3(0.0f, 100.0f, 500.0f));

  //camera->Orientation_ = QuaternionUtils::RotateTowards(camera->Orientation_, playerTransform->getOrientation(), 179.0f * (dt * 10.0f));
  //camera->Orientation_ = glm::mix(camera->Orientation_, playerTransform->getOrientation(), dt);
  //camera->updateCameraVectors();

  camera->Orientation_ = playerTransform->getOrientation();

}

void Physics::addRigidbody(Component::Rigidbody& rb) 
{ 
  rb.Initialize();

  rigidBodies_.push_back(&rb); 

  Component::Transform* transform = rb.m_owner->getComponent<Component::Transform>();

  float width = transform->getScale().x;
  float height = transform->getScale().y;
  float depth = transform->getScale().z;

  float mass = rb.getMass();

  glm::vec3 position = transform->getPosition();
  
  btRigidBody* bt_RB;
  switch (rb.getCollisionShape())
  {
  case BOX:
    bt_RB = PhysicsCore::instance()->getPhysics()->add_RB_Box(width, height, depth, position.x, position.y, position.z, mass);
    rb.setCollider(bt_RB, RigidbodyKey());
    break;
  case SPHERE:
    bt_RB = PhysicsCore::instance()->getPhysics()->add_RB_Sphere(width / 2.0f, position.x, position.y, position.z, mass);
    rb.setCollider(bt_RB, RigidbodyKey());
    break;
  case CYLINDER:
    bt_RB = PhysicsCore::instance()->getPhysics()->add_RB_Cylinder(width, height, position.x, position.y, position.z, mass);
    rb.setCollider(bt_RB, RigidbodyKey());
    break;
  case CONE:
    bt_RB = PhysicsCore::instance()->getPhysics()->add_RB_Cone(width, height, position.x, position.y, position.z, mass);
    rb.setCollider(bt_RB, RigidbodyKey());
    break;
  case PLANE:
    bt_RB = PhysicsCore::instance()->getPhysics()->add_RB_StaticPlane(position.x, position.y, position.z);
    break;
  default:
    bt_RB = nullptr;
    std::cout << "No valid shape given for Rigidbody!!!" << std::endl;
    break;
  }

  // placeholder code
  bt_RB->setDamping(0.2f, 0.2f);
  //btVector3 initialVel(0.0f, 0.0f, -1.0f);
  //bt_RB->setLinearVelocity(initialVel);
  bt_RB->setActivationState(DISABLE_DEACTIVATION);

  // Still need to rotation
  btTransform bulletTransform;
  bt_RB->getMotionState()->getWorldTransform(bulletTransform);

  glm::quat quat = transform->getOrientation();
  bulletTransform.setRotation(btQuaternion(quat.x, quat.y, quat.z, quat.w));
  
  rb.setCollider(bt_RB, RigidbodyKey());
}

btRigidBody* Physics::add_RB_Box(float width, float height, float depth, float x, float y, float z, float mass)
{
  btTransform t;
  t.setIdentity();
  t.setOrigin(btVector3(x, y, z));
  btBoxShape* box = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
  btVector3 inertia(0, 0, 0);
  if (mass != 0.0)
    box->calculateLocalInertia(mass, inertia);

  btMotionState* motion = new btDefaultMotionState(t);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
  btRigidBody* body = new btRigidBody(info);
  dynamicWorld_->addRigidBody(body);
  bodies_.push_back(body);
  return body;
}

btRigidBody* Physics::add_RB_Sphere(float rad, float x, float y, float z, float mass)
{
  // Create a transform for Bullet specifically
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(x, y, z));

  // Create the collision shape, in this case a sphere
  btSphereShape* sphere = new btSphereShape(rad);

  // Inertia? If mass isn't zero rigid body should have inertia
  btVector3 inertia(0, 0, 0);
  if (mass != 0.0f)
    sphere->calculateLocalInertia(mass, inertia);

  // Motion state is just a way for Bullet to do the calculations for you
  // Don't worry too much about what it does, it works and it's easy
  btMotionState* motion = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere);

  // Add the rigid body to the world and to the member array
  btRigidBody* body = new btRigidBody(info);
  dynamicWorld_->addRigidBody(body);
  bodies_.push_back(body);

  // Return the rigid body we added
  return body;
}

btRigidBody* Physics::add_RB_Cylinder(float d, float h, float x, float y, float z, float mass)
{
  btTransform t;
  t.setIdentity();
  t.setOrigin(btVector3(x, y, z));
  btCylinderShape* cylinder = new btCylinderShape(btVector3(d / 2.0f, h / 2.0f, d / 2.0f));
  btVector3 inertia(0, 0, 0);
  if (mass != 0.0)
    cylinder->calculateLocalInertia(mass, inertia);

  btMotionState* motion = new btDefaultMotionState(t);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);
  btRigidBody* body = new btRigidBody(info);
  dynamicWorld_->addRigidBody(body);
  bodies_.push_back(body);
  return body;
}

btRigidBody* Physics::add_RB_Cone(float d, float h, float x, float y, float z, float mass)
{
  btTransform t;
  t.setIdentity();
  t.setOrigin(btVector3(x, y, z));
  btConeShape* cone = new btConeShape(d, h);
  btVector3 inertia(0, 0, 0);
  if (mass != 0.0)
    cone->calculateLocalInertia(mass, inertia);

  btMotionState* motion = new btDefaultMotionState(t);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cone, inertia);
  btRigidBody* body = new btRigidBody(info);
  dynamicWorld_->addRigidBody(body);
  bodies_.push_back(body);
  return body;
}

btRigidBody* Physics::add_RB_StaticPlane(float x = 0, float y = 0, float z = 0)
{
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(x, y, z));

  btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

  btMotionState* motion = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);

  btRigidBody* body = new btRigidBody(info);
  dynamicWorld_->addRigidBody(body);
  bodies_.push_back(body);

  return body;
}

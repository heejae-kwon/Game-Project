#include "PhysicsCore.hpp"
#include <memory>

float gravity = 0;
//Magical singletern code

PhysicsCore * PhysicsCore::instance()  //!< Returns an instance of the class
{
	static std::unique_ptr<PhysicsCore> instance(new PhysicsCore());
	return instance.get();
}

PhysicsCore::PhysicsCore()
{
  physics_ = std::make_unique<Physics>(gravity);
}

PhysicsCore::~PhysicsCore()
{

}

void PhysicsCore::Initialize(void)
{
  //physics_->Initialize();
}

void PhysicsCore::Update(float dt)
{
  physics_->Update(dt);
}

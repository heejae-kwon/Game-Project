#pragma once
#include "BaseCore.hpp"
#include "Physics.hpp"
#include <memory>
class PhysicsCore : public BaseCore 
{
  public:
    //Magical singletern code
    static PhysicsCore* instance();
    ~PhysicsCore();

    //Initialize the system
    void Initialize(void) override;

    //All systems are updated every frame
    void Update(float dt) override;

    Physics* getPhysics() { return &*physics_; }

  private:
		PhysicsCore();
    std::unique_ptr<Physics> physics_;
};
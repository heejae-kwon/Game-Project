#include "PlayerController.hpp"
#include "Gamepad.hpp"
#include "Input.hpp"
#include "Actor.hpp"
#include "LogicCore.hpp"
#include "Rigidbody.hpp"
#include <iostream>
#include <imgui.h>

namespace Component {

	PlayerController::PlayerController(Actor* owner_) 
	{
		m_hashId = identifier;
		m_type = Type::PLAYERCONTROLLER;
		m_owner = owner_;
		moveSpeed_ = 10.0f;
		pitchSpeed_ = 7.5f;
		yawSpeed_ = 2.5f;
		rollSpeed_ = 7.5f;


		v = 0.0f;
		a = 50.0f; // for physics based movement, this is the speed
		b = 0.1f;
		v_default = moveSpeed_ * 0.01f;
		v = v_default;
		acceleration = 0.0f;
	LogicCore::instance()->registerActor(m_owner);
	}

	PlayerController::~PlayerController()
	{
	LogicCore::instance()->unregisterActor(m_owner);
	}

	void PlayerController::Update(float dt)
	{
		gamepadControl(dt);
		keyboardControl(dt);
	}
	/******************************
	Gamepad Input
	******************************/
	void PlayerController::gamepadControl(float dt)
	{
		// Get Transform component from owner
		Transform* playerTransform;
		playerTransform = m_owner->getComponent<Component::Transform>();

    Rigidbody* playerRB;
    playerRB = m_owner->getComponent<Component::Rigidbody>();
		
		// Set actual speeds with Dt
    actMovSpeed = moveSpeed_ * dt;
    actPitchSpeed = pitchSpeed_ * dt;
    actYawSpeed = yawSpeed_ * dt;
    actRollSpeed = rollSpeed_ * dt;

		Input::Gamepad* padController = Input::Gamepad::instance();		

		////// Pitching 
		//// Pitch Up
		if (padController->leftStick.DOWN || padController->leftStick.UP)
		{
			//playerTransform->pitch(actPitchSpeed * -padController->leftStick.yValue);
      //playerRB->applyTorque(glm::vec3(actPitchSpeed * -padController->leftStick.yValue, 0.0f, 0.0f));
      playerRB->applyTorque(playerTransform->getRight() * (actPitchSpeed * -padController->leftStick.yValue));
		}
		// Yawing
		 //Yaw Left
		if (padController->IsPressed(Key_CONTROLLER_BUTTON_LEFTSHOULDER))
		{
			//playerTransform->yaw(actYawSpeed);
      //playerRB->applyTorque(glm::vec3(0.0f, -1.0f * actYawSpeed, 0.0f));
      playerRB->applyTorque(playerTransform->getUP() * actYawSpeed);
		}
		// Yaw Right
		if (padController->IsPressed(Key_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			//playerTransform->yaw(actYawSpeed * -1.f);
      //playerRB->applyTorque(glm::vec3(0.0f, 1.0f * actYawSpeed, 0.0f));
      playerRB->applyTorque(playerTransform->getUP() * -actYawSpeed);
		}

		////// Rolling
		if (padController->leftStick.LEFT || padController->leftStick.RIGHT)
		{
			//playerTransform->roll(actRollSpeed * padController->leftStick.xValue);
      //playerRB->applyTorque(glm::vec3(0.0f, 0.0f, -actRollSpeed * padController->leftStick.xValue));
      playerRB->applyTorque(playerTransform->getFront() * (actRollSpeed * padController->leftStick.xValue));
		}
    
    ////Movement
    //Move Front
    if (padController->RT.isTriggered && Input::Gamepad::instance()->RT.triggerValue > 0.0f)
    {
      //v += a * dt * Input::Gamepad::instance()->RT.triggerValue * 2.0f;
      //acceleration = a * dt * Input::Gamepad::instance()->RT.triggerValue *0.5f;
      acceleration = a * Input::Gamepad::instance()->RT.triggerValue * 0.75f;
      /*
      playerTransform->translate(playerTransform->getFront() *
      actMovSpeed * 2.f *  Input::Gamepad::instance()->RT.triggerValue);*/

      //playerRB->applyForce(playerTransform->getFront() * v);

      playerRB->applyForce(playerTransform->getFront() * acceleration);
    }

    // Move Back
    if (padController->LT.isTriggered && Input::Gamepad::instance()->LT.triggerValue > 0.0f)
    {
      //v += -1.0f* a * dt * Input::Gamepad::instance()->LT.triggerValue * 2.0f;
      //acceleration =  -a * dt * Input::Gamepad::instance()->LT.triggerValue * 0.05f;

      /*playerTransform->translate(playerTransform->getFront() *
      actMovSpeed * -0.3f *  Input::Gamepad::instance()->LT.triggerValue);*/
    }

		//v += acceleration;
		

		//if ((padController->LT.triggerValue > 0.0f))
		//{

		//}
		//else
		/*if (v <= 0.8f *v_default )
      v = 0.8f * v_default;
		else
		  v *= 0.995f;*/


		//playerTransform->translate(playerTransform->getFront() * v);
    
    //playerRB->applyForce(playerTransform->getFront() * v);

    //playerRB->applyForce(playerTransform->getFront() * acceleration);
	}

	/******************************
		Keyboard Input
	*******************************/
	void PlayerController::keyboardControl(float dt)
	{
		// Get Transform component from owner
		Transform* playerTransform;
		playerTransform = m_owner->getComponent<Component::Transform>();

		// Set actual speeds with Dt
		actMovSpeed = moveSpeed_ * dt;
		actPitchSpeed = pitchSpeed_ * dt;
		actYawSpeed = yawSpeed_ * dt;
		actRollSpeed = rollSpeed_ * dt;


		////Movement
		// Move Front
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_W))
		{
			playerTransform->translate(playerTransform->getFront() * actMovSpeed);
      //playerRB->applyForce(playerTransform->getFront() * actMovSpeed);
		}
		// Move Back
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_S))
		{
			playerTransform->translate(playerTransform->getFront() * actMovSpeed * -1.f);
		}

		////// Pitching 
		//// Pitch Up
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_UP))
		{
			playerTransform->pitch(actPitchSpeed);
		}
		// Pitch Down
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_DOWN))
		{
			playerTransform->pitch(actPitchSpeed * -1.f);
		}

		//// Yawing
		// Yaw Left
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_LEFT))
		{
			playerTransform->yaw(actYawSpeed);
		}
		// Yaw Right
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_RIGHT))
		{
			playerTransform->yaw(actYawSpeed * -1.f);
		}

		//// Rolling
		// Roll left
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_E))
		{
			playerTransform->roll(actRollSpeed );
		}
		// Roll right
		if (Input::Keyboard::instance()->IsPressed(Key_SCANCODE_Q))
		{
			playerTransform->roll(actRollSpeed * -1.f);
		}

    playerTransform->translate(playerTransform->getFront() * v);
	}
	void PlayerController::getData(Json::Value & /*data_*/)
	{
	}
	void PlayerController::writeData(Json::Value & /*data_*/)
	{
	}
	void PlayerController::drawData()
	{
		if (ImGui::CollapsingHeader("PlayerController Logic"))
		{
			ImGui::PushItemWidth(160);
			{
				ImGui::InputFloat("Move Speed", &moveSpeed_, 1.f, 10.f, 2);
				ImGui::InputFloat("Pitch Speed", &pitchSpeed_, 1.f, 10.f, 2);
				ImGui::InputFloat("Yaw Speed", &yawSpeed_, 1.f, 10.f, 2);
				ImGui::InputFloat("Roll Speed", &rollSpeed_, 1.f, 10.f, 2);
			}
			ImGui::PopItemWidth();
		}
	}
}

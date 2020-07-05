#include "Actor.hpp"
#include "Bullet.h"
#include "Input.hpp"
#include "Gamepad.hpp"
#include "LogicCore.hpp"
#include <imgui.h>
namespace Component {

	Bullet::Bullet(Actor * owner_)
	{
		m_owner = owner_;
		bulletSpeed = 1000.f;
		deathTime = 2.0f;
		currentTime = 0.0f;
		reloadReady = true;

		m_hashId = identifier;
		m_type = Type::BULLET;
		LogicCore::instance()->registerActor(m_owner);
		fire = AudioCore::instance()->CreateSound("./Assets/Sound/PlayerFire.ogg");
	}

	Bullet::~Bullet()
	{
		LogicCore::instance()->unregisterActor(m_owner);
	}

	void Bullet::Update(float dt)
	{
		// Keyboard keys
		if (reloadReady)
		{
			stay();
			if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_SPACE)
				|| Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_B))
			{
				// shoot sound
				AudioCore::instance()->Play(*fire, 1.0f);
				setDirection();
			}
		}
		else
		{
			goForward(dt);
			if (currentTime >= deathTime)
				reload();
		}
	}

	void Bullet::getData(Json::Value & /*data_*/)
	{
	}

	void Bullet::writeData(Json::Value & /*data_*/)
	{
	}

	void Bullet::setPlayer(Actor * player)
	{
		m_player = player;
	}

	void Bullet::stay(void)
	{
		Transform* playerTransform;
		playerTransform = m_player->getComponent<Component::Transform>();
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();

		ownerTransform->goTo(playerTransform->getPosition());
		ownerTransform->setOrientation(playerTransform->getOrientation());
	}

	void Bullet::setDirection(void)
	{
		Transform* playerTransform;
		playerTransform = m_player->getComponent<Component::Transform>();
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();
		ownerTransform->goTo(playerTransform->getPosition());
		ownerTransform->setOrientation(playerTransform->getOrientation());
		m_direction = glm::normalize(playerTransform->getFront());
		reloadReady = false;
		currentTime = 0.0f;
	}

	void Bullet::reload(void)
	{
		reloadReady = true;
	}

	void Bullet::drawData()
	{
		if (ImGui::CollapsingHeader("Bullet Shooting Logic"))
		{
			ImGui::PushItemWidth(160);
			{
				ImGui::InputFloat("CoolDown", &coolDown, 1.f, 10.f, 2);
				ImGui::InputFloat("Bullet Speed", &bulletSpeed, 1.f, 10.f, 2);
				ImGui::InputFloat("Death Time", &deathTime, 1.f, 10.f, 2);
			}
			ImGui::PopItemWidth();
		}
	}

	void Bullet::goForward(float dt)
	{
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();
		ownerTransform->translate(m_direction * bulletSpeed * dt);
		currentTime += dt;
	}

}
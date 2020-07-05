#include "Actor.hpp"
#include "LogicCore.hpp"
#include "MissileExplode.h"
#include <imgui.h>

namespace Component {
	MissileExplode::MissileExplode(Actor * owner_) : m_target(nullptr)
	{
		m_owner = owner_;
		reloadReady = true;
		shootTime = 3.0f;
		currentTime = 0.0f;
		misSpeed = 5.0f;

		m_hashId = identifier;
		m_type = Type::MISSILEEXPLODE;
		LogicCore::instance()->registerActor(m_owner);

		pSound = AudioCore::instance()->CreateSound("./Assets/Sound/Explosion1.ogg");
		pSound1 = AudioCore::instance()->CreateSound("./Assets/Sound/Explosion2.ogg");
		pSound2 = AudioCore::instance()->CreateSound("./Assets/Sound/ShipFire.ogg");
	}

	MissileExplode::~MissileExplode()
	{
		LogicCore::instance()->unregisterActor(m_owner);
	}

	void MissileExplode::Update(float dt)
	{
		if (reloadReady)
			stay(dt);

		if (currentTime >= shootTime)
		{
			if (reloadReady)
			// shoot from ship sound
			{
				AudioCore::instance()->Play(*pSound2, 1.0f);
			}
			reloadReady = false;
			ChasingObj(dt);
		}

		if (collide())
		{
			// collide with player
			AudioCore::instance()->Play(*pSound, 1.0f);
			reload();

		}
		if (collideWithCloud())
		{
			// collide with cloud
			AudioCore::instance()->Play(*pSound1, 1.0f);
			reload();

		}
	}

	void MissileExplode::getData(Json::Value & /*data_*/)
	{
	}

	void MissileExplode::writeData(Json::Value & /*data_*/)
	{
	}

	void MissileExplode::stay(float dt)
	{
		Transform* shooterTransform;
		shooterTransform = m_shooter->getComponent<Component::Transform>();
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();

		ownerTransform->goTo(shooterTransform->getPosition());


		currentTime += dt;
	}

	void MissileExplode::reload(void)
	{
		reloadReady = true;
		currentTime = 0.0f;
	}

	bool MissileExplode::collide(void)
	{
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();
		Transform* targetTransform;
		targetTransform = m_target->getComponent<Component::Transform>();

		//std::cout << "onwer("<< m_owner->name << ") pos (" << ownerTransform->getPosition().x << ", " 
		//	<< ownerTransform->getPosition().y << ", " 
		//	<< ownerTransform->getPosition().z << ") ";
		//std::cout << "target(" << m_target->name << ") pos (" << targetTransform->getPosition().x << ", "
		//	<< targetTransform->getPosition().y << ", "
		//	<< targetTransform->getPosition().z << ") ";
		float colDistance = glm::distance(ownerTransform->getPosition(), targetTransform->getPosition());
		//std::cout << "dist : " << colDistance << std::endl;
		if (colDistance < 5.0f)
			return true;
		
		return false;
	}

	bool MissileExplode::collideWithCloud(void)
	{
		Transform* ownerTransform;
		ownerTransform = m_owner->getComponent<Component::Transform>();
		Transform* cloudTransform;
		cloudTransform = m_cloud->getComponent<Component::Transform>();

		float colDistance = glm::distance(ownerTransform->getPosition(), cloudTransform->getPosition());
		if (colDistance < 20.0f)
			return true;

		return false;
	}

	void MissileExplode::ChasingObj(float dt)
	{
			if (m_target == nullptr) {
					return;
			}
		//Chaser - Missile
		Transform* chaserTransform;
		chaserTransform = m_owner->getComponent<Component::Transform>();

		//Target - player or else
		Transform* Target = m_target->getComponent<Component::Transform>();

		glm::vec3 m_newPos = chaserTransform->getPosition(); //Missile position
		glm::vec3 t_newPos = Target->getPosition(); //Target position
		glm::vec3 P_rel = t_newPos - m_newPos; //Relative position between missile and target

		chaserTransform->translate(P_rel * misSpeed * dt);

		//Keep rotating toward target
		//chaserTransform->lookAt(Target->getPosition());

		

		//glm::quat q = chaserTransform->RotateTowards(glm::angleAxis(), Target->getOrientation(), 180.f);
		//chaserTransform->setOrientation(q);

		chaserTransform->RotateTowards(P_rel);

		

	}

	void MissileExplode::SetTarget(Actor* pTarget)
	{
		m_target = pTarget;
	}
	void MissileExplode::SetShooter(Actor* pShooter)
	{
		m_shooter = pShooter;
	}

	void MissileExplode::SetCloud(Actor * pCloud)
	{
		m_cloud = pCloud;
	}

	void MissileExplode::drawData()
	{
		if (ImGui::CollapsingHeader("MissileExplode Logic"))
		{
			ImGui::PushItemWidth(160);
			{
				ImGui::InputFloat("Chase Speed", &misSpeed, 1.f, 10.f, 2);
				ImGui::InputFloat("Shoot Delay", &shootTime, 1.f, 10.f, 2);
			}
			ImGui::PopItemWidth();
		}
	}

}
#include "Chasing.hpp"
#include "Actor.hpp"
#include "Input.hpp"
#include "LogicCore.hpp"
#include <imgui.h>

namespace Component 
{
	Chasing::Chasing(Actor* owner_) : target(nullptr)
	{
		m_hashId = identifier;
		m_type = Type::CHASING;
		m_owner = owner_;
		misSpeed = 3.0f;		
		LogicCore::instance()->registerActor(m_owner);
	}

	Chasing::~Chasing()
	{
		LogicCore::instance()->unregisterActor(m_owner);
	}

	void Chasing::Update(float dt)
	{
		ChasingObj(dt);
	}

	void Chasing::SetTarget(Actor* pTarget)
	{
		target = pTarget;
	}
		
	void Chasing::ChasingObj(float dt)
	{
			if (target == nullptr) {
					return;
			}
		//Chaser - Missile
		Transform* chaserTransform; 
		chaserTransform = m_owner->getComponent<Component::Transform>();
		
		//Target - player or else
		//target->addComponent<Component::Transform>();
		Transform* Target = target->getComponent<Component::Transform>();

		glm::vec3 m_newPos = chaserTransform->getPosition(); //Missile position
		glm::vec3 t_newPos = Target->getPosition(); //Target position
		glm::vec3 P_rel = t_newPos - m_newPos; //Relative position between missile and target
	
		chaserTransform->translate(P_rel * misSpeed * dt);
	
		//Keep rotating toward target
		glm::quat q = chaserTransform->RotateTowards(chaserTransform->getOrientation(), Target->getOrientation(), 180.f);
		chaserTransform->setOrientation(q);
	}

	void Chasing::getData(Json::Value & /*data_*/)
	{
	}
	void Chasing::writeData(Json::Value & data_)
	{
	    std::string componentField = Component::TypeStr[Component::CHASING];

    std::vector<float> speed = { misSpeed };
    JsonWriter::addFloatArray(data_["Actors"][m_owner->name][componentField]["misSpeed"], speed);
	}
	void Chasing::drawData()
	{
		if (ImGui::CollapsingHeader("Chasing Logic"))
		{
			ImGui::PushItemWidth(160);
			{
				ImGui::InputFloat("Chase Speed", &misSpeed, 1.f, 10.f, 2);
			}
			ImGui::PopItemWidth();
		}
	}
}

//void Chasing::MoveAround(float time)
	//{
	//	//const float PI = 4.0f*atan(1.0f);

	//	//Transform* ownerTransform;
	//	//ownerTransform = m_owner->getComponent<Component::Transform>();
	//	//
	//	//glm::vec3 ownerPos = ownerTransform->getPosition();
	//	//glm::vec3 aroundPos = glm::vec3
	//	//(
	//	//	(4 + sin(2 * PI / 25 * time))*sin(PI / 4 * (2 + sin(2 * PI / 35 * time)))*cos(PI*(1 + sin(2 * PI / 35 * time))),
	//	//	0,
	//	//	(4 + sin(2 * PI / 25 * time))*sin(PI / 4 * (2 + sin(2 * PI / 35 * time)))*sin(PI*(1 + sin(2 * PI / 35 * time)))
	//	//);
	//	//glm::vec3 rel_pos = aroundPos - ownerPos;
	//	////glm::quat q = ownerTransform->RotateTowards(ownerTransform->getOrientation(),  )

	//	//ownerTransform->translate(aroundPos * 0.003f);
	//}


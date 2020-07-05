#include "Logic.hpp"
#include "Logic.hpp"
#include "LogicCore.hpp"
#include <imgui.h>

Component::Logic::~Logic()
{
//	LogicCore::instance()->unregisterActor(m_owner);
}

void Component::Logic::Update(float /*dt*/)
{
}

Component::Logic::Logic(Actor * owner_ )
{
	/*These three MUST be exist in each Component*/
	m_hashId = identifier;
	m_type = Type::LOGIC;
	m_owner = owner_;
}

//
//void Component::Logic::drawData()
//{
//	if (ImGui::CollapsingHeader("Logic Component"))
//	{
//
//	}
//}

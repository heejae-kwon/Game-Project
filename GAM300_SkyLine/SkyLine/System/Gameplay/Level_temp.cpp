#include "Level_temp.hpp"
#include <Input.hpp>
#include <Engine.hpp>


Level::Level_temp::Level_temp(std::string stageFileName_)
{
}

Level::Level_temp::~Level_temp()
{
}

void Level::Level_temp::Update(float /*dt*/)
{
				if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_X)) {
						Engine::instance()->PopActiveLevel();
				return;
		}

}

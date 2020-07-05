#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>
#include <WIP\HBMath.hpp>

#include <GAME_SPECIFIC_FILES/sLevel1.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>

Stage::sLevel1::sLevel1(std::string fileName_)
    : BaseStage((fileName_ == "") ? "sLevel1.stg" : fileName_.c_str())
{
    std::cout << fileName_.c_str() << '\n';
    fileName = (fileName_ == "") ? "sLevel1.stg" : fileName_;
}

void
Stage::sLevel1::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

	player = getActor("player");
	hud = getActor("hud");
}

void
Stage::sLevel1::resume()
{
}

void
Stage::sLevel1::pause()
{
}






void
Stage::sLevel1::update(float dt_)
{
    for (auto & actor : _actorVec)
    {
        if (actor->_name == "camera")
        {
//            logic::camera::cameraMoveLogic(actor.get(), dt);
        }
		else if (actor->_name == "player")
		{
			logic::player::playerMoveLogic(actor.get(), dt_);
			//actor->getComponent<BE::Component::Transform>()->position.x += 150.f * dt_;
			//actor->getComponent<BE::Component::Transform>()->position.y += 150.f * dt_;				

		}

    }



    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_PLUS))
    {
        BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::%s] KeyPad + pressed\n", __func__);
        BE::WindowAbst::instance()->resizeWindow(glm::vec2(1920, 1080));
    }
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_MINUS))
    {
        BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::%s] KeyPad - pressed\n", __func__);
        BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 720));
    }
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE))
    {
        BE::Engine::BunnyEngine::instance()->pushActiveStage(new sConfirmMenu);
    }
}




#include <GAME_SPECIFIC_FILES/sHowtoKill.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>

Stage::sHowtoKill::sHowtoKill()
    : BaseStage("sHowtoKill.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
Stage::sHowtoKill::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);
}

void
Stage::sHowtoKill::resume()
{
}

void
Stage::sHowtoKill::pause()
{
}

void
Stage::sHowtoKill::update(float /*dt_*/)
{
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE) || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_s))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        return;
    }
}

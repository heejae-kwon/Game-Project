/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      main.cpp
Purpose:        Entry point of our program
Language:       C++
Project:        GAM200
Author:         Name : Stuat Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <BunnyEngine.hpp>

#include <GAME_SPECIFIC_FILES/sConfirmQuit.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyLogo.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <GAME_SPECIFIC_FILES/sOption.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPlay.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoKill.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPowerup.hpp>
#include <GAME_SPECIFIC_FILES/sCredit.hpp>
#include <GAME_SPECIFIC_FILES/sPokemon.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/sTestLevel.hpp>
#include <GAME_SPECIFIC_FILES/sTutorial.hpp>
#include <GAME_SPECIFIC_FILES/sGameStage.hpp>
#include <GAME_SPECIFIC_FILES/sRocketDestinationSelect.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmRestart.hpp>
#include <GAME_SPECIFIC_FILES/sESCMenu.hpp>

#include  <GAME_SPECIFIC_FILES/PlanetRotationTest.hpp>

int
main(int /*ac*/, char** /*av*/)
{

	{
		BE::Engine::BunnyEngine* game = BE::Engine::BunnyEngine::instance(true);

		// Creating the list of loadeable stages
		{
			BE::Engine::BunnyEngine::StageVec* availableStages = &BE::Engine::BunnyEngine::instance()->_availableStages;

            availableStages->push_back(std::unique_ptr<Stage::PlanetRotationTest>(new Stage::PlanetRotationTest));
            availableStages->push_back(std::unique_ptr<Stage::sConfirmQuit>(new Stage::sConfirmQuit));
			availableStages->push_back(std::unique_ptr<Stage::sConfirmMenu>(new Stage::sConfirmMenu));
			availableStages->push_back(std::unique_ptr<Stage::sLegacyLogo>(new Stage::sLegacyLogo));
			availableStages->push_back(std::unique_ptr<Stage::sLegacyMenu>(new Stage::sLegacyMenu));
			availableStages->push_back(std::unique_ptr<Stage::sHowtoPlay>(new Stage::sHowtoPlay));
            availableStages->push_back(std::unique_ptr<Stage::sOption>(new Stage::sOption));
            availableStages->push_back(std::unique_ptr<Stage::sCredit>(new Stage::sCredit));
			availableStages->push_back(std::unique_ptr<Stage::sPokemon>(new Stage::sPokemon));
			availableStages->push_back(std::unique_ptr<Stage::sWinScreen>(new Stage::sWinScreen));
            availableStages->push_back(std::unique_ptr<Stage::sLoseScreen>(new Stage::sLoseScreen));
            availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sTestStage.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel1.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel1-1.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel2.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel2-2.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel3.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sGameStage>(new Stage::sGameStage("sLevel4.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sHowtoKill>(new Stage::sHowtoKill));
			availableStages->push_back(std::unique_ptr<Stage::sHowtoPowerup>(new Stage::sHowtoPowerup));
			availableStages->push_back(std::unique_ptr<Stage::sConfirmRestart>(new Stage::sConfirmRestart("sLevel4.stg")));
			availableStages->push_back(std::unique_ptr<Stage::sESCMenu>(new Stage::sESCMenu("sLevel1.stg")));
        }

        game->pushActiveStage(new Stage::sLegacyLogo);
        game->run();
	}
    return 0;
}
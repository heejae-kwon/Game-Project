#pragma once

#include <string>
#include "BaseLevel.hpp"
#include "AudioCore.hpp"

class Actor;
class ObjectManager;
class Sound;

namespace Level{
		class Level_1 : public BaseLevel
		{
		public:
				Level_1(std::string stageFileName_);
				~Level_1();

				float time;
				void Update(float dt);
				//void LoadLevelFile(std::string fileName_);
				//void SaveLevelFile(std::string fileName_);

		private:
				Actor* actor; // player
				Actor* playerMissle; // player Missle

				Actor* Missile;
				Actor* BattleshipMissile;
				Actor* Target;

				Actor * Battleship;
				Actor * Island;

				Actor * Island1;
				Actor * Island2;
				Actor * Island3;
				Actor * Island4;

				Actor * Cloud1;
				Actor * Cloud2;

				Sound* mSound;
				Sound* mSound1;
				Sound* mSound2;

		};
}
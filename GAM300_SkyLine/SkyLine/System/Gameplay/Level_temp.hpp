#pragma once
#include <string>
#include "BaseLevel.hpp"
class Actor;
class ObjectManager;

namespace Level{
		class Level_temp : public BaseLevel
		{
		public:
				Level_temp(std::string stageFileName_);
				~Level_temp();

				void Update(float dt);
				//void LoadLevelFile(std::string fileName_);
				//void SaveLevelFile(std::string fileName_);

		private:

		};
}

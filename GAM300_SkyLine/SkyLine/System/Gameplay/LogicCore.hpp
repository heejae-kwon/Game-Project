#pragma once
#include "BaseCore.hpp"

/*Update ALL Logic component's Update function*/
class LogicCore : public BaseCore {
								public:
				//Magical singletern code
			static LogicCore* instance();
			~LogicCore();

			//Initialize the system
			//void Initialize(void) override;

		//All systems are updated every frame
			void Update(float dt) override;

				private:
								LogicCore();

};
#pragma once
#include <string>
class ObjectManager;
namespace Level {
		class BaseLevel
		{
		public:
				BaseLevel(std::string name = "");
				virtual ~BaseLevel() = default;

	//			virtual void Start(std::string fileName_ = "") = 0;        //!< Starts the stage, initialise values here
				virtual void LoadLevelFile(std::string fileName_);
				virtual void SaveLevelFile(std::string fileName_);

				virtual void Update(float dt) = 0;
				virtual void Resume();
				virtual void Pause();
				//        virtual void    loadProps(std::string fileName_);        //!< Should be called in start(), loads the props (image, audio...) needed by the actors
		protected:
				BaseLevel* m_previousLevel;
				std::string m_levelFileName;
				ObjectManager* m_obj;
				int m_numberOfActor;

		private:

		};
}

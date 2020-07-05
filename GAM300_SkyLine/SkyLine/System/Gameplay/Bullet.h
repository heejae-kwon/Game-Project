#pragma once

#include "Logic.hpp"
#include "AudioCore.hpp"

class Actor;
namespace Component
{
	class Bullet : public Logic  // Base class for each bullets
	{
	public:
		Bullet(Actor* owner_);
		~Bullet();

		void Update(float dt);
		void    getData(Json::Value& data_)     final;
		void    writeData(Json::Value& data_)   final;
		void		setPlayer(Actor* player);
		void		stay(void);
		void		setDirection(void);
		void		reload(void);

		void    drawData();
		void		goForward(float dt);

	protected:
		// Missile Infos
		float coolDown;			//!< time for reloading
		bool reloadReady;		//!< check missile is reload
		float bulletSpeed;			//!< speed of missile
		float deathTime;			//!< Death time
		float currentTime;		//!< time flew after shoot

		Actor* m_player;
		glm::vec3 m_direction;
		Sound* fire;
	};

}

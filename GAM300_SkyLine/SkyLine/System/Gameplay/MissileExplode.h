#pragma once

#include "Logic.hpp"
#include "AudioCore.hpp"

class Actor;
namespace Component
{
	class MissileExplode : public Logic  // Base class for each MissileExplodes
	{
	public:
		MissileExplode(Actor* owner_);
		~MissileExplode();

		void		Update(float dt);
		void    getData(Json::Value& data_)     final;
		void    writeData(Json::Value& data_)   final;
		void		stay(float dt);
		void		reload(void);
		bool	collide(void);

		bool collideWithCloud(void);

		void ChasingObj(float dt);

		void SetTarget(Actor * pTarget);
		void SetShooter(Actor * pShooter);
		void SetCloud(Actor * pCloud);

		void    drawData();

	private:
		// Missile Infos
		bool reloadReady;		//!< check missile is reload
		float shootTime;			//!< Death time
		float currentTime;		//!< time flew after shoot
		float misSpeed;

		Actor* m_target;
		Actor* m_shooter;
		Actor* m_cloud;

		Sound* pSound;
		Sound* pSound1;
		Sound* pSound2;

	};
}

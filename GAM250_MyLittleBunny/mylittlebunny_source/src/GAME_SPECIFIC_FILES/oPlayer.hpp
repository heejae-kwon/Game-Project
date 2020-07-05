/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      oPlayer.hpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon, Wonjae Jung
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <Components/Components.hh>

#include <GAME_SPECIFIC_FILES/Objects.hpp>
namespace Stage
{
	class Planet;

	class Player {
	public:
		Player(BE::Actor *player = nullptr);
        ~Player() = default;

		void initData(BE::Actor * player, float jumpforce = 0, float moveforce = 0, float damping = 0, float velsquarmax =0);
		void planetMovement(LevelSetting& LvSetting, float dt);
		void planetGravity(LevelSetting& LvSetting, float /*dt_*/);
		void Update(LevelSetting& LvSetting, float dt);

		void flytoOtherPlanet(std::string planetName, LevelSetting & LvSetting, float dt);
  void flytoOtherPlanet(BE::Actor *planet_, float dt_);
  void flytoDestination(BE::Actor* destination_, float dt);

		//Paritlce part
		void powerUp(void);
		void powerDown(void);
		void TailParticle(int i);

		const float getJumpForce(void) const;
		void setJumpForce(float input);
		const float getMoveForce(void) const;
		void setMoveForce(float input);
		const float getDamping(void) const;
		void setDamping(float input);
		const float getVelSquarMax(void) const;
		void setVelSquarMax(float input);
  const glm::vec2 getAnchorPoint();


		//Sound control
		void shutdownSounds(void);
		void resumeSounds(void);
		void pauseSounds(void);



		enum MoveState
		{
			STAND, WALK, JUMP, FLYING
		};
		enum InPutState
		{
			KEYBOARD, GAMEPAD
		};
		enum ParticleType
		{
			ONE,TWO,THREE,FOUR
		};

		int m_planetNum;
		BE::Actor* m_dirPlanet;
		
		BE::Actor* m_actor;
		MoveState m_movestate;
		InPutState m_inputstate;

		float m_powerGage;
		bool m_change;

	private:

		void movementControl(float dt_);
//        void Player::ChangeCharacter();
        void smoothRotation(float dt_);
        int getClosestAngleDir(float angle1_, float angle2_);
		
		BE::Component::Transform* m_transform;
		BE::Component::Rigidbody* m_rigidbody;
		BE::Component::CircleCollider* m_collider;
		BE::Component::ParticleEmitter* m_particle;
		BE::Component::Display* m_display;
		bool m_onground;
		bool m_canjump;

		float prevRadius; // for find the planet with distance, have to save the radius of current planet
        float rotationTarget; // for smooth rotation


	float JUMP_FORCE;
	float VELSQUARMAX;
	float MOVE_FORCE;
	float DAMPING;
	float CHANGE_MOVE_FORCE;
	
	 BE::PropManager::propNamePair* sndJump;
	 bool b_sndJump;
	 BE::PropManager::propNamePair* sndFlying;
	 bool b_sndFlying;
     BE::PropManager::propNamePair* sndPowerup;
     bool b_sndPowerup;
	 int increasingParticle;

	};

}
#endif // !

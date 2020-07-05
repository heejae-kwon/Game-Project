/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      oPlayer.cpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon, Wonjae Jung
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP/Gamepad.hpp>
#include <WIP\HBMath.hpp>

#include <GAME_SPECIFIC_FILES\oPlayer.hpp> 
#include <GAME_SPECIFIC_FILES/LevelSetting.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>

namespace Stage
{

    //constructor
    Player::Player(BE::Actor * player) : m_actor(player),
        m_transform(nullptr),
        m_rigidbody(nullptr),
        m_particle(nullptr),
        m_movestate(MoveState::STAND),
        m_onground(false),
        m_change(false),
        m_canjump(false),
        prevRadius(0),
        m_planetNum(0),
		m_powerGage(0),
        JUMP_FORCE(0),
        MOVE_FORCE(0),
        CHANGE_MOVE_FORCE(0),
        DAMPING(0),
        VELSQUARMAX(0),
		increasingParticle(0)
    {
        if (player != nullptr) {
            m_transform = player->getComponent<BE::Component::Transform>();
            m_rigidbody = player->getComponent<BE::Component::Rigidbody>();
            m_collider = player->getComponent<BE::Component::CircleCollider>();
            m_particle = player->getComponent<BE::Component::ParticleEmitter>();
            m_display = player->getComponent<BE::Component::Display>();
        }
    }

    //Each level's player need to use this fucntion fundamentally.
    void Player::initData(BE::Actor * player, float jumpforce,
        float moveforce, float damping,
        float velsquarmax) {
        m_actor = player;
        if (player != nullptr) {
            m_transform = player->getComponent<BE::Component::Transform>();
            m_rigidbody = player->getComponent<BE::Component::Rigidbody>();
            m_collider = player->getComponent<BE::Component::CircleCollider>();
            m_particle = player->getComponent<BE::Component::ParticleEmitter>();
            m_display = player->getComponent<BE::Component::Display>();
        }
        setJumpForce(jumpforce);
        setMoveForce(moveforce);
        setDamping(damping);
        setVelSquarMax(velsquarmax);
        MOVE_FORCE = moveforce;
        CHANGE_MOVE_FORCE = moveforce * 1.5f;
		
		//Init sounds
		sndFlying = BE::PropManager::instance()->lookupValue("sndFly");
		b_sndFlying = true;
		sndJump = BE::PropManager::instance()->lookupValue("sndJump");
		b_sndJump = true;
		sndPowerup = BE::PropManager::instance()->lookupValue("sndSpecial"); 
		b_sndPowerup = true;
    }

    void Player::Update(LevelSetting& LvSetting, float dt)
    {
        planetGravity(LvSetting, dt);
        planetMovement(LvSetting, dt);
    }

    void Player::flytoOtherPlanet(std::string planetName, LevelSetting & LvSetting, float dt)
    {
        if (m_movestate == MoveState::FLYING)
            return;

        BE::HBVec2 gravDir(
            m_rigidbody->gravity.x - m_transform->position.x,
            m_rigidbody->gravity.y - m_transform->position.y);
        gravDir.Normalize();

        m_movestate = MoveState::FLYING;
        m_transform->scale *= 2;
        m_collider->radius *= 2;
        m_rigidbody->force -= (getJumpForce()* gravDir) * dt;
        for (auto & planet : LvSetting.planetVector) {
            if (planet.GetOwner()->_name.find(planetName) != std::string::npos)
            {
                m_display->setTextureId("sprRocketPlayer");
                m_dirPlanet = planet.GetOwner();
                m_rigidbody->gravity = m_dirPlanet->getComponent<BE::Component::Transform>()->position;
                m_collider->ghost = true;
            }
        }
    }

    void Player::flytoOtherPlanet(BE::Actor *planet_, float dt_)
    {
        if (m_movestate == MoveState::FLYING)
            return;

        BE::HBVec2 gravDir(
            m_rigidbody->gravity.x - m_transform->position.x,
            m_rigidbody->gravity.y - m_transform->position.y);
        gravDir.Normalize();

        m_movestate = MoveState::FLYING;
        m_transform->scale *= 2;
        m_collider->radius *= 2;
        m_rigidbody->force -= (getJumpForce()* gravDir) * dt_;
        m_display->setTextureId("sprRocketPlayer");
        m_dirPlanet = planet_;
        m_rigidbody->gravity = m_dirPlanet->getComponent<BE::Component::Transform>()->position;
        m_collider->ghost = true;


    }

    void Player::flytoDestination(BE::Actor * destination_, float dt)
    {
        if (m_movestate == MoveState::FLYING)
            return;

        BE::HBVec2 gravDir(
            m_rigidbody->gravity.x - m_transform->position.x,
            m_rigidbody->gravity.y - m_transform->position.y);
        gravDir.Normalize();

        m_movestate = MoveState::FLYING;
        m_transform->scale *= 2;
        m_collider->radius *= 2;
        m_rigidbody->force -= (getJumpForce()* gravDir) * dt;
        m_display->setTextureId("sprRocketPlayer");
        m_dirPlanet = destination_;
        m_rigidbody->gravity = destination_->getComponent<BE::Component::Transform>()->position;
        m_collider->ghost = true;

    }

    void Player::powerUp(void)
    {
       // setMoveForce(CHANGE_MOVE_FORCE);
        m_change = true;
		//if (increasingParticle >= 200)
		//	return;
		//if (increasingParticle < 200)
		//{
		//	m_particle->setCapacity(++increasingParticle);
		//}
		//m_particle->size.x = 50;
		//m_particle->size.y = 50;
  //      m_particle->maxscale = 50;
  //      m_particle->maxvel = 50;
		//m_particle->lifetime = 2.5;
  //      m_particle->particleType = BE::ParticleType::ONE;
		//m_particle->loop = true;
		//m_particle->fade = true;
		m_particle->_texture.setTextureId("sprParticle");
  //      m_particle->resetParticles();


        m_display->setTextureId("sprChange");

    }

	void Player::TailParticle(int i)
	{
		
		m_particle->setCapacity(i);
		

		//m_particle->setCapacity(i);
		m_particle->size.x = 20;
		m_particle->size.y = 50;
		m_particle->maxscale = 130;
		m_particle->maxvel = 60;
		m_particle->lifetime = 2.5;
		m_particle->particleType = BE::ParticleType::THREE;
		m_particle->_texture.setTextureId("sprBasicParticle");
		m_particle->loop = true;
		m_particle->fade = true;
		//m_particle->resetParticles();

	}

    void Player::powerDown(void)
    {
        //setMoveForce(MOVE_FORCE);
        m_change = false;
		m_particle->_texture.setTextureId("sprBasicParticle");
        m_display->setTextureId("sprBasicPlayer");
    }


    //Movements
				void Player::movementControl(float dt) {

								BE::HBVec2 gravDir(
												m_rigidbody->gravity.x - m_transform->position.x,
												m_rigidbody->gravity.y - m_transform->position.y);
								gravDir.Normalize();
								BE::HBVec2 movDir(gravDir);
								movDir.Rotate(BE::HBMath::DegreeToRadian(90));

								Input::InputType inputType;

								bool upIsDown = Input::isPressed(Input::UP, &inputType);
								bool downIsDown = Input::isPressed(Input::DOWN, &inputType);
								bool leftIsDown = Input::isPressed(Input::LEFT, &inputType);
								bool rightIsDown = Input::isPressed(Input::RIGHT, &inputType);
								bool jumpIsDown = Input::isPressed(Input::JUMP, &inputType);
								bool superIsDown = Input::isPressed(Input::SUPER, &inputType);


								int isMoving = upIsDown + downIsDown + leftIsDown + rightIsDown;

								if (Input::isTriggered(Input::JUMP)) {
												m_canjump = true;

								}

								//if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_RIGHT))
								//{
								//	if(m_transform->scale.x > 0)
								//		m_transform->scale.x *= -1;
								//	m_display->playAnim("animPlayerWalk");
								//}
								//else if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LEFT))
								//{
								//	if (m_transform->scale.x < 0)
								//		m_transform->scale.x *= -1;
								//	m_display->playAnim("animPlayerWalk", false);
								//}
								//else
								//{
								//	//m_display->stopAnim();
								//	//
								//}
								//
								//Movement state
								switch (m_movestate)
								{
								case MoveState::STAND: {
												m_rigidbody->vel.Zero();
												//ChangeCharacter();
												if (superIsDown)
												{
																if (m_change == true)
																{
																				m_display->playAnim("animPounding", false);
																				m_dirPlanet->getComponent<BE::Component::Display>()->playAnim("animShaking", false);
																}
																// else
																				// m_display->playAnim("animBasicPunch", false);
												}
												if (!m_onground) {
																m_movestate = MoveState::JUMP;
																break;
												}
												//if right or left key is pressed, player walks.
												if (isMoving) {
																m_movestate = MoveState::WALK;
																break;
												}
												//Stand Jump
												else if (jumpIsDown &&
																m_rigidbody->vel.LengthSquared() < getVelSquarMax() &&
																m_canjump) {
																m_rigidbody->force -= (getJumpForce()* gravDir) * dt;
																m_movestate = MoveState::JUMP;

																//Play the Jump sound
																if (sndJump->second->type == BE::Prop::AUDIO && b_sndJump == true) {
																				static_cast<BE::Prop::Audio*>(sndJump->second)->play();
																				b_sndJump = false;
																}

																break;
												}

								}break; // Stand
								case MoveState::WALK: {

												//Walk to Stand
												if (!isMoving) {
																m_movestate = MoveState::STAND;
																m_rigidbody->vel.Zero();
																m_display->stopAnim();
																break;
												}
												//Walking

												if (isMoving && m_rigidbody->vel.LengthSquared() < getVelSquarMax()/*Limit vel*/) {

																if (inputType == Input::KEYBOARD)
																{
																				m_inputstate = KEYBOARD;
																				if (rightIsDown)
																				{
																								m_rigidbody->force += (getMoveForce()* movDir) * dt;
																								if (m_transform->scale.x > 0)
																												m_transform->scale.x *= -1;
																				}
																				else if (leftIsDown)
																				{
																								m_rigidbody->force -= (getMoveForce() * movDir) * dt;
																								if (m_transform->scale.x < 0)
																												m_transform->scale.x *= -1;
																				}
																}
																else if (inputType == Input::GAMEPAD)//
																{
																				m_inputstate = GAMEPAD;

																				glm::vec2 stickPos = BE::Input::Gamepad::instance()->getLeftStick();
																				float angle = glm::degrees(glm::atan(stickPos.x, stickPos.y));

																				glm::vec3 relativePositon = m_transform->position - m_dirPlanet->getComponent<BE::Component::Transform>()->position;
																				float playerAngle = glm::degrees(glm::atan(relativePositon.x, relativePositon.y));

																				int direction = getClosestAngleDir(playerAngle, angle);

																				if (playerAngle < angle - 1 || playerAngle > angle + 1)
																				{
																								if (direction > 0)
																								{
																												m_rigidbody->force += (getMoveForce()* movDir) * dt;
																												if (m_transform->scale.x > 0)
																																m_transform->scale.x *= -1;
																								}
																								else
																								{
																												m_rigidbody->force -= (getMoveForce() * movDir) * dt;
																												if (m_transform->scale.x < 0)
																																m_transform->scale.x *= -1;
																								}
																				}
																				else
																				{
																								m_rigidbody->vel.Zero();
																								m_display->stopAnim();
																				}
																}

																//ChangeCharacter();
																if (superIsDown)
																{
																				if (m_change == true)
																				{
																								m_display->playAnim("animPounding", false);
																								m_dirPlanet->getComponent<BE::Component::Display>()->playAnim("animShaking", false);
																				}
																				//else
																								//m_display->playAnim("animBasicPunch", false);
																}
																else if (m_change == true)
																{
																				m_display->playAnim("animPlayerWalk");
																}
																else
																				m_display->playAnim("animChangePlayer");
												}
												//Walk to Jump
												if (jumpIsDown &&
																m_rigidbody->vel.LengthSquared() < getVelSquarMax() &&
																m_canjump) {
																m_rigidbody->force -= (getJumpForce()* gravDir) * dt;
																//m_display->playAnim("animPunch", false);
																m_movestate = MoveState::JUMP;

																//Play the Jump sound
																if (sndJump->second->type == BE::Prop::AUDIO && b_sndJump == true) {
																				static_cast<BE::Prop::Audio*>(sndJump->second)->play();
																				b_sndJump = false;
																}

																break;
												}
												/*   else if (!m_onground) {
																			m_movestate = MoveState::JUMP;
																			break;
															}*/

								}break;//Walk
								case MoveState::JUMP: {


												//Moving during Jump
												if (rightIsDown &&
																m_rigidbody->vel.LengthSquared() < getVelSquarMax()) {
																m_rigidbody->force += (getMoveForce()* movDir) * dt;
																//ChangeCharacter();
												}
												else if (leftIsDown &&
																m_rigidbody->vel.LengthSquared() < getVelSquarMax()) {
																m_rigidbody->force -= (getMoveForce() * movDir) * dt;
																//ChangeCharacter();
												}

												if (m_onground) {

																if (!isMoving) {
																				m_movestate = MoveState::STAND;
																				m_rigidbody->vel.Zero();
																}
																else {
																				m_movestate = MoveState::STAND;
																}

																//Stop Jump sound
																if (sndJump->second->type == BE::Prop::AUDIO && b_sndJump == false) {
																				static_cast<BE::Prop::Audio*>(sndJump->second)->stop();
																				b_sndJump = true;
																}
												}
								}break; // Jump
								case MoveState::FLYING: {

												//Play Flying sound
												if (sndFlying->second->type == BE::Prop::AUDIO && b_sndFlying == true) {
																static_cast<BE::Prop::Audio*>(sndFlying->second)->play();
																b_sndFlying = false;
												}

												if (m_change == false)
																m_display->setTextureId("sprRocketPlayer");
												else
																m_display->setTextureId("sprSuperFly");
												//BE::Core::Debugger::instance()->AddLog("Charactor name '%s' do not have rigidbody \n", m_actor->_name.c_str());
												m_display->stopAnim();

												if (BE::Core::Physics::instance()->Collision(m_dirPlanet, m_actor) == BE::Core::Physics::CS_Start)
												{
																if (m_change == false)
																				m_display->setTextureId("sprBasicPlayer");
																else
																				m_display->setTextureId("sprAnimWalk");

																m_collider->ghost = false;
																m_transform->scale *= 0.5f;
																m_collider->radius *= 0.5f;
																m_movestate = MoveState::STAND;

																//Stop Flying Sound
																if (sndFlying->second->type == BE::Prop::AUDIO && b_sndFlying == false) {
																				static_cast<BE::Prop::Audio*>(sndFlying->second)->stop();
																				b_sndFlying = true;
																}

												}
								}break;//Flying

								}//swtich

				}
				void Player::smoothRotation(float dt_)
				{
								if (m_transform->rotation != rotationTarget) // Please help me with these maths
								{
												static float _cooldown = 0.f;

												_cooldown -= dt_;
												if (_cooldown <= 0.f)
												{
																_cooldown = 0.01f;
																float currentRotation = m_transform->rotation;
																float rotDistance;
																int rotSign;
																float rotMoveDistance = 12.f;

																rotDistance = currentRotation - rotationTarget;

																rotDistance = abs(rotDistance);
																rotSign = getClosestAngleDir(currentRotation, rotationTarget);

																if (rotDistance < rotMoveDistance)
																{
																				currentRotation = rotationTarget;
																}
																else
																{
																				currentRotation += rotMoveDistance * rotSign;
																}
																m_transform->rotation = currentRotation;
												}
								}
				}

    int Player::getClosestAngleDir(float angle1_, float angle2_)
    {
        double diff1 = (int(angle2_ - angle1_) + 180) % 360 - 180;
        diff1 = diff1 < -180 ? diff1 + 360 : diff1;

        return diff1 > 0 ? 1 : -1;
    }

    //void Player::ChangeCharacter() {
    //    if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_s))
    //    {

    //        setMoveForce(CHANGE_MOVE_FORCE);
    //        m_change = true;
    //        m_particle->capacity = 100;
    //        m_particle->maxscale = 50;
    //        m_particle->maxvel = 50;
    //        m_particle->particleType = BE::ParticleType::ONE;
    //        m_display->setTextureId("sprChange");

    //    }

    //    if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_d))
    //    {
    //        setMoveForce(MOVE_FORCE);
    //        m_change = false;
    //        m_particle->capacity = 0;
    //        m_display->setTextureId("sprBasicPlayer");

    //    }

    //}

    const float Player::getJumpForce(void) const {
        return JUMP_FORCE;
    }

    void Player::setJumpForce(float input) {
        JUMP_FORCE = input;
    }

    const float Player::getMoveForce(void) const {
        return MOVE_FORCE;
    }

    void Player::setMoveForce(float input) {
        MOVE_FORCE = input;
    }

    const float Player::getDamping(void) const {
        return DAMPING;
    }

    void Player::setDamping(float input) {
        DAMPING = input;
    }

    const float Player::getVelSquarMax(void) const {
        return VELSQUARMAX;
    }

    void Player::setVelSquarMax(float input) {
        VELSQUARMAX = input;
    }

    const glm::vec2 Player::getAnchorPoint()
    {
        glm::vec2 retVal;

        retVal.x = m_rigidbody->gravity.x;
        retVal.y = m_rigidbody->gravity.y;
        return retVal;
    }

				void Player::shutdownSounds(void)
				{
								if (sndFlying->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndFlying->second)->stop();
								}
								if (sndJump->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndJump->second)->stop();
								}
								if (sndPowerup->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndPowerup->second)->stop();
								}
				}

				void Player::resumeSounds(void)
				{
					if (sndFlying->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndFlying->second)->resume();
								}
								if (sndJump->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndJump->second)->resume();
								}
								if (sndPowerup->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndPowerup->second)->resume();
								}

				}

				void Player::pauseSounds(void)
				{
					if (sndFlying->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndFlying->second)->pause();
								}
								if (sndJump->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndJump->second)->pause();
								}
								if (sndPowerup->second->type == BE::Prop::AUDIO) {
												static_cast<BE::Prop::Audio*>(sndPowerup->second)->pause();
								}

				}


    void Player::planetMovement(LevelSetting& LvSetting, float dt_) {

        smoothRotation(dt_);

            //BE::Core::Debugger::instance()->AddLog(" %.5f\n", sum);

        //Control
        movementControl(dt_);

        //Damping only not in the ground(planet)
        if (!m_onground) {
            m_rigidbody->vel *= getDamping();
        }

        //OnGround test
        for (auto & planet : LvSetting.planetVector) {
            BE::Actor* planetActor = planet.GetOwner();
            if (BE::Core::Physics::instance()->Collision(planetActor, m_actor) == BE::Core::Physics::CS_Start ||
                BE::Core::Physics::instance()->Collision(planetActor, m_actor) == BE::Core::Physics::CS_OnCollision) {
                m_onground = true;
                break;
            }
            m_onground = false;
        }
    }

    void Player::planetGravity(LevelSetting& LvSetting, float) {

        if (!m_rigidbody) {
            BE::Core::Debugger::instance()->AddLog("-------------------------------------------\n");
            BE::Core::Debugger::instance()->AddLog("Charactor name '%s' do not have rigidbody \n", m_actor->_name.c_str());
            BE::Core::Debugger::instance()->AddLog("-------------------------------------------\n");
            return;
        }

        for (auto & planet : LvSetting.planetVector) {
            BE::Actor* planetActor = planet.GetOwner();

            BE::HBVec2 charPos(m_transform->position.x,
                m_transform->position.y);
            BE::HBVec2 planetPos(planetActor->getComponent<BE::Component::Transform>()->position.x,
                planetActor->getComponent<BE::Component::Transform>()->position.y);
            BE::HBVec2 recentGravity((m_rigidbody->gravity.x) - (charPos.x),
                (m_rigidbody->gravity.y) - (charPos.y));
            BE::HBVec2 planetGravity((planetPos.x) - (charPos.x),
                (planetPos.y) - (charPos.y));

            float planetRad = planetActor->getComponent<BE::Component::CircleCollider>()->radius;
            //float recentRad = ->getComponent<BE::Component::CircleCollider>()->radius;
            //switch
            if (m_movestate != MoveState::FLYING)
            {
                if (planetGravity.Length() - planetRad < recentGravity.Length() - prevRadius) {
                    m_rigidbody->gravity = planetPos;
                    prevRadius = planetRad;
                    m_planetNum = planet.GetNumber();
                    m_dirPlanet = planet.GetOwner();
                    m_canjump = false;
                }
            }
            BE::HBVec2 ImageRot = { m_rigidbody->gravity.x - charPos.x,m_rigidbody->gravity.y - charPos.y };
            if (m_movestate == MoveState::JUMP)
            {
                rotationTarget = BE::HBMath::RadianToDegree(atan2f(ImageRot.y, ImageRot.x)) + 90;
            }
            else
            {
                rotationTarget = BE::HBMath::RadianToDegree(atan2f(ImageRot.y, ImageRot.x)) + 90;
                m_transform->rotation = rotationTarget;
            }
        }




    }


}


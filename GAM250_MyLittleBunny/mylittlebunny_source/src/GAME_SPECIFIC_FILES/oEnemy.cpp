/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    oEnemy.cpp
Purpose:       This file contain Enemy object codes.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh, Wonjae Jung(particle)
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

#include <GAME_SPECIFIC_FILES/LevelSetting.hpp>

#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>

namespace Stage {
/***************************************************

Real Definition of the Classses

Enemy

****************************************************/
// Real Definition of the Enemy
Enemy::Enemy()
{

}
Enemy::Enemy(BE::Actor* rhs)
{
    // Set variables from the parent
    owner = rhs;
    number = enemyNum;
    ++enemyNum;
    health = 10;						// set initial value with 10
    type = type_ENEMY;

    m_transform = owner->getComponent<BE::Component::Transform>();
    m_transform->position.z = 2;
    m_display = owner->getComponent<BE::Component::Display>();
    m_rigidbody = owner->getComponent<BE::Component::Rigidbody>();
    m_particle = owner->getComponent<BE::Component::ParticleEmitter>();

    // Set variable of Enemy
    e_LifeTimer = 0;
    e_deadTimer = 0;
    e_damageTimer = 0;
	e_damageMaxTimer = 2.f;
	e_Growth = 1;
}

Enemy::~Enemy()
{

}

void Enemy::setEnemy(BE::Actor* rhs)
{
    owner = rhs;
    //number = enemyNum;
    //++enemyNum;

    m_transform = owner->getComponent<BE::Component::Transform>();
    m_display = owner->getComponent<BE::Component::Display>();
    m_rigidbody = owner->getComponent<BE::Component::Rigidbody>();
    m_collider = owner->getComponent<BE::Component::CircleCollider>();
    m_particle = owner->getComponent<BE::Component::ParticleEmitter>();

    InitEnemy();
}

void Enemy::InitEnemy(void)
{
    health = 10; // set initial value with 10
    type = type_ENEMY;
    condition = cond_eFlying;
    e_LifeTimer = 0;
    e_deadTimer = 0;
    e_damageTimer = 0;
	e_damageMaxTimer = 2.f;
    e_Growth = 1;

    m_transform->position.z = 2;
    m_transform->scale = { 1.5f, 1.5f };
    m_rigidbody->staticstate = false;
    m_collider->ghost = true;
    m_display->setTextureId("sprEnemiesSheet", 6);
	m_display->stopAnim();

    sndHit = BE::PropManager::instance()->lookupValue("sndHit");

}

void Enemy::setEnemyNum(int i)
{
    number = i;
}
void Enemy::setPlanetNum(int i)
{
e_PlanetNum = i;
    //planetNum = i;
}
void Enemy::ActiveEnemy(void)
{
    owner->_isActive = true;
}
void Enemy::InactiveEnemy(void)
{
    owner->_isActive = false;
    condition = cond_DEAD;
    ++deadEnemyNum;
    m_rigidbody->gravityscale = 0;
}
void Enemy::EnemyUpdate(LevelSetting & LvSetting, float dt)
{
    static bool buttonIsDown = false;
    static bool prevState = false;

    BE::Actor* player = LvSetting.player->m_actor;
    buttonIsDown = BE::Input::Gamepad::instance()->IsPressed(BE::GP::BUTTON_B);

    if (owner_Planet != nullptr)
        if (owner_Planet->GetOwner()->getComponent<BE::Component::Display>()->animPlaying == true && condition != cond_eFlying)
            //if (owner_Planet->Shaking == true && condition != cond_eFlying)
        {
            BE::HBVec2 gravDir(
                m_rigidbody->gravity.x - m_transform->position.x,
                m_rigidbody->gravity.y - m_transform->position.y);
            gravDir.Normalize();
			DecreaseHealth(1000);
			m_display->playAnim("animSpin", true);
            m_rigidbody->force -= (500000 * gravDir) * dt;

        }

    if (condition != cond_eFlying)
    {
        BE::HBVec2 ownerPos(m_transform->position.x, m_transform->position.y);

        if (BE::HBVec2::Distance(ownerPos, m_rigidbody->gravity) >= 1000)
        {
            DecreaseHealth(100);
        }
    }
    if (/*condition == cond_eFlying && */BE::Core::Physics::instance()->Collision(player, owner) == BE::Core::Physics::CS_Start)
    {
        if (condition == cond_eFlying)
        {
            if (LvSetting.player->m_movestate == Player::MoveState::FLYING)
            {
                DecreaseHealth(1000);
				m_display->playAnim("animSpin", true);
                m_collider->ghost = true;
            }
        }
        else
        {
            DecreaseHealth(1000);
			m_display->playAnim("animSpin", true);
            m_collider->ghost = true;
        }
    }

    if (BE::Core::Physics::instance()->Collision(player, owner) == BE::Core::Physics::CS_OnCollision)
    {
        if (condition == cond_eFlying)
        {
            //BE::Core::Debugger::instance()->AddLog("Enemy is flying to work!");
            if (LvSetting.player->m_movestate == Player::MoveState::FLYING)
            {
                DecreaseHealth(1000);
                m_display->playAnim("animSpin", true);
                m_collider->ghost = true;
            }
        }
        prevState = buttonIsDown;
    }
    //
    if (owner_Planet != nullptr)
    {
        if (BE::Core::Physics::instance()->Collision(owner_Planet->GetOwner(), owner) == BE::Core::Physics::CS_Start
            && condition == cond_eFlying
            )
        {
            m_display->setTextureId("sprEnemySheet1", 1);
            condition = cond_WORKING;
            m_rigidbody->vel.Zero();
            m_rigidbody->force.Zero();
            m_collider->ghost = false;
            
            if (particleSet == false)
            {
                particleSet = true;

                m_particle->setCapacity(30);
                m_particle->size = glm::vec2(60.0f);
                m_particle->maxvel = 200;
				m_particle->minvel = 50;
                m_particle->loop = false;
				m_particle->fade = true;
				m_particle->lifetime = 2.f;
                m_particle->particleType = BE::ParticleType::THREE;
                m_particle->_texture.setTextureId("sprSmoke");
                m_particle->resetParticles();
            }
        }
    }
    else
    {
        // BE::Core::Debugger::instance()->AddLog("Enemy %d does not have owner planet\n", number);
    }

}

void Enemy::Update(LevelSetting& LvSetting, float dt)
{

    BE::HBVec2 charPos(m_transform->position.x,
        m_transform->position.y);
    if (m_rigidbody != nullptr)
    {
        BE::HBVec2 ImageRot(m_rigidbody->gravity.x - charPos.x, m_rigidbody->gravity.y - charPos.y);
        m_transform->rotation = BE::HBMath::RadianToDegree(atan2f(ImageRot.y, ImageRot.x)) + 90; // rotate with 90degree by radian
    }

    if (owner_Planet != nullptr && owner_Planet->GetCondition() == cond_DEAD && condition != cond_DEAD)
    {
        InitEnemy();
        SetGravity(LvSetting.planetVector, LvSetting.max_planetNum);
    }

    EnemyUpdate(LvSetting, dt);
    Damage(LvSetting, dt);
    if (condition == cond_WORKING)
    {
        Movement(LvSetting, dt);
        Growing(dt);
		Attack(dt);
    }
}
void Enemy::Attack(float dt)
{
    e_damageTimer += dt;

    if (e_damageTimer >= e_damageMaxTimer)
    {
        owner_Planet->isAttacked = true;
		//e_animConnection = m_display->spriteIndex;
		m_display->playAnim("animEnemyPump", false);

		if (!owner_Planet->immortal)
			owner_Planet->DecreaseHealth(e_Growth);

        e_damageTimer = 0;
    }
}

void Enemy::Growing(float dt)
{

    //owner_Planet->isAttacked = true;

    if (e_Growth >= 3)
        return;


    e_LifeTimer += dt;
    // Enemy Growing
    if (e_LifeTimer >= 5)
    {
        if (e_Growth == 1)
        {
            e_Growth = 2;
            //health *= 2;
            m_transform->scale *= 1.25;
            m_display->setTextureId("sprEnemySheet2", 1);
            e_LifeTimer = 0;
			if (!owner_Planet->immortal)
				owner_Planet->DecreaseHealth(1);
			m_display->stopAnim();
        }
        else if (e_Growth == 2 && 
            BE::Core::Physics::instance()->Collision(owner_Planet->GetOwner(), owner) == 
            BE::Core::Physics::CS_OnCollision)
        {
            e_Growth = 3;
            m_rigidbody->staticstate = true;
            m_collider->ghost = true;
            //condition = cond_eFixed;
            //health *= 2;
            m_transform->scale *= 1.25;
            m_display->setTextureId("sprEnemySheet3", 1);
			if (!owner_Planet->immortal)
				owner_Planet->DecreaseHealth(2);
			m_display->stopAnim();
		}
    }
}

void Enemy::Damage(LevelSetting& LvSetting, float dt)
{
    if (health <= 0)
    {
        e_deadTimer += dt;
        if (condition != cond_DEAD)
        {
            ++LvSetting.deadEnemyNum;
            ++LvSetting.powerupCount;
            condition = cond_DEAD;
            //Decrease number of enemy which is on planet
            --owner_Planet->enemyNum;
            m_collider->ghost = true;
            //m_rigidbody->staticstate = true;
            m_display->setTextureId("sprEnemiesSheet", 5);
            owner_Planet->isAttacked = false;

			if(LvSetting.player->m_change == false)
				++LvSetting.player->m_powerGage;
			
			if (LvSetting.player->m_powerGage >= 10.f)
				LvSetting.player->m_powerGage = 10.f;

            //Play the Jump sound
            if (sndHit->second->type == BE::Prop::AUDIO) {
                static_cast<BE::Prop::Audio*>(sndHit->second)->play();
            }
        }
        if (e_deadTimer >= 0.5f)
        {
            InactiveEnemy();
        }
    }
}
const int Enemy::GetPlanetNum(void) const
{
    return planetNum;
}

void Enemy::Movement(LevelSetting& lvSetting, float dt)
{
    //m_rigidbody->gravityscale = 100000.f;
    m_rigidbody->force = movDir * dt * 5000.f;

    //for(m_collider->)
    for (auto enemies : lvSetting.enemyVector)
    {
        BE::Actor* enemOwn = enemies.GetOwner();
        if (enemOwn != owner)
			if (BE::Core::Physics::instance()->Collision(enemies.GetOwner(), owner) == BE::Core::Physics::CS_Start)
			{
				movDir *= -1;
				m_transform->scale.x *= -1;
			}
    }

	// Set Animation
	if (m_display->animPlaying == false)
	{
		if (e_Growth == 1)
		{
			m_display->playAnim("animEnemyMove1", false);
			//m_display->spriteIndex = e_animConnection;
		}
		else if (e_Growth == 2)
		{
			m_display->playAnim("animEnemyMove2", false);
			//m_display->spriteIndex = e_animConnection;
		}
		else if (e_Growth == 3)
		{
			m_display->playAnim("animEnemyMove3", false);
			//m_display->spriteIndex = e_animConnection;
		}
	}
}

void Enemy::SetGravity(std::vector<Planet>& planetVector, int size)
{
    if (m_rigidbody == nullptr)
        return;

    do {
        setPlanetNum(BE::HBRandom::GetInt(1, size));
        BE::Core::Debugger::instance()->AddLog("Enemy%d direction is %d \n", number, planetNum);

        for (auto & planet : planetVector)
        {
            if (planet.GetNumber() == e_PlanetNum)
            {
                BE::Core::Debugger::instance()->AddLog("Enemy%d direction is %d \n", number, planetNum);
                owner_Planet = &planet;
                BE::Component::Transform* planetTransform = planet.GetOwner()->getComponent<BE::Component::Transform>();
                m_rigidbody->gravity = { planetTransform->position.x, planetTransform->position.y };
				m_rigidbody->force = 0;
				m_rigidbody->vel = 0;
                m_rigidbody->gravityscale = 500.f;
                break;
            }
        }
        BE::HBVec2 gravDir(
            m_rigidbody->gravity.x - m_transform->position.x,
            m_rigidbody->gravity.y - m_transform->position.y);
        gravDir.Normalize();
        movDir = gravDir;
        movDir.Rotate(BE::HBMath::DegreeToRadian(-90));

        //Number of enemy which is on planet
        ++owner_Planet->enemyNum;
        if (owner_Planet->GetCondition() != cond_DEAD)
        {
            BE::Core::Debugger::instance()->AddLog("PLANET ALIVE, LOOP DONE \n", number, planetNum);
        }
        else if (owner_Planet->GetCondition() == cond_DEAD)
        {
            BE::Core::Debugger::instance()->AddLog("PLANET DEAD, DO IT AGAIN \n", number, planetNum);
        }
    } while (owner_Planet->GetCondition() == cond_DEAD);

}

}
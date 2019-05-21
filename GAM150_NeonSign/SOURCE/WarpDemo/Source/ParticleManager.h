/******************************************************************************/
/*!
\file   ParticleManager.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  This is the header file for all member functions of a class called
				ParticleManager.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef ParticleManager_H
#define ParticleManager_H

#include "WEVec2.h"
#include "GameTypes.h"

//! Particle
struct Particle
{
	WEVec2 pos; //!< position
	WEVec2 vel; //!< velocity
	float scale; //!< scale
};

//! EmitterType
enum EmitterType
{
	ET_EXPLOSION, //!< Explosion
	ET_TRAIL,     //!< Trail
	ET_DEFAULT    //!< Defalut
};

//! Emitter
struct Emitter
{
	Particle*   pParitcles;  //!< pointer of particles
	EmitterType type;        //!< Emitter type
	WEVec2      pos;         //!< position
	WEVec2      vel;         //!< velocity
	int         textureID;   //!< texture
	int         size;        //!< size
	int         capacity;    //!< max particle number of emitter
	int         emitterID;   //!< ID
	float       lifeTime;    //!< lifeTime
};

/******************************************************************************/
/*!
\class ParticleManager

\brief
The class that manage the particles.
*/
/******************************************************************************/
class ParticleManager
{
public:
	ParticleManager(int maxExpCount);
	~ParticleManager(void);

	void     LoadFile(const char* pFileName);
	Emitter* GetExpEmitters(void);
	Emitter* GetTrailEmitters(void);
	int      GetExpEmmiterCount(void);
	void      AddTrailEmitter(int particleCount,
		const WEVec2& pos,
		const WEVec2& vel,
		int textureID,
		EmitterType type);
	void      AddExpEmitter(int particleCount,
		const WEVec2& pos,
		const WEVec2& vel,
		int textureID,
		EmitterType type);
	void     UpdateEmitter(Ball *pBalls, Emitter *pEmitter, float dt);
	void     DrawEmitter(const Emitter *pEmitter);
	void     DeleteExpEmitter(int emitterID);

private:
	void InitExplosionSystem(Emitter* pEmitter);
	void InitTrailSystem(Emitter* pEmitter);

	Emitter* m_pTrailEmitters; //!< A pointer of m_pEmitters
	Emitter* m_pExpEmitters;
	int m_expcapacity;  //!< max number of emitter
	int m_expsize;      //!< size of emitter
	int m_expcurrentID;
	int m_trailcapacity;

	float m_minExpVel;  //!< min velocity of explosion emitter
	float m_maxExpVel;  //!< max velocity of explosion emitter
	float m_minExpScale;  //!< min scale of explosion emitter
	float m_maxExpScale;  //!< max scale of explosion emitter

	float m_minTrailVel;  //!< min velocity of trail emitter
	float m_maxTrailVel;  //!< max velocity of trail emitter
	float m_minTrailScale;  //!< min scale of trail emitter
	float m_maxTrailScale;  //!< max scale of trail emitter

	float m_scaleFactor;  //!< scaleFactor of particles
	float m_expLife;  //!< max time of emitter

};

#endif /*ParticleManager_H*/

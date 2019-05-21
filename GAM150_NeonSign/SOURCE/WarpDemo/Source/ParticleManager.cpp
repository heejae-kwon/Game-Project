/******************************************************************************/
/*!
\file   ParticleManager.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  This is the interface file for all member functions of a class called
				ParticleManager.

	“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "ParticleManager.h"
#include "WEMath.h"
#include "WEMtx44.h"
#include "WERandom.h"
#include "WEDebugTools.h"
#include "WEGraphics.h"
#include <cmath> /*atan2*/
#include <cstdio> /*FILE* fopen, fclose fscanf*/

/******************************************************************************/
/*!
\brief
Load datas from the text file.

\param pFileName
A pointer of file
*/
/******************************************************************************/
void ParticleManager::LoadFile(const char* pFileName)
{
	FILE* pFile = 0;
	fopen_s(&pFile, pFileName, "rt");
	if (!pFile)
		return;

	fscanf_s(pFile, "%f", &m_minExpVel);
	fscanf_s(pFile, "%f", &m_maxExpVel);
	fscanf_s(pFile, "%f", &m_minExpScale);
	fscanf_s(pFile, "%f", &m_maxExpScale);

	fscanf_s(pFile, "%f", &m_minTrailVel);
	fscanf_s(pFile, "%f", &m_maxTrailVel);
	fscanf_s(pFile, "%f", &m_minTrailScale);
	fscanf_s(pFile, "%f", &m_maxTrailScale);

	fscanf_s(pFile, "%f", &m_scaleFactor);
	fscanf_s(pFile, "%f", &m_expLife);

	fclose(pFile);
}

/******************************************************************************/
/*!
\brief
		Constructor of ParticleManager class. Initialize all data of emitter
		and pParitcle.

\param maxExpCount
		An integer that max count of Expemitter.
*/
/******************************************************************************/
ParticleManager::ParticleManager(int maxExpCount)
{
	m_pTrailEmitters = new Emitter;
	m_pExpEmitters = new Emitter[maxExpCount];

	//Initialize data
	for (int i = 0; i < maxExpCount; ++i)
	{
		m_pExpEmitters[i].pos = { 0, 0 };
		m_pExpEmitters[i].vel = { 0, 0 };
		m_pExpEmitters[i].textureID = 0;
		m_pExpEmitters[i].size = 0;
		m_pExpEmitters[i].capacity = 0;
		m_pExpEmitters[i].emitterID = 0;
		m_pExpEmitters[i].lifeTime = 0;
		m_pExpEmitters[i].pParitcles = 0;
	}

		m_pTrailEmitters->pos = { 0, 0 };
		m_pTrailEmitters->vel = { 0, 0 };
		m_pTrailEmitters->textureID = 0;
		m_pTrailEmitters->size = 0;
		m_pTrailEmitters->capacity = 0;
		m_pTrailEmitters->emitterID = 0;
		m_pTrailEmitters->lifeTime = 0;
		m_pTrailEmitters->pParitcles = 0;

	m_expsize = 0;
	m_expcurrentID = 0;
	m_expcapacity = maxExpCount;

	LoadFile("Source/ParticleProperties.txt");
}

/******************************************************************************/
/*!
\brief
Destructor of ParticleManager class. Delete particles and emitters.
*/
/******************************************************************************/
ParticleManager::~ParticleManager(void)
{
	//delete paritcles
	for (int i = 0; i < m_expcapacity; ++i)
	{
		delete[] m_pExpEmitters[i].pParitcles;
		m_pExpEmitters[i].pParitcles = 0;
	}


		delete[] m_pTrailEmitters->pParitcles;
		m_pTrailEmitters->pParitcles = 0;

	delete m_pTrailEmitters;
	m_pTrailEmitters = 0;

	//delete emitters
	delete[] m_pExpEmitters;
	m_pExpEmitters = 0;
}

/******************************************************************************/
/*!
\brief
Return the Expemitter pointer that is placed in private.

\return m_pExpEmitters
		A pointer of ExpEmitters
*/
/******************************************************************************/
Emitter* ParticleManager::GetExpEmitters(void)
{
	return m_pExpEmitters;
}

/******************************************************************************/
/*!
\brief
Return the Trailemitter pointer that is placed in private.

\return m_pTrailEmitters
A pointer of TrailEmitters
*/
/******************************************************************************/
Emitter* ParticleManager::GetTrailEmitters(void)
{
	return m_pTrailEmitters;
}
/******************************************************************************/
/*!
\brief
Return the size of exemitters.

\return m_expsize
The integer that size of emitters.
*/
/******************************************************************************/
int ParticleManager::GetExpEmmiterCount(void)
{
	return m_expsize;
}


/******************************************************************************/
/*!
\brief
Add trailemitter's data to emitter.

\param particleCount
An integer that count of paritcles.

\param pos
A vector that position of emitter.

\param vel
A vector that velocity of emitter.

\param textureID
An integer that textureID of emitter

\param type
A enum type that type of emiiter.

*/
/******************************************************************************/
void ParticleManager::AddTrailEmitter(int particleCount,
	const WEVec2& pos,
	const WEVec2& vel,
	int textureID,
	EmitterType type)
{	//check if current emitter has enough space
	//get ref to current emitter


	//check if current emitter has enough space
	m_pTrailEmitters->pParitcles = new Particle[particleCount];
	m_pTrailEmitters->size = particleCount;
	m_pTrailEmitters->capacity = particleCount;

	//loop at set pos, vel, type
	m_pTrailEmitters->pos = pos;
	m_pTrailEmitters->vel = vel;
	m_pTrailEmitters->textureID = textureID;
	m_pTrailEmitters->type = type;

	InitTrailSystem(m_pTrailEmitters);
}

/******************************************************************************/
/*!
\brief
Add explosion emitter's data to emitter.

\param particleCount
An integer that count of paritcles.

\param pos
A vector that position of emitter.

\param vel
A vector that velocity of emitter.

\param textureID
An integer that textureID of emitter

\param type
A enum type that type of emiiter.

*/
/******************************************************************************/
void ParticleManager::AddExpEmitter(int particleCount,
	const WEVec2& pos,
	const WEVec2& vel,
	int textureID,
	EmitterType type)
{	
	//check if current emitter has enough space
	//get ref to current emitter
	Emitter *pEmitter = &m_pExpEmitters[m_expsize];

	//check if current emitter has enough space
		pEmitter->pParitcles = new Particle[particleCount];
		pEmitter->size = particleCount;
		pEmitter->capacity = particleCount;

	//loop at set pos, vel, type
	pEmitter->pos = pos;
	pEmitter->vel = vel;
	pEmitter->textureID = textureID;
	pEmitter->type = type;
	pEmitter->emitterID = m_expcurrentID;
	pEmitter->lifeTime = 0;

	//init particles (exp or trail)
	InitExplosionSystem(pEmitter);

	++m_expcurrentID;
	++m_expsize;
}

/******************************************************************************/
/*!
\brief
The function that delete explosion emitter.

\param emitterID
An emitter that will be deleted.
*/
/******************************************************************************/
void     ParticleManager::DeleteExpEmitter(int emitterID)
{
	--m_expsize;

	for (int i = 0; i <= m_expsize; ++i)
	{
		//find the emitter that will be deleted
		if (m_pExpEmitters[i].emitterID == emitterID)
		{
			//copy the data
			m_pExpEmitters[i].type = m_pExpEmitters[m_expsize].type;
			m_pExpEmitters[i].pos = m_pExpEmitters[m_expsize].pos;
			m_pExpEmitters[i].vel = m_pExpEmitters[m_expsize].vel;
			m_pExpEmitters[i].textureID = m_pExpEmitters[m_expsize].textureID;
			m_pExpEmitters[i].size = m_pExpEmitters[m_expsize].size;
			m_pExpEmitters[i].capacity = m_pExpEmitters[m_expsize].capacity;
			m_pExpEmitters[i].lifeTime = m_pExpEmitters[m_expsize].lifeTime;
			m_pExpEmitters[i].emitterID = m_pExpEmitters[m_expsize].emitterID;

			//copy the particle's data
			for (int j = 0; j < m_pExpEmitters[i].size; ++j)
			{
				m_pExpEmitters[i].pParitcles[j].pos = m_pExpEmitters[m_expsize].pParitcles[j].pos;
				m_pExpEmitters[i].pParitcles[j].vel = m_pExpEmitters[m_expsize].pParitcles[j].vel;
				m_pExpEmitters[i].pParitcles[j].scale = m_pExpEmitters[m_expsize].pParitcles[j].scale;
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
The function that update emitter

\param pBalls
A pointer of Balls.

\param pEmitter
A pointer of emitter.

\param dt
A float number that 1/fps.
*/
/******************************************************************************/
void     ParticleManager::UpdateEmitter(Ball *pBalls, Emitter *pEmitter, float dt)
{
//	WEDEBUG_PRINT("%d WTF", m_size);
  if (pEmitter->type == ET_EXPLOSION)
	{
		
		for (int i = 0; i < pEmitter->size; ++i)
		{
			pEmitter->pParitcles[i].pos += pEmitter->pParitcles[i].vel*dt;
		//	WEDEBUG_PRINT("%f\n", pEmitter.pParitcles[i].vel.x);
			//pEmitter.pParitcles[i].pos = pEmitter.pos;
			pEmitter->pParitcles[i].scale -= m_scaleFactor*dt;

			if (pEmitter->pParitcles[i].scale <= 0)
				pEmitter->pParitcles[i].scale = 0;

			//WEMath::Clamp(pEmitter.pParitcles[i].scale, 0, m_maxExpScale);
		}
		pEmitter->lifeTime += dt;

		if (pEmitter->lifeTime > m_expLife)
			DeleteExpEmitter(pEmitter->emitterID);
	}

   else if (pEmitter->type == ET_TRAIL)
	{
		pEmitter->pos = pBalls->pos;
		
		for (int i = 0; i < pEmitter->size; ++i)
		{
			//Initialize the trail paritcles
			if (pEmitter->pParitcles[i].scale == 0)
			{

				float Rotation = atan2(pEmitter->vel.y, pEmitter->vel.x);
				Rotation += WEMath::PI;
				Rotation += WERandom::GetFloat(-WEMath::HALF_PI * 0.5f, WEMath::HALF_PI * 0.5f);
				pEmitter->pParitcles[i].vel = { cosf(Rotation), sinf(Rotation) };

				float trailvel = WERandom::GetFloat(m_minTrailVel, m_maxTrailVel);
				pEmitter->pParitcles[i].vel *= trailvel;
				pEmitter->pParitcles[i].pos = pEmitter->pos;
				pEmitter->pParitcles[i].scale
					= WERandom::GetFloat(m_minTrailScale, m_maxTrailScale);

			}
			pEmitter->pParitcles[i].pos += pEmitter->vel*dt;
			pEmitter->pParitcles[i].pos += pEmitter->pParitcles[i].vel * dt;
			pEmitter->pParitcles[i].scale -= m_scaleFactor*dt*1.5f;

			if (pEmitter->pParitcles[i].scale < 0)
				pEmitter->pParitcles[i].scale = 0;
			//WEMath::Clamp(pEmitter->pParitcles[i].scale, 0, m_maxTrailScale);
		}
	}
}

/******************************************************************************/
/*!
\brief
The function that draw paritcles that is in the emitter.

\param pEmitter
A pointer of emitter
*/
/******************************************************************************/
void     ParticleManager::DrawEmitter(const Emitter *pEmitter)
{
	WEMtx44 transform;
	WEGraphics::SetTexture(pEmitter->textureID);

	for (int i = 0; i < pEmitter->size; ++i)
	{
		unsigned char Test = static_cast<unsigned char>(WERandom::GetInt(0, 255));

		WEGraphics::SetTextureColor(Test, 255, 255, 130);
		//Draw particles
		WEMtx44::MakeTransform(transform,
			pEmitter->pParitcles[i].scale,
			pEmitter->pParitcles[i].scale,
			WERandom::GetFloat(-WEMath::PI, WEMath::PI),
			pEmitter->pParitcles[i].pos.x, pEmitter->pParitcles[i].pos.y, 0.f);

		WEGraphics::Draw(transform);
	}
}

/******************************************************************************/
/*!
\brief
The function that initialize the explosion emitter.

\param pEmitter
A pointer of explosion emitter.
*/
/******************************************************************************/
void ParticleManager::InitExplosionSystem(Emitter* pEmitter)
{
	for (int i = 0; i < pEmitter->size; ++i)
	{
		pEmitter->pParitcles[i].pos = pEmitter->pos;

		float RandomRotation = WERandom::GetFloat(0, WEMath::TWO_PI);

		pEmitter->pParitcles[i].vel
			= { cosf(RandomRotation), sinf(RandomRotation) };

		pEmitter->pParitcles[i].vel
			*= WERandom::GetFloat(m_minExpVel, m_maxExpVel);

		pEmitter->pParitcles[i].scale
			= WERandom::GetFloat(m_minExpScale, m_maxExpScale);
	}
}

/******************************************************************************/
/*!
\brief
The function that initialize the trail emitter.

\param pEmitter
A pointer of trail emitter.
*/
/******************************************************************************/
void ParticleManager::InitTrailSystem(Emitter* pEmitter)
{
	for (int i = 0; i < pEmitter->size; ++i)
		pEmitter->pParitcles[i].scale = 0;
}

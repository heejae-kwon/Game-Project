/******************************************************************************/
/*!
\file   Reflection.cpp
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
Ball reflection Codes

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Reflection.h"

#include "cmath"

/******************************************************************************/
/*!
\param pBalls
Get Ball struct

\param pBlocks
Get Block information

\param dt
Get the time

\param data
Know condition of all

\brief
Ball Reflection Code
*/
/******************************************************************************/
void Reflection(Ball *pBalls, Block *pBlocks, float dt, Play &data)
{
	if (data.ConditionData.ballCondition == Shooting)
		for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
		{
			for (int j = 0; j < data.pObjMgr->GetBlockCount(); ++j)
			{
				//Loof for four point box
				for (int firstpoint = 0; firstpoint < 4; ++firstpoint)
				{
					int secondpoint;
					if (firstpoint == 3)
						secondpoint = 0;
					else
						secondpoint = firstpoint + 1;

					//Ball touch the line in correct vector
					if (WEIntersection::CircleLine(pBalls[i].pos + pBalls[i].vel * dt, pBalls[i].radius, pBlocks[j].point[firstpoint], pBlocks[j].point[secondpoint]) && 0
				        > WEVec2::Dot({ pBlocks[j].line[firstpoint].y, -pBlocks[j].line[firstpoint].x }, pBalls[i].vel))
					{
						//Make particle
						data.pParticleMgr->AddExpEmitter(PARTICLE_COUNT, pBalls[i].pos, pBalls[i].vel, data.TextureData.particleTexture, ET_EXPLOSION);

						WEVec2 p_1;
						WEVec2 reflection_1;
						WEVec2 forplus_1;
						WEVec2 LineNormal_1;
						WEVec2 forforce;

						//Get line normal
						WEVec2::Normalize(LineNormal_1, pBlocks[j].line[firstpoint]);

						//For corner check
						int Check = 0;

						//Loof for four point box
						for (int Loop_1 = 0; Loop_1 < 4; ++Loop_1)
						{
							int Loop_2;
							if (Loop_1 == 3)
								Loop_2 = 0;
							else
								Loop_2 = Loop_1 + 1;

							//For corner check
							if (WEDistance::PointCircle((pBlocks[j].point[firstpoint] + pBlocks[j].point[secondpoint]) * 0.5f, pBalls[i].pos + pBalls[i].vel * dt, pBalls[i].radius)
						> WEDistance::PointCircle((pBlocks[j].point[Loop_1] + pBlocks[j].point[Loop_2]) * 0.5f, pBalls[i].pos + pBalls[i].vel * dt, pBalls[i].radius))
							{
								//Position Check
								pBalls[i].pos.x += -LineNormal_1.y * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pBlocks[j].point[firstpoint], pBlocks[j].point[secondpoint]);
								pBalls[i].pos.y += LineNormal_1.x * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pBlocks[j].point[firstpoint], pBlocks[j].point[secondpoint]);
								Check = 1;
							}
						}
						
						if (Check == 1)
							continue;


						//Position Check
						pBalls[i].pos.x += -LineNormal_1.y * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pBlocks[j].point[firstpoint], pBlocks[j].point[secondpoint]);
						pBalls[i].pos.y += LineNormal_1.x * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pBlocks[j].point[firstpoint], pBlocks[j].point[secondpoint]);

						///Music 
						data.FmodData.result = data.FmodData.system->playSound(data.FmodData.sound1, 0, false, &data.FmodData.channel);

						//To Set forceSum, get the vector for
						forplus_1.x = pBalls[i].vel.x * LineNormal_1.x;
						forplus_1.y = pBalls[i].vel.y * LineNormal_1.y;

						//Put two forplus to get reflect vector
						p_1 = (forplus_1.x + forplus_1.y) * LineNormal_1;

						//Get reflected normal
						WEVec2::Normalize(reflection_1, (-pBalls[i].vel) + (2 * p_1));

						WEVec2 inputVec;

						//Normalize pBall's vector
						WEVec2::Normalize(inputVec, pBalls[i].vel);

						//Set force x and y
						forforce.x = pBalls[i].vel.x * pBalls[i].mass * (1 / (dt * 2.5f)) * (1 / inputVec.x);
						forforce.y = pBalls[i].vel.y * pBalls[i].mass * (1 / (dt * 2.5f)) * (1 / inputVec.y);

						//Not to be a -force
						if (forforce.x < 0)
						{
							forforce.x *= (-1.f);
						}
						if (forforce.y < 0)
						{
							forforce.y *= (-1.f);
						}

						//give them reflected force
						pBalls[i].forceSum.x += forforce.x * reflection_1.x;
						pBalls[i].forceSum.y += forforce.y * reflection_1.y;

						//Just give reflect velocity
						pBalls[i].vel = { 0, 0 };

						//For Special box
						data.SBdt = 0;
					}
				}
			}
		}
	//data.ballCondition == Shooting
	//End ball reflection
}

/******************************************************************************/
/*!
\param pBalls
Get Ball struct

\param pWalls
Get Wall information

\param dt
Get the time

\param data
Know condition of all

\brief
Ball Reflection Code
*/
/******************************************************************************/
void WallReflection(Ball *pBalls, Block *pWalls, float dt, Play &data)
{
	if (data.ConditionData.ballCondition == Shooting)
		for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
		{
			for (int j = 0; j < data.pObjMgr->GetWallCount(); ++j)
			{
				//Loof for four point wall
				for (int firstpoint = 0; firstpoint < 4; ++firstpoint)
				{
					int secondpoint;
					if (firstpoint == 3)
						secondpoint = 0;
					else
						secondpoint = firstpoint + 1;

					//Ball touch the line in correct vector
					if (WEIntersection::CircleLine(pBalls[i].pos + pBalls[i].vel * dt, pBalls[i].radius, pWalls[j].point[firstpoint], pWalls[j].point[secondpoint]) && 0
				        > WEVec2::Dot({ pWalls[j].line[firstpoint].y, -pWalls[j].line[firstpoint].x }, pBalls[i].vel))
					{
						//Make Particle
						data.pParticleMgr->AddExpEmitter(PARTICLE_COUNT, pBalls[i].pos, pBalls[i].vel, data.TextureData.particleTexture, ET_EXPLOSION);

						WEVec2 p_1;
						WEVec2 reflection_1;
						WEVec2 forplus_1;
						WEVec2 LineNormal_1;
						WEVec2 forforce;

						//get wall's normal
						WEVec2::Normalize(LineNormal_1, pWalls[j].line[firstpoint]);

						//Position Check
						pBalls[i].pos.x += -LineNormal_1.y * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pWalls[j].point[firstpoint], pWalls[j].point[secondpoint]);
						pBalls[i].pos.y += LineNormal_1.x * WEDistance::CircleLine(pBalls[i].pos, pBalls[i].radius, pWalls[j].point[firstpoint], pWalls[j].point[secondpoint]);

						//Sound
						data.FmodData.result = data.FmodData.system->playSound(data.FmodData.sound1, 0, false, &data.FmodData.channel);

						//To Set forceSum, get the vector for
						forplus_1.x = pBalls[i].vel.x * LineNormal_1.x;
						forplus_1.y = pBalls[i].vel.y * LineNormal_1.y;

						//Put two forplus to get reflect vector
						p_1 = (forplus_1.x + forplus_1.y) * LineNormal_1;

						//Get reflected normal
						WEVec2::Normalize(reflection_1, (-pBalls[i].vel) + (2 * p_1));

						WEVec2 inputVec;

						WEVec2::Normalize(inputVec, pBalls[i].vel);

						//Set force x and y
						forforce.x = pBalls[i].vel.x * pBalls[i].mass * (1 / (dt * 2.5f)) * (1 / inputVec.x);
						forforce.y = pBalls[i].vel.y * pBalls[i].mass * (1 / (dt * 2.5f)) * (1 / inputVec.y);

						//Not to be a -force
						if (forforce.x < 0)
						{
							forforce.x *= (-1.f);
						}
						if (forforce.y < 0)
						{
							forforce.y *= (-1.f);
						}

						//give them reflected force
						pBalls[i].forceSum.x += forforce.x * reflection_1.x;
						pBalls[i].forceSum.y += forforce.y * reflection_1.y;

						//Just give reflect velocity
						pBalls[i].vel = { 0, 0 };
					}
				}
			}
		}
	//data.ballCondition == Shooting
	//End ball reflection
}

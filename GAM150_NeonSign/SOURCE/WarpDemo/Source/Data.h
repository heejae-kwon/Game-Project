/******************************************************************************/
/*!
\file   Data.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that includes Play struct information.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/

#ifndef DATA_H
#define DATA_H

#include "ParticleManager.h"
#include "ObjectManager.h"
#include "State.h"
#include <iostream>

//Include Engine Headers
#include "WEInput.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEMtx44.h"
#include "WEApplication.h"
#include "WEIntersection.h"
#include "WERandom.h"
#include "WEDebugTools.h"
#include "WEMath.h"
#include "WEVec2.h"

#include <cmath> //For cos, acos
#include <ctime>
#include <cstdio>
#include "GameTypes.h"
#include "FmodData.h"

const float SB_FORCE_SIZE = 600000;
const float FORCE_SIZE = 330000;
const int REC_POINT_COUNT = 4; //rectangle's 4 points
const float LeveltoLevelDT = 1;
const float DIRECTION_AREA = 25;
const int PARTICLE_COUNT = 400;
const int BUILDING_COUNT = 8;
const int EMITTER_COUNT = 100;

//Actions
void QuitAction(void);
void ShootAction(void);
void CreateBlockAction(void);
void MainMenuAction(void);
void OptionAction(void);
void HowToAction(void);

struct FileData
{
	WEVec2 pos;
	WEVec2 scale;
	float rotation;
};

struct TextureData
{
	int quitTexture;
	int shootTexture;
	int stopTexture;
	int ballTexture;
	int ballGuideTexture;
	int blockTexture;
	int boxbuttonTexture;
	int mainmenubuttonTexture;
	int howtobuttonTexture;
	int optionbuttonTexture;
	int arrowTexture;
	int goalTexture;
	int boxTutoTexture;
	int arrowTutoTexture;
	int wallTexture;
	int wallInTexture;
	int SBTexture;
	int ballBorderTexture;
	int NumberTextures;
	int menuTexture;
	int menutitleTexture;
	int particleTexture;
	int buildingTexture[BUILDING_COUNT];
	int buildingclearTexture[BUILDING_COUNT];
};

struct ConditionData
{
	ShotState ballCondition;
	MoveState blockCondition;
	RotateState rotateCondition;

	//For Developer
	ModState ballModCondition;
	ModState goalModCondition;

	ModRotateState RwallModCondition;
	ModState wallModCondition;

	ModRotateState RSBModCondition;
	ModState SBModCondition;
};


struct Play
{
    ObjectManager *pObjMgr;
	ParticleManager *pParticleMgr;

    int LevelControl;
	int MaxLevel;

    //defines object
    int maxBalls;
    int maxButtons;
    int maxBlocks;
    int maxGoals;
    int maxWalls;
    int maxSB;

    //Read & Save
    WEVec2 blockFileScale;
    FileData *pWalls;
    FileData *pGoals;
    FileData *pBalls;
    FileData *pButtons;
    FileData *pSB;

    float screenWidth;
    float screenHeight;

    WEVec2 topLeft;
    WEVec2 topRight;
    WEVec2 botLeft;
    WEVec2 botRight;

    WEVec2 KeepNormal;//!<Ball.cpp , in BallDirection

    FmodData FmodData;
    TextureData TextureData;
    ConditionData ConditionData;

    float GoalValue; //!< Goal.cpp
    float SBdt;      //!< SB.cpp
    bool DT;

    bool BTCheck;     //!< Ball.cpp
    bool BSCheck;     //!< SB.cpp
    bool BS;          //!< SB.cpp
	bool CheckSBInter;//!< SB.cpp
	bool CheckSBOut;  //!< SB.cpp
	int  Special;     //!< SB.cpp

	WEVec2 blockDrag;

	Building Buildings[BUILDING_COUNT];

	//For File open
	std::string path;
};

#endif

/******************************************************************************/
/*!
\file   FileIO.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes FileIO functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "FileIO.h"

/******************************************************************************/
/*!
\brief
Cheat code that control the game play level.

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void WriteLevelControl(const char* fileName, const Play &data)
{
	FILE* pFile = 0;

	fopen_s(&pFile, fileName, "wt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
	if (pFile)
	{
		fprintf(pFile, "%d\n", data.LevelControl);
		fprintf(pFile, "%d\n", data.MaxLevel);

		fclose(pFile);
	}
}

/******************************************************************************/
/*!
\brief
Write Ball info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void WriteBallInfo(const char* fileName, const Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "wt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  int ballCount = data.pObjMgr->GetBallCount();
	  Ball* pBalls = data.pObjMgr->GetBalls();

	  fprintf(pFile, "%d\n", ballCount);

	  for (int i = 0; i < ballCount; ++i)
	  {
		  WEVec2 Pos = pBalls[i].pos;

		  WEGraphics::ConvertWorldToScreen(Pos.x, Pos.y);

		  fprintf(pFile, "%f\n", Pos.x);
		  fprintf(pFile, "%f\n", Pos.y);
		  fprintf(pFile, "%f\n", pBalls[i].scale.x);
		  fprintf(pFile, "%f\n", pBalls[i].scale.y);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Write Goal info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void WriteGoalInfo(const char* fileName, const Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "wt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  int goalCount = data.pObjMgr->GetGoalCount();
	  Object* pGoals = data.pObjMgr->GetGoals();

	  fprintf(pFile, "%d\n", goalCount);

	  for (int i = 0; i < goalCount; ++i)
	  {
		  WEVec2 Pos = pGoals[i].pos;

		  WEGraphics::ConvertWorldToScreen(Pos.x, Pos.y);

		  fprintf(pFile, "%f\n", Pos.x);
		  fprintf(pFile, "%f\n", Pos.y);
		  fprintf(pFile, "%f\n", pGoals[i].scale.x);
		  fprintf(pFile, "%f\n", pGoals[i].scale.y);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Write Wall info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void WriteWallInfo(const char* fileName, const Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "wt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  int wallCount = data.pObjMgr->GetWallCount();
	  Block* pWalls = data.pObjMgr->GetWalls();


	  fprintf(pFile, "%d\n", wallCount);

	  for (int i = 0; i < wallCount; ++i)
	  {
		  WEVec2 Pos = pWalls[i].pos;
		  float Degree = WEMath::RadianToDegree(pWalls[i].rotation);

		  WEGraphics::ConvertWorldToScreen(Pos.x, Pos.y);

		  fprintf(pFile, "%f\n", Pos.x);
		  fprintf(pFile, "%f\n", Pos.y);
		  fprintf(pFile, "%f\n", pWalls[i].scale.x);
		  fprintf(pFile, "%f\n", pWalls[i].scale.y);
		  fprintf(pFile, "%f\n", Degree);
	  }

	  fclose(pFile);
  }
}


/******************************************************************************/
/*!
\brief
	Write SB Info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void WriteSBInfo(const char* fileName, const Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "wt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  int SBCount = data.pObjMgr->GetSBCount();
	  Block* pSB = data.pObjMgr->GetSB();


	  fprintf(pFile, "%d\n", SBCount);

	  for (int i = 0; i < SBCount; ++i)
	  {
		  WEVec2 Pos = pSB[i].pos;
		  float Degree = WEMath::RadianToDegree(pSB[i].rotation);

		  WEGraphics::ConvertWorldToScreen(Pos.x, Pos.y);

		  fprintf(pFile, "%f\n", Pos.x);
		  fprintf(pFile, "%f\n", Pos.y);
		  fprintf(pFile, "%f\n", pSB[i].scale.x);
		  fprintf(pFile, "%f\n", pSB[i].scale.y);
		  fprintf(pFile, "%f\n", Degree);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read Ball info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadBallInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxBalls);
	  data.pBalls = new FileData[data.maxBalls];

	  for (int i = 0; i < data.maxBalls; ++i)
	  {
		  fscanf_s(pFile, "%f", &data.pBalls[i].pos.x);
		  fscanf_s(pFile, "%f", &data.pBalls[i].pos.y);

		  WEGraphics::ConvertScreenToWorld(data.pBalls[i].pos.x, data.pBalls[i].pos.y);

		  fscanf_s(pFile, "%f", &data.pBalls[i].scale.x);
		  fscanf_s(pFile, "%f", &data.pBalls[i].scale.y);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read Block info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadBlockInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxBlocks);
	  fscanf_s(pFile, "%f", &data.blockFileScale.x);
	  fscanf_s(pFile, "%f", &data.blockFileScale.y);

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read Goal info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadGoalInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxGoals);
	  data.pGoals = new FileData[data.maxGoals];

	  for (int i = 0; i < data.maxGoals; ++i)
	  {
		  fscanf_s(pFile, "%f", &data.pGoals[i].pos.x);
		  fscanf_s(pFile, "%f", &data.pGoals[i].pos.y);

		  WEGraphics::ConvertScreenToWorld(data.pGoals[i].pos.x, data.pGoals[i].pos.y);

		  fscanf_s(pFile, "%f", &data.pGoals[i].scale.x);
		  fscanf_s(pFile, "%f", &data.pGoals[i].scale.y);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read Wall info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadWallInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxWalls);
	  data.pWalls = new FileData[data.maxWalls];

	  for (int i = 0; i < data.maxWalls; ++i)
	  {
		  float Degree;

		  fscanf_s(pFile, "%f", &data.pWalls[i].pos.x);
		  fscanf_s(pFile, "%f", &data.pWalls[i].pos.y);

		  WEGraphics::ConvertScreenToWorld(data.pWalls[i].pos.x, data.pWalls[i].pos.y);

		  fscanf_s(pFile, "%f", &data.pWalls[i].scale.x);
		  fscanf_s(pFile, "%f", &data.pWalls[i].scale.y);

		  fscanf_s(pFile, "%f", &Degree);
		  data.pWalls[i].rotation = WEMath::DegreeToRadian(Degree);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read SpecialBox info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadSBInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxSB);
	  data.pSB = new FileData[data.maxSB];

	  for (int i = 0; i < data.maxSB; ++i)
	  {
		  float Degree;

		  fscanf_s(pFile, "%f", &data.pSB[i].pos.x);
		  fscanf_s(pFile, "%f", &data.pSB[i].pos.y);

		  WEGraphics::ConvertScreenToWorld(data.pSB[i].pos.x, data.pSB[i].pos.y);

		  fscanf_s(pFile, "%f", &data.pSB[i].scale.x);
		  fscanf_s(pFile, "%f", &data.pSB[i].scale.y);

		  fscanf_s(pFile, "%f", &Degree);
		  data.pSB[i].rotation = WEMath::DegreeToRadian(Degree);
	  }

	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read Button info

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadButtonInfo(const char* fileName, Play &data)
{
  FILE* pFile = 0;

  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  if (pFile)
  {
	  fscanf_s(pFile, "%d", &data.maxButtons);
	  data.pButtons = new FileData[data.maxButtons];

	  for (int i = 0; i < data.maxButtons; ++i)
	  {
		  fscanf_s(pFile, "%f", &data.pButtons[i].pos.x);
		  fscanf_s(pFile, "%f", &data.pButtons[i].pos.y);

		  fscanf_s(pFile, "%f", &data.pButtons[i].scale.x);
		  fscanf_s(pFile, "%f", &data.pButtons[i].scale.y);
	  }
	  fclose(pFile);
  }
}

/******************************************************************************/
/*!
\brief
Read LevelControl number

\param fileName
File name that includes informations.

\param data
Get map data
*/
/******************************************************************************/
void ReadLevelControl(const char* fileName, Play &data)
{
	FILE* pFile = 0;

	fopen_s(&pFile, fileName, "rt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
	if (pFile)
	{
		fscanf_s(pFile, "%d", &data.LevelControl);
		fscanf_s(pFile, "%d", &data.MaxLevel);

		fclose(pFile);
	}
}

/******************************************************************************/
/*!
\brief
Save level's info to txt file

\param data
Get map data
*/
/******************************************************************************/
void SaveLevelInfo(Play &data)
{
  switch (data.LevelControl)
  {
  case 0:
    WriteBallInfo("Source/LevelInfo/Level0/BallInfo0.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level0/GoalInfo0.txt", data);
    WriteWallInfo("Source/LevelInfo/Level0/WallInfo0.txt", data);
    WriteSBInfo("Source/LevelInfo/Level0/SBInfo0.txt", data);
    
    break;
  case 1:
    WriteBallInfo("Source/LevelInfo/Level1/BallInfo1.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level1/GoalInfo1.txt", data);
    WriteWallInfo("Source/LevelInfo/Level1/WallInfo1.txt", data);
    WriteSBInfo("Source/LevelInfo/Level1/SBInfo1.txt", data);
  
    break;
  case 2:
    WriteBallInfo("Source/LevelInfo/Level2/BallInfo2.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level2/GoalInfo2.txt", data);
    WriteWallInfo("Source/LevelInfo/Level2/WallInfo2.txt", data);
    WriteSBInfo("Source/LevelInfo/Level2/SBInfo2.txt", data);
  
    break;
  case 3:
    WriteBallInfo("Source/LevelInfo/Level3/BallInfo3.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level3/GoalInfo3.txt", data);
    WriteWallInfo("Source/LevelInfo/Level3/WallInfo3.txt", data);
    WriteSBInfo("Source/LevelInfo/Level3/SBInfo3.txt", data);
    
    break;
  case 4:
    WriteBallInfo("Source/LevelInfo/Level4/BallInfo4.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level4/GoalInfo4.txt", data);
    WriteWallInfo("Source/LevelInfo/Level4/WallInfo4.txt", data);
    WriteSBInfo("Source/LevelInfo/Level4/SBInfo4.txt", data);

    break;
  case 5:
    WriteBallInfo("Source/LevelInfo/Level5/BallInfo5.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level5/GoalInfo5.txt", data);
    WriteWallInfo("Source/LevelInfo/Level5/WallInfo5.txt", data);
    WriteSBInfo("Source/LevelInfo/Level5/SBInfo5.txt", data);

    break;
  case 6:
    WriteBallInfo("Source/LevelInfo/Level6/BallInfo6.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level6/GoalInfo6.txt", data);
    WriteWallInfo("Source/LevelInfo/Level6/WallInfo6.txt", data);
    WriteSBInfo("Source/LevelInfo/Level6/SBInfo6.txt", data);

    break;
  case 7:
    WriteBallInfo("Source/LevelInfo/Level7/BallInfo7.txt", data);
    WriteGoalInfo("Source/LevelInfo/Level7/GoalInfo7.txt", data);
    WriteWallInfo("Source/LevelInfo/Level7/WallInfo7.txt", data);
    WriteSBInfo("Source/LevelInfo/Level7/SBInfo7.txt", data);

    break;

  default:
    break;
  }
}

/******************************************************************************/
/*!
\brief
Load level's info to txt file

\param data
Get map data
*/
/******************************************************************************/
void LoadLevelInfo(Play &data)
{
  switch (data.LevelControl)
  {
  case 0:
    ReadBallInfo("Source/LevelInfo/Level0/BallInfo0.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level0/BlockInfo0.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level0/GoalInfo0.txt", data);
    ReadWallInfo("Source/LevelInfo/Level0/WallInfo0.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level0/ButtonInfo0.txt", data);
    ReadSBInfo("Source/LevelInfo/Level0/SBInfo0.txt", data);
    WEDEBUG_PRINT("Read Position0\n");
    break;

  case 1:
    ReadBallInfo("Source/LevelInfo/Level1/BallInfo1.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level1/BlockInfo1.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level1/GoalInfo1.txt", data);
    ReadWallInfo("Source/LevelInfo/Level1/WallInfo1.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level1/ButtonInfo1.txt", data);
    ReadSBInfo("Source/LevelInfo/Level1/SBInfo1.txt", data);
    WEDEBUG_PRINT("Read Position1\n");
    break;

  case 2:
    ReadBallInfo("Source/LevelInfo/Level2/BallInfo2.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level2/BlockInfo2.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level2/GoalInfo2.txt", data);
    ReadWallInfo("Source/LevelInfo/Level2/WallInfo2.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level2/ButtonInfo2.txt", data);
    ReadSBInfo("Source/LevelInfo/Level2/SBInfo2.txt", data);
    WEDEBUG_PRINT("Read Position2\n");
    break;

  case 3:
    ReadBallInfo("Source/LevelInfo/Level3/BallInfo3.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level3/BlockInfo3.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level3/GoalInfo3.txt", data);
    ReadWallInfo("Source/LevelInfo/Level3/WallInfo3.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level3/ButtonInfo3.txt", data);
    ReadSBInfo("Source/LevelInfo/Level3/SBInfo3.txt", data);
    WEDEBUG_PRINT("Read Position3\n");
    break;

  case 4:
    ReadBallInfo("Source/LevelInfo/Level4/BallInfo4.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level4/BlockInfo4.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level4/GoalInfo4.txt", data);
    ReadWallInfo("Source/LevelInfo/Level4/WallInfo4.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level4/ButtonInfo4.txt", data);
    ReadSBInfo("Source/LevelInfo/Level4/SBInfo4.txt", data);
    WEDEBUG_PRINT("Read Position4\n");
    break;

  case 5:
    ReadBallInfo("Source/LevelInfo/Level5/BallInfo5.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level5/BlockInfo5.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level5/GoalInfo5.txt", data);
    ReadWallInfo("Source/LevelInfo/Level5/WallInfo5.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level5/ButtonInfo5.txt", data);
    ReadSBInfo("Source/LevelInfo/Level5/SBInfo5.txt", data);
    WEDEBUG_PRINT("Read Position5\n");
    break;

  case 6:
    ReadBallInfo("Source/LevelInfo/Level6/BallInfo6.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level6/BlockInfo6.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level6/GoalInfo6.txt", data);
    ReadWallInfo("Source/LevelInfo/Level6/WallInfo6.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level6/ButtonInfo6.txt", data);
    ReadSBInfo("Source/LevelInfo/Level6/SBInfo6.txt", data);
    WEDEBUG_PRINT("Read Position6\n");
    break;

  case 7:
    ReadBallInfo("Source/LevelInfo/Level7/BallInfo7.txt", data);
    ReadBlockInfo("Source/LevelInfo/Level7/BlockInfo7.txt", data);
    ReadGoalInfo("Source/LevelInfo/Level7/GoalInfo7.txt", data);
    ReadWallInfo("Source/LevelInfo/Level7/WallInfo7.txt", data);
    ReadButtonInfo("Source/LevelInfo/Level7/ButtonInfo7.txt", data);
    ReadSBInfo("Source/LevelInfo/Level7/SBInfo7.txt", data);
    WEDEBUG_PRINT("Read Position7\n");
    break;

  default:
    ReadBallInfo("Source/LevelInfo/Default/BallInfoD.txt", data);
    ReadBlockInfo("Source/LevelInfo/Default/BlockInfoD.txt", data);
    ReadGoalInfo("Source/LevelInfo/Default/GoalInfoD.txt", data);
    ReadWallInfo("Source/LevelInfo/Default/WallInfoD.txt", data);
    ReadButtonInfo("Source/LevelInfo/Default/ButtonInfoD.txt", data);
    ReadSBInfo("Source/LevelInfo/Default/SBInfoD.txt", data);
    WEStateManager::SetNextState(DS_STATE_ENGINEPROOF);
    break;
  }
}
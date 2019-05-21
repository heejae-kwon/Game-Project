/******************************************************************************/
/*!
\file   Play.cpp
\title  Neon sign
\author HeeJae Kwon, GueSik Kim
\par    GAM150
\brief  The file that includes Play state's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Play.h"
#include "Data.h"
#include "FmodData.h"

namespace
{
  Play data;
}

/******************************************************************************/
/*!
\brief MainMenu Button action
*/
/******************************************************************************/
void MainMenuAction(void)
{
  WEStateManager::SetNextState(DS_STATE_MAINMENU);
}
/******************************************************************************/
/*!
\brief Option Button action
*/
/******************************************************************************/
void OptionAction(void)
{
  WEStateManager::SetNextState(DS_STATE_OPTION);
}
/******************************************************************************/
/*!
\brief HowTo Button action
*/
/******************************************************************************/
void HowToAction(void)
{
  WEStateManager::SetNextState(DS_STATE_HOWTO);
}
  /******************************************************************************/
  /*!
  \brief Quit Button action
  */
  /******************************************************************************/
  void QuitAction(void)
  {
    WEStateManager::Quit();
  }//QuitAction
  /******************************************************************************/
  /*!
  \brief Shoot Button action
  */
  /******************************************************************************/
  void ShootAction(void)
  {
    if (data.ConditionData.ballCondition == Stoping)
      data.ConditionData.ballCondition = Shooting;
    else if (data.ConditionData.ballCondition == Shooting)
      data.ConditionData.ballCondition = Resetting;
  }//ShootAction
  /******************************************************************************/
  /*!
  \brief Create Block Button Actions
  */
  /******************************************************************************/
  void CreateBlockAction(void)
  {
    if (data.ConditionData.ballCondition != Shooting)
      CreateBlock(data, 1);
  }// CreateBlockAction

  /******************************************************************************/
  /*!
  \brief Drawing function
  */
  /******************************************************************************/
 void UpdateDraw(void)
 {
    Ball *pBalls = data.pObjMgr->GetBalls();
    Block *pBlocks = data.pObjMgr->GetBlocks();
    Block *pWalls = data.pObjMgr->GetWalls();
    Object *pButtons = data.pObjMgr->GetButtons();
    Object *pArrow = data.pObjMgr->GetArrow();
    Object *pGoals = data.pObjMgr->GetGoals();
    Block *pSB = data.pObjMgr->GetSB();
	Emitter *pExpEmitter = data.pParticleMgr->GetExpEmitters();
	Emitter *pTrailEmitter = data.pParticleMgr->GetTrailEmitters();

    WEGraphics::StartDraw();
	//Background
	DrawBuilding(data);

    //Objects*********************************************************************//
    WEGraphics::SetToPerspective();
    
	/*Draw Particles************************************************************/
	for (int i = 0; i < data.pParticleMgr->GetExpEmmiterCount(); ++i)
		data.pParticleMgr->DrawEmitter(pExpEmitter + i);

	data.pParticleMgr->DrawEmitter(pTrailEmitter);

	//Tuto
	if (data.LevelControl == 0)
	{
		WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
		WEMtx44 tranform;
		WEGraphics::SetTexture(data.TextureData.arrowTutoTexture);
		WEGraphics::SetTextureColor(255,
			255,
			255,
			150);
		WEMtx44::MakeTransform(tranform,
			40,
			40,
			0,
			-46,
			-26,
			0);
		WEGraphics::Draw(tranform);
	}

	if (data.LevelControl == 2)
	{
		WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
		WEMtx44 tranform;
		WEGraphics::SetTexture(data.TextureData.boxTutoTexture);
		WEGraphics::SetTextureColor(255,
			255,
			255,
			150);
		WEMtx44::MakeTransform(tranform,
			64,
			64,
			0,
			-46,
			-26,
			0);
		WEGraphics::Draw(tranform);
	}

	//Draw my DirentionLimit
	DrawDirectionLimit(pBalls, data);
    //Draw Arrow
    DrawArrow(pArrow, data);
    //Draw my Goal
    DrawGoal(pGoals, data);
    //Draw my Ball
    DrawBall(pBalls, data);
    //Draw my Blocks
    DrawBlock(pBlocks, data);
    //Draw my Walls
    DrawWall(pWalls, data);
    //Draw my SB
    DrawSB(pSB, data);

    //**************************************************************************//

    //HUD***********************************************************************//
    
    WEGraphics::SetToOrtho();
    //Draw my buttons
	DrawButton(pButtons, data);

	DrawNumbers(data);
    
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
	
    //Menu Draw
    InGameMenuDraw(data);

    //DEBUG MODE
    const int SIZE = 5;
    char LEVEL[SIZE];
    sprintf_s(LEVEL, "%d", data.LevelControl);
    WEGraphics::SetBackgroundColor(0, 0, 0);
    WEDEBUG_WRITETEXT("Level : ", 0,
      data.screenHeight-20);
    WEDEBUG_WRITETEXT(LEVEL, 60,
      data.screenHeight-20);


    //***********************************************************************//

    //This must be called after all drawing is done
    WEGraphics::EndDraw();
  }//UpdateDraw

  /******************************************************************************/
  /*!
  \brief Load All textures
  */
  /******************************************************************************/
  void Play_Load(void)
  {
    WERandom::Seed((int)time(0));

	/*Load the only texture we need for this state*/
	data.TextureData.buildingTexture[0]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding1.tga");
	data.TextureData.buildingTexture[1]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding2.tga");
	data.TextureData.buildingTexture[2]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding3.tga");
	data.TextureData.buildingTexture[3]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding4.tga");
	data.TextureData.buildingTexture[4]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding5.tga");
	data.TextureData.buildingTexture[5]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding6.tga");
	data.TextureData.buildingTexture[6]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding7.tga");
	data.TextureData.buildingTexture[7]		 = WEGraphics::LoadTexture("Textures\\LevelBuilding8.tga");

	data.TextureData.buildingclearTexture[0] = WEGraphics::LoadTexture("Textures\\LevelBuilding1C.tga");
	data.TextureData.buildingclearTexture[1] = WEGraphics::LoadTexture("Textures\\LevelBuilding2C.tga");
	data.TextureData.buildingclearTexture[2] = WEGraphics::LoadTexture("Textures\\LevelBuilding3C.tga");
	data.TextureData.buildingclearTexture[3] = WEGraphics::LoadTexture("Textures\\LevelBuilding4C.tga");
	data.TextureData.buildingclearTexture[4] = WEGraphics::LoadTexture("Textures\\LevelBuilding5C.tga");
	data.TextureData.buildingclearTexture[5] = WEGraphics::LoadTexture("Textures\\LevelBuilding6C.tga");
	data.TextureData.buildingclearTexture[6] = WEGraphics::LoadTexture("Textures\\LevelBuilding7C.tga");
	data.TextureData.buildingclearTexture[7] = WEGraphics::LoadTexture("Textures\\LevelBuilding8C.tga");

    data.TextureData.quitTexture             = WEGraphics::LoadTexture("Textures/ExitButton.tga");
    data.TextureData.shootTexture            = WEGraphics::LoadTexture("Textures/Shot.tga");
    data.TextureData.stopTexture			 = WEGraphics::LoadTexture("Textures/Stop.tga");
    data.TextureData.ballTexture			 = WEGraphics::LoadTexture("Textures/Ball.tga");
    data.TextureData.blockTexture			 = WEGraphics::LoadTexture("Textures/Tile.tga");
    data.TextureData.boxbuttonTexture		 = WEGraphics::LoadTexture("Textures/BoxButton.tga");
    data.TextureData.arrowTexture			 = WEGraphics::LoadTexture("Textures/Arrow.tga");
    data.TextureData.goalTexture			 = WEGraphics::LoadTexture("Textures/Goal.tga");
    data.TextureData.arrowTutoTexture		 = WEGraphics::LoadTexture("Textures/ArrowTutorial.tga");
    data.TextureData.boxTutoTexture			 = WEGraphics::LoadTexture("Textures/BoxTutorial.tga");
    data.TextureData.wallTexture			 = WEGraphics::LoadTexture("Textures/Wall.tga");
	data.TextureData.wallInTexture			 = WEGraphics::LoadTexture("Textures/WallIn.tga");
    data.TextureData.SBTexture				 = WEGraphics::LoadTexture("Textures/SB.tga");
    data.TextureData.ballBorderTexture		 = WEGraphics::LoadTexture("Textures/BallBorder.tga");
	data.TextureData.ballGuideTexture		 = WEGraphics::LoadTexture("Textures/BallGuideLine.tga");
    data.TextureData.NumberTextures			 = WEGraphics::LoadTexture("Textures/BoxNumber.tga");
    data.TextureData.menuTexture			 = WEGraphics::LoadTexture("Textures/MenuBox.tga");
    data.TextureData.mainmenubuttonTexture	 = WEGraphics::LoadTexture("Textures/BackToMain.tga");
    data.TextureData.howtobuttonTexture		 = WEGraphics::LoadTexture("Textures/HowToButton.tga");
    data.TextureData.optionbuttonTexture	 = WEGraphics::LoadTexture("Textures/OptionButton.tga");
    data.TextureData.menutitleTexture		 = WEGraphics::LoadTexture("Textures/MenuTitle.tga");
	data.TextureData.particleTexture		 = WEGraphics::LoadTexture("Textures/Particle.tga");
	
	data.path = getenv("USERPROFILE");
	data.path += "/My Documents/NeonSign/LevelControl.txt";

	ReadLevelControl(data.path.c_str(), data);
	/*Reset the timer for this state*/
	
  }//Play_Load

  /******************************************************************************/
  /*!
  \brief Initialize all objects
  */
  /******************************************************************************/
  void Play_Init(void)
  {
    WEDEBUG_CREATE_CONSOLE();


	if (data.MaxLevel <= data.LevelControl)
		data.MaxLevel = data.LevelControl;

	WEGraphics::GetWorldTopLeft(data.topLeft);
    WEGraphics::GetWorldTopRight(data.topRight);
    WEGraphics::GetWorldBotLeft(data.botLeft);
    WEGraphics::GetWorldBotRight(data.botRight);

    //Get Screen size
    data.screenWidth = static_cast<float>(WEApplication::GetWidth());
    data.screenHeight = static_cast<float>(WEApplication::GetHeight());

    //Load Level Info
    LoadLevelInfo(data);

    //Allocate ObjectManager
    data.pObjMgr = new ObjectManager(data.maxBalls,
      data.maxButtons,
      data.maxBlocks,
      data.maxGoals,
      data.maxWalls,
      data.maxSB);

	data.pParticleMgr = new ParticleManager(EMITTER_COUNT);

	//Background
	InitBuilding(data);

    //Init GameObjects
    CreateArrow(data);
    CreateButton(data);
    CreateBall(data);
    CreateGoal(data);
    CreateWall(data);
    CreateSB(data);
    
    data.ConditionData.SBModCondition = CanMod;
    data.ConditionData.ballModCondition = CanMod;
    data.ConditionData.goalModCondition = CanMod;
    data.ConditionData.wallModCondition = CanMod;
    data.ConditionData.RwallModCondition = CanModRotate;

    data.ConditionData.ballCondition = Stoping;
    data.ConditionData.blockCondition = CanMove;
    data.ConditionData.rotateCondition = CanRotate;

    //Initializing
    data.KeepNormal = { sqrt(2.f) * 0.5f, sqrt(2.f) * 0.5f };

    //FMOD
    /*Play music*/
    MusicInit(data.FmodData);

    data.FmodData.result = data.FmodData.system->createSound(Common_MediaPath("LevelBGM.ogg"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &data.FmodData.sound);
    data.FmodData.result = data.FmodData.sound->getNumSubSounds(&data.FmodData.numsubsounds);

    if (data.FmodData.numsubsounds)
      data.FmodData.sound->getSubSound(0, &data.FmodData.sound_to_play);
    else
      data.FmodData.sound_to_play = data.FmodData.sound;

    data.FmodData.result = data.FmodData.system->playSound(data.FmodData.sound_to_play, 0, false, &data.FmodData.channel);

    data.SBdt = 0;
    data.GoalValue = 0;

    //For ESC
    data.DT = true;
    //Button Check
    data.BTCheck = false;
    //For Ball & SB
    data.BSCheck = false;
    data.BS = true;

	data.CheckSBInter = false;
	data.CheckSBOut   = true;
	data.Special      = 0;

	//Defalut setting
	data.blockDrag = { data.botLeft.x - 1000, data.botLeft.y - 1000 };
  }//Play_Init



  /******************************************************************************/
  /*!
  \brief Main update function
  */
  /******************************************************************************/
  void Play_Update(float dt)
  {
    Ball *pBalls = data.pObjMgr->GetBalls();
    Block *pBlocks = data.pObjMgr->GetBlocks();
    Block *pWalls = data.pObjMgr->GetWalls();
    Object *pArrow = data.pObjMgr->GetArrow();
    Object *pGoals = data.pObjMgr->GetGoals();
    Object *pButtons = data.pObjMgr->GetButtons();
    Block *pSB = data.pObjMgr->GetSB();
	Emitter *pExpEmitter = data.pParticleMgr->GetExpEmitters();
	Emitter *pTrailEmitter = data.pParticleMgr->GetTrailEmitters();


if (data.DT == true)
{
      //DEVELOPER MODE
        DMRestart(data);
        DMSB(pSB, data);
        DMBall(pBalls, data);
        DMGoal(pGoals, data);
        DMWall(pWalls, data);
        DMSB(pSB, data);
        DMIncreaseLevel(data);
        DMDecreaseLevel(data);

      //UpdateButton
      UpdateButton(pButtons, data);

	  //UpdateSB
	  UpdateSB(pBalls, pSB, dt, data);

      //UpdateBlock
      UpdateBlockInput(pBlocks, data);

      //UpdateGoal
      UpdateGoal(pBalls, pGoals, data, dt);

      //DeleteBlock
      DeleteBlock(pBlocks, data);

      //Default Ball movement
      if (data.ConditionData.ballCondition == Shooting)
      {
        for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)

          BallMovement(pBalls, i, dt);

		//Move the arrow out of the screen
        pArrow[0].pos = { -10000, -10000 };
      }

	  //Set Ball Direction
      BallDirection(pBalls, pButtons, data);

      //UpdataArrow
      if (data.ConditionData.blockCondition == CanMove)
        UpdateArrow(pBalls, pArrow, pButtons, data);

      //Reset the Ball's position
      ResetBallPosition(pBalls, pButtons, pArrow, data);

      //Ball & Block Reflection
      Reflection(pBalls, pBlocks, dt, data);

      //Wall & Block Reflection
      WallReflection(pBalls, pWalls, dt, data);

      //This must be called before any drawing is done

	  data.pParticleMgr->UpdateEmitter(pBalls, pTrailEmitter, dt);

	  for (int i = 0; i < data.pParticleMgr->GetExpEmmiterCount(); ++i)

		  data.pParticleMgr->UpdateEmitter(pBalls, pExpEmitter + i, dt);

	  //Press Space to Shot
	  if (WEInput::IsTriggered(WE_SPACE))
	  {
		  pButtons[0].action();
	  }

      //Save to TEXTFILE
      if (WEInput::IsTriggered(WE_P))
        SaveLevelInfo(data);

}//end data.DT == true
    else if (data.DT == false)

      InGameMenuButtonUpdate(pButtons, data);


    //ESC
    Escaping(data);

    UpdateDraw();

  }//Play_Update

  /******************************************************************************/
  /*!
  \brief delete pObjMgr
  */
  /******************************************************************************/
  void Play_Shutdown(void)
  {
	delete data.pParticleMgr;
	data.pParticleMgr = 0;

    delete data.pObjMgr;
    data.pObjMgr = 0;
	
    delete [] data.pBalls;
    data.pBalls = 0;

    delete[] data.pButtons;
    data.pButtons = 0;

    delete[] data.pGoals;
    data.pGoals = 0;

    delete[] data.pWalls;
    data.pWalls = 0;

    delete[] data.pSB;
    data.pSB = 0;

    data.FmodData.result = data.FmodData.system->close();
    data.FmodData.result = data.FmodData.system->release();

    WEDEBUG_ASSERT(data.pWalls == 0, "Wall File Data wasn't deleted!!!!!!");
    WEDEBUG_ASSERT(data.pBalls == 0, "Ball File Data wasn't deleted!!!!!!");
    WEDEBUG_ASSERT(data.pButtons == 0, "Button File Data wasn't deleted!!!!!!");
    WEDEBUG_ASSERT(data.pGoals == 0, "Goal  File Data wasn't deleted!!!!!!");
    WEDEBUG_ASSERT(data.pSB == 0, "SB  File Data wasn't deleted!!!!!!");
  }//Play_Shutdown

  /******************************************************************************/
  /*!
  \brief Unload Texture
  */
  /******************************************************************************/
  void Play_Unload(void)
  {
    WEGraphics::UnloadTexture(data.TextureData.quitTexture);
    WEGraphics::UnloadTexture(data.TextureData.shootTexture);
    WEGraphics::UnloadTexture(data.TextureData.stopTexture);
    WEGraphics::UnloadTexture(data.TextureData.ballTexture);
    WEGraphics::UnloadTexture(data.TextureData.blockTexture);
    WEGraphics::UnloadTexture(data.TextureData.boxbuttonTexture);
    WEGraphics::UnloadTexture(data.TextureData.goalTexture);
    WEGraphics::UnloadTexture(data.TextureData.arrowTexture);
    WEGraphics::UnloadTexture(data.TextureData.boxTutoTexture);
    WEGraphics::UnloadTexture(data.TextureData.arrowTutoTexture);
    WEGraphics::UnloadTexture(data.TextureData.wallTexture);
	WEGraphics::UnloadTexture(data.TextureData.wallInTexture);
    WEGraphics::UnloadTexture(data.TextureData.SBTexture);
    WEGraphics::UnloadTexture(data.TextureData.ballBorderTexture);
    WEGraphics::UnloadTexture(data.TextureData.NumberTextures);
    WEGraphics::UnloadTexture(data.TextureData.menuTexture);
    WEGraphics::UnloadTexture(data.TextureData.mainmenubuttonTexture);
    WEGraphics::UnloadTexture(data.TextureData.howtobuttonTexture);
    WEGraphics::UnloadTexture(data.TextureData.optionbuttonTexture);
    WEGraphics::UnloadTexture(data.TextureData.menutitleTexture);
	WEGraphics::UnloadTexture(data.TextureData.particleTexture);
	WEGraphics::UnloadTexture(data.TextureData.ballGuideTexture);


	for (int i = 0; i < 8; ++i)
	{
		WEGraphics::UnloadTexture(data.TextureData.buildingTexture[i]);
		WEGraphics::UnloadTexture(data.TextureData.buildingclearTexture[i]);
	}

	WEDEBUG_PRINT("%d, %d\n", data.MaxLevel, data.LevelControl);
	


	WriteLevelControl(data.path.c_str(), data);


    
  }//Play_Unload

  
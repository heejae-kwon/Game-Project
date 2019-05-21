/******************************************************************************/
/*!
\file   Button.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that include button's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Button.h"
/******************************************************************************/
/*!
\brief 
	Create Buttons

\param data
	Get map data
*/
/******************************************************************************/
void CreateButton(Play &data)
{
  //Set up my buttons
  int texture;
  WEVec2 pos;
  WEVec2 scale;
  Action action;

  //Shot Button
  pos = data.pButtons[0].pos;
  scale = data.pButtons[0].scale;
  texture = data.TextureData.shootTexture;
  action = ShootAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

  //Box Button
  pos = data.pButtons[1].pos;
  scale = data.pButtons[1].scale;
  texture = data.TextureData.boxbuttonTexture;
  action = CreateBlockAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

  //Mainmenu Button
  pos = data.pButtons[2].pos;
  scale = data.pButtons[2].scale;
  texture = data.TextureData.mainmenubuttonTexture;
  action = MainMenuAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

  //HowTo Button
  pos = data.pButtons[3].pos;
  scale = data.pButtons[3].scale;
  texture = data.TextureData.howtobuttonTexture;
  action = HowToAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

  //Option Button
  pos = data.pButtons[4].pos;
  scale = data.pButtons[4].scale;
  texture = data.TextureData.optionbuttonTexture;
  action = OptionAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

  //Quit Button
  pos = data.pButtons[5].pos;
  scale = data.pButtons[5].scale;
  texture = data.TextureData.quitTexture;
  action = QuitAction;
  data.pObjMgr->AddButton(pos, scale, texture, 255, 255, 255, 255, action);

} // CreateButton

/******************************************************************************/
/*!
\brief
	Update buttons

\param pButtons
	The pointer of buttons

\param data
		Get map data
*/
/******************************************************************************/
void UpdateButton(Object *pButtons, Play &data)
{
  if (WEInput::IsTriggered(WE_MOUSE_LEFT))
  {
    WEVec2 click;
    WEInput::GetMouse(click);
    for (int i = 0; i < data.pObjMgr->GetButtonCount(); ++i)
    {
      if (WEIntersection::PointRect(click, pButtons[i].pos,
        pButtons[i].scale.x, pButtons[i].scale.y))
      {
        pButtons[i].action();

        if (data.ConditionData.ballCondition == Shooting && pButtons[i].texture == data.TextureData.shootTexture)
        {
          pButtons[i].texture = data.TextureData.stopTexture;
        }
        else if (data.ConditionData.ballCondition == Resetting)
        {
          pButtons[i].texture = data.TextureData.shootTexture;
        }
      }
    }// for loop
  }// IsTriggered

  if (data.DT == true)
  {
    for (int i = 2; i < 6; ++i)
    {
      pButtons[i].pos = { -2000, -2000 };
    }
  }
} //UpdateButton

/******************************************************************************/
/*!
\brief
 In game menu button update

\param pButtons
The pointer of buttons

\param data
Get map data
*/
/******************************************************************************/
void InGameMenuButtonUpdate(Object *pButtons, Play &data)
{
  if (data.DT == false)
  {
    //Menu button
    for (int i = 2; i < 6; ++i)
    {

      pButtons[i].pos = { 640, 580 - (static_cast<float>(i - 1)) * 100 };
      
    }
    if (WEInput::IsTriggered(WE_MOUSE_LEFT))
    {
      WEVec2 click;
      WEInput::GetMouse(click);
      for (int i = 2; i < 6; ++i)
      {
        if (WEIntersection::PointRect(click, pButtons[i].pos,
          pButtons[i].scale.x, pButtons[i].scale.y))
        {
          pButtons[i].action();
        }
      }
    }
  }

}

/******************************************************************************/
/*!
\brief
Draw buttons

\param pButtons
The pointer of buttons

\param data
Get map data
*/
/******************************************************************************/
void DrawButton(const Object *pButtons, const Play &data)
{
	//Get mouse
	WEVec2 click;
	WEInput::GetMouse(click);

  WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
  WEMtx44 tranform;
  for (int i = 0; i < data.pObjMgr->GetButtonCount(); ++i)
  {
	  if (!WEIntersection::PointRect(click, pButtons[i].pos,
		  pButtons[i].scale.x, pButtons[i].scale.y) || i < 2)
	  {
		  WEGraphics::SetTexture(pButtons[i].texture);
		  WEGraphics::SetTextureColor(pButtons[i].red,
			  pButtons[i].green,
			  pButtons[i].blue,
			  pButtons[i].alpha);
		  WEMtx44::MakeTransform(tranform,
			  pButtons[i].scale.x,
			  pButtons[i].scale.y,
			  0,
			  pButtons[i].pos.x,
			  pButtons[i].pos.y,
			  0);
		  WEGraphics::Draw(tranform);
	  }

	  else
	  {
		  WEGraphics::SetTexture(pButtons[i].texture);
		  WEGraphics::SetTextureColor(pButtons[i].red,
			  pButtons[i].green,
			  pButtons[i].blue,
			  pButtons[i].alpha);
		  WEMtx44::MakeTransform(tranform,
			  pButtons[i].scale.x * 1.2f,
			  pButtons[i].scale.y * 1.2f,
			  0,
			  pButtons[i].pos.x,
			  pButtons[i].pos.y,
			  0);
		  WEGraphics::Draw(tranform);
	  }

  }
}


/******************************************************************************/
/*!
\brief
	BLOCK NUMBER COUNT DISPLAY

\param data
Get map data
*/
/******************************************************************************/
void DrawNumbers(const Play &data)
{

    WEMtx44 tranform;
    int Number = data.pObjMgr->GetBlockCount();
    WEGraphics::SetTexture(data.TextureData.NumberTextures);

    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEMtx44::MakeTransform(tranform,
      64,
      64,
      0,
      data.pButtons[1].pos.x + data.pButtons[1].scale.x * 0.6f,
        data.pButtons[1].pos.y - data.pButtons[1].scale.y * 0.5f,
      1);
    WEGraphics::SetTextureCoords(0.1f, 1, 0, 0.1f * (data.maxBlocks - Number), 0);
    WEGraphics::Draw(tranform);
}

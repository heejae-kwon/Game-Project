/******************************************************************************/
/*!
\file   InGameMenu.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes InGameMenu's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "InGameMenu.h"

/******************************************************************************/
/*!
\brief
Draw InGameMenu

\param data
Get map data
*/
/******************************************************************************/
void InGameMenuDraw(Play &data)
{
  if (data.DT == false)
  {
    WEMtx44 transform;

    //Draw Menu Title
    WEGraphics::SetTexture(data.TextureData.menutitleTexture);
    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEMtx44::MakeTransform(transform,
      280,
      120,
      0.0f,
      640,
      600,
      0);
    WEGraphics::Draw(transform);

    //Draw Menu Background
    WEGraphics::SetTexture(data.TextureData.menuTexture);
    WEGraphics::SetTextureColor(255, 255, 255, 100);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      data.screenWidth / 2,
      data.screenHeight / 2,
      1.0);
    WEGraphics::Draw(transform);
  }
}

/******************************************************************************/
/*!
\brief 
Pause the game and call the InGameMenu

\param data
Get map data
*/
/******************************************************************************/
void Escaping(Play &data)
{
  if (WEInput::IsTriggered(WE_ESCAPE) && data.DT == true)
  {
    data.DT = false;
  }
  else if (WEInput::IsTriggered(WE_ESCAPE) && data.DT == false)
  {
    data.DT = true;
  }
}
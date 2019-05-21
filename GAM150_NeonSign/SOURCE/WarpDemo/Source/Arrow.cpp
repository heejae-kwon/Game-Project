/******************************************************************************/
/*!
\file   Arrow.cpp
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
To do draw Arrow and Update Arrow.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Arrow.h"

/******************************************************************************/
/*!
\param data
To make Arrow constructor

\brief Create Arrow
*/
/******************************************************************************/
void CreateArrow(Play &data)
{
	//Initialize the Arrow informations
  float scaleNUM = 14;
  float rotation = WEMath::DegreeToRadian(45);
  WEVec2 pos = { data.topLeft.x, data.botRight.y-100 };
  WEVec2 scale = { scaleNUM, scaleNUM };

  /*give it to Object manager*/
  data.pObjMgr->AddArrow(pos, scale, rotation, 255, 255, 255, 255);
}//CreateArrow

/******************************************************************************/
/*!
\param pBalls
Arrow's reference point is ball

\param pArrow
Update this arrow

\param pButtons
To get button condition

\param data
Get Play struct to get condition

\brief
Update Arrow
*/
/******************************************************************************/
void UpdateArrow(Ball *pBalls, Object *pArrow, Object *pButtons, Play &data)
{
  WEVec2 normal;
  
  if (WEInput::IsPressed(WE_MOUSE_LEFT) && data.ConditionData.ballCondition == Stoping && !WEInput::IsPressed(WE_P))
  {

    WEVec2 click;
    float cos;

	//Get click
    WEInput::GetMouse(click);
    for (int j = 0; j < data.pObjMgr->GetButtonCount(); ++j)
    {
		//Click the buttons
      if (WEIntersection::PointRect(click, pButtons[j].pos, pButtons[j].scale.x, pButtons[j].scale.y))
      {
        data.BTCheck = true;
      }
    }

	//Not click the buttons
    if (data.BTCheck == false)
    {
      for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
      {
		  //Get click position
        WEGraphics::ConvertScreenToWorld(click.x, click.y);

		//In click limit range
		if (WEIntersection::PointCircle(click, pBalls[i].pos, DIRECTION_AREA) == false)
			return;

		//Get click vector
        WEVec2::Normalize(normal, click - pBalls[i].pos);

		//Get rotation
        cos = WEVec2::Dot(normal, { 1, 0 });

		//Set rotation
        if (pBalls[i].pos.y < click.y)
          pArrow[0].rotation = WEMath::DegreeToRadian(My_Degreefloat(cos));
        else
          pArrow[0].rotation = WEMath::DegreeToRadian(-My_Degreefloat(cos));

		//Set texture
        pArrow[0].texture = data.TextureData.arrowTexture;

		//Set direction
        pArrow[0].pos.x = pBalls[i].pos.x + (normal.x * pArrow[0].scale.x);
        pArrow[0].pos.y = pBalls[i].pos.y + (normal.y * pArrow[0].scale.y);
      }
    }
    data.BTCheck = false;
  }
}//UpdateArrow

/******************************************************************************/
/*!
\param pArrow
Draw this arrow

\param data
Get Play struct to get condition

\brief
Draw Arrow
*/
/******************************************************************************/
void DrawArrow(const Object *pArrow, const Play &data)
{
	//Set texture coords
  WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);

  WEMtx44 tranform;

  //What to draw
  WEGraphics::SetTexture(data.TextureData.arrowTexture);

  //Texture color
  WEGraphics::SetTextureColor(pArrow[0].red, pArrow[0].blue, pArrow[0].green, pArrow[0].alpha);

  //Draw it
  WEMtx44::MakeTransform(tranform,
    pArrow[0].scale.x,
    pArrow[0].scale.y,
    pArrow[0].rotation,
    pArrow[0].pos.x,
    pArrow[0].pos.y,
    0);
  WEGraphics::Draw(tranform);
}

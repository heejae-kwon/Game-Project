/******************************************************************************/
/*!
\file   Wall.cpp
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
To make walls and get wall lines' informations

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Wall.h"

/******************************************************************************/
/*!
\param data
Get map data

\brief
Create Wall
*/
/******************************************************************************/
void CreateWall(Play &data)
{
	//While i is maxWalls
	for (int i = 0; i < data.maxWalls; ++i)
	{
		//Initialize values
		WEVec2 pos = data.pWalls[i].pos;
		WEVec2 scale = data.pWalls[i].scale;
		WEVec2 point[4];
		WEVec2 line[4];
		float rotation = data.pWalls[i].rotation;

		WEVec2 RotatedCoordinate[REC_POINT_COUNT];

		//Rotating points in zero
		RotatedCoordinate[0] = My_RotateVec2(rotation, scale.x * 0.5f, scale.y * 0.5f);
		RotatedCoordinate[1] = My_RotateVec2(rotation, scale.x * 0.5f, -scale.y * 0.5f);
		RotatedCoordinate[2] = My_RotateVec2(rotation, -scale.x * 0.5f, -scale.y * 0.5f);
		RotatedCoordinate[3] = My_RotateVec2(rotation, -scale.x * 0.5f, scale.y * 0.5f);

		//Set points and lines
		My_SetPoints_And_Lines(RotatedCoordinate, pos, point, line);

		/*Add to the object manager*/
		data.pObjMgr->AddWall(pos, scale, line, point, rotation,
			255, 255, 255, 255);
	}
}//CreateWall

/******************************************************************************/
/*!
\param pWall
Get all walls' information

\param data
Get map data

\brief
Create Wall
*/
/******************************************************************************/
void DrawWall(const Block *pWall, const Play &data)
{
	//Set Texture Coords
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);

	WEMtx44 tranform;

	//What to draw
	WEGraphics::SetTexture(data.TextureData.wallTexture);

	//Draw all walls
	for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
	{
		WEGraphics::SetTextureColor(pWall[i].red,
			pWall[i].green,
			pWall[i].blue,
			pWall[i].alpha);
		WEMtx44::MakeTransform(tranform,
			pWall[i].scale.x,
			pWall[i].scale.y,
			pWall[i].rotation,
			pWall[i].pos.x,
			pWall[i].pos.y,
			0);

		WEGraphics::Draw(tranform);
	}

	//What to draw
	WEGraphics::SetTexture(data.TextureData.wallInTexture);

	//Draw all wall neon
	for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
	{
		WEGraphics::SetTextureColor(pWall[i].red,
			pWall[i].green,
			pWall[i].blue,
			pWall[i].alpha);
		WEMtx44::MakeTransform(tranform,
			pWall[i].scale.x * .98f,
			pWall[i].scale.y * .98f,
			pWall[i].rotation,
			pWall[i].pos.x,
			pWall[i].pos.y,
			0);

		WEGraphics::Draw(tranform);
	}
}


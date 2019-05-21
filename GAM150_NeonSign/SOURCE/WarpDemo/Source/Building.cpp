/******************************************************************************/
/*!
\file   Building.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that include building's functions 

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Building.h"

/******************************************************************************/
/*!
\brief
Draw buildings (background)

\param data
Get map data
*/
/******************************************************************************/
void DrawBuilding(const Play &data)
{
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255, 255, 255, 50);
	for (int i = 0; i < BUILDING_COUNT; ++i)
	{
		WEMtx44 transform;
		WEGraphics::SetTexture(data.Buildings[i].texture);
		WEMtx44::MakeTransform(transform,
			data.Buildings[i].scale.x,
			data.Buildings[i].scale.y,
			0.0f,
			data.Buildings[i].pos.x,
			data.Buildings[i].pos.y,
			-1);
		WEGraphics::Draw(transform);
	}
}

/******************************************************************************/
/*!
\brief
Init buildings data

\param data
Get map data
*/
/******************************************************************************/
void InitBuilding(Play &data)
{
	//Setting Buildings
	data.Buildings[0].pos = { 100, 105 };
	data.Buildings[0].scale = { 142, 217 };
	data.Buildings[0].texture = data.TextureData.buildingTexture[0];

	data.Buildings[1].pos = { 250, 175 };
	data.Buildings[1].scale = { 85, 353 };
	data.Buildings[1].texture = data.TextureData.buildingTexture[1];

	data.Buildings[2].pos = { 380, 200 };
	data.Buildings[2].scale = { 80, 410 };
	data.Buildings[2].texture = data.TextureData.buildingTexture[2];

	data.Buildings[3].pos = { 540, 260 };
	data.Buildings[3].scale = { 114, 533 };
	data.Buildings[3].texture = data.TextureData.buildingTexture[3];

	data.Buildings[4].pos = { 700, 170 };
	data.Buildings[4].scale = { 94, 345 };
	data.Buildings[4].texture = data.TextureData.buildingTexture[4];

	data.Buildings[5].pos = { 860, 270 };
	data.Buildings[5].scale = { 152, 550 };
	data.Buildings[5].texture = data.TextureData.buildingTexture[5];

	data.Buildings[6].pos = { 1030, 230 };
	data.Buildings[6].scale = { 92, 463 };
	data.Buildings[6].texture = data.TextureData.buildingTexture[6];

	data.Buildings[7].pos = { 1180, 260 };
	data.Buildings[7].scale = { 130, 534 };
	data.Buildings[7].texture = data.TextureData.buildingTexture[7];

	for (int i = 0; i <= data.MaxLevel; ++i)
	{
		if (i != 0)
		  data.Buildings[i - 1].texture = data.TextureData.buildingclearTexture[i - 1];
	}
}
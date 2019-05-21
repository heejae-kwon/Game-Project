/******************************************************************************/
/*!
\file   Block.cpp
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
To make block and get block lines' informations

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Block.h"

/******************************************************************************/
/*!
\param data
Get map data

\param count
How many blocks exist

\brief
Create Block
*/
/******************************************************************************/
void CreateBlock(Play &data, int count)
{
	for (int i = 0; i < count; ++i)
	{
		//Initialize values
		WEVec2 pos;
		WEVec2 scale = data.blockFileScale;
		WEVec2 point[4];
		WEVec2 line[4];
		float rotation = 0;

		//It will be created in the screen.
		pos.x = WERandom::GetFloat(data.topLeft.x + scale.x, data.botRight.x + scale.x) * 0.5f;
		pos.y = WERandom::GetFloat(data.botRight.y + scale.x, data.topLeft.y + scale.x) * 0.5f;

		//Get rectangle's points
		point[0] = { pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f) };
		point[1] = { pos.x + (scale.x * 0.5f), pos.y - (scale.y * 0.5f) };
		point[2] = { pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f) };
		point[3] = { pos.x - (scale.x * 0.5f), pos.y + (scale.y * 0.5f) };


		//Get Line vectors
		line[0] = point[0] - point[1];
		line[1] = point[1] - point[2];
		line[2] = point[2] - point[3];
		line[3] = point[3] - point[0];

		/*Add to the object manager*/
		data.pObjMgr->AddBlock(pos, scale, line, point, rotation,
			255, 255, 255, 255);
	}//end for i
}//CreateBlock


/******************************************************************************/
/*!
\param pBlocks
Get created blocks

\param data
Get condition's and map data

\brief
Delete Block
*/
/******************************************************************************/
void DeleteBlock(Block *pBlocks, Play &data)
{
	//Delete the Block
	if (WEInput::IsPressed(WE_MOUSE_RIGHT))
	{
		//Get mouse
		WEVec2 click;
		WEInput::GetMouse(click);

		//Get mouse position
		WEGraphics::ConvertScreenToWorld(click.x, click.y);

		for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
		{
			//If user right click the box, delete it
			if (WEIntersection::PointRect(click, pBlocks[i].pos,
				pBlocks[i].scale.x, pBlocks[i].scale.y) && data.ConditionData.ballCondition == Stoping)
			{
				data.pObjMgr->DeleteBlock(pBlocks[i].blockID);
			}
		} //for loop
	}//WEInput::IsPressed(WE_MOUSE_RIGHT)
}

void DrawBlock(const Block *pBlocks, const Play &data)
{
	//Set Texture Coord
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);

	WEMtx44 tranform;

	//What to draw
	WEGraphics::SetTexture(data.TextureData.blockTexture);

	//Draw it while i is blockCount.
	for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
	{

		WEGraphics::SetTextureColor(pBlocks[i].red,
			pBlocks[i].green,
			pBlocks[i].blue,
			pBlocks[i].alpha);
		WEMtx44::MakeTransform(tranform,
			pBlocks[i].scale.x,
			pBlocks[i].scale.y,
			pBlocks[i].rotation,
			pBlocks[i].pos.x,
			pBlocks[i].pos.y,
			1);

		WEGraphics::Draw(tranform);
	}
}

/******************************************************************************/
/*!
\param pBlocks
Get blocks information

\param data
Get map data and condition

\brief
Update Block's Input
*/
/******************************************************************************/
void UpdateBlockInput(Block *pBlocks, Play &data)
{
	//UpdateBlockMovement

	//Rotating the ball
	if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_UP))
	{
		//Get click and it's position
		WEVec2 click;
		WEInput::GetMouse(click);
		WEGraphics::ConvertScreenToWorld(click.x, click.y);

		for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
		{
			//Condition is stoping and mouse is on the box
			if (WEIntersection::PointRect(click, pBlocks[i].pos,
				pBlocks[i].scale.x, pBlocks[i].scale.y)
				&& data.ConditionData.ballCondition == Stoping && data.ConditionData.rotateCondition == CanRotate)
			{
				pBlocks[i].Rotateclicked = true;
			}

			if (pBlocks[i].Rotateclicked == true)
			{
				//Set other box don't rotate
				data.ConditionData.rotateCondition = CannotRotate;

				//One scroll, change 15 degree
				pBlocks[i].rotation += WEMath::DegreeToRadian(15);

				//Set point position origin
				for (int k = 0; k < REC_POINT_COUNT; ++k)
				{
					pBlocks[i].point[k] -= pBlocks[i].pos;
				}

				WEVec2 RotatedCoordinate[REC_POINT_COUNT];

				//Rotating points in zero
				RotatedCoordinate[0] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[1] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[2] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[3] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);

				//Get line and point
				My_SetPoints_And_Lines(RotatedCoordinate, pBlocks[i].pos, pBlocks[i].point, pBlocks[i].line);

			}
		}//for
	}//WE_MOUSE_MIDDLE_UP

	else if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN))
	{
		//Get click and it's position
		WEVec2 click;
		WEInput::GetMouse(click);
		WEGraphics::ConvertScreenToWorld(click.x, click.y);

		for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
		{
			//Condition is stoping and mouse is on the box
			if (WEIntersection::PointRect(click, pBlocks[i].pos,
				pBlocks[i].scale.x, pBlocks[i].scale.y)
				&& data.ConditionData.ballCondition == Stoping && data.ConditionData.rotateCondition == CanRotate)
			{
				pBlocks[i].Rotateclicked = true;
			}
			if (pBlocks[i].Rotateclicked == true)
			{
				//Set other box don't rotate
				data.ConditionData.rotateCondition = CannotRotate;

				//One scroll, change 15 degree
				pBlocks[i].rotation -= WEMath::DegreeToRadian(15);

				//Set point position origin
				for (int k = 0; k < REC_POINT_COUNT; ++k)
				{
					pBlocks[i].point[k] -= pBlocks[i].pos;
				}

				WEVec2 RotatedCoordinate[REC_POINT_COUNT];

				//Rotating points in zero
				RotatedCoordinate[0] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[1] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[2] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[3] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);

				//Get line and point
				My_SetPoints_And_Lines(RotatedCoordinate, pBlocks[i].pos, pBlocks[i].point, pBlocks[i].line);

			}
		}//for
	} //WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN)
	//Drag the Block
	else if (WEInput::IsPressed(WE_MOUSE_LEFT))
	{
		//Get click and it's position
		WEVec2 click;
		WEInput::GetMouse(click);
		WEGraphics::ConvertScreenToWorld(click.x, click.y);


		for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
		{
			//Condition is stoping and mouse is on the box
			if (WEIntersection::PointRect(click, pBlocks[i].pos,
				pBlocks[i].scale.x, pBlocks[i].scale.y)
				&& data.ConditionData.ballCondition == Stoping && data.ConditionData.blockCondition == CanMove)
			{
				pBlocks[i].clicked = true;
			}

			if (pBlocks[i].clicked == true)
			{
				//Disturb the other ball's movement
				data.ConditionData.blockCondition = CannotMove;


				//Calculate move block distance for natural drag It should be happened only once.
				if (data.blockDrag.x == data.botLeft.x - 1000 && data.blockDrag.y == data.botLeft.y - 1000)
					data.blockDrag = click - pBlocks[i].pos;

				//Change position
				pBlocks[i].pos = click - data.blockDrag;


				//Move to zero cooridinate

				WEVec2 RotatedCoordinate[REC_POINT_COUNT];

				//Rotating points in zero
				RotatedCoordinate[0] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[1] = My_RotateVec2(pBlocks[i].rotation, pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[2] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, -pBlocks[i].scale.y * 0.5f);
				RotatedCoordinate[3] = My_RotateVec2(pBlocks[i].rotation, -pBlocks[i].scale.x * 0.5f, pBlocks[i].scale.y * 0.5f);

				//Get points and lines
				My_SetPoints_And_Lines(RotatedCoordinate, pBlocks[i].pos, pBlocks[i].point, pBlocks[i].line);

			}
		} //for loop
	}//WEInput::IsPressed(WE_MOUSE_LEFT)
	else
	{
		//Reset the informations
		for (int i = 0; i < data.pObjMgr->GetBlockCount(); ++i)
		{
			pBlocks[i].clicked = false;
			pBlocks[i].Rotateclicked = false;
			data.ConditionData.rotateCondition = CanRotate;
			data.ConditionData.blockCondition = CanMove;
			data.blockDrag = { data.botLeft.x - 1000, data.botLeft.y - 1000 };
		}
	}//Defalut settings

} //UpdateBlockInput

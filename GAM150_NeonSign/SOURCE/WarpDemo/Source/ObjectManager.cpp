/******************************************************************************/
/*!
\file   ObjectManager.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  This is the interface file for all member functions of a class called
				ObjectManager.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "ObjectManager.h"
#include "WEDebugTools.h"

/******************************************************************************/
/*!
\brief
Constructor of class called ObjectManager.

\param maxBalls
The maximum number of Balls

\param maxButtons
The maximum number of Buttons

\param maxBlocks
The maximum number of Blocks

\param maxGoals
The maximum number of Goals

\param maxWalls
The maximum number of Walls

\param maxSB
The maximum number of SpecialBox
*/
/******************************************************************************/
ObjectManager::ObjectManager(int maxBalls, int maxButtons, int maxBlocks, int maxGoals, int maxWalls, int maxSB)
{
m_button = new Object[maxButtons];
m_ball = new Ball[maxBalls];
m_block = new Block[maxBlocks];
m_arrow = new Object[1];
m_goal = new Object[maxGoals];
m_wall = new Block[maxWalls];
m_SB = new Block[maxSB];

m_maxBalls = maxBalls;
m_maxButtons = maxButtons;
m_maxBlocks = maxBlocks;
m_maxGoals = maxGoals;
m_maxWalls = maxWalls;
m_maxSB = maxSB;

m_ballcount = 0;
m_buttoncount = 0;
m_blockcount = 0;
m_arrowcount = 0;
m_goalcount = 0;
m_wallcount = 0;
m_SBcount = 0;
}

/******************************************************************************/
/*!
\brief
Destructor of class called ObjectManager.
*/
/******************************************************************************/
ObjectManager::~ObjectManager(void)
{
delete [] m_button;
m_button = 0;

delete [] m_ball;
m_ball = 0;

delete [] m_block;
m_block = 0;

delete [] m_arrow;
m_arrow = 0;

delete [] m_goal;
m_goal = 0;

delete[] m_wall;
m_wall = 0;
}

/******************************************************************************/
/*!
\brief
The function that returns pointer of ball

\return m_ball
*/
/******************************************************************************/
Ball* ObjectManager::GetBalls(void)
{
return m_ball;
}

/******************************************************************************/
/*!
\brief
The function that returns count of ball

\return m_ballcount
*/
/******************************************************************************/
int ObjectManager::GetBallCount(void) const
{
return m_ballcount;
}

/******************************************************************************/
/*!
\brief
The function that add Balls

\param pos
The position of ball

\param scale
The scale of ball

\param vel
The velocity of ball

\param forceSum
The forceSum of ball

\param mass
The mass of ball

\param radius
The radius of ball

\param rotation
The rotation of ball

\param rotationVel
The rotationVel of ball

\param DState
The DState of ball

\param red
The red of ball color

\param blue
The blue of ball color

\param green
The green of ball color

\param alpha
The alpha of ball color
*/
/******************************************************************************/
void ObjectManager::AddBall(WEVec2 pos,
WEVec2 scale,
WEVec2 vel,
WEVec2 forceSum,
float mass,
float radius,
float rotation,
float rotationVel,
bool DState,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha)

{
  if (m_ballcount < m_maxBalls)
  {
    m_ball[m_ballcount].pos = pos;
    m_ball[m_ballcount].scale = scale;
    m_ball[m_ballcount].vel = vel;
    m_ball[m_ballcount].forceSum = forceSum;
    m_ball[m_ballcount].mass = mass;
    m_ball[m_ballcount].radius = radius;
    m_ball[m_ballcount].rotation = rotation;
    m_ball[m_ballcount].rotationVel = rotationVel;
    m_ball[m_ballcount].DState = DState;
    m_ball[m_ballcount].red = red;
    m_ball[m_ballcount].blue = blue;
    m_ball[m_ballcount].green = green;
    m_ball[m_ballcount].alpha = alpha;
		m_ball[m_ballcount].clicked = false;
    m_ball[m_ballcount].ballID = m_ballcount;
    ++m_ballcount;
  }

}

/******************************************************************************/
/*!
\brief
The function that returns pointer of buttons

\return m_button
*/
/******************************************************************************/
Object* ObjectManager::GetButtons(void)
{
  return m_button;
}

/******************************************************************************/
/*!
\brief
The function that returns count of buttons

\return m_buttoncount
*/
/******************************************************************************/
int ObjectManager::GetButtonCount(void) const
{
  return m_buttoncount;
}

/******************************************************************************/
/*!
\brief
The function that add Buttons

\param pos
The position of buttons

\param scale
The scale of buttons

\param texture
The texture of buttons

\param action
The action of buttons

\param red
The red of buttons color

\param blue
The blue of buttons color

\param green
The green of buttons color

\param alpha
The alpha of buttons color
*/
/******************************************************************************/
void ObjectManager::AddButton(WEVec2 pos,
  WEVec2 scale,
  int texture,
  unsigned char red,
  unsigned char blue,
  unsigned char green,
  unsigned char alpha,
  Action action)
  {
    if (m_buttoncount < m_maxButtons)
    {
      m_button[m_buttoncount].pos = pos;
		  m_button[m_buttoncount].scale = scale;
      m_button[m_buttoncount].texture = texture;
		  m_button[m_buttoncount].objectID = m_buttoncount;
      m_button[m_buttoncount].red = red;
      m_button[m_buttoncount].blue = blue;
      m_button[m_buttoncount].green = green;
      m_button[m_buttoncount].alpha = alpha;
      m_button[m_buttoncount].action = action;

      ++m_buttoncount;
    }

  }

/******************************************************************************/
/*!
\brief
The function that returns pointer of blocks

\return m_block
*/
/******************************************************************************/
Block* ObjectManager::GetBlocks(void)
{
return m_block;
}
/******************************************************************************/
/*!
\brief
The function that returns count of blocks

\return m_blockcount
*/
/******************************************************************************/
int ObjectManager::GetBlockCount(void) const
{
return m_blockcount;
}

/******************************************************************************/
/*!
\brief
The function that add Blocks

\param pos
The position of blocks

\param scale
The scale of blocks

\param line
The line of blocks

\param point
The point of blocks

\param rotation
The rotation of blocks

\param red
The red of blocks color

\param blue
The blue of blocks color

\param green
The green of blocks color

\param alpha
The alpha of blocks color
*/
/******************************************************************************/
void ObjectManager::AddBlock(WEVec2 pos,
WEVec2 scale,
WEVec2 line[4],
WEVec2 point[4],
float rotation,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha)
{
		if (m_blockcount < m_maxBlocks)
		{
		m_block[m_blockcount].pos = pos;
		m_block[m_blockcount].scale = scale;
		m_block[m_blockcount].rotation = rotation;
		m_block[m_blockcount].red = red;
		m_block[m_blockcount].blue = blue;
		m_block[m_blockcount].green = green;
		m_block[m_blockcount].alpha = alpha;


		m_block[m_blockcount].blockID = m_blockcount;
		m_block[m_blockcount].clicked = false;
		m_block[m_blockcount].Rotateclicked = false;
  
		for (int j = 0; j < 4; ++j)
		{
		m_block[m_blockcount].line[j] = line[j];
		m_block[m_blockcount].point[j] = point[j];
		}

		++m_blockcount;
		}

}

/******************************************************************************/
/*!
\brief
The function that delete the blocks

\brief blockID
The ID of block that will be deleted
*/
/******************************************************************************/
void ObjectManager::DeleteBlock(int blockID)
{

--m_blockcount;
//move the remain arrays to front
	for (int i = blockID; i <= m_blockcount; ++i)
	{
	m_block[i].pos = m_block[i+1].pos;
	m_block[i].scale = m_block[i+1].scale;
	m_block[i].rotation = m_block[i + 1].rotation;
	m_block[i].red = m_block[i+1].red;
	m_block[i].blue = m_block[i+1].blue;
	m_block[i].green = m_block[i+1].green;
	m_block[i].alpha = m_block[i+1].alpha;

		for (int j = 0; j < 4; ++j)
		{
			m_block[i].line[j] = m_block[i + 1].line[j];
			m_block[i].point[j] = m_block[i + 1].point[j];
		}
	}
}

/******************************************************************************/
/*!
\brief
The function that returns pointer of arrow

\return m_arrow
*/
/******************************************************************************/
Object* ObjectManager::GetArrow(void)
{
return m_arrow;
}

/******************************************************************************/
/*!
\brief
The function that add Arrow

\param pos
The position of arrow

\param scale
The scale of arrow

\param rotation
The rotation of arrow

\param red
The red of arrow color

\param blue
The blue of arrow color

\param green
The green of arrow color

\param alpha
The alpha of arrow color
*/
/******************************************************************************/
void ObjectManager::AddArrow(WEVec2 pos,
WEVec2 scale,
float rotation,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha)
{
	m_arrow[0].pos = pos;
	m_arrow[0].scale = scale;
	m_arrow[0].rotation = rotation;
	m_arrow[0].red = red;
	m_arrow[0].blue = blue;
	m_arrow[0].green = green;
	m_arrow[0].alpha = alpha;

}

/******************************************************************************/
/*!
\brief
The function that returns pointer of Goal

\return m_goal
*/
/******************************************************************************/
Object* ObjectManager::GetGoals(void)
{
return m_goal;
}

/******************************************************************************/
/*!
\brief
The function that returns count of Goal

\return m_goalcount
*/
/******************************************************************************/
int ObjectManager::GetGoalCount(void) const
{
return m_goalcount;
}

/******************************************************************************/
/*!
\brief
The function that add Goal

\param pos
The position of goal

\param scale
The scale of goal

\param radius
The radius of goal

\param red
The red of goal color

\param blue
The blue of goal color

\param green
The green of goal color

\param alpha
The alpha of goal color

\param action
The action of goal color
*/
/******************************************************************************/
void ObjectManager::AddGoal(WEVec2 pos,
WEVec2 scale,
float radius,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha,
Action action)
{
  if (m_goalcount < m_maxGoals)
  {
    m_goal[m_goalcount].pos = pos;
    m_goal[m_goalcount].scale = scale;
    m_goal[m_goalcount].radius = radius;
    m_goal[m_goalcount].red = red;
    m_goal[m_goalcount].blue = blue;
    m_goal[m_goalcount].green = green;
    m_goal[m_goalcount].alpha = alpha;
    m_goal[m_goalcount].action = action;

    ++m_goalcount;
  }
}

/******************************************************************************/
/*!
\brief
The function that returns pointer of Wall

\return m_wall
*/
/******************************************************************************/
Block* ObjectManager::GetWalls(void)
{
return m_wall;
}

/******************************************************************************/
/*!
\brief
The function that returns count of Wall

\return m_wallcount
*/
/******************************************************************************/
int ObjectManager::GetWallCount(void) const
{
return m_wallcount;
}
/******************************************************************************/
/*!
\brief
The function that add Walls

\param pos
The position of Walls

\param scale
The scale of Walls

\param line
The line of Walls

\param point
The point of Walls

\param rotation
The rotation of Walls

\param red
The red of Walls color

\param blue
The blue of Walls color

\param green
The green of Walls color

\param alpha
The alpha of Walls color
*/
/******************************************************************************/
void ObjectManager::AddWall(WEVec2 pos,
WEVec2 scale,
WEVec2 line[4],
WEVec2 point[4],
float rotation,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha)
{
if (m_wallcount < m_maxWalls)
{
  m_wall[m_wallcount].pos = pos;
  m_wall[m_wallcount].scale = scale;
  m_wall[m_wallcount].rotation = rotation;
  m_wall[m_wallcount].red = red;
  m_wall[m_wallcount].blue = blue;
  m_wall[m_wallcount].green = green;
  m_wall[m_wallcount].alpha = alpha;


  m_wall[m_wallcount].blockID = m_wallcount;
  m_wall[m_wallcount].clicked = false;
  m_wall[m_wallcount].Rotateclicked = false;

  for (int j = 0; j < 4; ++j)
  {
    m_wall[m_wallcount].line[j] = line[j];
    m_wall[m_wallcount].point[j] = point[j];
  }

  ++m_wallcount;
}

}  

/******************************************************************************/
/*!
\brief
The function that returns pointer of SB

\return m_SB
*/
/******************************************************************************/
Block* ObjectManager::GetSB(void)
{
return m_SB;
}

/******************************************************************************/
/*!
\brief
The function that returns count of SB

\return m_SBcount
*/
/******************************************************************************/
int ObjectManager::GetSBCount(void) const
{
return m_SBcount;
}

/******************************************************************************/
/*!
\brief
The function that add SpecialBox

\param pos
The position of SpecialBox

\param scale
The scale of SpecialBox

\param rotation
The rotation of SpecialBox

\param red
The red of SpecialBox color

\param blue
The blue of SpecialBox color

\param green
The green of SpecialBox color

\param alpha
The alpha of SpecialBox color
*/
/******************************************************************************/
void ObjectManager::AddSB(WEVec2 pos,
WEVec2 scale,
float rotation,
unsigned char red,
unsigned char blue,
unsigned char green,
unsigned char alpha)
{
	if (m_SBcount < m_maxSB)
	{
		m_SB[m_SBcount].pos = pos;
		m_SB[m_SBcount].scale = scale;
		m_SB[m_SBcount].rotation = rotation;
		m_SB[m_SBcount].red = red;
		m_SB[m_SBcount].blue = blue;
		m_SB[m_SBcount].green = green;
		m_SB[m_SBcount].alpha = alpha;

		m_SB[m_SBcount].clicked = false;
		m_SB[m_SBcount].Rotateclicked = false;
		++m_SBcount;
	}
}
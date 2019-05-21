/******************************************************************************/
/*!
\file   ObjectManager.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  This is the header file for all member functions of a class called
				ObjectManager.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "GameTypes.h"

/******************************************************************************/
/*!
\class ObjectManager
The ObjectManager class implements managing all objects in game.
*/
/******************************************************************************/
class ObjectManager
{
public:
  ObjectManager(int maxBalls, int maxButtons, int maxBlocks, int maxGoals, int maxWalls, int maxSB);
  ~ObjectManager(void);

  //Ball
  Ball* GetBalls(void);
  int GetBallCount(void) const;
  void AddBall (WEVec2 pos,
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
  unsigned char alpha);

  //Button
  Object* GetButtons(void);
  int GetButtonCount(void) const;
  void AddButton(WEVec2 pos,
  WEVec2 scale,
  int texture,
  unsigned char red,
  unsigned char blue,
  unsigned char green,
  unsigned char alpha,
  Action action);

  //Block
  Block* GetBlocks(void);
  int GetBlockCount(void) const;
  void AddBlock(WEVec2 pos,
    WEVec2 scale,
    WEVec2 line[4],
    WEVec2 point[4],
    float rotation,
    unsigned char red,
    unsigned char blue,
    unsigned char green,
    unsigned char alpha);
  void DeleteBlock(int blockID);

  //Goal
  Object *GetGoals(void);
  int GetGoalCount(void) const;
  void AddGoal(WEVec2 pos,
    WEVec2 scale,
    float radius,
    unsigned char red,
    unsigned char blue,
    unsigned char green,
    unsigned char alpha,
    Action action);

  //Arrow
  Object *GetArrow(void);
  void AddArrow(WEVec2 pos,
    WEVec2 scale,
    float rotation,
    unsigned char red,
    unsigned char blue,
    unsigned char green,
    unsigned char alpha);
  void DeleteArrow(void);

  //Wall
  Block* GetWalls(void);
  int GetWallCount(void) const;
  void AddWall(WEVec2 pos,
   WEVec2 scale,
   WEVec2 line[4],
   WEVec2 point[4],
    float rotation,
    unsigned char red,
    unsigned char blue,
    unsigned char green,
    unsigned char alpha);

  //SB
  Block *GetSB(void);
  int GetSBCount(void) const;
  void AddSB(WEVec2 pos,
    WEVec2 scale,
    float rotation,
    unsigned char red,
    unsigned char blue,
    unsigned char green,
    unsigned char alpha);


private:

  
  Ball   *m_ball;
  Block  *m_block;
  Block  *m_wall;
  Object *m_button;
  Object *m_arrow;
  Object *m_goal;
  Block *m_SB;
  
  
  int m_ballcount;
  int m_buttoncount;
  int m_blockcount;
  int m_arrowcount;
  int m_goalcount;
  int m_wallcount;
  int m_SBcount;

  
  int m_maxBalls;
  int m_maxButtons;
  int m_maxBlocks;

  int m_maxGoals;
  int m_maxWalls;
  int m_maxSB;
};


#endif /* OBJECTMANAGER_H */

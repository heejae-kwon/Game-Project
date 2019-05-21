/******************************************************************************/
/*!
\file   GameTypes.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  This is the header file includes all types in game

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/

#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include "WEVec2.h"

enum ShotState
{
  Shooting,
  Stoping,
  Resetting
};

enum MoveState
{
  CanMove,
  CannotMove
};
enum RotateState
{
  CanRotate,
  CannotRotate
};

//For developer
enum ModRotateState
{
  CanModRotate,
  CannotModRotate
};
enum ModState
{
  CanMod,
  CannotMod
};


typedef void(*Action)(void);

struct Object
{
  WEVec2 pos;
  WEVec2 scale;
  float radius;
  float rotation;
  int texture;
  int objectID;
  Action action;
  bool clicked;

  unsigned char red;
  unsigned char blue;
  unsigned char green;
  unsigned char alpha;

};


struct Ball
{
  //mass, rotation, rotationVel, DynamicState
  WEVec2 pos;
  WEVec2 scale;
  WEVec2 vel;
  WEVec2 forceSum;
  float mass;
  float radius;
  float rotation;
  float rotationVel;
  bool DState;
  int texture;
  int ballID;
  unsigned char red;
  unsigned char blue;
  unsigned char green;
  unsigned char alpha;

  bool clicked;
};

struct Block
{
  //rotation, DynamicState
  WEVec2 pos;
  WEVec2 scale;
  WEVec2 line[4];
  WEVec2 point[4];
  float rotation;
  int texture;
  int blockID;
  unsigned char red;
  unsigned char blue;
  unsigned char green;
  unsigned char alpha;

  //click check
  bool clicked;
  bool Rotateclicked;
};

struct Building
{
	WEVec2 pos;
	WEVec2 scale;
	int texture;
};




#endif //GAME_TYPES_H
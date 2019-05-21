/******************************************************************************/
/*!
\file   WEGameData.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:Simple 2D Game Engine
\date   2012/12/5

This is a struct that you can define your own game specific game data in. This
is data that needs to be shared across states, such as player lives or game
score.  You must initilize the values in main before calling 
WEAppilcationInit.
*/
/******************************************************************************/
#ifndef WEGAMEDATA_H
#define WEGAMEDATA_H

/*! This struct holds game data that is shared between states. This struct must
have at least one data member in it.*/
struct WEGameData
{
  /*!< This should be removed and used for your game specific data */
  int yourGameDataHere;
};

#endif /* GameData_H */
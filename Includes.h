#pragma once

// - - - Libraries and stuff - - -
#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include	<SFML/Window.hpp>

#include	<array>
#include	<bitset>
#include	<cmath>
#include	<iostream>
#include	<string>
#include	<thread>
#include	<vector>
#include	<Windows.h>
#include	<memory>
#include	<cstdlib>

// - - - Header files - - -
	//	->	Network and Connections.
#include	"UserController.h"
#include	"SQLStuff.h"

//	->	Useful tools.
#include	"Tools_.h"
#include	"_MyIncludes_.h"

#include	"Room.h"
#include	"Terminal.h"
#include	"_Basics_Mouse.h"
#include	"_Basics_Button.h"
#include	"_Basics_KeyBoard.h"
#include	"SpriteFactory.h"
#include	"SoundFactory.h"
#include	"ShaderFactory.h"
#include	"MemoryUsage.h"
#include	"DrawFactory.h"
#include	"Statistic.h"
#include	"LogicalController.h"
#include	"ArcadeController.h"

//	->	Loading section.
#include	"Ld_SandTimer.h"
#include	"LoadingCenter.h"

//	->	Star Adventure
#include	"thyObject.h"
#include	"TheCandy.h"
#include	"BackGrounds.h"
#include	"VisualGridController.h"
#include	"thyGrid_Logic.h"
#include	"FancyLogo.h"
#include	"thyEffect.h"
#include	"Board.h"
#include	"AfterGlows.h"
#include	"TheSwitcher.h"
#include	"OnScreen.h"
#include	"Map.h"
#include	"LevelTransition.h"
#include	"LobbyController.h"

//	->	Friday Night Funkin'
#include	"FNF_Funking.h"


//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//			Commentary side.
//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
//	Class template:		"Switcher" was the first template.
//	
/*
class		UserIcon : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	UserIcon(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~UserIcon()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_SpritePosition(int What)
	{
		switch (What)
		{
		case	1:
			return		(this->xP + (this->_W_Sprite * 0.5));

		case	2:
			return		(this->yP - (this->_H_Sprite * 0.5));

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
/*	||	 ||
	||	 ||
	|| G ||
	|| O ||
	||	 ||
	|| T ||
	|| O ||
	||	 ||
	||	 ||	*/
/*
class		_Controller_User
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum	enm_Draw
	{

	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_User(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
	}

	~_Controller_User()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{

	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:

};
*/
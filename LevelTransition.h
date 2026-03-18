#pragma once

#include	"thyObject.h"
#include	"_MyIncludes_.h"
#include	"Tools_.h"
#include	"SpriteFactory.h"
#include	"DrawFactory.h"
#include	"BackGrounds.h"
#include	"_Basics_Button.h"
#include	"_Basics_Mouse.h"



class	_Controller_LevelTransition
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Variables
//	-------------------------------------------
private:
	int			Stt_ShowingAnimation = def::enm_Status::IsOn;

	double		m_TransitionTime	= 0.75;
	double		m_Time				= 0.0,		m_TimePoint		= 0.0;

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	_Basic_Mouse*			_Mouse_			= nullptr;
	_Basic_KeyBoard*		_KeyBoard_		= nullptr;
	SpriteFactory*			_Sprite_		= nullptr; 
	DrawFactory*			_Draw_			= nullptr;
	_Controller_Button*		_Buttons_		= nullptr; 





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_LevelTransition(	_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _KeyBoard_Ptr	, 
									SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr			,
									_Controller_Button*	_Button_Ptr								)
	{
		//	Link pointers.
		{
			this->_Mouse_		= _Mouse_Ptr;
			this->_KeyBoard_	= _KeyBoard_Ptr;
			this->_Sprite_		= _Sprite_Ptr;
			this->_Draw_		= _Draw_Ptr;
			this->_Buttons_		= _Button_Ptr;
		}
	}

	~_Controller_LevelTransition()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			LogicStuff()
	{
		//	Animation time.
		if (	this->Stt_ShowingAnimation == def::enm_Status::IsOn	)
		{
			if (	(this->m_Time - this->m_TimePoint) < this->m_TransitionTime		)
			{

			}
			else
			{
				//	Status changing.
				this->Stt_ShowingAnimation = def::enm_Status::IsDone;

				this->_Buttons_->ChangeRoom(	def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::Level, snd::MyPlayList::Unwind	);
				this->_Draw_->UseCamera(				drw::MyCamera::MainCamera					);
			}
		}
		else
		{
			//	Status changing.
			this->Stt_ShowingAnimation = def::enm_Status::IsOff;
		}

		//	Time passes too...
		this->m_Time = this->m_Time + (1.0 / GAME_LOOP_VALUE);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
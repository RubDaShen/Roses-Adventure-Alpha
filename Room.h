#pragma once
#include "_MyIncludes_.h"



class	Room
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	bool		m_RoomActive		= false;
	bool		m_IsOnTransition	= false;

	int			m_Command = -1;
	int			m_RoomID = -1;

	int			Cnt_Transition = 0,	Trg_Transition = 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//						Enums!
//	-------------------------------------------
public:
	enum	enm_Command
	{
		DeactivateRoom		= 0,
		ActivateRoom		= 1
	};

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Room(int _RoomID)
	{
		this->m_RoomID		= _RoomID;
	}

	~Room()
	{

	}

//	-------------------------------------------
//				Counters and all...
//	-------------------------------------------
public:
	inline void		SetRoomTransition(double _Time, int _Command)
	{
		this->m_IsOnTransition	= true;
		this->m_Command			= _Command;
		this->Cnt_Transition	= 0;
		this->Trg_Transition	= (GAME_LOOP_VALUE * _Time);
	}
	
//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		Transition()
	{
		if (	m_IsOnTransition	)
		{
			if (	this->Cnt_Transition < this->Trg_Transition)
			{
				++this->Cnt_Transition;
			}
			else
			{
				this->m_IsOnTransition	= false;
				this->Cnt_Transition	= 0;



				switch (	this->m_Command	)
				{
				case	Room::enm_Command::DeactivateRoom:
					this->m_RoomActive		= false;
					break;

				case	Room::enm_Command::ActivateRoom:
					this->m_RoomActive		= true;
					break;
				}
			}
		}
	}
	inline void		ResetStates()
	{
		this->m_RoomActive = false;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_RoomActive(bool _Val)
	{
		this->m_RoomActive		= _Val;
	}

	inline bool			g_RoomIsActive()
	{
		return		this->m_RoomActive;
	}
};
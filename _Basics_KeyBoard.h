#pragma once
#include	<vector>

#include	"_MyIncludes_.h"
#include	"thyObject.h"



namespace kyb
{
	enum Key
	{
		_Space_	,
		Enter	,


		D	,
		C	,
		F	,
		J	,
		K	,
		L	,
		P	,
		R	,
		T	,
		W	,


		Add			,
		Subtract	,
		Multiply	,
		Divide		,




		TotalKeys		
	};
}

class		_KeyBoard_KeyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_Key_ID = def::enm_Defines::_NOT_INITIALIZED;

	double		m_TimePressed = 0.0;

	int			Cnt_Release = 0, Trg_Release = 0;

	int			InstaPressedCounter = 0;

//	-------------------------------------------
//					Is
//	-------------------------------------------
private:
	bool		m_InstaPressed	= false;
	bool		m_IsPressed		= false;
	bool		m_IsReleased	= false;






//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_KeyBoard_KeyObject(int	_Key_ID)
	{
		this->m_Key_ID		= _Key_ID;
	}

	~_KeyBoard_KeyObject()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			KeepTrack()
	{
		//	Pressing event.
		if (	this->m_IsPressed	)
		{
			this->m_TimePressed		= this->m_TimePressed + (1.0 / GAME_LOOP_VALUE);

			//	About InstaPressed.
			{
				if (	this->InstaPressedCounter == 0	)
				{
					this->m_InstaPressed	= true;
				}
				else
				{
					this->m_InstaPressed		= false;
					this->InstaPressedCounter	= 0;
				}

				++InstaPressedCounter;
			}
		}
		else
		{
			this->m_TimePressed			= 0.0;

			this->m_InstaPressed		= false;
			this->InstaPressedCounter	= 0;
		}

		//	Release event.
		if (this->m_IsReleased)
		{
			if (this->Cnt_Release < this->Trg_Release)
			{
				++this->Cnt_Release;
			}
			else
			{
				this->Cnt_Release	= 0;
				this->m_IsReleased	= false;
				this->m_IsPressed	= false;
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_Is(int _What, bool _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_IsPressed		= _Val;
			break;

		case 2:
			this->m_IsReleased		= _Val;
			break;
		}
	}
	inline bool			g_Is(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_IsPressed;

		case 2:
			return		this->m_IsReleased;

		case 3:
			return		this->m_InstaPressed;
		}
	}

	inline double		g_PressedTime()
	{
		return		this->m_TimePressed;
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
class		_Basic_KeyBoard
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[0] Constants 
//	-------------------------------------------
private:

//	-------------------------------------------
//				[1] Containers
//	-------------------------------------------
private:
	std::vector<_KeyBoard_KeyObject*>		m_Keys;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Basic_KeyBoard()
	{
		//	When created, let's say to create all keys availables.
		{
			for (	int i = 0; 
					i < kyb::TotalKeys;
					++i	)
			{
				this->m_Keys.push_back(	new _KeyBoard_KeyObject(i)	);
			}
		}
	}
	 
	~_Basic_KeyBoard()
	{
		//	Deleting Keys !
		{
			while (!this->m_Keys.empty())
			{
				delete this->m_Keys[0];
				this->m_Keys.erase(this->m_Keys.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//			About states and related.
//	-------------------------------------------
public:
	inline void	UpdateStates()
	{
		for (	int i = 0; 
				i < kyb::TotalKeys;
				++i	)
		{
			this->m_Keys[i]->KeepTrack();
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline _KeyBoard_KeyObject*			g_Key(int _What)
	{
		return this->m_Keys[_What];
	}
};
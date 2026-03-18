#pragma once

#include	"_MyIncludes_.h"



class		thyGrid_Logic
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			 [0] Board Main Logic
//	-------------------------------------------
private:
	int			m_KindID = 0, m_ItemID = 0;
	int			m_CandyAt = 0;

	bool		m_CanMatch = true;
	bool		m_CanFall = true;

	bool		m_IsOff = false;
	bool		m_IsFalling = false;
	bool		m_IsBouncing = false;

	bool		m_HasABlocker = false;
	bool		m_HasSpawnBlocked = false;

	bool		m_IsDefinedFallingSide = false;

//	-------------------------------------------
//				[1] Gravity Stuff...
//	-------------------------------------------
private:
	int			m_GravityDirection = 1;

//	-------------------------------------------
//				[2] SideWays part...
//	-------------------------------------------
private:
	int			m_SideWayCandy_ID = 0;
	
//	-------------------------------------------
//				   [4] Counters
//	-------------------------------------------
private:
	int			Cnt_CanFall = 0, Trg_CanFall = 15;



	
	
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	thyGrid_Logic(int _GravityDirection)
	{
		this->m_GravityDirection = _GravityDirection;
	}

	~thyGrid_Logic()
	{

	}

//	-------------------------------------------
//			 [0] Board Main Logic
//	-------------------------------------------
public:
	inline void		UpdateStatus(int _KindID, int _ItemID, int _CandyAt, bool _CanMatch, bool _HasABlocker)
	{
		this->m_KindID		= _KindID;
		this->m_ItemID		= _ItemID;
		this->m_CandyAt		= _CandyAt;

		this->m_CanMatch	= _CanMatch;
		this->m_HasABlocker	= _HasABlocker;
	}
	inline void		ResetStatus()
	{
		this->m_KindID		= STA_::enm_KindID::_Invalid;
		this->m_ItemID		= STA_::enm_KindID::_Invalid;
		this->m_CandyAt		= def::enm_Defines::_NOT_FOUND;

		this->m_CanMatch			= false;
		this->m_HasSpawnBlocked		= false;
	}

	inline void		StartObjectCanFall()
	{
		if (!this->m_CanFall)
		{
			if (this->Cnt_CanFall < this->Trg_CanFall)
			{
				++this->Cnt_CanFall;
			}
			else
			{
				this->m_CanFall				= true;
				this->Cnt_CanFall			= 0;
			}
		}
	}


	inline void		s_KindID(int _Value)
	{
		this->m_KindID = _Value;
	}
	inline void		s_ItemID(int _Value)
	{
		this->m_ItemID = _Value;
	}
	inline void		s_CandyAt(int _Value)
	{
		this->m_CandyAt = _Value;
	}

	inline int		g_KindID()
	{
		return this->m_KindID;
	}
	inline int		g_ItemID()
	{
		return this->m_ItemID;
	}
	inline int		g_CandyAt()
	{
		return this->m_CandyAt;
	}

	inline void		s_Is(	int What, bool Value	)
	{
		switch (	What	)
		{
		case	1:
			this->m_IsDefinedFallingSide = Value;
		}
	}
	inline void		s_Can(int _What, bool _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_CanFall		= _Val;
			return;

		case 2:
			this->m_CanMatch	= _Val;
			return;
		}
	}
	inline void		s_Has(int _What, bool _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_HasABlocker = _Val;

		case 2:
			this->m_HasSpawnBlocked = _Val;
		}
	}

	inline bool		g_Is(int _What)
	{
		switch (_What)
		{
		case	1:
			return		this->m_IsOff;

		case	2:
			return		this->m_IsFalling;

		case	3:
			return		this->m_IsBouncing;

		case	4:
			return		this->m_IsDefinedFallingSide;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline bool		g_Can(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_CanFall;

		case 2:
			return		this->m_CanMatch;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

//	-------------------------------------------
//				[1] Gravity Stuff...
//	-------------------------------------------4
public:
	inline void		s_GravityDirection(int _Which, int _Value)
	{
		switch (_Which)
		{
		case 1:
			this->m_GravityDirection = _Value;
		}
	}
	inline int		g_GravityDirection(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_GravityDirection;

		default:
			return -1;
		}
	}

//	-------------------------------------------
//				[2] SideWays part...
//	-------------------------------------------
public:
	inline bool		g_Has(int _What)
	{
		switch (_What)
		{
		case	1:
			return		this->m_HasABlocker;

		case	2:
			return		this->m_HasSpawnBlocked;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	inline void		s_SideWaysID(	int Value	)
	{
		this->m_SideWayCandy_ID = Value;
	}
	inline int		g_SideWaysID()
	{
		return		this->m_SideWayCandy_ID;
	}
};
#pragma once

#include		"_MyIncludes_.h"
#include		"thyObject.h"
#include		"Camera.h"



class	_Basic_Mouse
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Positions
//	-------------------------------------------
private:
	int			m_xP_OnWindow = 0,		m_yP_OnWindow = 0;

	double		m_xP_Move = 0.0,		m_yP_Move = 0.0;
	double		m_xP_Pressed = 0.0,		m_yP_Pressed = 0.0;
	double		m_xP_Released = 0.0,	m_yP_Released = 0.0;
	double		m_xP_PressedPreviosly = 0.0, m_yP_PressedPreviosly = 0.0;

	double		m_W = 0.0, m_H = 0.0;

//	-------------------------------------------
//						Is
//	-------------------------------------------
private:
	bool		m_IsPressed				= false;
	bool		m_IsReleased			= false;
	bool		m_IsSinglePressed		= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Basic_Mouse()
	{
		this->m_W = this->m_H = 1;
	}
	 
	~_Basic_Mouse()
	{

	}

//	-------------------------------------------
//			About states and related.
//	-------------------------------------------
public:
	inline void		ResetStates()
	{
		this->m_IsReleased		= false;
		this->m_IsSinglePressed = false;
	}

//	-------------------------------------------
//					Operators
//	-------------------------------------------
public:
	inline void		operator=(_Basic_Mouse* _OtherMouse)
	{
		//	Here goes the position.
		{
			//	All about moving positions.
			{
				this->m_xP_Move = _OtherMouse->g_Position(1, 1);
				this->m_yP_Move = _OtherMouse->g_Position(1, 2);
			}

			//	All about moving positions.
			{
				this->m_xP_Pressed = _OtherMouse->g_Position(2, 1);
				this->m_yP_Pressed = _OtherMouse->g_Position(2, 2);
			}

			//	All about moving positions.
			{
				this->m_xP_Released = _OtherMouse->g_Position(3, 1);
				this->m_yP_Released = _OtherMouse->g_Position(3, 2);
			}
		}

		this->m_IsPressed = _OtherMouse->g_Is(1);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_Position(int _WhichKind, int _What, double _Val)
	{
		switch (_WhichKind)
		{
		case 0:
			switch (_What)
			{
			case 1:
				this->m_xP_OnWindow		= _Val;
				break;

			case 2:
				this->m_yP_OnWindow		= _Val;
				break;
			}
			break;

		case 1:
			switch (_What)
			{
			case 1:
				this->m_xP_Move = _Val;
				break;

			case 2:
				this->m_yP_Move = _Val;
				break;
			}
			break;

		case 2:
			switch (_What)
			{
			case 1:
				this->m_xP_Pressed = _Val;
				break;

			case 2:
				this->m_yP_Pressed = _Val;
				break;
			}
			break;

		case 3:
			switch (_What)
			{
			case 1:
				this->m_xP_Released = _Val;
				break;

			case 2:
				this->m_yP_Released = _Val;
				break;
			}
			break;

		case 4:
			switch (_What)
			{
			case 1:
				this->m_xP_PressedPreviosly = _Val;
				break;

			case 2:
				this->m_yP_PressedPreviosly = _Val;
				break;
			}
			break;
		}
	}
	inline void			s_Measures(int _What, double _Val)
	{
		switch (_What)
		{
		case 1: 
			this->m_W = _Val;
			break;

		case 2:
			this->m_H = _Val;
			break;
		}
	}
	inline void			s_Is(int _What, bool _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_IsPressed			= _Val;
			break;

		case 2:
			this->m_IsReleased			= _Val;
			break;

		case 3:
			this->m_IsSinglePressed		= _Val;
			break;
		}
	}

	inline double		g_Position(int _WhichKind, int _What)
	{
		switch (_WhichKind)
		{
		case 0:
			switch (_What)
			{
			case 1:
				return		this->m_xP_OnWindow;

			case 2:
				return		this->m_yP_OnWindow;
			}
			break;

		case 1:
			switch (_What)
			{
			case 1:
				return this->m_xP_Move;

			case 2:
				return this->m_yP_Move;
			}
			break;

		case 2:
			switch (_What)
			{
			case 1:
				return this->m_xP_Pressed;

			case 2:
				return this->m_yP_Pressed;
			}
			break;

		case 3:
			switch (_What)
			{
			case 1:
				return this->m_xP_Released;

			case 2:
				return this->m_yP_Released;
			}
			break;

		case 4:
			switch (_What)
			{
			case 1:
				return this->m_xP_PressedPreviosly;

			case 2:
				return this->m_yP_PressedPreviosly;
			}
			break;
		}
	}
	inline double		g_Position_Camera(int _WhichKind, int _What, Camera* _Camera)
	{
		switch (_WhichKind)
		{
		case 1:
			switch (_What)
			{
			case 1:
				return		(_Camera->g_Center(1) + _Camera->g_Position(1)) - (((_Camera->g_Center(1) + _Camera->g_Position(1)) - (this->m_xP_Move + _Camera->g_Position(1))) * _Camera->g_ZoomFactor());

			case 2:
				return		(_Camera->g_Center(2) + _Camera->g_Position(2)) - (((_Camera->g_Center(2) + _Camera->g_Position(2)) - (this->m_yP_Move + _Camera->g_Position(2))) * _Camera->g_ZoomFactor());
			}
			break;

		case 2:
			switch (_What)
			{
			case 1:
				return		(_Camera->g_Center(1) + _Camera->g_Position(1)) - (((_Camera->g_Center(1) + _Camera->g_Position(1)) - (this->m_xP_Pressed + _Camera->g_Position(1))) * _Camera->g_ZoomFactor());

			case 2:
				return		(_Camera->g_Center(2) + _Camera->g_Position(2)) - (((_Camera->g_Center(2) + _Camera->g_Position(2)) - (this->m_yP_Pressed + _Camera->g_Position(2))) * _Camera->g_ZoomFactor());
			}
			break;

		case 3:
			switch (_What)
			{
			case 1:
				return		(_Camera->g_Center(1) + _Camera->g_Position(1)) - (((_Camera->g_Center(1) + _Camera->g_Position(1)) - (this->m_xP_Released + _Camera->g_Position(1))) * _Camera->g_ZoomFactor());

			case 2:
				return		(_Camera->g_Center(2) + _Camera->g_Position(2)) - (((_Camera->g_Center(2) + _Camera->g_Position(2)) - (this->m_yP_Released + _Camera->g_Position(2))) * _Camera->g_ZoomFactor());
			}
			break;

		case 4:
			switch (_What)
			{
			case 1:
				return		(_Camera->g_Center(1) + _Camera->g_Position(1)) - (((_Camera->g_Center(1) + _Camera->g_Position(1)) - (this->m_xP_PressedPreviosly + _Camera->g_Position(1))) * _Camera->g_ZoomFactor());

			case 2:
				return		(_Camera->g_Center(2) + _Camera->g_Position(2)) - (((_Camera->g_Center(2) + _Camera->g_Position(2)) - (this->m_yP_PressedPreviosly + _Camera->g_Position(2))) * _Camera->g_ZoomFactor());
			}
			break;
		}
	}
	inline double		g_Measures(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_W;

		case 2:
			return this->m_H;

		default:
			return def::enm_Defines::_NOT_FOUND;
		}
	}
	inline bool			g_Is(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_IsPressed;

		case 2:
			return this->m_IsReleased;

		case 3:
			return this->m_IsSinglePressed;

		default:
			return def::enm_Defines::_NOT_FOUND;
		}
	}
};
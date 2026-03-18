#pragma once

#include	"thyObject.h"
#include	"Tools_.h"
#include	"DrawFactory.h"
#include	"SpriteFactory.h"
#include	"_MyIncludes_.h"



//	Not Finished Yet
//	But I think I will use it in the future.
//	Under construction.



class		Rectbord : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		m_BorderRadious			= 0.0;
	int			m_OutlineThickness		= 5;



//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Rectbord(double _xP, double _yP, double _BorderRadious) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_BorderRadious		= _BorderRadious;
	}

	~Rectbord()
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
	inline double		g_BorderRadious()
	{
		return		this->m_BorderRadious;
	}
	inline int			g_OutlineThickness()
	{
		return		this->m_OutlineThickness;
	}
};
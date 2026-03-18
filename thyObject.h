/*
	thyObject >> " Created by Ruben Mallma Quispe E. :D - version of header -> 1.4 - // 4 - 03 - 2023 \\. ".
		Working with 'HitBox.h' -> Under construction!


	Abreviations:
		s		set
		g		get
		f		factor
		cfg		configuration
		pos		position
		prp		properties
		col		color
		FS		fastStart
		xFct	xFct
		yFct	yFct
*/

#pragma once

#include		<iostream>
#include		"_MyIncludes_.h"




class		thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						Protected side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
protected:
	double		xP = 0.0, yP = 0.0, zP = 0.0;											//	Real position, not in the window display.
	double		xS = 0.0, yS = 0.0, zS = 0.0;											//	Movement, speed. How fast the object moves.
	double		xA = 0.0, yA = 0.0, zA = 0.0;											//	Aceleration of the movement.
	double		xD = 0.0, yD = 0.0, zD = 0.0;											//	Rate of change of the aceleration. Double derivative of speed.

	double		rotationDegree = 0.0;													//	To rotate the object.
	double		rotationSpeed = 0.0, rotationAceleration = 0.0;							//	Like Dpz and Acl.

	double		_W = 0.0, _H = 0.0, _D = 0.0;											//	Real width and height of an object. Useful for hitbox.
	double		_r = 0.0;																//	Radious.

	double		R_col = 255.0, G_col = 255.0, B_col = 255.0, A_alpha = 255.0;			//	RGB and Alpha channel.
	double		Col_s = 0.0, Alpha_s = 0.0;												//	Speed? No idea...
	double		Col_a = 0.0, Alpha_a = 0.0;												//	And aceleration too!

	double		xFct = 1.0, yFct = 1.0;													//	Use it to resize (bigger or smaller).
	double		xFctS = 0.0, yFctS = 0.0;												//	A speed like always.
	double		xFctA = 0.0, yFctA = 0.0;												//	Aceleration itself ~

	int			ObjectID = 0;															//	ID <as an ID card> of the object.
	double		ObjectHitPoints = 0;													//	You can understand this as hp or L I F E .
	int			ObjectType = 0;															//	Represents what type of object is this instance.

	int			_W_Sprite = 0, _H_Sprite = 0;											//	Measures of the sprite; don't use this as real measures (HitBox).

//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	thyObject()
	{

	}
	thyObject(double _xPos, double _yPos, int _ObjectType)
	{
		this->xP = _xPos;
		this->yP = _yPos;

		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / //

		this->R_col = this->G_col = this->B_col = this->A_alpha = 255;
		this->ObjectType = _ObjectType;
	}
	thyObject(double _xPos, double _yPos, double _zPos)
	{
		this->xP = _xPos;
		this->yP = _yPos;
		this->zP = _zPos;

		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / //

		this->R_col = this->G_col = this->B_col = this->A_alpha = 255;
	}

	virtual ~thyObject()
	{
		//	Debugging methods:
		//	std::cout << this << " -> ID =" << this->ObjectID << ", Type=" << this->ObjectType << "\n";

		this->ObjectID		= def::enm_Defines::_NOT_INITIALIZED;
	}

//	-------------------------------------------
//				Setters and getters
//	-------------------------------------------
public:
	//	Set any parameter related to position like position, speed, aceleration, etc.
	inline void					s_PositionPrp(int What, double Value)				
	{
		switch (	What	)
		{
		case 1:
			this->xP	= Value;
			break;
	
		case 2:
			this->yP	= Value;
			break;
	
		case 3:
			this->xS	= Value;
			break;
	
		case 4:
			this->yS	= Value;
			break;
	
		case 5:
			this->xA	= Value;
			break;
	
		case 6:
			this->yA	= Value;
			break;
	
		case 7:
			this->xD	= Value;
			break;
	
		case 8:
			this->yD	= Value;
			break;
	
		case 9:
			this->zP	= Value;
			break;
	
		case 10:
			this->zS	= Value;
			break;
	
		case 11:
			this->zA	= Value;
			break;
	
		case 12:
			this->zD	= Value;
			break;
		}
	}
	
	//	Set any parameter related to rotation such as rotationDegree, rotationSpeed, rotationAceleration.
	inline void					s_RotationPrp(int What, double Value)
	{
		switch (	What	)
		{
		case 1:
			this->rotationDegree		= Value;
			break;

		case 2:
			this->rotationSpeed			= Value;
			break;

		case 3:
			this->rotationAceleration	= Value;
			break;
		}
	}

	//	Set the width and height. These are related for collision, not for texture.
	inline void					s_MeasuresPrp(int What, double Value)
	{
		switch (	What	)
		{
		case 1:
			this->_W	= Value;
			break;

		case 2:
			this->_H	= Value;
			break;

		case 3:
			this->_r	= Value;
			break;

		case 4:
			this->_D	= Value;
			break;
		}
	}

	//	Set any parameter related to color properties such RGBA, fading, etc.
	inline void					s_ColorPrp(int What, double Value)
	{
		switch (	What	)
		{
		case 1:
			this->R_col		= Value;
			break;

		case 2:
			this->G_col		= Value;
			break;

		case 3:
			this->B_col		= Value;
			break;

		case 4:
			this->A_alpha	= Value;
			break;

		case 5:
			this->Col_s		= Value;
			break;

		case 6:
			this->Alpha_s	= Value;
			break;

		case 7:
			this->Col_a		= Value;
			break;

		case 8:
			this->Alpha_a	= Value;
			break;
		}
	}

	//	Set any parameter related to visual (visual stands for the texture of the object).
	inline void					s_VisualPrp(int What, double Value)
	{
		switch (	What	)
		{
		case 1:
			this->xFct	= Value;
			break;

		case 2:
			this->yFct	= Value;
			break;

		case 3:
			this->xFctS = Value;
			break;

		case 4:
			this->yFctS = Value;
			break;

		case 5:
			this->xFctA = Value;
			break;

		case 6:
			this->yFctA = Value;
			break;
		}
	}

	//	Set ObjectID.
	inline void					s_ObjectID(int Value)
	{
		this->ObjectID = Value;
	}

	//	Set the measures of the sprite.
	inline void					s_SpriteMeasures(int WhatMeasure, int Value)
	{
		switch (	WhatMeasure	)
		{
		case	1:
			this->_W_Sprite			= Value;

		case	2:
			this->_H_Sprite			= Value;
		}
	}



	//	Get any parameter related to position like position, speed, aceleration, etc.
	inline double				g_PositionPrp(int What) const
	{
		switch (	What	)
		{
		case 1:
			return this->xP;

		case 2:
			return this->yP;

		case 3:
			return this->xS;

		case 4:
			return this->yS;

		case 5:
			return this->xA;

		case 6:
			return this->yA;

		case 7:
			return this->xD;

		case 8:
			return this->yD;

		case 9:
			return this->zP;

		case 10:
			return this->zS;

		case 11:
			return this->zA;

		case 12:
			return this->zD;
		}
	}

	//	Get any parameter related to rotation such as rotationDegree, rotationSpeed, rotationAceleration.
	inline double				g_RotationPrp(int What) const
	{
		switch (	What	)
		{
		case 1:
			return	this->rotationDegree;

		case 2:
			return	this->rotationSpeed;

		case 3:
			return	this->rotationAceleration;
		}
	}

	//	Get the width and height. These are related for collision, not for texture.
	inline double				g_MeasuresPrp(int What) const
	{
		switch (	What	)
		{
		case 1:
			return	this->_W;

		case 2:
			return	this->_H;

		case 3:
			return	this->_r;

		case 4:
			return	this->_D;
		}
	}

	//	Get any parameter related to color properties such RGBA, fading, etc.
	inline double				g_ColorPrp(int What) const
	{
		switch (	What	)
		{
		case 1:
			return	this->R_col;

		case 2:
			return	this->G_col;

		case 3:
			return	this->B_col;

		case 4:
			return	this->A_alpha;

		case 5:
			return	this->Col_s;

		case 6:
			return	this->Alpha_s;

		case 7:
			return	this->Col_a;

		case 8:
			return	this->Alpha_a;
		}
	}

	//	Get any parameter related to visual (visual stands for the texture of the object).
	inline double				g_VisualPrp(int What) const
	{
		switch (	What	)
		{
		case 1:
			return	this->xFct;

		case 2:
			return	this->yFct;

		case 3:
			return	this->xFctS;

		case 4:
			return	this->yFctS;

		case 5:
			return	this->xFctA;

		case 6:
			return	this->yFctA;
		}
	}

	//	Get ObjectID.
	inline int					g_ObjectID() const
	{
		return		this->ObjectID;
	}

	//	Get the measure of the sprite.
	inline int					g_SpriteMeasures(int WhatMeasure)
	{
		switch (WhatMeasure)
		{
		case	1:
			return		this->_W_Sprite;

		case	2:
			return		this->_H_Sprite;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
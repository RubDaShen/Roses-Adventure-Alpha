#pragma once

#include	"Tools_.h"
#include	"_MyIncludes_.h"



struct		CameraTrigger
{
//	-------------------------------------------
//					Variables
//	-------------------------------------------
	int			EventType	= def::enm_Defines::_NOT_INITIALIZED;
	int			_When_		= 0;

	double		Value1		= 0.0;
	double		Value2		= 0.0;
	double		Value3		= 0.0;





//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
	CameraTrigger(int _EventType, int _When, double _Value1, double _Value2)
	{
		this->EventType		= _EventType;
		this->_When_		= _When;

		this->Value1		= _Value1;
		this->Value2		= _Value2;
	}
	CameraTrigger(int _EventType, int _When, double _Value1, double _Value2, double _Value3)
	{
		this->EventType		= _EventType;
		this->_When_		= _When;

		this->Value1		= _Value1;
		this->Value2		= _Value2;
		this->Value3		= _Value3;
	}

	~CameraTrigger()
	{

	}
};

class		Camera
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Actual variables
//	-------------------------------------------
private:
	int				m_xMoveEffectID	= 0;
	int				m_yMoveEffectID = 0;
	int				m_ZoomEffectID	= 0;

	int				m_ZoomCap_InnerTime		= 0;
	int				m_Zoom_InnerTime		= 0;
	int				m_xMove_InnerTime		= 0;
	int				m_yMove_InnerTime		= 0;

//	-------------------------------------------
//				Position Variables
//	-------------------------------------------
private:
	double			xP = 0.0, yP = 0.0;		
	double			Width = 0.0, Height = 0.0;

	double			xMoveTo = 0.0, xMoveSmoothTime = 0.0;
	double			yMoveTo = 0.0, yMoveSmoothTime = 0.0;

//	-------------------------------------------
//				Zooming-variables
//	-------------------------------------------
private:
	double			xCenter = 0.0, yCenter = 0.0;
	double			ZoomFactor = 1.0;

	double			ZoomFrom = 0.0, ZoomTo = 0.0, ZoomSmoothTime = 0.0;

	double			ZoomCap = 1.0, ZoomCapTo = 1.0, ZoomCapTime = 1.0;

	



//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Camera(double _xCenter, double _yCenter, double _Width, double _Height)
	{
		this->xCenter		= _xCenter;
		this->yCenter		= _yCenter;
		this->Width			= _Width;
		this->Height		= _Height;
	}

	~Camera()
	{

	}

//	-------------------------------------------
//				Pre-set functions
//	-------------------------------------------
public:
	//	- - - - - - - - - - - - - - - - - -
	//				Position :D
	//	- - - - - - - - - - - - - - - - - -	

	//	Just adds a value to the current camera position.
	inline void			Move(double _xP, double _yP)
	{
		this->xP		= this->xP + _xP;
		this->yP		= this->yP + _yP;
	}

	//	Easy to understand, but the _What value is which axis is to be affected.
	//	1 for 'x' axis, 2 for 'y' axis.
	//	If your argument is 1, 100, 1.0 means that 100 will be added
	//	to the current 'x' axis position in 1.0 second(s).
	inline void			SmoothMove(int _What, double _Amount, double _Time)
	{
		switch (_What)
		{
		case		def::enm_CameraSet::xSmoothMove:
			this->m_xMoveEffectID	= def::enm_CameraSet::xSmoothMove;

			this->xMoveTo			= this->xP + _Amount;
			this->xMoveSmoothTime	= _Time * GAME_LOOP_VALUE;
			
			this->m_xMove_InnerTime	= 0;

			break;

		case		def::enm_CameraSet::ySmoothMove:
			break;
		}
	}




	//	- - - - - - - - - - - - - - - - - -
	//				Zoom :D
	//	- - - - - - - - - - - - - - - - - -	
	
	//	Adds a value to the current zoom factor.
	inline void			Zoom(double _Zoom)
	{
		this->ZoomFactor = this->ZoomFactor + _Zoom;
	}

	//	From a given value (say 1.5 or 0.5) goes 
	//	up/down to a certain value.
	inline void			SmoothZoom(double _From, double _To, double _Time)
	{
		this->m_ZoomEffectID	= def::enm_CameraSet::SmoothZoom;
		this->ZoomFactor		= _From;

		this->ZoomFrom			= _From;
		this->ZoomTo			= _To;
		this->ZoomSmoothTime	= _Time * GAME_LOOP_VALUE;
		
		this->m_Zoom_InnerTime	= 0;
	}

	//	ZoomFocus focus :v at a certain factor value, say 0.85 meaning
	//	that all normal zooming functions will be 0.85
	inline void			ZoomFocus(double _Amount, double _Time)
	{
		this->ZoomCapTo		= _Amount;
		this->ZoomCapTime	= _Time;
	}

//	-------------------------------------------
//				Running functions
//	-------------------------------------------
public:
	inline void			Action()
	{
		//	Zoom cap is a special one.
		{
			//	Here is the zoom cap.
			this->ZoomCap = tls::SmoothMove(this->ZoomCap, this->ZoomCapTo, this->ZoomCapTime * GAME_LOOP_VALUE);
		}

		//	About all zoom effects.
		switch (this->m_ZoomEffectID)
		{
		case	def::enm_CameraSet::SmoothZoom:
			//	Here is the smooth movement.
			this->ZoomFactor = tls::SmoothMove(this->ZoomFactor, this->ZoomTo, this->ZoomSmoothTime);

			//	Then, when time is up make it stop and receive the set value.
			{
				if (this->m_Zoom_InnerTime > this->ZoomSmoothTime)
				{
					this->m_ZoomEffectID	= 0;
					this->ZoomFactor		= this->ZoomTo;					
				}			
			}

			break;
		}


		//	About all 'x' axis move effects.
		switch (this->m_xMoveEffectID)
		{
		case	def::enm_CameraSet::xSmoothMove:
			//	Here is the smooth movement.
			this->xP = tls::SmoothMove(this->xP, this->xMoveTo, this->xMoveSmoothTime);

			//	Then, when time is up make it stop and receive the set value.
			{
				if (this->m_xMove_InnerTime > this->xMoveSmoothTime)
				{
					this->m_xMoveEffectID		= 0;
					this->m_xMove_InnerTime		= this->ZoomTo;
				}			
			}

			break;
		}



		++this->m_ZoomCap_InnerTime;
		++this->m_Zoom_InnerTime;
		++this->m_xMove_InnerTime;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double			g_Position(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP;

		case 2:
			return		this->yP;
		}
	}
	inline double			g_Measures(int What)
	{
		switch (What)
		{
		case 1:
			return		this->Width;

		case 2:
			return		this->Height;
		}
	}
	inline double			g_ZoomFactor()
	{
		return		(this->ZoomFactor + this->ZoomCap - 1.0);
	}
	inline double			g_Center(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xCenter;

		case 2:
			return		this->yCenter;
		}
	}
	inline double			g_Bounds(int What)
	{
		//	Bounds is affected by the center.
		//	These operations kinda looks like:
		//	tls::TransformPos_X and tls::TransformPos_Y

		switch (	What	)
		{
		case	def::enm_CameraLimits::LeftBorder:
			return		(this->xP - this->g_Center(1));

		case	def::enm_CameraLimits::RightBorder:
			return		(this->xP + this->Width - this->g_Center(1));

		case	def::enm_CameraLimits::Cieling:
			return		(this->yP + this->g_Center(2));

		case	def::enm_CameraLimits::Floor:
			return		(this->yP - this->Height + this->g_Center(2));
		}
	}
};
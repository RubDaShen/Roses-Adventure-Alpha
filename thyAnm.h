#pragma once



class		thyAnm
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums
//	-------------------------------------------
public:
	enum	AnmPrp
	{
		_AnmStage	= 1	,
		_AnmState		,
		_AnmDelay		,
		_xIndex			,
		_yIndex
	};

	enum	TexturePrp
	{
		_xFS	= 1	,
		_yFS		,
		__widthFS	,
		__heightFS	,
		_FrameX		,
		_FrameY
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Protected side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
public:
	int				AnmStage = 0, AnmState = 0;
	int				AnmDelay = 0;
	int				xIndex = 0, yIndex = 0;

	double			xFS = 0, yFS = 0;					//	Position of the image / bitmap / texture to use.
	double			_widthFS = 0, _heightFS = 0;		//	Length of the rectangle to use from an image / a bitmap / texture.
	double			FrameX = 0, FrameY = 0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	thyAnm()
	{

	}
	virtual ~thyAnm()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline virtual void			s_AnmState(int)
	{

	}


	inline void			s_AnmPrp(int _ElmVal, int _Val)
	{
		switch (	_ElmVal	)
		{
		case	_AnmStage:
			this->AnmStage	 = _Val;
			break;

		case	_AnmState:
			this->AnmState	= _Val;
			break;

		case	_AnmDelay:
			this->AnmDelay	= _Val;
			break;

		case	_xIndex:
			this->xIndex	= _Val;
			break;

		case	_yIndex:
			this->yIndex	= _Val;
			break;
		}
	}
	inline void			s_TexturePrp(int _ElmVal, double _Val)
	{
		switch (	_ElmVal	)
		{
		case	_xFS:
			this->xFS		= _Val;
			break;

		case	_yFS:
			this->yFS		= _Val;
			break;

		case	__widthFS:
			this->_widthFS	= _Val;
			break;

		case	__heightFS:
			this->_heightFS	= _Val;
			break;

		case	_FrameX:
			this->FrameX	= _Val;
			break;

		case	_FrameY:
			this->FrameY	= _Val;
			break;
		}
	}

	inline int			g_AnmPrp(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	_AnmStage:
			return	this->AnmStage;

		case	_AnmState:
			return	this->AnmState;

		case	_AnmDelay:
			return	this->AnmDelay;

		case	_xIndex:
			return	this->xIndex;

		case	_yIndex:
			return	this->yIndex;
		}
	}
	inline double		g_TexturePrp(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	_xFS:
			return	this->xFS;

		case	_yFS:
			return	this->yFS;

		case	__widthFS:
			return	this->_widthFS;

		case	__heightFS:
			return	this->_heightFS;

		case	_FrameX:
			return	this->FrameX;

		case	_FrameY:
			return	this->FrameY;
		}
	}
};
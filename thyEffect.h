#pragma once

#include		"LogicalController.h"

/*
	Abreviations:
		FIn		FadeIn
		FOu		FadeOut
		FIO		FadeInAndOut

		Ini		Initialize (First time)
*/



class		thyEffect
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	enum	FIn_
	{
		_Alpha_FIn	= 1	,
		_Speed_FIn		,
	};

	enum	FOu_
	{
		_Alpha_FOu_ = 1	,
		_Speed_FOu_		,
	};

	enum	FLp_
	{
		_FLp_A = 1
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:






//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Protected side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
protected:
	//	-> FadeIn Vars.
	bool		FIn_Run = false;

	double		FIn_A = 0, FIn_S = 0;
	double		FIn_A_Trg = 0;
	double		FIn_Tm = 0;

	//	-> FadeOut Vars.
	bool		FOu_Run = false;

	double		FOu_A = 0, FOu_S = 0;
	double		FOu_A_Trg = 0;
	double		FOu_Tm = 0;

	//	-> FadeIO Vars.
	bool		FIO_Run = false;
	bool		FIO_Inv = false;
	bool		FIO_End = false;

	double		FIO_A = 0, FIO_S = 0;
	double		FIO_Ato = 0, FIO_Adown = 0;
	double		FIO_Sin = 0, FIO_Sout = 0;

	//	-> Rainbow Vars.
	int			Itr_Rainbow = 0;

	double		R = 0, G = 0, B = 0;
	double		ColS = 0;

	//	-> FadeLoop Vars.
	bool		FLp_Run = false;

	double		FLp_A = 0, FLp_S = 0;
	double		FLp_From = 0, FLp_To = 0;

	//	-> Spin Vars.
	bool		Spn_Run = 0;

	double		Spn_Dgr = 0, Spn_S = 0;
	bool		Spn_Dir = false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	thyEffect()
	{

	}

	~thyEffect()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	//	Remember::..
	//	That the time is given in seconds.
	//	That's why is double (could use float tho ;-;).

	inline void			Ini_FadeIn(double _InitialVal, double _UpTo, double _Time_InSec)
	{
		this->FIn_A_Trg		= ((_UpTo <= 255) ? _UpTo : 255);
	
		this->FIn_A			= 0, this->FIn_S = (_UpTo - _InitialVal) / (_Time_InSec * GAME_LOOP_VALUE);
		this->FIn_Run		= true;
	}
	inline void			FadeIn()
	{
		if (	this->FIn_Run	)
		{
			if (	(this->FIn_A + this->FIn_S) < this->FIn_A_Trg	)
			{
				this->FIn_A		= this->FIn_A + this->FIn_S;
			}
			else
			{
				this->FIn_A		= this->FIn_A_Trg;
				this->FIn_Run	= false;
			}
		}
	}

	inline void			Ini_FadeOut(double _InitialVal, double _DownTo, double _Time_InSec)
	{
		this->FOu_A_Trg		= ((_DownTo >= 0) ? _DownTo : 0);
	
		this->FOu_A = 0, this->FIn_S = (_InitialVal - _DownTo) / (_Time_InSec * _Controller_Logic::_ogLpV_);
		this->FOu_Run		= true;
	}
	inline void			FadeOut()
	{
		if (	this->FOu_Run	)
		{
			if (	(this->FOu_A - this->FOu_S) > this->FOu_A_Trg	)
			{
				this->FOu_A		= this->FOu_A - this->FOu_S;
			}
			else
			{
				this->FOu_A		= this->FOu_A_Trg;
				this->FOu_Run	= false;
			}
		}
	}

	inline void			Ini_FadeInOut(double _FromAlpha, double _ToAlpha, double _DownToAlpha, double _TimeIn, double _TimeOut)
	{
		//	_FromAlpha is like: I want to start from 0 (Alpha) to
		//	_ToAlpha with a value of 150, when I reach the value 
		//	I go down to _DownToAlpha with a value of 50.
		//	_FromAlpha = 0, _ToAlpha = 255, _DownToAlpha = 0;
		//	
		//	_TimeIn and _TimeOut are measured in seconds.
		//	From _FromAlpha to _ToAlpha will be a lap of 2 seconds : _TimeIn = 2
		//	Down from _ToAlpha to _DownToAlpha will be a lap of 1 second : _TimeOut = 1
		//
		//	Working on a function that uses a cuadratic, or a function that acts as a
		//	paraboloid to rise and then fall.
	
		this->FIO_A		= _FromAlpha;
		this->FIO_Ato	= _ToAlpha;
		this->FIO_Adown = _DownToAlpha;
	
		this->FIO_Sin	= (_ToAlpha - _FromAlpha) / (_TimeIn * _Controller_Logic::_ogLpV_);
		this->FIO_Sout	= (_DownToAlpha - _ToAlpha) / (_TimeOut * _Controller_Logic::_ogLpV_);
	
		this->FIO_Run	= true;
		this->FIO_Inv	= false;
	}
	inline void			FadeIO()
	{
		if (	this->FIO_Run	)
		{
			this->FIO_End	= false;



			//	Rise part.
			if (!this->FIO_Inv)
			{
				if (	(this->FIO_A + this->FIO_Sin) < this->FIO_Ato	)
				{
					this->FIO_A		= this->FIO_A + this->FIO_Sin;
				}
				else
				{
					this->FIO_A		= this->FIO_Ato;
					this->FIO_Inv	= true;
				}

			}
			//	Fall part.
			else
			{
				if (	(this->FIO_A + this->FIO_Sout) > this->FIO_Adown	)
				{
					this->FIO_A		= this->FIO_A + this->FIO_Sout;
				}
				else
				{
					this->FIO_A		= this->FIO_Adown;
					this->FIO_Run	= false;
					this->FIO_End	= true;
				}
			}
		}
	}

	inline void			Rainbow(bool _Active)
	{
		if (	_Active		)
		{
			switch (	this->Itr_Rainbow	)
			{
			case	0:
				if (	(this->G + this->ColS) < 255	)
				{
					this->G		= this->G + this->ColS;
				}
				else
				{
					this->G		= 255;
					this->Itr_Rainbow++;
				}
				break;

			case	1:
				if (	(this->R - this->ColS) > 0	)
				{
					this->R		= this->R - this->ColS;
				}
				else
				{
					this->R		= 0;
					this->Itr_Rainbow++;
				}
				break;

			case	2:
				if (	(this->B + this->ColS) < 255	)
				{
					this->B		= this->B + this->ColS;
				}
				else
				{
					this->B		= 255;
					this->Itr_Rainbow++;
				}
				break;

			case	3:
				if (	(this->G - this->ColS) > 0	)
				{
					this->G		= this->G - this->ColS;
				}
				else
				{
					this->G		= 0;
					this->Itr_Rainbow++;
				}
				break;

			case	4:
				if (	(this->R + this->ColS) < 255	)
				{
					this->R		= this->R + this->ColS;
				}
				else
				{
					this->R		= 255;
					this->Itr_Rainbow++;
				}
				break;

			case	5:
				if (	(this->B - this->ColS) > 0	)
				{
					this->B =	this->B - this->ColS;
				}
				else
				{
					this->B		= 0;
					this->Itr_Rainbow = 0;
				}
				break;
			}
		}
	}

	inline void			Ini_FadeLoop(double _From, double _To, double _Time_InSec)
	{
		this->FLp_From	= _From;
		this->FLp_To	= _To;

		this->FLp_S		= std::fabs(this->FLp_From - this->FLp_To) / (_Time_InSec * GAME_LOOP_LOGIC);
		this->FLp_Run	= true;
	}
	inline void			FadeLoop()
	{
		if (	this->FLp_Run	)
		{
			this->FLp_A		= this->FLp_A + this->FLp_S;

			if (	this->FLp_A >= this->FLp_To	)
			{
				this->FLp_A		= this->FLp_To;
			}
			if (this->FLp_A <= this->FLp_From)
			{
				this->FLp_A		= this->FLp_From;
			}
			if (	(this->FLp_A <= this->FLp_From) ||
					(this->FLp_A >= this->FLp_To)	)
			{
				this->FLp_S		= this->FLp_S * -1;
			}
				
		}
	}

	//	Start a spinning effect (as loop).
	//	_Speed : Pretty obvious.
	//	_Dir :	 0 for left, and 1 for right.
	inline void			Ini_SpnLoop(double _Speed, bool _Dir)
	{
		this->Spn_S		= _Speed;
		this->Spn_Dir	= _Dir;

		this->Spn_Run	= true;
	}
	inline void			SpnLoop()
	{
		if (	this->Spn_Run	)
		{
			this->Spn_Dgr	= this->Spn_Dgr + (this->Spn_S * ((this->Spn_Dir) ? 1 : -1));
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double		g_FIn(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	1:
			return	this->FIn_A;

		case	2:
			return	this->FIn_S;
		}
	}
	inline double		g_FOu(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	1:
			return	this->FOu_A;
	
		case	2:
			return	this->FOu_S;
		}
	}
	inline double		g_FIO(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->FIO_A;

		case 2:
			return this->FIO_Run;

		case 3:
			return this->FIO_End;
		}
	}
	inline double		g_FLp(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	1:
			return	this->FLp_A;
		}
	}
	inline double		g_Rainbow(int _ElmVal)
	{
		switch (	_ElmVal	)
		{
		case	1:
			return	this->R;
	
		case	2:
			return	this->G;
	
		case	3:
			return	this->B;
		}
	}
};
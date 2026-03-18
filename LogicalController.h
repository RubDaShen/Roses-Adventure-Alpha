#pragma once

#include		<iostream>

#include		"_Basics_KeyBoard.h"



class		_Controller_Logic
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Really Important Variables
//	-------------------------------------------
private:
	double		m_OriginalGameLoopValue		= 144.0;
	double		m_GameLoopValue				= 144.0;
	double		m_GameLoopLogic				= 1000.0 / (this->m_GameLoopValue);

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_LastSavedValue		= 0.0;

	bool			m_InstaKeyPressed		= false;
	bool			m_EffectKeyPressed		= false;

//	-------------------------------------------
//					Animations
//	-------------------------------------------
private:
	double			m_To				= 0.0;
	double			m_Speed				= 0.0;
	double			m_IntervalTime		= 0.0;
	double			m_EffectTime		= 1.5;

	int				m_Flag				= 0;
	int				m_AnimationFlag		= 0;

	bool			m_AnimationFlagUsed = false;
	bool			m_Finished			= true;

//	-------------------------------------------
//				External and Linkers
//	-------------------------------------------
private:
	_Basic_KeyBoard*		_KeyBoard_ = nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Static Variables
//	-------------------------------------------
public:
	static double		_fdTime_;		//	Stands for: Fixed Delta Time.
	static double		_dTime_;		//	Stands for: Delta Time.

	static double		_gLpVal_;		//	Stands for: Game Loop Value.
	static int			_ogLpV_;		//	Stands for: Original Game Loop Value; 

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Logic(	_Basic_KeyBoard* _KeyBoard_Ptr	)
	{
		this->_KeyBoard_	= _KeyBoard_Ptr;

		this->Ld_All();
	}

	~_Controller_Logic()
	{
		
	}

//	-------------------------------------------
//				Events and externals
//	-------------------------------------------
public:
	inline void			KeyBoardStuff()
	{
		if (	this->_KeyBoard_->g_Key(kyb::T)->g_Is(3)	)
		{
			if (	!this->m_InstaKeyPressed	)
			{
				this->m_GameLoopLogic	= 300.0;
			}
			else
			{
				this->m_GameLoopLogic	= 144.0;
			}


			this->m_InstaKeyPressed		= !this->m_InstaKeyPressed;

			this->_gLpVal_				= this->m_GameLoopLogic;
			this->_fdTime_				= this->m_OriginalGameLoopValue / this->m_GameLoopLogic;
			this->_dTime_				= 1.0 / this->m_GameLoopLogic;
		}

		if (	this->_KeyBoard_->g_Key(kyb::D)->g_Is(3)	)
		{
			if (	!this->m_EffectKeyPressed	)
			{
				this->SlowDown(300, this->m_EffectTime);
			}
			else
			{
				this->SlowDown(this->m_OriginalGameLoopValue, this->m_EffectTime);
			}



			this->m_EffectKeyPressed		= !this->m_EffectKeyPressed;
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		
	}

	inline void			SlowDown(	int To, double Time		)
	{
		//	This slow motion effect lasts what is was told,
		//	since slow motion is being applied that would mean
		//	that the slow motion effect should slow itslef down too.
		this->m_To			= To;
		this->m_Speed		= (this->m_To - this->_gLpVal_) / (this->m_OriginalGameLoopValue * Time);
		this->m_Finished	= false;

		if (	this->m_Speed <= 0.0	)
		{
			this->m_Flag	= 1;
		}
		else
		{
			this->m_Flag	= 2;
		}

		this->m_AnimationFlag		= this->m_Flag;
	}
	inline void			RunEffect()
	{
		if (	!this->m_Finished	)
		{
			//	Changing the frame rate.
			this->m_LastSavedValue	= this->_gLpVal_;
			this->_gLpVal_			= this->_gLpVal_ + this->m_Speed;

			//	Now, re-calculate all values.
			this->_fdTime_			= this->m_OriginalGameLoopValue / this->_gLpVal_;
			this->_dTime_			= 1.0 / this->_gLpVal_;

			//	Stop conditions.
			switch (	this->m_Flag	)
			{
			case	1:
				if (	this->m_To > this->_gLpVal_	)
				{
					//	DTime.
					this->_gLpVal_				= this->m_To;
					this->m_Finished			= true;
					this->m_LastSavedValue		= this->_gLpVal_;

					//	Interval Time.
					this->m_IntervalTime		= 0.0;
				}
				else
				{
					//	IntervalTime.
					this->m_IntervalTime		= this->m_IntervalTime - (1.0 / (this->m_EffectTime * this->_ogLpV_));
				}
				break;

			case	2:
				if (	this->m_To < this->_gLpVal_	)
				{
					//	DTime.
					this->_gLpVal_				= this->m_To;
					this->m_Finished			= true;
					this->m_LastSavedValue		= this->_gLpVal_;

					//	Interval Time.
					this->m_IntervalTime		= 1.0;
				}
				else
				{
					//	IntervalTime.
					this->m_IntervalTime		= this->m_IntervalTime + (1.0 / (this->m_EffectTime * this->_ogLpV_));
				}
				break;
			}
		}
	}

	inline void			LogicDis()
	{
		this->KeyBoardStuff();
		this->RunEffect();
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline bool			IsSlowMotion()
	{
		return		this->m_EffectKeyPressed;
	}
	inline double		GetValues(	int What	)		const
	{
		switch (	What	)
		{
		case 1:
			return		this->m_IntervalTime;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline bool			GameLoopIsChanging()
	{
		if (	this->m_LastSavedValue != this->_gLpVal_	)
		{
			return		true;
		}
		else
		{
			return		false;
		}
	}
	inline int			GetFlagForFlashBang(	bool FlagOut = false	)
	{
		if (	FlagOut	)
		{
			int _Aux_				= this->m_AnimationFlag;
			this->m_AnimationFlag	= 0;

			return		_Aux_;
		}

		return		this->m_AnimationFlag;
	}
};
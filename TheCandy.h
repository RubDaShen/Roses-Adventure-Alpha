/*
	Comment section . . .
	-	SwapDirection
			Intented to show where the swap direction is.
			For example: if the swap was from right to left or left to right and so on.
			And now, while I'm writing this comment, I just realized the importance of this
			variable. So now on, it < SwapDir> is meant to show
			up (1), left (2), down (3), right (4) state.

	-	_MatchingSensibility_
			This is basically how matches will be for candies.
			When a candy is falling, it cannot be matched, and then
			matching sensibility comes. If the speed of the candy is greater than
			the matching sensibility value, that means that the candy is 
			indeed falling, otherwise it is not and can be matched.

	-	0.0000001
			Defined as 0 when dividing the same number multiple times.

	-	$
			The dollar symbol shows that a variable is a constant or should not be
			modified.
*/

#pragma once

#include		"thyObject.h"
#include		"_MyIncludes_.h"
#include		"Tools_.h"
#include		"LogicalController.h"



class		TheCandy : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!	
//	-------------------------------------------
public:
	enum		enm_InstaState
	{
		Nothing			= 0,
		IsMatched		= 1,
		EatenByFish		= 2,
		FusedByBoB		= 3,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[0] Constants	
//	-------------------------------------------
private:
	const double		_BouncingChecker_ = 1.2;
	const double		_BouncingLimit_ = 0.3;

	const double		$_Width = 90.0;
	const double		$_Height = 90.0;

	const double		_SidingSpeed_ = 5.0;
	const double		$_SwappingSpeed = 0.45;
	const double		$_SwappingAceleration = 0.45;

//	-------------------------------------------
//		[1] Section about logic of candies
//	-------------------------------------------
private:
	int				m_iPos = 0, m_jPos = 0;
	int				m_KindID = 0, m_ItemID = 0;

	int				m_InnerTime = 0;

//	-------------------------------------------
//			[2] Section about swapping
//	-------------------------------------------
private:	
	int				m_Target_iPos = 0, m_Target_jPos = 0;
	int				m_SwapDirection = 0, m_Last_SwapDir = 0;
	int				m_OtherSwappedID = 0;
	int				m_SwitchOrder = 0;

	int				Cnt_EndSwap = 0, Trg_EndSwap = 5;
	int				Cnt_ThisWasSwapped = 0, Trg_ThisWasSwapped = 60;

	double			m_xP_SwapDes = 0.0, m_yP_SwapDes = 0.0;
	double			m_xS_Swap = 0.45, m_yS_Swap = 0.45;

	bool			m_IsSwapping = false;
	bool			m_ReachedSwapDestination = false;
	bool			m_InvalidSwap = false;
	bool			m_WasSwitched = false;
	bool			m_InstaDelete = false;

//	-------------------------------------------
//					[3]	Counters
//	-------------------------------------------
private:	
	int				Cnt_CanFall = 0, Trg_CanFall = (_TARGET_UNDEFINED);

	int				Cnt_CanBeCrushed = 0, Trg_CanBeCrushed = (_TARGET_UNDEFINED);

	int				Cnt_CanBeMatched = 0, Trg_CanBeMatched = (_TARGET_UNDEFINED);

	int				Cnt_IsInvincible = 0, Trg_IsInvincible = (_TARGET_UNDEFINED);

	int				Cnt_IsHidden = 0, Trg_IsHidden = 0;

	int				Tgg_IsOld	= def::enm_Triggers::NotInitialized;
	int				Cnt_IsOld	= 0, Trg_IsOld = 0;

//	-------------------------------------------
//				[4] For sideways
//	-------------------------------------------
private:
	double			m_xP_Side = 0.0, m_yP_Side = 0.0;
	double			m_xS_Side = 0.0, m_yS_Side = 5.0;

	int				m_SideDirection = 0;
	int				m_iPos_Side = -1, m_jPos_Side = -1;

	bool			m_IsSideWays = false;
	bool			m_HasArrived_Side = false;

//	-------------------------------------------
//			[5] For special candies
//	-------------------------------------------
private:
	//	1~	Jelly Fish !
	bool			m_TargetedByFish	= false;
	bool			m_CrushedByFish		= false;


	//	2~	Wrapped Candy !
	int				Tgg_ExplodeNow		= def::enm_Triggers::NotInitialized;
	int				Cnt_ExplodeNow		= 0, Trg_ExplodeNow = 0;

	int				m_WrappedTime		= 0;
	double			m_Expladious		= 2.0;

	bool			m_IsShaking			= false;


	//	3~	Bom-O-Bom !
	bool			m_IsFusing			= false;


	//	4~	Frozen Candy !
	bool			m_IsPainting		= false;


	//	8~	Popping Candy !
	bool			m_IsPopping			= false;

//	-------------------------------------------
//				[6]	Candy settings
//	-------------------------------------------
private:
	double			m_Bounciness	= 4.5;

	bool			m_HasBlocker	= false;

	bool			m_IsBouncing	= false;
	bool			m_IsFalling		= false;
	bool			m_IsToCrush		= false;
	bool			m_IsNotInPlay	= false;
	bool			m_IsInvincible	= false;
	bool			m_IsNew			= false;
	bool			m_IsHidden		= false;
	bool			m_IsSpecialMix	= false;

	int				m_IsBeingFused		= 0;
	int				m_IsBeingPainted	= 0;
	int				m_InstaState		= enm_InstaState::Nothing;

	bool			m_CanBeCrushed	= true;
	bool			m_CanBeMatched	= true;
	bool			m_CanFall		= true;

//	-------------------------------------------
//		[7] HitPoints and health system
//	-------------------------------------------
private:
	double			m_InitialHP			= 1.0;				
	double			m_LiquoriceCageHP	= 0.0;	

	bool			m_HasLiquoriceCage	= false;	

//	-------------------------------------------
//		[8] Physics and more gravity stuff
//	-------------------------------------------
private:
	int				m_GravityDirection		= 1;
	bool			m_RoofHit				= false;

//	-------------------------------------------
//		[9]	About its crushing properties.
//	-------------------------------------------
private:
	TheCandy*		m_LinkerProspform	= nullptr;

	bool			m_DropCrush		= true;
	
	double			m_CrushedAngle	= def::enm_Defines::_USE_DEFAULT;
	double			m_ExtraSpeed	= 0.0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	//	Default constructor. All to 0.s
	TheCandy() : thyObject(0, 0, def::enm_ObjectType::ObjCandy)
	{
		//	First things, first.
		this->_W				= $_Width, this->_H			= $_Height;
		this->_W_Sprite			= $_Width, this->_H_Sprite	= $_Height;
		this->ObjectHitPoints	= 1;

		tls::SetRGB(0, this->R_col, this->G_col, this->B_col);



		this->ObjectID		= this->_Cnt_ObjID_;
		++this->_Cnt_ObjID_;
	}
	TheCandy(double _xP, double _yP, int _KindID, int _ItemID, int _iPos, int _jPos) : thyObject(_xP, _yP, def::enm_ObjectType::ObjCandy)
	{
		//	First things, first.
		this->_W			= $_Width, this->_H			= $_Height;
		this->_W_Sprite		= $_Width, this->_H_Sprite	= $_Height;
		this->m_InitialHP	= 1;

		//	Some settings.
		this->m_iPos		= _iPos, this->m_jPos		= _jPos;
		this->m_KindID		= _KindID, this->m_ItemID	= _ItemID;

		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);



		this->ObjectID		= this->_Cnt_ObjID_;
		++this->_Cnt_ObjID_;
	}

	~TheCandy()
	{

	}

//	-------------------------------------------
//		Statics and global-like variables
//	-------------------------------------------
public:
	static int		_Cnt_ObjID_;
	static double	_Gravity_;
	static double	_MatchingSensibility_;

//	-------------------------------------------
//		[1] Section about logic of candies
//	-------------------------------------------
public:
	inline void			s_Pos(int _Which, int _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_iPos = _Val;
			break;

		case 2:
			this->m_jPos = _Val;
			break;
		}
	}
	inline void			s_KindID(int _Val)
	{
		this->m_KindID = _Val;

		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);
	}
	inline void			s_ItemID(int _Val)
	{
		//	Set the item value.
		this->m_ItemID = _Val;

		//	When changing values, make some other values
		//	change as well.
		switch (this->m_ItemID)
		{
		case		STA_::enm_ItemID::BomOBom:
			this->m_CanBeMatched = false;
			break;

		case		STA_::enm_ItemID::CupCake_1:	
		case		STA_::enm_ItemID::CupCake_2:
		case		STA_::enm_ItemID::CupCake_3:
		case		STA_::enm_ItemID::CupCake_4:
		case		STA_::enm_ItemID::CupCake_5:
			this->m_CanBeMatched	= false;
			this->m_CanFall			= false;
				
			//	This if checks if the candy is already dead.
			//	If the HP is 0 means that it is dead and is no
			//	longer meant to be updated.
			if (	0.0 < this->m_InitialHP	)
			{
				this->m_InitialHP		= this->m_ItemID - STA_::enm_ItemID::CupCake_1 + 1;
			}
			
			break;
		}
	}
	inline void			s_InnerTime(int _Val)
	{
		this->m_InnerTime = _Val;
	}

	inline int			g_Pos(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_iPos;

		case 2:
			return this->m_jPos;
		}
	}
	inline int			g_KindID()
	{
		return this->m_KindID;
	}
	inline int			g_ItemID()
	{
		return this->m_ItemID;
	}
	inline int			g_InnerTime(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_InnerTime;

		case 2:
			return this->m_WrappedTime;
		}
	}

//	-------------------------------------------
//			[2] Section about swapping
//	-------------------------------------------
public:
	inline void		SwapObject()
	{
		//	Pretty self explanatory...
		if (this->m_IsSwapping)
		{
			//	When switching candies, there are four possible cases:
			//	left, right, up and down.
			switch (this->m_SwapDirection)
			{
			case	def::enm_Directions::Up:			// Up
				if (this->m_yP_SwapDes > (this->yP + this->m_yS_Swap))
				{
					this->m_yS_Swap		= this->m_yS_Swap + this->$_SwappingAceleration;
					this->yP			= this->yP + this->m_yS_Swap;
				}
				else
				{
					this->yP			= this->m_yP_SwapDes;
					this->m_yS_Swap		= this->$_SwappingSpeed;

					if (this->Cnt_EndSwap < this->Trg_EndSwap)
					{
						++this->Cnt_EndSwap;
					}
					else
					{
						this->Cnt_EndSwap		= this->m_SwapDirection = 0;
						this->m_IsSwapping		= false;
						this->m_WasSwitched		= true;

						if (this->m_InvalidSwap)
						{
							this->m_ReachedSwapDestination	= true;
							this->m_InvalidSwap				= false;
						}
					}
				}

				break;

			case	def::enm_Directions::Left:			// Left
				if (this->m_xP_SwapDes < (this->xP - this->m_xS_Swap))
				{
					this->m_xS_Swap		= this->m_xS_Swap + this->$_SwappingAceleration;
					this->xP			= this->xP - this->m_xS_Swap;
				}
				else
				{
					this->xP			= this->m_xP_SwapDes;
					this->m_xS_Swap		= $_SwappingSpeed;



					if (this->Cnt_EndSwap < this->Trg_EndSwap)
					{
						++this->Cnt_EndSwap;
					}
					else
					{
						this->Cnt_EndSwap		= this->m_SwapDirection = 0;
						this->m_IsSwapping		= false;
						this->m_WasSwitched		= true;

						if (this->m_InvalidSwap)
						{
							this->m_ReachedSwapDestination	= true;
							this->m_InvalidSwap				= false;
						}
					}
				}

				break;

			case	def::enm_Directions::Down:			// Down
				if ((this->yP - this->m_yS_Swap) > this->m_yP_SwapDes)
				{
					this->m_yS_Swap		= this->m_yS_Swap + this->$_SwappingAceleration;
					this->yP			= this->yP - this->m_yS_Swap;
				}
				else
				{
					this->yP			= this->m_yP_SwapDes;
					this->m_yS_Swap		= this->$_SwappingSpeed;

					if (this->Cnt_EndSwap < this->Trg_EndSwap)
					{
						this->Cnt_EndSwap++;
					}
					else
					{
						this->Cnt_EndSwap		= this->m_SwapDirection = 0;
						this->m_IsSwapping		= false;
						this->m_WasSwitched		= true;

						if (this->m_InvalidSwap)
						{
							this->m_ReachedSwapDestination	= true;
							this->m_InvalidSwap				= false;
						}
					}
				}

				break;

			case	def::enm_Directions::Right:			// Right
				if ((this->xP + this->m_xS_Swap) < this->m_xP_SwapDes)
				{
					this->m_xS_Swap		= this->m_xS_Swap + this->$_SwappingAceleration;
					this->xP			= this->xP + this->m_xS_Swap;
				}
				else
				{
					this->xP			= this->m_xP_SwapDes;
					this->m_xS_Swap		= this->$_SwappingSpeed;
					


					if (this->Cnt_EndSwap < this->Trg_EndSwap)
					{
						this->Cnt_EndSwap++;
					}
					else
					{
						this->Cnt_EndSwap		= this->m_SwapDirection = 0;
						this->m_IsSwapping		= false;
						this->m_WasSwitched		= true;

						if (this->m_InvalidSwap)
						{
							this->m_ReachedSwapDestination		= true;
							this->m_InvalidSwap					= false;
						}
					}
				}

				break;
			}
		}
	}



	inline void		IniCnt_ObjSwitched()
	{
		if (	this->m_WasSwitched	)
		{
			if (this->Cnt_ThisWasSwapped < this->Trg_ThisWasSwapped)
			{
				this->Cnt_ThisWasSwapped++;
			}			
			else
			{
				this->Cnt_ThisWasSwapped	= 0;
				this->m_WasSwitched			= false;
				this->m_SwitchOrder			= 0;
			}
		}
	}



	inline void			s_IsSwapping(int _Which, bool _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_IsSwapping = _Val;
			break;

		case 2:
			this->m_ReachedSwapDestination = _Val;
			break;

		case 3:
			this->m_InvalidSwap = _Val;
			break;

		case 4:
			this->m_WasSwitched = _Val;
			break;
		}
	}
	inline bool			g_IsSwapping(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_IsSwapping;

		case 2:
			return this->m_ReachedSwapDestination;

		case 3:
			return this->m_InvalidSwap;

		case 4:
			return this->m_WasSwitched;

		default:
			return false;
		}
	}

	inline void			s_TargetPos(int _Which, int _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_Target_iPos = _Val;
			break;

		case 2:
			this->m_Target_jPos = _Val;
			break;
		}
	}

	inline void			s_SwapDirection(int _Val)
	{
		this->m_SwapDirection	= _Val;
		this->m_Last_SwapDir	= _Val;
	}
	inline int			g_SwapDirection()
	{
		return		this->m_SwapDirection;
	}
	inline void			Reverse_SwapDir(double _xSwap_Des, double _ySwap_Des)
	{
		this->m_ReachedSwapDestination = false;



		switch (this->m_Last_SwapDir)
		{
		case def::enm_Directions::Up:	
			this->m_SwapDirection	= def::enm_Directions::Down;
			this->m_yP_SwapDes		= _ySwap_Des;
			this->m_yS_Swap			= $_SwappingSpeed;

			break;

		case def::enm_Directions::Left:	
			this->m_SwapDirection	= def::enm_Directions::Right;
			this->m_xP_SwapDes		= _xSwap_Des;
			this->m_xS_Swap			= $_SwappingSpeed;

			break;

		case def::enm_Directions::Down:
			this->m_SwapDirection	= def::enm_Directions::Up;
			this->m_yP_SwapDes		= _ySwap_Des;
			this->m_yS_Swap			= $_SwappingSpeed;

			break;

		case def::enm_Directions::Right:	
			this->m_SwapDirection	= def::enm_Directions::Left;
			this->m_xP_SwapDes		= _xSwap_Des;
			this->m_xS_Swap			= $_SwappingSpeed;

			break;
		}
	}

	inline void			s_OtherSwappedID(int _Val)
	{
		this->m_OtherSwappedID = _Val;
	}
	inline int			g_OtherSwappedID()
	{
		return this->m_OtherSwappedID;
	}

	inline void			s_SwapDes(double _xP_Des, double _yP_Des)
	{
		this->m_xP_SwapDes	= _xP_Des;
		this->m_yP_SwapDes	= _yP_Des;
	}
	inline double		g_SwapDes(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_xP_SwapDes;

		case 2:
			return this->m_yP_SwapDes;
		}
	}

	inline void			s_SwitchOrder(int _Val)
	{
		this->m_SwitchOrder = _Val;
	}
	inline int			g_SwitchOrder()
	{
		return		this->m_SwitchOrder;
	}

	inline void			s_InstaDelete(bool _Val)
	{
		this->m_InstaDelete			= _Val;
	}
	inline bool			g_InstaDelete()
	{
		return		this->m_InstaDelete;
	}

//	-------------------------------------------
//					[3]	Counters
//	-------------------------------------------
public:
	inline void		IniCnt_CanFall()
	{
		if (!this->m_CanFall)
		{
			if (this->Cnt_CanFall < this->Trg_CanFall)
			{
				++this->Cnt_CanFall;

				this->xS	= this->yS = 0.0;
			}				
			else
			{
				this->Cnt_CanFall		= 0;
				this->m_CanFall			= true;
				this->Trg_CanFall		= (_TARGET_UNDEFINED);
			}
		}
	}
	inline void		SetTrg_CanFall(double _Time_In_Seconds)
	{
		if (_Time_In_Seconds == def::enm_Defines::_USE_DEFAULT)
		{
			this->m_CanFall			= false;
			this->Trg_CanFall		= (GAME_LOOP_VALUE) * 0.5;
		}
		else
		{
			this->m_CanFall			= false;
			this->Trg_CanFall		= (GAME_LOOP_VALUE) * _Time_In_Seconds;
		}	
	}

	inline void		IniCnt_CanBeCrushed()
	{
		if (!this->m_CanBeCrushed)
		{
			if (this->Cnt_CanBeCrushed < this->Trg_CanBeCrushed)
			{
				++this->Cnt_CanBeCrushed;
			}				
			else
			{
				this->Cnt_CanBeCrushed	= 0;
				this->m_CanBeCrushed	= true;
				this->Trg_CanBeCrushed	= (_TARGET_UNDEFINED);
			}
		}
	}
	inline void		SetTrg_CanBeCrushed(double _Time_In_Seconds)
	{
		if (_Time_In_Seconds == def::enm_Defines::_USE_DEFAULT)
		{
			this->m_CanBeCrushed	= false;
			this->Trg_CanBeCrushed	= (GAME_LOOP_VALUE) * 0.5;
		}
		else
		{
			this->m_CanBeCrushed	= false;
			this->Trg_CanBeCrushed	= (GAME_LOOP_VALUE) * _Time_In_Seconds;
		}	
	}

	inline void		IniCnt_CanBeMatched()
	{
		if (!this->m_CanBeMatched)
		{
			if (this->Cnt_CanBeMatched < this->Trg_CanBeMatched)
			{
				++this->Cnt_CanBeMatched;
			}
			else
			{
				this->Cnt_CanBeMatched	= 0;
				this->Trg_CanBeMatched	= (_TARGET_UNDEFINED);

				//	Setting to true but first let's verify.
				if (		(this->m_ItemID != STA_::enm_ItemID::BomOBom)			&&			
							(this->m_ItemID != STA_::enm_ItemID::WrappedFuse)		)
				{
					this->m_CanBeMatched = true;
				}
			}
		}
	}
	inline void		SetTrg_CanBeMatched(double _Time_In_Seconds)
	{
		this->m_CanBeMatched		= false;



		if (	_Time_In_Seconds == def::enm_Defines::_USE_DEFAULT	)
		{
			this->Trg_CanBeMatched	= (GAME_LOOP_VALUE) * 0.5;
		}
		else
		{	
			this->Trg_CanBeMatched = (GAME_LOOP_VALUE) * _Time_In_Seconds;
		}	
	}

	inline void		IniCnt_IsInvincible()
	{
		if (this->m_IsInvincible)
		{
			if (this->Cnt_IsInvincible < this->Trg_IsInvincible)
			{
				this->Cnt_IsInvincible++;
			}				
			else
			{
				this->Cnt_IsInvincible	= 0;
				this->m_IsInvincible	= false;
				this->Trg_IsInvincible	= (_TARGET_UNDEFINED);
			}
		}
	}
	inline void		SetTrg_IsInvincible(double _Time_In_Seconds)
	{
		if (_Time_In_Seconds == def::enm_Defines::_USE_DEFAULT)
		{
			this->m_IsInvincible	= true;
			this->Trg_IsInvincible	= (GAME_LOOP_VALUE)	* 0.2;
		}
		else
		{
			this->m_IsInvincible	= true;
			this->Trg_IsInvincible	= (GAME_LOOP_VALUE) * _Time_In_Seconds;
		}
	}

	inline void		IniCnt_IsHidden()
	{
		if (this->m_IsHidden)
		{
			if (	this->Cnt_IsHidden < this->Trg_IsHidden)
			{
				++this->Cnt_IsHidden;
			}
			else
			{
				this->Cnt_IsHidden		= 0;
				this->Trg_IsHidden		= (_TARGET_UNDEFINED);
				this->m_IsHidden		= false;
			}
		}
	}

	inline void		IniCnt_InnerTime()
	{
		++this->m_InnerTime;



		//	In here you can add more like 
		//	wrapped explosion, bubblegum explosion, ...
		if (this->Tgg_ExplodeNow == def::enm_Triggers::Waiting)
		{
			++this->m_WrappedTime;
		}
	}

//	-------------------------------------------
//					[4]	Sideways
//	-------------------------------------------
	inline void			MoveToSide()
	{
		//	Once it has settled to move sideways, the HasArrived is
		//	obviously false.
		this->m_HasArrived_Side = false;

		//	If it is settled to move sideways, then do some stuff...
		{
			if (this->m_IsSideWays)
			{
				//	Also, is falling.
				this->m_IsFalling = true;

				//	With SideDirection I mean the following...
				//		[1]	[ ]	[2]
				//		[ ]	[O]	[ ]
				//		[3]	[ ]	[4]
				switch (this->m_SideDirection)
				{
				case	def::enm_Directions::Up:
					break;

				case	def::enm_Directions::Down:
					break;

				case	def::enm_Directions::Left:
					this->m_xS_Side = -this->_SidingSpeed_;
					this->m_yS_Side = -this->_SidingSpeed_;

					// --- Move it, Side it ! ---

					//	Sideways stuff...
					{
						//	This is only for 'x' axis.
						{
							if ((this->xP + m_xS_Side) > this->m_xP_Side)
							{
								this->xP = this->xP + this->m_xS_Side;
							}
							else
							{
								this->xP = this->m_xP_Side;
							}
						}

						//	Now yeah, for 'y' axis too.
						{
							if ((this->yP + this->m_yS_Side) > this->m_yP_Side)
							{
								this->yP = this->yP + this->m_yS_Side;
							}
							else
							{
								this->yP = this->m_yP_Side;
							}
						}

						//	Checking if both positions are correct.
						{
							if ((this->xP == this->m_xP_Side) && (this->yP == this->m_yP_Side))
							{
								this->m_IsSideWays = false;
								this->m_HasArrived_Side = true;
							}
						}
					}



					break;

				case	def::enm_Directions::Right:
					this->m_xS_Side = this->_SidingSpeed_;
					this->m_yS_Side = -this->_SidingSpeed_;

					// --- Move it, Side it ! ---

					//	Sideways stuff...
					{
						//	This is only for 'x' axis.
						{
							if ((this->xP + m_xS_Side) < this->m_xP_Side)
							{
								this->xP = this->xP + this->m_xS_Side;
							}
							else
							{
								this->xP = this->m_xP_Side;
							}
						}

						//	Now yeah, for 'y' axis too.
						{
							if ((this->yP + this->m_yS_Side) > this->m_yP_Side)
							{
								this->yP = this->yP + this->m_yS_Side;
							}
							else
							{
								this->yP = this->m_yP_Side;
							}
						}

						//	Checking if both positions are correct.
						{
							if ((this->xP == this->m_xP_Side) && (this->yP == this->m_yP_Side))
							{
								this->m_IsSideWays = false;
								this->m_HasArrived_Side = true;
							}
						}
					}

					break;
				}
			}
		}
	}

	inline void			s_SideDirection(int _SideDirection, double _xP, double _yP)
	{
		this->m_SideDirection = _SideDirection;

		this->m_xP_Side = _xP;
		this->m_yP_Side = _yP;
	}
	inline void			s_SideWaysPos(	int iPos, int jPos	)
	{
		this->m_iPos_Side = iPos, this->m_jPos_Side = jPos;
	}
	inline int			g_SideWaysPos(	int What	)
	{
		switch (What)
		{
		case	1:	
			return		this->m_iPos_Side;
			
		case	2:
			return		this->m_jPos_Side;
		}
	}

	inline void			s_IsSideWays(	int What, int Value		)
	{
		switch (	What	)
		{
		case	1:
			this->m_IsSideWays = Value;
		}
	}
	inline bool			g_IsSideWays(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_IsSideWays;

		default:
			return false;
		}
	}
	inline bool			g_HasArrivedSideWays()
	{
		return		this->m_HasArrived_Side;
	}

//	-------------------------------------------
//			[5] For special candies
//	-------------------------------------------
public:
	inline void			IniTgg_IsOld()
	{
		if (this->Tgg_IsOld == def::enm_Triggers::Waiting)
		{
			if (this->Cnt_IsOld < this->Trg_IsOld)
			{
				++this->Cnt_IsOld;
			}
			else
			{
				this->Cnt_IsOld		= 0;
				this->Trg_IsOld		= (def::enm_Defines::_NOT_INITIALIZED);
				this->Tgg_IsOld		= def::enm_Triggers::Activated;
			}
		}
	}
	inline void			Trigger_SpecialCandyCreated(double _Time_In_Seconds)
	{
		if (	this->Tgg_IsOld == def::enm_Triggers::NotInitialized	)
		{
			this->m_IsHidden		= true;
			this->m_IsNew			= true;



			this->Tgg_IsOld			= def::enm_Triggers::Waiting;

			this->Trg_IsHidden		= (GAME_LOOP_VALUE * _Time_In_Seconds);
			this->Trg_IsOld			= (GAME_LOOP_VALUE * _Time_In_Seconds);
		} 
	}



	//	1~	Jelly Fish !
	inline void			s_TargetedByFish(bool _Val)
	{
		//	If you are looking why targeted candies cannot be matched (fall property),
		//	then go and check the Board class and find when the values are
		//	updated to the board at I and J!
		//	Update: Solved!

		this->m_TargetedByFish = _Val;
	}
	inline bool			g_TargetedByFish()
	{
		return this->m_TargetedByFish;
	}

	//	2~	Wrapped Candy !
	inline void			EnableShaking(bool _Val)
	{
		this->m_IsShaking = _Val;
	}

	inline void			IniTgg_ExplodeNow()
	{
		if (this->Tgg_ExplodeNow == def::enm_Triggers::Waiting)
		{
			if (this->Cnt_ExplodeNow < this->Trg_ExplodeNow)
			{
				++this->Cnt_ExplodeNow;

				this->m_CanFall		= false;
				this->xS			= this->yS = 0.0;
			}
			else
			{
				this->Cnt_ExplodeNow	= 0;
				this->Trg_ExplodeNow	= (GAME_LOOP_VALUE);
				this->Tgg_ExplodeNow	= def::enm_Triggers::Activated;
				this->m_WrappedTime		= 0;
				this->m_CanBeMatched	= false;
				this->m_CanFall			= true;	
			}
		}
	}
	inline void			Trigger_WrappedExplosion(double _Time_In_Seconds)
	{
		if (	this->Tgg_ExplodeNow == def::enm_Triggers::NotInitialized	)
		{
			this->Tgg_ExplodeNow		= def::enm_Triggers::Waiting;
			this->Trg_ExplodeNow		= (GAME_LOOP_VALUE * _Time_In_Seconds);

			this->SetTrg_CanBeMatched(_Time_In_Seconds);
		}
	}

	inline double		g_Expladious()
	{
		return		this->m_Expladious;
	}
	
	inline void			s_BoB_Is(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_IsFusing		= _Val;
			break;

		case 2:
			this->m_IsBeingFused	= _Val;
			break;
		}
	}
	inline int			g_BoB_Is(int _What)
	{
		//	About m_IsBeingFused:
		//		Number 0 means, well, false.
		//		Number 1 means on.

		switch (_What)
		{
		case 1:
			return		this->m_IsFusing;

		case 2:
			return		this->m_IsBeingFused;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	//	4~	Frozen Candy !
	inline void			s_Fc_Is(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_IsPainting		= _Val;
			break;

		case 2:
			this->m_IsBeingPainted	= _Val;
			break;
		}
	}
	inline int			g_Fc_Is(int _What)
	{
		//	About m_IsBeingPainted:
		//		Number 0 means, well, false.
		//		Number 1 means that is not painted yet.
		//		Number 2 means painted and ready to go.

		switch (_What)
		{
		case 1:
			return		this->m_IsPainting;

		case 2:
			return		this->m_IsBeingPainted;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	//	5~	Popping Candy !
	inline void			s_Ppc_Is(int _What, int _Val)
	{
		switch (	_What	)
		{
		case 1:
			this->m_IsPopping =	_Val;
		}
	}
	inline int			g_Ppc_Is(int _What)
	{
		//	About m_IsBeingPainted:
		//		Number 0 means, well, false.
		//		Number 1 means that is popping out.

		switch (_What)
		{
		case 1:
			return		this->m_IsPopping;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

//	-------------------------------------------
//				[6] Candy Settings
//	-------------------------------------------
public:
	inline void			HideCandy(double _Time_In_Seconds)
	{
		this->m_IsHidden	= true;

		this->Trg_IsHidden	= (GAME_LOOP_VALUE * _Time_In_Seconds);
	}
	inline void			ResetInstaStates()
	{
		this->m_InstaState		= enm_InstaState::Nothing;
	}


	inline void			s_Can(int _Which, bool _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_CanFall = _Val;

			//	Code here the always condition...
			//	But check I and J, since it changes the value already.

			break;

		case 2:
			this->m_CanBeCrushed = _Val;
			break;

		case 3:
			this->m_CanBeMatched = _Val;
			break;
		}
	}
	inline void			s_Is(int _Which, bool _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_IsFalling = _Val;
			break;

		case 2:
			this->m_IsBouncing = _Val;
			break;

		case 3:
			this->m_IsToCrush = _Val;
			break;

		case 4:
			this->m_IsNotInPlay = _Val;
			break;

		case 5:
			this->m_IsInvincible = _Val;
			break;

		case 6:
			this->m_IsNew = _Val;
			break;

		case 7:
			this->m_IsSpecialMix = _Val;
			break;
		}
	}
	inline void			s_InstaState(int Value)
	{
		this->m_InstaState			= Value;
	}

	inline bool			g_Can(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_CanFall;

		case 2:
			return this->m_CanBeCrushed;

		case 3:
			return this->m_CanBeMatched;
		}
	}
	inline bool			g_Is(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_IsFalling;

		case 2:
			return this->m_IsBouncing;

		case 3:
			return this->m_IsToCrush;

		case 4:
			return this->m_IsNotInPlay;

		case 5:
			return this->m_IsInvincible;

		case 6:
			return this->m_IsNew;

		case 7:	
			return this->m_IsSpecialMix;

		case 8:		//	Deprecated.
			return this->m_IsBeingFused;		

		case 9:		//	Deprecated.
			return this->m_IsBeingPainted;		

		case 10:
			return this->m_IsHidden;

		case 11:
			return this->m_IsShaking;

		default:
			return def::enm_Defines::_NOT_FOUND;
		}
	}
	inline int			g_InstaState()
	{
		return			this->m_InstaState;
	}
	inline int			g_Trigger(int _What)
	{
		int*		_Aux_Val	= nullptr;
		int			_Org_Value	= def::enm_Triggers::_Unknown;



		//	Selecting what trigger to use.
		{
			switch (_What)
			{
			case 1:
				_Aux_Val = &this->Tgg_IsOld;
				break;

			case 2:		//	Wrapped candy and BubbleGum.
				_Aux_Val = &this->Tgg_ExplodeNow;
				break;

			default:
				throw std::runtime_error("_Aux_Val is not pointing to any value.");
			}
		}

		//	Then checks for trigger value.
		{
			_Org_Value = *_Aux_Val;



			if (*_Aux_Val == def::enm_Triggers::Activated)
			{
				*_Aux_Val = def::enm_Triggers::NotInitialized;
			}
		}

		//	Finally, return.
		{
			return _Org_Value;
		}
	}
	inline int			g_JustTrigger(int _What)
	{
		switch (_What)
		{
		case 1:
			return	this->Tgg_IsOld;

		case 2:
			return	this->Tgg_ExplodeNow;

		default:
			return	def::enm_Defines::_NOT_FOUND;
		}
	}

	inline bool			g_ItemAllowsSomething(	int What	)
	{
		switch (	What	)
		{
		//	-------------------------
		//		Allows matching?
		//	-------------------------
		case		1:
			if (	(this->m_ItemID != STA_::enm_ItemID::CupCake_1)		&&
					(this->m_ItemID != STA_::enm_ItemID::CupCake_2)		&&
					(this->m_ItemID != STA_::enm_ItemID::CupCake_3)		&&
					(this->m_ItemID != STA_::enm_ItemID::CupCake_4)		&&
					(this->m_ItemID != STA_::enm_ItemID::CupCake_5)		)	
			{
				return		true;
			}
			else
			{
				return		false;
			}
			break;

		//	-------------------------
		//		Can be fused?
		//	-------------------------
		case		2:
			if (	(this->m_ItemID == STA_::enm_ItemID::CupCake_1)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_2)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_3)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_4)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_5)		)	
			{
				return		false;
			}
			else
			{
				return		true;
			}
			break;

		//	-------------------------
		//			Can fall?
		//	-------------------------
		case		3:
			if (	(this->m_ItemID == STA_::enm_ItemID::CupCake_1)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_2)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_3)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_4)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_5)		)
			{
				return		false;
			}
			else
			{
				return		true;
			}
			break;

			
		//	--------------------------
		//		Cannot be switched?
		//	--------------------------
		case		4:
			if (	(this->m_ItemID == STA_::enm_ItemID::CupCake_1)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_2)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_3)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_4)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_5)		)
			{
				return		true;
			}
			else
			{
				return		false;
			}
			break;

		//	-------------------------
		//		Can be painted?
		//	-------------------------
		case		5:
			if (	(this->m_ItemID == STA_::enm_ItemID::CupCake_1)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_2)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_3)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_4)		||
					(this->m_ItemID == STA_::enm_ItemID::CupCake_5)		)	
			{
				return		false;
			}
			else
			{
				return		true;
			}
			break;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
		
	}

//	-------------------------------------------
//		[7] HitPoints and health system
//	-------------------------------------------
public:
	inline void		HitOne_HP()
	{
		//	If the candy is invincible, than nothing can stop it!
		if (!this->m_IsInvincible)
		{
			//	If the candy shows to be on a liquorice cage,
			//	Then the candy will have a little extra HP
			//	(because of the cage). The liquorice cage is the first one
			//	to be damaged, then the actual candy.
			if (this->m_HasLiquoriceCage)
			{
				//	If the cage is still alive, then hit it.
				if (this->m_LiquoriceCageHP > 0)
				{
					this->m_LiquoriceCageHP = this->m_LiquoriceCageHP - 1.0;
				}

				//	If the cage has not HP left, then the candy
				//	has no more a liquorice cage.
				if (this->m_LiquoriceCageHP <= 0)
				{
					this->m_HasLiquoriceCage = false;
					this->m_LiquoriceCageHP = 0;
				}

				return;
			}

			//	At the end, checks for the actual candy.
			//	The proper member that stores the HP of the candy
			//	is ObjectHitPoints, but the candy also has its
			//	HP, for example a six-layer cupcake has six hitpoints,
			//	and when the game request for the HP of the candy, a function
			//	will return the sum of its parts (liquorice cage HP, InitialHP, and all).
			if (this->m_InitialHP > 0)
			{
				this->m_InitialHP = this->m_InitialHP - 1;

				if (this->m_InitialHP <= 0)
				{
					this->m_InitialHP = 0;
				}
			}			
		}
	}
	inline void		AddOne_HP(int _Which)
	{
		//	With _Which I mean if you would like to add one HP to
		//	the liquorice cage or maybe the actual candy...
		switch (_Which)
		{
		case 1:
			this->m_InitialHP = this->m_InitialHP + 1;
	
			if (this->m_InitialHP <= 0.0)
			{
				this->m_InitialHP = 0.0;
			}
				
			break;

		case 2:
			if (this->m_HasLiquoriceCage)
			{
				this->m_LiquoriceCageHP = this->m_LiquoriceCageHP + 1;

				if (this->m_HasLiquoriceCage <= 0.0)
				{
					this->m_HasLiquoriceCage = false;
					this->m_LiquoriceCageHP = 0.0;
				}
			}

			break;
		}
	}

	inline double		g_InitialHP()
	{
		return		(this->m_InitialHP);
	}
	inline double		g_TotalHP()
	{
		return (this->m_InitialHP + this->m_LiquoriceCageHP);
	}


	inline void			s_ObjectHitPoints(int _Which, double _objectHitPoints)
	{
		//	Just like AddOne_HP function, you will choose which
		//	HP property to set (liquorice cage, initialHP, ...).
		switch (_Which)
		{
		case 1:
			this->m_InitialHP = _objectHitPoints;

			if (this->m_InitialHP <= 0.0)
				this->m_InitialHP = 0.0;

			break;

		case 2:
			if (this->m_HasLiquoriceCage)
			{
				if (this->m_HasLiquoriceCage > 0.0)
					this->m_LiquoriceCageHP = _objectHitPoints;

				if (this->m_HasLiquoriceCage <= 0.0)
				{
					this->m_HasLiquoriceCage = false;
					this->m_LiquoriceCageHP = 0.0;
				}
			}

			break;
		}	
	}

	inline void			s_Blocker(	int Which	)
	{
		//	Set the blocker of a candy.
		switch (	Which	)
		{
		//	Licorice cage.
		case	1:
			this->m_HasLiquoriceCage	= true;
			this->m_LiquoriceCageHP		= 1.0;

			break;
		}	
	}
	inline bool			g_HasBlocker(int _Which)
	{
		switch (_Which)
		{
		case	1:
			return		((this->m_HasLiquoriceCage) && (this->m_LiquoriceCageHP > 0.0));

		case	def::enm_Defines::_SEARCH_ALL:
			return		( (g_HasBlocker(1)) );

		default:
			return		false;
		}
	}

//	-------------------------------------------
//		[8] Physics and more gravity stuff
//	-------------------------------------------
public:
	inline void		PhysicObject(double& _Ground)
	{
		this->m_IsFalling = false;
	
		//	Checks if the object can fall and is not going sideways.
		{
			if (this->m_CanFall && !this->m_IsSideWays)
			{
				// Here is the gravity condition.
				{
					//	Fall until it reaches the ground !
					if ((this->yP + (this->yS * _Controller_Logic::_fdTime_) - this->_H) > _Ground)
					{
						//	For the speed.
						this->yS = this->yS + (this->_Gravity_ * _Controller_Logic::_fdTime_);
	
						//	For the position
						this->yP = this->yP + (this->yS * _Controller_Logic::_fdTime_);
	
						//	Fix also (position)...
						{
							if (	(this->yP + (this->yS * _Controller_Logic::_fdTime_) - this->_H) < _Ground	)
							{
								this->yP		= _Ground + this->_H;
							}
						}
					}		
					//	Else, make it bounce.
					else
					{
						//	---------------------------------------------------------------------
						//		Once the candy (or object in general) has reached the ground,
						//			it should bounce. Starts bouncing and stop falling.
						//	---------------------------------------------------------------------
						{
							this->m_IsFalling	= false;
							this->m_IsBouncing	= true;
	
							if (	!this->m_RoofHit	)
							{
								this->yP		= _Ground + this->_H;
							}
						}
	
						//	---------------------------------------------------------------------
						//		Then, the ySpeed of the object will become positive (going up)
						//						and start falling again...
						//	---------------------------------------------------------------------
						{
							this->yS = (this->yS / -this->m_Bounciness);
	
							//	If ySpeed is greater than the constant of bouncing,
							//	that means that the object is indeed falling
							//	and not bouncing.
							if (fabs(this->yS) > this->_BouncingChecker_)
							{
								this->m_IsFalling	= true;
								this->m_IsBouncing	= false;
							}						
						}
	
	
						//	---------------------------------------------------------------------
						//		Finally, when the object stops falling and continuosly bouncing,
						//		then there will be a limit for it to stop. It is call the... 
						//	---------------------------------------------------------------------
						{
							if (fabs(this->yS) <= this->_BouncingLimit_)
							{
								this->yS = 0.0;
	
								this->m_IsBouncing = false;
								this->m_IsFalling = false;
							}
						}
					}
	
	
					//	This if checks whether the candy is falling.
					{
						if ((fabs(this->yS) >= this->_MatchingSensibility_))
						{
							this->m_IsFalling = true;
						}
					}
				}
			}
			else
			{
				this->m_IsFalling	= false;
				this->yS			= 0.0;
			}
		}
	}

	inline void		UpdateGravityState(int _GravityDirection)
	{
		this->s_GravityDirection(1, _GravityDirection);
	}

	inline void		s_GravityDirection(int _Which, int _Val)
	{
		switch (_Which)
		{
		case 1:
			this->m_GravityDirection = _Val;
		}
	}
	inline int		g_GravityDirection(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return		this->m_GravityDirection;

		default:
			return		-1;
		}
	}

	inline void		SetRoofHit(		bool Value	)
	{
		this->m_RoofHit		= Value;
	}
	inline bool		GetRoofHit()
	{
		return		this->m_RoofHit;
	}

	inline bool		ObjectIsStatic()
	{
		return	(							this->g_HasBlocker(1)							||
						(	(STA_::enm_ItemID::CupCake_1 <= this->m_ItemID)		&& 
							(this->m_ItemID <= STA_::enm_ItemID::CupCake_5)		)			||
					((this->yS == 0.0) && (!this->m_IsSideWays) && (!this->m_IsSwapping))	);
	}

//	-------------------------------------------
//		[9] About its crushed particles
//	-------------------------------------------
public:
	inline void			CalculateCrushedAngle(double _xP, double _yP)
	{
		this->m_CrushedAngle = tls::FindAngle(_xP, _yP, this->xP + (this->_W_Sprite * 0.5), this->yP - (this->_H_Sprite * 0.5), false);
	}
	inline void			SetCrushedAngle(double _Angle)
	{
		this->m_CrushedAngle = _Angle;
	}
	inline void			s_ExtraSpeed(double _xS, double _yS)
	{
		this->m_ExtraSpeed = this->m_ExtraSpeed + (tls::DoPhytagoras(_xS, _yS) / 7.5);
	}
	inline void			s_DropCrush(bool _Val)
	{
		this->m_DropCrush = _Val;
	}
	inline void			s_LinkerProspform(TheCandy* _MyPtr)
	{
		this->m_LinkerProspform = _MyPtr;
	}

	inline double		g_CrushingProperties(int _What)
	{
		switch (_What)
		{
		case	1:
			return		this->m_CrushedAngle;

		case	2:
			return		this->m_ExtraSpeed;
		}
	}
	inline bool			g_DropCrush()
	{
		return this->m_DropCrush;
	}
	inline TheCandy*	g_LinkerProspform()
	{
		return this->m_LinkerProspform;
	}
};
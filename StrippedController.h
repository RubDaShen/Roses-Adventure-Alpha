#pragma once

#include		"Tools_.h"
#include		"AfterGlows.h"
#include		"_MyIncludes_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"SpecialMixes.h"
#include		"LogicalController.h"

#include		<vector>



class		AnimatedObject : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_SpawnCommand
	{
		None				= 0,

		HorizontalSides		= 1,
		JustLeft			= 2,
		JustRight			= 3,
		VerticalSides		= 4,
		JustUp				= 5,
		JustDown			= 6,
		CrossSign			= 7,

		Big_HorizontalSides		= 20,
		Big_VerticalSides		= 21,
		Big_CrossSign			= 22,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_LifeTime_First	= 0.3;
	double			m_LifeTime_Second	= 0.075;
	double			m_DelayEnd			= 0.0;
	double			m_InnerTime			= 0.0;

	double			xP_Des			= 0.0, yP_Des = 0.0;
	double			xP_Des_Second	= 0.0, yP_Des_Second = 0.0;

	bool			m_End					= false;
	bool			m_SpawnPureLight		= false;
	bool			m_LightExplodes			= false;

	int				m_EnteredSecondPhase	= def::enm_Triggers::Waiting;

	int				m_KindID		= 0;
	int				m_ItemID		= 0;
	int				m_MixID			= 0;

	int				m_SwitchOrder			= 0;
	int				m_SwitchDirection		= 0;
	int				m_SpawnCommand			= 0;

	int				m_Horz_Cross_Kind		= 0;
	int				m_Vert_Cross_Kind		= 0;

//	-------------------------------------------
//				Linking and More
//	-------------------------------------------
private:
	TheCandy*		m_Linker	= nullptr;
	int				m_UniqueID	= def::enm_Defines::_NOT_INITIALIZED;






//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	AnimatedObject(		TheCandy* _My_, TheCandy* _Destiny_		,
						bool _HomogeneousMix, int sMixID			, 
						int _SpawnCommand, bool _SpawnPureLight		) : thyObject(_My_->g_PositionPrp(1), _My_->g_PositionPrp(2), def::enm_ObjectType::StrippedTraits_AnimatedObject)
	{
		using			sMx = SpecialMixWrapper::enm_SpecialMix;

		bool			_Static_ = false;
		double			_OffSet_ = 45.0;

		

		//	Vars.
		{
			this->xP_Des	= this->xP;
			this->yP_Des	= this->yP;

			this->_W		= _My_->g_MeasuresPrp(1);
			this->_H		= _My_->g_MeasuresPrp(2);
		}
		
		//	IDs.
		{
			//	Candy properties.
			this->m_KindID			= _My_->g_KindID();
			this->m_ItemID			= _My_->g_ItemID();
			this->m_SpawnCommand	= _SpawnCommand;
			this->m_SpawnPureLight	= _SpawnPureLight;

			if (	this->m_SpawnCommand == enm_SpawnCommand::CrossSign	)
			{
				if (	_My_->g_ItemID() == STA_::enm_ItemID::StrippedH	)
				{
					this->m_Horz_Cross_Kind			= _My_->g_KindID();
					this->m_Vert_Cross_Kind			= _Destiny_->g_KindID();
				}
				else
				{
					this->m_Horz_Cross_Kind			= _Destiny_->g_KindID();
					this->m_Vert_Cross_Kind			= _My_->g_KindID();
				}
			}

			//	Switching properties.
			this->m_SwitchOrder		= _My_->g_SwitchOrder();
			this->m_SwitchDirection	= _My_->g_SwapDirection();
			this->m_MixID			= sMixID;

			//	Real candy linkings.
			this->m_Linker			= _Destiny_;	
			this->m_UniqueID		= this->m_Linker->g_ObjectID();
		}

		//	Depending on the mix, do different animations.
		switch (	sMixID	)
		{
		case	sMx::StrippedH_StrippedH:		
		case	sMx::StrippedH_StrippedV:
		case	sMx::StrippedH_WrappedFuse:
			//	First movement.
			{
				//	Homogeneous mix means if both candies are
				//	of the same type (ItemID).
				if (		_HomogeneousMix		)
				{ 
					switch (	_My_->g_SwapDirection()		)
					{
					case	def::enm_Directions::Up:
						this->yP_Des = this->yP - _OffSet_;
						break;

					case	def::enm_Directions::Down:
						this->yP_Des = this->yP + _OffSet_;							
						break;

					case	def::enm_Directions::Left:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->xP_Des	= this->xP + _OffSet_;
						}
						else
						{
							_Static_	= true;
						}
						break;

					case	def::enm_Directions::Right:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->xP_Des	= this->xP - _OffSet_;
						}
						else
						{
							_Static_	= true;
						}
						break;
					}
				}
				else
				{
					_Static_		= true;

					switch (	_My_->g_SwapDirection()	)
					{
					case	def::enm_Directions::Up:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->yP_Des = this->yP - _OffSet_;
						}
						break;

					case	def::enm_Directions::Down:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->yP_Des	= this->yP + _OffSet_;
						}	
						break;

					case	def::enm_Directions::Left:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->xP_Des	= this->xP + _OffSet_;
						}
						break;

					case	def::enm_Directions::Right:
						if (	_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::First	)
						{
							this->xP_Des	= this->xP - _OffSet_;
						}
						break;
					}
				}
			}

			//	Second movement.
			{
				this->xS	= (_Destiny_->g_PositionPrp(1) - this->xP_Des) / (GAME_LOOP_VALUE * this->m_LifeTime_Second);
				this->yS	= (_Destiny_->g_PositionPrp(2) - this->yP_Des) / (GAME_LOOP_VALUE * this->m_LifeTime_Second);
			


				if (	_HomogeneousMix		)
				{
					if ((	(_My_->g_SwapDirection() == def::enm_Directions::Left) || (_My_->g_SwapDirection() == def::enm_Directions::Right))	&&
														(_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::Second)							)
					{
						this->xS = this->yS = 0.0;
					}
				}
				else
				{
					if (		_My_->g_SwitchOrder() == Switcher::enm_SwitchingOrder::Second		)
					{
						this->xS = this->yS = 0.0;
					}
				}
			}

			//	Some final touches.
			{
				if (	sMixID == sMx::StrippedH_WrappedFuse	)
				{
					this->m_LightExplodes	=	true;
				}
			}
			
			break;

		case sMx::StrippedH_Wrapped:
			//	Just movements.
			{
				double		_Wrapped_Growth_	= 0.75;

				this->m_LifeTime_First		= 0.1;	
				this->m_LifeTime_Second		= 0.4;



				if (	this->m_SwitchOrder == Switcher::enm_SwitchingOrder::First	)
				{
					this->xS		= (_Destiny_->g_PositionPrp(1) - this->xP_Des) / (GAME_LOOP_VALUE * this->m_LifeTime_First);
					this->yS		= (_Destiny_->g_PositionPrp(2) - this->yP_Des) / (GAME_LOOP_VALUE * this->m_LifeTime_First);
				}
				else
				{
					this->xFctS		= _Wrapped_Growth_ / (GAME_LOOP_VALUE * m_LifeTime_Second);
				}
			}
			
			break;
		}
	}

	~AnimatedObject()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		using			sMx = SpecialMixWrapper::enm_SpecialMix;



		//	Depending on the mix, do different animations.
		switch (	this->m_MixID	)
		{
		case	sMx::StrippedH_StrippedH:		
		case	sMx::StrippedH_StrippedV:
		case	sMx::StrippedH_WrappedFuse:
			//	Position.
			{
				if (	this->m_InnerTime < this->m_LifeTime_First	)
				{
					this->xP	= tls::SmoothMove(this->xP, this->xP_Des, this->m_LifeTime_First * GAME_LOOP_VALUE);
					this->yP	= tls::SmoothMove(this->yP, this->yP_Des, this->m_LifeTime_First * GAME_LOOP_VALUE);
				}
				else
				{
					if (this->m_InnerTime < (this->m_LifeTime_First + this->m_LifeTime_Second))
					{
						this->xP	= this->xP + this->xS;
						this->yP	= this->yP + this->yS;
					}
				}
			}

			break;

		case	sMx::StrippedH_Wrapped:
			//	Animation of the first selected candy.
			{
				//	Movement.
				if (	this->m_InnerTime < this->m_LifeTime_First	)
				{
					this->xP = this->xP + this->xS;
					this->yP = this->yP + this->yS;
				}
				
				//	Triggers.
				{
					//	For second phase.
					if (		(this->m_InnerTime > this->m_LifeTime_First)		)
					{
						if (	this->m_EnteredSecondPhase == def::enm_Triggers::Waiting	)
						{
							this->m_EnteredSecondPhase = def::enm_Triggers::Activated;
						}
						else
						{
							this->m_EnteredSecondPhase		= def::enm_Triggers::NotInitialized;
						}
					}
				}
			}

			//	Animation of the second selected candy.
			{
				if (	this->m_LifeTime_First < this->m_InnerTime	)
				{
					double		_InnerTime_		= (this->m_InnerTime - this->m_LifeTime_First) * GAME_LOOP_VALUE;



					this->xFct		= this->xFct + this->xFctS;
					this->yFct		= this->xFct;

					this->rotationDegree	=	_InnerTime_ * std::cos(_InnerTime_ / 2.0) * 0.4;
				}
			}
			break;
		}
		
		//	LifeTime.
		{
			if (	(this->m_LifeTime_First + this->m_LifeTime_Second + this->m_DelayEnd) < this->m_InnerTime		)
			{
				this->m_End = true;
			}

			this->m_InnerTime		= this->m_InnerTime + (1.0 / GAME_LOOP_VALUE);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline bool			HasEnd()
	{
		return		this->m_End;
	}
	inline bool			g_SpawnPureLight()
	{
		return		this->m_SpawnPureLight;
	}
	inline bool			g_LightExplodes()
	{
		return		this->m_LightExplodes;
	}

	inline int			g_SpritePosition(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		(this->xP + (this->_W * 0.5));

		case 2:
			return		(this->yP - (this->_H * 0.5));
		}
	}
	inline int			g_KindID()
	{
		return		this->m_KindID;
	}
	inline int			g_ItemID()
	{
		return			this->m_ItemID;
	}
	inline int			g_MixID()
	{
		return		this->m_MixID;
	}
	inline int			g_Switches(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_SwitchDirection;

		case 2:
			return		this->m_SwitchOrder;
		}
	}
	inline int			g_SpawnCommand()
	{
		return		this->m_SpawnCommand;
	}
	inline int			g_CrossKind(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		this->m_Horz_Cross_Kind;

		case 2:
			return		this->m_Vert_Cross_Kind;
		}
	}

	inline double		g_Time()
	{
		return		this->m_InnerTime;
	}	
	inline bool			g_EnteredCertainPhase(	int WhatPhase	)
	{
		switch (	WhatPhase	)
		{
		case 2:
			return		(this->m_EnteredSecondPhase == def::enm_Triggers::Activated);

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	inline TheCandy*		g_Linker()
	{
		if (	this->m_UniqueID == this->m_Linker->g_ObjectID()	)
		{
			return		this->m_Linker;
		}
		
		return		nullptr;
	}
};
class		StrippedLightningParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Important values
//	-------------------------------------------
private:
	double			_Speed_				= 0.212;
	double			_Aceleration_		= 0.3451;

	double			_GridBound_		= 90.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_KindID		= def::enm_Defines::_NOT_INITIALIZED;
	int				m_Direction		= def::enm_Defines::_NOT_INITIALIZED;
	int				m_iPos			= def::enm_Defines::_NOT_INITIALIZED;
	int				m_jPos			= def::enm_Defines::_NOT_INITIALIZED;

	double			m_SpriteOffSet_X	= 0.0;
	double			m_SpriteOffSet_Y	= 0.0;

	double			m_xHitBoxPos		= 0.0;
	double			m_yHitBoxPos		= 0.0;

	double			m_InnerTime			= 0.0;
	double			m_LightExplodesAt	= 0.275;
	double			m_Expladious		= 2.0;

	bool			m_PureLight			= false;
	bool			m_CollisionForAll	= false;
	bool			m_LightExplodes		= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	StrippedLightningParticle(	double _xP, double _yP				, 
								int _KindID, int _Direction			,	
								tls::Vec2<int> _Pos					,
								bool _PureLight						,
								tls::Vec2<double> Scale				,
								tls::Vec2<double> HitBoxPosition	,
								bool LightExplodes					,
								bool CollisionForAll				) : thyObject(_xP, _yP, def::enm_ObjectType::StrippedLightningParticle)
	{
		//	Direction:
		//		1.	Up
		//		2.	Down
		//		3.	Left
		//		4.	Right


		//	Important values.
		{
			this->m_KindID				= _KindID;
			this->m_Direction			= _Direction;
			this->m_PureLight			= _PureLight;
			this->m_CollisionForAll		= CollisionForAll;
			this->m_LightExplodes		= LightExplodes;

			this->_W			= 60.0 * Scale.First;
			this->_H			= 60.0 * Scale.Second;

			this->xFct			= Scale.First;
			this->yFct			= Scale.Second;

			this->m_iPos		= _Pos.First;
			this->m_jPos		= _Pos.Second;

			this->m_xHitBoxPos	= HitBoxPosition.First;
			this->m_yHitBoxPos	= HitBoxPosition.Second;

			if (	this->m_PureLight	)
			{
				this->m_KindID		= STA_::enm_KindID::_White;
			}


			tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);
		}

		//	Position.
		{
			this->xP	= _xP;
			this->yP	= _yP;

			this->xS	= this->xA = 0.0;
			this->yS	= this->yA = 0.0;



			switch (this->m_Direction)
			{
			case		def::enm_Directions::Up:			
				this->yS				= this->_Speed_;
				this->yA				= this->_Aceleration_;

				this->rotationDegree	= 0.0;

				this->m_SpriteOffSet_X		= 0.0;
				this->m_SpriteOffSet_Y		= 0.0;


				break;

			case		def::enm_Directions::Down:
				this->yS				= -this->_Speed_;
				this->yA				= -this->_Aceleration_;

				this->rotationDegree	= 180.0;

				this->m_SpriteOffSet_X		= 0.0;
				this->m_SpriteOffSet_Y		= 0.0;


				break;

			case		def::enm_Directions::Left:
				this->xS				= -this->_Speed_;
				this->xA				= -this->_Aceleration_;

				this->rotationDegree	= -90.0;

				this->m_SpriteOffSet_X		= 0.0;
				this->m_SpriteOffSet_Y		= 0.0;


				break;

			case		def::enm_Directions::Right:
				this->xS = this->_Speed_;
				this->xA = this->_Aceleration_;

				this->rotationDegree = 90.0;

				this->m_SpriteOffSet_X		= 0.0;
				this->m_SpriteOffSet_Y		= 0.0;


				break;
			}
		}
	}

	~StrippedLightningParticle()
	{

	}

//	-------------------------------------------
//					Functions !
//	-------------------------------------------
public:
	inline void			DoParticle()
	{
		//	Position.
		{
			this->xP = this->xP + (this->xS * _Controller_Logic::_fdTime_);
			this->xS = this->xS + (this->xA * _Controller_Logic::_fdTime_);
								  
			this->yP = this->yP + (this->yS * _Controller_Logic::_fdTime_);
			this->yS = this->yS + (this->yA * _Controller_Logic::_fdTime_);
		}

		//	InnerTime.
		{
			this->m_InnerTime		= this->m_InnerTime + (_Controller_Logic::_fdTime_ / _Controller_Logic::_ogLpV_);
		}
	}

//	-------------------------------------------
//				Setters and Getters !
//	-------------------------------------------
public:
	inline void			s_ID(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			 this->m_KindID = _Val;
			 break;
		}
	}

	inline int			g_ID(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_KindID;

		case 2:
			return		this->m_Direction;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
		
	}
	inline int			g_Pos(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_iPos;

		case 2:
			return this->m_jPos;
		}
	}
	inline double		g_OffSet(int _What)
	{
		//	OffSet is just the additional value when the sprite 
		//	moved due to rotation, scaling, etc.

		switch (_What)
		{
		case 1:
			return		this->m_SpriteOffSet_X;

		case 2:
			return		this->m_SpriteOffSet_Y;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline int			g_SpritePosition(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		this->xP + this->g_OffSet(1);

		case 2:
			return		this->yP + this->g_OffSet(2);

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	inline double		g_HitBoxPosition(int What)
	{
		switch (	What	)
		{
		case 1:
			return		this->m_xHitBoxPos;

		case 2:
			return		this->m_yHitBoxPos;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline bool			g_CollisionForAll()
	{
		return		this->m_CollisionForAll;
	}
	inline bool			g_LightExplodes()
	{
		if (	this->m_LightExplodes	)
		{
			if (	this->m_LightExplodesAt < this->m_InnerTime	)
			{
				return		true;
			}
		}

		return		false;
	}
	inline double		g_Expladious()
	{
		return		this->m_Expladious;
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
class		_Controller_Stripped
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Remember		= 0,
		_Sparkle		= 1,
		_Lightning		= 2,
		_Mixes			= 3,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double		_LightningWidth_	= 60.0;
	double		_LightningHeight_	= 60.0;

	double		_GridBound_			= 90.0;

//	-------------------------------------------
//				Containers
//	-------------------------------------------
private:
	std::vector<StrippedLightningParticle*>		m_Lightning;
	std::vector<GlowParticle*>					m_Sparkles;
	std::vector<GlowParticle*>					m_RememberStarLights;

	std::vector<AnimatedObject*>				m_AnimatedObjects;

//	-------------------------------------------
//				Anima-variables
//	-------------------------------------------
private:
	int			Rnd_Sparkle				= 2;

	int			Rnd_FadeSparkle_From	= 1;
	int			Rnd_FadeSparkle_To		= 17;

	int			Rnd_Amt_From			= 1;
	int			Rnd_Amt_To				= 1;

	double		Tme_RememberStarLight			= 1.85;	
	double		Amt_Grow_RememberStarLight		= 3.25;

//	-------------------------------------------
//					Special Mixes
//	-------------------------------------------
private:
	double		m_WrappedStripped_Size			= 1.3;
	double		m_WrappedStripped_DistBetw		= 90.0;

//	-------------------------------------------
//					Auxiliars
//	-------------------------------------------
private:
	int			_MyAux_				= 0;
	int			_Container_Size_	= 0;
	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;

//	-------------------------------------------
//				External and Linkers
//	-------------------------------------------
private:
	DrawFactory*		_Draw_			= nullptr;
	SpriteFactory*		_Sprites_		= nullptr;
	SoundFactory*		_Sound_			= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_Stripped(	double _GridWidth, double _GridHeight				,
							DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	, 
							SoundFactory* _Sound_Ptr							)	
	{
		this->_GridBound_	= _GridWidth;
		this->_GridBound_	= _GridWidth;

		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sound_		= _Sound_Ptr;
	}

	~_Controller_Stripped()
	{
		//	Deleting CrushingParticle !
		{
			while (!this->m_Lightning.empty())
			{
				delete this->m_Lightning[0];
				this->m_Lightning.erase(this->m_Lightning.begin() + 0);
			}
		}

		//	Deleting Sparkles !
		{
			while (!this->m_Sparkles.empty())
			{
				delete this->m_Sparkles[0];
				this->m_Sparkles.erase(this->m_Sparkles.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddLightning(	double _xP, double _yP, int _KindID, int _Direction		, 
										tls::Vec2<int> _Pos, bool _PureLight					, 
										tls::Vec2<double> _Scale 								,
										tls::Vec2<double> _HitBox								,
										bool LightExplodes, bool CollisionForAll = false		)
	{	
		this->m_Lightning.push_back(	new StrippedLightningParticle(	_xP, _yP, _KindID, _Direction		,
																		_Pos, _PureLight, _Scale, _HitBox	,
																		LightExplodes, CollisionForAll		)	);
	}
	inline void			AddSparkle(StrippedLightningParticle* _Lightning_Ptr)
	{
		if (	!tls::Random(0, Rnd_Sparkle / _Controller_Logic::_fdTime_)	)
		{
			double			_RandAngle_ = tls::DegToRad(	tls::Random(0, 360)		);
			this->_MyAux_ = tls::Random(this->Rnd_Amt_From, this->Rnd_Amt_To);



			for (	int i = 0; 
					i < this->_MyAux_;
					++i	)
			{
				this->m_Sparkles.push_back(		new GlowParticle(	_Lightning_Ptr->g_PositionPrp(1) + _Lightning_Ptr->g_HitBoxPosition(1)		,
																	_Lightning_Ptr->g_PositionPrp(2) + _Lightning_Ptr->g_HitBoxPosition(2)		,
																	AnmGlow::StrippedSparkle			,
																	AnmGlow::StrippedSparkle			,
																	_Lightning_Ptr->g_ID(1)				)	);



				//	Applying a little position changing.
				{
					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_PositionPrp(	1,	this->m_Sparkles[this->m_Sparkles.size() - 1]->g_PositionPrp(1) + 
																						(tls::Random(0, 40) * std::cos(_RandAngle_)	)		);
					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_PositionPrp(	2,	this->m_Sparkles[this->m_Sparkles.size() - 1]->g_PositionPrp(2) + 
																						(tls::Random(0, 40) * std::sin(_RandAngle_)	)		);
				}

				//	Setting all up.
				{
					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Pos_WithContainer(			tls::Vec4<double>(	_Lightning_Ptr->g_PositionPrp(3) / 2.5	, 
																													_Lightning_Ptr->g_PositionPrp(4) / 2.5	,
																													0.0, 0.0								)	);

					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Opacity_WithContainer(		tls::Vec3<double>(	255.0																		, 
																													-(tls::Random(this->Rnd_FadeSparkle_From, this->Rnd_FadeSparkle_To) / 10.0)	,
																													0.0																			)	);

					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Rotation_WithContainer(	tls::Vec3<double>(	0.0																			, 
																													_Lightning_Ptr->g_PositionPrp(3) + _Lightning_Ptr->g_PositionPrp(4)		,
																													0.0																		)	);

					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Visual_WithContainer(		tls::Vec2<double>(	1.0 - (tls::Random(0, 5) * 0.1), 0.0	)	);
				}
			}
		}
	}
	inline void			AddRememberStarLight(double _xP, double _yP, int _KindID)
	{
		this->m_RememberStarLights.push_back(	new GlowParticle(_xP, _yP, GlowID::StarLightRemember, AnmGlow::StaticGlow, _KindID)				);
		this->m_RememberStarLights[this->m_RememberStarLights.size() - 1]->s_ColorPrp(	6, -255.0 / (GAME_LOOP_VALUE * Tme_RememberStarLight)	);
		this->m_RememberStarLights[this->m_RememberStarLights.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(0.75, this->Amt_Grow_RememberStarLight / (GAME_LOOP_VALUE * Tme_RememberStarLight)));
	}

	inline void			AddSpecialMix(		SpecialMixWrapper* _Wrapper	)
	{
		using			sMx = SpecialMixWrapper::enm_SpecialMix;
		using			spC = AnimatedObject::enm_SpawnCommand;

		TheCandy*	_First_		= _Wrapper->g_Pointers(0);
		TheCandy*	_Second_	= _Wrapper->g_Pointers(1);



		switch (	_Wrapper->g_SpecialMixID()	)
		{
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//			Stripped Horizontal + Stripped Horizontal
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		case sMx::StrippedH_StrippedH:
			{
				int			_Spawn_Command_First_		= spC::None,	_Spawn_Command_Second_		= spC::None;
				bool		_Spawn_PureLight_First_		= false,		_Spawn_PureLight_Second_	= false;
				


				//	Spawning selection (What objects spawn).	
				{
					if (	(_First_->g_SwapDirection() == def::enm_Directions::Left)		||
							(_First_->g_SwapDirection() == def::enm_Directions::Right)		)
					{
						_Spawn_Command_Second_		= spC::HorizontalSides;
						_Spawn_PureLight_Second_	= true;
					}
					else
					{
						_Spawn_Command_First_		= spC::HorizontalSides;
						_Spawn_Command_Second_		= spC::HorizontalSides;
					}
				}



				//	First to Second.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_First_, _Second_, true, sMx::StrippedH_StrippedH	,
																				_Spawn_Command_First_, _Spawn_PureLight_First_		)	);

				//	Second to First.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_Second_, _First_, true, sMx::StrippedH_StrippedH	,
																				_Spawn_Command_Second_, _Spawn_PureLight_Second_	)	);
			}
			break;

		case sMx::StrippedH_StrippedV:
			{
				int			_Spawn_Command_First_		= spC::None,	_Spawn_Command_Second_		= spC::None;
				bool		_Spawn_PureLight_First_		= false,		_Spawn_PureLight_Second_	= false;
				


				//	Spawning selection (What objects spawn).	
				{
					_Spawn_Command_Second_		= spC::CrossSign;
				}



				//	First to Second.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_First_, _Second_, false, sMx::StrippedH_StrippedV	,
																				_Spawn_Command_First_, _Spawn_PureLight_First_		)	);

				//	Second to First.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_Second_, _First_, false, sMx::StrippedH_StrippedV	,
																				_Spawn_Command_Second_, _Spawn_PureLight_Second_	)	);
			}
			break;

		case sMx::StrippedH_Wrapped:
			{
				int			_Spawn_Command_First_		= spC::None,	_Spawn_Command_Second_		= spC::None;
				bool		_Spawn_PureLight_First_		= false,		_Spawn_PureLight_Second_	= false;
				


				//	Spawning selection (What objects spawn).	
				{
					if (	(_First_->g_ItemID() == STA_::enm_ItemID::StrippedH)		||	
							(_Second_->g_ItemID() == STA_::enm_ItemID::StrippedH)		)
					{
						_Spawn_Command_Second_		= spC::Big_HorizontalSides;
					}
					else
					{
						_Spawn_Command_Second_		= spC::Big_VerticalSides;
					}
				}


				//	First to Second.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_First_, _Second_, false, sMx::StrippedH_Wrapped	,
																				_Spawn_Command_First_, _Spawn_PureLight_First_		)	);

				//	Second to First.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_Second_, _First_, false, sMx::StrippedH_Wrapped	,
																				_Spawn_Command_Second_, _Spawn_PureLight_Second_	)	);
			}
			break;

		case sMx::StrippedH_WrappedFuse:
			{
				int			_Spawn_Command_First_		= spC::None,	_Spawn_Command_Second_		= spC::None;
				bool		_Spawn_PureLight_First_		= false,		_Spawn_PureLight_Second_	= false;
				


				//	Spawning selection (What objects spawn).	
				{
					if (	(_First_->g_ItemID() == STA_::enm_ItemID::StrippedH)		||	
							(_Second_->g_ItemID() == STA_::enm_ItemID::StrippedH)		)
					{
						_Spawn_Command_Second_		= spC::HorizontalSides;
					}
					else
					{
						_Spawn_Command_Second_		= spC::VerticalSides;
					}
				}


				//	First to Second.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_First_, _Second_, false, sMx::StrippedH_WrappedFuse	,
																				_Spawn_Command_First_, _Spawn_PureLight_First_			)	);

				//	Second to First.
				this->m_AnimatedObjects.push_back(		new AnimatedObject(		_Second_, _First_, false, sMx::StrippedH_WrappedFuse	,
																				_Spawn_Command_Second_, _Spawn_PureLight_Second_		)	);
			}
			break;
		}
	}



	inline void			Animate()
	{
		using			sMx = SpecialMixWrapper::enm_SpecialMix;
		using			spC = AnimatedObject::enm_SpawnCommand;



		//	Sparkles and glows.
		for (	int i = 0;
				i < this->m_Sparkles.size();
				++i	)
		{
			//	Moving sparkle.
			{
				this->m_Sparkles[i]->AnimateParticle();
			}

			//	Erasing sparkle.
			{
				if (											(this->m_Sparkles[i]->g_ColorPrp(4)	   <= 0.0)										|| 
						(	(this->m_Sparkles[i]->g_PositionPrp(1) <= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::LeftBorder) - 100.0))	||
							(this->m_Sparkles[i]->g_PositionPrp(1) >= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::RightBorder) + 100.0))	||
							(this->m_Sparkles[i]->g_PositionPrp(2) <= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Floor) - 100.0))		||
							(this->m_Sparkles[i]->g_PositionPrp(2) >= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Cieling) + 100.0))		)	)
				{
					tls::EraseElement<GlowParticle*>(this->m_Sparkles, i);
				}
			}
		}
	
		//	The remember-me glow.
		for (	int i = 0;
				i < this->m_RememberStarLights.size();
				++i	)
		{
			this->m_RememberStarLights[i]->AnimateParticle();

			if (this->m_RememberStarLights[i]->g_ColorPrp(4) <= 0.0)
			{
				tls::EraseElement(this->m_RememberStarLights, i);
			}
		}

		//	Special mixes.
		{
			for (	int i = 0;
					i < this->m_AnimatedObjects.size();
					++i	)
			{
				//	Movement.
				this->m_AnimatedObjects[i]->Animate();

				//	Triggers.
				{
					switch (	this->m_AnimatedObjects[i]->g_MixID()	)
					{
					case		sMx::StrippedH_Wrapped:
						//	Play Sound.
						{
							if (	this->m_AnimatedObjects[i]->g_EnteredCertainPhase(2)	)
							{
								this->_Sound_->Play(	snd::SndSys::Wrapped, 2		);
							}
						}
						break;
					}
				}

				//	..Clear..
				if (	(this->m_AnimatedObjects[i]->HasEnd())		)
				{
					TheCandy*		_Candy_ = this->m_AnimatedObjects[i]->g_Linker();



					//	About deleting the original candies.
					{
						if (	_Candy_ != nullptr	)
						{
							_Candy_->s_InstaDelete(true);
						}
					}

					//	What should the animated object trigger?
					{
						if (	_Candy_ != nullptr	)
						{
							bool		_PlaySound_			= true;
							bool		_PureLight_			= false;
							bool		_LightExplodes_		= false;



							//	Just pure light!
							_PureLight_			= this->m_AnimatedObjects[i]->g_SpawnPureLight();
							_LightExplodes_		= this->m_AnimatedObjects[i]->g_LightExplodes();

							//	Just spawns!
							switch (	this->m_AnimatedObjects[i]->g_SpawnCommand()	)
							{
							case	spC::None:
								_PlaySound_		= false;
								break;

							case	spC::HorizontalSides:
								{
									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															_Candy_->g_KindID(), def::enm_Directions::Left								,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);

									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															_Candy_->g_KindID(), def::enm_Directions::Right								,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);
								}
								break;

							case	spC::VerticalSides:
								{
									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															_Candy_->g_KindID(), def::enm_Directions::Up								,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);

									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															_Candy_->g_KindID(), def::enm_Directions::Down								,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);
								}
								break;

							case	spC::CrossSign:
								{
									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															this->m_AnimatedObjects[i]->g_CrossKind(1), def::enm_Directions::Up			,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);

									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															this->m_AnimatedObjects[i]->g_CrossKind(1), def::enm_Directions::Down		,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);

									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															this->m_AnimatedObjects[i]->g_CrossKind(2), def::enm_Directions::Left		,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);

									this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)						,
															_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)						,
															this->m_AnimatedObjects[i]->g_CrossKind(2), def::enm_Directions::Right		,
															tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																				_Candy_->g_Pos(2)	)									,
															_PureLight_, tls::Vec2<double>(1.0, 1.0)									,				
															tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0						, 
																				this->g_LightningMeasures(2) / 2.0						),
															_LightExplodes_																);
								}
								break;

							case	spC::Big_HorizontalSides:
								{
									//	Three to the left.
									{
										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)									,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0) + m_WrappedStripped_DistBetw		,
																_Candy_->g_KindID(), def::enm_Directions::Left											,
																tls::Vec2<int>(		_Candy_->g_Pos(1) - 1	,
																					_Candy_->g_Pos(2)		)											,
																_PureLight_, tls::Vec2<double>(		1.0, 1.0	)										,		
																tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0									, 
																					this->g_LightningMeasures(2) / 2.0									),
																_LightExplodes_																			);

										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)									,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0) - m_WrappedStripped_DistBetw		,
																_Candy_->g_KindID(), def::enm_Directions::Left											,
																tls::Vec2<int>(		_Candy_->g_Pos(1) + 1	,
																					_Candy_->g_Pos(2)		)								 			,
																_PureLight_, tls::Vec2<double>(		1.0, 1.0	)										,	
																tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0									, 
																					this->g_LightningMeasures(2) / 2.0									),
																_LightExplodes_																			);

										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)									,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)									,
																_Candy_->g_KindID(), def::enm_Directions::Left											,
																tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																					_Candy_->g_Pos(2)	)												,
																_PureLight_, tls::Vec2<double>(	this->m_WrappedStripped_Size	, 
																								this->m_WrappedStripped_Size	)						,
																tls::Vec2<double>(	-this->g_LightningMeasures(1, this->m_WrappedStripped_Size) / 2.0	, 
																					this->g_LightningMeasures(2, this->m_WrappedStripped_Size) / 2.0	),
																_LightExplodes_																			);
									}
									
									//	And another three to the right.
									{
										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)										,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0) + this->m_WrappedStripped_DistBetw	,
																_Candy_->g_KindID(), def::enm_Directions::Right												,
																tls::Vec2<int>(		_Candy_->g_Pos(1) - 1,
																					_Candy_->g_Pos(2)	)													,
																_PureLight_, tls::Vec2<double>(		1.0, 1.0	)											,		
																tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0										,
																					this->g_LightningMeasures(2) / 2.0										),
																_LightExplodes_																				);

										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)										,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0) - this->m_WrappedStripped_DistBetw	,	
																_Candy_->g_KindID(), def::enm_Directions::Right												,
																tls::Vec2<int>(		_Candy_->g_Pos(1) + 1,
																					_Candy_->g_Pos(2)	)													,
																_PureLight_, tls::Vec2<double>(		1.0, 1.0	)											,		
																tls::Vec2<double>(	-this->g_LightningMeasures(1) / 2.0										,
																					this->g_LightningMeasures(2) / 2.0										),
																_LightExplodes_																				);

										this->AddLightning(		_Candy_->g_PositionPrp(1) + (this->_GridBound_ / 2.0)										,
																_Candy_->g_PositionPrp(2) - (this->_GridBound_ / 2.0)										,
																_Candy_->g_KindID(), def::enm_Directions::Right												,
																tls::Vec2<int>(		_Candy_->g_Pos(1)	,
																					_Candy_->g_Pos(2)	)													,
																_PureLight_, tls::Vec2<double>(	this->m_WrappedStripped_Size	, 
																								this->m_WrappedStripped_Size	)							,		
																tls::Vec2<double>(	-this->g_LightningMeasures(1, this->m_WrappedStripped_Size) / 2.0		,
																					this->g_LightningMeasures(2, this->m_WrappedStripped_Size) / 2.0		),
																_LightExplodes_																				);
									}

									//	Sound of explosion.
									{
										this->_Sound_->Play(	snd::SndSys::Wrapped, 3		);
										this->_Sound_->Play(	snd::SndSys::Wrapped, 3		);

										this->_Sound_->Play(	snd::SndSys::Stripped, 2	);
										this->_Sound_->Play(	snd::SndSys::Stripped, 2	);
									}
								}
								break;
							}

							//	Just sound!
							if (	_PlaySound_		)
							{
								this->_Sound_->Play(snd::SndSys::Stripped, 2);
							}
						}
					}

					//	Deleting the animated object.
					tls::EraseElement(this->m_AnimatedObjects, i);
				}
			}
		}
	}



	inline void			Draw(	int	What	)
	{
		//	Remember
		if (	enm_Draw::_Remember == What		)
		{
			this->_Container_Size_		= this->m_RememberStarLights.size();
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_What_Kind_			= GlowID::StarLightRemember;



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				//	Draw the sparkle.
				{
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_RememberStarLights[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(this->m_RememberStarLights[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))	);

					//	Applying color properties. 
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_RememberStarLights[i]->g_ColorPrp(1)	,
																														this->m_RememberStarLights[i]->g_ColorPrp(2)	, 
																														this->m_RememberStarLights[i]->g_ColorPrp(3)	, 
																														this->m_RememberStarLights[i]->g_ColorPrp(4)	)	);

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_RememberStarLights[i]->g_VisualPrp(1)	,
																												this->m_RememberStarLights[i]->g_VisualPrp(2)	);



					this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
				}
			}
		}

		//	Sparkle.
		if (	enm_Draw::_Sparkle == What		)
		{
			this->_Container_Size_		= this->m_Sparkles.size();
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_What_Kind_			= 4;

			int			_OffSet_x		= 5.0;
			int			_OffSet_y		= -5.0;





			//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			//			For every sparkle object, also draw an inslight.
			//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				//	Draw the sparkle.
				{
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_Sparkles[i]->g_PositionPrp(1) + (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Third / 2.0), this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(this->m_Sparkles[i]->g_PositionPrp(2) - (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Fourth / 2.0), this->_Draw_->g_WorldBounds(2))	);

					//	Applying color properties.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_Sparkles[i]->g_ColorPrp(1)	,
																														this->m_Sparkles[i]->g_ColorPrp(2)	, 
																														this->m_Sparkles[i]->g_ColorPrp(3)	, 
																														this->m_Sparkles[i]->g_ColorPrp(4)	)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Sparkles[i]->g_RotationPrp(1)	);

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Sparkles[i]->g_VisualPrp(1)	,
																												this->m_Sparkles[i]->g_VisualPrp(2)	);



					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
				}

				//	Inslight
				{
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(5)->setPosition(	tls::FixPos_X(this->m_Sparkles[i]->g_PositionPrp(1) + (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(5).Third / 2.0) + _OffSet_x, this->_Draw_->g_WorldBounds(1))		,
																								tls::FixPos_Y(this->m_Sparkles[i]->g_PositionPrp(2) - (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(5).Fourth / 2.0) + _OffSet_y, this->_Draw_->g_WorldBounds(2))		);

					//	Applying color properties.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(5)->setColor(		sf::Color(255.0, 255.0, 255.0, this->m_Sparkles[i]->g_ColorPrp(4))	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(5)->setRotation(	this->m_Sparkles[i]->g_RotationPrp(1)	);

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(5)->setScale(		this->m_Sparkles[i]->g_VisualPrp(1)	,
																								this->m_Sparkles[i]->g_VisualPrp(2)	);



					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(5));
				}
			}
		}

		//	Draw the lightning.
		if (	enm_Draw::_Lightning == What	)
		{
			this->_What_Sprite_				= spr::enm_At::GlowParticles;
			this->_Container_Size_			= this->m_Lightning.size();



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				//			For every lighning object, also draw an inslight.
				//		An inslight is the white glow inside the lightning object.
				//						Just to be clear.
				//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

				//	Lightning.
				{
					
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(2)->setPosition(		tls::FixPos_X(this->m_Lightning[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																									tls::FixPos_Y(this->m_Lightning[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

					//	Applying color properties.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(2)->setColor(sf::Color(	this->m_Lightning[i]->g_ColorPrp(1)	,
																										this->m_Lightning[i]->g_ColorPrp(2)	,
																										this->m_Lightning[i]->g_ColorPrp(3)	,
																										this->m_Lightning[i]->g_ColorPrp(4)	)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(2)->setRotation(	this->m_Lightning[i]->g_RotationPrp(1)	);

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(2)->setScale(		this->m_Lightning[i]->g_VisualPrp(1)	,
																								this->m_Lightning[i]->g_VisualPrp(2)	);



					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(2));
				}

				//	Inslight
				{
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(3)->setPosition(		tls::FixPos_X(this->m_Lightning[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																									tls::FixPos_Y(this->m_Lightning[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(3)->setRotation(	this->m_Lightning[i]->g_RotationPrp(1));

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(3)->setScale(		this->m_Lightning[i]->g_VisualPrp(1)	,
																								this->m_Lightning[i]->g_VisualPrp(2)	);





					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(3));
				}
			}
		}
		
		//	Draw the animations.
		if (	enm_Draw::_Mixes == What	)
		{
			double			_AlphaGlow_ = 0.0;

			this->_Container_Size_			= this->m_AnimatedObjects.size();



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				this->_What_Kind_		= this->m_AnimatedObjects[i]->g_KindID() - 1;



				//	Just the glow of the candy.
				{
					this->_What_Sprite_		= spr::enm_At::CandiesGlow;



					//	About candy glow.
					_AlphaGlow_				= 255.0;

					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(	this->m_AnimatedObjects[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))	,
																													tls::FixPos_Y(	this->m_AnimatedObjects[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))	);

					//	Applying color properties.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	tls::GetPunctualRGB(this->m_AnimatedObjects[i]->g_KindID(), 1)	,
																															tls::GetPunctualRGB(this->m_AnimatedObjects[i]->g_KindID(), 2)	,
																															tls::GetPunctualRGB(this->m_AnimatedObjects[i]->g_KindID(), 3)	,
																															_AlphaGlow_						)	);
					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_AnimatedObjects[i]->g_VisualPrp(1)	,
																												this->m_AnimatedObjects[i]->g_VisualPrp(2)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(		this->m_AnimatedObjects[i]->g_RotationPrp(1)	);



					this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)	);
				}

				//	Draw the candy.
				{
					this->_What_Sprite_			= spr::enm_At::Candies + this->m_AnimatedObjects[i]->g_ItemID() - 1;



					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_AnimatedObjects[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(this->m_AnimatedObjects[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))	);

					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_AnimatedObjects[i]->g_VisualPrp(1)	,
																												this->m_AnimatedObjects[i]->g_VisualPrp(2)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_AnimatedObjects[i]->g_RotationPrp(1)	);



					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));			
				}
			}
		}
		
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<StrippedLightningParticle*>&			g_Vec_Lightning()
	{
		return this->m_Lightning;
	}

	inline double			g_LightningMeasures(	int _What, double _ExtraFactor = 1.0	)
	{
		switch (_What)
		{
		case 1:
			return		(this->_LightningWidth_ * _ExtraFactor);

		case 2:
			return		(this->_LightningHeight_ * _ExtraFactor);

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
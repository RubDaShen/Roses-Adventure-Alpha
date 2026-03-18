#pragma once

#include		"Tools_.h"
#include		"_MyIncludes_.h"
#include		"TheCandy.h"
#include		"AfterGlows.h"
#include		"SoundFactory.h"
#include		"Scores.h"
#include		"LogicalController.h"

#include		<vector>



class		FishBubbles : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	float		m_LifeTime = 0.0f;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FishBubbles(tls::Vec2<double> _Position) : thyObject(_Position.First, _Position.Second, def::enm_ObjectType::FishBubble)
	{
		this->m_LifeTime	= tls::Random(10, 20) * 0.2f;



		this->Alpha_s	= -255.0 / (this->m_LifeTime * GAME_LOOP_VALUE);
		this->xFctS		= -1.0 / (this->m_LifeTime * GAME_LOOP_VALUE);
		this->yS		= tls::Random(2, 6) * 0.2;
		
		this->_W		= this->_H = 39.0;
	}

	~FishBubbles()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateBubble()
	{
		//	Position 
		this->yP		= this->yP + (this->yS * _Controller_Logic::_fdTime_);

		//	Opacity.
		this->A_alpha	= this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

		//	Shrinking.
		this->xFct		= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
		this->yFct		= this->xFct;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		(this->xP + (this->_W * 0.5));

		case	2:
			return		(this->yP + (this->_H * 0.5));

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
class		FishTargetParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double			$_SpriteMeasures = 100.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_When			= 0;

	bool			m_RotDirection	= false;
	bool			m_End			= false;
	bool			m_Queued		= false;

	float			m_TimeShrink	= 0.5f;
	double			m_InnerTime		= 0.0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	FishTargetParticle(double _xP, double _yP, int _ID) : thyObject(_xP, _yP, def::enm_ObjectType::FishTarget)
	{
		this->xP			= this->xP + ((90.0 - $_SpriteMeasures) / 2.0);
		this->yP			= this->yP - ((90.0 - $_SpriteMeasures) / 2.0);
		this->ObjectID		= _ID;



		this->m_RotDirection	= tls::Random(0, 1);

		this->rotationSpeed		= (this->m_RotDirection * -1) + 3.0;
		this->xFct				= this->yFct = 0.0;

		this->A_alpha			= 0.0;

		this->_W				= 100.0;
		this->_H				= 100.0;
	}

	~FishTargetParticle()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		AnimateTarget()
	{
		//	Spinning.
		{
			this->rotationDegree		= this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
		}

		//	Opacity.
		{
			if (!this->m_End && (this->m_InnerTime < (_Controller_Logic::_ogLpV_ * m_TimeShrink)))
			{
				this->A_alpha = this->A_alpha + ((255.0 / (_Controller_Logic::_ogLpV_ * m_TimeShrink)) * _Controller_Logic::_fdTime_);
			}
			else
			{
				if (	this->m_End	)
				{
					this->A_alpha = this->A_alpha - ((255.0 / (_Controller_Logic::_ogLpV_ * m_TimeShrink)) * _Controller_Logic::_fdTime_);
				}
			}
		}

		//	Shrinking.
		{
			if (!this->m_End && (this->m_InnerTime < (_Controller_Logic::_ogLpV_ * m_TimeShrink)))
			{
				this->xFct		= 0.5 + ((std::sin(tls::DegToRad(270.0) + ((this->m_InnerTime * _Pi_) / (GAME_LOOP_VALUE * 0.5f)) ) / 2.0));
				this->yFct		= this->xFct;
			}
			else
			{
				if (this->m_End)
				{
					this->xFct		= 0.5 + ((std::sin(tls::DegToRad(90.0) + (((this->m_InnerTime - this->m_When) * _Pi_) / (GAME_LOOP_VALUE * 0.5f)) ) / 2.0));
					this->yFct		= this->xFct;
				}
			}
		}



		this->m_InnerTime = this->m_InnerTime + (1.0 * _Controller_Logic::_fdTime_);
		if (this->m_Queued)
		{
			this->m_End = true;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_End(bool _Val)
	{
		if (this->m_InnerTime > (_Controller_Logic::_ogLpV_ * m_TimeShrink))
		{
			this->m_End		= _Val;
			this->m_When	= this->m_InnerTime;
		}

		this->m_Queued		= _Val;
	}
	inline bool			g_End()
	{
		return		this->m_End;
	}

	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return			(this->xP + (this->_W * 0.5));

		case	2:
			return			(this->yP - (this->_H * 0.5));

		default:
			return			def::enm_Defines::_NOT_FOUND;
		}
	}
};
/*	||	 ||
	|| J ||
	|| O ||
	|| I ||
	|| N ||
	||	 ||	*/
class		FishEntity : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const float			$_AngVar = 90.0;

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	TheCandy*				_Linker_	= nullptr;
	int						_Linker_UniqueID = 0;

	FishTargetParticle*		_Target_	= nullptr;
	int						_Target_UniqueID = 0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int					m_FishType	= 0;
	int					m_FishKind	= 0;
	int					m_Defined	= 0;
	double				m_InnerTime = 0;

	int					_SignDirection_		= 0;
	double				_InternAngle_		= 0.0;
	double				_CenterAngle_		= 0.0;
	double				_Distance_			= 0.0;
	double				_Radious_			= 0.0;
	double				_SpriteAngle_		= 0.0;

	bool				m_HasArrived = false;

//	-------------------------------------------
//				Positional values
//	-------------------------------------------
private:
	double				m_xCenter	= 0.0, m_yCenter = 0.0;
	double				m_xTarget	= 0.0, m_yTarget = 0.0;
	double				m_xOrg		= 0.0, m_yOrg = 0.0;
	double				m_LifeTime	= 1.56;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FishEntity(	double _xP, double _yP, int _KindID, int _FishType	, 
				TheCandy* _Linker, FishTargetParticle* _Target		) : thyObject(_xP, _yP, def::enm_ObjectType::FishEntity)
	{
		//	Linkers and more...
		{
			this->_Linker_			= _Linker;
			this->_Linker_UniqueID	= this->_Linker_->g_ObjectID();

			this->_Target_			= _Target;
			this->_Target_UniqueID	= this->_Target_->g_ObjectID();

			//	std::cout << "Fish created with TargetID = " << this->_Target_UniqueID << " and Address = " << this->_Linker_ << "\n";
		}

		//	Setting all up.
		{
			this->m_FishKind	= _KindID;
			this->m_FishType	= _FishType;


			this->m_xTarget		= _Linker->g_PositionPrp(1);
			this->m_yTarget		= _Linker->g_PositionPrp(2);
			this->m_xOrg		= _xP;
			this->m_yOrg		= _yP;
			
			this->_W			= this->_H = 60.0;
		}

		//	Sprite Measures.
		{
			this->_W_Sprite		= 125;
			this->_H_Sprite		= 100;
		}
	}

	~FishEntity()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateFish()
	{
		this->m_InnerTime		= this->m_InnerTime + (1 * _Controller_Logic::_fdTime_);



		//	Position values.
		{
			this->xP = this->m_xCenter + (this->_Radious_ * std::cos(this->_CenterAngle_));
			this->yP = this->m_yCenter + (this->_Radious_ * std::sin(this->_CenterAngle_));
		}

		//	Increase or decrease the angle.
		{
			this->_CenterAngle_		= this->_CenterAngle_ + ((this->_SignDirection_ * (tls::DegToRad(90.0) / (_Controller_Logic::_ogLpV_ * this->m_LifeTime))) * _Controller_Logic::_fdTime_);
			this->_InternAngle_		= this->_InternAngle_ + ((this->_SignDirection_ * (tls::DegToRad(90.0) / (_Controller_Logic::_ogLpV_ * this->m_LifeTime))));

			this->_SpriteAngle_		= this->_SpriteAngle_ + ((this->_SignDirection_ * (90.0 / (_Controller_Logic::_ogLpV_ * this->m_LifeTime))) * _Controller_Logic::_fdTime_);


			//	Now this part is about the sprite rotations.
			{
				this->rotationDegree	= this->_SpriteAngle_;



				//	Fixes for sprite ('x' scaling).
				if (this->m_Defined == 0)
				{
					if (	((90.0 <= this->rotationDegree) && (this->rotationDegree <= 270.0))	)
					{
						this->rotationDegree	= 180.0 - this->rotationDegree;					
						this->xFct				= -1;
						this->m_Defined			= 1;
					}
					else
					{
						this->rotationDegree	= 360.0 - this->rotationDegree;
						this->xFct				= 1;
						this->m_Defined			= 2;
					}
				}
				else
				{
					switch (this->m_Defined)
					{
					case 1:
						this->rotationDegree	= 180.0 - this->rotationDegree;					
						this->xFct				= -1;

						break;

					case 2:
						this->rotationDegree	= 360.0 - this->rotationDegree;
						this->xFct				= 1;

						break;
					}
				}			

				//	And 'y' scaling.
				if (this->_SignDirection_ == -1)
				{
					this->yFct = 1;
				}
			}			
		}

		//	Has reached the destiny?
		{
			//	if (	(std::fabs(static_cast<int>(this->xP) - static_cast<int>(this->m_xTarget)) <= 2 )	&&
			//			(std::fabs(static_cast<int>(this->yP) - static_cast<int>(this->m_yTarget)) <= 2	)	)
			if (	this->m_LifeTime <= (this->m_InnerTime / _Controller_Logic::_ogLpV_)	)
			{
				//	Checking if the candy is still alive to untarget it.
				if (	this->_Linker_->g_ObjectID() == this->_Linker_UniqueID	)
				{
					this->_Linker_->s_TargetedByFish(false);
				}



				this->m_HasArrived = true;
			}
		}

		//	About the target.
		{
			//	Checking if the target is still alive...
			if (	this->GetTarget() != nullptr	)
			{
				//	Fish has arrived destiny.
				if (this->m_HasArrived)
				{
					this->_Target_->s_End(true);
				}

				//	Or candy was already destroyed.
				if (this->_Linker_->g_ObjectID() != this->_Linker_UniqueID)
				{
					this->_Target_->s_End(true);
				}
			}
		}
	}
	inline void			DoCalculus()
	{
		if (this->$_AngVar != 90.0)
		{
			return;
		}



		//	Sign Direction calculation (+-).
		{
			this->_SignDirection_ = ((tls::Random(0, 1)) ? 1 : -1);
		}
		
		//	Distance calculation (m).
		{
			this->_Distance_ = tls::DoPhytagoras(	this->m_yTarget - this->yP	,
													this->m_xTarget - this->xP	);
		}
		
		//	Radious calculation (r).
		{
			this->_Radious_ = (std::sqrt(2.0) / 2.0) * this->_Distance_;
		}
		
		//	Angle calculation (theta).
		{
			this->_InternAngle_ = tls::FindAngle(this->xP, this->yP, this->m_xTarget, this->m_yTarget, true) + (tls::DegToRad(45.0) * this->_SignDirection_);
		}

		//	Center calculation (O).
		{
			this->m_xCenter = this->m_xOrg + (this->_Radious_ * std::cos(this->_InternAngle_));
			this->m_yCenter = this->m_yOrg + (this->_Radious_ * std::sin(this->_InternAngle_));
		}

		//	Center Angle calculation (alpha).
		{
			this->_CenterAngle_ = tls::FindAngle(this->m_xCenter, this->m_yCenter, this->m_xOrg, this->m_yOrg, true);
		}

		//	Sprite purposes.
		{
			this->_SpriteAngle_ = tls::FindAngle(this->m_xOrg, this->m_yOrg, this->m_xTarget, this->m_yTarget, false) - (45.0 * this->_SignDirection_);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline FishTargetParticle*		GetTarget()
	{
		if (	this->_Target_ != nullptr	)
		{
			if (	this->_Target_UniqueID == this->_Target_->g_ObjectID()	)
			{
				return		this->_Target_;
			}
			else
			{
				//	std::cout << "The target with TargetID = " << this->_Target_UniqueID << " got nullified.\n";
				this->_Target_		= nullptr;
			}
		}
			
		return		this->_Target_;
	}

	inline int						g_FishPrp(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_FishType;

		case 2:
			return		this->m_FishKind;

		case 3:
			return		this->m_InnerTime;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}	
	}
	inline bool						g_HasArrived()
	{
		return this->m_HasArrived;
	}
	inline tls::Vec2<double>		g_BodyPosition()
	{
		return	tls::Vec2<double>(	this->xP + 60.0	,
									this->yP - 45.0	);
	}
	
	inline int						g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		(this->xP + (this->_W_Sprite * 0.5));

		case	2:
			return		(this->yP - (this->_H_Sprite * 0.5));

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
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
class _Controller_Fish
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
		_FishTarget		= 0,
		_Sparkmoke		= 1,
		_Bubbles		= 2,
		_JellyFish		= 3,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<FishEntity*>			m_Fishes;
	std::vector<FishBubbles*>			m_Bubbles;
	std::vector<FishTargetParticle*>	m_Targets;
	std::vector<GlowParticle*>			m_Sparkmoke;

//	-------------------------------------------
//				Variables and constants
//	-------------------------------------------
private:
	std::vector<int>		_LicoriceCage_Pool_;
	std::vector<int>		_Cupcakes_Pool_;
	std::vector<int>		_Available_Pool_;

	float			_SpriteSpin_			= 32.0f;
	float			_DistanceFromBody_		= 15.0f;

//	-------------------------------------------
//					Amima-riables
//	-------------------------------------------
private:
	float			Tme_BubblesSpawn			= 0.25f;

	int				Rnd_Sparkmoke				= 9;
	int				Rnd_Amt_To_Sparkmoke		= 3;
	int				Rnd_LifeTime_From_Sparkmoke = 17;
	int				Rnd_LifeTime_To_Sparkmoke	= 25;

	int				Cnt_TargetsID	= 1;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	SoundFactory*			_Sound_		= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	ShaderFactory*			_Shader_	= nullptr;

	_Controller_Score*		_Scores_	= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_Fish(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr			,	
						SoundFactory* _Sound_Ptr, ShaderFactory* _Shader_Ptr		,
						_Controller_Score* _Score_Ptr		)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sound_		= _Sound_Ptr;
		this->_Shader_		= _Shader_Ptr;

		this->_Scores_		= _Score_Ptr;
	}
	
	~_Controller_Fish()
	{
		//	Deleting Fishes Entities !
		{
			while (!this->m_Fishes.empty())
			{
				delete this->m_Fishes[0];
				this->m_Fishes.erase(this->m_Fishes.begin() + 0);
			}
		}

		//	Deleting Fish Bubbles !
		{
			while (!this->m_Bubbles.empty())
			{
				delete this->m_Bubbles[0];
				this->m_Bubbles.erase(this->m_Bubbles.begin() + 0);
			}
		}

		//	Deleting Fish Targets !
		{
			while (!this->m_Targets.empty())
			{
				delete this->m_Targets[0];
				this->m_Targets.erase(this->m_Targets.begin() + 0);
			}
		}

		//	Deleting Fish Sparkmokes !
		{
			while (!this->m_Sparkmoke.empty())
			{
				delete this->m_Sparkmoke[0];
				this->m_Sparkmoke.erase(this->m_Sparkmoke.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				AddFish(		TheCandy* _Fish_Ptr				, 
											std::vector<TheCandy*>& _Candies	)
	{
		int			_Where_				= def::enm_Defines::_NOT_FOUND;
		int			_AtPos_				= 0;
		bool		_Target_Correct_	= false;
	


		//	Fish AI.
		{
			//	Creating all the pool.
			{
				int		_Container_Size_	= _Candies.size();


				this->_LicoriceCage_Pool_.clear();
				this->_Cupcakes_Pool_.clear();
				this->_Available_Pool_.clear();


				
				//	Licorice cages.
				for (	int i = 0; 
						i < _Container_Size_; 
						++i	)
				{
					//	Licorice Cage pool.
					if (				(_Candies[i]->g_HasBlocker(1))						&&
							(_Candies[i]->g_ItemID() != STA_::enm_ItemID::WrappedFuse)		&&
										(!_Candies[i]->g_TargetedByFish())					)
					{
						this->_LicoriceCage_Pool_.push_back(i);
						continue;
					}

					//	Cupcake pool.
					if (	(STA_::enm_ItemID::CupCake_1 <= _Candies[i]->g_ItemID())	&&
							(_Candies[i]->g_ItemID() <= STA_::enm_ItemID::CupCake_5)	&&
										(!_Candies[i]->g_TargetedByFish())				)
					{
						this->_Cupcakes_Pool_.push_back(i);
						continue;
					}

					//	Candies pool.
					if (	(_Candies[i]->g_ItemID() != STA_::enm_ItemID::WrappedFuse)			&&
												(!_Candies[i]->g_BoB_Is(2))						&&
								(_Candies[i]->g_ObjectID() != _Fish_Ptr->g_ObjectID())			&&
											(_Candies[i]->g_TotalHP() > 0)						&&
						(	(0 <= _Candies[i]->g_Pos(1)) && (0 <= _Candies[i]->g_Pos(2))	)	&&
										(!_Candies[i]->g_TargetedByFish())						)
					{ 
						this->_Available_Pool_.push_back(i);
						continue;
					}
				}
			}



			//	------------------------=
			//	Priority!
			//		1.	Licorice cages.
			//		2.	Cupcakes.
			//		3.	Random Candies.
			
			//	---------------------------------
			//			Priority Level 1. 
			//			Licorice cages
			//	---------------------------------
			{
				while (		!_Target_Correct_	)
				{
					if (	this->_LicoriceCage_Pool_.empty()	)
					{
						_AtPos_				= def::enm_Defines::_NOT_FOUND;
						_Target_Correct_	= false;

						break;
					}

					_Where_				= tls::Random(0, this->_LicoriceCage_Pool_.size() - 1);
					_AtPos_				= this->_LicoriceCage_Pool_[_Where_];
					_Target_Correct_	= true;
				}
			}

			//	---------------------------------
			//			Priority Level 2. 
			//				Cupcakes
			//	---------------------------------
			{
				while (		!_Target_Correct_	)
				{
					if (this->_Cupcakes_Pool_.empty())
					{
						_AtPos_				= def::enm_Defines::_NOT_FOUND;
						_Target_Correct_	= false;

						break;
					}

					_Where_				= tls::Random(0, this->_Cupcakes_Pool_.size() - 1);
					_AtPos_				= this->_Cupcakes_Pool_[_Where_];
					_Target_Correct_	= true;
				}
			}

			//	---------------------------------
			//			Priority Level 3. 
			//				Candies
			//	---------------------------------
			{
				while (		!_Target_Correct_	)
				{
					if (	this->_Available_Pool_.empty()	)
					{
						_AtPos_				= def::enm_Defines::_NOT_FOUND;
						_Target_Correct_	= false;

						break;
					}

					_Where_				= tls::Random(0, this->_Available_Pool_.size() - 1);
					_AtPos_				= this->_Available_Pool_[_Where_];
					_Target_Correct_	= true;
				}
			}
		}


		//	Creating the fish and its target.
		{
			if (	_AtPos_ != def::enm_Defines::_NOT_FOUND	)
			{			
				//	Adding fish and target.
				{
					this->m_Targets.push_back(	new FishTargetParticle(	_Candies[_AtPos_]->g_PositionPrp(1)	,
																		_Candies[_AtPos_]->g_PositionPrp(2)	,
																		Cnt_TargetsID						)	);
					++Cnt_TargetsID;



					this->m_Fishes.push_back(	new FishEntity(	_Fish_Ptr->g_PositionPrp(1), _Fish_Ptr->g_PositionPrp(2)	, 
																_Fish_Ptr->g_KindID(), 1, _Candies[_AtPos_]					,
																this->m_Targets[this->m_Targets.size() - 1]					)	);
				}

				//	Setting all up.
				{
					//	Fishy.
					this->m_Fishes[this->m_Fishes.size() - 1]->DoCalculus();

					//	Candy.
					_Candies[_AtPos_]->s_TargetedByFish(true);
				}
			}
		}
	}
	inline void				AddBubble(		FishEntity* _Fishy	)
	{
		if (	(_Fishy->g_FishPrp(3) % (static_cast<int>(this->Tme_BubblesSpawn * _Controller_Logic::_gLpVal_))) == 0	)
		{
			this->m_Bubbles.push_back(	new FishBubbles(	_Fishy->g_BodyPosition()	)	);
		}
	}
	inline void				AddSparkmoke(	FishEntity* _Fishy	)
	{
		if (!tls::Random(0, this->Rnd_Sparkmoke / _Controller_Logic::_fdTime_))
		{
			int			_Times_ = tls::Random(1, this->Rnd_Amt_To_Sparkmoke);



			for (	int i = 0; 
					i < _Times_; 
					++i	)
			{
				float		_Angle_		= tls::DegToRad(tls::Random(0, 360));
				float		_LifeTime_	= tls::Random(this->Rnd_LifeTime_From_Sparkmoke, this->Rnd_LifeTime_To_Sparkmoke) / 10.0;




				this->m_Sparkmoke.push_back(	new GlowParticle(	_Fishy->g_BodyPosition().First	+ (std::cos(_Angle_) * this->_DistanceFromBody_),
																	_Fishy->g_BodyPosition().Second + (std::sin(_Angle_) * this->_DistanceFromBody_),
																	GlowID::SparkmokeShort, AnmGlow::StaticGlow	)	);

				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Opacity_WithContainer(	tls::Vec3<double>(	255.0												, 
																												-255.0 / (_LifeTime_ * _Controller_Logic::_ogLpV_)	,
																												0.0												)	);
				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(	1.0													, 
																												-1.0 / (_LifeTime_ * _Controller_Logic::_ogLpV_)	)	);
				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Color_WithKind(			_Fishy->g_FishPrp(2)		);

			}
		}
	}

	inline void				Animate(		std::vector<TheCandy*>& _Candies	)
	{
		//	Fishy fishy.
		for (	int i = 0; 
				i < this->m_Fishes.size();
				++i	)
		{
			this->m_Fishes[i]->AnimateFish();
			this->AddBubble(		this->m_Fishes[i]		);
			this->AddSparkmoke(		this->m_Fishes[i]		);



			//	Deleting when done.
			{
				if (this->m_Fishes[i]->g_HasArrived())
				{
					//	Checking the collision of the fish with any possible candy.
					{
						//	Fishes target candies and when this 
						//	candy is reached by a fish, means 
						//	that the candy is no longer targeted.

						//	Fishes don't make some candies invincibles
						//	since it's only one unique hit.

						int			_Candies_Size = _Candies.size();



						for (	int c = 0; 
								c < _Candies_Size; 
								++c	)
						{
							if (	tls::CollidesWith(	this->m_Fishes[i]->g_PositionPrp(1) + ((90.0 - this->m_Fishes[i]->g_MeasuresPrp(1)) / 2.0)	,
														this->m_Fishes[i]->g_PositionPrp(2) - ((90.0 - this->m_Fishes[i]->g_MeasuresPrp(2)) / 2.0)	,
														this->m_Fishes[i]->g_MeasuresPrp(1), this->m_Fishes[i]->g_MeasuresPrp(2)					,
														_Candies[c]->g_PositionPrp(1), _Candies[c]->g_PositionPrp(2)								,
														_Candies[c]->g_MeasuresPrp(1), _Candies[c]->g_MeasuresPrp(2)								)	)
							{
								if (	(_Candies[c]->g_Pos(1) >= 0)	&&		//	I
										(_Candies[c]->g_Pos(2) >= 0)	&&		//	J
										(!_Candies[c]->g_Is(5))			&&		//	Can't be invincible.
										(_Candies[c]->g_Can(2))			)		//	Can be crushed
								{
									this->_Scores_->AddScore(	_Candies[c]->g_PositionPrp(1)									,
																_Candies[c]->g_PositionPrp(2)									, 
																ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	,
																_Candies[c]->g_KindID()											);


								
									_Candies[c]->s_TargetedByFish(false);										//	Is no longer targeted by fish.
									_Candies[c]->HitOne_HP();													//	Hit one HP.
									_Candies[c]->s_InstaState(	TheCandy::enm_InstaState::EatenByFish	);		//	State.
								}


								break;
							}	
						}
					}



					//	Delete the fish entity.
					tls::EraseElement<FishEntity*>(this->m_Fishes, i);
				}
			}
		}

		//	Bubbles.
		for (	int i = 0;
				i < this->m_Bubbles.size();
				++i	)
		{
			this->m_Bubbles[i]->AnimateBubble();



			//	Deleting when done.
			{
				if (	this->m_Bubbles[i]->g_ColorPrp(4) <= 0.0	)
				{
					tls::EraseElement<FishBubbles*>(this->m_Bubbles, i);
				}
			}
		}

		//	Sparkmoke (Sparkle + Smoke).
		for (	int i = 0;
				i < this->m_Sparkmoke.size();
				++i	)
		{
			this->m_Sparkmoke[i]->AnimateParticle();



			//	Deleting when done.
			{
				if (	this->m_Sparkmoke[i]->g_ColorPrp(4) <= 0.0	)
				{
					tls::EraseElement<GlowParticle*>(this->m_Sparkmoke, i);
				}
			}
		}

		//	Targets.
		for (	int i = 0; 
				i < this->m_Targets.size();
				++i	)
		{
			this->m_Targets[i]->AnimateTarget();



			//	Deleting when done.
			{
				if (	(this->m_Targets[i]->g_ColorPrp(4) <= 0.0)	&&
						(this->m_Targets[i]->g_End())				)
				{
					tls::EraseElement<FishTargetParticle*>(this->m_Targets, i);
				}
			}
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void				Draw(	int What	)
	{
		//	Fish Target.
		if (	What == enm_Draw::_FishTarget	)
		{
			this->_What_Sprite_			= spr::enm_At::JellyFish_Contents;
			this->_What_Kind_			= 1;
			this->_Container_Size_		= this->m_Targets.size();



			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Targets[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Targets[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Targets[i]->g_RotationPrp(1)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Targets[i]->g_VisualPrp(1)	,
																											this->m_Targets[i]->g_VisualPrp(2)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Sparkmoke.
		if (	What == enm_Draw::_Sparkmoke	)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_What_Kind_			= GlowID::SparkmokeShort;
			this->_Container_Size_		= this->m_Sparkmoke.size();



			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Sparkmoke[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Sparkmoke[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_Sparkmoke[i]->g_ColorPrp(1)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(2)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(3)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Sparkmoke[i]->g_VisualPrp(1)	,
																											this->m_Sparkmoke[i]->g_VisualPrp(2)	);



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Bubbles.
		if (	What == enm_Draw::_Bubbles		)
		{
			this->_What_Sprite_			= spr::enm_At::JellyFish_Contents;
			this->_What_Kind_			= 0;
			this->_Container_Size_		= this->m_Bubbles.size();



			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Bubbles[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Bubbles[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Bubbles[i]->g_VisualPrp(1)	,
																											this->m_Bubbles[i]->g_VisualPrp(2)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(sf::Color(	this->m_Bubbles[i]->g_ColorPrp(1)	,
																													this->m_Bubbles[i]->g_ColorPrp(2)	,
																													this->m_Bubbles[i]->g_ColorPrp(3)	,
																													this->m_Bubbles[i]->g_ColorPrp(4)	)	);

				

				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Fish.
		if (	What == enm_Draw::_JellyFish	)
		{
			this->_What_Sprite_			= spr::enm_At::JellyFish;
			this->_Container_Size_		= this->m_Fishes.size();



			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_			= this->m_Fishes[i]->g_FishPrp(2) - 1;
				//	((_Fishes_->at(i)->g_FishPrp(1) - 1) * _Sprites_->g_Data(1)) + _Fishes_->at(i)->g_FishPrp(2) - 1



				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Fishes[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Fishes[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Fishes[i]->g_VisualPrp(1)	,
																											this->m_Fishes[i]->g_VisualPrp(2)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(sf::Color(	this->m_Fishes[i]->g_ColorPrp(1)	,
																													this->m_Fishes[i]->g_ColorPrp(2)	,
																													this->m_Fishes[i]->g_ColorPrp(3)	,
																													this->m_Fishes[i]->g_ColorPrp(4)	)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Fishes[i]->g_RotationPrp(1)	);


				//	Usage of shaders.
				{
					this->_Shader_->s_Uniform_SwimmingFish(this->m_Fishes[i]->g_FishPrp(3), tls::Vec4<float>(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getTextureRect().left		,
																												_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getTextureRect().top		,
																												_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getTextureRect().width	,
																												_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getTextureRect().height	)	);
				}
				


				this->_Draw_->DrawShader(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), this->_Shader_->g_Shader(shd::MyShaders::SwimmingFish));
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double			g_SpriteSpin()
	{
		return this->_SpriteSpin_;
	}
	inline bool				g_FishesAreSwimming()
	{
		return	(!this->m_Fishes.empty());
	}
};
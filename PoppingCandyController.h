#pragma once

#include	"Tools_.h"
#include	"_MyIncludes_.h"
#include	"TheCandy.h"
#include	"AfterGlows.h"
#include	"SoundFactory.h"
#include	"Scores.h"
#include	"VisualGridController.h"
#include	"DrawFactory.h"
#include	"SpriteFactory.h"

#include	<vector>



class		PoppingSpawnTracker
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	TheCandy*		_Linker_			= nullptr;
	int				_Linker_UniqueID	= 0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	bool			m_End			= false;
	bool			m_Spawn			= false;

	int				m_PopAmounts	= 0;
	int				m_PopCounter	= 0;

	double			m_Time			= 0.0;
	double			m_DelayBegin	= 0.0, m_DelayEnd = 0.0;

	double			m_TimeEndAt		= 10'000'000.0;
	double			m_TimeIterator	= 0.0;
	double			m_LifeTime		= 0;

//	-------------------------------------------
//				Tracking variables
//	-------------------------------------------
private:
	int				ObjectID		= 0;		//	Understand as m_ObjectID of the tracker.





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	PoppingSpawnTracker(	double _DelayBegin, double _DelayEnd			,
							TheCandy* _Linker, int _Tracker_Unique_ID		,
							int _PopAmount, int _LifeTime_					)
	{
		//	Linkers and external...
		{
			this->_Linker_				= _Linker;
			this->_Linker_UniqueID		= _Linker->g_ObjectID();

			this->ObjectID		= _Tracker_Unique_ID;
		}

		//	About timing and all.
		{
			this->m_DelayBegin		= _DelayBegin;
			this->m_DelayEnd		= _DelayEnd;
			this->m_PopAmounts		= _PopAmount;
		}

		//	About variables.
		{
			this->m_LifeTime		= _LifeTime_ / GAME_LOOP_VALUE;
		}
	}

	~PoppingSpawnTracker()
	{
		this->ObjectID		= def::enm_Defines::_NOT_INITIALIZED;
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		RunTracker()
	{
		//	Random popping.
		{
			//	First, delay begin and then continue.
			if (	this->m_DelayBegin <= this->m_Time	)
			{
				this->m_Spawn		= false;

				//	Second, do stuff...
				{
					//	Adding the pops!
					if (		this->m_Time > this->m_TimeIterator		)
					{
						if (	this->m_PopCounter < this->m_PopAmounts		)
						{
							++this->m_PopCounter;
							this->m_Spawn = true;
						}	
			
						this->m_TimeIterator	= this->m_Time + this->m_LifeTime;
					}
				}

				//	Third, active delay...
				{
					if (	(this->m_DelayEnd + this->m_TimeEndAt) <= this->m_Time	)
					{
						this->m_End		= true;
					}

					//	Checking if end.
					if (	this->m_PopCounter == this->m_PopAmounts	)
					{
						this->m_TimeEndAt	= this->m_Time;
						++this->m_PopCounter;
					}
				}
			}
		}

		//	Time goes by...
		this->m_Time	= this->m_Time + (1.0 / GAME_LOOP_VALUE);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline TheCandy*		g_Linker()
	{
		if (	this->_Linker_UniqueID == this->_Linker_->g_ObjectID()	)
		{
			return		this->_Linker_;
		}
		else
		{
			return		nullptr;
		}		
	}
	inline int				g_Saved_LinkerID()
	{
		return this->_Linker_UniqueID;
	}

	inline bool				g_End()
	{
		return		this->m_End;
	}
	inline bool				g_Spawn()
	{
		return		this->m_Spawn;
	}
};
class		PoppingCracker : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
				
//	-------------------------------------------
//				Positional Variables
//	-------------------------------------------
private:
	const double	$_Gravity		= -9.81;
	double			$_LifeTime		= 0.0;
	double			$_AngleUp_		= 14.0;		//	14.0 is considered normal.

	double			xTarget		= 0.0, yTarget	= 0.0, zTarget	= 0.0;
	double			xOrg		= 0.0, yOrg		= 0.0, zOrg		= 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_KindID		= def::enm_Defines::_NOT_INITIALIZED;

	double			m_Time			= 0.0;
	int				m_InnerTime		= 0;

	bool			m_HasPopped		= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	PoppingCracker(	double _xP, double _yP			,
					int _KindID, double _LifeTime	,
					double _xP_Des, double _yP_Des	) : thyObject(_xP, _yP, def::enm_ObjectType::PoppingCracker)
	{
		this->m_KindID		= _KindID;
		this->_W			= 25, this->_H = 27;



		//	Calculating the position.
		{
			this->$_LifeTime	= _LifeTime;

			this->xOrg		= this->xP;
			this->yOrg		= this->yP;
			this->zOrg		= 0.0;

			this->xTarget	= _xP_Des;
			this->yTarget	= _yP_Des;
			this->zTarget	= 10.0;

			this->xS	= (this->xTarget - this->xP) / this->$_LifeTime;
			this->yS	= ((this->yTarget - this->yP) / (this->$_LifeTime * this->$_AngleUp_)) - (0.5 * this->$_Gravity * this->$_LifeTime * this->$_AngleUp_);
			this->zS	= (this->zTarget - this->zP) / this->$_LifeTime;

			this->rotationSpeed		= tls::Random(2, 6) * tls::UnityRound(std::cos(tls::DegToRad(std::atan(this->yS / this->xS)))) * 2.0;
		}
	}

	~PoppingCracker()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimatePopCracker()
	{
		this->m_HasPopped = false;


		//	Run Run !!!
		{
			//	Calculating the rotation.
			{
				this->rotationDegree = this->rotationDegree + this->rotationSpeed;
			}

			//	Change position.
			{
				this->xP	= this->xOrg + (this->xS * this->m_Time);
				this->yP	= this->yOrg + (this->yS * this->m_Time * this->$_AngleUp_) + (0.5 * this->$_Gravity * this->m_Time * this->m_Time * this->$_AngleUp_ * this->$_AngleUp_);
				this->zP	= this->zOrg + (this->zS * this->m_Time);
			}

			//	If frojectile reached destiny.
			{
				if (	(this->m_Time > this->$_LifeTime)	)
				{
					this->m_HasPopped	= true;
				}
			}

			this->m_Time = this->m_Time + (1.0 / GAME_LOOP_VALUE);
			++this->m_InnerTime;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_InnerTime()
	{
		return		this->m_InnerTime;
	}
	inline int			g_KindID()
	{
		return		this->m_KindID;
	}
	inline bool			g_HasPopped()
	{
		return this->m_HasPopped;
	}

	inline int			g_SpritePosition(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		(this->xP);
			break;

		case 2:
			return		(this->yP);
			break;
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
class		_Controller_PoppingCandy
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
		_PoppingCracker		= 0,
		_Spark				= 1,
	};




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<PoppingSpawnTracker*>		m_Trackers;
	std::vector<PoppingCracker*>			m_PopCrackers;
	std::vector<GlowParticle*>				m_Sparks;

//	-------------------------------------------
//				Variables and constants
//	-------------------------------------------
private:
	int			Cnt_TrackersID			= 0;

	int			m_PopAmount				= 100;
	int			Rnd_SpawnTime_From		= 10,	Rnd_SpawnTime_To = 15;

	int			m_PopCrackerRadiousFrom		= 180;

//	-------------------------------------------
//					Amima-riables
//	-------------------------------------------
private:
	double		m_DelayBegin				= 0.25, m_DelayEnd = 0.85;
	
	int			Rnd_GlowLifeTime_From		= 2;
	int			Rnd_GlowLifeTime_To			= 4;

	double		LifeTime_SharpSpark			= 0.1;

	int			Rnd_PopCrackerLifeTime_From	= 4;
	int			Rnd_PopCrackerLifeTime_To	= 6;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	SoundFactory*			_Sound_			= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;

	_Controller_Score*			_Score_			= nullptr;

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
	_Controller_PoppingCandy(	SoundFactory* _Sound_Ptr		,
								_Controller_Score* _Score_Ptr	,
								DrawFactory* _Draw_Ptr			,
								SpriteFactory* _Sprite_Ptr		)
	{
		this->_Sound_	= _Sound_Ptr;
		this->_Score_	= _Score_Ptr;
		this->_Draw_	= _Draw_Ptr;
		this->_Sprites_ = _Sprite_Ptr;
	}
	
	~_Controller_PoppingCandy()
	{
		tls::DeleteVector(this->m_Trackers);
		tls::DeleteVector(this->m_PopCrackers);
	}

//	-------------------------------------------
//				Spawning functions
//	-------------------------------------------
public:
	inline void			AddTracker(		TheCandy* _PoppingCandy_Linker		)
	{
		//	Adding a tracker using the 
		//	object ID of the popping candy.
		{
			int		_LifeTime_ = tls::Random(	this->Rnd_SpawnTime_From, this->Rnd_SpawnTime_To	);



			++Cnt_TrackersID;
			this->m_Trackers.push_back(	new PoppingSpawnTracker(	this->m_DelayBegin, this->m_DelayEnd		, 
																	_PoppingCandy_Linker, this->Cnt_TrackersID	,
																	this->m_PopAmount, _LifeTime_				)	);
		}

		//	Adjusting the candy properties.
		{
			_PoppingCandy_Linker->s_Ppc_Is(1, true);
			_PoppingCandy_Linker->s_Can(2, false);
			_PoppingCandy_Linker->s_Can(3, false);
		}
	}
	inline void			AddPopCracker(	TheCandy* _PoppingCandy_Linker		)
	{
		double		_xP_ = _PoppingCandy_Linker->g_PositionPrp(1) + (_PoppingCandy_Linker->g_MeasuresPrp(1) * 0.5);
		double		_yP_ = _PoppingCandy_Linker->g_PositionPrp(2) - (_PoppingCandy_Linker->g_MeasuresPrp(2) * 0.5);



		this->m_PopCrackers.push_back(		new PoppingCracker(		_xP_, _yP_, _PoppingCandy_Linker->g_KindID()											,
																	tls::Random(this->Rnd_PopCrackerLifeTime_From, this->Rnd_PopCrackerLifeTime_To)	* 0.1	,
																	_xP_ + (	this->m_PopCrackerRadiousFrom * std::cos(tls::DegToRad(tls::Random(0, 360))))	,
																	_yP_ + (	this->m_PopCrackerRadiousFrom * std::sin(tls::DegToRad(tls::Random(0, 360))))	)	);
	}
	inline void			AddSpark(	PoppingCracker* _PoppingCracker_Linker	)
	{
		//	Glow.
		int		_LifeTime_	= tls::Random(this->Rnd_GlowLifeTime_From, this->Rnd_GlowLifeTime_To);



		this->m_Sparks.push_back(		new GlowParticle(	_PoppingCracker_Linker->g_PositionPrp(1)			,
															_PoppingCracker_Linker->g_PositionPrp(2)			, 
															GlowID::XLGlow, AnmGlow::StaticGlow				)	);

		this->m_Sparks[this->m_Sparks.size() - 1]->s_Color_WithKind(	_PoppingCracker_Linker->g_KindID()	);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_ColorPrp(		1, this->m_Sparks[this->m_Sparks.size() - 1]->g_ColorPrp(1)		);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_ColorPrp(		2, this->m_Sparks[this->m_Sparks.size() - 1]->g_ColorPrp(2)		);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_ColorPrp(		3, this->m_Sparks[this->m_Sparks.size() - 1]->g_ColorPrp(3)		);

		this->m_Sparks[this->m_Sparks.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(0.5, -0.5 / (_LifeTime_ * GAME_LOOP_VALUE * 0.1))			);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_Opacity_WithContainer(	tls::Vec3<double>(255.0, -255.0 / (_LifeTime_ * GAME_LOOP_VALUE * 0.1), 0.0)	);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_Blending(		true		);



		//	Spark.
		_LifeTime_	= tls::Random(this->Rnd_GlowLifeTime_From, this->Rnd_GlowLifeTime_To);



		this->m_Sparks.push_back(		new GlowParticle(	_PoppingCracker_Linker->g_PositionPrp(1)			,
															_PoppingCracker_Linker->g_PositionPrp(2)			, 
															GlowID::SharpSpark, AnmGlow::StaticGlow				)	);

		this->m_Sparks[this->m_Sparks.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(1.0, -1.0 / (this->LifeTime_SharpSpark * GAME_LOOP_VALUE ))			);
		this->m_Sparks[this->m_Sparks.size() - 1]->s_Rotation_WithContainer(	tls::Vec3<double>(	tls::Random(0, 360), 0.0, 0.0)			);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoTrackers(std::vector<TheCandy*>&		_Candies_)
	{
		//	About the trackers.
		for (	int i = 0; 
				i < this->m_Trackers.size(); 
				++i	)
		{
			//	If tracker ends.
			if (	this->m_Trackers[i]->g_End()	)
			{
				//	When a tracker ends, say that candy (the linked one) to
				//	finish its job and get crushed.
				if (	this->m_Trackers[i]->g_Linker() != nullptr		)
				{
					//	Then, as said, the linker candy (in this case the Bom-O-Bom)
					//	will be crushed and die...
					for	(	int c = 0; 
							c < _Candies_.size(); 
							++c	)
					{
						if (	this->m_Trackers[i]->g_Saved_LinkerID() == _Candies_[c]->g_ObjectID()	)
						{
							//	Sound part.
							this->_Sound_->Play(snd::SndSys::PoppingCandy, 3);

							tls::EraseElement<TheCandy*>(_Candies_, c);
							break;
						}
					}
				}

				//	Then, erase the tracker when everything is all done.
				tls::EraseElement(this->m_Trackers, i);
				continue;
			}

			//	If a tracker spawns.
			if (	this->m_Trackers[i]->g_Spawn()	)
			{
				if (	this->m_Trackers[i]->g_Linker() != nullptr	)
				{
					this->AddPopCracker(	this->m_Trackers[i]->g_Linker()		);
				}
			}

			//	Run, tracker, Run!
			{
				this->m_Trackers[i]->RunTracker();
			}
		}
	}

	inline void			Animate(std::vector<TheCandy*>&		_Candies_)
	{
		//	Popping crackers.
		{
			for (	int i = 0; 
					i < this->m_PopCrackers.size(); 
					++i	)
			{
				//	Popping Deletus.
				if (	this->m_PopCrackers[i]->g_HasPopped()	)
				{
					//	Finding the candy to be crushed.
					for (	int j = 0; 
							j < _Candies_.size(); 
							++j	)
					{
						if (	tls::CollidesWith(	this->m_PopCrackers[i]->g_PositionPrp(1), this->m_PopCrackers[i]->g_PositionPrp(2)	,
													this->m_PopCrackers[i]->g_MeasuresPrp(1), this->m_PopCrackers[i]->g_MeasuresPrp(2)	,
													_Candies_[j]->g_PositionPrp(1), _Candies_[j]->g_PositionPrp(2)						,
													_Candies_[j]->g_MeasuresPrp(1), _Candies_[j]->g_MeasuresPrp(2)						)	)
						{
							if (	0 < _Candies_[j]->g_TotalHP()	)
							{
								this->_Score_->AddScore(	_Candies_[j]->g_PositionPrp(1)									,
															_Candies_[j]->g_PositionPrp(2)									,
															ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	,
															_Candies_[j]->g_KindID()										);

								_Candies_[j]->HitOne_HP();

								break;
							}
						}
					}

					//	Add spark.
					this->AddSpark(		this->m_PopCrackers[i]	);

					//	Erase candy.
					tls::EraseElement(	this->m_PopCrackers, i	);

					continue;
				}

				//	Animation.
				this->m_PopCrackers[i]->AnimatePopCracker();
			}
		}

		//	Sparks.
		{
			for (	int i = 0;
					i < this->m_Sparks.size();
					++i	)
			{
				//	Animate.
				this->m_Sparks[i]->AnimateParticle();

				//	Deleting spark.
				if (	this->m_Sparks[i]->g_VisualPrp(1) <= 0.0		)
				{
					tls::EraseElement(this->m_Sparks, i);
				}
			}
		}
	}



	inline void			Draw(	int What	)
	{
		//	Pop Cracker.
		if (	enm_Draw::_PoppingCracker == What	)
		{
			this->_Container_Size_		= this->m_PopCrackers.size();
			this->_What_Sprite_			= spr::enm_At::PoC_Contents;



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				this->_What_Kind_		= this->m_PopCrackers[i]->g_KindID() - 1;



				//	Set the position of the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(this->m_PopCrackers[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(this->m_PopCrackers[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);


				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(		this->m_PopCrackers[i]->g_ColorPrp(1)	,
																															this->m_PopCrackers[i]->g_ColorPrp(2)	,
																															this->m_PopCrackers[i]->g_ColorPrp(3)	,
																															this->m_PopCrackers[i]->g_ColorPrp(4)	)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(		this->m_PopCrackers[i]->g_RotationPrp(1)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Spark & Glow.
		if (		enm_Draw::_Spark == What		)
		{
			this->_Container_Size_		= this->m_Sparks.size();
			this->_What_Sprite_			= spr::enm_At::GlowParticles;



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				this->_What_Kind_		= this->m_Sparks[i]->g_GlowID();



				//	Set the position of the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(this->m_Sparks[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(this->m_Sparks[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);


				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(		this->m_Sparks[i]->g_ColorPrp(1)	,
																															this->m_Sparks[i]->g_ColorPrp(2)	,
																															this->m_Sparks[i]->g_ColorPrp(3)	,
																															this->m_Sparks[i]->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Sparks[i]->g_VisualPrp(1)	,
																											this->m_Sparks[i]->g_VisualPrp(2)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Sparks[i]->g_RotationPrp(1)		);



				//	Drawing...
				if (	this->m_Sparks[i]->g_Blending()	)
				{
					this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
				}
				else
				{
					this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
				}
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
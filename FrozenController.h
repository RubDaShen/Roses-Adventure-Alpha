#pragma once

#include		"Tools_.h"
#include		"_MyIncludes_.h"
#include		"TheCandy.h"
#include		"AfterGlows.h"
#include		"SoundFactory.h"
#include		"Scores.h"
#include		"VisualGridController.h"
#include		"SpawnPointController.h"
#include		"LogicalController.h"

#include		<vector>



class		SpawnPointTracker
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double					$_BoardBounds		= 90.0;

//	-------------------------------------------
//				External and linkers.
//	-------------------------------------------
private:
	TheCandy*				_Linker_			= nullptr;
	int						_Linker_UniqueID	= 0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double				_Board_xP	= 0.0, _Board_yP	= 0.0;
	double				_Board_W	= 0.0, _Board_H		= 0.0;

	double				xP = 0.0, yP = 0.0, _W = 0.0, _H = 0.0;

	double				m_Speed		= 0.0;

	double				m_LifeTime	= 0.0;
	double				m_Time		= 0.0;
	double				m_RunTime	= 0.0;
	double				m_DelayEnd	= 0.0;

//	-------------------------------------------
//				Tracking variables
//	-------------------------------------------
private:
	int				m_KindToSearch		= def::enm_Defines::_NOT_FOUND;
	int				m_ItemToWrite		= def::enm_Defines::_NOT_FOUND;
	int				m_KindToRead		= def::enm_Defines::_NOT_FOUND;
	int				ObjectID			= 0;

	bool			m_SelfKindSearch	= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	SpawnPointTracker(	double _TimeSearch, double _DelayBegin, double _DelayEnd					, 
						int _KindToSearch, int _ItemToWrite, int _KindToRead						,	
						TheCandy* _Linker, tls::Vec4<double> _Bounds, int _Tracker_Unique_ID		,
						bool _SelfKindSearch														)
	{
		//	Linkers and external...
		{
			this->_Linker_				= _Linker;
			this->_Linker_UniqueID		= _Linker->g_ObjectID();

			this->ObjectID		= _Tracker_Unique_ID;
		}

		//	MyVariables.
		{
			this->m_KindToSearch	= _KindToSearch;
			this->m_ItemToWrite		= _ItemToWrite;
			this->m_KindToRead		= _KindToRead;
			this->m_SelfKindSearch = _SelfKindSearch;

			this->_Board_xP		= _Bounds.First;
			this->_Board_yP		= _Bounds.Second;
			this->_Board_W		= _Bounds.Third;
			this->_Board_H		= _Bounds.Fourth;

			

			
			//	Calculation of speed and delay.
			{
				this->m_Speed	= (this->_Board_W * (this->_Board_H / this->$_BoardBounds)) / (_TimeSearch * GAME_LOOP_VALUE);

				this->m_LifeTime	= _TimeSearch + _DelayBegin;
				this->m_RunTime		= _DelayBegin;
				this->m_DelayEnd	= _DelayEnd;
			}

			//	Resize the width.
			{
				this->_H		= 30.0;
				this->_W		= this->m_Speed;

				this->xP		= this->_Board_xP - this->_W - 10.0;
			}
		}
 	}

	~SpawnPointTracker()
	{
		this->ObjectID		= def::enm_Defines::_NOT_INITIALIZED;
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		RunTracker()
	{
		//	Position of the tracker.
		{
			if (this->m_RunTime <= this->m_Time)
			{
				this->xP = this->xP + (this->m_Speed * _Controller_Logic::_fdTime_);
			}
		}

		//	Time.
		{
			this->m_Time	= this->m_Time + ((1.0 / _Controller_Logic::_ogLpV_) * _Controller_Logic::_fdTime_);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline tls::Vec4<double>		g_Positional()
	{
		tls::Vec4<double>	_Pos_;



		_Pos_.First		= this->_Board_xP + (static_cast<int>(std::fabs(this->xP - this->_Board_xP)) % static_cast<int>(this->_Board_W));
		_Pos_.Second	= this->_Board_yP - ((static_cast<int>(std::fabs(this->xP - this->_Board_xP)) / static_cast<int>(this->_Board_W)) * this->$_BoardBounds);

		//	_Pos_.First		= _Pos_.First + ((this->$_BoardBounds - this->_W) / 2.0);
		//	_Pos_.Second	= _Pos_.Second - ((this->$_BoardBounds - this->_H) / 2.0);

		_Pos_.Third		= this->_W;
		_Pos_.Fourth	= this->_H;

		return _Pos_;
	}
	inline TheCandy*				g_Linker()
	{
		if (	this->_Linker_UniqueID == this->_Linker_->g_ObjectID()	)
		{
			return this->_Linker_;
		}
		else
		{
			return nullptr;
		}		
	}
	inline int						g_Saved_LinkerID()
	{
		return this->_Linker_UniqueID;
	}

	inline bool						g_End()					const
	{
		return ((this->m_Time >= (this->m_LifeTime + this->m_DelayEnd)) ? true : false);
	}
	inline bool						g_IsRunning()			const
	{
		return ((this->m_Time >= this->m_RunTime) ? true : false);
	}
	inline bool						g_SelfKindSearch()		const
	{
		return		this->m_SelfKindSearch;
	}

	inline int						g_KindToSearch()
	{
		return		this->m_KindToSearch;
	}
	inline int						g_sMx_Item()
	{
		return		this->m_ItemToWrite;
	}
	inline int						g_sMx_Kind()
	{
		return		this->m_KindToRead;
	}
	inline int						g_MyUniqueID()
	{
		return		this->ObjectID;
	}

	inline double					g_Bounds(	int What	)
	{
		switch (	What	)
		{
		case 1:
			return		this->_W;

		case 2:
			return		this->_H;

		default:
			throw		std::runtime_error("Will return anything.");
		}
	}
};



class		Frojectile : public thyObject
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
	TheCandy*				_Linker_			= nullptr;
	int						_Linker_UniqueID	= 0;

	int						_TrackerID_			= 0;

	bool					_HasPainted_	= false;
				
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
	int				m_ItemIDToWrite = def::enm_Defines::_NOT_INITIALIZED;
	int				m_FrojectileID	= def::enm_Defines::_NOT_INITIALIZED;

	double			m_Time			= 0.0;
	int				m_InnerTime		= 0;

	bool			m_End			= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Frojectile(	double _xP, double _yP, TheCandy* _Linker		,
				int _KindID, int _ItemToWrite					,
				int _TrackerID, double _LifeTime				) : thyObject(_xP, _yP, def::enm_ObjectType::Frojectile)
	{
		this->m_KindID			= _KindID;
		this->m_ItemIDToWrite	= _ItemToWrite;
		this->m_FrojectileID	= tls::Random(1, 2);
		this->_W				= this->_H = 30.0;
		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);



		//	Linkers and external...
		{
			this->_Linker_				= _Linker;
			this->_Linker_UniqueID		= _Linker->g_ObjectID();

			this->_TrackerID_			= _TrackerID;
		}

		//	Calculating the position.
		{
			this->$_LifeTime	= _LifeTime;

			this->xOrg		= this->xP;
			this->yOrg		= this->yP;
			this->zOrg		= 0.0;

			this->xTarget	= _Linker->g_PositionPrp(1) + (_Linker->g_MeasuresPrp(1) / 2.0);
			this->yTarget	= _Linker->g_PositionPrp(2) - (_Linker->g_MeasuresPrp(2) / 2.0);
			this->zTarget	= _Linker->g_MeasuresPrp(1);

			this->xS	= (this->xTarget - this->xP) / this->$_LifeTime;
			this->yS	= ((this->yTarget - this->yP) / (this->$_LifeTime * this->$_AngleUp_)) - (0.5 * this->$_Gravity * this->$_LifeTime * this->$_AngleUp_);
			this->zS	= (this->zTarget - this->zP) / this->$_LifeTime;

			this->rotationSpeed		= tls::Random(2, 6) * tls::UnityRound(std::cos(tls::DegToRad(std::atan(this->yS / this->xS)))) * 2.0;
		}
	}

	~Frojectile()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateFrojectile()
	{
		this->_HasPainted_	= false;


		//	Run while it didn't end.
		if (!this->m_End)
		{
			//	Calculating the rotation.
			{
				this->rotationDegree = this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
			}

			//	Change position.
			{
				this->xP	= this->xOrg + (this->xS * this->m_Time);
				this->yP	= this->yOrg + (this->yS * this->m_Time * this->$_AngleUp_) + (0.5 * this->$_Gravity * this->m_Time * this->m_Time * this->$_AngleUp_ * this->$_AngleUp_);
				this->zP	= this->zOrg + (this->zS * this->m_Time);
			}

			//	If frojectile reached destiny.
			{
				if (	(this->m_Time > this->$_LifeTime)	&&
								(!this->m_End)				)
				{
					//	If candy is still alive, then do some modification to it.
					if (	this->_Linker_UniqueID == this->_Linker_->g_ObjectID()	)
					{
						this->_Linker_->s_KindID(this->m_KindID);		//	Paint it!

						this->_Linker_->s_Fc_Is(2, 2);					//	Can fall now.
						this->_Linker_->s_Can(1, true);					//	Can fall now.



						//	Also, if enable, change the itemID.
						if (	this->m_ItemIDToWrite != def::enm_Defines::_SKIP_THIS	)
						{
							switch (	this->m_ItemIDToWrite	)
							{
							case	STA_::enm_ItemID::StrippedH:
							case	STA_::enm_ItemID::StrippedV:
								this->_Linker_->s_ItemID(STA_::enm_ItemID::StrippedH + tls::Random(0, 1));
								break;

							default:
								this->_Linker_->s_ItemID(this->m_ItemIDToWrite);
							}
						}
					}

					this->m_End			= true;
					this->_HasPainted_	= true;
				}
			}

			this->m_Time = this->m_Time + ((1.0 / _Controller_Logic::_ogLpV_) * _Controller_Logic::_fdTime_);
			++this->m_InnerTime;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline TheCandy*	g_Linker()
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
	inline int			g_Linker_UniqueID()
	{
		return		this->_Linker_UniqueID;
	}

	inline int			g_InnerTime()
	{
		return		this->m_InnerTime;
	}
	inline int			g_KindID()
	{
		return		this->m_KindID;
	}
	inline int			g_FrojectileID()
	{
		return		this->m_FrojectileID;
	}
	inline bool			g_HasPainted()
	{
		return this->_HasPainted_;
	}
	inline int			g_TrackerID()
	{
		return		this->_TrackerID_;
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
			return		(this->xP + (this->_W_Sprite * 0.5));
	
		case	2:
			return		(this->yP - (this->_H_Sprite * 0.5));
	
		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
class		Fc_Splash : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	double			m_LifeTime		= 0.0;
	double			m_Time			= 0.0;

	double			m_SplashTime	= 0.0;
	double			m_FadeTime		= 0.0;

	int				m_KindID		= def::enm_Defines::_NOT_INITIALIZED;
	int				m_SplashID		= def::enm_Defines::_NOT_INITIALIZED;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Fc_Splash(double _xP, double _yP, double _LifeTime, int _KindID) : thyObject(_xP, _yP, def::enm_ObjectType::Fc_Splash)
	{
		this->m_LifeTime		= _LifeTime;
		this->m_SplashTime		= _LifeTime / 5.0;
		this->m_FadeTime		= _LifeTime / 2.0;

		this->m_KindID		= _KindID;
		this->m_SplashID	= tls::Random(1, 1);

		//	Setting all up.
		{
			this->xFct		= this->yFct = 0.25;
			this->xFctS		= 0.75 / (GAME_LOOP_VALUE * this->m_SplashTime);

			this->Alpha_s	= -255.0 / (GAME_LOOP_VALUE * this->m_FadeTime);
		}
	}

	~Fc_Splash()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateSplash()
	{
		//	Growing time.
		{
			if (this->m_Time <= this->m_SplashTime)
			{
				this->xFct	= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);

				if (this->xFct >= 1.0)
				{
					this->xFct = 1.0;
				}

				this->yFct = this->xFct;
			}
		}

		//	Opacity side.
		{
			if (this->m_Time >= this->m_FadeTime)
			{
				this->A_alpha = this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

				if (this->A_alpha <= 0.0)
				{
					this->A_alpha = 0.0;
				}
			}
		}



		this->m_Time = this->m_Time + ((1.0 / _Controller_Logic::_ogLpV_) * _Controller_Logic::_fdTime_);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_KindID()
	{
		return		this->m_KindID;
	}
	inline int			g_SplashID()
	{
		return		this->m_SplashID;
	}

	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case 1:
			return		(this->xP + (this->_W * 0.5));

		case 2:
			return		(this->yP - (this->_H * 0.5));

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
class _Controller_FrozenCandy
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Splash			= 0,
		_Sparkmoke		= 1,
		_Sparkle		= 2,
		_Frojectile		= 3,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<Frojectile*>				m_Frojectiles;
	std::vector<Fc_Splash*>					m_Splashes;
	std::vector<GlowParticle*>				m_Sparkmoke;
	std::vector<GlowParticle*>				m_Sparkles;

	std::vector<SpawnPointTracker*>			m_Trackers;

//	-------------------------------------------
//			Variables and constants
//	-------------------------------------------
private:
	const int				_CommonCellBounds_		= 90;
	const int				$_Common_Candies_Size	= 10;

	std::vector<int>		_AmountPerKind_;
	std::vector<bool>		_ChoosenColor_;

	int						_TrackedID_Cnt = 0;

//	-------------------------------------------
//				Amima-riables
//	-------------------------------------------
private:
	double			m_TrackerTime		= 1.00;
	double			m_TrackingDelay		= 0.15;

	double			m_LifeTime_Frojectiles	= 0.65;

	double			m_SplashLifeTime	= 0.75;


	int				Rnd_Sparkmoke					= 8;
	int				Rnd_Amt_To_Sparkmoke			= 3;
	int				Rnd_LifeTime_From_Sparkmoke		= 8;
	int				Rnd_LifeTime_To_Sparkmoke		= 11;

	int				Tck_Sparkles					= 15;
	int				Rnd_LifeTime_From_Sparkle		= 5;
	int				Rnd_LifeTime_To_Sparkle			= 10;
	int				Rnd_Amt_To_Sparkles				= 1;

	float			_DistanceFromCenter_		= 5.0f;
	float			_DistanceForSparkles_		= 5.0f;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	_Controller_Score*			_Score_			= nullptr;
	_Controller_SpawnPoints*	_SpawnPoints_	= nullptr;	

	SoundFactory*			_Sound_		= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;

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
	_Controller_FrozenCandy(	DrawFactory* _Draw_Ptr						,
								SpriteFactory* _Sprite_Ptr					, 
								SoundFactory* _Sound_Ptr					, 
								_Controller_Score* _Score_Ptr				,
								_Controller_SpawnPoints* _SpawnPoints_Ptr	)
	{
		this->_Draw_			= _Draw_Ptr;
		this->_Sprites_			= _Sprite_Ptr;
		this->_Sound_			= _Sound_Ptr;
		this->_Score_			= _Score_Ptr;
		this->_SpawnPoints_		= _SpawnPoints_Ptr;



		//	Creating the vectors.
		{
			//	For the amounts.
			for (	int i = 0; 
					i < this->$_Common_Candies_Size; 
					++i	)
			{
				this->_AmountPerKind_.push_back(0);
			}

			//	For the choosens.
			for (	int i = 0; 
					i < this->$_Common_Candies_Size; 
					++i	)
			{
				this->_ChoosenColor_.push_back(false);
			}
		}

	}
	
	~_Controller_FrozenCandy()
	{
		//	Deleting Frojectiles Entities !
		{
			while (!this->m_Frojectiles.empty())
			{
				delete this->m_Frojectiles[0];
				this->m_Frojectiles.erase(this->m_Frojectiles.begin() + 0);
			}
		}

		//	Deleting Splashes !
		{
			while (!this->m_Splashes.empty())
			{
				delete this->m_Splashes[0];
				this->m_Splashes.erase(this->m_Splashes.begin() + 0);
			}
		}

		//	Deleting Sparkmokes !
		{
			while (!this->m_Sparkmoke.empty())
			{
				delete this->m_Sparkmoke[0];
				this->m_Sparkmoke.erase(this->m_Sparkmoke.begin() + 0);
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
//				Spawning functions
//	-------------------------------------------
public:
	inline void			AddTracker(	TheCandy* _Linker, double _Time, double _Delay									, 
									tls::Vec4<double> _BoardPos, std::vector<TheCandy*>& _Candies_, int _Where_Pos	,
									int CustomKind, int CustomItemID												)
	{
		int				_FinalKind_		= def::enm_Defines::_NOT_FOUND;
		int				_PopularAmount_ = def::enm_Defines::_NOT_FOUND;
		double			_ExtraDelay_	= 0.15;
		bool			_SelfSearch_	= true;



		//	Finding which kind is the most popular around.
		{
			if (	CustomKind == def::enm_Defines::_SKIP_THIS	)
			{ 
				//	Search all kinds.
				{
					int		_Size_ = _Candies_.size();



					for (	int i = 0;
							i < _Size_;
							++i	)
					{
						if (	((0 <= _Candies_[i]->g_Pos(1)) && (0 <= _Candies_[i]->g_Pos(2)))	&&		//	Valid position on board.
								(_Candies_[i]->g_ObjectID() != _Linker->g_ObjectID())				&&		//	Can't count itself.
								(0 < _Candies_[i]->g_KindID())										&&		//	Has a valid kind.
								(_Candies_[i]->g_ItemID() != STA_::enm_ItemID::WrappedFuse)			&&		//	Can't be a wrapped fuse.
								(_Candies_[i]->g_ItemID() != STA_::enm_ItemID::BomOBom)				&&		//	Can't be a Bom-O-Bom.
								(!_Candies_[i]->g_Fc_Is(1))	&& (!_Candies_[i]->g_Fc_Is(2))			)		//	Can't paint and being painted.
						{
							++this->_AmountPerKind_[_Candies_[i]->g_KindID() - 1];
						}
					}
				}

				//	Searching the most popular.
				{
					//	Invalidating those ocupied.
					{
						for (	int i = 0;
								i < this->$_Common_Candies_Size;
								++i	)
						{
							if (	this->_ChoosenColor_[i]	)
							{
								this->_AmountPerKind_[i] = def::enm_Defines::_NOT_INITIALIZED;
							}

							if (	!this->_SpawnPoints_->g_ColorIsInPallette(i + 1)	)
							{
								this->_AmountPerKind_[i] = def::enm_Defines::_NOT_INITIALIZED;
							}
						}


						//	Also, invalid its same kind.
						{
							this->_AmountPerKind_[_Linker->g_KindID() - 1] = def::enm_Defines::_NOT_INITIALIZED;
						}
					}

					//	Selecting something to compare and find the popular.
					{
						for (	int i = 0;
								i < this->$_Common_Candies_Size;
								++i	)
						{
							if (						!this->_ChoosenColor_[i]						&& 
									(this->_AmountPerKind_[i] != def::enm_Defines::_NOT_INITIALIZED)	)
							{
								_PopularAmount_		= this->_AmountPerKind_[i];
								_FinalKind_			= i + 1;

								break;
							}
						}
					}

					//	Actual search.
					{
						for (	int i = 1;
								i < this->$_Common_Candies_Size;
								++i	)
						{
							if (	_PopularAmount_ < this->_AmountPerKind_[i]	)
							{
								_PopularAmount_ = this->_AmountPerKind_[i];
								_FinalKind_ = i + 1;
							}
						}
					}
				}

				//	Setting as ocupied.
				{
					//	Ocupied!
					if (	_FinalKind_ != def::enm_Defines::_NOT_FOUND	)
					{
						this->_ChoosenColor_[_FinalKind_ - 1] = true;
					}

					//	Clearing!
					for (	int i = 0;
							i < this->$_Common_Candies_Size;
							++i	)
					{
						this->_AmountPerKind_[i] = 0;
					}
				}
			}
			else
			{
				_FinalKind_		= CustomKind;
			}
		}


		//	Creating the tracker.
		//	If the kind seems invalid then...
		if (	_FinalKind_ != def::enm_Defines::_NOT_FOUND	)
		{
			++_TrackedID_Cnt;

			//	Extra delay?
			if (	CustomKind == def::enm_Defines::_SKIP_THIS	)
			{
				_ExtraDelay_	= 0.0;
			}
			//	Is custom ID?
			if (	CustomItemID == def::enm_Defines::_SKIP_THIS	)
			{
				_SelfSearch_	= false;
			}
			this->m_Trackers.push_back(	new SpawnPointTracker(	m_TrackerTime, m_TrackingDelay + _ExtraDelay_, m_LifeTime_Frojectiles + 0.25	,
																_FinalKind_, CustomItemID, _Linker->g_KindID(), _Linker, _BoardPos				,
																_TrackedID_Cnt, _SelfSearch_													)	);
		
			//	Adjusting the candy properties.
			{
				_Linker->s_Fc_Is(1, true);
				_Linker->s_Can(1, false);
				_Linker->s_Can(2, false);
				_Linker->s_Can(3, false);
			}

			//	Sound part.
			{
				this->_Sound_->Play(snd::SndSys::FrozenC, 2);
			}
		}
		else
		{
			//	Here goes some animation where simulates that
			//	the frozen candy goes crazy and auto-destroy
			//	itself.

			//	Massive Score.
			this->_Score_->AddScore(	_Linker->g_PositionPrp(1), _Linker->g_PositionPrp(2)			, 
										ScoreSys::Bonus_FrozenNotFound, def::enm_Defines::_SKIP_THIS	,
										false, _Linker->g_KindID()										);

			//	Finally, erase it from vector.
			tls::EraseElement<TheCandy*>(_Candies_, _Where_Pos);
		}
	}
	inline void			SpawnFrojectile(	double _xP, double _yP, TheCandy* _What_Candy	, 
											int _Kind, int _Item, int _TrackerID			)
	{
		this->m_Frojectiles.push_back(	new Frojectile(_xP, _yP, _What_Candy, _Kind, _Item, _TrackerID, m_LifeTime_Frojectiles)	);
	}
	inline void			AddSplash(		double _xP, double _yP, int _KindID			)
	{
		this->m_Splashes.push_back(	new Fc_Splash(_xP, _yP, m_SplashLifeTime, _KindID)	);
	}
	inline void			AddSparkmoke(	double _xP, double _yP, int _KindID			)
	{
		if (	!tls::Random(0, this->Rnd_Sparkmoke / _Controller_Logic::_fdTime_)	)
		{
			int			_Times_ = tls::Random(1, this->Rnd_Amt_To_Sparkmoke);



			for (	int i = 0; 
					i < _Times_; 
					++i	)
			{
				float		_Angle_		= tls::DegToRad(tls::Random(0, 360));
				float		_LifeTime_	= tls::Random(this->Rnd_LifeTime_From_Sparkmoke, this->Rnd_LifeTime_To_Sparkmoke) / 10.0;




				this->m_Sparkmoke.push_back(	new GlowParticle(	_xP	+ (std::cos(_Angle_) * this->_DistanceFromCenter_),
																	_yP + (std::sin(_Angle_) * this->_DistanceFromCenter_),
																	GlowID::SparkmokeMedium, AnmGlow::StaticGlow	)	);

				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Opacity_WithContainer(	tls::Vec3<double>(	255.0									, 
																												-255.0 / (_LifeTime_ * GAME_LOOP_VALUE)	,
																												0.0										)	);
				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(	1.0										, 
																												-1.0 / (_LifeTime_ * GAME_LOOP_VALUE)	)	);
				this->m_Sparkmoke[this->m_Sparkmoke.size() - 1]->s_Color_WithKind(	_KindID	);

			}
		}
	}
	inline void			AddSparkle(		double _xP, double _yP, double _Rot_Speed, int _InnerTime	)
	{
		if (	!(_InnerTime % (static_cast<int>(this->Tck_Sparkles / _Controller_Logic::_fdTime_))) 	)
		{
			int			_Times_ = tls::Random(1, this->Rnd_Amt_To_Sparkles);



			for (	int i = 0; 
					i < _Times_; 
					++i	)
			{
				float		_Angle_		= tls::DegToRad(tls::Random(0, 360));
				double		_LifeTime_	= (tls::Random(this->Rnd_LifeTime_From_Sparkle, this->Rnd_LifeTime_To_Sparkle) / 10.0) * GAME_LOOP_VALUE;



				this->m_Sparkles.push_back(		new GlowParticle(	_xP + (std::cos(_Angle_) * this->_DistanceForSparkles_)	,
																	_yP + (std::sin(_Angle_) * this->_DistanceForSparkles_)	,
																	GlowID::RadiantGlow,	AnmGlow::StaticGlow		)	);



				//	Setting all up.
				{
					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Opacity_WithContainer(		tls::Vec3<double>(	255.0				, 
																													-255.0 / _LifeTime_	,
																													0.0					)	);

					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Visual_WithContainer(		tls::Vec2<double>(	0.85 - (tls::Random(0, 3) * 0.1), -1.0 / _LifeTime_	)	);

					this->m_Sparkles[this->m_Sparkles.size() - 1]->s_Rotation_WithContainer(	tls::Vec3<double>(	tls::RadToDeg(_Angle_), _Rot_Speed / 5.0, 0.0)		);
				}
			}
		}
	}

	
	inline void			AddSpecialMix(	SpecialMixWrapper* Wrapper	)
	{
		using			sMx = SpecialMixWrapper::enm_SpecialMix;
		using			spC = AnimatedObject::enm_SpawnCommand;

		TheCandy*	_First_		= Wrapper->g_Pointers(0);
		TheCandy*	_Second_	= Wrapper->g_Pointers(1);



		switch (	Wrapper->g_SpecialMixID()	)
		{
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//			Stripped Horizontal + Stripped Horizontal
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		case	sMx::FrozenCandy_CommonCandy:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_StrippedHorizontal:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_StrippedVertical:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_Wrapped:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_WrappedFuse:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_JellyFish:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_StarLight:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_FireWork:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_BubbleGum:
			//	Code anything here.
			break;

		case	sMx::FrozenCandy_Popping:
			//	Code anything here.
			break;
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoTrackers(	std::vector<TheCandy*>&		_Candies_	)
	{
		for (	int i = 0; 
				i < this->m_Trackers.size();
				++i)
		{
			//	If tracker ends.
			if (this->m_Trackers[i]->g_End())
			{
				//	When a tracker ends, say that candy (the linked one) to
				//	finish its job and get crushed.
				//
				//	Use this line of code if you don't want the 'being painted' candies
				//	attributte set off if the frozen candy that painted them died.
				// 
				//	if (	this->m_Trackers[i]->g_Linker() != nullptr	)
				{
					//	First of all, from all the frojectiles, let all the linked
					//	candies become matchable.
					//	I'm not using the vector of candies since it can be expensive.
					//	Besides, there is already a vector for this purpose.
					for	(	int c = 0; 
							c < this->m_Frojectiles.size(); 
							++c	)
					{
						//	Check if the current tracker owns this frojectile.
						if (this->m_Frojectiles[c]->g_TrackerID() == this->m_Trackers[i]->g_MyUniqueID())
						{
							//	If the linker (or painted candy) still exists,
							//	then change some properties of the candy.
							if (	this->m_Frojectiles[c]->g_Linker() != nullptr	)
							{
								this->m_Frojectiles[c]->g_Linker()->s_Can(		3, 1	);
								this->m_Frojectiles[c]->g_Linker()->s_Fc_Is(	2, 0	);
							}

							//	Finally, erase it from vector.
							tls::EraseElement<Frojectile*>(this->m_Frojectiles, c);
						}
					}

					//	Then, as said, the linker candy (now the frozen one)
					//	will be crushed and die...
					for	(	int c = 0; 
							c < _Candies_.size(); 
							++c	)
					{
						if (	this->m_Trackers[i]->g_Saved_LinkerID() == _Candies_[c]->g_ObjectID()	)
						{
							//	Sound part.
							this->_Sound_->Play(snd::SndSys::FrozenC, 4);

							tls::EraseElement<TheCandy*>(_Candies_, c);
							break;
						}
					}
				}

				//	Then, erase the tracker when everything is all done.
				this->_ChoosenColor_[this->m_Trackers[i]->g_KindToSearch() - 1] = false;
				tls::EraseElement<SpawnPointTracker*>(this->m_Trackers, i);
				continue;
			}

			//	Finding candy stuff.
			{
				int		_Size_		= _Candies_.size();



				for (	int c = 0;
						c < _Size_;
						++c	)
				{
					//	The first collision, or the first matching
					//	means that the tracker has encounter something...
					if (	tls::CollidesWith(	this->m_Trackers[i]->g_Positional().First, this->m_Trackers[i]->g_Positional().Second	,
												this->m_Trackers[i]->g_Positional().Third, this->m_Trackers[i]->g_Positional().Fourth	, 
												_Candies_[c]->g_PositionPrp(1), _Candies_[c]->g_PositionPrp(2)							,
												_Candies_[c]->g_MeasuresPrp(1), _Candies_[c]->g_MeasuresPrp(2)							)	)
					{
						if (	(	(_Candies_[c]->g_KindID() == this->m_Trackers[i]->g_KindToSearch())		||
									(	(_Candies_[c]->g_KindID() == this->m_Trackers[i]->g_sMx_Kind()	&&
										(this->m_Trackers[i]->g_SelfKindSearch()						)	))) &&	//	Does the kind match?
								(!_Candies_[c]->g_Fc_Is(1))														&&	//	Is not painting.
								(!_Candies_[c]->g_Fc_Is(2))														&&	//	Is not being painted by another.
								(_Candies_[c]->g_ItemID() != STA_::enm_ItemID::WrappedFuse)						&&	//	Cannot take a fuse wrapped.
								(_Candies_[c]->g_ItemID() != STA_::enm_ItemID::BomOBom)							&&	//	Nor another Bom-O-Bom.
								(_Candies_[c]->g_ItemAllowsSomething(5))										)	//	Item allows painting?
						{
							//	Create frojectile.
							{
								//	Well, 45.0 is the half of the boundaries of the candy.
								//	I'm not writting the whole code since it's pretty obvious.
								int		_x_Pos_	= 0, _y_Pos_ = 0;

								switch (	tls::Random(1, 2)	)
								{
								case 1:
									_x_Pos_ = -43, _y_Pos_ = 46;
									break;

								case 2:
									_x_Pos_ = 21, _y_Pos_ = 52;
									break;
								}



								if (	this->m_Trackers[i]->g_Linker() != nullptr	)
								{
									this->SpawnFrojectile(	this->m_Trackers[i]->g_Linker()->g_PositionPrp(1) + 45 + _x_Pos_	,
															this->m_Trackers[i]->g_Linker()->g_PositionPrp(2) - 45 + _y_Pos_	,
															_Candies_[c]														, 
															this->m_Trackers[i]->g_Linker()->g_KindID()							,
															this->m_Trackers[i]->g_sMx_Item()									,
															this->m_Trackers[i]->g_MyUniqueID()									);
								}
							}

							//	Set candy properties.
							{
								_Candies_[c]->s_Fc_Is(2, 1);
							}
						}
					}
				}
			}

			//	Run, tracker, Run!
			{
				this->m_Trackers[i]->RunTracker();
			}
		}
	}
	inline void			Animate(VisualGrid***	_BoardVisual_)
	{
		//	Just frojectiles.
		for (	int i = 0;
				i < this->m_Frojectiles.size();
				++i	)
		{
			this->m_Frojectiles[i]->AnimateFrojectile();

			if (	!this->m_Frojectiles[i]->g_End()	)
			{
				this->AddSparkmoke(	this->m_Frojectiles[i]->g_PositionPrp(1)	,
									this->m_Frojectiles[i]->g_PositionPrp(2)	,
									this->m_Frojectiles[i]->g_KindID()			);

				this->AddSparkle(	this->m_Frojectiles[i]->g_PositionPrp(1)	,
									this->m_Frojectiles[i]->g_PositionPrp(2)	,
									this->m_Frojectiles[i]->g_RotationPrp(2)	,
									this->m_Frojectiles[i]->g_InnerTime()		);
			}



			if (	this->m_Frojectiles[i]->g_HasPainted()	)
			{
				//	Sound part.
				this->_Sound_->Play(snd::SndSys::FrozenC, 3);

				//	Splash effect.
				this->AddSplash(	this->m_Frojectiles[i]->g_PositionPrp(1)	, 
									this->m_Frojectiles[i]->g_PositionPrp(2)	,
									this->m_Frojectiles[i]->g_KindID()			);

				//	Coloring grid.
				if (	this->m_Frojectiles[i]->g_Linker() != nullptr	)
				{
					if (	(0 <= this->m_Frojectiles[i]->g_Linker()->g_Pos(1))		&& 
							(0 <= this->m_Frojectiles[i]->g_Linker()->g_Pos(2))		)
					{
						_BoardVisual_[this->m_Frojectiles[i]->g_Linker()->g_Pos(1)][this->m_Frojectiles[i]->g_Linker()->g_Pos(2)]->UseColorKind(this->m_Frojectiles[i]->g_KindID());
					}
				}
			}
		}

		//	Splash zone.
		for (	int i = 0;
				i < this->m_Splashes.size();
				++i	)
		{
			this->m_Splashes[i]->AnimateSplash();



			if (	this->m_Splashes[i]->g_ColorPrp(4) <= 0.0	)
			{
				tls::EraseElement<Fc_Splash*>(this->m_Splashes, i);
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

		//	Sparkmoke (Sparkle + Smoke).
		for (	int i = 0;
				i < this->m_Sparkles.size();
				++i	)
		{
			this->m_Sparkles[i]->AnimateParticle();



			//	Deleting when done.
			{
				if (	this->m_Sparkles[i]->g_ColorPrp(4) <= 0.0	)
				{
					tls::EraseElement<GlowParticle*>(this->m_Sparkles, i);
				}
			}
		}
	}

//	-------------------------------------------
//				Draw Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Splash.
		if (	enm_Draw::_Splash == What		)
		{
			this->_What_Sprite_			= spr::enm_At::Fc_Splash;
			this->_Container_Size_		= this->m_Splashes.size();



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_		= ((this->m_Splashes[i]->g_SplashID() - 1) * STA_::enm_Definitions::TotalKind) + this->m_Splashes[i]->g_KindID() - 1;


		
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Splashes[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Splashes[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Splashes[i]->g_VisualPrp(1)	,
																											this->m_Splashes[i]->g_VisualPrp(2)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_Splashes[i]->g_ColorPrp(1)	,
																														this->m_Splashes[i]->g_ColorPrp(2)	, 
																														this->m_Splashes[i]->g_ColorPrp(3)	, 
																														this->m_Splashes[i]->g_ColorPrp(4)	)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Sparkmoke.
		if (	enm_Draw::_Sparkmoke == What	)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_Container_Size_		= this->m_Sparkmoke.size();



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_		= this->m_Sparkmoke[i]->g_GlowID();


		
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Sparkmoke[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Sparkmoke[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Sparkmoke[i]->g_VisualPrp(1)	,
																											this->m_Sparkmoke[i]->g_VisualPrp(2)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_Sparkmoke[i]->g_ColorPrp(1)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(2)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(3)	,
																														this->m_Sparkmoke[i]->g_ColorPrp(4)	)	);



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Sparkle.
		if (	enm_Draw::_Sparkle == What		)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_Container_Size_		= this->m_Sparkles.size();



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_		= this->m_Sparkles[i]->g_GlowID();


		
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Sparkles[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Sparkles[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Sparkles[i]->g_VisualPrp(1)	,
																											this->m_Sparkles[i]->g_VisualPrp(2)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_Sparkles[i]->g_ColorPrp(1)	,
																														this->m_Sparkles[i]->g_ColorPrp(2)	,
																														this->m_Sparkles[i]->g_ColorPrp(3)	,
																														this->m_Sparkles[i]->g_ColorPrp(4)	)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Sparkles[i]->g_RotationPrp(1)	);



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Frojectile.
		if (	enm_Draw::_Frojectile == What		)
		{
			this->_What_Sprite_			= spr::enm_At::Fc_Frojectiles;
			this->_Container_Size_		= this->m_Frojectiles.size();



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{	
				if (	!this->m_Frojectiles[i]->g_End()	)
				{
					this->_What_Kind_		= ((this->m_Frojectiles[i]->g_FrojectileID() - 1) * STA_::enm_Definitions::TotalKind) + this->m_Frojectiles[i]->g_KindID() - 1;


					
					//	Glow :D
					{
						//	Set position to the sprite.
						_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::MoreMediumGlow)->setPosition(	tls::FixPos_X(	this->m_Frojectiles[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																																tls::FixPos_Y(	this->m_Frojectiles[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

						//	Then goes the shrinking model.
						_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::MoreMediumGlow)->setScale(		this->m_Frojectiles[i]->g_VisualPrp(1)	,
																																this->m_Frojectiles[i]->g_VisualPrp(2)	);

						//	Spining.
						_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::MoreMediumGlow)->setRotation(	this->m_Frojectiles[i]->g_RotationPrp(1)	);

						//	Applying color properties.
						_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::MoreMediumGlow)->setColor(		sf::Color(	this->m_Frojectiles[i]->g_ColorPrp(1)	,
																																			this->m_Frojectiles[i]->g_ColorPrp(2)	,
																																			this->m_Frojectiles[i]->g_ColorPrp(3)	,
																																			this->m_Frojectiles[i]->g_ColorPrp(4)	)	);



						this->_Draw_->DrawBlend(_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::MoreMediumGlow));
					}

					//	The frojectile.
					{
						//	Set position to the sprite.
						_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Frojectiles[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																													tls::FixPos_Y(	this->m_Frojectiles[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

						//	Then goes the shrinking model.
						_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Frojectiles[i]->g_VisualPrp(1)	,
																													this->m_Frojectiles[i]->g_VisualPrp(2)	);

						//	Spining.
						_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Frojectiles[i]->g_RotationPrp(1)	);



						this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
					}
				}
			}
		}
	}
};
#pragma once

#include		"FrozenController.h"
#include		"SpawnPointController.h"
#include		"LogicalController.h"



class		LightBon : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	TheCandy*				_Linker_			= nullptr;
	int						_Linker_UniqueID	= 0;

	TheCandy*				_BonOBom_			= nullptr;
	int						_BonOBom_UniqueID	= 0;

	int						_TrackerID_			= 0;

	bool					_HasArrived_		= false;
	bool					_End_				= false;
				
//	-------------------------------------------
//				Positional Variables
//	-------------------------------------------
private:
	double			m_ArrivingTime = 0.25;

	double			xTarget		= 0.0, yTarget	= 0.0, zTarget	= 0.0;
	double			xOrg		= 0.0, yOrg		= 0.0, zOrg		= 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_KindID		= def::enm_Defines::_NOT_INITIALIZED;
	int				m_ItemToWrite	= def::enm_Defines::_NOT_INITIALIZED;

	double			m_Time			= 0.0;
	int				m_InnerTime		= 0;

	double			m_Factor		= 0.0, m_FactorSpeed = 0.0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LightBon(	double _xP, double _yP, TheCandy* _Linker			,
				int _KindID, int _ItemIDToWrite, int _TrackerID		, 
				double _ArrivalTime, TheCandy* _BonOBom_			) : thyObject(_xP, _yP, def::enm_ObjectType::LightBon)
	{
		this->m_KindID			= _KindID;
		this->m_ItemToWrite		= _ItemIDToWrite;
		this->_W				= this->_H = 30.0;



		//	Linkers and external...
		{
			this->_Linker_				= _Linker;
			this->_Linker_UniqueID		= _Linker->g_ObjectID();

			this->_BonOBom_				= _BonOBom_;
			this->_BonOBom_UniqueID		= _BonOBom_->g_ObjectID();

			this->_TrackerID_			= _TrackerID;
			this->m_ArrivingTime		= _ArrivalTime;
		}

		//	Calculating the position.
		{
			this->xOrg		= this->xP;
			this->yOrg		= this->yP;
			this->zOrg		= 0.0;

			this->xTarget	= _Linker->g_PositionPrp(1) + (_Linker->g_MeasuresPrp(1) / 2.0);
			this->yTarget	= _Linker->g_PositionPrp(2) - (_Linker->g_MeasuresPrp(2) / 2.0);
			this->zTarget	= _Linker->g_MeasuresPrp(1);
		}

		//	Calculating the arrival factor.
		{
			this->m_FactorSpeed		= 1.0 / (_Controller_Logic::_ogLpV_ * this->m_ArrivingTime);
			this->xFct				= 0.0;
		}
	}

	~LightBon()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateLightBon()
	{
		this->_HasArrived_		= false;

	

		//	Change position.
		{
			//	About the position.
			if (	this->_BonOBom_->g_ObjectID() == this->_BonOBom_UniqueID	)
			{
				this->xP		= this->_BonOBom_->g_PositionPrp(1) + (this->_BonOBom_->g_MeasuresPrp(1) / 2.0);
				this->yP		= this->_BonOBom_->g_PositionPrp(2) - (this->_BonOBom_->g_MeasuresPrp(2) / 2.0);
				this->zP		= 0.0;
			}

			//	About the target.
			if (	this->_Linker_->g_ObjectID() == this->_Linker_UniqueID	)
			{
				this->xTarget	= this->_Linker_->g_PositionPrp(1) + (this->_Linker_->g_MeasuresPrp(1) / 2.0);
				this->yTarget	= this->_Linker_->g_PositionPrp(2) - (this->_Linker_->g_MeasuresPrp(2) / 2.0);
				this->zTarget	= 0.0;
			}

			//	Rotation sides.
			this->rotationDegree	= 360.0 - tls::FindAngle(	this->xP, this->yP, this->xTarget, this->yTarget, false	);
		}

		//	Checking arrival animation.
		{
			if (	 this->m_Time < this->m_ArrivingTime	)
			{
				//	Factor part.
				this->m_Factor		= this->m_Factor + (this->m_FactorSpeed * _Controller_Logic::_fdTime_);
				if (this->m_Factor > 1.0)
				{
					this->m_Factor = 1.0;
				}
			}

			//	Scaling part.
			double		_SpriteLength_ = 120.0;
			this->xFct		= (tls::Lenght(this->xP, this->yP, this->xTarget, this->yTarget) / _SpriteLength_) * this->m_Factor;
		}

		//	Checking if lightbon has arrived.
		{
			if (	(this->m_Time > this->m_ArrivingTime)	&&
								(!this->_End_)				)
			{
				this->_HasArrived_	= true;
				this->_End_			= true;
			}
		}



		this->m_Time = this->m_Time + ((1.0 / _Controller_Logic::_ogLpV_) * _Controller_Logic::_fdTime_);
		++this->m_InnerTime;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline TheCandy*	g_Linker()
	{
		return		this->_Linker_;
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
	inline int			g_ItemIDToWrite()
	{
		return		this->m_ItemToWrite;
	}
	inline bool			g_HasArrived()
	{
		return		this->_HasArrived_;
	}
	inline int			g_TrackerID()
	{
		return		this->_TrackerID_;
	}

	inline double		g_TargetPosition(int What)
	{
		switch (	What	)
		{
		case 1:
			return		this->xTarget;

		case 2:
			return		this->yTarget;

		case 3:
			return		this->zTarget;
		}
	}

	inline int			g_SpritePosition(int What)
	{
		switch (	What	)
		{
		case 1:
			return		(this->xP);

		case 2:
			return		(this->yP);

		default:
			return		def::enm_Defines::_NOT_INITIALIZED;
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
class		_Controller_BonOBom
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
		_LightBon		= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<LightBon*>					m_LightBons;

	std::vector<SpawnPointTracker*>			m_Trackers;

//	-------------------------------------------
//			Variables and constants
//	-------------------------------------------
private:
	const int					$_Common_Candies_Size = 10;

	std::vector<int>			_AmountPerKind_;
	std::vector<bool>			_ChoosenColor_;

	int							_TrackedID_Cnt = 0;

//	-------------------------------------------
//				Amima-riables
//	-------------------------------------------
private:
	double			m_TrackerTime		= 2.0;
	double			m_TrackingDelay		= 0.15;

	double			m_Arrival_LightBons = 0.1;

	bool			m_PlaySound			= false;
	int				Cnt_PlaySound		= 0, Trg_PlaySound = 10;

//	-------------------------------------------
//					Auxiliar vars
//	-------------------------------------------
private:
	int				_Container_Size_	= 0;
	int				_What_Sprite_		= 0;
	int				_What_Kind_			= 0;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------	
private:
	DrawFactory*				_Draw_			= nullptr;
	SpriteFactory*				_Sprites_		= nullptr;
	SoundFactory*				_Sound_			= nullptr;

	_Controller_Score*			_Score_			= nullptr;
	_Controller_SpawnPoints*	_SpawnPoints_	= nullptr;	





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_BonOBom(	SoundFactory* _Sound_Ptr, _Controller_Score* _Score_Ptr		,
							_Controller_SpawnPoints* _SpawnPoints_Ptr					,
							DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr			)
	{
		this->_Sound_			= _Sound_Ptr;
		this->_Draw_			= _Draw_Ptr;
		this->_Sprites_			= _Sprite_Ptr;

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
	
	~_Controller_BonOBom()
	{
		tls::DeleteVector(this->m_Trackers);
		tls::DeleteVector(this->m_LightBons);
	}

//	-------------------------------------------
//				Spawning functions
//	-------------------------------------------
public:
	inline void			AddTracker(	TheCandy* _Linker, double _Time, double _Delay									, 
									tls::Vec4<double> _BoardPos, std::vector<TheCandy*>& _Candies_, int _Where_Pos	,
									int CustomKind, int CustomItemID												)
	{
		int						_FinalKind_		= def::enm_Defines::_NOT_FOUND;
		int						_PopularAmount_ = def::enm_Defines::_NOT_FOUND;
		double					_ExtraDelay_	= 0.35;



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
						//	Can't be a wrapped fuse is already taken when asking if the 
						//	candy can be crushed.



						if (	((0 <= _Candies_[i]->g_Pos(1)) && (0 <= _Candies_[i]->g_Pos(2)))	&&		//	Valid position on board.
								(_Candies_[i]->g_ObjectID() != _Linker->g_ObjectID())				&&		//	Can't count itself.
								(0 < _Candies_[i]->g_KindID())										&&		//	Has a valid kind.
								(_Candies_[i]->g_ItemID() != STA_::enm_ItemID::BomOBom)				&&		//	Can't be a wrapped fuse.
								(!_Candies_[i]->g_Fc_Is(1))	&& (!_Candies_[i]->g_Fc_Is(2))			&&		//	Can't paint and being painted.
								(!_Candies_[i]->g_BoB_Is(1)) && (!_Candies_[i]->g_BoB_Is(2))		&&		//	Can't fuse and being fused.
								(_Candies_[i]->g_Can(2))											)		//	Can be crushed.
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
								_PopularAmount_		= this->_AmountPerKind_[i];
								_FinalKind_			= i + 1;
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
				_ExtraDelay_ = 0.0;
			}
			this->m_Trackers.push_back(	new SpawnPointTracker(	m_TrackerTime, m_TrackingDelay + _ExtraDelay_, m_Arrival_LightBons + 0.5	,
																_FinalKind_, CustomItemID, def::enm_Defines::_SKIP_THIS, _Linker			, 
																_BoardPos, _TrackedID_Cnt, false											)	);
			
			//	Locking the kind from SpawnPoints.
			{
				this->_SpawnPoints_->LockKind(_FinalKind_);
			}

			//	Adjusting the candy properties.
			{
				_Linker->s_BoB_Is(1, true);
				_Linker->s_Can(2, false);
			}

			//	Sound part.
			{
				_Sound_->Play(snd::SndSys::BomOBom, 2);
			}
		}
		else
		{
			//	Here goes some animation where simulates that
			//	the Bon-O-Bom goes crazy and auto-destroy
			//	itself.

			//	Massive Score.
			this->_Score_->AddScore(	_Linker->g_PositionPrp(1), _Linker->g_PositionPrp(2)			, 
										ScoreSys::Bonus_BonOBomNotFound, def::enm_Defines::_SKIP_THIS	,
										false, _Linker->g_KindID()										);

			//	Finally, erase it from vector.
			tls::EraseElement<TheCandy*>(_Candies_, _Where_Pos);
		}
	}
	inline void			SpawnLightBon(		double _xP, double _yP, TheCandy* _What_Candy					,
											int _Kind, int _ItemID, int _TrackerID, TheCandy* What_BonOBom	)
	{
		this->m_LightBons.push_back(	new LightBon(	_xP, _yP, _What_Candy, _Kind, _ItemID	, 
														_TrackerID, this->m_Arrival_LightBons	, 
														What_BonOBom							)	);
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
		case	sMx::BonOBom_CommonCandy:
			//	Code anything here.
			break;

		case	sMx::BonOBom_StrippedHorizontal:
			//	Code anything here.
			break;

		case	sMx::BonOBom_StrippedVertical:
			//	Code anything here.
			break;

		case	sMx::BonOBom_Wrapped:
			//	Code anything here.
			break;

		case	sMx::BonOBom_WrappedFuse:
			//	Code anything here.
			break;

		case	sMx::BonOBom_JellyFish:
			//	Code anything here.
			break;

		case	sMx::BonOBom_StarLight:
			//	Code anything here.
			break;

		case	sMx::BonOBom_FireWork:
			//	Code anything here.
			break;

		case	sMx::BonOBom_BubbleGum:
			//	Code anything here.
			break;

		case	sMx::BonOBom_Popping:
			//	Code anything here.
			break;
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoTrackers(		std::vector<TheCandy*>&		_Candies_	)
	{
		for (	int i = 0; 
				i < this->m_Trackers.size();
				++i)
		{
			//	If tracker ends.
			if (	this->m_Trackers[i]->g_End()	)
			{
				//	When a tracker ends, say that candy (the linked one) to
				//	finish its job and get crushed.
				//
				//	Use this line of code if you don't want the 'being fused' candies
				//	attributte set off if the Bon-o-Bom candy that fused them died.
				// 
				//	if (	this->m_Trackers[i]->g_Linker() != nullptr	)
				{
					//	First of all, from all the frojectiles, let all the linked
					//	candies become matchable.
					//	I'm not using the vector of candies since it can be expensive.
					//	Besides, there is already a vector for this purpose.
					for	(	int c = 0; 
							c < this->m_LightBons.size(); 
							++c	)
					{
						//	Check if the current tracker owns this frojectile.
						if (this->m_LightBons[c]->g_TrackerID() == this->m_Trackers[i]->g_MyUniqueID())
						{
							//	If the linker (or fusing candy) still exists,
							//	then change some properties of the candy.
							if (	this->m_LightBons[c]->g_Linker()->g_ObjectID() == this->m_LightBons[c]->g_Linker_UniqueID()		)
							{
								//	Make Scores!
								this->_Score_->AddScore(	this->m_LightBons[c]->g_Linker()->g_PositionPrp(1)				,
															this->m_LightBons[c]->g_Linker()->g_PositionPrp(2)				,
															ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	,
															this->m_LightBons[c]->g_Linker()->g_KindID()					);			

								this->m_LightBons[c]->g_Linker()->s_BoB_Is(2, 0);		//	Is no longer fused.
								this->m_LightBons[c]->g_Linker()->s_Can(2, true);		//	Can be crushed now.
								this->m_LightBons[c]->g_Linker()->s_Can(3, true);		//	Can be matched as well. 

								this->m_LightBons[c]->g_Linker()->HitOne_HP();												//	Hit One.
								this->m_LightBons[c]->g_Linker()->s_InstaState(TheCandy::enm_InstaState::FusedByBoB);		//	State.
							}

							//	Finally, erase it from vector.
							tls::EraseElement<LightBon*>(this->m_LightBons, c);
						}
					}

					//	Then, as said, the linker candy (in this case the Bom-O-Bom)
					//	will be crushed and die...
					for	(	int c = 0; 
							c < _Candies_.size(); 
							++c	)
					{
						if (	this->m_Trackers[i]->g_Saved_LinkerID() == _Candies_[c]->g_ObjectID()	)
						{
							//	Sound part.
							this->_Sound_->Play(snd::SndSys::BomOBom, 4);

							tls::EraseElement<TheCandy*>(_Candies_, c);
							break;
						}
					}
				}

				//	One more thing, unlock the kind.
				this->_SpawnPoints_->UnlockKind(	this->m_Trackers[i]->g_KindToSearch()	);

				//	Then, erase the tracker when everything is all done.
				this->_ChoosenColor_[this->m_Trackers[i]->g_KindToSearch() - 1] = false;
				tls::EraseElement<SpawnPointTracker*>(this->m_Trackers, i);
				continue;
			}

			//	Finding candy stuff.
			{
				int		_Size_ = _Candies_.size();



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
						if (	(_Candies_[c]->g_KindID() == this->m_Trackers[i]->g_KindToSearch())		&&		//	Does the kind match?
								(!_Candies_[c]->g_Fc_Is(1))												&&		//	Is not painting.
								(!_Candies_[c]->g_Fc_Is(2))												&&		//	Is not being painted by another.
								(!_Candies_[c]->g_BoB_Is(2))											&&		//	Is not being fused by another.
								(_Candies_[c]->g_ItemID() != STA_::enm_ItemID::WrappedFuse)				&&		//	Cannot take a fuse wrapped.
								(_Candies_[c]->g_ItemID() != STA_::enm_ItemID::BomOBom)					&&		//	Nor another Bom-O-Bom.
								(_Candies_[c]->g_ItemAllowsSomething(2)									)	)	//	Item allows fusing?
						{
							//	Create frojectile.
							{
								//	I'm just gonna note that 45.0 is half of the boundaries of
								//	candies. So now you know.

								if (	this->m_Trackers[i]->g_Linker() != nullptr	)
								{
									this->SpawnLightBon(	this->m_Trackers[i]->g_Linker()->g_PositionPrp(1) + 45.0	,
															this->m_Trackers[i]->g_Linker()->g_PositionPrp(2) - 45.0	,
															_Candies_[c]												, 
															this->m_Trackers[i]->g_Linker()->g_KindID()					,
															this->m_Trackers[i]->g_sMx_Item()							,
															this->m_Trackers[i]->g_MyUniqueID()							,
															this->m_Trackers[i]->g_Linker()								);
								}
							}

							//	Set candy properties.
							{
								_Candies_[c]->s_BoB_Is(2, 1);		//	It is now being fused.
								_Candies_[c]->s_Can(2, false);		//	Can't be crushed.
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
	inline void			Animate(		VisualGrid***	_BoardVisual_			)
	{
		//	Just LightBons.
		for (	int i = 0;
				i < this->m_LightBons.size();
				++i	)
		{
			this->m_LightBons[i]->AnimateLightBon();



			if (	this->m_LightBons[i]->g_HasArrived()	)
			{
				//	Sound part.
				{
					if (	this->m_PlaySound	)
					{
						this->_Sound_->Play(snd::SndSys::BomOBom, 3);
						this->m_PlaySound		= false;
					}
				}

				//	Coloring grid.
				if (	this->m_LightBons[i]->g_Linker_UniqueID() == this->m_LightBons[i]->g_Linker()->g_ObjectID()		)
				{
					if (	(0 <= this->m_LightBons[i]->g_Linker()->g_Pos(1))		&&
							(0 <= this->m_LightBons[i]->g_Linker()->g_Pos(2))		)
					{
						_BoardVisual_[this->m_LightBons[i]->g_Linker()->g_Pos(1)][this->m_LightBons[i]->g_Linker()->g_Pos(2)]->UseColorKind(STA_::enm_KindID::_White);
					}
				}

				//	If changes ItemID.
				if (	this->m_LightBons[i]->g_Linker_UniqueID() == this->m_LightBons[i]->g_Linker()->g_ObjectID()		)
				{
					//	There are some special cases where the ItemID
					//	changes the behaviour of some candies like:
					//	Stripped candies.
					if (	this->m_LightBons[i]->g_ItemIDToWrite() != def::enm_Defines::_SKIP_THIS	)
					{
						switch (	this->m_LightBons[i]->g_ItemIDToWrite()		)
						{
						case	STA_::enm_ItemID::StrippedH:
						case	STA_::enm_ItemID::StrippedV:
							this->m_LightBons[i]->g_Linker()->s_ItemID(STA_::enm_ItemID::StrippedH + tls::Random(0, 1));
							break;

						default:
							this->m_LightBons[i]->g_Linker()->s_ItemID(this->m_LightBons[i]->g_ItemIDToWrite());
						}
					}
				}
			}
		}

		//	Play sound chill.
		if (	!this->m_PlaySound	)
		{
			if (	this->Cnt_PlaySound < (this->Trg_PlaySound * _Controller_Logic::_fdTime_)	)
			{
				++this->Cnt_PlaySound;
			}
			else
			{
				this->Cnt_PlaySound		= 0;
				this->m_PlaySound		= true;
			}
		}
	}

	

	inline void			Draw(	int What	)
	{
		//	LightBon.
		if (	enm_Draw::_LightBon == What		)
		{
			this->_Container_Size_		= this->m_LightBons.size();
			this->_What_Sprite_			= spr::enm_At::BoB_Contents;
			this->_What_Kind_			= 0;



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				//	Draw the LightBon.
				{
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_LightBons[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(this->m_LightBons[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))	);
					
					//	Applying color properties. 
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_LightBons[i]->g_ColorPrp(1)	,
																														this->m_LightBons[i]->g_ColorPrp(2)	,
																														this->m_LightBons[i]->g_ColorPrp(3)	,
																														this->m_LightBons[i]->g_ColorPrp(4)	)	);
					
					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_LightBons[i]->g_VisualPrp(1)	,
																												this->m_LightBons[i]->g_VisualPrp(2)	);

					//	Spining.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(		this->m_LightBons[i]->g_RotationPrp(1)	);
					
					
					
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
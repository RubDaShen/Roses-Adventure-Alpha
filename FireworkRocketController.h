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



class		FireWorkEntity : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_KindID		= 0;
	int			m_iPos_Des		= 0, m_jPos_Des = 0;

	double		m_FlightTime	= 0.0;
	double		m_Time			= 0.0;
	double		m_yP_Org		= 0.0;

	bool		m_HasArrived	= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FireWorkEntity(	TheCandy* _Candy_Ptr							, 
					int _Flight, double _FlightTime					,
					double _BoardGridHeight							) : thyObject(	_Candy_Ptr->g_PositionPrp(1)			,
																					_Candy_Ptr->g_PositionPrp(2)			,
																					def::enm_ObjectType::FireWorkEntity		)
	{
		//	Setting some values.
		this->m_KindID		= _Candy_Ptr->g_KindID();
		this->m_FlightTime	= _FlightTime;

		this->_W	= 90.0;
		this->_H	= 90.0;

		//	Calculating destination.
		//	Using Aceleration Motion.
		double			_Distance_ = 0;

		//	Firework distance calculation.
		if (	(_Candy_Ptr->g_Pos(1) - _Flight) < 1	)
		{
			_Flight		= _Candy_Ptr->g_Pos(1) - 1;
			_Distance_	= _Flight * _BoardGridHeight;
		}
		else
		{
			_Distance_	= _Flight * _BoardGridHeight;
		}

		//	Destination on board.
		this->m_iPos_Des		= _Candy_Ptr->g_Pos(1) - _Flight;
		this->m_jPos_Des		= _Candy_Ptr->g_Pos(2);

		//	Movement calculation.
		this->m_yP_Org	= this->yP;

		if (	_Distance_ <= 0.0	)
		{
			m_FlightTime		= 0.0;	
			this->yA			= 0.0;

			if (_Distance_ == 0.0)
			{
				this->m_iPos_Des = 1;
			}
			else
			{
				this->m_iPos_Des = 0;
			}
		}
		else
		{
			this->yA		= (2.0 * _Distance_) / (this->m_FlightTime * this->m_FlightTime);
		}
	}

	~FireWorkEntity()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	About positions.
		this->yP		= this->m_yP_Org + (0.5 * this->yA * this->m_Time * this->m_Time);

		//	Time and times.
		this->m_Time = this->m_Time + (1.0 / GAME_LOOP_VALUE);

		//	Final condition.
		if (	this->m_FlightTime < this->m_Time	)
		{
			this->m_HasArrived		= true;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int		g_KindID()
	{
		return		this->m_KindID;
	}
	inline bool		g_HasArrived()
	{
		return		this->m_HasArrived;
	}
	inline int		g_PosDestination(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		this->m_iPos_Des;

		case 2:
			return		this->m_jPos_Des;
		}
	}

	inline int		g_SpritePosition(int _What)
	{
		switch (_What)
		{
		case 1:
			return	(this->xP + (this->_W / 2.0));

		case 2:
			return	(this->yP - (this->_H / 2.0));
		}
	}
};
class	FireWorkEmber : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		m_AirResistance		= 0.00;
	double		m_Gravity			= -0.01;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FireWorkEmber(	double _xP, double _yP	,
					int _KindID				) : thyObject(_xP, _yP, def::enm_ObjectType::FireWorkEmber)
	{
		this->_W = 15.0,	this->_H = 15.0;

		tls::SetRGB(_KindID, this->R_col, this->G_col, this->B_col);
	}

	~FireWorkEmber()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	Position...
		this->xP		= this->xP + this->xS;
		this->yP		= this->yP + this->yS;
		this->yS		= this->yS + this->m_Gravity;

		//	Color...
		this->A_alpha	= this->A_alpha + this->Alpha_s;
		if (	this->A_alpha <= 0.0	)
		{
			this->A_alpha = 0.0;
		}

		//	Visual...
		this->xFct		= this->xFct + this->xFctS;
		this->yFct		= this->xFct;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int		g_SpritePosition(int _What)
	{
		switch (_What)
		{
		case 1:
			return	(this->xP + (this->_W / 2.0));

		case 2:
			return	(this->yP - (this->_H / 2.0));
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
class _Controller_FireworkRocket
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_FireWorkRocket		= 0,
		_BigGlow			= 1,
		_FireWorkEmber		= 2,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<FireWorkEntity*>		m_FireWorks;
	std::vector<FireWorkEmber*>			m_Embers;
	std::vector<GlowParticle*>			m_BigGlow;

//	-------------------------------------------
//			Variables and constants
//	-------------------------------------------
private:
	int			m_FireworkFlight	= 4;
	float		m_FlightTime		= 0.65f;

	int			_BoardWidth_		= 0, _BoardHeight_ = 0;

//	-------------------------------------------
//					Amima-riables
//	-------------------------------------------
private:
	int			m_DistanceFromCenter	= 5;
	int			m_AmountPerLayer		= 9;
	double		m_ExplosionForce		= 0.9;
	int			m_EmberLifeTime_From	= 6, m_EmberLifeTime_To		= 11;
	int			m_Layers				= 4;
	int			m_BigGlowLifeTime		= 50;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	SoundFactory*			_Sound_		= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
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
	_Controller_FireworkRocket( DrawFactory* _Draw_Ptr			,
								SpriteFactory* _Sprite_Ptr		,
								SoundFactory* _Sound_Ptr		,
								_Controller_Score* _Score_Ptr	)
	{
		this->_Draw_			= _Draw_Ptr;
		this->_Sprites_			= _Sprite_Ptr;
		this->_Sound_			= _Sound_Ptr;
		this->_Scores_			= _Score_Ptr;
	}
	
	~_Controller_FireworkRocket()
	{
		tls::DeleteVector(this->m_FireWorks);
		tls::DeleteVector(this->m_Embers);
		tls::DeleteVector(this->m_BigGlow);
	}

//	-------------------------------------------
//				Spawning functions
//	-------------------------------------------
public:
	inline void			SpawnFireWork(	TheCandy* _Candy_Ptr, double _BoardGridHeight	)
	{
		this->m_FireWorks.push_back(	new FireWorkEntity(		_Candy_Ptr						,
																m_FireworkFlight, m_FlightTime	,
																_BoardGridHeight				)	);
	}
	inline void			SpawnEmberExplosion(	FireWorkEntity* _FireWork_Ptr	)
	{
		double			_AngleSeparator_	= 360.0 / this->m_AmountPerLayer;
		int				_RandomAngle_		= tls::Random(0, 360);
		int				_RandomLifeTime_	= 0;

		int				_ExtraAmount_		= this->m_AmountPerLayer;
		int				_ExtraDistance_		= this->m_DistanceFromCenter;
		double			_ExtraForce_		= this->m_ExplosionForce;



		for (	int c = 0; 
				c < this->m_Layers; 
				++c	)
		{
			//	Actual layer.
			for (	int i = 0; 
					i < _ExtraAmount_;
					++i	)
			{
				_RandomLifeTime_	= tls::Random(this->m_EmberLifeTime_From, this->m_EmberLifeTime_To);



				//	Creating the ember.
				this->m_Embers.push_back(	new FireWorkEmber(	_FireWork_Ptr->g_PositionPrp(1) + (std::cos(tls::DegToRad(_RandomAngle_)) * _ExtraDistance_) + 45.0,
																_FireWork_Ptr->g_PositionPrp(2) + (std::sin(tls::DegToRad(_RandomAngle_)) * _ExtraDistance_) - 45.0,
																_FireWork_Ptr->g_KindID()									)	);

				//	About speed properties.
				this->m_Embers[this->m_Embers.size() - 1]->s_PositionPrp(	3, _ExtraForce_ * std::cos(tls::DegToRad(_RandomAngle_))	);
				this->m_Embers[this->m_Embers.size() - 1]->s_PositionPrp(	4, _ExtraForce_ * std::sin(tls::DegToRad(_RandomAngle_))	);

				//	About color properties.
				this->m_Embers[this->m_Embers.size() - 1]->s_ColorPrp(	6, -255.0 / (_RandomLifeTime_ * GAME_LOOP_VALUE * 0.1)	);
			
				//	About visual properties.
				this->m_Embers[this->m_Embers.size() - 1]->s_VisualPrp(	3, -1.0 / (_RandomLifeTime_ * GAME_LOOP_VALUE * 0.1)		);

			

				_RandomAngle_		= _RandomAngle_ + _AngleSeparator_;
			}

			//	Increase some values per layer.
			{
				_ExtraAmount_		= _ExtraAmount_ + 6;
				_ExtraDistance_		= _ExtraDistance_ + 10;
				_ExtraForce_		= _ExtraForce_ + 0.45;

				_RandomAngle_		= tls::Random(0, 360);
				_AngleSeparator_	= 360.0 / _ExtraAmount_;
			}
		}
	}
	inline void			SpawnBigGlow(			FireWorkEntity* _FireWork_Ptr	)
	{
		this->m_BigGlow.push_back(	new GlowParticle(	_FireWork_Ptr->g_PositionPrp(1) + 45.0	,
														_FireWork_Ptr->g_PositionPrp(2)	- 45.0	, 
														GlowID::XLGlow, AnmGlow::StaticGlow		, 
														_FireWork_Ptr->g_KindID()				)	);

		//	The default measure of the sprite is 400x400 pixels.
		//	this->m_BigGlow[this->m_BigGlow.size() - 1]->s_MeasuresPrp(		1, 400.0	);
		//	this->m_BigGlow[this->m_BigGlow.size() - 1]->s_MeasuresPrp(		2, 400.0	);

		//	Setting the glow animation values.
		this->m_BigGlow[this->m_BigGlow.size() - 1]->s_Opacity_WithContainer(		tls::Vec3<double>(255, -255.0 / (this->m_BigGlowLifeTime * GAME_LOOP_VALUE * 0.1), 0.0)		);
	}
	inline void			BlowUpCandies(		FireWorkEntity* _FireWork_Ptr	, 
											thyGrid_Logic*** _TheGrid_		,
											std::vector<TheCandy*>& _Candies)
	{
		int		_iPos_	= 0, _jPos_ = 0;
		int		_At_	= 0;



		for (	int i = 0; 
				i < 5; 
				++i	)
		{
			//	This is just case selecting, not too complex.
			switch (i)
			{
			case 0:		//	Center.
				_iPos_		= _FireWork_Ptr->g_PosDestination(1);
				_jPos_		= _FireWork_Ptr->g_PosDestination(2);
				break;

			case 1:		//	Up Left.
				_iPos_		= _FireWork_Ptr->g_PosDestination(1) - 1;
				_jPos_		= _FireWork_Ptr->g_PosDestination(2) - 1;
				break;

			case 2:		//	Up Right
				_iPos_		= _FireWork_Ptr->g_PosDestination(1) - 1;
				_jPos_		= _FireWork_Ptr->g_PosDestination(2) + 1;
				break;

			case 3:		//	Down Left
				_iPos_		= _FireWork_Ptr->g_PosDestination(1) + 1;
				_jPos_		= _FireWork_Ptr->g_PosDestination(2) - 1; 
				break;

			case 4:		//	Down Right
				_iPos_		= _FireWork_Ptr->g_PosDestination(1) + 1;
				_jPos_		= _FireWork_Ptr->g_PosDestination(2) + 1; 
				break;
			}

			//	Validation out of array.
			if (	((_iPos_ < 0) || (this->_BoardHeight_ <= _iPos_))	||
					((_jPos_ < 0) || (this->_BoardWidth_ <= _jPos_))	)
			{
				continue;
			}

			//	Get the _At_ candy.
			_At_		= _TheGrid_[_iPos_][_jPos_]->g_CandyAt();
			if (_At_ == def::enm_Defines::_NOT_FOUND)
			{
				continue;
			}
		
			//	Do some crush.
			_Candies[_At_]->HitOne_HP();
			_Candies[_At_]->s_Can(2, true);
			this->_Scores_->AddScore(	_Candies[_At_]->g_PositionPrp(1), _Candies[_At_]->g_PositionPrp(2)						, 
										ScoreSys::NormalCandy, def::enm_Defines::_SKIP_THIS, false, _Candies[_At_]->g_KindID()	);
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate(	thyGrid_Logic*** _TheGrid_			,
									std::vector<TheCandy*>& _Candies	)
	{
		//	Animating the fireworks.
		{
			for (	int i = 0;
					i < this->m_FireWorks.size();
					++i	)
			{
				//	Just animate.
				this->m_FireWorks[i]->Animate();

				//	Final condition.
				if (	this->m_FireWorks[i]->g_HasArrived()	)
				{
					//	Spawning and animations.c
					this->BlowUpCandies(this->m_FireWorks[i], _TheGrid_, _Candies);
					this->SpawnEmberExplosion(		this->m_FireWorks[i]		);
					this->SpawnBigGlow(				this->m_FireWorks[i]		);

					//	Delete object.
					tls::EraseElement(this->m_FireWorks, i);

					//	SoUnD!
					this->_Sound_->Play(snd::SndSys::FireWorkRocket, 3);
				}
			}
		}

		//	Animating the embers.
		{
			for (	int i = 0;
					i < this->m_Embers.size();
					++i	)
			{
				//	Just animate.
				this->m_Embers[i]->Animate();

				//	Final condition.
				if (	this->m_Embers[i]->g_ColorPrp(4) <= 0.0	)
				{
					tls::EraseElement(this->m_Embers, i);
				}
			}
		}		

		//	Animating the big glow.
		{
			for (	int i = 0;
					i < this->m_BigGlow.size();
					++i	)
			{
				//	Just animate.
				this->m_BigGlow[i]->AnimateParticle();

				//	Final condition.
				if (	this->m_BigGlow[i]->g_ColorPrp(4) <= 0.0	)
				{
					tls::EraseElement(this->m_BigGlow, i);
				}
			}
		}
	}

	inline void			Draw(	int What	)
	{
		//	FireWorkRocket.
		if (	enm_Draw::_FireWorkRocket == What	)
		{
			this->_What_Sprite_			= spr::enm_At::FireWorkRocket;
			this->_What_Kind_			= 0;
			this->_Container_Size_		= this->m_FireWorks.size();



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_		= this->m_FireWorks[i]->g_KindID() - 1;



				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_FireWorks[i]->g_SpritePosition(1), _Draw_->g_WorldBounds(1)	)	,
																													tls::FixPos_Y(	this->m_FireWorks[i]->g_SpritePosition(2), _Draw_->g_WorldBounds(2)	)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}	
		}

		//	BigGlow.
		if (		enm_Draw::_BigGlow == What		)
		{
			this->_Container_Size_		= this->m_BigGlow.size();
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_What_Kind_			= GlowID::XLGlow;



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				//	Fix position to properly render on screen.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_BigGlow[i]->g_SpritePosition(1), _Draw_->g_WorldBounds(1)	),
																											tls::FixPos_Y(	this->m_BigGlow[i]->g_SpritePosition(2), _Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_BigGlow[i]->g_ColorPrp(1)	,
																														this->m_BigGlow[i]->g_ColorPrp(2)	,
																														this->m_BigGlow[i]->g_ColorPrp(3)	,
																														this->m_BigGlow[i]->g_ColorPrp(4)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_BigGlow[i]->g_VisualPrp(1)	, 
																											this->m_BigGlow[i]->g_VisualPrp(2)	);



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	
		//	FireWorkEmber.
		if (	enm_Draw::_FireWorkEmber == What	)
		{
			this->_Container_Size_		= this->m_Embers.size();
			this->_What_Sprite_			= spr::enm_At::FwR_Contents;
			this->_What_Kind_			= 0;



			for (	int i = 0;
					i < this->_Container_Size_;
					++i	)
			{
				//	Fix position to properly render on screen.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Embers[i]->g_SpritePosition(1), _Draw_->g_WorldBounds(1)	),
																											tls::FixPos_Y(	this->m_Embers[i]->g_SpritePosition(2), _Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_Embers[i]->g_ColorPrp(1)	,
																														this->m_Embers[i]->g_ColorPrp(2)	,
																														this->m_Embers[i]->g_ColorPrp(3)	,
																														255									)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Embers[i]->g_VisualPrp(1) 	,
																											this->m_Embers[i]->g_VisualPrp(2)	);


				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), true, drw::MyCanvas::FireWorkCanvas);
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline bool			g_IsEmpty()
	{
		return		this->m_FireWorks.empty();
	}

	inline void			SetBoardBounds(		int _BoardWidth, int _BoardHeight	)
	{
		this->_BoardWidth_		= _BoardWidth;
		this->_BoardHeight_		= _BoardHeight;
	}
};
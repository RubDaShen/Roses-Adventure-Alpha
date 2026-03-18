#pragma once

#include		<vector>

#include		"thyObject.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"SoundFactory.h"
#include		"TheCandy.h"
#include		"SQLStuff.h"



class		Coin : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		m_Gravity			= -0.045;
	double		m_Bouncy			= 1.4;
	double		m_BouncingLimit		= 0.2;

//	-------------------------------------------
//				External and Linkers
//	-------------------------------------------
private:
	DrawFactory*		_Draw_ = nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Coin(	TheCandy*	_Candy_, DrawFactory* _Draw_Ptr	) : thyObject(	_Candy_->g_PositionPrp(1) + (_Candy_->g_MeasuresPrp(1) * 0.5)	,
																		_Candy_->g_PositionPrp(2) - (_Candy_->g_MeasuresPrp(2) * 0.5)	,
																		def::enm_ObjectType::Coin										)
	{
		this->_Draw_			= _Draw_Ptr;
		double		_Angle_		= _Candy_->g_CrushingProperties(1);
		double		_Speed_		= _Candy_->g_CrushingProperties(2);
		if (	_Angle_ == def::enm_Defines::_USE_DEFAULT	)
		{
			_Angle_		= tls::Random(0, 360);
		}
		if (	_Speed_ == 0.0	)
		{
			_Speed_		= 0.75;
		}



		//	Important values.
		{
			this->xS			= 5.0 * _Speed_;
			this->yS			= _Speed_;
			this->xA			= 0.0035;
			
			this->_W			= 75.0,	this->_H			= 75.0;
			this->_r			= this->_W * 0.5;
			this->_W_Sprite		= 68,	this->_H_Sprite		= 68;
		}

		//	Position values.
		{
			//	Speeds !
			this->xS = this->xS * std::cos(		tls::DegToRad(_Angle_)		);
			this->yS = this->yS * std::sin(		tls::DegToRad(_Angle_)		);
		}
	}

	~Coin()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			MoveCoin()
	{
		//	Apply position changes.
		{
			this->xP	= this->xP + this->xS;
			this->yP	= this->yP + this->yS;
		}

		//	Case for xS...
		{
			//	Means that xS is negative, so xA (positive) needs to
			//	deacelerate this particle.
			if (	this->xS < 0.0	)
			{
				this->xS = this->xS + this->xA;
			}
			else
			{
				//	Means that xS is positive, so xA (negative) needs to
				//	deacelerate this particle.
				if (	this->xS > 0.0	)
				{
					this->xS = this->xS - this->xA;
				}
			}

			//	Stop moving at all.
			if (	std::fabs(this->xS) < this->xA	)
			{
				this->xA = this->xS = 0.0;
			}



			//	Borders hit.
			if (	this->xP < this->_Draw_->GetCameraLimits(def::enm_CameraLimits::LeftBorder)		)
			{
				this->xP	= this->_Draw_->GetCameraLimits(def::enm_CameraLimits::LeftBorder);
				this->xS	= (this->xS * -1.0) / this->m_Bouncy;
			}
			else
			{
				if (	this->_Draw_->GetCameraLimits(def::enm_CameraLimits::RightBorder) < (this->xP + this->_W_Sprite)	)
				{
					this->xP	= this->_Draw_->GetCameraLimits(def::enm_CameraLimits::RightBorder) - this->_W_Sprite;
					this->xS	= (this->xS * -1.0) / this->m_Bouncy;
				}
			}
		}

		//	Case for yS...
		{		
			//	Ground hit.
			if (	this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Floor) < (this->yP - this->_W_Sprite)	)
			{
				this->yP	= this->yP + this->yS;
				this->yS	= this->yS + this->m_Gravity;
			}
			else
			{
				this->yP	= this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Floor) + this->_W_Sprite;
				this->yS	= (this->yS * -1.0) / this->m_Bouncy;

				if (	fabs(this->yS) <= this->m_BouncingLimit	)
				{
					this->yS = 0.0;
				}
			}
		}
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
class		_Controller_Coin
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
		_Coin	= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<Coin*>		m_Coins;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			Rnd_CoinSpawn	= 0.01;		//	0.01

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	SoundFactory*			_Sounds_	= nullptr;
	_Basic_Mouse*			_Mouse_		= nullptr;
	sql::SQLConnector*		_SQL_		= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Coin(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	, 
						SoundFactory* _Sound_Ptr, _Basic_Mouse* _Mouse_Ptr	,
						sql::SQLConnector* _SQL_Ptr							)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sounds_		= _Sound_Ptr;
		this->_Mouse_		= _Mouse_Ptr;
		this->_SQL_			= _SQL_Ptr;
	}

	~_Controller_Coin()
	{
		tls::DeleteVector(this->m_Coins);
	}

//	-------------------------------------------
//					Events
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{
		//	Picking up coins.
		if (	this->_Mouse_->g_Is(3)	)
		{
			for (	int i = 0;
					i < this->m_Coins.size(); 
					++i	)
			{
				if (	tls::RectangleCollidesWithCircle(	this->_Mouse_->g_Position_Camera(4, 1, this->_Draw_->g_CurrentCamera())				, 
															this->_Mouse_->g_Position_Camera(4, 2, this->_Draw_->g_CurrentCamera()), 1.0, 1.0	,
															this->m_Coins[i]->g_SpritePosition(1)	,
															this->m_Coins[i]->g_SpritePosition(2)	,
															this->m_Coins[i]->g_MeasuresPrp(3)		)	)
				{
					tls::EraseElement(this->m_Coins, i);
					this->_Sounds_->Play(snd::SndSys::Coin, 2);
					break;
				}
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddCoin(	TheCandy* Candy	)
	{
		if (	tls::Probability(this->Rnd_CoinSpawn, 2)	)
		{
			this->m_Coins.push_back(	new Coin(Candy, this->_Draw_)		);

			this->_Sounds_->Play(snd::SndSys::Surprise, 1);
		}
	}
	inline void			Animate()
	{
		//	Coin.
		for (	int i = 0; 
				i < this->m_Coins.size(); 
				++i	)
		{
			this->m_Coins[i]->MoveCoin();
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Coin.
		if (	enm_Draw::_Coin == What		)
		{
			this->_What_Sprite_			= spr::enm_At::CoinsAndSurprises;
			this->_Container_Size_		= this->m_Coins.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Coins[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))		,
																											tls::FixPos_Y(	this->m_Coins[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))		);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:

};
#pragma once

#include		"Tools_.h"
#include		"AfterGlows.h"
#include		"_MyIncludes_.h"
#include		"LogicalController.h"

#include		<vector>



class		CrushingParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double		_Gravity_ = -0.00175;

//	-------------------------------------------
//				Important values
//	-------------------------------------------
private:
	int				m_KindID	= def::enm_Defines::_NOT_INITIALIZED;
	int				m_CrushID	= def::enm_Defines::_NOT_INITIALIZED;

	int				m_Time			= 0;
	int				m_SpawnTick		= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	CrushingParticle(	double _xP, double _yP, int _KindID, int _CrushID	, 
						double _Angle, double _ExtraSpeed					,
						int SpawnTick										) : thyObject(_xP, _yP, def::enm_ObjectType::CrushParticle)
	{
		//	Important values.
		{
			this->m_KindID		= _KindID;
			this->m_CrushID		= _CrushID;
			this->m_SpawnTick	= SpawnTick / _Controller_Logic::_fdTime_;



			this->xS		= 3.0 * _ExtraSpeed;
			this->yS		= 1.0 * _ExtraSpeed;
			this->xA		= this->yA = 0.02;
			
			this->_W		= 30.0;
			this->_H		= 30.0;

			this->Alpha_s		= -1.5;

			this->xFct		= this->yFct = 0.75;
			this->xFctS		= -0.0065;
			this->yFctS		= -0.0065;
		}

		//	Position values.
		{
			//	Speeds !
			this->xS = this->xS * std::cos(		tls::DegToRad(_Angle));
			this->yS = this->yS * std::sin(		tls::DegToRad(_Angle));

			//	Aceleration !
			this->xA = this->xA * tls::UnityRound(	std::cos(tls::DegToRad(_Angle))	);
			this->yA = this->yA * tls::UnityRound(	std::sin(tls::DegToRad(_Angle))	);

			//	Rotation !
			this->rotationSpeed = tls::Random(2, 6) * tls::UnityRound(std::cos(tls::DegToRad(_Angle)));
		}
	}

	~CrushingParticle()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoParticle()
	{
		//	Apply position changes.
		{
			this->xP = this->xP + (this->xS * _Controller_Logic::_fdTime_);
			this->yP = this->yP + (this->yS * _Controller_Logic::_fdTime_);
		}

		//	Case for xS...
		{
			//	Means that xS is negative, so xA (positive) needs to
			//	deacelerate this particle.
			if ((this->xS + this->xA) < 0.0)
			{
				this->xS = this->xS + (this->xA * _Controller_Logic::_fdTime_);
			}
			else
			{
				//	Means that xS is positive, so xA (negative) needs to
				//	deacelerate this particle.
				if ((this->xS + this->xA) > 0.0)
				{
					this->xS = this->xS + (this->xA * _Controller_Logic::_fdTime_);
				}
				else
				{
					//	End moving.
					this->xS = this->xA = 0.0;
				}
			}
		}

		//	Case for yS...
		{
			this->yS = this->yS + (this->yA * _Controller_Logic::_fdTime_);
			this->yA = this->yA + (this->_Gravity_ * _Controller_Logic::_fdTime_);
		}




		//	Shrinking part.
		{
			this->xFct = this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
			this->yFct = this->yFct + (this->yFctS * _Controller_Logic::_fdTime_);



			if ((this->xFct <= 0.0))
			{
				this->xFct = 0.0;
			}

			if ((this->yFct <= 0.0))
			{
				this->yFct = 0.0;
			}
		}

		//	Opacity.
		{
			this->A_alpha = this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

			if (this->A_alpha <= 0.0)
			{
				this->A_alpha = 0.0;
			}
		}

		//	Rotating side.
		{
			this->rotationDegree = this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
		}



		//	Time.
		{
			++this->m_Time;
		}
	}
	inline bool			SpawnsGlow()
	{
		return		!static_cast<bool>(this->m_Time % this->m_SpawnTick);
	}

//	-------------------------------------------
//				Setters and Getters !
//	-------------------------------------------
public:
	inline void			s_ID(	int _What, int _Val	)
	{
		switch (_What)
		{
		case 1:
			 this->m_KindID = _Val;
			 break;

		case 2:
			this->m_CrushID = _Val;
			break;
		}
	}

	inline int			g_ID(	int What	)
	{
		switch (	What	)
		{
		case 1:
			return		this->m_KindID;

		case 2:
			return		this->m_CrushID;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
		
	}

	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		(this->xP + (this->_W_Sprite * 0.5));

		case 2:
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
class		_Controller_CrushEffect
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
		_SquareGlow			= 0,
		_Glow				= 1,
		_CrushEffect		= 2,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<CrushingParticle*>		m_Crushes;
	std::vector<GlowParticle*>			m_Glow;
	std::vector<GlowParticle*>			m_SquareGlow;

//	-------------------------------------------
//				Variables for crushing
//	-------------------------------------------
private:
	int				Amt_Crush_From		= 5;
	int				Amt_Crush_To		= 7;

	int				Tck_GlowSpawn		= static_cast<int>(_Controller_Logic::_gLpVal_ * 1.0);
	int				RadiousDistance		= 15;
	double			m_GlowLifetime		= 0.85;
	double			m_SpeedFactor		= 0.55;

	double			m_Deg_Xplosion		= 100.0;

//	-------------------------------------------
//					Other options
//	-------------------------------------------
public:
	bool			m_DefaultAnm	= true;
	double			_Auxiliar_		= 0;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
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
	_Controller_CrushEffect(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
	}

	~_Controller_CrushEffect()
	{
		tls::DeleteVector(this->m_Crushes);
		tls::DeleteVector(this->m_Glow);
		tls::DeleteVector(this->m_SquareGlow);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddCrush(	TheCandy* Candy		)
	{
		int			_Crush_Size			= 0;
		int			_Random_CrushID_	= 0;

		int			_Xplosion_Amt		= tls::Random(this->Amt_Crush_From, this->Amt_Crush_To);
		double		_Separator_Angle	= 0;

		int			_Angle_			= Candy->g_CrushingProperties(1);
		double		_ExtraSpeed_	= Candy->g_CrushingProperties(2);



		//	Explosion direction and intensity.
		{
			if (_Angle_ == def::enm_Defines::_USE_DEFAULT)
			{
				_Angle_				= tls::Random(0, 360);
				_Separator_Angle	= (360.0 / _Xplosion_Amt);
				_ExtraSpeed_		= 1.0;
			}
			else
			{
				_Angle_				= _Angle_ - (this->m_Deg_Xplosion / 3.0);
				_Separator_Angle	= (this->m_Deg_Xplosion / _Xplosion_Amt);
			}
		}

		//	Square glow particles
		{
			this->m_SquareGlow.push_back(	new GlowParticle(		Candy->g_PositionPrp(1), Candy->g_PositionPrp(2)	,
																	1, 2, Candy->g_KindID()								)	);



			this->m_SquareGlow[this->m_SquareGlow.size() - 1]->s_Opacity_WithContainer(	tls::Vec3<double>(	255.0, -1.964, 0.0 )	);
			this->m_SquareGlow[this->m_SquareGlow.size() - 1]->s_MeasuresPrp(	1, this->_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Measures()->at(1).Third		);
			this->m_SquareGlow[this->m_SquareGlow.size() - 1]->s_MeasuresPrp(	2, this->_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Measures()->at(1).Fourth	);
		}

		//	Crushing particles.
		{
			for (	int i = 0; 
					i < _Xplosion_Amt;
					++i	)
			{			
				//	Crushes particles!
				{
					_Random_CrushID_	= tls::Random(1, 3);

					this->m_Crushes.push_back(		new CrushingParticle(	Candy->g_PositionPrp(1), Candy->g_PositionPrp(2)	,
																			Candy->g_KindID(), _Random_CrushID_					,	
																			_Angle_, _ExtraSpeed_, this->Tck_GlowSpawn			)	);

					_Crush_Size = this->m_Crushes.size() - 1;



					this->m_Crushes[_Crush_Size]->s_SpriteMeasures(	1, this->_Sprites_->g_Sprite(spr::enm_At::CrushingParticles)->g_Measures()->at(_Random_CrushID_ - 1).Third		);
					this->m_Crushes[_Crush_Size]->s_SpriteMeasures(	2, this->_Sprites_->g_Sprite(spr::enm_At::CrushingParticles)->g_Measures()->at(_Random_CrushID_ - 1).Fourth		);
				}



				_Angle_ = _Angle_ + _Separator_Angle;
			}
		}
	}
	inline void			Animate()
	{
		//	Crush particles.
		{
			for (	int i = 0; 
					i < this->m_Crushes.size(); 
					++i	)
			{			
				if (		this->m_Crushes[i]->SpawnsGlow()		&&
						0.65 < this->m_Crushes[i]->g_VisualPrp(1)	)
				{
					this->_Auxiliar_		= tls::DegToRad(	tls::Random(0, 360)		);



					this->m_Glow.push_back(new GlowParticle(	this->m_Crushes[i]->g_SpritePosition(1) + (this->RadiousDistance * std::cos(this->_Auxiliar_))	,
																this->m_Crushes[i]->g_SpritePosition(2) + (this->RadiousDistance * std::sin(this->_Auxiliar_))	,
																0, 1, this->m_Crushes[i]->g_ID(1)																)	);



					this->m_Glow[this->m_Glow.size() - 1]->s_Pos_WithContainer(tls::Vec4<double>(	this->m_Crushes[i]->g_PositionPrp(3) * this->m_SpeedFactor	, 
																									this->m_Crushes[i]->g_PositionPrp(4) * this->m_SpeedFactor	,
																									0.0, 0.0													)	);

					this->m_Glow[this->m_Glow.size() - 1]->s_Visual_WithContainer(tls::Vec2<double>(	0.85, -1.0 / (_Controller_Logic::_ogLpV_ * this->m_GlowLifetime)));

					this->m_Glow[this->m_Glow.size() - 1]->s_Opacity_WithContainer(tls::Vec3<double>(	255.0, -255.0 / (_Controller_Logic::_ogLpV_ * this->m_GlowLifetime), 0.0)	);

					this->m_Glow[this->m_Glow.size() - 1]->s_Rotation_WithContainer(	tls::Vec3<double>(	tls::Random(0, 360), 1.0, 0.0	));
					
				}
				this->m_Crushes[i]->DoParticle();



				if (this->m_Crushes[i]->g_ColorPrp(4) <= 0.0)
				{
					tls::EraseElement<CrushingParticle*>(this->m_Crushes, i);
				}
			}
		}

		//	Glow particles.
		{
			for (	int i = 0; 
					i < this->m_Glow.size(); 
					++i	)
			{
				this->m_Glow[i]->AnimateParticle();

				if (this->m_Glow[i]->g_ColorPrp(4) <= 0.0)
				{
					tls::EraseElement<GlowParticle*>(this->m_Glow, i);
				}
			}
		}

		//	Square Glow particles.
		{
			for (	int i = 0; 
					i < this->m_SquareGlow.size(); 
					++i	)
			{
				this->m_SquareGlow[i]->AnimateParticle();

				if (this->m_SquareGlow[i]->g_ColorPrp(4) <= 0.0)
				{
					tls::EraseElement<GlowParticle*>(this->m_SquareGlow, i);
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
		//	Square Glow.
		if (	What == enm_Draw::_SquareGlow	)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_Container_Size_		= this->m_SquareGlow.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				this->_What_Kind_ = this->m_SquareGlow[i]->g_GlowID();



				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_SquareGlow[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))		,
																											tls::FixPos_Y(	this->m_SquareGlow[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))		);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_SquareGlow[i]->g_ColorPrp(1)	,
																														this->m_SquareGlow[i]->g_ColorPrp(2)	, 
																														this->m_SquareGlow[i]->g_ColorPrp(3)	, 
																														this->m_SquareGlow[i]->g_ColorPrp(4)	)	);

				



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Glow Particle.
		if (	What == enm_Draw::_Glow		)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_Container_Size_		= this->m_Glow.size();



			for (int i = 0; i < this->_Container_Size_; ++i)
			{
				this->_What_Kind_		= this->m_Glow[i]->g_GlowID();



				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Glow[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Glow[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_Glow[i]->g_ColorPrp(1)	,
																													this->m_Glow[i]->g_ColorPrp(2)	, 
																													this->m_Glow[i]->g_ColorPrp(3)	, 
																													this->m_Glow[i]->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Glow[i]->g_VisualPrp(1)		,
																											this->m_Glow[i]->g_VisualPrp(2)		);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Glow[i]->g_RotationPrp(1)	);



				this->_Draw_->DrawBlend(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Crushing Particle.
		if (	What == enm_Draw::_CrushEffect	)
		{
			this->_What_Sprite_			= spr::enm_At::CrushingParticles;
			this->_Container_Size_		= this->m_Crushes.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				this->_What_Kind_		= this->m_Crushes[i]->g_ID(1) - 1;								//	KindID
				this->_What_Kind_		= (this->_What_Kind_ * 3) + (this->m_Crushes[i]->g_ID(2) - 1);	//	CrushParticleID
				


				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Crushes[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Crushes[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	255, 255, 255, this->m_Crushes[i]->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Crushes[i]->g_VisualPrp(1)		,
																											this->m_Crushes[i]->g_VisualPrp(2)		);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Crushes[i]->g_RotationPrp(1)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
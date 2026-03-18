#pragma once

#include		"thyObject.h"
#include		"_MyIncludes_.h"
#include		"LogicalController.h"



//	Animation of glow particle list:
//		1.	Basic moving.


enum	AnmGlow
{
	BasicMoving = 1		,
	StaticGlow			,
	StrippedSparkle		,
	LinearMovement		
};
enum	GlowID
{
	RadiantGlow = 0		,
	SquareGlow			,
	StrippedLightning	,
	StrippedInsLight	,
	FourStarLight		,
	FourStarInsLight	,
	DrawnStar			,
	FullStarShort		,
	SparkmokeShort		,
	SparkmokeMedium		,
	StarLightRemember	,
	MediumCircularGlow	,
	FrozenCandyBackGlow	,
	XLGlow				,
	SharpSpark			,
	MoreMediumGlow		,
};


class		GlowParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Important values
//	-------------------------------------------
private:
	int			m_GlowID		= def::enm_Defines::_NOT_INITIALIZED;
	int			m_AnimationID	= def::enm_Defines::_NOT_INITIALIZED;

	double		$_Gravity		= -0.0025;

//	-------------------------------------------
//					Other values
//	-------------------------------------------
private:
	int			m_Direction		= 0;
	int			m_KindID		= 0;

	bool		m_UseBlending	= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	GlowParticle() : thyObject()
	{

	}
	GlowParticle(double _xPos, double _yPos, int _GlowID, int _AnimationID) : thyObject(_xPos, _yPos, def::enm_ObjectType::GlowParticle)
	{
		this->m_GlowID			= _GlowID;
		this->m_AnimationID		= _AnimationID;	

		tls::SetRGB(STA_::enm_KindID::_White, this->R_col, this->G_col, this->B_col);
	}
	GlowParticle(double _xPos, double _yPos, int _GlowID, int _AnimationID, int _KindID) : thyObject(_xPos, _yPos, def::enm_ObjectType::GlowParticle)
	{
		this->m_GlowID			= _GlowID;
		this->m_AnimationID		= _AnimationID;
		this->m_KindID			= _KindID;



		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);
	}

	~GlowParticle()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateParticle()
	{
		switch (this->m_AnimationID)
		{
		case	AnmGlow::BasicMoving:
			//	Apply position changes.
			{
				this->xP	= this->xP + (this->xS * _Controller_Logic::_fdTime_);
				this->yP	= this->yP + (this->yS * _Controller_Logic::_fdTime_);
			}

			//	Case for xS...
			{
				//	Means that xS is negative, so xA (positive) needs to
				//	deacelerate this particle.
				if ((this->xS + this->xA) < 0.0)
				{
					this->xS	= this->xS + (this->xA * _Controller_Logic::_fdTime_);
				}
				else
				{
					//	Means that xS is positive, so xA (negative) needs to
					//	deacelerate this particle.
					if ((this->xS + this->xA) > 0.0)
					{
						this->xS	= this->xS + (this->xA * _Controller_Logic::_fdTime_);
					}
					else
					{
						//	End moving.
						this->xS	= this->xA = 0.0;
					}
				}
			}

			//	Case for yS...
			{
				//	this->yP = this->yP + (this->yS * _Controller_Logic::_fdTime_);
				this->yS = this->yS + (this->yA * _Controller_Logic::_fdTime_);
				this->yA = this->yA + (this->$_Gravity * 0.05 * _Controller_Logic::_fdTime_);
			}




			//	Shrinking part.
			{
				this->xFct		= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
				this->yFct		= this->yFct + (this->yFctS * _Controller_Logic::_fdTime_);



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
				this->A_alpha	= this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

				if (this->A_alpha <= 0.0)
				{
					this->A_alpha = 0.0;
				}
			}

			//	Rotating side.
			{
				this->rotationDegree	= this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
			}
		
			break;

		case AnmGlow::StaticGlow:
			//	Opacity.
			{
				this->A_alpha	= this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

				if (this->A_alpha <= 0.0)
				{
					this->A_alpha = 0.0;
				}
			}

			//	Shrinking part.
			{
				this->xFct		= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
				this->yFct		= this->yFct + (this->yFctS * _Controller_Logic::_fdTime_);



				if ((this->xFct <= 0.0))
				{
					this->xFct = 0.0;
				}

				if ((this->yFct <= 0.0))
				{
					this->yFct = 0.0;
				}
			}

			//	Rotating side.
			{
				this->rotationDegree	= this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
			}

			break;

		case AnmGlow::StrippedSparkle:
			//	Apply position changes.
			{
				this->xP	= this->xP + (this->xS * _Controller_Logic::_fdTime_);
				this->yP	= this->yP + (this->yS * _Controller_Logic::_fdTime_);
			}

			//	For Speed and Aceleration.
			{
				double			_Itv_Speed_ = (600.0 / _Controller_Logic::_fdTime_);



				this->xS = this->xS - (this->xS / _Itv_Speed_);
				this->yS = this->yS - (this->yS / _Itv_Speed_);
			}

			//	Opacity.
			{
				this->A_alpha		= this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

				if (this->A_alpha <= 0.0)
				{
					this->A_alpha = 0.0;
				}
			}

			//	Rotating side.
			{
				double			_Itv_Rotation_ = (2000.0 / _Controller_Logic::_fdTime_);



				this->rotationDegree	= this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
				this->rotationSpeed		= this->rotationSpeed - (this->rotationSpeed / _Itv_Rotation_);
			}

			//	Shrinking part.
			{
				this->xFct		= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
				this->yFct		= this->yFct + (this->yFctS * _Controller_Logic::_fdTime_);



				if ((this->xFct <= 0.0))
				{
					this->xFct = 0.0;
				}

				if ((this->yFct <= 0.0))
				{
					this->yFct = 0.0;
				}
			}

			break;

		case AnmGlow::LinearMovement:
			//	Cases for position.
			{
				this->xP	= this->xP + (this->xS * _Controller_Logic::_fdTime_);
				this->yP	= this->yP + (this->yS * _Controller_Logic::_fdTime_);
										
				this->xS	= this->xS + (this->xA * _Controller_Logic::_fdTime_);
				this->yS	= this->yS + (this->yA * _Controller_Logic::_fdTime_);
			}

			//	Opacity.
			{
				this->A_alpha	= this->A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_);

				if (this->A_alpha <= 0.0)
				{
					this->A_alpha = 0.0;
				}
			}

			//	Rotating side.
			{
				this->rotationDegree	= this->rotationDegree + (this->rotationSpeed * _Controller_Logic::_fdTime_);
				this->rotationSpeed		= this->rotationSpeed + (this->rotationAceleration * _Controller_Logic::_fdTime_);
			}

			//	Shrinking part.
			{
				this->xFct		= this->xFct + (this->xFctS * _Controller_Logic::_fdTime_);
				this->yFct		= this->yFct + (this->yFctS * _Controller_Logic::_fdTime_);



				if ((this->xFct <= 0.0))
				{
					this->xFct = 0.0;
				}

				if ((this->yFct <= 0.0))
				{
					this->yFct = 0.0;
				}
			}

			break;
		}
	}

//	-------------------------------------------
//			Setters and Getters !
//	-------------------------------------------
public:
	inline void		s_GlowID(int _Val)
	{
		this->m_GlowID = _Val;
	}
	inline void		s_AnimationID(int _Val)
	{
		this->m_AnimationID = _Val;
	}
	inline void		s_ID(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_KindID = _Val;
			break;

		case 2:
			this->m_Direction = _Val;
			break;
		}
	}
	inline void		s_Blending(bool _Val)
	{
		this->m_UseBlending = _Val;
	}

	inline int		g_GlowID()
	{
		return this->m_GlowID;
	}
	inline int		g_AnimationID()
	{
		return this->m_AnimationID;
	}
	inline int		g_ID(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_KindID;

		case 2:
			return this->m_Direction;
		}
	}
	inline bool		g_Blending()
	{
		return		this->m_UseBlending;
	}
	inline int		g_KindID()
	{
		return		this->m_KindID;
	}



	inline void		s_Pos_WithContainer(		tls::Vec4<double> _My_Container		)
	{
		this->xS	=	_My_Container.First;
		this->yS	=	_My_Container.Second;
		this->xA	=	_My_Container.Third;
		this->yA	=	_My_Container.Fourth;
	}
	inline void		s_Visual_WithContainer(		tls::Vec2<double> _My_Container		)
	{
		this->xFct = _My_Container.First;
		this->yFct = _My_Container.First;

		this->xFctS = _My_Container.Second;
		this->yFctS = _My_Container.Second;
	}
	inline void		s_Color_WithContainer(		tls::Vec4<double> _My_Container		)
	{
		this->R_col		=	_My_Container.First;
		this->G_col		=	_My_Container.Second;
		this->B_col		=	_My_Container.Third;
		this->A_alpha	=	_My_Container.Fourth;
	}
	inline void		s_Color_WithKind(			int _What)
	{
		tls::SetRGB(_What, this->R_col, this->G_col, this->B_col);
	}
	inline void		s_Opacity_WithContainer(	tls::Vec3<double> _My_Container		)
	{
		this->A_alpha	= _My_Container.First;
		this->Alpha_s	= _My_Container.Second;
		this->Alpha_a	= _My_Container.Third;
	}
	inline void		s_Rotation_WithContainer(	tls::Vec3<double> _My_Container		)
	{
		this->rotationDegree		=	_My_Container.First;
		this->rotationSpeed			=	_My_Container.Second;
		this->rotationAceleration	=	_My_Container.Third;
	}

	inline int		g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		(this->xP + (this->_W * 0.5) );

		case	2:
			return		(this->yP - (this->_H * 0.5));

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};
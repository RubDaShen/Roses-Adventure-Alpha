#pragma once
#pragma once

#include		"LetterBoxing.h"
#include		"FancyLogo.h"
#include		"LightBricks.h"
#include		"_MyIncludes_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"_Basics_KeyBoard.h"
#include		"BackGrounds.h"
#include		"thyEffect.h"


class		FlashBang
{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//					Enums
	//	-------------------------------------------
public:
	enum	enm_Draw
	{
		_FlashBang = 0,
	};





	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Private side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//				[1] Variables
	//	-------------------------------------------
private:
	std::pair<BackGround*, thyEffect*>		m_FlashBang;

	double		m_Time_FromUp = 0.2;
	double		m_Time_UpDown = 1.0;

	int			m_PhaseFlag = 0;

	//	-------------------------------------------
	//			[2] Outside and Linkers
	//	-------------------------------------------
private:
	DrawFactory*	_Draw_ = nullptr;
	SpriteFactory*	_Sprites_ = nullptr;

	int			_What_Sprite_ = 0;
	int			_What_Kind_ = 0;
	int			_Container_Size_ = 0;




	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//			Constructors and Destructor
	//	-------------------------------------------
public:
	FlashBang(DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr, ShaderFactory* _Shader_Ptr)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;

		this->Ld_All();
	}

	~FlashBang()
	{
		this->Del_All();
	}

	//	-------------------------------------------
	//					Functions
	//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		this->m_FlashBang = std::make_pair<BackGround*, thyEffect*>
			(
				new BackGround(		tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	,
									tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2))	,
									STA_::enm_BackGrounds::BlankScene),
				new thyEffect()
			);

		this->m_FlashBang.first->ScaleToFit(this->_Sprites_, this->_Draw_);
		this->m_FlashBang.first->s_ColorPrp(4, 0.0);
	}
	inline void			Del_All()
	{
		//	Pair: FlashBang.
		delete		this->m_FlashBang.first;
		delete		this->m_FlashBang.second;
	}

	inline void			SetAnimation(int WhatAnimation)
	{
		switch (WhatAnimation)
		{
		case		1:
			this->m_FlashBang.second->Ini_FadeInOut(0.0, 255.0, 0.0, this->m_Time_FromUp, this->m_Time_UpDown);
			break;

		case		2:
			this->m_FlashBang.second->Ini_FadeInOut(0.0, 255.0, 0.0, this->m_Time_FromUp, this->m_Time_UpDown);
			break;
		}

	}
	inline void			Animate()
	{
		this->m_FlashBang.second->FadeIO();
		this->m_FlashBang.first->s_ColorPrp(4, this->m_FlashBang.second->g_FIO(1));
	}

	inline void			LogicDis()
	{
		this->Animate();
	}

	//	-------------------------------------------
	//				Drawing Functions
	//	-------------------------------------------
public:
	inline void			Draw(int What)
	{
		//	FlashBang
		if (enm_Draw::_FlashBang == What)
		{
			this->_What_Sprite_ = spr::enm_At::BackGrounds;
			this->_What_Kind_ = 0;



			//	Drawing part.
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_FlashBang.first->g_PositionPrp(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(this->m_FlashBang.first->g_PositionPrp(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->m_FlashBang.first->g_ColorPrp(1)	,
																														this->m_FlashBang.first->g_ColorPrp(2)	,
																														this->m_FlashBang.first->g_ColorPrp(3)	,
																														this->m_FlashBang.first->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_FlashBang.first->g_VisualPrp(1)	,
																											this->m_FlashBang.first->g_VisualPrp(2)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}

	//	-------------------------------------------
	//				Setters and Getters
	//	-------------------------------------------
public:
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
class		OnScreen
{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//					Enums
	//	-------------------------------------------
public:
	enum	enm_Draw
	{
		_SlowMotion_FlashBang = 0,
	};





	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Private side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//				[0] Controllers
	//	-------------------------------------------
private:
	_Controller_LetterBoxes*		m_Bars		= nullptr;
	_Controller_Logo*				m_Logos		= nullptr;
	_Controller_LightBricks*		m_Lights	= nullptr;

	//	-------------------------------------------
	//				[1] Variables
	//	-------------------------------------------
private:
	FlashBang*		m_SlowMotion_FlashBang	= nullptr;

	//	-------------------------------------------
	//			[2] Outside and Linkers
	//	-------------------------------------------
private:
	DrawFactory*		_Draw_			= nullptr;
	SpriteFactory*		_Sprites_		= nullptr;
	ShaderFactory*		_Shader_		= nullptr;
	_Basic_KeyBoard*	_KeyBoard_		= nullptr;

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
	OnScreen(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr		,
				ShaderFactory* _Shader_Ptr								)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Shader_		= _Shader_Ptr;
	}

	~OnScreen()
	{
		this->Del_Everything();
	}

	//	-------------------------------------------
	//					Functions
	//	-------------------------------------------
public:
	inline void			LogicDis()
	{
		this->m_Logos->Animate();
		this->m_SlowMotion_FlashBang->LogicDis();
	}

	//	-------------------------------------------
	//			Initializing Functions
	//	-------------------------------------------
public:
	inline void			SetLogoAnimation_FIO(int _What, int _Which_PreSet)
	{
		double		_From = 0.0, _To = 0.0, _Down = 0.0;
		double		_Time_From_To = 0.0, _Time_To_Down = 0.0;



		//	From the presets, select which one to use.
		{
			switch (_Which_PreSet)
			{
			case 0:
				_From = 0.0, _To = 255.0, _Down = 0.0;
				_Time_From_To = 0.75, _Time_To_Down = 0.5;

				break;
			}
		}

		//	Set the animation.
		this->m_Logos->s_Anm_FadeIO(_What, _From, _To, _Down, _Time_From_To, _Time_To_Down);
	}

	//	-------------------------------------------
	//				Loading Functions
	//	-------------------------------------------
public:
	inline void			Ld_Everything()
	{
		//	Creating the Bars.
		{
			this->m_Bars	= new _Controller_LetterBoxes(	this->_Draw_->g_WindowBounds(1), this->_Draw_->g_WindowBounds(2)	,
															this->_Draw_->g_WorldBounds(1), this->_Draw_->g_WorldBounds(2)		);
		}

		//	Creating the logo.
		{
			this->m_Logos	= new _Controller_Logo(this->_Draw_->g_WindowBounds(1), this->_Draw_->g_WindowBounds(2));
		}

		//	Creating the Smooth Layer.
		{
			this->m_Lights	= new _Controller_LightBricks(this->_Draw_, this->_Sprites_);
		}

		//	Slow Motion Flash Bang.
		{
			this->m_SlowMotion_FlashBang = new FlashBang(this->_Draw_, this->_Sprites_, this->_Shader_);
		}
	}
	inline void			Del_Everything()
	{
		delete		this->m_Bars;
		delete		this->m_Logos;
		delete		this->m_Lights;
		delete		this->m_SlowMotion_FlashBang;
	}

	//	-------------------------------------------
	//				Drawing Functions
	//	-------------------------------------------
public:
	inline void			Draw(int What)
	{
		//	FlashBang
		if (enm_Draw::_SlowMotion_FlashBang == What)
		{
			this->m_SlowMotion_FlashBang->Draw(What);
		}
	}

	//	-------------------------------------------
	//				Setters and Getters
	//	-------------------------------------------
public:
	inline _Controller_LetterBoxes*		g_Ctrl_Bars()
	{
		return		this->m_Bars;
	}
	inline _Controller_Logo*			g_Ctrl_Logos()
	{
		return		this->m_Logos;
	}
	inline _Controller_LightBricks*		g_Ctrl_LightBricks()
	{
		return		this->m_Lights;
	}

	inline FlashBang*					GetSlowMotion_FlashBang()
	{
		return		this->m_SlowMotion_FlashBang;
	}
};
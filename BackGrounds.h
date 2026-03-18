#pragma once

#include		<vector>

#include		"thyObject.h"
#include		"_MyIncludes_.h"
#include		"Tools_.h"
#include		"SpriteFactory.h"
#include		"DrawFactory.h"



class		BackGround : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	int				m_What_Kind		= 0;
	int				m_What_Sprite	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	BackGround(		double _xP, double _yP, int _What_Kind		, 
					int _What_Sprite = spr::BackGrounds			) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_What_Kind		= _What_Kind;
		this->m_What_Sprite		= _What_Sprite;
	}

	~BackGround()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			ScaleToFit(	SpriteFactory* _Sprite_, DrawFactory* _Draw_	)
	{
		//	Out of vector.
		{
			if (	_Sprite_->g_Sprite(this->m_What_Sprite)->g_Measures()->size() <= this->m_What_Kind)
			{
				//	Default size: 2048x2048
				int		_DefaultSize_ = 2048;


				
				//	Width.
				if (_DefaultSize_ < _Draw_->g_WindowBounds(1))
				{
					this->xFct = tls::Scale(_DefaultSize_, _Draw_->g_WindowBounds(1));
				}

				//	Height.
				if (_DefaultSize_ < _Draw_->g_WindowBounds(2))
				{
					this->yFct = tls::Scale(_DefaultSize_, _Draw_->g_WindowBounds(2));
				}

				return;
			}
		}

		//	About xFct
		{
			this->xFct = 1.0;

			if (	_Sprite_->g_Sprite(this->m_What_Sprite)->g_Measures()->at(this->m_What_Kind).Third < _Draw_->g_WindowBounds(1)	)
			{
				this->xFct = tls::Scale(_Sprite_->g_Sprite(this->m_What_Sprite)->g_Measures()->at(this->m_What_Kind).Third, _Draw_->g_WindowBounds(1));
			}
		}

		//	About yFct
		{
			this->yFct = 1.0;

			if (	_Sprite_->g_Sprite(this->m_What_Sprite)->g_Measures()->at(this->m_What_Kind).Fourth < _Draw_->g_WindowBounds(2))
			{
				this->yFct = tls::Scale(_Sprite_->g_Sprite(this->m_What_Sprite)->g_Measures()->at(this->m_What_Kind).Fourth, _Draw_->g_WindowBounds(2));
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_BackGroundID(int _Val)
	{
		this->m_What_Kind		= _Val;
	}
	inline void			s_Color_WithContainer(tls::Vec4<double> _Colors)
	{
		this->R_col		= _Colors.First;
		this->G_col		= _Colors.Second;
		this->B_col		= _Colors.Third;
		this->A_alpha	= _Colors.Fourth;
	}

	inline int			g_BackGroundID()
	{
		return			this->m_What_Kind;
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
class	_Controller_BackGround
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	std::vector<BackGround*>			m_BGs;

//	-------------------------------------------
//			[2] External and linkers
//	-------------------------------------------
private:
	SpriteFactory*			_Sprite_	= nullptr;
	DrawFactory*			_Draw_		= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_BackGround(		double _Win_W, double _Win_H, double _xGround, double _yGround	,
								SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr				)
	{
		this->_Sprite_		= _Sprite_Ptr;
		this->_Draw_		= _Draw_Ptr;


		this->Ld_BGs();
	}

	~_Controller_BackGround()
	{
		//	Deleting BGs !
		{
			while (!this->m_BGs.empty())
			{
				delete		this->m_BGs[0];
				this->m_BGs.erase(this->m_BGs.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//				Loading	Functions
//	-------------------------------------------
public:
	inline void			Ld_BGs()
	{
		//	A blank scene.		0
		{
			this->m_BGs.push_back(	new BackGround(		tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	,
														tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2))	,
														STA_::enm_BackGrounds::BlankScene						)	);

			this->m_BGs[this->m_BGs.size() - 1]->ScaleToFit(	this->_Sprite_, this->_Draw_	);
		}

		//	The main bg.		1
		{
			this->m_BGs.push_back(	new BackGround(	tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	,
													tls::TransformPos_Y((this->_Draw_->g_WindowBounds(2) / 2.0) - 50.0, this->_Draw_->g_WorldBounds(2))	,
													STA_::enm_BackGrounds::ConfrontTheReality													)	);

			this->m_BGs[this->m_BGs.size() - 1]->ScaleToFit(this->_Sprite_, this->_Draw_);
		}

		//	Lobby part.			2
		{
			//	Choose what background you want.
			int		_What_ = STA_::enm_BackGrounds::ChooseYourAdventure;



			this->m_BGs.push_back(	new BackGround(		tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	,
														tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2))	,
														_What_		)	);

			this->m_BGs[this->m_BGs.size() - 1]->ScaleToFit(	this->_Sprite_, this->_Draw_	);
		}

		//	Level.				3
		{
			//	Choose what background you want.
			int		_What_ = STA_::enm_BackGrounds::NightCity;



			this->m_BGs.push_back(	new BackGround(		tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	,
														tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2))	,
														_What_		)	);

			this->m_BGs[this->m_BGs.size() - 1]->ScaleToFit(	this->_Sprite_, this->_Draw_	);
		}
	}

//	-------------------------------------------
//				Drawing	Functions
//	-------------------------------------------
public:
	inline void			DrawBackGround(		int _What_Room		)
	{
		int			_What_BackGround = 0;
		switch (	_What_Room	)
		{
		case	STA_::enm_Rooms::MainMenu:
			_What_BackGround = 1;
			break;

		case	STA_::enm_Rooms::Lobby:
			_What_BackGround = 2;
			break;

		case	STA_::enm_Rooms::Map:
			_What_BackGround = 3;
			break;
		}



		//	Drawing the background.
		{
			int						_SpriteID_BackGrounds	= spr::enm_At::BackGrounds;
			int						_WhatSprite_			= this->m_BGs[_What_BackGround]->g_BackGroundID();



			//	Actual Drawing.
			{
				//	Set position to the sprite.
				this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_BGs[_What_BackGround]->g_PositionPrp(1)	,
																												this->m_BGs[_What_BackGround]->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_BGs[_What_BackGround]->g_VisualPrp(1)	,
																											this->m_BGs[_What_BackGround]->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(	this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



				this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_));
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline BackGround*			g_Vec_At_BGs(int _What)
	{
		return		this->m_BGs[_What];
	}
};
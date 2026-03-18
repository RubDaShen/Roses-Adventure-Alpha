#pragma once

#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"BackGrounds.h"



class		_Controller_Arcade
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum	enm_Draw
	{
		_Background		= 1
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:

//	-------------------------------------------
//				Included Variables
//	-------------------------------------------
private:
	BackGround*			m_BackGround	= nullptr;

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
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Arcade(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;



		this->LoadAll();
	}

	~_Controller_Arcade()
	{
		this->DeleteAll();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			LoadAll()
	{
		//	Loading the background.
		{
			//	Choose what background you want.
			double		xFct = 0.0, yFct = 0.0;
			int			_What_ = STA_::enm_BackGrounds::BlankScene;


			this->m_BackGround = new BackGround(		tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1))	, 
														tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2))	,
														_What_													);

			this->m_BackGround->ScaleToFit(this->_Sprites_, this->_Draw_);
			this->m_BackGround->s_Color_WithContainer(tls::Vec4<double>(74.0, 74.0, 74.0, 255.0));
		}
	}
	inline void			DeleteAll()
	{
		tls::Delete(	this->m_BackGround		);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Drawing the main background.
		{
			_What_Sprite_		= spr::enm_At::BackGrounds;
			_What_Kind_			= this->m_BackGround->g_BackGroundID();



			//	Actual Drawing.
			{
				//	Set position to the sprite.
				this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_)->setPosition(	this->m_BackGround->g_PositionPrp(1)	,
																										this->m_BackGround->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_)->setScale(	this->m_BackGround->g_VisualPrp(1)	,
																									this->m_BackGround->g_VisualPrp(2)	);				

				//	Here all your color, scale, and more !
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_BackGround->g_ColorPrp(1)	,
																														this->m_BackGround->g_ColorPrp(2)	,
																														this->m_BackGround->g_ColorPrp(3)	,
																														this->m_BackGround->g_ColorPrp(4)	)	);

				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_)->setPosition(	tls::FixPos_X(	this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)	)	,
																										tls::FixPos_Y(	this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2)	)	);



				this->_Draw_->Draw(this->_Sprites_->g_Sprite(_What_Sprite_)->g_Sprites()->at(_What_Kind_), false);
			}			
		}
	}
	inline void			DrawArcade()
	{
		this->Draw(		_Controller_Arcade::enm_Draw::_Background	);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:

};
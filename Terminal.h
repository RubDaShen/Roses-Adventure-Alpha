#pragma once

#include		"Tools_.h"
#include		"BackGrounds.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"



class		Terminal : public thyObject
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
		_BackGround		= 0,
		_Text			= 1
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	BackGround*			m_BackGround	= nullptr;
	tls::String*		m_Data			= nullptr;

	double				m_LetterSpacing		= -20;
	double				m_EndLineSpacing	= -10;
	double				m_Font_W			= 0, m_Font_H = 0;

//	-------------------------------------------
//			[2] Outside and Linkers
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
	Terminal(	double _xP, double _yP, double _Font_W, double _Font_H	,
				DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr		) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;

		this->m_Font_W		= _Font_W;
		this->m_Font_H		= _Font_H;



		this->Ld_All();
	}

	~Terminal()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		//	Data.
		{
			this->m_Data	= new tls::String();
			this->m_Data->SetLetterSpacing(-20);
		}

		//	BackGround.
		{
			this->m_BackGround		= new BackGround(	tls::TransformPos_X(0.0, this->_Draw_->g_WorldBounds(1)	)	,
														tls::TransformPos_Y(0.0, this->_Draw_->g_WorldBounds(2)	)	,
														0, spr::inLoading_BackGrounds								);

			this->m_BackGround->ScaleToFit(					this->_Sprites_, this->_Draw_			);
			this->m_BackGround->s_Color_WithContainer(	tls::Vec4<double>(0.0, 0.0, 0.0, 255.0)		);
		}
	}
	inline void			Del_All()
	{
		tls::Delete(this->m_BackGround);
		tls::Delete(this->m_Data);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				Write(const std::string& _MoreText, double _FontSize = 7)
	{
		//	Some properties.
		this->m_Data->s_PositionPrp(1, this->xP);
		this->m_Data->s_PositionPrp(2, this->yP);

		//	The text is all done.
		this->m_Data->Write(_MoreText, _FontSize);

		//	Then, fixing every character position for printing on the screen.
		this->m_Data->RePos();
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	BackGround.
		if (	enm_Draw::_BackGround == What	)
		{
			this->_What_Sprite_		= spr::inLoading_BackGrounds;
			this->_What_Kind_		= 0;



			//	Actual Drawing.
			{
				//	Fix position to properly render on screen.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_BackGround->g_PositionPrp(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_BackGround->g_PositionPrp(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Color the background.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_BackGround->g_ColorPrp(1)	, 
																													this->m_BackGround->g_ColorPrp(2)	, 
																													this->m_BackGround->g_ColorPrp(3)	, 
																													this->m_BackGround->g_ColorPrp(4)	)	);

				//	Scale to fit.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(	this->m_BackGround->g_VisualPrp(1)	, 
																										this->m_BackGround->g_VisualPrp(2)	);

				

				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Text.
		if (	enm_Draw::_Text == What		)
		{
			this->_Container_Size_		= this->m_Data->size();
			this->_What_Sprite_			= spr::enm_At::inLoading_ImageFont;
			
			

			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				this->_What_Kind_	= this->m_Data->at(i)->g_CharID();
				
				
				
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->m_Data->at(i)->g_PositionPrp(1) + ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Third / 2.0) * this->m_Data->at(i)->g_VisualPrp(1)	),
																											this->m_Data->at(i)->g_PositionPrp(2) - ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Fourth / 2.0) * this->m_Data->at(i)->g_VisualPrp(2)	)	);
				
				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Data->at(i)->g_VisualPrp(1)		,
																											this->m_Data->at(i)->g_VisualPrp(2)		);
				
				//	Fix position to properly render on screen.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																											tls::FixPos_Y(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
				
				
				
				//	Draw it.
				this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)		);
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline tls::String*		g_String()
	{
		return this->m_Data;
	}
};
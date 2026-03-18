#pragma once

#include		"thyObject.h"
#include		"Tools_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"_MyIncludes_.h"
#include		"Layouts.h"



class		LifeIcon : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int		m_Lifes		= 1;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LifeIcon(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~LifeIcon()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

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
	inline int			g_Lifes()
	{
		return		this->m_Lifes;
	}

	inline int*			gRef_Life()
	{
		return		&this->m_Lifes;
	}
};
class		CoinIcon : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int		m_Amount		= 0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	CoinIcon(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~CoinIcon()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

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
	inline int			g_TotalAmount()
	{
		return		this->m_Amount;
	}

	
	inline int*			gRef_Coins()
	{
		return		&this->m_Amount;
	}
};
class		LiviconPanel : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int		m_LefightWidth		= 18;
	int		m_TopttomHeight		= 18;



//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LiviconPanel(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~LiviconPanel()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:

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
	inline int			g_BorderMeasures(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		this->m_LefightWidth;

		case	2:
			return		this->m_TopttomHeight;

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
class		_Controller_LiviconHUD
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
		_Life		= 0,
		_Coin		= 1,
		_Panel		= 2,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	LifeIcon*		m_LifeIcon			= nullptr;
	Rectbord*		m_Life_Rectbord		= nullptr;
	tls::String*	m_Life_Text			= nullptr;

	CoinIcon*		m_CoinIcon			= nullptr;
	Rectbord*		m_Coin_Rectbord		= nullptr;
	tls::String*	m_Coin_Text			= nullptr;

	LiviconPanel*	m_Panel				= nullptr;

	int		m_GapSpacing	= 10;
	int		m_PanelGap		= 25;

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
	_Controller_LiviconHUD(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;


		
		this->LoadAll();
	}

	~_Controller_LiviconHUD()
	{
		this->DeleteAll();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			LoadAll()
	{
		//	Panel.
		{
			this->m_Panel		= new LiviconPanel(		tls::TransformPos_X(0.0, this->_Draw_->g_WorldBounds(1)					)	, 
														tls::TransformPos_Y(this->m_PanelGap, this->_Draw_->g_WorldBounds(2)	)	);

			this->m_Panel->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(2).Third);
			this->m_Panel->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(2).Fourth);
		}

		//	Life Icon.
		{
			this->m_LifeIcon		= new LifeIcon(0.0, 0.0);
			this->m_LifeIcon->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(0).Third);
			this->m_LifeIcon->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(0).Fourth);

			this->m_Life_Rectbord	= new Rectbord(0.0, 0.0, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Fourth / 2.0);
			this->m_Life_Rectbord->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Third);
			this->m_Life_Rectbord->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Fourth);

			this->m_Life_Text		= new tls::String();
			this->m_Life_Text->SetLetterSpacing(-15);
			this->m_Life_Text->Write(tls::IntToStr(this->m_LifeIcon->g_Lifes()), 8);



			//	LifeIcon->x
			double PanelWidth		= this->m_Panel->g_SpriteMeasures(1) - this->m_Panel->g_BorderMeasures(1);
			double LifeAndRecWidth	= (this->m_LifeIcon->g_SpriteMeasures(1) / 2.0) + this->m_Life_Rectbord->g_SpriteMeasures(1) - this->m_Life_Rectbord->g_BorderRadious();
			double xPosition		= this->m_Panel->g_PositionPrp(1) + ((PanelWidth - LifeAndRecWidth) / 2.0);
			this->m_LifeIcon->s_PositionPrp(1, xPosition);

			//	LifeIcon->y
			double PanelBorder		= this->m_Panel->g_BorderMeasures(2) + this->m_Panel->g_BorderMeasures(2);
			double PanelHeight		= this->m_Panel->g_SpriteMeasures(2) - PanelBorder;
			double HalfPanelHeight	= PanelHeight / 2.0;
			double LifeIconHeight	= this->m_LifeIcon->g_SpriteMeasures(2);
			double yPosition		= this->m_Panel->g_PositionPrp(2) - PanelBorder + (this->m_PanelGap / 2.0) - ((HalfPanelHeight - LifeIconHeight) / 2.0);
			this->m_LifeIcon->s_PositionPrp(2, yPosition);

			//	Life_Rectbord->x
			this->m_Life_Rectbord->s_PositionPrp(1, this->m_LifeIcon->g_PositionPrp(1) + (this->m_LifeIcon->g_SpriteMeasures(1) / 2.0) - this->m_Life_Rectbord->g_BorderRadious());

			//	Life_Rectbord->y
			this->m_Life_Rectbord->s_PositionPrp(2, (this->m_LifeIcon->g_PositionPrp(2) - ((this->m_LifeIcon->g_SpriteMeasures(2) - this->m_Life_Rectbord->g_SpriteMeasures(2)) / 2.0)));
		
			//	Life_Text->x
			double xInitialPos		= this->m_LifeIcon->g_PositionPrp(1) + this->m_LifeIcon->g_SpriteMeasures(1);
			double TextWidth		= this->m_Life_Text->GetStringMeasure(1);
			double VisibleWidth		= (this->m_Life_Rectbord->g_PositionPrp(1) + this->m_Life_Rectbord->g_SpriteMeasures(1) - this->m_Life_Rectbord->g_OutlineThickness()) - xInitialPos;
			double xFinalPos		= xInitialPos + ((VisibleWidth - TextWidth) / 2.0);
			this->m_Life_Text->s_PositionPrp(1, xFinalPos);

			//	Life_Text->y
			double yInitialPos		= this->m_Life_Rectbord->g_PositionPrp(2);
			double TextHeight		= this->m_Life_Text->GetStringMeasure(2);
			double VisibleHeight	= this->m_Life_Rectbord->g_SpriteMeasures(2);
			double yFinalPos		= yInitialPos - ((VisibleHeight - TextHeight) / 2.0);
			this->m_Life_Text->s_PositionPrp(2, yFinalPos);

			this->m_Life_Text->RePos();
		}

		//	Coin Icon.
		{
			this->m_CoinIcon		= new CoinIcon(0.0, 0.0);
			this->m_CoinIcon->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(0).Third);
			this->m_CoinIcon->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::LiviconHUD)->g_Measures()->at(0).Fourth);

			this->m_Coin_Rectbord	= new Rectbord(0.0, 0.0, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Fourth / 2.0);
			this->m_Coin_Rectbord->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Third);
			this->m_Coin_Rectbord->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::Layouts)->g_Measures()->at(0).Fourth);

			this->m_Coin_Text		= new tls::String();
			this->m_Coin_Text->SetLetterSpacing(-15);
			this->m_Coin_Text->Write(tls::IntToStr(this->m_CoinIcon->g_TotalAmount()), 8);



			//	CoinIcon->x
			double PanelWidth		= this->m_Panel->g_SpriteMeasures(1) - this->m_Panel->g_BorderMeasures(1);
			double CoinAndRecWidth	= (this->m_CoinIcon->g_SpriteMeasures(1) / 2.0) + this->m_Coin_Rectbord->g_SpriteMeasures(1) - this->m_Coin_Rectbord->g_BorderRadious();
			double xPosition		= this->m_Panel->g_PositionPrp(1) + ((PanelWidth - CoinAndRecWidth) / 2.0);
			this->m_CoinIcon->s_PositionPrp(1, xPosition);

			//	CoinIcon->y
			double PanelHeight		= this->m_Panel->g_SpriteMeasures(2) - this->m_Panel->g_BorderMeasures(2) - this->m_Panel->g_BorderMeasures(2);
			double HalfPanelHeight	= PanelHeight/ 2.0;
			double CoinIconHeight	= this->m_CoinIcon->g_SpriteMeasures(2);
			double yPosition		= this->m_Panel->g_PositionPrp(2) - HalfPanelHeight - (this->m_PanelGap / 2.0) - ((HalfPanelHeight - CoinIconHeight) / 2.0);
			this->m_CoinIcon->s_PositionPrp(2, yPosition);

			//	Coin_Rectbord->x
			this->m_Coin_Rectbord->s_PositionPrp(1, this->m_CoinIcon->g_PositionPrp(1) + (this->m_CoinIcon->g_SpriteMeasures(1) / 2.0) - this->m_Coin_Rectbord->g_BorderRadious());

			//	Coin_Rectbord->y
			this->m_Coin_Rectbord->s_PositionPrp(2, (this->m_CoinIcon->g_PositionPrp(2) - ((this->m_CoinIcon->g_SpriteMeasures(2) - this->m_Coin_Rectbord->g_SpriteMeasures(2)) / 2.0)));
		
			//	Coin_Text->x
			double xInitialPos		= this->m_CoinIcon->g_PositionPrp(1) + this->m_CoinIcon->g_SpriteMeasures(1);
			double TextWidth		= this->m_Coin_Text->GetStringMeasure(1);
			double VisibleWidth		= (this->m_Coin_Rectbord->g_PositionPrp(1) + this->m_Coin_Rectbord->g_SpriteMeasures(1) - this->m_Coin_Rectbord->g_OutlineThickness()) - xInitialPos;
			double xFinalPos		= xInitialPos + ((VisibleWidth - TextWidth) / 2.0);
			this->m_Coin_Text->s_PositionPrp(1, xFinalPos);

			//	Coin_Text->y
			double yInitialPos		= this->m_Coin_Rectbord->g_PositionPrp(2);
			double TextHeight		= this->m_Coin_Text->GetStringMeasure(2);
			double VisibleHeight	= this->m_Coin_Rectbord->g_SpriteMeasures(2);
			double yFinalPos		= yInitialPos - ((VisibleHeight - TextHeight) / 2.0);
			this->m_Coin_Text->s_PositionPrp(2, yFinalPos);

			this->m_Coin_Text->RePos();
		}
	}
	inline void			DeleteAll()
	{
		tls::Delete(this->m_LifeIcon);
		tls::Delete(this->m_Life_Rectbord);
		tls::Delete(this->m_Life_Text);

		tls::Delete(this->m_CoinIcon);
		tls::Delete(this->m_Coin_Rectbord);
		tls::Delete(this->m_Coin_Text);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			LogicDis()
	{
		//	Life text.
		{
			this->m_Life_Text->Write(tls::IntToStr(this->m_LifeIcon->g_Lifes()), 8, false, true);

			//	Life_Text->x
			double xInitialPos		= this->m_LifeIcon->g_PositionPrp(1) + this->m_LifeIcon->g_SpriteMeasures(1);
			double TextWidth		= this->m_Life_Text->GetStringMeasure(1);
			double VisibleWidth		= (this->m_Life_Rectbord->g_PositionPrp(1) + this->m_Life_Rectbord->g_SpriteMeasures(1) - this->m_Life_Rectbord->g_OutlineThickness()) - xInitialPos;
			double xFinalPos		= xInitialPos + ((VisibleWidth - TextWidth) / 2.0);
			this->m_Life_Text->s_PositionPrp(1, xFinalPos);

			this->m_Life_Text->RePos();
		}
		
		//	Coin text.
		{
			this->m_Coin_Text->Write(tls::IntToStr(this->m_CoinIcon->g_TotalAmount()), 8, false, true);

			//	Coin_Text->x
			double xInitialPos		= this->m_CoinIcon->g_PositionPrp(1) + this->m_CoinIcon->g_SpriteMeasures(1);
			double TextWidth		= this->m_Coin_Text->GetStringMeasure(1);
			double VisibleWidth		= (this->m_Coin_Rectbord->g_PositionPrp(1) + this->m_Coin_Rectbord->g_SpriteMeasures(1) - this->m_Coin_Rectbord->g_OutlineThickness()) - xInitialPos;
			double xFinalPos		= xInitialPos + ((VisibleWidth - TextWidth) / 2.0);
			this->m_Coin_Text->s_PositionPrp(1, xFinalPos);

			this->m_Coin_Text->RePos();
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		if (	enm_Draw::_Panel == What		)
		{
			this->_What_Sprite_		= spr::enm_At::LiviconHUD;
			this->_What_Kind_		= 2;



			
			//	Fix position to properly render on screen.
			this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Panel->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(	this->m_Panel->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

			


			this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
		}

		if (	enm_Draw::_Life == What		)
		{
			//	Life Rectbord.
			{
				this->_What_Sprite_		= spr::enm_At::Layouts;
				this->_What_Kind_		= 0;



				
				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Life_Rectbord->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	),
																													tls::FixPos_Y(	this->m_Life_Rectbord->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				


				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}

			//	Life string.
			{
				this->_Container_Size_		= this->m_Life_Text->size();
				this->_What_Sprite_			= spr::enm_At::OldCartoonFont;
				
				

				for (	int i = 0; 
						i < this->_Container_Size_;
						++i	)
				{
					this->_What_Kind_	= this->m_Life_Text->at(i)->g_CharID();
					
					
					
					//	Set position to the sprite.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->m_Life_Text->at(i)->g_PositionPrp(1) + ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Third / 2.0) * this->m_Life_Text->at(i)->g_VisualPrp(1)	),
																												this->m_Life_Text->at(i)->g_PositionPrp(2) - ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Fourth / 2.0) * this->m_Life_Text->at(i)->g_VisualPrp(2)	)	);
					
					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Life_Text->at(i)->g_VisualPrp(1)		,
																												this->m_Life_Text->at(i)->g_VisualPrp(2)		);
					
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
					
					
					
					//	Draw it.
					this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false		);
				}
			}

			//	Life Icon.
			{
				this->_What_Sprite_		= spr::enm_At::LiviconHUD;
				this->_What_Kind_		= 0;



				
				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_LifeIcon->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	),
																													tls::FixPos_Y(	this->m_LifeIcon->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				


				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}
		}

		if (	enm_Draw::_Coin == What		)
		{
			//	Coin Rectbord.
			{
				this->_What_Sprite_		= spr::enm_At::Layouts;
				this->_What_Kind_		= 0;



				
				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Coin_Rectbord->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	),
																													tls::FixPos_Y(	this->m_Coin_Rectbord->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				


				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}

			//	Coin string.
			{
				this->_Container_Size_		= this->m_Coin_Text->size();
				this->_What_Sprite_			= spr::enm_At::OldCartoonFont;
				
				

				for (	int i = 0; 
						i < this->_Container_Size_;
						++i	)
				{
					this->_What_Kind_	= this->m_Coin_Text->at(i)->g_CharID();
					
					
					
					//	Set position to the sprite.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->m_Coin_Text->at(i)->g_PositionPrp(1) + ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Third / 2.0) * this->m_Coin_Text->at(i)->g_VisualPrp(1)	),
																												this->m_Coin_Text->at(i)->g_PositionPrp(2) - ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Fourth / 2.0) * this->m_Coin_Text->at(i)->g_VisualPrp(2)	)	);
					
					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Coin_Text->at(i)->g_VisualPrp(1)		,
																												this->m_Coin_Text->at(i)->g_VisualPrp(2)		);
					
					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
					
					
					
					//	Draw it.
					this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false		);
				}
			}

			//	Coin Icon.
			{
				this->_What_Sprite_		= spr::enm_At::LiviconHUD;
				this->_What_Kind_		= 1;



				
				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_CoinIcon->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	),
																													tls::FixPos_Y(	this->m_CoinIcon->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				


				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline LifeIcon*		g_LifeIcon()
	{
		return		this->m_LifeIcon;
	}
	inline CoinIcon*		g_CoinIcon()
	{
		return		this->m_CoinIcon;
	}
};
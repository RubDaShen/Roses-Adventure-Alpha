#pragma once

#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<vector>

#include	"thyObject.h"
#include	"_MyIncludes_.h"
#include	"Tools_.h"
#include	"SpriteFactory.h"
#include	"DrawFactory.h"
#include	"BackGrounds.h"
#include	"_Basics_Button.h"
#include	"_Basics_Mouse.h"
#include	"World.h"




//	---------------------------------
//	m_State:
//				0	Not initialized
//				1	Normal
//				2	MouseOver
//				3	Clicked (Pressed)
//	---------------------------------
class		MapChart : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_MapID = 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	MapChart(	double _xP, double _yP, int _MapID	) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_MapID		= _MapID;
	}

	~MapChart()
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
	inline int			g_MapID()
	{
		return			this->m_MapID;
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
class	_Controller_Map
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double			_Win_W = 0.0,	_Win_H = 0.0;
	double			xGround = 0.0,	yGround = 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			_xLast_Camera_	= 0.0, _yLast_Camera_ = 0.0;
	double			m_ButtonPush	= -15.0;

	double			m_LeftBorder	= 0.0, m_RightBorder = 0.0;
	double			m_TopBorder		= 0.0, m_BottomBorder = 0.0;

//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	PushableButton*		_What_Button_ = nullptr;

	double		_x_ = 0.0, _y_ = 0.0;

	int			_Buttons_Size		= 0.0;

	bool		_Button_Collision		= false;
	bool		_A_Button_Was_Pressed	= false;

//	-------------------------------------------
//					Containters
//	-------------------------------------------
private:
	std::vector<MapChart*>				m_Maps;
	std::vector<PushableButton*>		m_PushButtons;

//	-------------------------------------------
//				Included Variables
//	-------------------------------------------
private:
	BackGround*			m_BackGround	= nullptr;
	Camera*				m_CameraMap		= nullptr;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	TextFactory*			_Text_		= nullptr;

	_Controller_World*		_World_		= nullptr;
	_Controller_Button*		_Buttons_	= nullptr;
	_Basic_Mouse*			_Mouse_		= nullptr;

	int			_What_Sprites_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Map(	_Basic_Mouse* _Mouse_Ptr								,
						SpriteFactory* _Sprites_Ptr, DrawFactory* _Draw_Ptr		,
						_Controller_Button* _Buttons_Ptr						,
						_Controller_World* _World_Ptr, TextFactory* _Text_Ptr	)
	{
		this->_World_	= _World_Ptr;
		this->_Buttons_ = _Buttons_Ptr;

		this->_Mouse_	= _Mouse_Ptr;
		this->_Draw_	= _Draw_Ptr;
		this->_Sprites_	= _Sprites_Ptr;
		this->_Text_	= _Text_Ptr;

		

		this->_Win_W	= this->_Draw_->g_WindowBounds(1);
		this->_Win_H	= this->_Draw_->g_WindowBounds(2);
		this->xGround	= this->_Draw_->g_WorldBounds(1);
		this->yGround	= this->_Draw_->g_WorldBounds(2);



		this->Ld_All();
	}

	~_Controller_Map()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading	Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		//	Creating the own camera of this map.
		{
			this->m_CameraMap = new Camera(		this->xGround, this->yGround, this->_Draw_->g_WindowBounds(1), this->_Draw_->g_WindowBounds(2));

			this->_Draw_->LinkCamera(this->m_CameraMap, 1);
			this->_Draw_->UseCamera(1);
		}

		//	Loading the background.
		{
			//	Choose what background you want.
			double		xFct = 0.0, yFct = 0.0;
			int			_What_ = STA_::enm_BackGrounds::BlankScene;



			this->m_BackGround = new BackGround(		tls::TransformPos_X(this->_Win_W / 2.0, this->_Draw_->g_WindowBounds(1))	, 
														tls::TransformPos_Y(this->_Win_H / 2.0, this->_Draw_->g_WindowBounds(2))	,
														_What_																		);
			this->m_BackGround->ScaleToFit(this->_Sprites_, this->_Draw_);
		}

		//	Maps !
		{
			double		MapBound = 2048.0;

			this->m_Maps.push_back(		new MapChart(	tls::TransformPos_X(this->_Draw_->g_WindowBounds(1) / 2.0, this->_Draw_->g_WorldBounds(1)) - (MapBound / 2.0),
														tls::TransformPos_Y(this->_Draw_->g_WindowBounds(2) / 2.0, this->_Draw_->g_WorldBounds(2)) + (MapBound / 2.0), 0)	);

			this->m_Maps[0]->s_MeasuresPrp(1, 2048.0);
			this->m_Maps[0]->s_MeasuresPrp(2, 2048.0);

			//	Now that all maps chunks are created, it's time to 
			//	fing the borders or limits of the whole creation.
			//	Map position starts from the upper-left corner.
			this->m_LeftBorder		= this->m_Maps[0]->g_PositionPrp(1);
			this->m_RightBorder		= this->m_Maps[0]->g_PositionPrp(1) + this->m_Maps[0]->g_MeasuresPrp(1);
			this->m_TopBorder		= this->m_Maps[0]->g_PositionPrp(2);
			this->m_BottomBorder	= this->m_Maps[0]->g_PositionPrp(2) - this->m_Maps[0]->g_MeasuresPrp(2);
			this->_Container_Size_	= this->m_Maps.size();

			for (	int i = 0; 
					i < this->_Container_Size_;
					++i	)
			{
				//	Left.
				if (this->m_Maps[i]->g_PositionPrp(1) < this->m_LeftBorder)
				{
					this->m_LeftBorder		= this->m_Maps[i]->g_PositionPrp(1);
				}

				//	Right.
				if (this->m_RightBorder < (this->m_Maps[i]->g_PositionPrp(1) + this->m_Maps[i]->g_MeasuresPrp(1)))
				{
					this->m_RightBorder		= this->m_Maps[i]->g_PositionPrp(1) + this->m_Maps[i]->g_MeasuresPrp(1);
				}

				//	Left.
				if (this->m_TopBorder < this->m_Maps[i]->g_PositionPrp(2))
				{
					this->m_TopBorder		= this->m_Maps[i]->g_PositionPrp(2);
				}

				//	Right.
				if ((this->m_Maps[i]->g_PositionPrp(2) - this->m_Maps[i]->g_MeasuresPrp(2)) < this->m_BottomBorder)
				{
					this->m_BottomBorder	= this->m_Maps[i]->g_PositionPrp(2) - this->m_Maps[i]->g_MeasuresPrp(2);
				}
			}
		}

		//	All pushable buttons.
		{
			//	Lollipop Meadow.
			{
				this->m_PushButtons.push_back(new PushableButton(0.0, 600.0));

				this->m_PushButtons[0]->s_MeasuresPrp(1, this->_Sprites_->g_Sprite(spr::enm_At::PushableButton)->g_Measures()->at(2).Third);
				this->m_PushButtons[0]->s_MeasuresPrp(2, this->_Sprites_->g_Sprite(spr::enm_At::PushableButton)->g_Measures()->at(2).Fourth);

				this->m_PushButtons[0]->s_ID(PushableButton::enm_ID::LevelState, PushableButton::enm_LevelState::LevelUnlocked);
			}
		}
	}
	inline void			Del_All()
	{
		//	Deleting camera related.
		{
			tls::Delete(this->m_CameraMap);
		}

		//	Deleting the background.
		{
			tls::Delete(this->m_BackGround);
		}

		//	Deleting eveything about map.
		{
			tls::DeleteVector(this->m_Maps);
		}

		//	Deleting the little buttons of the map.
		{
			tls::DeleteVector(this->m_PushButtons);
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	Animating the push buttons.
		{
			for (	int i = 0; 
					i < this->m_PushButtons.size(); 
					++i	)
			{
				this->m_PushButtons[i]->Animate();
			}
		}
	}

//	-------------------------------------------
//				Drawing	Functions
//	-------------------------------------------
public:
	inline void			DrawMap()
	{
		int						_SpriteID_What	= spr::enm_At::Maps;
		int						_WhatSprite_	= 0;



		//	Drawing the main background.
		{
			_SpriteID_What			= spr::enm_At::BackGrounds;
			_WhatSprite_			= this->m_BackGround->g_BackGroundID();



			//	Actual Drawing.
			{
				//	Set position to the sprite.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_BackGround->g_PositionPrp(1)	,
																										this->m_BackGround->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_BackGround->g_VisualPrp(1)	,
																									this->m_BackGround->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																										tls::FixPos_Y(	this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



				this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_), false);
			}			
		}

		//	Draw the actual map.
		{
			_SpriteID_What = spr::enm_At::Maps;
			_WhatSprite_			= 0;



			for (	int i = 0; 
					i < this->m_Maps.size(); 
					++i	)
			{
				_WhatSprite_		= this->m_Maps[i]->g_MapID();



				//	Set position to the sprite.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_Maps[i]->g_PositionPrp(1)	,
																										this->m_Maps[i]->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_Maps[i]->g_VisualPrp(1)	,
																									this->m_Maps[i]->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																										tls::FixPos_Y(	this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



				this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
			}
		}

		//	Drawing the little buttons.
		{
			_SpriteID_What			= spr::enm_At::PushableButton;
			_WhatSprite_			= 0;



			for (	int i = 0; 
					i < this->m_PushButtons.size(); 
					++i	)
			{
				_What_Button_ = this->m_PushButtons[i];		//	For now... (12/08/2023 - 1040)



				//	Drawing the back base.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::BackBase;

					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_BackBase(1)	,	
																											_What_Button_->g_FinalPosition_BackBase(2)	);

					//	Here all your color, scale, and more !
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the push button.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::PushButton;

					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_PushButton(1)	,
																											_What_Button_->g_FinalPosition_PushButton(2)	);
												
					//	Here all your color, scale, and more !
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the name (Tag).
				{
					//	Setting the string.
					this->_Text_->g_Text(fnt::enm_At::Vcr)->setString(		_What_Button_->g_Name()		);

					//	Then goes the shrinking model.
					this->_Text_->g_Text(fnt::enm_At::Vcr)->setScale(		_What_Button_->g_VisualPrp(1)		,
																			_What_Button_->g_VisualPrp(2)		);

					//	Fix position to properly render on screen.
					this->_Text_->g_Text(fnt::enm_At::Vcr)->setPosition(	tls::FixPos_X(	_What_Button_->g_FinalPosition_NameTag(1, this->_Text_->g_Text(fnt::enm_At::Vcr)->getGlobalBounds().width), this->xGround)	,
																			tls::FixPos_Y(	_What_Button_->g_FinalPosition_NameTag(2, this->_Text_->g_Text(fnt::enm_At::Vcr)->getGlobalBounds().height), this->yGround)	);



					this->_Draw_->DrawText(	this->_Text_->g_Text(fnt::enm_At::Vcr)	);
				}

				//	Drawing the front base.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::FrontBase;

					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_FrontBase(1)	,
																											_What_Button_->g_FinalPosition_FrontBase(2)	);

					//	Here all your color, scale, and more !
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the lightning of the base.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::LightningBase;

					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_Lightning(1)	,
																											_What_Button_->g_FinalPosition_Lightning(2)	);
												
					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the lightning of the button.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::LighningButton;

					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_LightningButton(1)	,
																											_What_Button_->g_FinalPosition_LightningButton(2)	);
												
					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprites_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}
			}
		}
	}

//	-------------------------------------------
//				Event functions
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{	
		//	Wondering around the map.
		{		
			//	Events when the mouuse is pressed.
			if (		this->_Mouse_->g_Is(1)		&&
					(!this->_A_Button_Was_Pressed)	)
			{		
				int			_x_Camera_		= this->_xLast_Camera_ - this->_Mouse_->g_Position_Camera(	1, 1, this->_Draw_->g_CurrentCamera()	);
				int			_y_Camera_		= this->_yLast_Camera_ - this->_Mouse_->g_Position_Camera(	1, 2, this->_Draw_->g_CurrentCamera()	);
				int			_CameraLeftBorder_		= this->_Draw_->g_CurrentCamera()->g_Bounds(def::enm_CameraLimits::LeftBorder);
				int			_CameraRightBorder_		= this->_Draw_->g_CurrentCamera()->g_Bounds(def::enm_CameraLimits::RightBorder);
				int			_CameraTopBorder_		= this->_Draw_->g_CurrentCamera()->g_Bounds(def::enm_CameraLimits::Cieling);
				int			_CameraBottomBorder_	= this->_Draw_->g_CurrentCamera()->g_Bounds(def::enm_CameraLimits::Floor);
				
				

				//	Map borders.
				//	Left:
				if (	(_CameraLeftBorder_ + _x_Camera_) < this->m_LeftBorder		)
				{
					_x_Camera_		= this->m_LeftBorder - _CameraLeftBorder_;
				}
				//			Right:
				if (	this->m_RightBorder < (_CameraRightBorder_ + _x_Camera_)	)
				{
					_x_Camera_		= this->m_RightBorder - _CameraRightBorder_;
				}
				//	Top:
				//	
				if (	this->m_TopBorder < (_CameraTopBorder_ + _y_Camera_)		)
				{
					_y_Camera_		= this->m_TopBorder - _CameraTopBorder_;
				}
				//	
				//	Bottom:
				if (	(_CameraBottomBorder_ + _y_Camera_) < this->m_BottomBorder	)
				{
					_y_Camera_		= this->m_BottomBorder - _CameraBottomBorder_;
				}



				this->_Draw_->g_CurrentCamera()->Move(	_x_Camera_, _y_Camera_	);
			}



			//	Updating the mouse pointer values.
			{
				//	Getting the last camera position.
				{
					this->_xLast_Camera_ = this->_Mouse_->g_Position_Camera(	1, 1, this->_Draw_->g_CurrentCamera()		);
					this->_yLast_Camera_ = this->_Mouse_->g_Position_Camera(	1, 2, this->_Draw_->g_CurrentCamera()		);
				}
			}
		}

		;	// _-^-_

		//	Tapping on a map button (Little button).
		{
			this->_Buttons_Size			= this->m_PushButtons.size();
			this->_Button_Collision		= false;




			//	...___...___...___...___...___...___...___...
			//			 M O V I N G		M O U S E
			//	...___...___...___...___...___...___...___...
			{	
				//	-------------------------
				//	>	Code for buttons	<
				//	-------------------------
				{
					for	(	int i = 0;
							i < this->_Buttons_Size;
							++i	)	
					{
						this->_What_Button_			= this->m_PushButtons[i];



						//	-------------------------------------------------------------
						//		Whenever the mouse is hovering some button, make that 
						//		button turn other color, or being brighten, or idk...
						//	-------------------------------------------------------------
						{
							//	-------------------------------------------------------------
							//	This switch is pretty simple. Don't confuse with 'where' and
							//	   'when' a button should be enable or so. This is just to   
							//			 do a switch for buttons type, for example a 
							//	  rectangular button or a circular button, and other types.
							//	-------------------------------------------------------------
							{
								//	-------------------------------------------------------------
								//					Getting the mouse position.
								//		Some buttons may require the real position of the mouse
								//				regardless of the camera settings.
								//	-------------------------------------------------------------
								{
									this->_x_	= this->_Mouse_->g_Position_Camera(1, 1, this->_Draw_->g_CurrentCamera());
									this->_y_	= this->_Mouse_->g_Position_Camera(1, 2, this->_Draw_->g_CurrentCamera());
								}



								this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																				this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																				this->_x_, this->_y_, 1, 1)														);
							}



							//	------------------------------------------------------
							//		What this 'if' does is to check whether or not 
							//					a button is hovered.
							//	------------------------------------------------------
							{
								if (this->_Button_Collision)
								{
									if (this->_What_Button_->g_Is(1))
									{
										this->_What_Button_->s_State(3);
									}
									else
									{
										this->_What_Button_->s_State(2);
									}
								}
								else
								{
									this->_What_Button_->s_State(1);
								}
							}
						}
					}
				}
			}



			//	...___...___...___...___...___...___...___...
			//			P R E S S E D 		M O U S E
			//	...___...___...___...___...___...___...___...
			{
				//	-------------------------
				//	>	Code for buttons	<
				//	-------------------------
				{
					for (	int i = 0;
							i < this->_Buttons_Size;
							++i	)	
					{			
						//	-------------------------------------------------------------
						//		Easy. Whenever the mouse is pressed, then do stuff.
						//	-------------------------------------------------------------
						if (	(this->_Mouse_->g_Is(1))	)
						{
							this->_What_Button_ = this->m_PushButtons[i];



							//	-------------------------------------------------------------
							//					Getting the mouse position.
							//		Some buttons may require the real position of the mouse
							//				regardless of the camera settings.
							//	-------------------------------------------------------------
							{
								this->_x_	= this->_Mouse_->g_Position_Camera(2, 1, this->_Draw_->g_CurrentCamera());
								this->_y_	= this->_Mouse_->g_Position_Camera(2, 2, this->_Draw_->g_CurrentCamera());
							}



							//	-------------------------------------------------------------
							//	This switch is pretty simple. Don't confuse with 'where' and
							//	   'when' a button should be enable or so. This is just to   
							//			 do a switch for buttons type, for example a 
							//	  rectangular button or a circular button, and other types.
							//	-------------------------------------------------------------
							this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																			this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																			this->_x_, this->_y_, 1, 1														)	);



							//	------------------------------------------------------
							//		What this 'if' does is to check whether or not 
							//				a button has been pressed.
							//	------------------------------------------------------
							if (	(this->_Button_Collision) && (!this->_What_Button_->g_Is(1))	)
							{
								this->_A_Button_Was_Pressed = true;

								this->_What_Button_->s_State(3);
								this->_What_Button_->s_Is(1, true);

								this->_What_Button_->PushMyButton();
							}
						}
					}
				}
			}



			//	...___...___...___...___...___...___...___...
			//		R E L E A S E D 		M O U S E
			//	...___...___...___...___...___...___...___...
			{
				//	-------------------------
				//	>	Code for buttons	<
				//	-------------------------
				{
					for (	int i = 0;
							i < this->_Buttons_Size;
							++i	)	
					{				
						if (this->_Mouse_->g_Is(2))
						{
							this->_A_Button_Was_Pressed		= false;
							this->_What_Button_				= this->m_PushButtons[i];
					


							//	-------------------------------------------------------------
							//					Getting the mouse position.
							//		Some buttons may require the real position of the mouse
							//				regardless of the camera settings.
							//	-------------------------------------------------------------
							{
								this->_x_	= this->_Mouse_->g_Position_Camera(3, 1, this->_Draw_->g_CurrentCamera());
								this->_y_	= this->_Mouse_->g_Position_Camera(3, 2, this->_Draw_->g_CurrentCamera());
							}



							//	-------------------------------------------------------------
							//	This switch is pretty simple. Don't confuse with 'where' and
							//	   'when' a button should be enable or so. This is just to   
							//			 do a switch for buttons type, for example a 
							//	  rectangular button or a circular button, and other types.
							//	-------------------------------------------------------------
							this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																			this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																			this->_x_, this->_y_, 1.0, 1.0												)	);
					


							//	-------------------------------------------------------------
							//		Also check if the button was previously pressed.
							//	-------------------------------------------------------------
							if (	!this->_What_Button_->g_Is(1)	)
							{
								this->_Button_Collision = false;
							}



							//	-------------------------------------------------------------
							//			Reset all buttons to their original position.
							//	   At the end, when the mouse is released, means that just
							//	  one button will be pressed meanwhile the others will not.
							//	-------------------------------------------------------------
							{
								if (	this->_What_Button_->g_Is(1)	)
								{
									this->_What_Button_->PushMyButton();
									this->_What_Button_->s_Is(1, false);
								}

								this->_What_Button_->s_Is(1, false);
							}
					
					




							//	Cases for all buttons!
							{
								//	Then, checks if the mouse is being pressed.
								if (	this->_Button_Collision	)
								{
									switch (i)
									{
									case 0:
										this->_Buttons_->ChangeRoom(def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::World, snd::MyPlayList::Unwind);
										this->_World_->LoadWorld(STA_::enm_Worlds::LollipopMeadow);
										break;
									}

								}
								else
								{
									this->_What_Button_->s_State(1);
								}
							}
						}
					}
				}
			}
		}	
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
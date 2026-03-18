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
#include	"InfoPanel.h"
#include	"json/json.h"
#include	"Board.h"
#include	"LogicalController.h"



class		WorldScenary
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double			_Win_W = 0.0, _Win_H = 0.0;
	double			xGround = 0.0, yGround = 0.0;

//	-------------------------------------------
//				Important Variables
//	-------------------------------------------
private:
	int				m_WorldID = 0;

//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	double			_x_ = 0.0, _y_	= 0.0;
	double			_xLast_Camera_	= 0.0, _yLast_Camera_ = 0.0;
	double			m_ButtonPush	= -5.0;

	int				_Buttons_Size			= 0;
	int				_Unique_Pressed_Button	= def::enm_Defines::_NOT_FOUND;

	bool			_A_Button_Was_Pressed	= false;
	bool			_Button_Collision		= false;

//	-------------------------------------------
//				Included Variables
//	-------------------------------------------
private:
	Camera*				m_WorldCamera = nullptr;

	BackGround*							m_BackGround	= nullptr;
	std::vector<PushableButton*>		m_PushButtons;

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	PushableButton*			_What_Button_ = nullptr;
	Board*					_SharedBoard_ = nullptr;


	_Controller_Button*		_Buttons_	= nullptr;
	_Basic_Mouse*			_Mouse_		= nullptr;

	SpriteFactory*			_Sprite_	= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	TextFactory*			_Text_		= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	WorldScenary(	int _WorldID	, 
					_Basic_Mouse* _Mouse_Ptr									,	
					SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr			,
					_Controller_Button* _Buttons_Ptr, TextFactory* _Text_Ptr	,
					Board* _Board_Ptr											)
	{
		//	Important values such as IDs, ...
		{
			this->m_WorldID		= _WorldID;
		}

		//	Loading controllers and external linkers.
		{
			this->_Mouse_		= _Mouse_Ptr;

			this->_Draw_		= _Draw_Ptr;
			this->_Sprite_		= _Sprite_Ptr;
			this->_Text_		= _Text_Ptr;

			this->_Buttons_		= _Buttons_Ptr;
			this->_SharedBoard_ = _Board_Ptr;

			this->_Win_W	= this->_Draw_->g_WindowBounds(1);
			this->_Win_H	= this->_Draw_->g_WindowBounds(2);
			this->xGround	= this->_Draw_->g_WorldBounds(1);
			this->yGround	= this->_Draw_->g_WorldBounds(2);
		}



		this->Ld_All();
	}

	~WorldScenary()
	{
		this->Ld_All();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		this->m_BackGround = new BackGround(	0.0, 0.0, 0		);
		this->m_WorldCamera	= new Camera(		0.0, this->yGround / 2.0, this->_Draw_->g_WindowBounds(1), this->_Draw_->g_WindowBounds(2));
	}

	inline void			Del_All()
	{
		tls::Delete(		this->m_BackGround		);
		tls::DeleteVector(	this->m_PushButtons	);
	}


	inline void			CreateLilButtons(int _Amount_)
	{
		for (	int c = 0;
				c < _Amount_;
				++c	)
		{
			this->m_PushButtons.push_back(	new PushableButton(0, 0)	);
		}
	}

//	-------------------------------------------
//				Drawing stuff
//	-------------------------------------------
public:
	inline void			DrawWorld()
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
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_BackGround->g_PositionPrp(1)	,
																										this->m_BackGround->g_PositionPrp(2) 	);

				//	Applying color properties.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(		sf::Color(	this->m_BackGround->g_ColorPrp(1)	,
																													this->m_BackGround->g_ColorPrp(2)	,
																													this->m_BackGround->g_ColorPrp(3)	,
																													this->m_BackGround->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_BackGround->g_VisualPrp(1)	,
																									this->m_BackGround->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																										tls::FixPos_Y(	this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



				this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_), false);
			}			
		}

		//	Drawing the little buttons.
		{
			_SpriteID_What = spr::enm_At::PushableButton;
			_WhatSprite_ = 0;



			for (int i = 0;
				i < this->m_PushButtons.size();
				++i)
			{
				_What_Button_ = this->m_PushButtons[i];		//	For now... (12/08/2023 - 1040)



				//	Drawing the back base.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::BackBase;

					//	Set position to the sprite.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_BackBase(1)	,	
																											_What_Button_->g_FinalPosition_BackBase(2)	);

					//	Here all your color, scale, and more !
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the push button.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::PushButton;

					//	Set position to the sprite.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_PushButton(1)	,
																											_What_Button_->g_FinalPosition_PushButton(2)	);
												
					//	Here all your color, scale, and more !
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
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
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_FrontBase(1)	,
																											_What_Button_->g_FinalPosition_FrontBase(2)	);

					//	Here all your color, scale, and more !
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_What_Button_->g_ColorByState(_WhatSprite_, 1)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 2)	,
																													_What_Button_->g_ColorByState(_WhatSprite_, 3)	,
																													_What_Button_->g_ColorPrp(4)					)	);

					//	Then goes the shrinking model.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the lightning of the base.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::LightningBase;

					//	Set position to the sprite.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_Lightning(1)	,
																											_What_Button_->g_FinalPosition_Lightning(2)	);
												
					//	Then goes the shrinking model.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}

				//	Drawing the lightning of the button.
				{
					_WhatSprite_ = PushableButton::enm_ButtonParts::LighningButton;

					//	Set position to the sprite.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_FinalPosition_LightningButton(1)	,
																											_What_Button_->g_FinalPosition_LightningButton(2)	);
												
					//	Then goes the shrinking model.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(		_What_Button_->g_VisualPrp(1)	,
																											_What_Button_->g_VisualPrp(2)	);

					//	Fix position to properly render on screen.
					this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



					this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_));
				}
			}
		}
	}

//	-------------------------------------------
//			Mouse and keyboard stuff
//	-------------------------------------------
public:
	inline void			MouseStuff(_Controller_InfoPanel* _InfoPanel)
	{
		//	Wondering around the world.
		{		
			//	Events when the mouse is pressed.
			if (		this->_Mouse_->g_Is(1)		&&
					(!this->_A_Button_Was_Pressed)	)
			{		
				int			_x_Camera_		= this->_xLast_Camera_ - this->_Mouse_->g_Position_Camera(	1, 1, this->_Draw_->g_CurrentCamera()	);
				int			_y_Camera_		= this->_yLast_Camera_ - this->_Mouse_->g_Position_Camera(	1, 2, this->_Draw_->g_CurrentCamera()	);



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



			//	---------------------------------
			//		Updating states of buttons
			//	---------------------------------
			{
				for (	int i = 0;
						i < this->_Buttons_Size;
						++i	)
				{
					this->m_PushButtons[i]->s_Is(		Button::enm_Is::IsReleased, false	);
				}
			}


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
									this->_What_Button_->s_State(		Button::enm_State::MouseOver	);
								}
								else
								{
									this->_What_Button_->s_State(		Button::enm_State::Normal		);
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
							this->_What_Button_		= this->m_PushButtons[i];



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
							if (	(this->_Button_Collision) && (!this->_What_Button_->g_Is(1))	&&
									(_Unique_Pressed_Button == def::enm_Defines::_NOT_FOUND)		&&
									(	(this->_What_Button_->g_ID(1) == PushableButton::enm_LevelState::LevelUnlocked) ||
										(this->_What_Button_->g_ID(1) == PushableButton::enm_LevelState::LevelSkipped)	)	)
							{
								this->_A_Button_Was_Pressed		= true;
								this->_Unique_Pressed_Button	= i;

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
								if (	this->_What_Button_->g_Is(Button::enm_Is::IsPressed)	)
								{
									this->_What_Button_->PushMyButton();
									this->_What_Button_->s_Is(Button::enm_Is::IsReleased, true);
								}

								this->_What_Button_->s_Is(	Button::enm_Is::IsPressed, false	);
								this->_Unique_Pressed_Button = def::enm_Defines::_NOT_FOUND;
							}
					
					




							//	Manage the button code.
							{
								//	Then, checks if the mouse is being pressed.
								if (	this->_Button_Collision	)
								{
									_InfoPanel->ShowPanel(	this->_What_Button_->g_ID(2), InfoPanel::enm_PanelAnimation::Show	);
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
//					Functions
//	-------------------------------------------
public:
	inline void			Animator()
	{
		for (	int i = 0; 
				i < this->m_PushButtons.size(); 
				++i	)
		{
			this->m_PushButtons[i]->Animate();
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_ID()
	{
		return		this->m_WorldID;
	}

	inline Camera*								g_WorldCamera()
	{
		return			this->m_WorldCamera;
	}
	inline BackGround*							g_BG()
	{
		return		this->m_BackGround;
	}
	inline std::vector<PushableButton*>&		g_LilButtons()
	{
		return		this->m_PushButtons;
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
class	_Controller_World
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1]	Variables
//	-------------------------------------------
private:
	Board*		m_Board		= nullptr;

//	-------------------------------------------
//			[2]	Auxiliar Variables
//	-------------------------------------------
private:
	WorldScenary*		_What_World_	= nullptr;

//	-------------------------------------------
//		[3] Containers and Controllers
//	-------------------------------------------
private:
	_Controller_InfoPanel*				m_InfoPanel;
	std::vector<WorldScenary*>			m_Worlds;

//	-------------------------------------------
//			[4] External and linkers
//	-------------------------------------------
private:
	_Controller_Button*		_Buttons_			= nullptr;
	_Basic_Mouse*			_Mouse_				= nullptr;
	_Basic_KeyBoard*		_KeyBoard_			= nullptr;

	SpriteFactory*			_Sprite_			= nullptr;
	DrawFactory*			_Draw_				= nullptr;
	TextFactory*			_Text_				= nullptr;
	ShaderFactory*			_Shaders_			= nullptr;
	SoundFactory*			_Sounds_			= nullptr;
	sql::SQLConnector*		_SQLConnection_		= nullptr;
	_Controller_Logic*		_Logical_			= nullptr;

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
private:
	inline void			Ld_All()
	{
		//	Same case for the board.
		//	m_Board is unique from this controller.
		//	Multiple worlds uses the same Board (with caution of course). 
		this->m_Board		= new Board(	this->_Mouse_, this->_KeyBoard_, this->_Sounds_	, 
											this->_Draw_->g_CurrentCamera(), this->_Draw_	,	
											this->_Sprite_, this->_Text_, this->_Shaders_	,
											this->_SQLConnection_, this->_Logical_			);
		
		//	There is only one info-panel per controller.
		//	Not all worlds have an info-panel.
		//	Multiple worlds use this one.
		this->m_InfoPanel	= new _Controller_InfoPanel(	this->_Mouse_, this->_KeyBoard_		,
															this->_Sprite_, this->_Draw_		,
															this->_Buttons_, this->_Shaders_	,
															this->m_Board						);
	}
	inline void			Del_All()
	{
		tls::Delete(			this->m_InfoPanel		);
		tls::DeleteVector(		this->m_Worlds			);
	}




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_World(	_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _KeyBoard_Ptr	,
						SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr			,	
						_Controller_Button* _Buttons_Ptr, TextFactory* _Text_Ptr	,
						ShaderFactory* _Shader_Ptr, SoundFactory* _Sound_Ptr		,
						sql::SQLConnector* _SQL_Ptr, _Controller_Logic* _Logic_Ptr	)
	{
		this->_KeyBoard_		= _KeyBoard_Ptr;
		this->_Mouse_			= _Mouse_Ptr;

		this->_Draw_			= _Draw_Ptr;
		this->_Sprite_			= _Sprite_Ptr;
		this->_Text_			= _Text_Ptr;
		this->_Shaders_			= _Shader_Ptr;
		this->_Sounds_			= _Sound_Ptr;
		this->_SQLConnection_	= _SQL_Ptr;
		this->_Logical_			= _Logic_Ptr;

		this->_Buttons_			= _Buttons_Ptr;



		this->Ld_All();
	}

	~_Controller_World()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading	Functions
//	-------------------------------------------
public:
	inline void				LoadWorld(	int _WorldID	)
	{
		std::string		_Source_					= "_Resources_\\DataAndThingYouAreNotSupposedToSee\\Worlds\\";
		int				_World_Already_Loaded_		= def::enm_Defines::_NOT_FOUND;



		//	------------------------------------------------
		//		Switching and finding what world to load
		//	------------------------------------------------
		{
			//	First off, find if the world has been already loaded.
			{
				for (	int i = 0; 
						i < this->m_Worlds.size(); 
						++i	)
				{
					if (	_WorldID == this->m_Worlds[i]->g_ID()	)
					{
						_World_Already_Loaded_ = i;
						break;
					}
				}
			}

			//	Should I load the requested world?
			{
				if (	_World_Already_Loaded_ == def::enm_Defines::_NOT_FOUND	)
				{
					switch (	_WorldID	)
					{
					case	STA_::enm_Worlds::LollipopMeadow:
						_Source_ += "LollipopMeadow.json";
						break;
					}



					this->m_Worlds.push_back(	new WorldScenary(	_WorldID						, 
																	this->_Mouse_, this->_Sprite_	, 
																	this->_Draw_, this->_Buttons_	,
																	this->_Text_					,
																	this->m_Board					)	);

					this->_What_World_ = this->m_Worlds[this->m_Worlds.size() - 1];					
				}
				else
				{
					this->_What_World_ = this->m_Worlds[_World_Already_Loaded_];
				}			
			}	

			//	Some camera linking.			
			{
				this->_Draw_->LinkCamera(	this->_What_World_->g_WorldCamera(), drw::MyCamera::WorldCamera			);
				this->_Draw_->UseCamera(	drw::MyCamera::WorldCamera, this->_Buttons_->g_TimeTransition() / 2.0	);
			
				if (	_World_Already_Loaded_ != def::enm_Defines::_NOT_FOUND	)
				{
					return;
				}
			}
		}

		//	------------------------------------------------
		//					Read the files
		//	------------------------------------------------
		{
			std::ifstream		File(_Source_);
			Json::Reader		Reader;
			Json::Value			Objects;


			//	If the file couldn't be opened.
			if (	!File.is_open()	)
			{
				std::cout << "Couldn't read file. Proceeding to an error!\n";
				throw	std::runtime_error("JSON file not opened.");
				return;
			}

			//	Read then.
			Reader.parse(File, Objects);
				
			this->_What_World_->g_BG()->s_BackGroundID(Objects["BackGround"]["BackGroundID"].asInt());
			this->_What_World_->g_BG()->s_ColorPrp(1, Objects["BackGround"]["ColorR"].asInt());
			this->_What_World_->g_BG()->s_ColorPrp(2, Objects["BackGround"]["ColorG"].asInt());
			this->_What_World_->g_BG()->s_ColorPrp(3, Objects["BackGround"]["ColorB"].asInt());
			this->_What_World_->g_BG()->s_ColorPrp(4, Objects["BackGround"]["ColorA"].asInt());

			
			std::vector<PushableButton*>*	_PushButton_		= &this->_What_World_->g_LilButtons();
			int								_Container_Size		= Objects["Level"]["Size"].asInt();
			this->_What_World_->CreateLilButtons(_Container_Size);
			for (	int i = 0; 
					i < _Container_Size; 
					++i	)
			{
				//	Positions.
				_PushButton_->at(i)->s_PositionPrp(	1, Objects["Level"]["Where"][tls::IntToStr(i)]["xP"].asInt());
				_PushButton_->at(i)->s_PositionPrp(	2, Objects["Level"]["Where"][tls::IntToStr(i)]["yP"].asInt()	);
				_PushButton_->at(i)->s_PositionPrp(	9, Objects["Level"]["Where"][tls::IntToStr(i)]["zP"].asInt()	);
				
				//	Measures.
				_PushButton_->at(i)->s_MeasuresPrp(	1, this->_Sprite_->g_Sprite(spr::enm_At::PushableButton)->g_Measures()->at(2).Third		);
				_PushButton_->at(i)->s_MeasuresPrp(	2, this->_Sprite_->g_Sprite(spr::enm_At::PushableButton)->g_Measures()->at(2).Fourth	);
				
				//	LevelID.
				_PushButton_->at(i)->s_ID(	1, Objects["Level"]["Where"][tls::IntToStr(i)]["ID"].asInt()	);

				//	LevelState.
				_PushButton_->at(i)->s_ID(	2, Objects["Level"]["Where"][tls::IntToStr(i)]["LevelState"].asInt()	);
			}
		}
	}

//	-------------------------------------------
//				Drawing	Functions
//	-------------------------------------------
public:
	inline void			DrawWorld()
	{
		//	Drawing the world.
		this->_What_World_->DrawWorld();

		//	Drawing the panel.
		this->m_InfoPanel->DrawInfoPanel();
	}

//	-------------------------------------------
//				Event functions
//	-------------------------------------------
public:
	inline void			EventsStuff()
	{	
		//	Events about the world itself.
		this->_What_World_->MouseStuff(this->m_InfoPanel);

		//	Events about info panel.
		this->m_InfoPanel->MouseStuff();
		this->m_InfoPanel->KeyBoardStuff();
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			LogicNow()
	{
		this->_What_World_->Animator();
		this->m_InfoPanel->LogicDis();
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline Board*		g_Board()	const
	{
		return		this->m_Board;
	}
};
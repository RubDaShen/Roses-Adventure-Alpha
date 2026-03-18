#pragma once

#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<vector>
#include	<json/json.h>

#include	"thyObject.h"
#include	"_MyIncludes_.h"
#include	"Tools_.h"
#include	"SpriteFactory.h"
#include	"DrawFactory.h"
#include	"BackGrounds.h"
#include	"_Basics_Button.h"
#include	"_Basics_Mouse.h"
#include	"Board.h"



class		LevelBanner : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int		m_LevelNumber		= 0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LevelBanner(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~LevelBanner()
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
	inline void		SetNumber(int Value)
	{
		this->m_LevelNumber		= Value;
	}
	inline int		GetNumber()
	{
		return		this->m_LevelNumber;
	}	

	inline int			g_SpritePosition(int What)
	{
		switch (What)
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
class		InfoPanel : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Showing (Coming) Variables
//	-------------------------------------------
private:
	int			m_WhatAnimation		= 1;

	double		m_MoveAmount		= 500.0;
	double		m_ShowingTime		= 0.15;
	double		m_Time				= 0.0;

	double					m_xPosOrigin			= 0.0;
	std::vector<double>		m_xPosButtonOrigin;
	double					m_xPosLevelBannerOrigin = 0.0;

//	-------------------------------------------
//				Other objects
//	-------------------------------------------
private:
	std::vector<BasicButton*>		m_Buttons;
	LevelBanner*					m_LevelBanner;

//	-------------------------------------------
//			Auxiliars and helpers
//	-------------------------------------------
private:
	BasicButton*		_What_Button_	= nullptr;

	int			_Buttons_Size			= 0;
	bool		_Button_Collision		= 0;
	double		_x_ = 0.0, _y_ = 0.0;
	bool		_A_Button_Was_Pressed	= false;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_LevelSelected		= def::enm_Defines::_NOT_INITIALIZED;
	bool		m_LaunchLevel		= false;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_					= nullptr;
	SpriteFactory*			_Sprites_				= nullptr;
	ShaderFactory*			_Shaders_				= nullptr;
	_Basic_KeyBoard*		_KeyBoard_				= nullptr;
	_Basic_Mouse*			_Mouse_					= nullptr;
	_Controller_Button*		_Buttons_Controller_	= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//						Enums!
//	-------------------------------------------
public:
	enum	enm_PanelAnimation
	{
		Show	= 0,
		Hide	= 1
	};

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	InfoPanel(	double _xP, double _yP, double _Width, double _Height			,	 
				_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _Keyboard_Ptr		,
				DrawFactory* _Draw_Ptr, _Controller_Button* _Button_Controller	,
				ShaderFactory* _Shader_Ptr, SpriteFactory* _Sprites_Ptr			) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_xPosOrigin			= _xP;
		this->_KeyBoard_			= _Keyboard_Ptr;
		this->_Mouse_				= _Mouse_Ptr;
		this->_Draw_				= _Draw_Ptr;
		this->_Buttons_Controller_	= _Button_Controller;
		this->_Shaders_				= _Shader_Ptr;
		this->_Sprites_				= _Sprites_Ptr;

		this->_W	= _Width;
		this->_H	= _Height;

		this->LoadAll();
	}

	~InfoPanel()
	{
		this->DeleteAll();
	}

//	-------------------------------------------
//				Loading functions
//	-------------------------------------------
public:
	inline void			LoadAll()
	{
		//	Buttons.
		{
			//	Close Button.
			{
				double			xPosCloseButton = 685.0;
				double			yPosCloseButton = 77.0;

				this->m_Buttons.push_back(	new BasicButton(	this->xP + xPosCloseButton, this->yP - yPosCloseButton			, 
																def::enm_Defines::_SKIP_THIS, Button::enm_HitBoxType::Circular	, 
																STA_::enm_ButtonID::CloseButton, true							)	);

				this->m_xPosButtonOrigin.push_back(this->xP + xPosCloseButton);
				this->m_Buttons[this->m_Buttons.size() - 1]->s_MeasuresPrp(3, this->_Sprites_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::CloseButton).Third / 2.0);
			}	

			//	PlayLevel Button.
			{
				double			xPosPlayLevelButton		= (this->_W - this->_Sprites_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::PlayLevelButton).Third) / 2.0;
				double			yPosPlayLevelButton		= 775.0;

				this->m_Buttons.push_back(	new BasicButton(	this->xP + xPosPlayLevelButton, this->yP - yPosPlayLevelButton		,
																def::enm_Defines::_SKIP_THIS, Button::enm_HitBoxType::Rectangular	, 
																STA_::enm_ButtonID::PlayLevelButton, true							)	);

				this->m_xPosButtonOrigin.push_back(this->xP + xPosPlayLevelButton);
				this->m_Buttons[this->m_Buttons.size() - 1]->s_MeasuresPrp(1, this->_Sprites_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::PlayLevelButton).Third);
				this->m_Buttons[this->m_Buttons.size() - 1]->s_MeasuresPrp(2, this->_Sprites_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::PlayLevelButton).Fourth);
			}	
		}

		//	Level banner.
		{
			double		WidthDistance	= (this->_W - this->_Sprites_->g_Sprite(spr::enm_At::LevelInfoPanel)->g_Measures()->at(1).Third) / 2.0;
			double		HeightDistance	= -128.0;

			this->m_LevelBanner		= new LevelBanner(this->xP + WidthDistance, this->yP + HeightDistance);
			this->m_LevelBanner->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::LevelInfoPanel)->g_Measures()->at(1).Third);
			this->m_LevelBanner->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::LevelInfoPanel)->g_Measures()->at(1).Fourth);

			this->m_xPosLevelBannerOrigin	= this->xP + WidthDistance;
		}



		//	Setting up.
		{
			this->m_Time	=	this->m_ShowingTime + 1.0;
			this->SetAnimation(InfoPanel::enm_PanelAnimation::Show, false);
		}
	}
	inline void			DeleteAll()
	{
		tls::DeleteVector(this->m_Buttons);
		tls::Delete(this->m_LevelBanner);
	}

//	-------------------------------------------
//				Events functions
//	-------------------------------------------
public:
	inline void			KeyBoardStuff()
	{
		//	Temporary solution.
		if (	this->_KeyBoard_->g_Key(kyb::Key::Enter)->g_Is(3)	)
		{
			//	Make a level transition.
			this->_Buttons_Controller_->ChangeRoom(def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::LevelTransition, def::enm_Defines::_SKIP_THIS);
			this->_Draw_->UseCamera(drw::MyCamera::MainCamera, this->_Buttons_Controller_->g_TimeTransition() / 2.0);
		}
	}
	inline void			MouseStuff()
	{
		this->_Buttons_Size			= this->m_Buttons.size();
		this->_Button_Collision		= false;



		//	---------------------------------
		//		Updating states of buttons
		//	---------------------------------
		{
			for (	int i = 0;
					i < this->_Buttons_Size;
					++i	)
			{
				this->_What_Button_		= this->m_Buttons[i];
				this->_What_Button_->s_Is(		Button::enm_Is::IsReleased, false	);
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
					this->_What_Button_		= this->m_Buttons[i];



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
								if (	this->_What_Button_->g_IgnoresCam()	)
								{
									this->_x_	= this->_Mouse_->g_Position(1, 1);
									this->_y_	= this->_Mouse_->g_Position(1, 2);
								}
								else
								{
									this->_x_	= this->_Mouse_->g_Position_Camera(1, 1, this->_Draw_->g_CurrentCamera());
									this->_y_	= this->_Mouse_->g_Position_Camera(1, 2, this->_Draw_->g_CurrentCamera());
								}
							}



							switch (this->_What_Button_->g_ButtonType())
							{
							case 1:
								this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																				this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																				this->_x_, this->_y_, 1, 1)													);
								break;

							case 2:
								this->_Button_Collision = (tls::RectangleCollidesWithCircle(	this->_x_, this->_y_, 1, 1														,
																								this->_What_Button_->g_PositionPrp(1) + (this->_What_Button_->g_MeasuresPrp(3))	,
																								this->_What_Button_->g_PositionPrp(2) - (this->_What_Button_->g_MeasuresPrp(3))	,
																								this->_What_Button_->g_MeasuresPrp(3))											);
								break;
							}
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
						this->_What_Button_		= this->m_Buttons[i];



						//	-------------------------------------------------------------
						//					Getting the mouse position.
						//		Some buttons may require the real position of the mouse
						//				regardless of the camera settings.
						//	-------------------------------------------------------------
						{
							if (	this->_What_Button_->g_IgnoresCam()	)
							{
								this->_x_	= this->_Mouse_->g_Position(4, 1);
								this->_y_	= this->_Mouse_->g_Position(4, 2);
							}
							else
							{
								this->_x_	= this->_Mouse_->g_Position_Camera(4, 1, this->_Draw_->g_CurrentCamera());
								this->_y_	= this->_Mouse_->g_Position_Camera(4, 2, this->_Draw_->g_CurrentCamera());
							}
						}



						//	-------------------------------------------------------------
						//	This switch is pretty simple. Don't confuse with 'where' and
						//	   'when' a button should be enable or so. This is just to   
						//			 do a switch for buttons type, for example a 
						//	  rectangular button or a circular button, and other types.
						//	-------------------------------------------------------------
						switch (this->_What_Button_->g_ButtonType())
						{
						case 1:
							this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																			this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																			this->_x_, this->_y_, 1, 1													)	);
							break;

						case 2:
							this->_Button_Collision = (tls::RectangleCollidesWithCircle(	this->_x_, this->_y_, 1, 1,
																							this->_What_Button_->g_PositionPrp(1) + (this->_What_Button_->g_MeasuresPrp(3))	,
																							this->_What_Button_->g_PositionPrp(2) - (this->_What_Button_->g_MeasuresPrp(3))	,
																							this->_What_Button_->g_MeasuresPrp(3)											)	);
							break;
						}



						//	------------------------------------------------------
						//		What this 'if' does is to check whether or not 
						//				a button has been pressed.
						//	------------------------------------------------------
						if (	(this->_Button_Collision) && (!this->_What_Button_->g_Is(Button::enm_Is::IsPressed))	)
						{
							this->_What_Button_->s_Is(		Button::enm_Is::IsPressed, true		);
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
					if (	this->_Mouse_->g_Is(2)	)
					{
						this->_What_Button_		= this->m_Buttons[i];



						
				


						//	-------------------------------------------------------------
						//					Getting the mouse position.
						//		Some buttons may require the real position of the mouse
						//				regardless of the camera settings.
						//	-------------------------------------------------------------
						{
							if (	this->_What_Button_->g_IgnoresCam()	)
							{
								this->_x_	= this->_Mouse_->g_Position(3, 1);
								this->_y_	= this->_Mouse_->g_Position(3, 2);
							}
							else
							{
								this->_x_	= this->_Mouse_->g_Position_Camera(3, 1, this->_Draw_->g_CurrentCamera());
								this->_y_	= this->_Mouse_->g_Position_Camera(3, 2, this->_Draw_->g_CurrentCamera());
							}
						}



						//	-------------------------------------------------------------
						//	This switch is pretty simple. Don't confuse with 'where' and
						//	   'when' a button should be enable or so. This is just to   
						//			 do a switch for buttons type, for example a 
						//	  rectangular button or a circular button, and other types.
						//	-------------------------------------------------------------
						switch (this->_What_Button_->g_ButtonType())
						{
						case 1:
							this->_Button_Collision = (tls::CollidesWith(	this->_What_Button_->g_PositionPrp(1), this->_What_Button_->g_PositionPrp(2)	,
																			this->_What_Button_->g_MeasuresPrp(1), this->_What_Button_->g_MeasuresPrp(2)	,
																			this->_x_, this->_y_, 1.0, 1.0												)	);
							break;
				
						case 2:
							this->_Button_Collision = (tls::RectangleCollidesWithCircle(	this->_x_, this->_y_, 1.0, 1.0													,
																							this->_What_Button_->g_PositionPrp(1) + (this->_What_Button_->g_MeasuresPrp(3))	,
																							this->_What_Button_->g_PositionPrp(2) - (this->_What_Button_->g_MeasuresPrp(3))	,
																							this->_What_Button_->g_MeasuresPrp(3)											)	);
							break;
						}



						//	-------------------------------------------------------------
						//		Also check if the button was previously pressed.
						//	-------------------------------------------------------------
						if (	!this->_What_Button_->g_Is(	Button::enm_Is::IsPressed	)	)
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
								this->_What_Button_->s_Is(Button::enm_Is::IsReleased, true);
							}

							this->_What_Button_->s_Is(	Button::enm_Is::IsPressed, false	);
						}

				

						//	Then, checks if the mouse is being pressed.
						if (	this->_Button_Collision	)
						{
							switch (i)
							{
							case 0:		//	Close Button.
								this->SetAnimation(InfoPanel::enm_PanelAnimation::Hide);

								break;

							case 1:		//	PlayLevel Button.
								this->SetAnimation(InfoPanel::enm_PanelAnimation::Hide);
								this->_Buttons_Controller_->ChangeRoom(def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::LevelTransition);
								this->m_LaunchLevel = true;

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

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			SetAnimation(	int _WhatAnimation, bool StartAnimation = true	)
	{
		//	The animation is whether
		//	is showing or hiding.
		//	Use InfoPanel::enm_PanelAnimation
		
		this->m_WhatAnimation	= _WhatAnimation;
		if (	StartAnimation	)
		{
			this->m_Time = 0.0;
		}

		switch (	this->m_WhatAnimation	)
		{
		case	InfoPanel::Show:
			//	Panel.
			this->A_alpha	= 0.0;
			this->xP		= this->m_xPosOrigin - this->m_MoveAmount;

			//	Buttons.
			for (	int i = 0; 
					i < this->m_Buttons.size(); 
					++i	)
			{
				this->_What_Button_ = this->m_Buttons[i];
				this->_What_Button_->s_ColorPrp(4, 0.0);
				this->_What_Button_->s_PositionPrp(1, this->m_xPosButtonOrigin[i] - this->m_MoveAmount);
			}

			//	Level Banner.
			this->m_LevelBanner->s_ColorPrp(4, 0.0);
			this->m_LevelBanner->s_PositionPrp(1, this->m_xPosLevelBannerOrigin - this->m_MoveAmount);



			this->Alpha_s	= 255.0 / (_Controller_Logic::_ogLpV_ * this->m_ShowingTime);
			this->xS		= this->m_MoveAmount / (_Controller_Logic::_ogLpV_ * this->m_ShowingTime);

			break;

		case	InfoPanel::Hide:
			//	Panel.
			this->A_alpha	= 255.0;

			//	Buttons.
			for (	int i = 0; 
					i < this->m_Buttons.size(); 
					++i	)
			{
				this->_What_Button_		= this->m_Buttons[i];
				this->_What_Button_->s_ColorPrp(4, 255.0);
			}

			//	Level Banner.
			this->m_LevelBanner->s_ColorPrp(4, 255.0);



			this->Alpha_s	= -255.0 / (_Controller_Logic::_ogLpV_ * this->m_ShowingTime);
			this->xS		= this->m_MoveAmount / (_Controller_Logic::_ogLpV_ * this->m_ShowingTime);

			break;
		}
	}
	inline void			Animate()
	{
		//	Panel and buttons.
		if (	this->m_Time < this->m_ShowingTime	)
		{
			//	It is better to move the whole panel 
			//	(not adding a variable to the positions) since it will 
			//	become difficult to calculate and manage the collisions.

			//	Panel.
			this->xP		= this->xP + this->xS;
			this->A_alpha	= this->A_alpha + this->Alpha_s;
			
			if (	this->A_alpha >= 255.0	)
			{
				this->A_alpha = 255.0;
			}
			if (	this->A_alpha <= 0.0	)
			{
				this->A_alpha = 0.0;
			}

			//	Buttons.
			for (	int i = 0; 
					i < this->m_Buttons.size(); 
					++i	)
			{
				this->_What_Button_		= this->m_Buttons[i];

				this->_What_Button_->s_PositionPrp(1, this->m_Buttons[i]->g_PositionPrp(1) + this->xS);
				this->_What_Button_->s_ColorPrp(4, this->m_Buttons[i]->g_ColorPrp(4) + this->Alpha_s);

				if (	this->_What_Button_->g_ColorPrp(4) >= 255.0	)
				{
					this->_What_Button_->s_ColorPrp(4, 255.0);
				}
				if (	this->_What_Button_->g_ColorPrp(4) <= 0.0	)
				{
					this->_What_Button_->s_ColorPrp(4, 0.0);
				}
			}

			//	Level Banner.
			this->m_LevelBanner->s_PositionPrp(1, this->m_LevelBanner->g_PositionPrp(1) + this->xS);
			this->m_LevelBanner->s_ColorPrp(4, this->m_LevelBanner->g_ColorPrp(4) + this->Alpha_s);
			
			if (	this->m_LevelBanner->g_ColorPrp(4) >= 255.0)
			{
				this->m_LevelBanner->s_ColorPrp(4, 255.0);
			}
			if (	this->m_LevelBanner->g_ColorPrp(4) <= 0.0	)
			{
				this->m_LevelBanner->s_ColorPrp(4, 0.0);
			}
		}

		//	Buttons (Shading).
		for (	int i = 0; 
				i < this->m_Buttons.size(); 
				++i	)
		{
			this->_What_Button_		= this->m_Buttons[i];
			this->_What_Button_->Animate();
		}


		this->m_Time = this->m_Time + (1.0 / _Controller_Logic::_ogLpV_);
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			DrawPanel()
	{
		//	Drawing the panel itself.
		{
			this->_What_Sprite_		= spr::enm_At::LevelInfoPanel;
			this->_What_Kind_		= 0;
		
		
		
			//	Draw the panel.
			{
				this->_What_Kind_		= 0;
		
		
				//	Set position to the sprite.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->xP + (this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Third / 2.0)	,
																													this->yP - (this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Fourth / 2.0)	);
		
				//	Then goes the shrinking model.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(	this->xFct, this->yFct	);
		
				//	Applying color properties.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(	this->R_col, this->G_col, this->B_col, this->A_alpha)	);
		
				//	Fix position to properly render on screen.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																													tls::FixPos_Y(	this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
		
		
		
				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}

			//	Draw the level banner.
			{
				this->_What_Kind_		= 1;
		
		
				//	Set position to the sprite.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(this->m_LevelBanner->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1))	,
																													tls::FixPos_Y(this->m_LevelBanner->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2))	);
		
				//	Then goes the shrinking model.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(	this->m_LevelBanner->g_VisualPrp(1), this->m_LevelBanner->g_VisualPrp(2)	);
		
				//	Applying color properties.
				this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_LevelBanner->g_ColorPrp(1)	, 
																															this->m_LevelBanner->g_ColorPrp(2)	, 
																															this->m_LevelBanner->g_ColorPrp(3)	,
																															this->m_LevelBanner->g_ColorPrp(4)	) );
		
		
		
				this->_Draw_->Draw(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false);
			}
		
			//	Draw the buttons.
			{
				this->_What_Sprite_		= spr::enm_At::Buttons;
				this->_Buttons_Size		= this->m_Buttons.size();
		
		
		
				for (	int i = 0;
						i < this->_Buttons_Size;
						++i	)
				{
					this->_What_Button_		= this->m_Buttons[i];
					this->_What_Kind_		= this->_What_Button_->g_SpriteID();
		
		
		
					//	Set position to the sprite.
					this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->_What_Button_->g_PositionPrp(1) + (this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Third / 2.0)	,
																														this->_What_Button_->g_PositionPrp(2) - (this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Kind_).Fourth / 2.0)	);
		
					//	Then goes the shrinking model.
					this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(	this->_What_Button_->g_VisualPrp(1)	,
																													this->_What_Button_->g_VisualPrp(2)	);				

					//	Fix position to properly render on screen.
					this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																														tls::FixPos_Y(	this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
		
					//	Usage of shaders.
					this->_Shaders_->s_Uniform_Brightness(	this->_What_Button_->g_Brightness(), this->_What_Button_->g_ColorPrp(4) / 255.0		);
					
		
		
					this->_Draw_->DrawShader(this->_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), this->_Shaders_->g_Shader(shd::MyShaders::Brightness), !this->_What_Button_->g_IgnoresCam());
				}
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_LevelSelected(int Value)
	{
		this->m_LevelSelected	= Value;
	}
	inline int			g_LevelSelected(bool MakeFalse)
	{
		if (	this->m_LaunchLevel		)
		{
			this->m_LaunchLevel = !MakeFalse;
			return		this->m_LevelSelected;
		}
		else
		{
			return		def::enm_Defines::_NOT_INITIALIZED;
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
class		_Controller_InfoPanel
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double		xGround = 0, yGround = 0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:


//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	int				_What_Sprite_	= 0;
	int				_What_Kind_		= 0;
	

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	InfoPanel*		m_LevelInfoPanel = nullptr;

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	_Controller_Button*		_Buttons_		= nullptr;
	_Basic_Mouse*			_Mouse_			= nullptr;
	_Basic_KeyBoard*		_KeyBoard_		= nullptr;
	Board*					_Board_			= nullptr;

	SpriteFactory*			_Sprite_	= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	ShaderFactory*			_Shaders_	= nullptr;

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
private:
	inline void			Ld_All()
	{
		int		SpriteWidth		= this->_Sprite_->g_Sprite(spr::enm_At::LevelInfoPanel)->g_Measures()->at(0).Third;
		int		SpriteHeight	= this->_Sprite_->g_Sprite(spr::enm_At::LevelInfoPanel)->g_Measures()->at(0).Fourth;
		int		xPos			= (this->_Draw_->g_WindowBounds(1) - SpriteWidth) / 2.0;
		int		yPos			= (this->_Draw_->g_WindowBounds(2) + SpriteHeight) / 2.0;

		this->m_LevelInfoPanel	= new InfoPanel(	tls::TransformPos_X(xPos, this->_Draw_->g_WorldBounds(1)), yPos, SpriteWidth, SpriteHeight		, 
													this->_Mouse_, this->_KeyBoard_, this->_Draw_, this->_Buttons_, this->_Shaders_, this->_Sprite_	);
		
	}
	inline void			Del_All()
	{
		tls::Delete(this->m_LevelInfoPanel);
	}

	inline void			LoadLevel(	int WhatLevel	)
	{
		//	----------------------------------------------
		//		There are over hundreds of worlds!
		//	All of them have unique IDs and this function
		//		is the responsible to load them up.
		//	----------------------------------------------
		std::fstream			_File_;
		std::string				_Source_ = "_Resources_\\DataAndThingYouAreNotSupposedToSee\\Levels\\" + tls::IntToStr(WhatLevel) + ".json";
		


		//	------------------------------------------------
		//		If world has not been loaded previously, 
		//			then loaded it from file.
		//	------------------------------------------------
		{
			std::ifstream		File(_Source_);
			Json::Reader		Reader;
			Json::Value			Objects;


			//	If the file couldn't be opened.
			if (	!File.is_open()	)
			{
				std::cout << "Couldn't read file (level information). Proceeding to an error!\n";
				throw	std::runtime_error("JSON file not opened.");
				return;
			}

			//	Read then.
			Reader.parse(File, Objects);
			
			//	Verify.
			if (	!this->_Board_->IsBrandNew()	)
			{
				return;
			}

			//	Create!
			int		BoardWidth		= Objects["BoardWidth"].asInt();
			int		BoardHeight		= Objects["BoardHeight"].asInt();
			this->_Board_->CreateBoard(BoardWidth, BoardHeight, 0.0, 0.0);
		}
	}




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_InfoPanel(	_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _KeyBoard_Ptr		,
							SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr				,
							_Controller_Button* _Buttons_Ptr, ShaderFactory* _Shader_Ptr	,
							Board* _Board_Ptr												)
	{
		this->_KeyBoard_	= _KeyBoard_Ptr;
		this->_Mouse_		= _Mouse_Ptr;
		this->_Draw_		= _Draw_Ptr;
		this->_Sprite_		= _Sprite_Ptr;
		this->_Buttons_		= _Buttons_Ptr;
		this->_Shaders_		= _Shader_Ptr;
		this->_Board_		= _Board_Ptr;


		this->xGround	= _Draw_Ptr->g_WorldBounds(1);
		this->yGround	= _Draw_Ptr->g_WorldBounds(2);



		this->Ld_All();
	}

	~_Controller_InfoPanel()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Drawing	Functions
//	-------------------------------------------
public:
	inline void			DrawInfoPanel()
	{
		this->m_LevelInfoPanel->DrawPanel();
	}

//	-------------------------------------------
//				Event functions
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{	
		this->m_LevelInfoPanel->MouseStuff();
	}
	inline void			KeyBoardStuff()
	{
		this->m_LevelInfoPanel->KeyBoardStuff();
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			ShowPanel(	int _WhatLevel, int _WhatAnimation	)
	{
		//	Panel Animation.
		this->m_LevelInfoPanel->s_LevelSelected(	_WhatLevel	);
		this->m_LevelInfoPanel->SetAnimation(	_WhatAnimation	);
	}

	inline void			LogicDis()
	{
		//	Pure animation and effects.
		this->m_LevelInfoPanel->Animate();

		//	Logical: Create the level.
		if (	this->m_LevelInfoPanel->g_LevelSelected(false) != def::enm_Defines::_NOT_INITIALIZED	)
		{
			this->LoadLevel(this->m_LevelInfoPanel->g_LevelSelected(true));
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
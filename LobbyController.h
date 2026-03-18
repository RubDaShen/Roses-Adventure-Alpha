#pragma once

#include	<vector>

#include	"_MyIncludes_.h"
#include	"thyObject.h"
#include	"Tools_.h"
#include	"SpriteFactory.h"
#include	"ShaderFactory.h"
#include	"DrawFactory.h"
#include	"BackGrounds.h"
#include	"_Basics_Button.h"
#include	"_Basics_Mouse.h"



class		_Controller_Lobby
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
//					Variables
//	-------------------------------------------
private:
	double			m_ButtonPush = 0.0;

//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	BasicButton*		_What_Button_	= nullptr;

	double		_x_ = 0.0, _y_ = 0.0;

	int			_Buttons_Size			= 0.0;

	bool		_Button_Collision		= false;
	bool		_A_Button_Was_Pressed	= false;

//	-------------------------------------------
//					Containters
//	-------------------------------------------
private:
	std::vector<BasicButton*>		m_LobbyButtons;

//	-------------------------------------------
//				Included Variables
//	-------------------------------------------
private:
	BackGround*			m_BackGround = nullptr;

//	-------------------------------------------
//				External and linkers
//	-------------------------------------------
private:
	_Controller_Button*		_Buttons_	= nullptr;
	_Basic_Mouse*			_Mouse_		= nullptr;

	SpriteFactory*			_Sprite_	= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	ShaderFactory*			_Shader_	= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Lobby(	_Basic_Mouse* _Mouse_Ptr							,
						SpriteFactory* _Sprite_Ptr, DrawFactory* _Draw_Ptr	,
						ShaderFactory* _Shader_Ptr							,
						_Controller_Button* _Buttons_Ptr					)
	{
		//	Linking external.
		{
			this->_Buttons_ = _Buttons_Ptr;

			this->_Mouse_	= _Mouse_Ptr;
			this->_Draw_	= _Draw_Ptr;
			this->_Sprite_	= _Sprite_Ptr;
			this->_Sprite_	= _Sprite_Ptr;
			this->_Shader_	= _Shader_Ptr;
		}

		

		this->_Win_W	= this->_Draw_->g_WindowBounds(1);
		this->_Win_H	= this->_Draw_->g_WindowBounds(2);
		this->xGround	= this->_Draw_->g_WorldBounds(1);
		this->yGround	= this->_Draw_->g_WorldBounds(2);



		this->Ld_All();
	}

	~_Controller_Lobby()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading	Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		//	Loading the background.
		{
			//	Choose what background you want.
			double		xFct = 0.0, yFct = 0.0;
			int			_What_ =STA_::enm_BackGrounds::ChooseYourAdventure;


			this->m_BackGround = new BackGround(		tls::TransformPos_X(this->_Win_W / 2.0, this->xGround)	, 
														tls::TransformPos_Y(this->_Win_H / 2.0, this->yGround)	,
														_What_													);

			this->m_BackGround->ScaleToFit(this->_Sprite_, this->_Draw_);
		}

		//	Loading all the buttons.
		{
			//	Remember that the center of the screen (drawing) for 'x' axis 
			//	is 0.0 and for 'y' axis is half the screen height.
			//	This is not to change so you can work without complications.

			//	Creating the map button.
			{
				this->m_LobbyButtons.push_back(	new BasicButton(0.0, 0.0)	);
				this->m_LobbyButtons[0]->s_ButtonType(STA_::enm_ButtonID::MapButton);

				this->m_LobbyButtons[0]->s_MeasuresPrp(		1, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::MapButton).Third		);
				this->m_LobbyButtons[0]->s_MeasuresPrp(		2, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::MapButton).Fourth		);
			
				this->m_LobbyButtons[0]->s_PositionPrp(		1, tls::TransformPos_X((this->_Draw_->g_WindowBounds(1) - this->m_LobbyButtons[0]->g_MeasuresPrp(1)) / 2.0, this->xGround)	);
				this->m_LobbyButtons[0]->s_PositionPrp(		2, tls::TransformPos_Y((this->_Draw_->g_WindowBounds(2) - this->m_LobbyButtons[0]->g_MeasuresPrp(2)) / 2.0, this->yGround)	);
			}

			//	Creating the arcade button.
			{
				this->m_LobbyButtons.push_back(	new BasicButton(0.0, 0.0)	);
				this->m_LobbyButtons[1]->s_ButtonType(STA_::enm_ButtonID::ArcadeButton);

				this->m_LobbyButtons[1]->s_MeasuresPrp(		1, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::ArcadeButton).Third		);
				this->m_LobbyButtons[1]->s_MeasuresPrp(		2, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::ArcadeButton).Fourth	);
				
				this->m_LobbyButtons[1]->s_PositionPrp(		1, tls::TransformPos_X(	(tls::FixPos_X(this->m_LobbyButtons[0]->g_PositionPrp(1), this->xGround) - this->m_LobbyButtons[1]->g_MeasuresPrp(1)) / 2.0, this->xGround));
				this->m_LobbyButtons[1]->s_PositionPrp(		2, tls::TransformPos_Y(	(this->_Draw_->g_WindowBounds(2) - this->m_LobbyButtons[1]->g_MeasuresPrp(2)) / 2.0, this->yGround)	);
			}
		}
	}
	inline void			Del_All()
	{
		//	Deleting the background.
		{
			tls::Delete(this->m_BackGround);
		}
	}

//	-------------------------------------------
//				Event functions
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{	
		//	Tapping on a lobby button.
		{
			this->_Buttons_Size			= this->m_LobbyButtons.size();
			this->_Button_Collision		= false;



			//	---------------------------------
			//		Updating states of buttons
			//	---------------------------------
			{
				for (	int i = 0;
						i < this->_Buttons_Size;
						++i	)
				{
					this->m_LobbyButtons[i]->s_Is(		Button::enm_Is::IsReleased, false	);
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
						this->_What_Button_			= this->m_LobbyButtons[i];



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
							this->_What_Button_ = this->m_LobbyButtons[i];



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
							if (	(this->_Button_Collision) && (!this->_What_Button_->g_Is(Button::enm_Is::IsPressed))	)
							{
								this->_A_Button_Was_Pressed = true;

								this->_What_Button_->s_Is(		Button::enm_Is::IsPressed, true		);

								this->_What_Button_->s_PositionPrp(2, this->_What_Button_->g_PositionPrp(2) + this->m_ButtonPush);
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
							this->_What_Button_				= this->m_LobbyButtons[i];
					


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
							if (	!this->_What_Button_->g_State()	)
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
									this->_What_Button_->s_PositionPrp(2, this->_What_Button_->g_PositionPrp(2) - this->m_ButtonPush);
									this->_What_Button_->s_Is(Button::enm_Is::IsReleased, true);
								}

								this->_What_Button_->s_Is(	Button::enm_Is::IsPressed, false	);
							}
					
					




							//	Cases for all buttons!
							{
								//	Then, checks if the mouse is being pressed.
								if (	this->_Button_Collision		)
								{
									switch (i)
									{
									case 0:		//	Map.
										this->_Buttons_->ChangeRoom(def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::Map, snd::MyPlayList::Unwind);

										//	Code here what you want to happen.
										{
											//	When changing rooms, change the camera as well.
											this->_Draw_->UseCamera(drw::MyCamera::MapCamera, this->_Buttons_->g_TimeTransition() / 2.0);
										}
										break;

									case 1:		//	Arcade.
										this->_Buttons_->ChangeRoom(def::enm_Defines::_SKIP_THIS, STA_::enm_Rooms::Arcade, snd::MyPlayList::InGame);

										//	Lobby already uses main camera so no need
										//	to change the camera again to main.
									}

								}
								else
								{
									this->_What_Button_->s_State(	Button::enm_State::Normal	);
								}
							}
						}
					}
				}
			}
		}	
	}

//	-------------------------------------------
//					 Functions
//	-------------------------------------------
public:
	inline void			LogicStuff()
	{
		//	Animating the buttons.
		{
			for (	int i = 0;
					i < this->_Buttons_Size;
					++i	)
			{
				this->m_LobbyButtons[i]->Animate();
			}
		}
	}

//	-------------------------------------------
//				Drawing	Functions
//	-------------------------------------------
public:
	inline void			DrawLobby()
	{
		int						_SpriteID_What = spr::enm_At::Maps;
		int						_WhatSprite_ = 0;



		//	Drawing the main background.
		{
			_SpriteID_What			= spr::enm_At::BackGrounds;
			_WhatSprite_			= this->m_BackGround->g_BackGroundID();



			//	Actual Drawing.
			{
				//	Set position to the sprite.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_BackGround->g_PositionPrp(1)	,
																										this->m_BackGround->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_BackGround->g_VisualPrp(1)	,
																									this->m_BackGround->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																										tls::FixPos_Y(	this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



				this->_Draw_->Draw(this->_Sprite_->g_Sprite(_SpriteID_What)->g_Sprites()->at(_WhatSprite_), false);
			}			
		}

		//	Drawing the lobby buttons.
		{
			int					_SpriteID_Buttons			= spr::enm_At::Buttons;
			int					_WhatSprite_				= 0;
			this->_Buttons_Size								= this->m_LobbyButtons.size();



			for (	int i = 0;
					i < this->_Buttons_Size;
					++i	)
			{
				this->_What_Button_		= this->m_LobbyButtons[i];
				_WhatSprite_			= this->_What_Button_->g_SpriteID();



				//	Set position to the sprite.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->_What_Button_->g_PositionPrp(1) + (this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Measures()->at(_WhatSprite_).Third / 2.0)	,
																											this->_What_Button_->g_PositionPrp(2) - (this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Measures()->at(_WhatSprite_).Fourth / 2.0)	);

				//	Then goes the shrinking model.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setScale(	this->_What_Button_->g_VisualPrp(1)	,
																										this->_What_Button_->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(	this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);

				//	Usage of shaders.
				this->_Shader_->s_Uniform_Brightness(	this->_What_Button_->g_Brightness()	);
				


				this->_Draw_->DrawShader(this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_), this->_Shader_->g_Shader(shd::MyShaders::Brightness), !this->_What_Button_->g_IgnoresCam());
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
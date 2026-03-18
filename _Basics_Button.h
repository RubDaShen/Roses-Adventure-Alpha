#pragma once
#include	<vector>
#include	<string>

#include	"thyObject.h"
#include	"thyEffect.h"

#include	"Room.h"
#include	"SoundFactory.h"
#include	"Camera.h"
#include	"SpriteFactory.h"
#include	"DrawFactory.h"
#include	"ShaderFactory.h"



class		Button : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Protected side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
protected:
	int				m_State				= 0;
	int				m_AssignedRoom		= -1;
	int				m_ButtonType		= 0;			//	1 for rectangle, 2 for circle
	int				m_SpriteID			= 0;

	bool			m_IsPressed			= false;
	bool			m_IsReleased		= false;
	bool			m_IgnoresCamera		= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//						Enum!
//	-------------------------------------------
public:
	enum	enm_HitBoxType
	{
		Rectangular		= 1,
		Circular		= 2
	};

	enum	enm_Is
	{
		IsPressed		= 1,
		IsReleased		= 2
	};

	enum	enm_State
	{
		NotInitialized	= 0,
		Normal			= 1,
		MouseOver		= 2,
	};	

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Button(	double a_xP, double a_yP, int _AssignedRoom		,	 
			int _ButtonType, int _Button_SpriteID			, 
			bool _IgnoresCamera = false						) : thyObject(a_xP, a_yP, def::enm_ObjectType::Generic)
	{
		this->m_State			= 1;
		this->m_AssignedRoom	= _AssignedRoom;
		this->m_ButtonType		= _ButtonType;
		this->m_IgnoresCamera	= _IgnoresCamera;
		this->m_SpriteID		= _Button_SpriteID;
	}

	virtual ~Button()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline bool		MouseIsOver(int xP_Mouse, int yP_Mouse)
	{
		
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void		s_State(int _Val)
	{
		this->m_State = _Val;
	}
	inline void		s_Is(int _What, bool _Val)
	{
		switch (_What)
		{
		case Button::enm_Is::IsPressed:
			this->m_IsPressed = _Val;
			break;

		case Button::enm_Is::IsReleased:
			this->m_IsReleased = _Val;
			break;
		}
	}
	inline void		s_ButtonType(int Value)
	{
		this->m_ButtonType	= Value;
		this->m_SpriteID	= Value;
	}

	inline bool		g_Is(int _What)
	{
		switch (	_What	)
		{
		case	Button::enm_Is::IsPressed:
			return		this->m_IsPressed;

		case	Button::enm_Is::IsReleased:
			return		this->m_IsReleased;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline int		g_State()
	{
		return this->m_State;
	}

	inline bool		g_IgnoresCam()
	{
		return		this->m_IgnoresCamera;
	}
	inline int		g_AssignedRoom()
	{
		return this->m_AssignedRoom;
	}
	inline int		g_ButtonType()
	{
		return this->m_ButtonType;
	}
	inline int		g_SpriteID()
	{
		return		this->m_SpriteID;
	}
};
class		PushableButton : public Button
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum	enm_ButtonParts
	{
		BackBase		= 0,
		FrontBase		= 1,
		PushButton		= 2,
		LightningBase	= 3,
		LighningButton	= 4,
	};
	enum	enm_LevelState
	{
		LevelLocked			= 0,
		LevelUnlocked		= 1,
		LevelPassed			= 2,
		LevelSkipped		= 3
	};

	enum	enm_ID
	{
		LevelID			= 1,
		LevelState		= 2,
	};

//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Variables
//	-------------------------------------------
private:
	int				m_LevelID		= 0;
	int				m_LevelState	= 0;

	std::string		m_Name;

//	-------------------------------------------
//			Sprite and animation variables
//	-------------------------------------------
private:
	bool		m_AnimatePush		= false;
	bool		m_PushFlag			= false;

	double		m_PushOffSet		= 0.0;
	double		m_PushTime			= 0.075;
	double		m_PushSpeed			= 0.0;

	int			m_PushValue			= -15;



	int			BackBase_W		= 155,	BackBase_H = 21;
	int			BackBase_y		= -69;
	
	int			FrontBase_W		= 155,	FrontBase_H = 40;
	int			FrontBase_y		= -90;

	int			LightBase_W		= 25,	LightBase_H = 34;
	int			LightBase_x		= 25,	LightBase_y = -95;

	int			LightButton_W	= 40,	LightButton_H = 44;
	int			LightButton_x	= 35,	LightButton_y = -15;






//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	PushableButton(	double _xP, double _yP) : Button(_xP, _yP, def::enm_Defines::_SKIP_THIS, Button::enm_HitBoxType::Rectangular, def::enm_Defines::_SKIP_THIS)
	{
		
	}

	~PushableButton()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			PushMyButton()
	{
		//	PushFlag: 
		//		false:	Ready to get pushed.
		//		true:	Pushback.

		if (	!this->m_PushFlag	)
		{
			this->m_PushSpeed	= this->m_PushValue / (GAME_LOOP_VALUE * this->m_PushTime);
		}
		else
		{
			this->m_PushSpeed	= -this->m_PushValue / (GAME_LOOP_VALUE * this->m_PushTime);
		}



		this->m_AnimatePush		= true;
		this->m_PushFlag		= !this->m_PushFlag;
	}
	inline void			Animate()
	{
		//	Animation for the push effect.
		if (	this->m_AnimatePush		)
		{
			this->m_PushOffSet = this->m_PushOffSet + this->m_PushSpeed;


			//	Fixings...
			{
				if (	this->m_PushOffSet > 0.0	)
				{
					this->m_PushOffSet		= 0.0;
					this->m_AnimatePush		= false;
				}

				if (	this->m_PushOffSet < this->m_PushValue	)
				{
					this->m_PushOffSet		= this->m_PushValue;
					this->m_AnimatePush		= false;	
				}
			}
		}



		//	Timers and time.
		{
			
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void				s_ID(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_LevelID		= _Val;
			this->m_Name		= tls::IntToStr(_Val);
			break;

		case 2:
			this->m_LevelState	= _Val;
			break;
		}
	}
	inline void				s_Name(const std::string _Name)
	{
		this->m_Name = _Name;
	}

	inline int				g_ID(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		this->m_LevelState;

		case 2:
			return		this->m_LevelID;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline std::string		g_Name()
	{
		return		this->m_Name;
	}
	inline int				g_ColorByState(int _What_Part, int _What_Color)
	{
		switch (_What_Part)
		{
		case	enm_ButtonParts::BackBase: 
		case	enm_ButtonParts::FrontBase:		
			switch (this->m_LevelState)
			{
			case	enm_LevelState::LevelLocked:
				switch (_What_Color)
				{
				case	1:
					return		0x91;

				case	2:
					return		0x91;

				case	3:
					return		0x91;
				}

			case	enm_LevelState::LevelUnlocked:
				switch (_What_Color)
				{
				case	1:
					return		0x43;

				case	2:
					return		0x7d;

				case	3:
					return		0xff;
				}
			}
				
		case	enm_ButtonParts::PushButton:				
			switch (this->m_LevelState)
			{
			case	enm_LevelState::LevelLocked:
				switch (_What_Color)
				{
				case	1:
					return		0xff;

				case	2:
					return		0xff;

				case	3:
					return		0xff;
				}

			case	enm_LevelState::LevelUnlocked:
				switch (_What_Color)
				{
				case	1:
					return		0x81;

				case	2:
					return		0xd7;

				case	3:
					return		0xff;
				}
			}
		}

		return		0;
	}

	inline double		g_FinalPosition_BackBase(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP + (this->BackBase_W / 2.0);

		case 2:
			return		this->yP - (this->BackBase_H / 2.0) + this->BackBase_y;
		}
	}
	inline double		g_FinalPosition_FrontBase(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP + (this->FrontBase_W / 2.0);

		case 2:
			return		this->yP - (this->FrontBase_H / 2.0) + this->FrontBase_y;
		}
	}
	inline double		g_FinalPosition_PushButton(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP + (this->_W / 2.0);

		case 2:
			return		this->yP - (this->_H / 2.0) + this->m_PushOffSet;
		}
	}
	inline double		g_FinalPosition_NameTag(int _What, float _FontSize)
	{
		switch (_What)
		{
		case 1:
			return		this->xP - (_FontSize / 2.0) + (this->_W / 2.0);

		case 2:
			return		this->yP - (this->_H / 2.0) + (_FontSize / 2.0) + this->m_PushOffSet;
		}
	}
	inline double		g_FinalPosition_Lightning(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP + (this->LightBase_W / 2.0) + this->LightBase_x;

		case 2:
			return		this->yP - (this->LightBase_H / 2.0) + this->LightBase_y;
		}
	}
	inline double		g_FinalPosition_LightningButton(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xP + (this->LightButton_W / 2.0) + this->LightButton_x;

		case 2:
			return		this->yP - (this->LightButton_H / 2.0) + this->LightButton_y + this->m_PushOffSet;
		}
	}
};
class		BasicButton : public Button
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_GrowingAmount		= 0.10;

	double			m_BrightnessTime	= 0.075;
	double			m_BrightnessAmount	= 0.2;

	double			m_Brightness		= 0.0;
	double			m_BrightnessSpeed	= (this->m_BrightnessAmount / (this->m_BrightnessTime * GAME_LOOP_VALUE));

	double			m_BrightnessTimeBreak	= this->m_BrightnessTime;



//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	BasicButton(	double _xP, double _yP, int _Assigned_Room, int _HitBoxType, int _ButtonSprite_ID, bool _IgnoresCamera = false		) : 
					Button(		_xP, _yP, _Assigned_Room, _HitBoxType, _ButtonSprite_ID, _IgnoresCamera									)
	{
		//	Increasing effect.
		{
			//							Amount?											//	Time?
			this->xFctS = (this->m_GrowingAmount) / (GAME_LOOP_VALUE * this->m_BrightnessTime);
		}
	}
	BasicButton(	double _xP, double _yP	) : Button(_xP, _yP, def::enm_Defines::_SKIP_THIS, Button::enm_HitBoxType::Rectangular, STA_::enm_ButtonID::MapButton)
	{
		//	Increasing effect.
		{
			//							Amount?											//	Time?
			this->xFctS		= (this->m_GrowingAmount) / (GAME_LOOP_VALUE * this->m_BrightnessTime);
		}
	}

	~BasicButton()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	Here is the brightness calculation.
		{
			//	Brightness changing.
			{
				if (	(				(!this->m_IsPressed)					&&
							(this->m_State == Button::enm_State::MouseOver)		)		||	
							(this->m_BrightnessTimeBreak <= this->m_BrightnessTime)		)
				{
					this->m_Brightness			= this->m_Brightness + this->m_BrightnessSpeed;
					this->xFct					= this->xFct + this->xFctS;
				}
				else
				{
					this->m_Brightness			= this->m_Brightness - this->m_BrightnessSpeed;
					this->xFct					= this->xFct - this->xFctS;
				}

				if (	this->m_IsReleased		)
				{
					this->m_BrightnessTimeBreak = 0.0;
				}
			}

			//	Clamp the brightness amount.
			{
				//	For higher values than amount set.
				if (	this->m_Brightness >= this->m_BrightnessAmount	)
				{
					this->m_Brightness	=	this->m_BrightnessAmount;
					this->xFct			=	1.0 + this->m_GrowingAmount;
				}

				//	If value is too low.
				if (	this->m_IsPressed	)
				{
					if (	(this->m_Brightness <= -this->m_BrightnessAmount)		)
					{
						this->m_Brightness	= -this->m_BrightnessAmount;
						this->xFct			= 1.0 - this->m_GrowingAmount;
					}
				}
				else
				{
					if (				(this->m_Brightness <= 0.0)						&&
							(this->m_BrightnessTimeBreak >= this->m_BrightnessTime)		)
					{
						this->m_Brightness		= 0.0;
						this->xFct				= 1.0;
					}
				}
			}

			//	Time goes by...
			{
				this->m_BrightnessTimeBreak = this->m_BrightnessTimeBreak + (1.0 / GAME_LOOP_VALUE);

				this->yFct	= this->xFct;
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double		g_Brightness()
	{
		return		this->m_Brightness;
	}
};



//	------------------------------------------------------------
//	Class Controller_Button
//		>	On the other hand, the controller button is like
//			a manager for all the existing buttons you may have
//			a button of Play, another of Exit, and so on.
// 
//		>	Also, there exist 'rooms'. Rooms are just booleans
//			that implies where the user is at. If the user is
//			on a room, then it's true, else false.
//	------------------------------------------------------------
class	_Controller_Button
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Actual Variables
//	-------------------------------------------
private:
	std::vector<BasicButton*>			m_Buttons;
	std::vector<Room*>					m_Rooms;

	thyEffect*							m_CoolTransition = nullptr;


//	-------------------------------------------
//				Auxiliars and more
//	-------------------------------------------
private:
	BasicButton*		_What_Button_ = nullptr;
	int					_Itr_ = 0;


	double			_x_ = 0.0, _y_ = 0.0;

	int				_Rooms_Size = 0;
	int				_Buttons_Size = 0;

	bool			_Button_Collision = false;

//	-------------------------------------------
//				About buttons
//	-------------------------------------------
private:
	double					m_ButtonPush = 0.0;

//	-------------------------------------------
//			About Transition and effects
//	-------------------------------------------
private:
	double					m_EffTm_CoolTransition = 0.5;

//	-------------------------------------------
//				External Controllers
//	-------------------------------------------
private:
	_Basic_Mouse*			_Mouse_		= nullptr;
	Camera*					_Camera_	= nullptr;
	SoundFactory*			_Sounds_	= nullptr;
	SpriteFactory*			_Sprite_	= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	ShaderFactory*			_Shader_	= nullptr;

	double					xGround = 0.0, yGround = 0.0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//						Enums!
//	-------------------------------------------
public:
	enum	enm_Which_Button
	{
		PlayButton		= 0,
		SettingsButton	= 1,
		BackButton		= 2,
		MapButton		= 3,
	};

	enum	enm_Is
	{
		IsPressed		= 1
	};

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_Button(	_Basic_Mouse* _Mouse_Ptr			, 
						Camera* _Camera_Ptr					,	
						SoundFactory* _Sound_Ptr			,
						SpriteFactory* _Sprite_Ptr			,
						DrawFactory* _Draw_Ptr				,
						ShaderFactory* _Shader_Ptr			)
	{
		this->m_CoolTransition		= new thyEffect();

		this->_Mouse_				= _Mouse_Ptr;
		this->_Camera_				= _Camera_Ptr;
		this->_Sounds_				= _Sound_Ptr;
		this->_Sprite_				= _Sprite_Ptr;
		this->_Draw_				= _Draw_Ptr;
		this->_Shader_				= _Shader_Ptr;

		this->xGround		= this->_Draw_->g_WorldBounds(1);
		this->yGround		= this->_Draw_->g_WorldBounds(2);
	}

	~_Controller_Button()
	{
		//	Deleting all buttons.
		{
			for (	int i = 0; 
					i < this->m_Buttons.size(); 
					++i	)
			{
				delete		this->m_Buttons[i];
				this->m_Buttons.erase(this->m_Buttons.begin() + i);
				--i;
			}
		}

		//	Deleting effects.
		{
			if (this->m_CoolTransition != nullptr)
			{
				delete this->m_CoolTransition;
			}
		}
	}

//	-------------------------------------------
//			Mouse and interactive side
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{
		this->_Buttons_Size			= this->m_Buttons.size();
		this->_Button_Collision		= false;



		//	---------------------------------
		//		Updating states of buttons
		//	---------------------------------
		{
			for (	int i = 0;
					i < this->g_ButtonSz_PerRoom(this->GetCurrentActiveRoom());
					++i	)
			{
				this->_Itr_ = this->g_ButtonAt_Itr_PerRoom(this->GetCurrentActiveRoom(), i);
				this->m_Buttons[this->_Itr_]->s_Is(		Button::enm_Is::IsReleased, false	);
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
						i < this->g_ButtonSz_PerRoom(this->GetCurrentActiveRoom());
						++i	)	
				{
					this->_Itr_				= this->g_ButtonAt_Itr_PerRoom(this->GetCurrentActiveRoom(), i);
					this->_What_Button_		= this->g_Vec_At_Button(this->_Itr_);



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
									this->_x_	= this->_Mouse_->g_Position_Camera(1, 1, this->_Camera_);
									this->_y_	= this->_Mouse_->g_Position_Camera(1, 2, this->_Camera_);
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
						i < this->g_ButtonSz_PerRoom(this->GetCurrentActiveRoom());
						++i	)	
				{			
					//	-------------------------------------------------------------
					//		Easy. Whenever the mouse is pressed, then do stuff.
					//	-------------------------------------------------------------
					if (	(this->_Mouse_->g_Is(1))	)
					{
						this->_Itr_				= this->g_ButtonAt_Itr_PerRoom(this->GetCurrentActiveRoom(), i);
						this->_What_Button_		= this->g_Vec_At_Button(this->_Itr_);



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
								this->_x_	= this->_Mouse_->g_Position_Camera(4, 1, this->_Camera_);
								this->_y_	= this->_Mouse_->g_Position_Camera(4, 2, this->_Camera_);
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

							this->_What_Button_->s_PositionPrp(2, this->_What_Button_->g_PositionPrp(2) + m_ButtonPush);
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
						i < this->g_ButtonSz_PerRoom(this->GetCurrentActiveRoom());
						++i	)	
				{				
					if (	this->_Mouse_->g_Is(2)	)
					{
						this->_Itr_				= this->g_ButtonAt_Itr_PerRoom(this->GetCurrentActiveRoom(), i);
						this->_What_Button_		= this->g_Vec_At_Button(this->_Itr_);



						
				


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
								this->_x_	= this->_Mouse_->g_Position_Camera(3, 1, this->_Camera_);
								this->_y_	= this->_Mouse_->g_Position_Camera(3, 2, this->_Camera_);
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
								this->_What_Button_->s_PositionPrp(2, this->_What_Button_->g_PositionPrp(2) - this->m_ButtonPush);
								this->_What_Button_->s_Is(Button::enm_Is::IsReleased, true);
							}

							this->_What_Button_->s_Is(	Button::enm_Is::IsPressed, false	);
						}

				
				
				

						//	Cases for Menu Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::MainMenu]->g_RoomIsActive()	)
						{
							//	Then, checks if the mouse is being pressed.
							if (	this->_Button_Collision	)
							{
								switch (i)
								{
								case 0:		//	Play button.
									this->ChangeRoom(_Itr_, STA_::enm_Rooms::Lobby, snd::MyPlayList::InGame);
									break;
									
								case 1:		//	Settings button.
									this->ChangeRoom(_Itr_, STA_::enm_Rooms::Level, snd::MyPlayList::PandaEyesColorblind);
									//	snd::MyPlayList::HymnForTheWeekend
									break;
								}

							}
							else
							{
								this->_What_Button_->s_State(1);
							}
						}
				
						//	Cases for Lobby Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::Lobby]->g_RoomIsActive()		)
						{
							//	Then, checks if the mouse is being pressed.
							if (this->_Button_Collision)
							{
								switch (i)
								{
								case 0:		//	Back Button
									this->ChangeRoom(	this->_Itr_, STA_::enm_Rooms::MainMenu, snd::MyPlayList::MainMenu		);

									//	Code here what you want to happen.
									{
										//	When changing rooms, change the camera as well.
										this->_Draw_->UseCamera(drw::MyCamera::MainCamera, this->m_EffTm_CoolTransition / 2.0);
									}
									break;
								}
							}
							else
							{
								this->_What_Button_->s_State(1);
							}
						}

						//	Cases for Map Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::Map]->g_RoomIsActive()			)
						{
							//	Then, checks if the mouse is being pressed.
							if (this->_Button_Collision)
							{
								switch (i)
								{
								case 0:		//	Back Button.
									this->ChangeRoom(this->_Itr_, STA_::enm_Rooms::Lobby, snd::MyPlayList::InGame);

									//	Code here what you want to happen.
									{
										//	When changing rooms, change the camera as well.
										this->_Draw_->UseCamera(drw::MyCamera::MainCamera, this->m_EffTm_CoolTransition / 2.0);
									}

									break;
								}
							}
							else
							{
								this->_What_Button_->s_State(1);
							}
						}

						//	Cases for World Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::World]->g_RoomIsActive()			)
						{
							//	Then, checks if the mouse is being pressed.
							if (this->_Button_Collision)
							{
								switch (i)
								{
								case 0:		//	Back Button.
									this->ChangeRoom(this->_Itr_, STA_::enm_Rooms::Map, snd::MyPlayList::InGame);

									//	Code here what you want to happen.
									{
										//	When changing rooms, change the camera as well.
										this->_Draw_->UseCamera(drw::MyCamera::MapCamera, this->m_EffTm_CoolTransition / 2.0);
									}

									break;
								}
							}
							else
							{
								this->_What_Button_->s_State(1);
							}
						}

						//	Cases for Level Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::Level]->g_RoomIsActive()			)
						{
							//	Then, checks if the mouse is being pressed.
							if (this->_Button_Collision)
							{
								switch (i)
								{
								case 0:		//	Back Button.
									this->ChangeRoom(this->_Itr_, STA_::enm_Rooms::MainMenu, snd::MyPlayList::MainMenu);

									//	Code here what you want to happen.
									{
										//	When changing rooms, change the camera as well.
										this->_Draw_->UseCamera(drw::MyCamera::MainCamera, this->m_EffTm_CoolTransition / 2.0);
									}

									break;
								}
							}
							else
							{
								this->_What_Button_->s_State(1);
							}
						}

						//	Cases for Arcade Buttons !
						if (	this->m_Rooms[STA_::enm_Rooms::Arcade]->g_RoomIsActive()			)
						{
							//	Then, checks if the mouse is being pressed.
							if (this->_Button_Collision)
							{
								switch (i)
								{
								case 0:		//	Back Button.
									this->ChangeRoom(this->_Itr_, STA_::enm_Rooms::Lobby, snd::MyPlayList::InGame);

									//	Changing the camera back to Main is redundant since
									//	Arcade already uses this camera.

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

//	-------------------------------------------
//				Loading functions
//	-------------------------------------------
public:
	inline void			Ld_Rooms()
	{
		//	Creating the rooms.
		{
			//	Pushing all the values.
			for (	int i = 0; 
					i < STA_::enm_Rooms::Rooms_Size;
					++i	)
			{	
				this->m_Rooms.push_back(	new Room(i)	);
			}

			//	When finished, set to logo loading...
			m_Rooms[1]->s_RoomActive(true);
		}	
	}
	inline void			Ld_Buttons()
	{
		//	--------------------------------------------------------
		//		To be clear...	
		//			1 means it is a rectangular button.	And
		//			2 means that it is a circular button.
		//		All of that just for collision context.
		//						-> Not complicated :D
		//	--------------------------------------------------------


		//	Creating the play button.
		{
			this->m_Buttons.push_back(	new BasicButton(0.0, 0.0, 3, 1, STA_::enm_ButtonID::PlayButton)	);

			this->m_Buttons[0]->s_MeasuresPrp(1, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::PlayButton).Third);
			this->m_Buttons[0]->s_MeasuresPrp(2, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::PlayButton).Fourth);

			this->m_Buttons[0]->s_PositionPrp(1, tls::TransformPos_X(	(this->_Draw_->g_WindowBounds(1) - this->m_Buttons[0]->g_MeasuresPrp(1)) / 2.0, this->xGround)	);
			this->m_Buttons[0]->s_PositionPrp(2, tls::TransformPos_Y(	(this->_Draw_->g_WindowBounds(2) - this->m_Buttons[0]->g_MeasuresPrp(2)) / 2.0, this->yGround)	);
		}

		//	Creating the settings button.
		{
			this->m_Buttons.push_back(	new BasicButton(0.0, 0.0, 3, 1, STA_::enm_ButtonID::SettingsButton)	);

			this->m_Buttons[1]->s_MeasuresPrp(1, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::SettingsButton).Third);
			this->m_Buttons[1]->s_MeasuresPrp(2, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::SettingsButton).Fourth);
		
			this->m_Buttons[1]->s_PositionPrp(1, tls::TransformPos_X(	(this->_Draw_->g_WindowBounds(1) - this->m_Buttons[1]->g_MeasuresPrp(1)) / 2.0, this->xGround)				);
			this->m_Buttons[1]->s_PositionPrp(2, tls::TransformPos_Y(	(this->_Draw_->g_WindowBounds(2) - this->m_Buttons[1]->g_MeasuresPrp(2)) / 2.0, this->yGround)	- 100.0		);
		}

		//	Creating the back button.
		{
			this->m_Buttons.push_back(	new BasicButton(700.0, 210.0, 4, 2, STA_::enm_ButtonID::BackButton, true)	);

			this->m_Buttons[2]->s_MeasuresPrp(3, this->_Sprite_->g_Sprite(spr::enm_At::Buttons)->g_Measures()->at(STA_::enm_ButtonID::BackButton).Third / 2.0);
		
			this->m_Buttons[2]->s_PositionPrp(1, tls::TransformPos_X(	tls::CenterObjTo(4, this->_Draw_->g_WindowBounds(1)							, 
																							this->m_Buttons[2]->g_MeasuresPrp(3) * 2.0				,		
																							-25.0 * this->_Draw_->GetScale(DrawFactory::Axis::x)	), this->xGround	)		);
			this->m_Buttons[2]->s_PositionPrp(2, tls::TransformPos_Y(	tls::CenterObjTo(4, this->_Draw_->g_WindowBounds(2)							, 
																							this->m_Buttons[2]->g_MeasuresPrp(3) * 2.0				, 
																							-75.0 * this->_Draw_->GetScale(DrawFactory::Axis::y)	), this->yGround	)		);
		}
	}

//	-------------------------------------------
//				 Changing rooms
//	-------------------------------------------
public:
	inline void			ChangeRoom(int _CurrentButton, int _RoomDestination, int _Music = def::enm_Defines::_NOT_INITIALIZED)
	{
		//	Reset button state.
		if (	_CurrentButton != def::enm_Defines::_SKIP_THIS	)
		{
			this->m_Buttons[_CurrentButton]->s_State(2);
		}

		//	Redirect to another room.
		this->IsOnRoomAt(_RoomDestination, true, this->m_EffTm_CoolTransition / 2.0);
		this->m_CoolTransition->Ini_FadeInOut(0, 255, 0, this->m_EffTm_CoolTransition / 2.0, this->m_EffTm_CoolTransition / 2.0);

		//	Settings about the music.
		if (	_Music >= 0	)
		{
			this->_Sounds_->SetMusic(_Music, this->m_EffTm_CoolTransition / 2.0);
		}
		else
		{
			this->_Sounds_->SetMusic(def::enm_Defines::_NOT_INITIALIZED, this->m_EffTm_CoolTransition / 2.0);
		}
	}

//	-------------------------------------------
//				Functional Side
//	-------------------------------------------
public:
	inline void			IsOnRoomAt(const int _atPos, const bool showTransition, const double _Time = 1.0)
	{
		this->_Rooms_Size				= this->m_Rooms.size();
		int					SavedRoom	= 0;


		//	Reseting all rooms and saving that one (current on).
		for (int i = 0; i < this->_Rooms_Size; i++)
		{
			if (	m_Rooms[i]->g_RoomIsActive()	)
			{
				SavedRoom = i;
			}

			m_Rooms[i]->ResetStates();
		}



		//	For the SavedRoom, lets config it!
		{
			m_Rooms[SavedRoom]->s_RoomActive(		true		);
			m_Rooms[SavedRoom]->SetRoomTransition(	((showTransition) ? _Time : 0)		, 
													Room::enm_Command::DeactivateRoom	);
		}

		//	Then, the room we want to enter!
		{
			m_Rooms[_atPos]->SetRoomTransition(		((showTransition) ? _Time : 0		), 
													Room::enm_Command::ActivateRoom		);
		}

		//	Finally, if show the cool transition!
		{
			m_Rooms[1]->s_RoomActive(				((showTransition) ? true : false)	);
			m_Rooms[SavedRoom]->SetRoomTransition(	((showTransition) ? _Time : 0)		, 
													Room::enm_Command::DeactivateRoom	);
		}
	}
	inline int			GetCurrentActiveRoom()
	{
		this->_Rooms_Size = this->m_Rooms.size();



		for (int i = 0; i < this->_Rooms_Size; ++i)
		{
			if ((m_Rooms[i]->g_RoomIsActive()) && (i != 1))
			{
				return i;
			}
		}
	}

	inline void			RoomTransition()
	{
		for (	int i = 0; 
				i < this->m_Rooms.size(); 
				++i	)
		{
			this->m_Rooms[i]->Transition();
		}		
	}

	inline void			TransitionEffectStuff()
	{
		this->m_CoolTransition->FadeIO();

		if (!this->m_CoolTransition->g_FIO(2))
		{
			this->m_Rooms[1]->s_RoomActive(false);
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
				this->m_Buttons[i]->Animate();
			}
		}
	}

//	-------------------------------------------
//				Drawing side
//	-------------------------------------------
public:
	inline void			DrawButtons(int _What_Room)
	{
		//	Drawing the buttons.
		{
			int					_SpriteID_Buttons			= spr::enm_At::Buttons;
			int					_WhatSprite_				= 0;



			for (	int i = 0;
					i < this->g_ButtonSz_PerRoom(_What_Room);
					++i	)
			{
				_What_Button_		=	this->g_Vec_At_Button(	this->g_ButtonAt_Itr_PerRoom(_What_Room, i)	);
				_WhatSprite_		=	_What_Button_->g_SpriteID();



				//	Set position to the sprite.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setPosition(	_What_Button_->g_PositionPrp(1) + (this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Measures()->at(_WhatSprite_).Third / 2.0)	,
																											_What_Button_->g_PositionPrp(2) - (this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Measures()->at(_WhatSprite_).Fourth / 2.0)	);

				//	Then goes the shrinking model.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setScale(	_What_Button_->g_VisualPrp(1)	,
																										_What_Button_->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																											tls::FixPos_Y(	this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);
				//	Usage of shaders.
				this->_Shader_->s_Uniform_Brightness(	this->_What_Button_->g_Brightness()		);




				this->_Draw_->DrawShader(this->_Sprite_->g_Sprite(_SpriteID_Buttons)->g_Sprites()->at(_WhatSprite_), this->_Shader_->g_Shader(shd::MyShaders::Brightness), !_What_Button_->g_IgnoresCam());
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_IsOnRoom(int _Which, bool _Value)
	{
		this->m_Rooms[_Which]->s_RoomActive(_Value);
	}



	inline Room			g_Room(int _Which)
	{
		Room	_Room_Copy = *this->m_Rooms[_Which];
		return	_Room_Copy;
	}
	inline int			g_Room_Size()
	{
		return this->m_Rooms.size();
	}
	inline bool			g_IsOnRoom(int _Which)
	{
		return this->m_Rooms[_Which]->g_RoomIsActive();
	}
	inline thyEffect*	g_CoolTransition()
	{
		return		this->m_CoolTransition;
	}
	inline double		g_TimeTransition()
	{
		return		this->m_EffTm_CoolTransition;
	}


	inline BasicButton*		g_Vec_At_Button(int _What)
	{
		return		this->m_Buttons[_What];
	}
	inline int				g_ButtonSz_PerRoom(int _WhatRoom)
	{
		switch (_WhatRoom)
		{
		case STA_::enm_Rooms::MainMenu:
			return 2;
			break;

		case STA_::enm_Rooms::Lobby:
			return 1;
			break;

		case STA_::enm_Rooms::Map:
			return 1;
			break;

		case STA_::enm_Rooms::World:
			return 1;
			break;

		case STA_::enm_Rooms::Level:
			return 1;
			break;

		case STA_::enm_Rooms::Arcade:
			return 1;
			break;

		default:
			return 0;
			break;
		}
	}
	inline int				g_ButtonAt_Itr_PerRoom(int _WhatRoom, int _Itr)
	{
		switch (_WhatRoom)
		{
		case STA_::enm_Rooms::MainMenu:
			switch (_Itr)
			{
			case 0:
				return 0;

			case 1:
				return 1;
			}

			break;

		case STA_::enm_Rooms::Lobby:
			switch (_Itr)
			{
			case 0:
				return		_Controller_Button::enm_Which_Button::BackButton;
			}

			break;

		case STA_::enm_Rooms::Map:
			switch (_Itr)
			{
			case 0:
				return		_Controller_Button::enm_Which_Button::BackButton;
			}

			break;

		case STA_::enm_Rooms::World:
			switch (_Itr)
			{
			case 0:
				return		_Controller_Button::enm_Which_Button::BackButton;
			}

			break;

		case STA_::enm_Rooms::Level:
			switch (_Itr)
			{
			case 0:
				return		_Controller_Button::enm_Which_Button::BackButton;
			}

			break;

		case STA_::enm_Rooms::Arcade:
			switch (_Itr)
			{
			case 0:
				return		_Controller_Button::enm_Which_Button::BackButton;
			}

			break;

		default:
			return 0;
			break;
		}
	}
};
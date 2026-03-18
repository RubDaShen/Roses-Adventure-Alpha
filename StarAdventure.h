#pragma once

#include		"Includes.h"




//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//			Commentary side.
//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	This is the core class, the main class.
//	It all works with a single function.
//	The function StartAdventure().

class	StarAdventure
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//		[*] Other games (Idk how to call it)
//	-------------------------------------------
private:
	Funking*			m_FNF			= nullptr;

	bool				m_EnableFNF		= false;

//	-------------------------------------------
//		[*] External variables and linkers
//	-------------------------------------------
private:
	DrawFactory*		_Draw_		= nullptr;
	SoundFactory*		_Sound_		= nullptr;
	SpriteFactory*		_Sprites_	= nullptr;	
	ShaderFactory*		_Shader_	= nullptr;
	TextFactory*		_Text_		= nullptr;

	_Basic_Mouse*		_Mouse_		= nullptr;
	_Basic_KeyBoard*	_KeyBoard_	= nullptr;
	_Controller_Logic*	_Logic_		= nullptr;

	Camera*				_Camera_	= nullptr;
	OnScreen*			_OnScreen_	= nullptr;

//	-------------------------------------------
//			[*]	NetWork And Handlers
//	-------------------------------------------
private:
	sql::SQLConnector*		_SQLConnection_		= nullptr;

//	-------------------------------------------
//				[*] Statistics
//	-------------------------------------------
private:
	_Controller_Statistics*			m_Statistics	= nullptr;

//	-------------------------------------------
//			[*] Handling events and more
//	-------------------------------------------
private:
	sf::Event*			m_Event		= nullptr;
	sf::Clock*			m_Clock		= nullptr;
	sf::Time*			m_Time		= nullptr;

	double				xMouseMove = 0.0,		yMouseMove = 0.0;
	double				xMousePressed = 0.0,	yMousePressed = 0.0;
	double				xMouseReleased = 0.0,	yMouseReleased = 0.0;

	double				_Win_W = 0.0, _Win_H = 0.0, xGround = 0.0, yGround = 0.0;

//	-------------------------------------------
//			[*] Timing and Frames
//	-------------------------------------------
private:
	double				nowTm_Graphics	= 0,	ftrTm_Graphics	= 0,	tckVal_Graphics = GAME_LOOP_LOGIC;
	double				nowTm_Logic		= 0,	ftrTm_Logic		= 0,	tckVal_Logic	= GAME_LOOP_LOGIC;

	int					LpCnt_Graphics	= 0,	LpCnt_Logic		= 0;

//	-------------------------------------------
//				[0]	Controllers
//	-------------------------------------------
private:
	_Controller_Button*				m_Buttons			= nullptr;
	_Controller_Map*				m_Map				= nullptr;
	_Controller_World*				m_World				= nullptr;
	_Controller_LevelTransition*	m_LevelTransition	= nullptr;	
	_Controller_BackGround*			m_BackGrounds		= nullptr;
	_Controller_Lobby*				m_Lobby				= nullptr;
	_Controller_User*				m_User				= nullptr;
	_Controller_Arcade*				m_Arcade			= nullptr;

//	-------------------------------------------
//				[1]	Other Variables
//	-------------------------------------------
private:
	Board*							_Board_Pointer		= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	StarAdventure(	DrawFactory* _Draw_Ptr, OnScreen* _OnScreen_Ptr				,
					_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _KeyBoard_Ptr	,
					SoundFactory* _Sound_Ptr, SpriteFactory* _Sprite_Ptr		,
					Camera* _Camera_Ptr, ShaderFactory* _Shader_Ptr				,
					TextFactory* _Text_Ptr, sql::SQLConnector* _SQL_Ptr			,
					_Controller_Logic* _Logic_Ptr								)
	{
		this->_Draw_			= _Draw_Ptr;
		this->_OnScreen_		= _OnScreen_Ptr;
		this->_Mouse_			= _Mouse_Ptr;
		this->_KeyBoard_		= _KeyBoard_Ptr;
		this->_Sound_			= _Sound_Ptr;
		this->_Sprites_			= _Sprite_Ptr;
		this->_Camera_			= _Camera_Ptr;
		this->_Shader_			= _Shader_Ptr;
		this->_Text_			= _Text_Ptr;
		this->_SQLConnection_	= _SQL_Ptr;
		this->_Logic_			= _Logic_Ptr;

		this->UpdateMeasures();



		this->Ld_Networking();
		this->Ld_Linkers();
		this->Ld_Handlers();
		this->Ld_Statistics();
		this->Ld_Controllers();
		this->Ld_FNF();
	}

	~StarAdventure()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_Linkers()
	{
		//	Link the camera with _Draw_.
		{
			this->_Draw_->LinkCamera(this->_Camera_, 0);
			this->_Draw_->UseCamera(drw::MyCamera::MainCamera);
		}
	}
	inline void			Ld_Handlers()
	{
		//	Loading all the events related.
		{
			this->m_Event = new sf::Event();
		}

		//	Loading all the time variables.
		{
			this->m_Clock = new sf::Clock();
		}

		//	Loading all the time variables.
		{
			this->m_Time = new sf::Time();
		}
	}
	inline void			Ld_Statistics()
	{
		//	Creating statistics.
		{
			this->m_Statistics = new _Controller_Statistics(	this->_Draw_, this->_Text_	);
		}
	}
	inline void			Ld_Controllers()
	{
		//	None of this pointers uses null-pointed objects.
		//	_Mouse_, _Camera_, _Draw_, _Sound_, etc.,
		//	all of them are already created and instanced.

		//	Creating the controller of buttons.
		{
			this->m_Buttons = new _Controller_Button(	this->_Mouse_, this->_Camera_	,
														this->_Sound_, this->_Sprites_	,
														this->_Draw_, this->_Shader_	);

			this->m_Buttons->Ld_Buttons();
			this->m_Buttons->Ld_Rooms();
		}

		this->m_BackGrounds = new _Controller_BackGround(	this->_Win_W, this->_Win_H		,
															this->xGround, this->yGround	,
															this->_Sprites_, this->_Draw_	);

		this->m_World = new _Controller_World(this->_Mouse_, this->_KeyBoard_, this->_Sprites_, this->_Draw_, this->m_Buttons, this->_Text_, this->_Shader_, this->_Sound_, this->_SQLConnection_, this->_Logic_);

		this->m_Map = new _Controller_Map(this->_Mouse_, this->_Sprites_, this->_Draw_, this->m_Buttons, this->m_World, this->_Text_);

		this->m_LevelTransition = new _Controller_LevelTransition(	this->_Mouse_, this->_KeyBoard_		,
																	this->_Sprites_, this->_Draw_		,
																	this->m_Buttons						);

		this->m_Lobby = new _Controller_Lobby(	this->_Mouse_, this->_Sprites_, this->_Draw_	,
												this->_Shader_, this->m_Buttons					);

		this->m_User	= new _Controller_User(		this->_Draw_, this->_Sprites_, this->_Text_, this->_SQLConnection_		);
		this->m_Arcade	= new _Controller_Arcade(	this->_Draw_, this->_Sprites_	);
		
	}
	inline void			Ld_Networking()
	{
		
	}
	inline void			Ld_FNF()
	{
		//	Creating FNF.
		{
			this->m_FNF = new Funking(	this->_KeyBoard_, this->_Sound_, this->_Camera_	,
										tls::Vec2<double>(	this->_Win_W, this->_Win_H	)	);
		}
	}

	inline void			Del_All()
	{
		//	Deleting handlers.
		{
			tls::Delete(this->m_Event);
			tls::Delete(this->m_Clock);
			tls::Delete(this->m_Time);
		}

		//	Deleting all controllers.
		{
			tls::Delete(this->m_Buttons);
			tls::Delete(this->m_Map);
			tls::Delete(this->m_World);
			tls::Delete(this->m_Lobby);
		}

		//	Deleting statistics.
		{
			tls::Delete(this->m_Statistics);
		}

		//	Deleting all stuff related to levels.
		{
			tls::Delete(this->_Board_Pointer);
		}

		//	Deleting FNF (Sounds weird ;-;).
		{
			tls::Delete(this->m_FNF);
		}

		tls::Delete(this->m_User);
		tls::Delete(this->m_Arcade);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			StartAdventure()
	{
		//	Main Loop, Main function, Main Everything !
		//	Can also use an if instead, that way the thread won't be locked
		//	on a single while loop.
		while (		this->_Draw_->g_Window()->isOpen()		)
		{
			//	---------------------------------------------------
			//		While (n) :		Use it for all window events
			//	---------------------------------------------------
			while (	this->_Draw_->g_Window()->pollEvent(*this->m_Event)	)
			{
				//	--------------------
				//		Window side !
				//	--------------------

				//	Event::Closed	:  Means when the window is closed.
				if (this->m_Event->type == sf::Event::Closed)
				{
					this->_Draw_->g_Window()->close();
				}

				//	Event::Resized	:  Means when window is being resized.
				if (this->m_Event->type == sf::Event::Resized)
				{
					this->_Draw_->ResizeEvent(	this->m_Event	);
				}



				//	-------------------
				//		Mouse Side !
				//	-------------------

				//	Event::MouseMoved			:	Mouse is being moved.
				if (this->m_Event->type == sf::Event::MouseMoved)
				{
					this->xMouseMove = tls::TransformPos_X(		this->_Draw_->Transform(1, this->m_Event->mouseMove.x), this->xGround	);
					this->yMouseMove = tls::TransformPos_Y(		this->_Draw_->Transform(2, this->m_Event->mouseMove.y), this->yGround	);

					//	Mouse States for ButtonPressed.
					{
						this->_Mouse_->s_Position(0, 1, this->m_Event->mouseMove.x);
						this->_Mouse_->s_Position(0, 2, this->m_Event->mouseMove.y);

						this->_Mouse_->s_Position(1, 1, this->xMouseMove);
						this->_Mouse_->s_Position(1, 2, this->yMouseMove);



						//	The pressed event by itself is only triggered once.
						//	Hence, to ensure the correct values of MousePressed
						//	this if will update it anytime the mouse is being pressed.
						if (	this->_Mouse_->g_Is(1)		)
						{
							this->_Mouse_->s_Position(2, 1, this->xMouseMove);
							this->_Mouse_->s_Position(2, 2, this->yMouseMove);

							this->_Mouse_->s_Is(1, true);
							this->_Mouse_->s_Is(2, false);
						}
					}					
				}

				//	Event::MouseButtonPressed	:	Mouse is pressed.
				if (this->m_Event->type == sf::Event::MouseButtonPressed)
				{
					this->xMousePressed = tls::TransformPos_X(	this->_Draw_->Transform(1, this->m_Event->mouseButton.x) , this->xGround);
					this->yMousePressed = tls::TransformPos_Y(	this->_Draw_->Transform(2, this->m_Event->mouseButton.y) , this->yGround);

					//	Mouse States for ButtonPressed.
					{
						//	Pressed previosly!
						this->_Mouse_->s_Position(4, 1, this->xMousePressed);
						this->_Mouse_->s_Position(4, 2, this->yMousePressed);

						//	Actual pressing value! (Allows drag click)
						this->_Mouse_->s_Position(2, 1, this->xMousePressed);
						this->_Mouse_->s_Position(2, 2, this->yMousePressed);

						//	Update States!		(Continuous pressing)
						this->_Mouse_->s_Is(1, true);
						this->_Mouse_->s_Is(2, false);

						//	Update States!		(Single pressing)
						this->_Mouse_->s_Is(3, true);
					}
				}

				//	Event::MouseButtonReleased	:	Mouse is released.
				if (this->m_Event->type == sf::Event::MouseButtonReleased)
				{
					this->xMouseReleased = tls::TransformPos_X(	this->_Draw_->Transform(1, this->m_Event->mouseButton.x), this->xGround);
					this->yMouseReleased = tls::TransformPos_Y( this->_Draw_->Transform(2, this->m_Event->mouseButton.y), this->yGround);

					//	Mouse States for ButtonReleased.
					{
						this->_Mouse_->s_Position(3, 1, this->xMouseReleased);
						this->_Mouse_->s_Position(3, 2, this->yMouseReleased);

						this->_Mouse_->s_Is(1, false);
						this->_Mouse_->s_Is(2, true);
					}	
				}



				//	-----------------------
				//		Keyboard Side !
				//	-----------------------

				//	Event::KeyPressed	:	A key is pressed.
				if (this->m_Event->type == sf::Event::KeyPressed)
				{		
					//	All abecedary keys !
					{
						if (this->m_Event->key.code == sf::Keyboard::D)
						{
							this->_KeyBoard_->g_Key(kyb::D)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::C)
						{
							this->_KeyBoard_->g_Key(kyb::C)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::F)
						{
							this->_KeyBoard_->g_Key(kyb::F)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::J)
						{
							this->_KeyBoard_->g_Key(kyb::J)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::K)
						{
							this->_KeyBoard_->g_Key(kyb::K)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::L)
						{
							this->_KeyBoard_->g_Key(kyb::L)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::R)
						{
							this->_KeyBoard_->g_Key(kyb::R)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::W)
						{
							this->_KeyBoard_->g_Key(kyb::W)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::P)
						{
							this->_KeyBoard_->g_Key(kyb::P)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::T)
						{
							this->_KeyBoard_->g_Key(kyb::T)->s_Is(1, true);
						}
					}

					//	Big ones !
					{
						if (this->m_Event->key.code == sf::Keyboard::Space)
						{
							this->_KeyBoard_->g_Key(kyb::_Space_)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Enter)
						{
							this->_KeyBoard_->g_Key(kyb::Enter)->s_Is(1, true);
						}
					}

					//	Math and operations !
					{
						if (this->m_Event->key.code == sf::Keyboard::Add)
						{
							this->_KeyBoard_->g_Key(kyb::Add)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Subtract)
						{
							this->_KeyBoard_->g_Key(kyb::Subtract)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Multiply)
						{
							this->_KeyBoard_->g_Key(kyb::Multiply)->s_Is(1, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Divide)
						{
							this->_KeyBoard_->g_Key(kyb::Divide)->s_Is(1, true);
						}
					}
				}

				//	Event::KeyPressed	:	A key is released.
				if (this->m_Event->type == sf::Event::KeyReleased)
				{
					//	All abecedary keys !
					{
						if (this->m_Event->key.code == sf::Keyboard::D)
						{
							this->_KeyBoard_->g_Key(kyb::D)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::C)
						{
							this->_KeyBoard_->g_Key(kyb::C)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::F)
						{
							this->_KeyBoard_->g_Key(kyb::F)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::J)
						{
							this->_KeyBoard_->g_Key(kyb::J)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::K)
						{
							this->_KeyBoard_->g_Key(kyb::K)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::L)
						{
							this->_KeyBoard_->g_Key(kyb::L)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::R)
						{
							this->_KeyBoard_->g_Key(kyb::R)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::W)
						{
							this->_KeyBoard_->g_Key(kyb::W)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::P)
						{
							this->_KeyBoard_->g_Key(kyb::P)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::T)
						{
							this->_KeyBoard_->g_Key(kyb::T)->s_Is(2, true);
						}
					}

					//	Big ones !
					{
						if (this->m_Event->key.code == sf::Keyboard::Space)
						{
							this->_KeyBoard_->g_Key(kyb::_Space_)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Enter)
						{
							this->_KeyBoard_->g_Key(kyb::Enter)->s_Is(2, true);
						}
					}

					//	Math and operations !
					{
						if (this->m_Event->key.code == sf::Keyboard::Add)
						{
							this->_KeyBoard_->g_Key(kyb::Add)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Subtract)
						{
							this->_KeyBoard_->g_Key(kyb::Subtract)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Multiply)
						{
							this->_KeyBoard_->g_Key(kyb::Multiply)->s_Is(2, true);
						}
						if (this->m_Event->key.code == sf::Keyboard::Divide)
						{
							this->_KeyBoard_->g_Key(kyb::Divide)->s_Is(2, true);
						}
					}
				}
			}

			//	------------------------------------------------
			//		Time (1) :		Use it for loop timers.
			//	------------------------------------------------
			*this->m_Time = this->m_Clock->getElapsedTime();




			
			//	---------------------------------------
			//		Timers (~) :	Logic and more.
			//	---------------------------------------

			//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
			//				Star Adventure
			//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

			//	Logic			:   The brain of the game.
			if (	(this->m_Time->asMicroseconds() / 1000.0) >= this->ftrTm_Logic	)
			{
				this->nowTm_Logic = this->m_Time->asMicroseconds();



				//	..::	Code	::..
				
				
				//	Logic part.
				{
					_Logic_->LogicDis();
				}	
				//	OnScreen.
				{
					this->_OnScreen_->GetSlowMotion_FlashBang()->SetAnimation(	this->_Logic_->GetFlagForFlashBang()	);
				}
				//	Draw part.
				{
					this->_Draw_->LogicDis();
					this->_Draw_->SetVintageFilterValues(	1, this->_Logic_->GetValues(1)	);
				}
				//	Sound part.
				{
					this->_Sound_->LogicDis();
				}
				//	Buttons and rooms part...
				{
					//	Buttons part.
					this->m_Buttons->MouseStuff();
					this->m_Buttons->LogicStuff();

					//	Rooms config. 
					this->m_Buttons->RoomTransition();
				}			
				//	Statistics part.
				{
					this->m_Statistics->DoStatistics();
				}
				//	User.
				{
					this->m_User->LogicDis(_Controller_User::enm_Logic::_Queries);
					this->m_User->LogicDis(_Controller_User::enm_Logic::_UserProperties);
				}
				//	Other stuff.
				{
					this->_Board_Pointer	= this->m_World->g_Board();
				}




				//	IsOnRoom[1]:	Cool Transition.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::Transition	))
				{
					this->m_Buttons->TransitionEffectStuff();
				}

				//	IsOnRoom[2]:	Logo animation.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::LogoPart		))
				{
					//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
					//		The only case to ever exist (by now) in the logo animation
					//		is the logo ended event to proceed to the other rooms.
					//				If there are more events, just code it!
					//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
					if (	this->_OnScreen_->g_Ctrl_Logos()->g_Vec_Logos().at(0)->g_AnimationEnd()	)
					{
						this->m_Buttons->IsOnRoomAt(3, true, 0.0);
						this->_Sound_->SetMusic(snd::MyPlayList::MainMenu, 0.0);
					}
				}

				//	IsOnRoom[3]:	Main Menu.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::MainMenu		))
				{
					
				}

				//	IsOnRoom[4]:	Lobby.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Lobby	))
				{
					this->m_Lobby->MouseStuff();
					this->m_Lobby->LogicStuff();
				}

				//	IsOnRoom[5]:	Map.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Map		))
				{
					//	All about map stuff.
					{
						this->m_Map->MouseStuff();

						this->m_Map->Animate();
					}

					this->m_User->LogicDis(	_Controller_User::enm_Logic::_Livicon	);
				}

				//	IsOnRoom[6]:	World.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::World	))
				{
					//	All about world stuff.
					{
						this->m_World->EventsStuff();
						this->m_World->LogicNow();
					}

					this->m_User->LogicDis(	_Controller_User::enm_Logic::_Livicon	);
				}

				//	IsOnRoom[7]:	Level transition.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::LevelTransition	))
				{
					//	All logic possible.
					this->m_LevelTransition->LogicStuff();
				}

				//	IsOnRoom[8]:	A level room.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Level	))
				{
					//	----------------------------------
					//			Auxiliar Part !
					//	----------------------------------	
	
					//	Board logic.
					this->_Board_Pointer->KeyBoardStuff();
					this->_Board_Pointer->MouseStuff();
					this->_Board_Pointer->SlowMotionFlashBang(	this->_Logic_->GetFlagForFlashBang(true)	);

					if (!this->_Board_Pointer->g_FreezeBrain())
					{											
						this->_Board_Pointer->OptimizeAndReduce();
						this->_Board_Pointer->DoSpawn();


						this->_Board_Pointer->SwapCandies();


						this->_Board_Pointer->IandJ();
						this->_Board_Pointer->SortItOut();
						this->_Board_Pointer->UpdateBoardState();
			
						this->_Board_Pointer->OptimizeAndReduce();
						this->_Board_Pointer->DoCandies();
						this->_Board_Pointer->SideWays();
						this->_Board_Pointer->MatchSequence();

						this->_Board_Pointer->UpdateBoardState();
						this->_Board_Pointer->Matches();
						
						this->_Board_Pointer->OptimizeAndReduce();
						this->_Board_Pointer->UpdateBoardState();
						this->_Board_Pointer->CrushingTime();

						this->_Board_Pointer->Clocks();
						this->_Board_Pointer->OptimizeAndReduce();
						this->_Board_Pointer->UpdateBoardState();
						this->_Board_Pointer->SpecialCandies();
						
						this->_Board_Pointer->OptimizeAndReduce();
						this->_Board_Pointer->UpdateBoardState();					
						this->_Board_Pointer->Animator();
					}
				}

				//	IsOnRoom[9]:	Arcade.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Arcade	))
				{
					
				}



				this->_OnScreen_->LogicDis();
				this->_KeyBoard_->UpdateStates();
				this->_Mouse_->ResetStates();
				this->_Sound_->IniCnt_PlayMusic();
				this->_Camera_->Action();



				//	..::	Timer	::..

				ftrTm_Logic = (this->m_Time->asMicroseconds() / 1000.0) + tckVal_Logic - ((this->m_Time->asMicroseconds() - nowTm_Logic) / 1000.0);
			}





			//	---------------------------------------
			//		Rendering Graphics : Images !
			//	---------------------------------------
			if (	(this->m_Time->asMicroseconds() / 1000.0) >= this->ftrTm_Graphics	)
			{
				this->nowTm_Graphics = this->m_Time->asMicroseconds();



				//	..::	Code	::..

				//	Before rendering something, let's set the view.
				{
					this->_Draw_->UseView();
				}



				//	IsOnRoom[2]:	Logo.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::LogoPart		))
				{
					//	Drawing the black cover.
					{
						BackGround*				_MyBg_					= this->m_BackGrounds->g_Vec_At_BGs(STA_::enm_BackGrounds::BlankScene);

						int						_SpriteID_BackGrounds	= spr::enm_At::BackGrounds;
						int						_WhatSprite_			= _MyBg_->g_BackGroundID();



						//	Actual Drawing.
						{
							//	Set position to the sprite.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	_MyBg_->g_PositionPrp(1)	,
																													_MyBg_->g_PositionPrp(2) 	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setScale(	_MyBg_->g_VisualPrp(1)	,
																													_MyBg_->g_VisualPrp(2)	);
							
							//	Applying color properties.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	0, 0, 0, 255	)	);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																													tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



							this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_));
						}
					}

					//	Drawing the logo.
					{
						FancyLogo*					_MyLogo_				= this->_OnScreen_->g_Ctrl_Logos()->g_Vec_Logos().at(0);

						int							_SpriteID_OnScreen		= spr::enm_At::OnScreen;
						int							_WhatSprite_			= 2;



						//	Actual drawing.
						{
							//	Set position to the sprite.
							_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setPosition(	_MyLogo_->g_PositionPrp(1)	,
																													_MyLogo_->g_PositionPrp(2) 	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setScale(		_MyLogo_->g_VisualPrp(1)	,
																													_MyLogo_->g_VisualPrp(2)	);

							//	Applying color properties.
							_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_MyLogo_->g_ColorPrp(1)	,
																															_MyLogo_->g_ColorPrp(2)	,
																															_MyLogo_->g_ColorPrp(3)	,
																															_MyLogo_->g_ColorPrp(4)	)	);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																													tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



							this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_));
						}
					}
				}

				//	IsOnRoom[3]:	Main Menu.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::MainMenu		))
				{
					this->m_BackGrounds->DrawBackGround(STA_::enm_Rooms::MainMenu);
					this->m_Buttons->DrawButtons(	STA_::enm_Rooms::MainMenu	);

					this->m_User->Draw(		_Controller_User::enm_Draw::_Icon		);
					this->m_User->Draw(		_Controller_User::enm_Draw::_Username	);
				}

				//	IsOnRoom[4]:	Lobby.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Lobby	))
				{
					this->m_Lobby->DrawLobby();

					this->m_Buttons->DrawButtons(	STA_::enm_Rooms::Lobby	);
				}

				//	IsOnRoom[5]:	Map.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Map		))
				{
					this->m_Map->DrawMap();
					this->m_User->Draw(_Controller_User::enm_Draw::_LiviconHUD);
					this->m_Buttons->DrawButtons(	STA_::enm_Rooms::Map	);
				}

				//	IsOnRoom[6]:	World.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::World	))
				{
					this->m_World->DrawWorld();
					this->m_User->Draw(_Controller_User::enm_Draw::_LiviconHUD);
					this->m_Buttons->DrawButtons(	STA_::enm_Rooms::World	);
				}

				//	IsOnRoom[7]:	Level transition.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::LevelTransition	))
				{
					
				}

				//	IsOnRoom[8]:	A level room.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Level	))
				{
					this->DrawLevel();

					this->m_Buttons->DrawButtons(STA_::enm_Rooms::Level);
					this->_OnScreen_->Draw(		OnScreen::enm_Draw::_SlowMotion_FlashBang	);
				}

				//	IsOnRoom[9]:	Arcade.
				if (this->m_Buttons->g_IsOnRoom(		STA_::enm_Rooms::Arcade	))
				{
					this->m_Arcade->DrawArcade();
					this->m_Buttons->DrawButtons(	STA_::enm_Rooms::Arcade		);
				}





				//	Before rendering something, let's reset the view.
				{
					this->_Draw_->ResetView();
				}

				//	Smooth Layer.
				{
					//	Smooth Layer !
					{
						if (	!this->m_Buttons->g_IsOnRoom(2)		)
						{
							BackGround*							_Layer_				= this->_OnScreen_->g_Ctrl_LightBricks()->g_Vec_LightLayers().at(0);

							int									_SpriteID_OnScreen	= spr::enm_At::OnScreen;
							int									_WhatSprite_		= 3;



							//	Actual drawing.
							{
								//	Set position to the sprite.
								_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setPosition(	_Layer_->g_PositionPrp(1)	,
																														_Layer_->g_PositionPrp(2)	);

								//	Applying color properties.
								_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_Layer_->g_ColorPrp(1)	,
																																_Layer_->g_ColorPrp(2)	,
																																_Layer_->g_ColorPrp(3)	,
																																_Layer_->g_ColorPrp(4)	)	);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setScale(		_Layer_->g_VisualPrp(1)	,
																														_Layer_->g_VisualPrp(2)	);

								//	Fix position to properly render on screen.
								_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																														tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



								this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_OnScreen)->g_Sprites()->at(_WhatSprite_), false);
							}
						}
					}
				}

				//	IsOnRoom[1]:	Cool Transition.
				if (this->m_Buttons->g_IsOnRoom(	STA_::enm_Rooms::Transition))
				{
					//	Drawing the black background.
					{
						BackGround*				_MyBg_					= this->m_BackGrounds->g_Vec_At_BGs(0);

						int						_SpriteID_BackGrounds	= spr::enm_At::BackGrounds;
						int						_WhatSprite_			= _MyBg_->g_BackGroundID();



						//	Actual Drawing.
						{
							//	Set position to the sprite.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	_MyBg_->g_PositionPrp(1)	,
																													_MyBg_->g_PositionPrp(2) 	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setScale(	_MyBg_->g_VisualPrp(1)	,
																													_MyBg_->g_VisualPrp(2)	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(0, 0, 0, this->m_Buttons->g_CoolTransition()->g_FIO(1))	);
							
							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																													tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



							this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_), false);
						}
					}
				}

				//	OnScreen and Statistics!
				{
					//	LetterBoxing !
					{
						std::vector<LetterBox*>*			_Bars_				= &this->_OnScreen_->g_Ctrl_Bars()->g_Vec_Bars();
						int									_Bars_Size_			= _Bars_->size();

						int									_SpriteID_Bars		= spr::enm_At::OnScreen;
						int									_WhatSprite_		= 0;



						for (	int i = 0; 
								i < _Bars_Size_;
								++i	)
						{
							//	Set position to the sprite.
							_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->setPosition(	_Bars_->at(i)->g_PositionPrp(1)		,
																												_Bars_->at(i)->g_PositionPrp(2)		);

							//	Applying color properties.
							_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->setColor(	sf::Color(	_Bars_->at(i)->g_ColorPrp(1)	,
																														_Bars_->at(i)->g_ColorPrp(2)	,
																														_Bars_->at(i)->g_ColorPrp(3)	,
																														_Bars_->at(i)->g_ColorPrp(4)	)	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->setScale(		_Bars_->at(i)->g_VisualPrp(1)	,
																												_Bars_->at(i)->g_VisualPrp(2)	);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



							this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_Bars)->g_Sprites()->at(_WhatSprite_), false);
						}	
					}

					//	Statistics ! (FPS and Memory)
					if (	false	)
					{
						this->m_Statistics->DrawStatistics();
					}
				}

				//	Displaying side.
				{
					this->_Draw_->RenderTextures();
					this->_Draw_->RenderWindow();

					//	//	Psss... little part for the mouse drawing.
					//	{
					//		//	Draw Cursor
					//		{
					//			int					_SpriteID_Cursor = spr::MySprite::Cursor;
					//			int					_WhatSprite_ = 0;
					//	
					//	
					//	
					//			//	Drawing.
					//			{
					//				//	Set position to the sprite.
					//				_Sprites_->g_Sprite(_SpriteID_Cursor)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->_Mouse_->g_Position(0, 1) + (_Sprites_->g_Sprite(_SpriteID_Cursor)->g_Measures()->at(_WhatSprite_).Third / 2.0) - 3	,
					//																									this->_Mouse_->g_Position(0, 2) + (_Sprites_->g_Sprite(_SpriteID_Cursor)->g_Measures()->at(_WhatSprite_).Fourth / 2.0)		);
					//	
					//				this->_Draw_->DrawWindow(_Sprites_->g_Sprite(_SpriteID_Cursor)->g_Sprites()->at(_WhatSprite_));
					//			}
					//		}
					//	}

					this->_Draw_->Display();
				}



				//	..::	Timer	::..

				ftrTm_Graphics = (this->m_Time->asMicroseconds() / 1000.0) + tckVal_Graphics - ((this->m_Time->asMicroseconds() - nowTm_Graphics) / 1000.0);
			}
		}
	}
	inline void			TextureLoadingFinished()
	{
		this->m_Buttons->s_IsOnRoom(0, false);		//	From the terminal.
		this->m_Buttons->s_IsOnRoom(2, true);		//	To the logo animation.

		//	- - - No transition involved - - -
	}

	inline void			DrawLevel()
	{
		//	- - - - - - - - - - - - - - - - - - -
		//		!	Drawing with both	!
		//	- - - - - - - - - - - - - - - - - - -

		//	Drawing the background.
		{
			BackGround*				_MyBg_					= this->m_BackGrounds->g_Vec_At_BGs(3);

			int						_SpriteID_BackGrounds	= spr::enm_At::BackGrounds;
			int						_WhatSprite_			= _MyBg_->g_BackGroundID();



			//	Actual Drawing.
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	_MyBg_->g_PositionPrp(1)	,
																										_MyBg_->g_PositionPrp(2) 	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setScale(	_MyBg_->g_VisualPrp(1)	,
																										_MyBg_->g_VisualPrp(2)	);				

				//	Fix position to properly render on screen.
				_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().x, xGround)	,
																										tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_)->getPosition().y, yGround)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_BackGrounds)->g_Sprites()->at(_WhatSprite_));
			}
		}





		//	- - - - - - - - - - - - - - - - - - -
		//		   Star Adventure Drawings
		//	- - - - - - - - - - - - - - - - - - -

		this->_Board_Pointer->DrawAll();		

		





		//	- - - - - - - - - - - - - - - - - - -
		//		Friday Night Funking Drawings
		//	- - - - - - - - - - - - - - - - - - -

		//	FNF it's not the original game of this game.
		//	If you ever want to play FNF, just set this->m_EnableFNF
		//	to true and that's all. Have fun :D
		if (this->m_EnableFNF)
		{
			
		}
	}

//	-------------------------------------------
//			Connecting with the outside
//	-------------------------------------------
public:
	inline void			UpdateMeasures()
	{
		this->_Win_W		= this->_Draw_->g_WindowBounds(1);
		this->_Win_H		= this->_Draw_->g_WindowBounds(2);

		this->xGround		= this->_Draw_->g_WorldBounds(1);
		this->yGround		= this->_Draw_->g_WorldBounds(2);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
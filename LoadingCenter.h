#pragma once

#include		"Includes.h"
#include		"_MyIncludes_.h"

//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//			Commentary side.
//	-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	Just like StarAdventure class, this class
//	is made to take the loading textures part
//	as a scenary or a important part of the game.
//	In other words, this is like its controller.



class	LoadingCenter
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			External variables and linkers
//	-------------------------------------------
private:
	DrawFactory*		_Draw_		= nullptr;
	SpriteFactory*		_Sprites_	= nullptr;
	ShaderFactory*		_Shader_	= nullptr;

	Camera*				_Camera_	= nullptr;

//	-------------------------------------------
//			Networking and Connection
//	-------------------------------------------
private:
	sql::SQLConnector*	_SQLConnection_		= nullptr;

//	-------------------------------------------
//			Handling events and more
//	-------------------------------------------
private:
	sf::Event*			m_Event		= nullptr;
	sf::Clock*			m_Clock		= nullptr;
	sf::Time*			m_Time		= nullptr;

	sf::Mutex			_Mutex_;

	double				_Win_W = 0.0, _Win_H = 0.0, xGround = 0.0, yGround = 0.0;

//	-------------------------------------------
//				Timing and Frames
//	-------------------------------------------
private:
	double				nowTm_Graphics	= 0,	ftrTm_Graphics	= 0,	tckVal_Graphics = GAME_LOOP_LOGIC;
	double				nowTm_Logic		= 0,	ftrTm_Logic		= 0,	tckVal_Logic	= GAME_LOOP_LOGIC;

	int					LpCnt_Graphics	= 0,	LpCnt_Logic		= 0;

//	-------------------------------------------
//				Included variables
//	-------------------------------------------
private:
	Ld_SandTimer*		m_SandTimer		= nullptr;
	Terminal*			m_Terminal		= nullptr;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	bool			m_ResourcesFinished		= false;
	bool			m_DataBaseFinished		= true;

	bool			IgnoreSomeTextures	= true;
	bool			Load_Sft_GF			= false;
	bool			Load_Sft_BF			= false;
	bool			Load_CGirlClone		= true;
	bool			Load_BoyFriend		= true;

//	-------------------------------------------
//					Threads
//	-------------------------------------------
private:
	std::thread*			m_LoadResources		= nullptr;
	std::thread*			m_LoadDBConnection	= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LoadingCenter(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	, 
					Camera* _Camrea_Ptr, ShaderFactory* _Shader_Ptr		,
					sql::SQLConnector* _SQL_Ptr							)
	{
		this->_Draw_			= _Draw_Ptr;
		this->_Sprites_			= _Sprite_Ptr;
		this->_Camera_			= _Camrea_Ptr;
		this->_Shader_			= _Shader_Ptr;
		this->_SQLConnection_	= _SQL_Ptr;

		this->_Win_W		= this->_Draw_->g_WindowBounds(1);
		this->_Win_H		= this->_Draw_->g_WindowBounds(2);
		this->xGround		= this->_Draw_->g_WorldBounds(1);
		this->yGround		= this->_Draw_->g_WorldBounds(2);
	}

	~LoadingCenter()
	{
		this->Del_All();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		//	Handling events.
		{
			//	Linking and external.
			{
				this->_Draw_->LinkCamera(this->_Camera_);
			}

			//	Loading all the events related.
			{
				this->m_Event = new sf::Event();
				this->m_Clock = new sf::Clock();			
				this->m_Time = new sf::Time();
			}
		}

		//	Loading the sand timer.
		{
			this->m_SandTimer = new Ld_SandTimer(	tls::TransformPos_X(tls::CenterObjTo(4, this->_Win_W, 110.0, -20), this->xGround)	,
													tls::TransformPos_Y(tls::CenterObjTo(4, this->_Win_H, 147.0, -20), this->yGround)	);
		}

		//	Loading the terminal.
		{
			int								_MyFont_W = 66, _MyFont_H = 100;



			this->m_Terminal = new Terminal(	-xGround, yGround, _MyFont_W, _MyFont_H		, 
												this->_Draw_, this->_Sprites_				);
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

		//	Deleting all included variables.
		{
			tls::Delete(this->m_Terminal);
			tls::Delete(this->m_SandTimer);
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	//	Function that draws a nice animation
	//	when all the proccess of loading and stablish
	//	connections is being done.
	inline void			StartLoading()
	{
		while (		(!this->m_ResourcesFinished)	||
					(!this->m_DataBaseFinished)		)
		{	
			//	---------------------------------------------------
			//		While (n) :		Use it for all window events
			//	---------------------------------------------------
			while (this->_Draw_->g_Window()->pollEvent(*this->m_Event))
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
					//	1	Idk what I tried to do in here but its like
					//		a factor when windows is resized.
					// 
					//		xFactor = window.getSize().x / static_cast<double>(WindowWidth);
					//		yFactor = window.getSize().y / static_cast<double>(WindowHeight);


					//	2	I guess this is for viewing size.
					// 
					//		theView.setSize(	{	static_cast<float>(this->m_Event.size.width),
					//								static_cast<float>(this->m_Event.size.height)	}	);
					//		window.setView(theView);


					//	3	Same here.
					// 		
					//		sf::FloatRect			visibleArea(0, 0, WindowWidth, WindowHeight);
					//		window.setView(sf::View(visibleArea));
				}
			}

			//	------------------------------------------------
			//		Time (1) :		Use it for loop timers.
			//	------------------------------------------------
			*this->m_Time = this->m_Clock->getElapsedTime();





			//	---------------------------------------
			//		Timers (~) :	Logic and more.
			//	---------------------------------------

			//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
			//			Loading Loading ...
			//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
			if ((this->m_Time->asMicroseconds() / 1000.0) >= ftrTm_Logic)
			{
				this->nowTm_Logic = this->m_Time->asMicroseconds();



				//	..::	Code	::..
				this->m_SandTimer->Animate();



				//	..::	Timer	::..

				this->ftrTm_Logic = (this->m_Time->asMicroseconds() / 1000.0) + this->tckVal_Logic - ((this->m_Time->asMicroseconds() - this->nowTm_Logic) / 1000.0);
			}





			//	---------------------------------------
			//		Rendering Graphics : Images !
			//	---------------------------------------
			if ((this->m_Time->asMicroseconds() / 1000.0) >= ftrTm_Graphics)
			{
				nowTm_Graphics = this->m_Time->asMicroseconds();



				//	..::	Code	::..

				//	BackGround :D
				{
					this->m_Terminal->Draw(		Terminal::enm_Draw::_BackGround		);
				}	

				//	Draw the letters (Terminal).
				{
					this->_Mutex_.lock();

					this->m_Terminal->Draw(		Terminal::enm_Draw::_Text		);

					this->_Mutex_.unlock();
				}

				//	Sand Timer.
				{
					int						_SpriteID_SandTimer		= spr::enm_At::inLoading_SandTimer;
					int						_WhatSprite_			= 0;




					//	Actual Drawing.
					{
						//	Set position to the sprite.
						_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->setPosition(	this->m_SandTimer->g_PositionPrp(1)	,
																												this->m_SandTimer->g_PositionPrp(2) 	);

						//	Then goes the shrinking model.
						_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->setScale(	this->m_SandTimer->g_VisualPrp(1)	,
																											this->m_SandTimer->g_VisualPrp(2)	);	

						//	Spining.
						_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->setRotation(	this->m_SandTimer->g_RotationPrp(1)	);

						//	Fix position to properly render on screen.
						_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->getPosition().x, this->xGround)	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_)->getPosition().y, this->yGround)	);



						this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_SandTimer)->g_Sprites()->at(_WhatSprite_));
					}
				}


				//	Displaying side.
				{
					this->_Draw_->RenderTextures();
					this->_Draw_->RenderWindow();
					this->_Draw_->Display();
				}



				//	..::	Timer	::..
				this->ftrTm_Graphics = (this->m_Time->asMicroseconds() / 1000.0) + tckVal_Graphics - ((this->m_Time->asMicroseconds() - nowTm_Graphics) / 1000.0);
			}
		}
	}

	//	Starts all thread to load, connect, etc.
	//	You should call this function once.
	//	And also, be nice when threading.
	inline void			StartThreads(	std::array<sf::Texture, Arr_SA_Txtr_Size>&		Arr_SA_Txtr_tLd		,
										std::array<sf::Texture, Arr_FNF_Txtr_Size>&		Arr_FNF_Txtr_tLd	,
										std::array<sf::SoundBuffer, Arr_SA_SB_Size>&	Arr_SB_tLd			)
	{
		//	-----------------------------
		//	..::### T H R E A D S ###::..
		//	-----------------------------
		this->m_LoadResources		= new std::thread(	&LoadingCenter::LoadResources, this,	std::ref(Arr_SA_Txtr_tLd), std::ref(Arr_FNF_Txtr_tLd)	,
																								std::ref(Arr_SB_tLd)									);

		//	Uncomment this if you want to load the database connection in a thread.
		//	this->m_LoadDBConnection	= new std::thread(	&LoadingCenter::LoadDataBase, this,		"MyFirstDataBaseDNS");




		//	Detaching parts...
		this->m_LoadResources->detach();

		//	And this one too...
		//	this->m_LoadDBConnection->detach();
	}





	//	This functions as not suppossed to be called.
	//	I guess I should put them in private.
	inline int			LoadResources(	std::array<sf::Texture, Arr_SA_Txtr_Size>			&Arr_SA_Txtr_tLd	, 
										std::array<sf::Texture, Arr_FNF_Txtr_Size>			&Arr_FNF_Txtr_tLd	, 
										std::array<sf::SoundBuffer, Arr_SA_SB_Size>			&Arr_SB_tLd			)
	{
		using namespace			std::chrono_literals;
	
		const std::string		_R_T_Bgs		= "_Resources_\\Textures\\BGs\\";
		const std::string		_R_T_Btn		= "_Resources_\\Textures\\Buttons\\";
		const std::string		_R_T_Cnd		= "_Resources_\\Textures\\Candies\\";
		const std::string		_R_T_Igs		= "_Resources_\\Textures\\InGameStuff\\";
		const std::string		_R_T_IUs		= "_Resources_\\Textures\\IsUserEqualsTrue\\";
		const std::string		_R_T_Lns		= "_Resources_\\Textures\\LogoAndStuff\\";
		const std::string		_R_T_Map		= "_Resources_\\Textures\\Maps\\";
		const std::string		_R_T_PaB		= "_Resources_\\Textures\\PanelsAndBoxes\\";
		const std::string		_R_T_Tts		= "_Resources_\\Textures\\Testures\\";
		const std::string		_R_L_			= "_Resources_\\LetterAndStuff\\";
	
		const std::string		_R_S_S_MSq		= "_Resources_\\SoundAndMusic\\SFX\\MatchSequence\\";
		const std::string		_R_S_S_Swt		= "_Resources_\\SoundAndMusic\\SFX\\Switches\\";
		const std::string		_R_S_S_IVo		= "_Resources_\\SoundAndMusic\\SFX\\InstaVoices\\";
		const std::string		_R_S_S_Spc_		= "_Resources_\\SoundAndMusic\\SFX\\Special Candies\\";
		const std::string		_R_S_S_CnS		= "_Resources_\\SoundAndMusic\\SFX\\CoinsAndSurprises\\";
	
	
	
		const std::string		_R_F_OSf		= "_Resources_\\FridayNightFunking\\Other Stuff\\";
		const std::string		_R_F_Chr		= "_Resources_\\FridayNightFunking\\Characters\\";
	
		const std::string		_SGF			= "Soft GirlFriend\\";
		const std::string		_SBF			= "Soft BoyFriend\\";
		const std::string		_CGC			= "Cassette Girl Clone\\";
		const std::string		_BF				= "BoyFriend\\";
	
	
	
	
	
		//	All of this is about texture loading !
		{
			//	All about BackGrounds :D					- - - [3]
			{
				Arr_SA_Txtr_tLd[0].loadFromFile(_R_T_Bgs + "Blank.png");
				Arr_SA_Txtr_tLd[1].loadFromFile(_R_T_Bgs + "SmoothLayer.png");
				Arr_SA_Txtr_tLd[2].loadFromFile(_R_T_Bgs + "ConfrontTheReality.png");
				//	Arr_SA_Txtr_tLd[3].loadFromFile(_R_T_Bgs + "Stranded.png");
	
				Arr_SA_Txtr_tLd[10].loadFromFile(_R_T_Bgs + "ChooseYourAdventure.png");
			}
	
			//	Candies and their delicious sweets !		- - - [8]
			{
				Arr_SA_Txtr_tLd[4].loadFromFile(_R_T_Cnd + "MainCandy.png");
				Arr_SA_Txtr_tLd[5].loadFromFile(_R_T_IUs + "UserUser.png");
				Arr_SA_Txtr_tLd[6].loadFromFile(_R_T_Cnd + "Blockers.png");
				Arr_SA_Txtr_tLd[7].loadFromFile(_R_T_Cnd + "GeneralParticles.png");
				//	Number [8] is free to use.
	
				Arr_SA_Txtr_tLd[13].loadFromFile(_R_T_Cnd + "Crushes_Effects.png");
				Arr_SA_Txtr_tLd[14].loadFromFile(_R_T_Cnd + "GlowParticles.png");
			}
	
			//	In Game Stuff (aka. Board, HUD, ...)		- - - [9]
			{
				Arr_SA_Txtr_tLd[9].loadFromFile(_R_T_Igs + "BoardAndStuff.png");
	
				//	Arr_SA_Txtr_tLd[22].loadFromFile(_R_T_Igs + "InfoBoxAndHUD.png");
			}
	
			//	Letters and Fonts		 ABC				- - - [10]
			{
				Arr_SA_Txtr_tLd[19].loadFromFile(_R_T_PaB + "LevelInfoPanel.png");
				Arr_SA_Txtr_tLd[15].loadFromFile(_R_L_ + "_ScoreFont_.png");
	
				//	Arr_SA_Txtr_tLd[21].loadFromFile(_R_L_ + "ScoreAndOtherStuffWhichAreNotAFontLikeButJustImages.png");
			}
	
			//	Fancy Logo >:D								- - - [11]
			{
				Arr_SA_Txtr_tLd[11].loadFromFile(_R_T_Lns + "FancyLogo.png");
			}
	
			//	All about Buttons. So squishy.				- - - [12]
			{
				Arr_SA_Txtr_tLd[12].loadFromFile(_R_T_Btn + "buttonsPack_r.png");
			}
	
			//	All about BackGrounds :D					- - - [3]
			{
				//	Arr_SA_Txtr_tLd[16].loadFromFile(_R_T_Bgs + "NeonCity.png");
				Arr_SA_Txtr_tLd[17].loadFromFile(_R_T_Bgs + "NightCity.png");
			}
	
			//	Then goes the map.
			{
				Arr_SA_Txtr_tLd[18].loadFromFile(_R_T_Map + "Map.png");
			}
	
			//	Then goes the map.
			{
				//	Arr_SA_Txtr_tLd[20].loadFromFile(_R_T_Lns + "Cursor.png");
			}

			Arr_SA_Txtr_tLd[23].loadFromFile(_R_T_Igs + "inGamePanels.png");
			Arr_SA_Txtr_tLd[24].loadFromFile(_R_L_ + "_OldCartoonFont_.png");
			Arr_SA_Txtr_tLd[25].loadFromFile(_R_L_ + "_CommonFont_.png");
	


			for (int i = 0; i < Arr_SA_Txtr_Size; i++)
				Arr_SA_Txtr_tLd[i].setSmooth(true);
	
	
	
			this->_Mutex_.lock();
			this->m_Terminal->Write("Texture loading finished!\n");
			this->_Mutex_.unlock();
		}
	
		//	Now about sound loading part !
		{
			//	Just loading the match sequence cascade <3		- - -	[10]
			{
				for (int i = 1; i <= 11; i++)
					Arr_SB_tLd[i - 1].loadFromFile(_R_S_S_MSq + "match_sequence_" + tls::IntToStr(i) + "_sfx.wav");
			}
	
			//	About Switches :D								- - -	[13]
			{
				Arr_SB_tLd[11].loadFromFile(_R_S_S_Swt + "negativeSwitch.ogg");
				Arr_SB_tLd[12].loadFromFile(_R_S_S_Swt + "candySwitch.ogg");
				Arr_SB_tLd[13].loadFromFile(_R_S_S_Swt + "specialSwitch.ogg");
			}
	
			//	Divine voices ++								- - -	[17]
			{
				Arr_SB_tLd[14].loadFromFile(_R_S_S_IVo + "sweet.ogg");
				Arr_SB_tLd[15].loadFromFile(_R_S_S_IVo + "tasty.ogg");
				Arr_SB_tLd[16].loadFromFile(_R_S_S_IVo + "delicious.ogg");
				Arr_SB_tLd[17].loadFromFile(_R_S_S_IVo + "divine.ogg");
			}
	
			// Stripped candy SFX								- - -	[19]
			{
				Arr_SB_tLd[18].loadFromFile(_R_S_S_Spc_ + "Stripped Candies\\StrippedCreated.ogg");
				Arr_SB_tLd[19].loadFromFile(_R_S_S_Spc_ + "Stripped Candies\\StrippedLightning.ogg");
			}
	
			// Wrapped candy :3									- - -	[21]
			{
				Arr_SB_tLd[20].loadFromFile(_R_S_S_Spc_ + "Wrapped Candies\\WrappedCreated.ogg");
				Arr_SB_tLd[21].loadFromFile(_R_S_S_Spc_ + "Wrapped Candies\\WrappedCharging.ogg");
				Arr_SB_tLd[22].loadFromFile(_R_S_S_Spc_ + "Wrapped Candies\\WrappedXplode.ogg");
				Arr_SB_tLd[23].loadFromFile(_R_S_S_Spc_ + "Wrapped Candies\\WrappedFuse.ogg");
			}
	
			// Bom-O-Bom waaa									- -	-	[25]
			{
				Arr_SB_tLd[24].loadFromFile(_R_S_S_Spc_ + "Bom-O-Bom\\BomOBomCreated.ogg");
				Arr_SB_tLd[25].loadFromFile(_R_S_S_Spc_ + "Bom-O-Bom\\BomOBomDie.ogg");
				Arr_SB_tLd[26].loadFromFile(_R_S_S_Spc_ + "Bom-O-Bom\\BomOBomHit.ogg");
				Arr_SB_tLd[27].loadFromFile(_R_S_S_Spc_ + "Bom-O-Bom\\BomOBomFuses.ogg");
			}
	
			// Frozen Candy [*]									- -	-	[29]
			{
				Arr_SB_tLd[28].loadFromFile(_R_S_S_Spc_ + "Frozen Candies\\FrozenCandyCreated.ogg");
				Arr_SB_tLd[29].loadFromFile(_R_S_S_Spc_ + "Frozen Candies\\FrozenCandyBurst.ogg");
				Arr_SB_tLd[30].loadFromFile(_R_S_S_Spc_ + "Frozen Candies\\FrozenCandyHit.ogg");
				Arr_SB_tLd[31].loadFromFile(_R_S_S_Spc_ + "Frozen Candies\\FrozenCandyBurstTwo.ogg");
			}
	
			// Jelly Fish -.-									- - -	[31]
			{
				Arr_SB_tLd[32].loadFromFile(_R_S_S_Spc_ + "Jelly Fish\\JellyFishCreated.ogg");
				Arr_SB_tLd[33].loadFromFile(_R_S_S_Spc_ + "Jelly Fish\\JellyFishSwim.ogg");
			}
	
			// Firework Rockets BOOM!!							- - -	[34]
			{
				Arr_SB_tLd[34].loadFromFile(_R_S_S_Spc_ + "FireWork Rocket Candies\\FireWork Launch.ogg");
				Arr_SB_tLd[35].loadFromFile(_R_S_S_Spc_ + "FireWork Rocket Candies\\FireWork Created.ogg");
				Arr_SB_tLd[36].loadFromFile(_R_S_S_Spc_ + "FireWork Rocket Candies\\FireWork Explosion Simple.ogg");
			}
	
			// Coins and Surprises								- - -	[36]
			{
				Arr_SB_tLd[37].loadFromFile(_R_S_S_CnS + "CoinSpawns.ogg");
				Arr_SB_tLd[38].loadFromFile(_R_S_S_CnS + "CoinPicking.ogg");
				Arr_SB_tLd[39].loadFromFile(_R_S_S_CnS + "Chime.ogg");
				Arr_SB_tLd[40].loadFromFile(_R_S_S_CnS + "PickingPrize.ogg");
			}
	
			//	CupCake.
			{
				Arr_SB_tLd[41].loadFromFile(_R_S_S_Spc_ + "CupCakes\\CupCakeEaten.ogg");
			}
	
	
	
			this->_Mutex_.lock();
			this->m_Terminal->Write("Sound loading finished!\n");
			this->_Mutex_.unlock();
		}
	
		if (	0	)
		//	{ It's FNF turns to load its textures ! }
		{
			//	All about arrows and related!				- - -	[0]
			{
				Arr_FNF_Txtr_tLd[0].loadFromFile(_R_F_OSf + "Arrows.png");
			}
	
			//	Characters and people!						- - -	[1]
			{
				if (	0		)
				{
					Arr_FNF_Txtr_tLd[1].loadFromFile(_R_F_Chr + _SGF + "SoftGF.png");
				}
				if (	0		)
				{
					Arr_FNF_Txtr_tLd[2].loadFromFile(_R_F_Chr + _SBF + "SoftBF.png");
				}
				if (	1	)
				{
					Arr_FNF_Txtr_tLd[3].loadFromFile(_R_F_Chr + _CGC + "CassetteGirlClone.png");
				}
				if (	1	)
				{
					Arr_FNF_Txtr_tLd[4].loadFromFile(_R_F_Chr + _BF + "BoyFriend.png");
				}
			}
			
	
	
			for (int i = 0; i < Arr_FNF_Txtr_Size; i++)
				Arr_FNF_Txtr_tLd[i].setSmooth(true);
	
	
	
			this->_Mutex_.lock();
			this->m_Terminal->Write("Texture loading finished!\n");
			this->_Mutex_.unlock();
		}
	
	
	
		this->_Mutex_.lock();
		this->m_Terminal->Write("All multimedia files loaded! Enjoy~");
		this->_Mutex_.unlock();
	
	
	
		std::this_thread::sleep_for(0.1s);
		this->m_ResourcesFinished	= true;

		return		0;
	}
	
	inline int			LoadDataBase(	const std::string& DataBaseDSN	)
	{
		this->m_DataBaseFinished = this->_SQLConnection_->StartConnection(		DataBaseDSN		);

		this->_Mutex_.lock();
		this->m_Terminal->Write("DataBase Connection Success!\n");
		this->_Mutex_.unlock();

		return		0;
	}


//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline Terminal*		g_Terminal()
	{
		return			this->m_Terminal;
	}
};
#pragma once
#include	<iostream>
#include	<array>

#include	<SFML/Graphics.hpp>
#include	<SFML/Window.hpp>


//									Remember List !
//	----------------------------------------------------------------------------------
//		1.	The + and - when drawing, depends on the center of the sprite (origin).
//		2.	'v' for vector and 'c' for container.
//		3.	Sprite origin: Extra offset is depending on the ammount of origin.
//			Example:	Sprite (4, 4) Origin (1, 1) -> Add (+1, -1);


//	All about sprites, textures, and more !
namespace		spr
{
	enum	enm_At
	{
		//	-----------------------
		//		Loading section
		//	-----------------------
		inLoading_BackGrounds	,
		inLoading_SandTimer		,
		inLoading_ImageFont		,

		//	-----------------------
		//		All contexts
		//	-----------------------
		Cursor					,
		BackGrounds				,
		OnScreen				,
		Buttons					,

		//	-----------------------
		//		Star Adventure
		//	-----------------------
		ScoreFont				,

		CrushingParticles		,
		GlowParticles			,
		GeneralParticles		,
		LevelInfoPanel			,
		Board					,

		Candies					,
		StrippedHorizontal		,
		StrippedVertical		,
		WrappedCandy			,
		WrappedFuse				,
		JellyFish				,
		FrozenCandy				,
		BonOBom					,
		StarLight				,
		FireWorkRocket			,
		BubbleGum				,
		PoppingCandy			,

		CandiesGlow				,
		JellyFish_Contents		,
		Fc_Base					,
		Fc_Frojectiles			,
		Fc_Splash				,
		BoB_Contents			,
		StL_Base				,
		StL_Contents			,
		FwR_Contents			,
		PoC_Base				,
		PoC_Contents			,

		Blockers				,
		CupCakes				,

		Maps					,
		PushableButton			,
		CombosAndScore			,
		LevelHUD				,
		InGamePanels			,
		CoinsAndSurprises		,

		UserUser				,
		LiviconHUD				,

		Layouts					,
		OldCartoonFont			,
		CommonFont				,


		//	------------------------------
		//		Friday Night Funking
		//	------------------------------
		FNF_Arrows				,
		FNF_Glows				,
		FNF_GirlFriendSoft		,
		FNF_BoyFriendSoft		,
		FNF_CassetteGirlClone	,
		FNF_BoyFriend			,



		Size	,
	};

	enum	enm_FcSplash
	{
		SplashAmount		= 1,
		FrojectileAmount	= 2,
	};
}
namespace		fnt
{
	enum	enm_At
	{
		Mojangles	= 0,
		Vcr			= 1
	};

	enum	enm_FontType
	{
		Normal		= 0,
		CommonFont	= 1,
	};
}



class	SpriteContainer
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Typenames
//	-------------------------------------------
private:
	typedef		std::vector<sf::Sprite*>			vSpr_;
	typedef		std::vector<tls::Vec6<double>>		cSize_;

//	-------------------------------------------
//				Sprite Variables
//	-------------------------------------------
private:
	vSpr_*			m_Sprites = nullptr;

//	-------------------------------------------
//				Measures Variables
//	-------------------------------------------
private:
	cSize_*			m_Measures = nullptr;


//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	SpriteContainer()
	{
		this->m_Sprites		= new vSpr_();
		this->m_Measures	= new cSize_();
	}

	~SpriteContainer()
	{
		//	Erasing m_Sprites...
		{
			while (!this->m_Sprites->empty())
			{
				delete		this->m_Sprites->at(0);
				this->m_Sprites->erase(this->m_Sprites->begin() + 0);
			}

			if (this->m_Sprites != nullptr)
			{
				delete this->m_Sprites;
			}
		}

		//	Erasing m_Measures...
		{
			while (!this->m_Measures->empty())
			{
				this->m_Measures->erase(this->m_Measures->begin() + 0);
			}

			if (this->m_Measures != nullptr)
			{
				delete this->m_Measures;
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddSprite(sf::Sprite* _Sprite)
	{
		this->m_Sprites->push_back(_Sprite);
	}
	inline void			AddMeasure(tls::Vec4<double> _Measure)
	{
		this->m_Measures->push_back(tls::Vec6<double>(	_Measure.First	, 
														_Measure.Second	,
														_Measure.Third	,
														_Measure.Fourth	,
														0.0, 0.0		) );
	}
	inline void			AddMeasure(tls::Vec6<double> _Measure)
	{
		this->m_Measures->push_back(_Measure);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline vSpr_*		g_Sprites()
	{
		return this->m_Sprites;
	}
	inline cSize_*		g_Measures()
	{
		return this->m_Measures;
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
class	SpriteFactory
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Textures
//	-------------------------------------------
private:
	sf::RenderTexture		_RenderTexture_;
	sf::Texture				_Texture_;

//	-------------------------------------------
//				Sprites Container
//	-------------------------------------------
private:
	std::vector<SpriteContainer*>		m_Sprites;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_TotalKind					= 10;
	int			m_ScoreFont_Characters		= 58;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	SpriteFactory()
	{
		//	Render textures.
		{
			_RenderTexture_.create(2048, 1024);
			_Texture_.create(2048, 1024);
		}

		//	Sprites container.
		{
			for (	int i = 0; 
					i < spr::enm_At::Size; 
					++i	)
			{
				this->m_Sprites.push_back(	new SpriteContainer()	);
			}
		}
	}

	~SpriteFactory()
	{
		tls::DeleteVector(		this->m_Sprites		);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Ld_Sprites_Loading(		const std::array<sf::Texture, Arr_Testures_Size>&	_Ld_Textures_		)
	{
		//	- - - - - - - - - - - - - - - - - - -
		//				Before and all
		//	- - - - - - - - - - - - - - - - - - -

		//	BackGrounds.
		{					
			this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2048.0, 2048.0)	);
			


			for (	int i = 0; i < 1; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Ld_Textures_[0]		);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->g_Measures()->at(i).Fourth)	);



				this->m_Sprites[spr::enm_At::inLoading_BackGrounds]->AddSprite(_NewSprite);
			}						
		}

		//	Sand Timer.
		{
			this->m_Sprites[spr::enm_At::inLoading_SandTimer]->AddMeasure(	tls::Vec4<double>(0, 0, 110.0, 147.0)	);	//	Blank for covering :D



			for (	int i = 0; i < 1; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Ld_Textures_[1]		);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).Fourth)		);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::inLoading_SandTimer]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::inLoading_SandTimer]->AddSprite(_NewSprite);
			}							
		}

		//	Fonts
		{
			this->m_Sprites[spr::enm_At::inLoading_ImageFont]->AddMeasure(tls::Vec4<double>(0, 0, 66.0, 100.0));	//	Blank for covering :D



			int			_Aux_			= -1;
			int			_NoLetter_Row_	= 20;



			for (	int i = 0;
						i < 128;
						++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();

				if (	(i % _NoLetter_Row_) == 0	)
				{
					++_Aux_;
				}



				_NewSprite->setTexture(_Ld_Textures_[2]);

				_NewSprite->setTextureRect(	sf::IntRect(	(i - (_Aux_ * _NoLetter_Row_)) * this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Third	,
															_Aux_ * this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Fourth							,
															this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Third									,
															this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Fourth									)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Third / 2.0,
										this->m_Sprites[spr::enm_At::inLoading_ImageFont]->g_Measures()->at(0).Fourth / 2.0);



				this->m_Sprites[spr::enm_At::inLoading_ImageFont]->AddSprite(_NewSprite);
			}				
		}
	}
	inline void			Ld_Sprites(				const std::array<sf::Texture, Arr_SA_Txtr_Size>&	_Textures_			)
	{
		//	- - - - - - - - - - - - - - - - - - -
		//				All contexts
		//	- - - - - - - - - - - - - - - - - - -

		//	Cursor.
		{
			this->m_Sprites[spr::enm_At::Cursor]->AddMeasure(tls::Vec4<double>(0, 0, 35.0, 38.0));	//	Cursor.
			

		
			for (	int i = 0; i < 1; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();


				
				_NewSprite->setTexture(		_Textures_[20]		);		

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).Fourth)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::Cursor]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::Cursor]->AddSprite(	_NewSprite	);
			}						
		}

		//	BackGrounds.
		{
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2048.0, 2048.0)	);	//	Blank for covering :D
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2000.0, 1200.0)	);	//	ConfrontTheReality.
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2000.0, 1300.0)	);	//	Stranded.
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2144.0, 1206.0)	);	//	Night city.
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 3412.0, 2021.0)	);	//	Neon city.
			this->m_Sprites[spr::enm_At::BackGrounds]->AddMeasure(	tls::Vec4<double>(0, 0, 2048.0, 1024.0)	);	//	Choose your adventure.
			

			
			for (	int i = 0; i < 6; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();


				
				switch (i)
				{
				case 0:
					_NewSprite->setTexture(_Textures_[0]);
					break;

				case 1:
					_NewSprite->setTexture(_Textures_[2]);
					break;

				case 2:
					_NewSprite->setTexture(_Textures_[3]);
					break;

				case 3:
					_NewSprite->setTexture(_Textures_[17]);
					break;

				case 4:
					_NewSprite->setTexture(_Textures_[16]);
					break;

				case 5:
					_NewSprite->setTexture(_Textures_[10]);
					break;
				}				

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::BackGrounds]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::BackGrounds]->AddSprite(_NewSprite);
			}				
		}

		//	OnScreen.
		{
			this->m_Sprites[spr::enm_At::OnScreen]->AddMeasure(	tls::Vec4<double>(0, 0, 1800.0, 100.0)	);	//	LetterBox
			this->m_Sprites[spr::enm_At::OnScreen]->AddMeasure(	tls::Vec4<double>(0, 0, 2048.0, 2048.0)	);	//	Blank Image
			this->m_Sprites[spr::enm_At::OnScreen]->AddMeasure(	tls::Vec4<double>(0, 0, 483.0, 367.0)	);	//	Main Logo
			this->m_Sprites[spr::enm_At::OnScreen]->AddMeasure(	tls::Vec4<double>(0, 0, 2048.0, 1024.0)	);	//	Smooth layer
		


			//	Letter Box
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[0]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(0).First		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(0).Second	,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(0).Third		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(0).Fourth)	);



				this->m_Sprites[spr::enm_At::OnScreen]->AddSprite(_NewSprite);
			}

			//	Blank Image
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[0]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).First		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).Second	,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).Third		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).Fourth)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).Third / 2.0	,
											this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(1).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::OnScreen]->AddSprite(_NewSprite);
			}			

			//	Fancy Logo.
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[11]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).First		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).Second	,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).Third		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).Fourth)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).Third / 2.0	,
											this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(2).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::OnScreen]->AddSprite(_NewSprite);
			}

			//	Smooth Layer.
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[1]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(3).First		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(3).Second	,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(3).Third		,
															this->m_Sprites[spr::enm_At::OnScreen]->g_Measures()->at(3).Fourth	)	);



				this->m_Sprites[spr::enm_At::OnScreen]->AddSprite(_NewSprite);				
			}	
		}

		//	Buttons.
		{
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(0, 0, 173, 87)		);	//	PlayButton
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(174, 0, 235, 74)		);	//	SettingButton
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(410, 0, 150, 150)		);	//	BackButton
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(560, 0, 250, 210)		);	//	Map Button
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(560, 210, 198, 275)	);	//	Arcade Button

			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(891, 0, 130, 130)		);	//	Close Button
			this->m_Sprites[spr::enm_At::Buttons]->AddMeasure(	tls::Vec4<double>(1025, 2, 316, 116)	);	//	PlayLevel Button


		
			//	First five buttons.
			for (	int i = 0;
					i < 5;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[12]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::Buttons]->AddSprite(		_NewSprite		);
			}		

			//	Close Button, PlayLevel Button.
			for (	int i = 5;
					i < 7;
					++i	)
			{
				sf::Sprite* _NewSprite		= new sf::Sprite();



				_NewSprite->setTexture(_Textures_[19]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::Buttons]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::Buttons]->AddSprite(		_NewSprite		);
			}
		}





		//	- - - - - - - - - - - - - - - - - - -
		//				Star Adventure
		//	- - - - - - - - - - - - - - - - - - -

		//	LevelInfoPanel.
		{
			this->m_Sprites[spr::enm_At::LevelInfoPanel]->AddMeasure(	tls::Vec4<double>(0, 0, 890, 960)		);	//	Panel.
			this->m_Sprites[spr::enm_At::LevelInfoPanel]->AddMeasure(	tls::Vec4<double>(892, 130, 493, 163)	);	//	Level Banner.



			for (	int i = 0;
					i < 2;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[19]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).Fourth)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).Third / 2.0		,
										this->m_Sprites[spr::enm_At::LevelInfoPanel]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::LevelInfoPanel]->AddSprite(_NewSprite);
			}
		}

		//	ScoreFont.
		{
			this->m_Sprites[spr::enm_At::ScoreFont]->AddMeasure(tls::Vec4<double>(0, 0, 66, 100));
			


			int			_Aux_			= -1;
			int			_FontWidthEnd_	= 20;

			

			for (	int i = 0;
					i < this->m_ScoreFont_Characters;
					++i	)
			{
				sf::Sprite* _NewSprite		= new sf::Sprite();



				if (	(i % _FontWidthEnd_) == 0	)
				{
					++_Aux_;
				}

				_NewSprite->setTexture(_Textures_[15]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Third * (i - (_Aux_ * _FontWidthEnd_))	,
															_Aux_ * this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Fourth		,
															this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Third / 2.0	,
										this->m_Sprites[spr::enm_At::ScoreFont]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::ScoreFont]->AddSprite(_NewSprite);
			}
		}

		//	Board.
		{
			this->m_Sprites[spr::enm_At::Board]->AddMeasure(tls::Vec4<double>(0, 0, 90, 90));
			this->m_Sprites[spr::enm_At::Board]->AddMeasure(tls::Vec4<double>(91, 0, 90, 90));


			
			for (	int i = 0;
					i < 2;
					++i	)
			{
				sf::Sprite* _NewSprite		= new sf::Sprite();



				_NewSprite->setTexture(						_Textures_[9]				);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::Board]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::Board]->AddSprite(_NewSprite);
			}
		}

		//	Candies.
		{
			this->m_Sprites[spr::enm_At::Candies]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(	_Textures_[4]	);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).Second				,
															this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).Third				,	
															this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).Third / 2.0,
										this->m_Sprites[spr::enm_At::Candies]->g_Measures()->at(0).Fourth / 2.0);



				this->m_Sprites[spr::enm_At::Candies]->AddSprite(_NewSprite);
			}
		}

		//	CandiesGlow
		{
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 100, 113, 111)	);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 0, 0)		);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 211, 118, 103)	);

			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 314, 110, 108)	);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 100, 100)	);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 422, 114, 99)	);

			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 0, 0)		);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 0, 0)		);
			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 0, 0)		);

			this->m_Sprites[spr::enm_At::CandiesGlow]->AddMeasure(	tls::Vec4<double>(0, 0, 0, 0)		);	



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[14]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).Fourth)		);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).Third / 2.0		,
										this->m_Sprites[spr::enm_At::CandiesGlow]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::CandiesGlow]->AddSprite(_NewSprite);
			}
		}

		//	StrippedHorizontal.
		{
			this->m_Sprites[spr::enm_At::StrippedHorizontal]->AddMeasure(	tls::Vec4<double>(0, 0, 100, 100)	);



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(	_Textures_[4]	);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).Second + 100		,
															this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).Fourth			)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).Third / 2.0		,
										this->m_Sprites[spr::enm_At::StrippedHorizontal]->g_Measures()->at(0).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::StrippedHorizontal]->AddSprite(_NewSprite);
			}
		}

		//	StrippedVertical.
		{
			this->m_Sprites[spr::enm_At::StrippedVertical]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[4]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).Second + 200		,
															this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).Third / 2.0		,
											this->m_Sprites[spr::enm_At::StrippedVertical]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::StrippedVertical]->AddSprite(	_NewSprite		);
			}
		}

		//	WrappedCandy.
		{
			this->m_Sprites[spr::enm_At::WrappedCandy]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).Second + 300		,
															this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).Third / 2.0	,
											this->m_Sprites[spr::enm_At::WrappedCandy]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::WrappedCandy]->AddSprite(_NewSprite);
			}
		}

		//	WrappedFuse.
		{		
			this->m_Sprites[spr::enm_At::WrappedFuse]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).Second + 400			,
															this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).Third / 2.0	,
											this->m_Sprites[spr::enm_At::WrappedFuse]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::WrappedFuse]->AddSprite(_NewSprite);
			}
		}

		//	JellyFish.
		{
			this->m_Sprites[spr::enm_At::JellyFish]->AddMeasure(tls::Vec4<double>(0, 0, 125, 100));



			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).First + (125 * i)	,
															this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).Second + 500		,
															this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).Third / 2.0	,
											this->m_Sprites[spr::enm_At::JellyFish]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::JellyFish]->AddSprite(_NewSprite);
			}
		}

		//	JellyFish_Contents.
		{
			this->m_Sprites[spr::enm_At::JellyFish_Contents]->AddMeasure(		tls::Vec4<double>(0, 0, 39, 39)			);		//	Bubble.
			this->m_Sprites[spr::enm_At::JellyFish_Contents]->AddMeasure(		tls::Vec4<double>(39, 0, 100, 100)		);		//	Fish Target.



			for (	int i = 0;
					i < 2;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[7]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).Third / 2.0	,
											this->m_Sprites[spr::enm_At::JellyFish_Contents]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::JellyFish_Contents]->AddSprite(	_NewSprite		);
			}
		}

		//	FrozenCandy.
		{
			this->m_Sprites[spr::enm_At::FrozenCandy]->AddMeasure(	tls::Vec4<double>(0, 0, 110, 110)	);
			


			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).First + (110 * i)	,
															this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).Second + 600			,
															this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).Third / 2.0		,
											this->m_Sprites[spr::enm_At::FrozenCandy]->g_Measures()->at(0).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::FrozenCandy]->AddSprite(_NewSprite);
			}
		}

		//	Fc_Base.
		{
			//	Measures and bounds (Splash).
			{
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(241, 200, 100, 100)		);		//	Color
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(241, 300, 100, 100)		);		//	Shadow
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(241, 100, 100, 100)		);		//	Light
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(241, 0, 100, 100)			);		//	Draw
			}

			//	Measures and bounds (Frojectile).
			{
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(139, 100, 40, 50)		);		//	Color
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(139, 150, 40, 50)		);		//	Shadow
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(139, 50, 40, 50)		);		//	Light
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(139, 0, 40, 50)		);		//	Draw

				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(179, 90, 45, 45)		);		//	Color
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(179, 135, 45, 45)		);		//	Shadow
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(179, 45, 45, 45)		);		//	Light
				this->m_Sprites[spr::enm_At::Fc_Base]->AddMeasure(	tls::Vec4<double>(179, 0, 45, 45)		);		//	Draw
			}



			for (	int i = 0; i < 12; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[7]	);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(i).Fourth	)	);



				this->m_Sprites[spr::enm_At::Fc_Base]->AddSprite(	_NewSprite	);
			}
		}

		//	BonOBom.
		{
			this->m_Sprites[spr::enm_At::BonOBom]->AddMeasure(	tls::Vec4<double>(1000, 0, 100, 100)	);



			for (	int i = 0; i < 1; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[4]	);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).Third / 2.0	,
										this->m_Sprites[spr::enm_At::BonOBom]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::BonOBom]->AddSprite(	_NewSprite	);
			}
		}

		//	BoB_Contents.
		{
			this->m_Sprites[spr::enm_At::BoB_Contents]->AddMeasure(tls::Vec4<double>(392, 0, 120, 6));
			


			for (	int i = 0;
					i < 1;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[7]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::BoB_Contents]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::BoB_Contents]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::BoB_Contents]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::BoB_Contents]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(		0.0																				,
											this->m_Sprites[spr::enm_At::BoB_Contents]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::BoB_Contents]->AddSprite(_NewSprite);
			}
		}

		//	StarLight.
		{
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(0, 710, 100, 100)		);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(100, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(200, 710, 100, 100)	);
	
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(300, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(400, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(500, 710, 100, 100)	);
			
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(600, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(700, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(800, 710, 100, 100)	);
			this->m_Sprites[spr::enm_At::StarLight]->AddMeasure(	tls::Vec4<double>(900, 710, 100, 100)	);
			


			for (	int i = 0; 	i < 10; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[4]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).Third / 2.0	,
										this->m_Sprites[spr::enm_At::StarLight]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::StarLight]->AddSprite(_NewSprite);
			}
		}

		//	StL_Base.
		{
			this->m_Sprites[spr::enm_At::StL_Base]->AddMeasure(	tls::Vec4<double>(1100, 0, 140, 145)	);
			this->m_Sprites[spr::enm_At::StL_Base]->AddMeasure(	tls::Vec4<double>(1100, 290, 140, 145)	);
			this->m_Sprites[spr::enm_At::StL_Base]->AddMeasure(	tls::Vec4<double>(1100, 145, 140, 145)	);
			this->m_Sprites[spr::enm_At::StL_Base]->AddMeasure(	tls::Vec4<double>(1240, 0, 140, 145)	);
			


			for (	int i = 0;
					i < 4;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(i).Fourth	)	);



				this->m_Sprites[spr::enm_At::StL_Base]->AddSprite(_NewSprite);
			}
		}

		//	FireWorkRocket.
		{
			this->m_Sprites[spr::enm_At::FireWorkRocket]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));
			


			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[4]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).Second + 810		,
															this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).Fourth			)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).Third / 2.0		,
											this->m_Sprites[spr::enm_At::FireWorkRocket]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::FireWorkRocket]->AddSprite(		_NewSprite		);
			}
		}

		//	FwR_Contents.
		{
			this->m_Sprites[spr::enm_At::FwR_Contents]->AddMeasure(tls::Vec4<double>(341, 0, 50, 50));



			for (	int i = 0;
					i < 1;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[7]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).First 	,
															this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).Third / 2.0		,
											this->m_Sprites[spr::enm_At::FwR_Contents]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::FwR_Contents]->AddSprite(		_NewSprite		);
			}
		}

		//	BubbleGum.
		{
			this->m_Sprites[spr::enm_At::BubbleGum]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));
			


			for (	int i = 0;
					i < this->m_TotalKind;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[4]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).Second + 910		,
															this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).Third / 2.0	,
											this->m_Sprites[spr::enm_At::BubbleGum]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::BubbleGum]->AddSprite(_NewSprite);
			}
		}

		//	PoppingCandy.
		{
			this->m_Sprites[spr::enm_At::PoppingCandy]->AddMeasure(tls::Vec4<double>(0, 0, 100, 100));
			


			for (int i = 0;
				i < this->m_TotalKind;
				++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[4]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).First + (100 * i)	,
															this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).Second + 1010		,
															this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).Third				,
															this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).Fourth				)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).Third / 2.0		,
											this->m_Sprites[spr::enm_At::PoppingCandy]->g_Measures()->at(0).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::PoppingCandy]->AddSprite(_NewSprite);
			}
		}

		//	PoC_Base.
		{
			this->m_Sprites[spr::enm_At::PoC_Base]->AddMeasure(	tls::Vec4<double>(341, 78, 25, 27)	);
			this->m_Sprites[spr::enm_At::PoC_Base]->AddMeasure(	tls::Vec4<double>(341, 51, 25, 27)	);



			for (	int i = 0;
					i < 2;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[7]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(i).Fourth	)	);



				this->m_Sprites[spr::enm_At::PoC_Base]->AddSprite(	_NewSprite	);
			} 
		}

		//	CrushingParticles.
		{
			this->m_Sprites[spr::enm_At::CrushingParticles]->AddMeasure(	tls::Vec4<double>(0, 0, 100, 100)	);
			this->m_Sprites[spr::enm_At::CrushingParticles]->AddMeasure(	tls::Vec4<double>(102, 0, 99, 90)	);
			this->m_Sprites[spr::enm_At::CrushingParticles]->AddMeasure(	tls::Vec4<double>(203, 16, 99, 74)	);
			


			for (	int i = 0; i < 30; ++i	)
			{
				sf::Sprite*			_NewSprite = new sf::Sprite();



				_NewSprite->setTexture(						_Textures_[13]	);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).First, 
															this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).Second + (101 * (i / 3)),
															this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).Third,
															this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).Fourth	)	);
														
				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).Third / 2.0,
															this->m_Sprites[spr::enm_At::CrushingParticles]->g_Measures()->at(i % 3).Fourth / 2.0	);

				this->m_Sprites[spr::enm_At::CrushingParticles]->AddSprite(		_NewSprite	);
			}
		}	

		//	GlowParticles.
		{
			//	Compress.
			{
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(0, 0, 100, 100)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(100, 0, 90, 90)	);

				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(191, 0, 215, 300)	);	
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(406, 0, 96, 143)	);		
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(406, 143, 54, 54)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(460, 143, 44, 45)	);	

				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(406, 197, 45, 44)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(450, 197, 30, 30)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(480, 188, 26, 26)	);

				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(480, 214, 41, 41)	);

				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(502, 0, 138, 129)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(640, 0, 110, 106)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(751, 0, 135, 143)	);

				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(190, 300, 400, 400)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(521, 129, 120, 118)	);
				this->m_Sprites[spr::enm_At::GlowParticles]->AddMeasure(	tls::Vec4<double>(191, 700, 120, 120)	);
			}



			for (	int i = 0; i < 16; ++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[14]);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).Third / 2.0	,
															this->m_Sprites[spr::enm_At::GlowParticles]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::GlowParticles]->AddSprite(			_NewSprite		);
			}
		}

		//	GeneralParticles.
		{
			this->m_Sprites[spr::enm_At::GeneralParticles]->AddMeasure(tls::Vec4<double>(0, 0, 39, 39));



			for (int i = 0; i < 1; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[7]);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).Third / 2.0		,	
															this->m_Sprites[spr::enm_At::GeneralParticles]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::GeneralParticles]->AddSprite(			_NewSprite		);
			}
		}	

		//	Maps.
		{
			this->m_Sprites[spr::enm_At::Maps]->AddMeasure(tls::Vec4<double>(0, 0, 2048, 2048));
			


			for (	int i = 0;
					i < 1;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[18]			);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::Maps]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::Maps]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::Maps]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::Maps]->g_Measures()->at(i).Fourth	)	);



				this->m_Sprites[spr::enm_At::Maps]->AddSprite(_NewSprite);
			}
		}

		//	PushableButton.
		{
			//	Compress.
			{
				this->m_Sprites[spr::enm_At::PushableButton]->AddMeasure(	tls::Vec4<double>(810, 0, 155, 21)		);	//	BackBase
				this->m_Sprites[spr::enm_At::PushableButton]->AddMeasure(	tls::Vec4<double>(810, 21, 155, 40)		);	//	FrontBase
				this->m_Sprites[spr::enm_At::PushableButton]->AddMeasure(	tls::Vec4<double>(810, 61, 153, 104)	);	//	PushButton
				this->m_Sprites[spr::enm_At::PushableButton]->AddMeasure(	tls::Vec4<double>(810, 165, 25, 34)		);	//	LightningBase
				this->m_Sprites[spr::enm_At::PushableButton]->AddMeasure(	tls::Vec4<double>(836, 165, 40, 44)		);	//	LightningBase
			}



			for (	int i = 0;
					i < 5;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[12]);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).Third / 2.0		,
											this->m_Sprites[spr::enm_At::PushableButton]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::PushableButton]->AddSprite(		_NewSprite		);
			}
		}

		//	CombosAndScore.
		{
			//	Compress.
			{
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 0, 96, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 97, 75, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 172, 96, 145)	);

				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 268, 87, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 355, 91, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 446, 89, 145)	);

				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 535, 93, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 628, 89, 145)	);
				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 717, 94, 145)	);

				this->m_Sprites[spr::enm_At::CombosAndScore]->AddMeasure(	tls::Vec4<double>(0, 811, 89, 145)	);
			}

			

			for (	int i = 0;
					i < 10;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[21]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).Fourth)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).Third / 2.0		,
										this->m_Sprites[spr::enm_At::CombosAndScore]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::CombosAndScore]->AddSprite(_NewSprite);
			}
		}

		//	HUDs.
		{
			//	Compress.
			{
				//	Lollipop Meadow.
				{
					this->m_Sprites[spr::enm_At::LevelHUD]->AddMeasure(	tls::Vec4<double>(0, 0, 472, 529)		);	//	Tree
					this->m_Sprites[spr::enm_At::LevelHUD]->AddMeasure(	tls::Vec4<double>(472, 0, 303, 92)		);	//	Sign 1
					this->m_Sprites[spr::enm_At::LevelHUD]->AddMeasure(	tls::Vec4<double>(472, 92, 334, 213)	);	//	Sign 2
				}
			}



			for (	int i = 0;
					i < 3;
					++i	)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(			_Textures_[22]			);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).Fourth)		);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).Third / 2.0		,
										this->m_Sprites[spr::enm_At::LevelHUD]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::LevelHUD]->AddSprite(	_NewSprite	);
			}
		}

		//	CoinsAndSurprises.
		{
			this->m_Sprites[spr::enm_At::CoinsAndSurprises]->AddMeasure(	tls::Vec4<double>(0, 221, 68, 68)			);		//	Coin.



			for (int i = 0; i < 1; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[7]);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::CoinsAndSurprises]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::CoinsAndSurprises]->AddSprite(			_NewSprite		);
			}
		}

		//	Blockers.
		{
			this->m_Sprites[spr::enm_At::Blockers]->AddMeasure(	tls::Vec4<double>(0, 0, 100, 93)			);		//	LicoriceCage.



			for (int i = 0; i < 1; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[6]	);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::Blockers]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::Blockers]->AddSprite(			_NewSprite		);
			}
		}

		//	CupCakes.
		{
			this->m_Sprites[spr::enm_At::CupCakes]->AddMeasure(	tls::Vec4<double>(0, 1110, 100, 100)	);		//	Cupcake_1.
			this->m_Sprites[spr::enm_At::CupCakes]->AddMeasure(	tls::Vec4<double>(100, 1110, 100, 100)	);		//	Cupcake_2.
			this->m_Sprites[spr::enm_At::CupCakes]->AddMeasure(	tls::Vec4<double>(200, 1110, 100, 100)	);		//	Cupcake_3.
			this->m_Sprites[spr::enm_At::CupCakes]->AddMeasure(	tls::Vec4<double>(300, 1110, 100, 100)	);		//	Cupcake_4.
			this->m_Sprites[spr::enm_At::CupCakes]->AddMeasure(	tls::Vec4<double>(400, 1110, 100, 100)	);		//	Cupcake_5.



			for (int i = 0; i < 5; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[4]);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::CupCakes]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::CupCakes]->AddSprite(			_NewSprite		);
			}
		}

		//	UserUser.
		{
			this->m_Sprites[spr::enm_At::UserUser]->AddMeasure(	tls::Vec4<double>(0, 0, 175, 175)	);		//	User Icon.



			for (int i = 0; i < 1; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(_Textures_[5]);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::UserUser]->g_Measures()->at(i).Fourth / 2.0	);



				this->m_Sprites[spr::enm_At::UserUser]->AddSprite(			_NewSprite		);
			}
		}

		//	InGamePanels.
		{
			this->m_Sprites[spr::enm_At::InGamePanels]->AddMeasure(		tls::Vec4<double>(0, 0, 415, 612)			);		//	StatsPanel back.
			this->m_Sprites[spr::enm_At::InGamePanels]->AddMeasure(		tls::Vec4<double>(415, 0, 385, 583)			);		//	StatsPanel front.



			for (int i = 0; i < 2; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[23]	);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::InGamePanels]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::InGamePanels]->AddSprite(			_NewSprite		);
			}
		}

		//	LiviconHUD.
		{
			this->m_Sprites[spr::enm_At::LiviconHUD]->AddMeasure(		tls::Vec4<double>(758, 210, 100, 86)		);		//	Life Icon.
			this->m_Sprites[spr::enm_At::LiviconHUD]->AddMeasure(		tls::Vec4<double>(858, 210, 92, 86)			);		//	Coin Icon.
			this->m_Sprites[spr::enm_At::LiviconHUD]->AddMeasure(		tls::Vec4<double>(964, 0, 250, 282)			);		//	Panel.



			for (int i = 0; i < 3; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[12]	);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::LiviconHUD]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::LiviconHUD]->AddSprite(			_NewSprite		);
			}
		}

		//	Layouts.
		{
			this->m_Sprites[spr::enm_At::Layouts]->AddMeasure(		tls::Vec4<double>(758, 296, 205, 70)			);		//	Recbord



			for (int i = 0; i < 1; ++i)
			{
				sf::Sprite* _NewSprite = new sf::Sprite();



				_NewSprite->setTexture(		_Textures_[12]	);			

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).Second		,
															this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).Fourth		)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::Layouts]->g_Measures()->at(i).Fourth / 2.0		);



				this->m_Sprites[spr::enm_At::Layouts]->AddSprite(			_NewSprite		);
			}
		}

		//	OldCartoonFont.
		{
			this->m_Sprites[spr::enm_At::OldCartoonFont]->AddMeasure(tls::Vec4<double>(0, 0, 66.0, 100.0));	//	Blank for covering :D



			int			_Aux_			= -1;
			int			_NoLetter_Row_	= 20;



			for (	int i = 0;
						i < 128;
						++i	)
			{
				sf::Sprite*		_NewSprite = new sf::Sprite();

				if (	(i % _NoLetter_Row_) == 0	)
				{
					++_Aux_;
				}



				_NewSprite->setTexture(_Textures_[24]);

				_NewSprite->setTextureRect(	sf::IntRect(	(i - (_Aux_ * _NoLetter_Row_)) * this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Third	,
															_Aux_ * this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Fourth							,
															this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Third										,
															this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Fourth									)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Third / 2.0,
										this->m_Sprites[spr::enm_At::OldCartoonFont]->g_Measures()->at(0).Fourth / 2.0);



				this->m_Sprites[spr::enm_At::OldCartoonFont]->AddSprite(_NewSprite);
			}	
		}

		//	CommonFont.
		{
			//	Zipper.
			{
				//	Skipping some characters.
				{
					for (int i = 0; i < 97; ++i)
					{
						this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(tls::Vec4<double>(0, 0, 0.0, 0.0));
					}
				}

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(0, 0, 69, 88)			);	//	a: 97
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(69, 0, 77, 119)		);	//	b: 98
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(146, 0, 76, 84)		);	//	c: 99
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(222, 0, 72, 123)		);	//	d: 100
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(294, 0, 78, 85)		);	//	e: 101

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(372, 0, 60, 124)		);	//	f: 102
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(432, 0, 73, 130)		);	//	g: 103
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(505, 0, 73, 125)		);	//	h: 104
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(578, 0, 21, 102)		);	//	i: 105
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(599, 0, 50, 119)		);	//	j: 106

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(649, 0, 63, 115)		);	//	k: 107
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(712, 0, 49, 114)		);	//	l: 108
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(761, 0, 124, 76)		);	//	m: 109
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(885, 0, 75, 78)		);	//	n: 110
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(0, 119, 78, 78)		);	//	o: 111

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(78, 119, 69, 125)		);	//	p: 112
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(147, 84, 69, 125)		);	//	q: 113
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(216, 123, 70, 83)		);	//	r: 114
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(286, 123, 77, 83)		);	//	s: 115
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(363, 124, 53, 114)	);	//	t: 116

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(416, 130, 80, 78)		);	//	u: 117
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(496, 130, 83, 77)		);	//	v: 118
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(579, 119, 119, 82)	);	//	w: 119
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(698, 115, 85, 84)		);	//	x: 120
				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(783, 76, 75, 112)		);	//	y: 121

				this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(	tls::Vec4<double>(858, 78, 78, 78)		);	//	z: 122


				//	Skipping some characters.
				{
					for (int i = 123; i < 128; ++i)
					{
						this->m_Sprites[spr::enm_At::CommonFont]->AddMeasure(tls::Vec4<double>(0, 0, 0.0, 0.0));
					}
				}
			}



			for (	int i = 0;
						i < 128;
						++i	)
			{
				sf::Sprite*		_NewSprite = new sf::Sprite();



				_NewSprite->setTexture(	_Textures_[25]	);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(	this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(0).Third / 2.0,
										this->m_Sprites[spr::enm_At::CommonFont]->g_Measures()->at(0).Fourth / 2.0);



				this->m_Sprites[spr::enm_At::CommonFont]->AddSprite(_NewSprite);
			}	
		}
	}
	inline void			Ld_Sprites_FNF(			const std::array<sf::Texture, Arr_FNF_Txtr_Size>&	_FNF_Textures_		)
	{
		//	- - - - - - - - - - - - - - - - - - -
		//			Friday Night Funking
		//	- - - - - - - - - - - - - - - - - - -

		//	FNF_Arrows.
		{
			//	Compress.
			{
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(0, 310, 154, 154)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(0, 155, 154, 154)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(0, 0, 154, 154)	);

				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(155, 310, 154, 154)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(155, 156, 154, 154)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(155, 0, 154, 154)		);

				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(410, 300, 50, 44)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(360, 300, 50, 44)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(310, 300, 50, 44)	);

				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(410, 345, 50, 64)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(360, 345, 50, 64)	);
				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddMeasure(	tls::Vec4<double>(310, 345, 50, 64)	);
			}

		

			for (	int i = 0; i < 12; ++i	)
			{
				sf::Sprite*			_NewSprite = new sf::Sprite();



				_NewSprite->setTexture(						_FNF_Textures_[0]		);

				_NewSprite->setTextureRect(sf::IntRect(		this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).First		,
															this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).Third		,
															this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::FNF_Arrows]->g_Measures()->at(i).Fourth / 2.0		);

				this->m_Sprites[spr::enm_At::FNF_Arrows]->AddSprite(		_NewSprite	);
			}
		}

		//	FNF_Glows.
		{
			this->m_Sprites[spr::enm_At::FNF_Glows]->AddMeasure(	tls::Vec4<double>(310, 0, 300, 300)	);
			


			for (	int i = 0; i < 1; ++i	)
			{
				sf::Sprite*			_NewSprite = new sf::Sprite();



				_NewSprite->setTexture(						_FNF_Textures_[0]		);

				_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).First	,
															this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).Second	,
															this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).Third	,
															this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).Fourth	)	);

				_NewSprite->setOrigin(						this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).Third / 2.0		,
															this->m_Sprites[spr::enm_At::FNF_Glows]->g_Measures()->at(i).Fourth / 2.0		);

				this->m_Sprites[spr::enm_At::FNF_Glows]->AddSprite(		_NewSprite	);
			}
		}

		//	[FNF Characters]
		{
			//	-----------------------
			//		Soft GirlFriend
			//	-----------------------
			{
				//	Compress.
				{
					//	..::Iddle::..
					{
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(406, 575, 352, 574, 0, -5)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(758, 575, 345, 575, -6, -4)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1103, 575, 339, 574, -9, -5)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1442, 575, 337, 573, -8, -6)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(0, 1162, 309, 564, -7, -15)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(309, 1162, 313, 570, -8, -8)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(622, 1162, 322, 579, -9, 0)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(944, 1162, 331, 572, -8, -7)	);
					}

					//	..::Left::..
					{
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(754, 0, 368, 570, -2, 0)		);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1122, 0, 362, 564, 0, -5)		);
					}

					//	..::Down::..
					{
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(0, 0, 376, 508, -4, -61)		);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(376, 0, 378, 509, 0, -60)		);
					}

					//	..::Up::..
					{								
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1275, 1162, 353, 653, -4, 90)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1628, 1162, 356, 641, 0, 73)	);
					}

					//	..::Right::..
					{
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(1484, 0, 390, 575, 65, 28)	);
						this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddMeasure(	tls::Vec6<double>(0, 575, 406, 587, 63, 40)		);
					}
				}

				

				for (	int i = 0; i < 16; ++i	)
				{
					sf::Sprite*			_NewSprite = new sf::Sprite();



					_NewSprite->setTexture(						_FNF_Textures_[1]		);

					_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->g_Measures()->at(i).First		,
																this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->g_Measures()->at(i).Second	,
																this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->g_Measures()->at(i).Third		,
																this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->g_Measures()->at(i).Fourth	)	);

					this->m_Sprites[spr::enm_At::FNF_GirlFriendSoft]->AddSprite(		_NewSprite	);
				}
			}



			//	-----------------------
			//		Soft BoyFriend
			//	-----------------------
			{
				//	Compress.
				{
					//	..::Iddle::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(3798, 1898, 378, 414, -3, -22)	);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(4176, 1898, 381, 416, -1, -20)	);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(4557, 1898, 380, 421, -3, -15)	);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(4937, 1898, 387, 434, 0, -2)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(5324, 1898, 386, 436, -1, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(5324, 1898, 386, 436, -1, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(5324, 1898, 386, 436, -1, 0)		);
					}

					//	..::Left::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(0, 986, 401, 429, 0, 0)			);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(401, 986, 383, 427, -19, -2)		);
					}

					//	..::Down::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(6341, 508, 398, 379, 0, -55)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(6739, 508, 387, 384, -7, -50)		);
					}

					//	..::Up::..
					{								
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(3126, 986, 421, 449, 0, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(3547, 986, 415, 449, 0, 0)		);
					}

					//	..::Right::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(1568, 986, 390, 427, -10, -10)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddMeasure(	tls::Vec6<double>(1958, 986, 390, 430, -10, -5)		);
					}
				}

				

				for (	int i = 0; i < 15; ++i	)
				{
					sf::Sprite*			_NewSprite = new sf::Sprite();



					_NewSprite->setTexture(						_FNF_Textures_[2]		);

					_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->g_Measures()->at(i).First	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->g_Measures()->at(i).Second	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->g_Measures()->at(i).Third	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->g_Measures()->at(i).Fourth	)	);

					this->m_Sprites[spr::enm_At::FNF_BoyFriendSoft]->AddSprite(		_NewSprite	);
				}
			}



			//	-----------------------
			//	  Cassette Girl Clone
			//	-----------------------
			{
				//	Compress.
				{
					//	..::Iddle::..
					{
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1942, 10, 354, 745, 0, -22)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(2306, 10, 354, 745, 0, -22)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(2670, 10, 344, 749, -10, -19)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3024, 10, 351, 771, -11, -6)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3024, 10, 351, 771, -11, -6)		);

						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3385, 10, 349, 779, -14, -1)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3385, 10, 349, 779, -14, -1)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3744, 10, 342, 780, -14, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3744, 10, 342, 780, -14, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4096, 10, 332, 779, -14, -1)		);

						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4096, 10, 332, 779, -14, -1)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4438, 10, 332, 777, -14, -2)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4780, 10, 334, 777, -14, -2)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5124, 10, 332, 777, -14, -2)		);
					}

					//	..::Left::..
					{
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5466, 10, 450, 776, 92, -12)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5926, 10, 450, 776, 92, -12)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(6386, 10, 471, 789, 105, -4)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(6867, 10, 473, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(6867, 10, 473, 796, 104, 0)		);

						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(7350, 10, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(7350, 10, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(10, 816, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(10, 816, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(495, 816, 475, 796, 104, 0)		);

						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(495, 816, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(980, 816, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1465, 816, 475, 796, 104, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1950, 816, 475, 796, 104, 0)		);
					}

					//	..::Down::..
					{
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(10, 10, 324, 674, 0, -44)			);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(10, 10, 324, 674, 0, -44)			);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(344, 10, 313, 693, -11, -32)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(667, 10, 308, 702, -16, -26)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(667, 10, 308, 702, -16, -26)		);

						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(985, 10, 309, 703, -16, -26)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(985, 10, 309, 703, -16, -26)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1304, 10, 309, 703, -16, -26)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1304, 10, 309, 703, -16, -26)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(1623, 10, 309, 703, -16, -26)		);
					}

					//	..::Up::..
					{								
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(2875, 3211, 297, 833, 0, 20)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3182, 3211, 297, 833, 0, 20)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3489, 3211, 279, 845, -11, 27)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3778, 3211, 285, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3778, 3211, 285, 849, -14, 30)	);
																												 
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4073, 3211, 283, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4073, 3211, 283, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4366, 3211, 280, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4366, 3211, 280, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4656, 3211, 280, 849, -14, 30)	);
																											  	 
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4656, 3211, 280, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4946, 3211, 280, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5236, 3211, 280, 849, -14, 30)	);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5526, 3211, 280, 849, -14, 30)	);
					}

					//	..::Right::..
					{
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(2435, 816, 385, 789, 0, -14)			);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(2830, 816, 385, 789, 0, -14)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3225, 816, 394, 785, -2, -16)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3629, 816, 399, 784, -3, -17)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(3629, 816, 399, 784, -3, -17)		);
																							
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4038, 816, 401, 781, -3, -19)			);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4038, 816, 401, 781, -3, -19)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4449, 816, 400, 795, -3, -10)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4449, 816, 400, 795, -3, -10)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4859, 816, 400, 805, -3, -4)		);
																							
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(4859, 816, 400, 805, -3, -4)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5269, 816, 400, 803, -3, -6)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(5679, 816, 400, 809, -3, 0)		);
						this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddMeasure(	tls::Vec6<double>(6089, 816, 400, 782, -3, -18)		);
					}
				}

			

				for (	int i = 0; i < 66; ++i	)
				{
					sf::Sprite*			_NewSprite = new sf::Sprite();



					_NewSprite->setTexture(						_FNF_Textures_[3]		);

					_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->g_Measures()->at(i).First		,
																this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->g_Measures()->at(i).Second		,
																this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->g_Measures()->at(i).Third		,
																this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->g_Measures()->at(i).Fourth		)	);

					this->m_Sprites[spr::enm_At::FNF_CassetteGirlClone]->AddSprite(	_NewSprite	);
				}
			}


			//	-----------------------
			//		   BoyFriend
			//	-----------------------
			{
				//	Compress.
				{
					//	..::Iddle::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(0, 2344, 406, 392, -1, -20)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(0, 2344, 406, 392, -1, -20)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(416, 2344, 408, 393, 0, -19)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(416, 2344, 408, 393, 0, -19)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(834, 2344, 405, 398, -3, -14)		);

						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(834, 2344, 405, 398, -3, -14)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1249, 2344, 410, 411, -1, -1)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1249, 2344, 410, 411, -1, -1)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);

						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1669, 2344, 408, 412, -2, 0)		);
					}

					//	..::Left::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(0, 988, 383, 406, 11, -6)			);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(0, 988, 383, 406, 11, -6)			);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
																								  
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
																										
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(393, 988, 374, 404, 0, -8)		);
					}

					//	..::Down::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(6640, 509, 374, 357, -1, -55)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(6640, 509, 374, 357, -1, -55)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);

						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);

						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(7024, 509, 373, 362, 0, -50)		);
					}

					//	..::Up::..
					{								
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3580, 988, 369, 446, -53, 31)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3580, 988, 369, 446, -53, 31)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
																								   		
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
																								  		
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(3959, 988, 376, 441, -48, 26)		);
					}

					//	..::Right::..
					{
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1929, 988, 408, 405, -42, -9)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(1929, 988, 408, 405, -42, -9)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
																								   		
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
																										
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
						this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddMeasure(	tls::Vec6<double>(2347, 988, 408, 407, -41, -7)		);
					}
				}

				

				for (	int i = 0; i < 70; ++i	)
				{
					sf::Sprite*			_NewSprite = new sf::Sprite();



					_NewSprite->setTexture(						_FNF_Textures_[4]		);

					_NewSprite->setTextureRect(	sf::IntRect(	this->m_Sprites[spr::enm_At::FNF_BoyFriend]->g_Measures()->at(i).First	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriend]->g_Measures()->at(i).Second	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriend]->g_Measures()->at(i).Third	,
																this->m_Sprites[spr::enm_At::FNF_BoyFriend]->g_Measures()->at(i).Fourth	)	);

					this->m_Sprites[spr::enm_At::FNF_BoyFriend]->AddSprite(		_NewSprite	);
				}
			}
		}
	}

	inline void			Ld_RenderTexture()
	{
		//	----------------------------=
		//	The "ends in ..." is always added by one.
		//	For example, <Ends in 146> actually ended in 145,
		//	but to avoid problems and so it is just added one more pixel.
		//	----------------------------------------------------------------=
		int			_Current_ = 0;


		//	StL_Contents.
		{
			//	Drawing part.
			{
				for (	int i = 0;
						i < this->m_TotalKind;
						++i	)
				{
					//	Back.
					{
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(0)->setPosition(i * this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Third, 0);
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(0)->setColor(	sf::Color(	tls::GetDarkRGB(i + 1, 1)	,
																											tls::GetDarkRGB(i + 1, 2)	, 
																											tls::GetDarkRGB(i + 1, 3)	, 
																											255							)	);
																			
						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(0)		);
					}

					//	Spikes.
					{
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(1)->setPosition(i * this->m_Sprites[spr::enm_At::StL_Base] ->g_Measures()->at(1).Third, 0);
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(1)->setColor(	sf::Color(	0xff, 0xff, 0x00, 255)	);
						
						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(1)		);
					}

					//	Front blank.
					{
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(3)->setPosition(i * this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(3).Third, 0);

						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(3)		);
					}

					//	Front.
					{
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(2)->setPosition(i * this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(2).Third, 0);
						this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(2)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																											tls::GetRGB(i + 1, 2)	, 
																											tls::GetRGB(i + 1, 3)	, 
																											255						)	);
						
						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::StL_Base]->g_Sprites()->at(2)		);
					}
				}



				this->_RenderTexture_.display();
				this->_Texture_ = this->_RenderTexture_.getTexture();
				this->_Texture_.setSmooth(true);
			}

			//	Texturing part.
			{
				for (	int i = 0;
						i < this->m_TotalKind;
						++i	)
				{
					sf::Sprite* _NewSprite	= new sf::Sprite();



					_NewSprite->setTexture(			_Texture_			);

					_NewSprite->setTextureRect(sf::IntRect(		i * this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Third,	 0	,
																this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Third 			,
																this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Fourth			)	);

					_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Third / 2.0		,
												this->m_Sprites[spr::enm_At::StL_Base]->g_Measures()->at(0).Fourth / 2.0	);



					this->m_Sprites[spr::enm_At::StL_Contents]->AddSprite(_NewSprite);
				}
			}



			_Current_	= _Current_ + 145 + 1;
		}
			
		//	PoC_Contents.
		{
			//	Drawing part.
			{
				for (	int i = 0;
						i < this->m_TotalKind;
						++i	)
				{
					//	Back.
					{
						this->m_Sprites[spr::enm_At::PoC_Base]->g_Sprites()->at(0)->setPosition(i * this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Third, 146);
						this->m_Sprites[spr::enm_At::PoC_Base]->g_Sprites()->at(0)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																											tls::GetRGB(i + 1, 2)	, 
																											tls::GetRGB(i + 1, 3)	, 
																											255							)	);
																			
						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::PoC_Base]->g_Sprites()->at(0)		);
					}

					//	Spikes.
					{
						this->m_Sprites[spr::enm_At::PoC_Base]->g_Sprites()->at(1)->setPosition(i * this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(1).Third, 146);
						
						this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::PoC_Base]->g_Sprites()->at(1)		);
					}
				}



				this->_RenderTexture_.display();
				this->_Texture_ = this->_RenderTexture_.getTexture();
				this->_Texture_.setSmooth(true);
			}

			//	Texturing part.
			{
				for (	int i = 0;
						i < 10;
						++i	)
				{
					sf::Sprite* _NewSprite	= new sf::Sprite();



					_NewSprite->setTexture(			_Texture_			);

					_NewSprite->setTextureRect(		sf::IntRect(	(i * this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Third)		,
																	_Current_																	, 
																	this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Third			,
																	this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Fourth			)	);

					_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Third / 2.0		,
												this->m_Sprites[spr::enm_At::PoC_Base]->g_Measures()->at(0).Fourth / 2.0	);



					this->m_Sprites[spr::enm_At::PoC_Contents]->AddSprite(	_NewSprite	);
				}
			}



			_Current_		= _Current_ + 27 + 1;
		}

		//	Fc_Splash & Fc_Frojectiles.
		{
			//	--- List ---
			//		>	First is always the Splash.
			//			Second is the Frojectile. 
			int			_At_OffSet_		= spr::enm_FcSplash::SplashAmount * 4;
			int			_PreCurrent_	= 0;



			//	Splash.
			{			
				//	Drawing part.
				{
					_PreCurrent_		= _Current_;
					for (	int k = 0; k < spr::enm_FcSplash::SplashAmount; ++k	)
					{
						for (	int i = 0;
								i < this->m_TotalKind;
								++i	)
						{
							//	Color.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k)->setPosition(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k).Third, _Current_	);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																													tls::GetRGB(i + 1, 2)	, 
																													tls::GetRGB(i + 1, 3)	, 
																													255						)	);
																					
								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k)		);
							}

							//	Shadow.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 1)->setPosition(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k + 1).Third, _Current_);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 1)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																														tls::GetRGB(i + 1, 2)	, 
																														tls::GetRGB(i + 1, 3)	, 
																														255						)	);

								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 1)		);
							}

							//	Color.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 2)->setPosition(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k + 2).Third, _Current_);
																					
								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 2)		);
							}

							//	DrawLine.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 3)->setPosition(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k + 3).Third, _Current_);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 3)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																														tls::GetRGB(i + 1, 2)	, 
																														tls::GetRGB(i + 1, 3)	, 
																														255						)	);

								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(k + 3)		);
							}
						}



						_Current_ = _Current_ + this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k).Fourth;
					}
					_Current_		= _PreCurrent_;
					


					this->_RenderTexture_.display();
					this->_Texture_ = this->_RenderTexture_.getTexture();
					this->_Texture_.setSmooth(true);
				}

				//	Texturing part.
				{
					for (	int k = 0; k < spr::enm_FcSplash::SplashAmount; ++k	)
					{
						for (	int i = 0;	
								i < this->m_TotalKind; 
								++i	)
						{
							sf::Sprite* _NewSprite	= new sf::Sprite();



							_NewSprite->setTexture(			_Texture_			);

							_NewSprite->setTextureRect(		sf::IntRect(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k * 4).Third, _Current_		,
																			this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k * 4).Third 					,
																			this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k * 4).Fourth					)	);

							_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k * 4).Third / 2.0		,
														this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k * 4).Fourth / 2.0		);



							this->m_Sprites[spr::enm_At::Fc_Splash]->AddSprite(	_NewSprite	);
						}



						_Current_		= _Current_ + this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(k).Fourth;
					}
				}

				++_Current_;
			}

			//	Frojectile.
			{	
				//	Drawing part.
				{
					_PreCurrent_	= _Current_;
					for (	int k = 0; k < spr::enm_FcSplash::FrojectileAmount; ++k	)
					{
						for (	int i = 0;
								i < this->m_TotalKind;
								++i	)
						{
							//	Color.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4))->setPosition(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Third, _Current_		);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4))->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																																		tls::GetRGB(i + 1, 2)	, 
																																		tls::GetRGB(i + 1, 3)	, 
																																		255						)	);
																					
								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4))		);
							}

							//	Shadow.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 1)->setPosition(		i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4) + 1).Third, _Current_		);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 1)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																																tls::GetRGB(i + 1, 2)				, 
																																tls::GetRGB(i + 1, 3)				, 
																																255									)	);

								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 1)		);
							}

							//	Color.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 2)->setPosition(		i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4) + 2).Third, _Current_	);
																					
								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(	_At_OffSet_ + (k * 4) + 2)		);
							}

							//	DrawLine.
							{
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 3)->setPosition(		i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4) + 3).Third, _Current_	);
								this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 3)->setColor(	sf::Color(	tls::GetRGB(i + 1, 1)	,
																																tls::GetRGB(i + 1, 2)				, 
																																tls::GetRGB(i + 1, 3)				, 
																																255									)	);

								this->_RenderTexture_.draw(		*this->m_Sprites[spr::enm_At::Fc_Base]->g_Sprites()->at(_At_OffSet_ + (k * 4) + 3)		);
							}
						}



						_Current_		= _Current_ + this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Fourth;
					}				
					_Current_		= _PreCurrent_;



					this->_RenderTexture_.display();
					this->_Texture_ = this->_RenderTexture_.getTexture();
					this->_Texture_.setSmooth(true);
				}

				//	Texturing part.
				{
					for (	int k = 0; k < spr::enm_FcSplash::FrojectileAmount; ++k	)
					{
						for (	int i = 0;	
								i < this->m_TotalKind; 
								++i	)
						{
							sf::Sprite* _NewSprite	= new sf::Sprite();



							_NewSprite->setTexture(			_Texture_			);

							_NewSprite->setTextureRect(		sf::IntRect(	i * this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Third, _Current_		,
																			this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Third 					,
																			this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Fourth					)	);

							_NewSprite->setOrigin(		this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Third / 2.0		,
														this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Fourth / 2.0		);



							this->m_Sprites[spr::enm_At::Fc_Frojectiles]->AddSprite(	_NewSprite	);
						}



						_Current_		= _Current_ + this->m_Sprites[spr::enm_At::Fc_Base]->g_Measures()->at(_At_OffSet_ + (k * 4)).Fourth;
					}
				}



				++_Current_;
			}
		}

		//	this->_RenderTexture_.getTexture().copyToImage().saveToFile("a.png");
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline SpriteContainer*			g_Sprite(	int What	)
	{
		if (	(What < 0) || ((spr::enm_At::Size - 1) < What)	)
		{
			throw		std::runtime_error("Can't find that sprite in container.");
		}

		return		this->m_Sprites[What];
	}
	
//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline int				g_Data(int What)
	{
		switch (	What	)
		{
		case	1:
			return		this->m_TotalKind;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
};



//	- - - - - - - - - - - - - - - - - - ->



class	TextContainer
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Sprite Variables
//	-------------------------------------------
private:
	sf::Text		_MyText;

//	-------------------------------------------
//				Measures Variables
//	-------------------------------------------
private:



//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	TextContainer()
	{

	}

	~TextContainer()
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
class	TextFactory
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Fonts
//	-------------------------------------------
private:
	std::vector<sf::Font*>		_Fonts_;

//	-------------------------------------------
//					Texts
//	-------------------------------------------
private:
	std::vector<sf::Text*>		_Texts_;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	TextFactory()
	{
		
	}

	~TextFactory()
	{
		//	Erasing _Fonts_...
		{
			while (!this->_Fonts_.empty())
			{
				delete		this->_Fonts_.at(0);
				this->_Fonts_.erase(this->_Fonts_.begin() + 0);
			}
		}

		//	Erasing _Texts_...
		{
			while (!this->_Texts_.empty())
			{
				delete		this->_Texts_.at(0);
				this->_Texts_.erase(this->_Texts_.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Ld_Text()
	{
		const std::string						_R_L_ = "_Resources_\\LetterAndStuff\\";



		//	/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/

		//	Mojangles font.
		{		
			sf::Font*		_NewFont = new sf::Font();
			_NewFont->loadFromFile(_R_L_ + "Mojangles.ttf");

			this->_Fonts_.push_back(	_NewFont	);
		}

		//	Vcr font.
		{		
			sf::Font*		_NewFont = new sf::Font();
			_NewFont->loadFromFile(_R_L_ + "vcr.ttf");

			this->_Fonts_.push_back(	_NewFont	);
		}

		//	/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/

		//	Creating a text.
		{
			this->_Texts_.push_back(new sf::Text());
			this->_Texts_[0]->setFont(*this->_Fonts_[fnt::enm_At::Mojangles]);


			this->_Texts_.push_back(new sf::Text());
			this->_Texts_[1]->setFont(*this->_Fonts_[fnt::enm_At::Vcr]);
			this->_Texts_[1]->setCharacterSize(45);
			this->_Texts_[1]->setOutlineColor(sf::Color(0, 0, 0, 255));
			this->_Texts_[1]->setOutlineThickness(3.0f);
		}
	}


//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline sf::Text*	g_Text(int _What)
	{
		return		this->_Texts_[_What];
	}
	inline sf::Font*	g_Font(int _What)
	{
		return		this->_Fonts_[_What];
	}
};
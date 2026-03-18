//	--- RubDaShen 2023 ----------

/*
	vec and Vec are the same, don't complex about it!

	Abreviations:
		vec			vector
		Arr			Array
		SB			SoundBuffer
		txtr		texture
		txt			text
		fnt			font
		msc			music
		tLd			toLoad
		mx			maximum
		spr			sprite
		Amt			Amount
		Dgt			Digit
		Prc			Porcentual
		Rnd			Random
		val			value
		Nmb			number
		Anm			animation
		tck			Tick
		spw			Spawn
		nStc		non-static
		Stc			static
		tgg			trigger

		Cnt			Counter
		Trg			Target
		Ttl			Total
		Prg			Progress

		xP			x Position
		yP			y Position
		xM			x Movement
		yM			y Movement
		xS			x Speed
		yS			y Speed
		xA			x Aceleration
		yA			y Aceleration
		xF			x Factor
		yF			y Factor

		HasF		Has Finished

	NamesAbreviations:
		spA					spriteArray
		nwTm				nowTime
		ftrTm				futureTime
		tckVal				tickValue
		lpCnt				loopCounter
		LyP					last yPos
		auxVal				auxiliar Value
		ColorChoosen_B		Color choosen Bom-o-Bom
		ColorChoosen_F		Color choosen Frozen Candy
		SA					Star Adventure
		FNF					Friday Night Funkin'
		Charc				Character
		BSpr				BlackSprite
		dt					Draw Technique
		Dbg					Debug Option
		vSp					vector of Sprites
*/

#include		"StarAdventure.h"



//	..:: - STATICS - ::..
int						TheCandy::_Cnt_ObjID_ = 1;
double					TheCandy::_Gravity_ = -0.18;
double					TheCandy::_MatchingSensibility_ = 0.25;

double					_Controller_Logic::_gLpVal_ = 144;
int						_Controller_Logic::_ogLpV_ = 144;
double					_Controller_Logic::_fdTime_ = 1.0;
double					_Controller_Logic::_dTime_ = 1.0 / _Controller_Logic::_ogLpV_;


//	..:: - MAIN FUNCTION - ::..
int			main(void)
{
	System::Console::CursorVisible = false;
	std::srand(std::time(0));


	bool			isFullScreen = false;

	int				WindowWidth = ((isFullScreen) ? sf::VideoMode::getDesktopMode().width : 1800);
	int				WindowHeight = ((isFullScreen) ? sf::VideoMode::getDesktopMode().height : 1000);

	double			yGround = WindowHeight;
	double			xGround = WindowWidth / 2.0;



	_Basic_Mouse* _Mouse_ = new _Basic_Mouse();
	_Basic_KeyBoard* _KeyBoard_ = new _Basic_KeyBoard();

	DrawFactory* _Draw_ = new DrawFactory(xGround, yGround, isFullScreen);
	SpriteFactory* _Sprites_ = new SpriteFactory();
	TextFactory* _Text_ = new TextFactory();
	_Controller_Logic* _Logic_ = new _Controller_Logic(_KeyBoard_);
	SoundFactory* _Sound_ = new SoundFactory(_Logic_);
	ShaderFactory* _Shaders_ = new ShaderFactory();

	Camera* _Camera_ = new Camera(0.0, yGround / 2.0, _Draw_->g_WindowBounds(1), _Draw_->g_WindowBounds(2));
	OnScreen* _OnScreen_ = new OnScreen(_Draw_, _Sprites_, _Shaders_);

	sql::SQLConnector* _SQLConnector_ = new sql::SQLConnector();




	//////////////////////////////////////////////////////////////////////
	//																	//
	//	-------------------------------------------------------------	//
	//	|															|	//
	//	|	- * # Loading Side - Everything has its time. # * -		|	//
	//	|															|	//
	//	-------------------------------------------------------------	//
	//																	//
	//////////////////////////////////////////////////////////////////////
	LoadingCenter* MyLoader = new LoadingCenter(_Draw_, _Sprites_, _Camera_, _Shaders_, _SQLConnector_);



	const int									ASz_Testures = 3;
	std::array<sf::Texture, ASz_Testures>		Arr_Loading_Textures{};

	//	Load the sprites and textures.
	{
		const std::string						_R_T_Ld = "_Resources_\\Textures\\Loading\\";
		const std::string						_R_L_ = "_Resources_\\LetterAndStuff\\";



		//	Loading Page !									- - -	[0]
		{
			Arr_Loading_Textures[0].loadFromFile(_R_T_Ld + "Blank.png");
			Arr_Loading_Textures[1].loadFromFile(_R_T_Ld + "SandTimer.png");
			Arr_Loading_Textures[2].loadFromFile(_R_L_ + "_MyFont_.png");
		}

		_Sprites_->Ld_Sprites_Loading(Arr_Loading_Textures);

		MyLoader->Ld_All();
		MyLoader->g_Terminal()->Write("Testures all loaded!\n");
	}





	//////////////////////////////////////////////////////////
	//														//
	//	-------------------------------------------------	//
	//	|												|	//
	//	|		- * # Star Adventure v 0.0.3 # * -		|	//
	//	|												|	//
	//	-------------------------------------------------	//
	//														//
	//////////////////////////////////////////////////////////

	std::array<sf::Texture, Arr_SA_Txtr_Size>			Arr_SA_Textures{};
	std::array<sf::SoundBuffer, Arr_SA_SB_Size>			Arr_SndBuffers{};





	//////////////////////////////////////////////////////////
	//														//
	//	-------------------------------------------------	//
	//	|												|	//
	//	|	- * # Friday Night Funking v 0.0.2 # * -	|	//
	//	|												|	//
	//	-------------------------------------------------	//
	//														//
	//////////////////////////////////////////////////////////

	std::array<sf::Texture, Arr_FNF_Txtr_Size>		Arr_FNF_Textures{};





	MyLoader->StartThreads(Arr_SA_Textures, Arr_FNF_Textures, Arr_SndBuffers);
	MyLoader->StartLoading();



	_Sprites_->Ld_Sprites(Arr_SA_Textures);
	_Sprites_->Ld_Sprites_FNF(Arr_FNF_Textures);
	_Sprites_->Ld_RenderTexture();
	_Sound_->Ld_Sounds(Arr_SndBuffers);
	_Shaders_->Ld_Shaders();
	_Text_->Ld_Text();
	_OnScreen_->Ld_Everything();
	_OnScreen_->SetLogoAnimation_FIO(0, 0);



	StarAdventure* _MyGame_ = new StarAdventure(_Draw_, _OnScreen_, _Mouse_, _KeyBoard_, _Sound_, _Sprites_, _Camera_, _Shaders_, _Text_, _SQLConnector_, _Logic_);

	_MyGame_->TextureLoadingFinished();
	_MyGame_->StartAdventure();

	return 0;
}

/*
	Template for a timer	:
		if ((theTime.asMicroseconds() / 1000.0) >= ftrTm_Logic)
			{
				nowTm_Logic = theTime.asMicroseconds();



				//	..::	Code	::..



				//	..::	Timer	::..

				ftrTm_Logic = (theTime.asMicroseconds() / 1000.0) + tckVal_Logic - ((theTime.asMicroseconds() - nowTm_Logic) / 1000.0);
			}
*/
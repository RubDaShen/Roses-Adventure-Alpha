#pragma once


#define	GAME_LOOP_VALUE					(144)
#define	GAME_LOOP_LOGIC					(1000.0 / GAME_LOOP_VALUE)


#define _TARGET_UNDEFINED				(2147483647)
#define _COMMON_ITR_USAGE				(0xDDDFFF)


#define	_Pi_							(3.141592653589793)
#define _e_								(2.718281828459045)
#define	_Mx_Int7						(128)


#define	Arr_SA_Txtr_Size				(26)
#define	Arr_SA_SB_Size					(42)
#define	Arr_FNF_Txtr_Size				(5)
#define	Arr_Testures_Size				(3)



//	-----------------------------------
//		About definitons and logic
//	-----------------------------------
namespace		def
{
	enum	enm_Directions
	{
		_None_	,
		Up		,
		Down	,
		Left	,
		Right
	};
	enum	enm_Triggers
	{
		NotInitialized	= 1	,
		Waiting				,
		Activated			,
		_Unknown
	};
	enum	enm_CameraSet
	{
		_InvalidMotion_		= 0	,
		SmoothZoom				,
		xSmoothMove				,
		ySmoothMove				,
		ZoomCap					
	};
	enum	enm_CameraLimits
	{
		Cieling			= 1,
		Floor			= 2,
		LeftBorder		= 3,
		RightBorder		= 4,
	};
		
	enum	enm_Status
	{
		IsOff		= 0,
		IsOn		= 1,
		IsDone		= 2
	};
	enum	enm_Defines
	{
		_NOT_FOUND = -1,
		_NOT_INITIALIZED = -2,
		_USE_DEFAULT = -3,
		_SKIP_THIS = -4,
		_SEARCH_ALL = 100,
	};
	
	enum	enm_ObjectType
	{
		Generic							= 0,
		ObjCandy						= 1,
		CrushParticle					= 2,
		ScoreParticle					= 3,
		ScoreInText						= 4,
		Prospform						= 5,
		StrippedLightningParticle		= 6,
		StrippedTraits_AnimatedObject	= 7,
		GlowParticle					= 8,
		FishBubble						= 9,
		FishTarget						= 10,
		FishEntity						= 11,
		Frojectile						= 12,
		Fc_Splash						= 13,
		LightBon						= 14,
		FireWorkEntity					= 15,
		FireWorkEmber					= 16,
		PoppingCracker					= 17,
		Coin							= 18,
	};
}
	


//	-------------------
//		About games
//	-------------------
namespace		STA_
{	
	enum	enm_ItemID
	{
		Invalid			= 0	,

		CommonCandy		,
		StrippedH		,
		StrippedV		,
		WrappedCandy	,
		WrappedFuse		,
		JellyFish		,
		FrozenCandy		,
		BomOBom			,
		Starlight		,
		FireWorkRocket	,
		BubbleGum		,
		PoppingCandy	,

		CupCake_1		,
		CupCake_2		,
		CupCake_3		,
		CupCake_4		,
		CupCake_5		,
	};
	enum	enm_KindID
	{
		_Invalid	= 0	,
	
		_Red		,
		_Orange		,
		_Yellow		,
		_Green		,
		_Aquamarine	,
		_Cyan		,
		_Blue		,
		_Purple		,
		_Pink		,
		_Chocolate	,
		_White		,
	};
		
	enum	enm_ButtonID
	{
		PlayButton		= 0	,
		SettingsButton		,
		BackButton			,
		MapButton			,
		ArcadeButton		,
		CloseButton			,
		PlayLevelButton		,
	};
	enum	enm_Rooms
	{
		_Terminal	= 0	,
		Transition		,
		LogoPart		,
		MainMenu		,
		Lobby			,
		Map				,
		World			,
		LevelTransition	,
		Level			,
		Arcade			,
	
	
	
		Rooms_Size		
	};
	enum	enm_BackGrounds
	{
		BlankScene = 0		,
		ConfrontTheReality	,
		Stranded			,
		NightCity			,
		NeonCity			,
		ChooseYourAdventure
	};
	enum	enm_Worlds
	{
		LollipopMeadow			= 1	,
		TastyHills				= 2	,
		SugarSticksBluesward	= 3	,
		ChocolateMountains		= 4	,
		CitricCanyon			= 5	,
		LemonadeLake			= 6	,
		EasterHills				= 7	,
		SodaBeach				= 8	
	};

	enum	enm_Definitions
	{
		TotalKind	= 10,
	};
}

namespace		FNF_
{
	enum	enm_ChrStates
	{
		Iddle = 0	,
		Left		,
		Down		,
		Up			,
		Right
	};
			
	enum	enm_Characters
	{
		SoftGF					,
		SoftBF					,
		CassetteGirlClone		,
		BoyFriend				,
	};
}
#pragma once

#include		<iostream>
#include		<string>
#include		<vector>

#include		"thyObject.h"
#include		"Tools_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"LogicalController.h"





//	Enum of score
enum ScoreSys
{
	CustomScore = 1		,
	NormalCandy			,
	BasicMatch			,
	StrippedMatch		,
	WrappedMatch		,
	Fishy4Match			,
	Fishy5Match			,
	FrozenC6Match		,
	FrozenC7Match		,
	BomOBomMatch		,
	StarlightMatch		,
	FireworkMatch		,
	BubbleGumMatch		,
	PopppingCandyMatch	,

	Bonus_FrozenNotFound	,
	Bonus_BonOBomNotFound
};


//	Part of the level HUD.
class		LevelHUD : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	int				m_WhatHUD = 0;

	//	Branches.
	int				m_BranchesID	= 0;

	//	Combo Box.
	int				m_ComboBoxID	= 0;
	double			xP_ComboBox		= 0.0, yP_ComboBox = 0.0;
	double			xP_ScoreBox		= 0.0, yP_ScoreBox = 0.0;

	//	Score Box.
	int				m_ScoreBoxID	= 0;
	double			W_ComboBox		= 0.0, H_ComboBox = 0.0;
	double			W_ScoreBox		= 0.0, H_ScoreBox = 0.0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums
//	-------------------------------------------
public:
	enum	enm_WhatHUD
	{
		Default				= 0,
		LollipopMeadow		= 1
	};

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	LevelHUD(	double _xP, double _yP		, 
				SpriteFactory* _Sprites_	,
						int _What_HUD		) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_WhatHUD			= _What_HUD;


		switch (this->m_WhatHUD)
		{
		case 1:
			this->m_BranchesID		= 0;
			this->_W				= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(0).Third;
			this->_H				= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(0).Fourth;

			this->m_ComboBoxID		= 1;
			this->xP_ComboBox		= -630,		this->yP_ComboBox = 580;
			this->W_ComboBox		= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(1).Third;
			this->H_ComboBox		= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(1).Fourth;

			this->m_ScoreBoxID		= 2;
			this->xP_ScoreBox		= -630,		this->yP_ScoreBox = 370;
			this->W_ScoreBox		= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(2).Third;
			this->H_ScoreBox		= _Sprites_->g_Sprite(spr::enm_At::LevelHUD)->g_Measures()->at(2).Fourth;

			break;
		}
	}

	~LevelHUD()
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
	inline int			g_SpritePosition(int _What)
	{
		switch (_What)
		{
		case 1:
			return		(this->xP + (this->_W / 2.0));

		case 2:
			return		(this->yP - (this->_H / 2.0));
		}
	}
	inline int			g_SpritePosition_Combo(int _What)
	{
		switch (_What)
		{
		case 1:
			return		(this->xP_ComboBox);

		case 2:
			return		(this->yP_ComboBox);
		}
	}
	inline int			g_SpritePosition_Score(int _What)
	{
		switch (_What)
		{
		case 1:
			return		(this->xP_ScoreBox);

		case 2:
			return		(this->yP_ScoreBox);
		}
	}

	inline int			g_IDs(int _What)
	{
		switch (	_What	)
		{
		case 1:
			return		this->m_BranchesID;

		case 2:
			return		this->m_ComboBoxID;

		case 3:
			return		this->m_ScoreBoxID;
		}
	}
};

//	Just about scores purposes.
class		ScoreParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const double		$_RainbowScore	= 9000.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_CharacterID		= 0;
	int			m_ChangeSpeed		= false;
	int			m_KindID			= 0;

	double		m_OriginSprite_X	= 0.0;
	double		m_OriginSprite_Y	= 0.0;

//	-------------------------------------------
//				Special effect
//	-------------------------------------------
private:
	int			Cnt_RainbowCase		= 0;

	double		_RainbowSpeed_		= 0.0;
	double		_Time_				= 5.0;
	double		_ScalarVar_			= 5.0;
	double		_FixedScale_		= 0.45;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	ScoreParticle(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::ScoreParticle)
	{

	}
	ScoreParticle(double _xP, double _yP, int _CharacterID, int _KindID, int _ActualScore) : thyObject(_xP, _yP, def::enm_ObjectType::ScoreParticle)
	{
		this->m_CharacterID		= _CharacterID;
		this->m_KindID			= _KindID;

		this->yA				= -0.055;
		this->yS				= 3.75;

		this->Alpha_s			= -4.0;



		//	Rainbow Speed :D
		{
			this->_RainbowSpeed_ = (_ActualScore / this->$_RainbowScore) * 2.25;



			if (this->_RainbowSpeed_ >= 30.0)
			{
				this->_RainbowSpeed_ = 30.0;
			}
		}

		//	Scaling effect.
		{
			this->_FixedScale_		= this->_FixedScale_ + (_ActualScore / (this->$_RainbowScore * 25.0));
			if (this->_FixedScale_ >= 1.175)
			{
				this->_FixedScale_ = 1.175;
			}
			this->xFct				= this->yFct = this->_FixedScale_;

			this->_ScalarVar_		= this->_ScalarVar_ - (_RainbowSpeed_);



			if (this->_ScalarVar_ >= 4.25)
			{
				this->_ScalarVar_ = 2500.0;
			}

			if (this->_ScalarVar_ <= 0.85)
			{
				this->_ScalarVar_ = 0.85;
			}
		}

		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);
	}

	~ScoreParticle()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				AnimateScore()
	{
		//	Position.
		{
			//	Falling randomizer :D
			if (this->m_ChangeSpeed == 1)
			{
				this->yA = this->yA + ((	(tls::Random(1, 5) * 2.5) / 1000.0	) * _Controller_Logic::_fdTime_	);

				this->m_ChangeSpeed = 2;
			}



			this->yS	= this->yS + (this->yA * _Controller_Logic::_fdTime_);
			this->yP	= this->yP + (this->yS * _Controller_Logic::_fdTime_);
		}

		//	Opacity.
		{
			if (this->yS <= 0.0)
			{
				if (this->m_ChangeSpeed < 1)
				{
					++this->m_ChangeSpeed;
				}



				if (	(this->A_alpha + this->Alpha_s) > 0.0	)
				{
					this->A_alpha = A_alpha + (this->Alpha_s * _Controller_Logic::_fdTime_	);
				}
				else
				{
					this->A_alpha = 0.0;
				}
			}
		}

		//	Rainbow effect.
		{
			switch (	this->Cnt_RainbowCase	)
			{
			case 0:
				if (	(this->G_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) < 255	)
				{
					this->G_col = this->G_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->G_col = 255;
					++this->Cnt_RainbowCase;
				}

				break;

			case 1:
				if (	(this->R_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) > 0	)
				{
					this->R_col = this->R_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->R_col = 0;
					this->Cnt_RainbowCase++;
				}

				break;

			case 2:
				if (	(this->B_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) < 255	)
				{
					this->B_col = this->B_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->B_col = 255;
					this->Cnt_RainbowCase++;
				}

				break;

			case 3:
				if (	(this->G_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) > 0	)
				{
					this->G_col = this->G_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->G_col = 0;
					++this->Cnt_RainbowCase;
				}

				break;

			case 4:
				if (	(this->R_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) < 255	)
				{
					this->R_col = this->R_col + (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->R_col = 255;
					++this->Cnt_RainbowCase;
				}

				break;

			case 5:
				if (	(this->B_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_)) > 0	)
				{
					this->B_col = this->B_col - (this->_RainbowSpeed_ * _Controller_Logic::_fdTime_);
				}
				else
				{
					this->B_col = 0;
					this->Cnt_RainbowCase = 0;
				}

				break;
			}
		}

		//	Scale decisions.
		{
			this->_Time_		= this->_Time_ + (0.02 * _Controller_Logic::_fdTime_);

			

			if (this->m_ChangeSpeed == 2)
			{
				this->_ScalarVar_ = this->_ScalarVar_ + 0.2;
			}


			this->xFct	= ((std::sin(3.5 * this->_Time_)) / (this->_ScalarVar_ * this->_Time_)) + this->_FixedScale_;
			this->yFct	= this->xFct;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_OriginSprite(int _What, double _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_OriginSprite_X = _Val;
			break;

		case 2:
			this->m_OriginSprite_Y = _Val;
			break;
		}
	}

	inline int			g_ID(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_CharacterID;

		case 2:
			return this->m_KindID;
		}
	}
	inline double		g_OriginSprite(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_OriginSprite_X;

		case 2:
			return this->m_OriginSprite_Y;
		}
	}
	inline int			g_SpritePosition(int _What)
	{
		switch (_What)
		{
		case 1:
			return	 (this->xP + this->g_OriginSprite(_What));

		case 2:
			return	 (this->yP - this->g_OriginSprite(_What));
		}
	}
};
class		ScoreInText : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_Padding			= 0;
	int				m_CharacterSize		= 0;
	int				yP_StringOffSet		= 0;

	int				m_ItrTime_Pulse		= 0;
	int				m_KindOfText		= 0;
	
	std::string		m_String;

//	-------------------------------------------
//				Animation Effects
//	-------------------------------------------
private:





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	ScoreInText(	double _xP, double _yP, int _What_Text		) : thyObject(_xP, _yP, def::enm_ObjectType::ScoreInText)
	{
		//	For many texts types.
		this->m_KindOfText		= _What_Text;
		switch (	_What_Text	)
		{
		case 1:
			this->m_Padding			= -225;
			this->m_CharacterSize	= 25;
			this->yP_StringOffSet	= -100;

			this->m_ItrTime_Pulse	= 36;

			this->m_String			= "Combo x";

			break;

		case 2:
			this->m_Padding			= -225;
			this->m_CharacterSize	= 25;
			this->yP_StringOffSet	= -100;

			this->m_ItrTime_Pulse	= 36;

			this->m_String			= "Score";
			break;
		}

		//	Final touches to the position.
		//	this->xP		= this->xP+ this->m_Padding;

	}

	~ScoreInText()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	About pulsing animation.
		this->xFct		= this->xFct + ((1.0 - this->xFct) / this->m_ItrTime_Pulse);
		this->yFct		= this->xFct;
	}

	inline void			Pulse(double _Factor)
	{
		//	Pulse animation may look agressively interrupted
		//	if the given factor is less than the current factor.
		if (	_Factor <= this->xFct	)
		{
			return;
		}

		//	Go for it!
		switch (	this->m_KindOfText	)
		{ 
		case 1:
			if (	2.0 <= _Factor	)
			{
				_Factor = 2.0;
			}

			this->xFct		= _Factor;
			this->yFct		= _Factor;
			break;

		case 2:
			if (	3.25 <= _Factor	)
			{
				_Factor = 3.25;
			}

			this->xFct		= _Factor;
			this->yFct		= _Factor;
			break;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int				g_KindOfText()
	{
		return		this->m_KindOfText;
	}
	inline int				g_CharacterSize()
	{
		return		this->m_CharacterSize;
	}
	inline int				g_TextPosition(		int _What, int _FontSize	)
	{
		switch (	_What	)
		{
		case 1:
			return		(	this->xP - (_FontSize * 0.5)	);

		case 2:
			return		(	this->yP + (_FontSize) + this->yP_StringOffSet	);
		}
	}

	inline std::string&		g_String()
	{
		return		this->m_String;
	}
};



class		StatsPanelBack : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	StatsPanelBack(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~StatsPanelBack()
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
class		StatsPanelFront : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	StatsPanelFront(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~StatsPanelFront()
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
/*	||	 ||
	||	 ||
	|| G ||
	|| O ||
	||	 ||
	|| T ||
	|| O ||
	||	 ||
	||	 ||	*/
class		_Controller_StatsPanel
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum	enm_Draw
	{
		_BackPanel		= 0	,
		_FrontPanel			,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		xP		= 0.0, yP = 0.0;

	int			Combo	= 0;

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	StatsPanelBack*					m_Back;
	StatsPanelFront*				m_Front;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_StatsPanel(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;



		this->LoadAll();
	}

	~_Controller_StatsPanel()
	{
		this->DeleteAll();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			LoadAll()
	{
		this->m_Back	= new StatsPanelBack(0.0, 0.0);
		this->m_Back->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::InGamePanels)->g_Measures()->at(0).Third);
		this->m_Back->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::InGamePanels)->g_Measures()->at(0).Fourth);

		this->m_Front	= new StatsPanelFront(0.0, 0.0);
		this->m_Front->s_SpriteMeasures(1, this->_Sprites_->g_Sprite(spr::enm_At::InGamePanels)->g_Measures()->at(1).Third);
		this->m_Front->s_SpriteMeasures(2, this->_Sprites_->g_Sprite(spr::enm_At::InGamePanels)->g_Measures()->at(1).Fourth);
	}
	inline void			DeleteAll()
	{
		tls::Delete(this->m_Back);
		tls::Delete(this->m_Front);
	}

	inline void			SetUpEnviroment(	int xBoardPos, int yBoardPos		, 
											int BoardWidth, int BoardHeight		, 
											int GridBound						)
	{
		//	Set the positions.
		{
			int		MarginLeft	= 0;
			this->xP	= xBoardPos - (GridBound * 0.5) - MarginLeft - (this->m_Back->g_SpriteMeasures(1));
			this->yP	= yBoardPos - (BoardHeight * GridBound * 0.5) + (this->m_Back->g_SpriteMeasures(2) * 0.5);
		}

		//	Alligning the panels.
		{
			double		FrontPanel_xOffSet	= (this->m_Back->g_SpriteMeasures(1) - this->m_Front->g_SpriteMeasures(1)) * 0.5;
			double		FrontPanel_yOffSet	= (this->m_Back->g_SpriteMeasures(2) - this->m_Front->g_SpriteMeasures(2)) * 0.5;



			this->m_Back->s_PositionPrp(1, this->xP);
			this->m_Back->s_PositionPrp(2, this->yP);

			this->m_Front->s_PositionPrp(1, this->m_Back->g_PositionPrp(1) + FrontPanel_xOffSet);
			this->m_Front->s_PositionPrp(2, this->m_Back->g_PositionPrp(2) - FrontPanel_yOffSet);
		}
		
		//	Set up the color.
		{
			this->m_Back->s_ColorPrp(1, 0x17);
			this->m_Back->s_ColorPrp(2, 0xd8);
			this->m_Back->s_ColorPrp(3, 0xfb);

			this->m_Front->s_ColorPrp(1, 0xaf);
			this->m_Front->s_ColorPrp(2, 0xd7);
			this->m_Front->s_ColorPrp(3, 0xf1);
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		
	}

	inline void			LogicDis()
	{
		//	Put here all the animations and logic.
		this->Animate();
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	_BackPanel.
		if (	enm_Draw::_BackPanel == What	)
		{
			this->_What_Sprite_			= spr::enm_At::InGamePanels;
			this->_What_Kind_			= 0;
			


			//	Set position to the sprite.
			_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Back->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)),
																										tls::FixPos_Y(	this->m_Back->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);
			
			//	Applying color properties.
			_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(		this->m_Back->g_ColorPrp(1)	,
																														this->m_Back->g_ColorPrp(2)	,
																														this->m_Back->g_ColorPrp(3)	,
																														this->m_Back->g_ColorPrp(4)	)	);

	
			
			//	Draw it.
			this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)		);
		}

		//	_FrontPanel.
		if (	enm_Draw::_FrontPanel == What	)
		{
			this->_What_Sprite_			= spr::enm_At::InGamePanels;
			this->_What_Kind_			= 1;
			


			//	Set position to the sprite.
			_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Front->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																										tls::FixPos_Y(	this->m_Front->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);
			
			//	Applying color properties.
			_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(		this->m_Front->g_ColorPrp(1)	,
																														this->m_Front->g_ColorPrp(2)	,
																														this->m_Front->g_ColorPrp(3)	,
																														this->m_Front->g_ColorPrp(4)	)	);

	
			
			//	Draw it.
			this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)		);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			GatherInfo(int _Combo)
	{
		this->Combo		= _Combo;
	}
	inline double		GetPosition(int What)
	{
		switch (What)
		{
		case 1:
			return		this->xP;

		case 2:
			return		this->yP;
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
class		_Controller_Score
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Scores			= 0,
		_ScoreLayout	= 1
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const double			WidthFont		= 60.0;		//	66.0
	const double			CandyWidth		= 90.0;
	const double			CandyHeight		= 90.0;

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<ScoreParticle*>		m_Scores;
	std::vector<ScoreInText*>		m_ScoresInText;

	LevelHUD*						m_HUD			= nullptr;
	_Controller_StatsPanel*			m_StatsPanel	= nullptr;

//	-------------------------------------------
//				Statics and more
//	-------------------------------------------
private:
	double				m_MatchSensibility		= 0.1;
	double				m_Gravity				= -0.15;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_CurrentScore		= 0.0;

	bool			m_CascadeIsActive	= false;

	int				m_MatchSeq = 0, m_Swoints = 0;
	int				m_SwointsVoicePhase = 1;
	int				Cnt_CascadeActive = 0, Trg_CascadeActive = (0.5 / _Controller_Logic::_dTime_);

//	-------------------------------------------
//				OtherVariables
//	-------------------------------------------
private:
	double			xP_Board = 0.0, yP_Board = 0.0;
	int				BoardWidth = 0, BoardHeight = 0;
	double			GridBounds = 0.0;

//	-------------------------------------------
//				Helpers and auxiliars
//	-------------------------------------------
private:
	std::string		_MyStr_;

	double			_OriginX_	= 0.0, _OriginY_ = 0.0;

	double			_OffSet_	= 0.0;
	double			_Number_	= 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int					_Score_BasicCandy		= 10;
	int					_Stripped_Bonus			= 5;
	int					_Wrapped_Bonus			= 8;
	int					_Fish4_Bonus			= 4;
	int					_Fish5_Bonus			= 4;
	int					_FrozenC6_Bonus			= 8;
	int					_FrozenC7_Bonus			= 10;
	int					_BomOBom_Bonus			= 7;
	int					_StarLight_Bonus		= 6;
	int					_FireWorkRocket_Bonus	= 7;
	int					_BubbleGum_Bonus		= 6;
	int					_PoppingCandy_Bonus		= 8;

	int					_Swoints_Match			= 3;
	int					_Swoints_Stripped		= 10;
	int					_Swoints_Wrapped		= 15;
	int					_Swoints_Fish4			= 5;
	int					_Swoints_Fish5			= 6;
	int					_Swoints_FrozenC6		= 30;
	int					_Swoints_FrozenC7		= 40;
	int					_Swoints_BonOBom		= 25;
	int					_Swoints_StarLight		= 15;
	int					_Swoints_FireWorkRocket	= 15;
	int					_Swoints_BubbleGum		= 10;
	int					_Swoints_PoppingCandy	= 20;

	int					_SwointTarget_Sweet		= 50;
	int					_SwointTarget_Tasty		= 100;
	int					_SwointTarget_Delicious	= 250;
	int					_SwointTarget_Divine	= 500;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	TextFactory*			_Text_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	SoundFactory*			_Sound_		= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_What_Measure_		= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_Score(	DrawFactory* _Draw_Ptr_		,
						SpriteFactory* _Sprite_Ptr	,
						TextFactory* _Text_Ptr		,
						SoundFactory* _Sound_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr_;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Text_		= _Text_Ptr;
		this->_Sound_		= _Sound_Ptr;
	}

	~_Controller_Score()
	{
		tls::DeleteVector(this->m_Scores);
		tls::DeleteVector(this->m_ScoresInText);

		tls::Delete(this->m_HUD);
		tls::Delete(this->m_StatsPanel);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddCombo()
	{
		//	This is for the combo number addition.
		this->_MyStr_.clear();
		this->_MyStr_		= tls::IntToStr(this->m_MatchSeq);

		this->_OffSet_		= (	((this->_MyStr_.size() - 1) * this->WidthFont) / 2.0		);
		this->_OriginX_		= (	((this->_MyStr_.size() - 1) * this->WidthFont) / 2.0		);



		for (	int i = 0; 
				i < this->_MyStr_.size(); 
				++i	)
		{			
			this->_OriginY_		= 0.0;



			this->m_Scores.push_back(	new ScoreParticle(	this->m_ScoresInText[0]->g_PositionPrp(1) + (this->WidthFont * i) - _OffSet_	,
															this->m_ScoresInText[0]->g_PositionPrp(2) - (this->CandyHeight / 2.0)			,
															static_cast<int>(this->_MyStr_[i])												,
															STA_::enm_KindID::_White, this->m_MatchSeq * this->_Score_BasicCandy			)	);

			this->m_Scores.at(this->m_Scores.size() - 1)->s_OriginSprite(1, this->_OriginX_);
			this->m_Scores.at(this->m_Scores.size() - 1)->s_OriginSprite(2, this->_OriginY_);



			this->_OriginX_		= this->_OriginX_ - this->WidthFont;
		}


		//	About animation for the combo and score text.
		this->m_ScoresInText[0]->Pulse(		1.0 + (this->m_MatchSeq / 250.0)			);
	}
	inline void			AddScore(double _xP, double _yP, int _Score_Type, double _Score, bool _CountAsMatch, int _KindID)
	{
		//	Finding the score.
		{
			this->m_CascadeIsActive		= true;
			this->Cnt_CascadeActive		= 0;



			//	Checking the match type.
			{
				//	Count as match?
				if (	_CountAsMatch	)
				{
					//	Add sequence.
					++this->m_MatchSeq;
					this->m_Swoints = this->m_Swoints + _Swoints_Match;

					//	Combo.
					this->AddCombo();

					//	Sound play.
					this->_Sound_->Play(	snd::SndSys::MatchSound, this->m_MatchSeq	);
				}

				//	Selecting the match type.
				switch (_Score_Type)
				{
				case ScoreSys::CustomScore:
					this->_Number_		= _Score;
					break;

				case ScoreSys::NormalCandy:
					this->_Number_		= this->_Score_BasicCandy;
					break;

				case ScoreSys::BasicMatch:
					this->_Number_		= (this->_Score_BasicCandy * 3.0 * this->m_MatchSeq);
					break;

				case ScoreSys::StrippedMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 4.0) + this->_Stripped_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_Stripped;
					break;

				case ScoreSys::WrappedMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_Wrapped_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_Wrapped;
					break;

				case ScoreSys::Fishy4Match:
					this->_Number_		= (((this->_Score_BasicCandy * 4.0) + this->_Fish4_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_Fish4;
					break;

				case ScoreSys::Fishy5Match:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_Fish5_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_Fish5;
					break;

				case ScoreSys::FrozenC6Match:
					this->_Number_		= (((this->_Score_BasicCandy * 6.0) + this->_FrozenC6_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_FrozenC6;
					break;

				case ScoreSys::FrozenC7Match:
					this->_Number_		= (((this->_Score_BasicCandy * 7.0) + this->_FrozenC7_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_FrozenC7;
					break;

				case ScoreSys::BomOBomMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_BomOBom_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_BonOBom;
					break;

				case ScoreSys::StarlightMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_StarLight_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_StarLight;
					break;

				case ScoreSys::FireworkMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_FireWorkRocket_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_FireWorkRocket;
					break;

				case ScoreSys::BubbleGumMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 5.0) + this->_BubbleGum_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_BubbleGum;
					break;

				case ScoreSys::PopppingCandyMatch:
					this->_Number_		= (((this->_Score_BasicCandy * 6.0) + this->_PoppingCandy_Bonus) * this->m_MatchSeq);
					this->m_Swoints		= this->m_Swoints + this->_Swoints_PoppingCandy;
					break;




				case ScoreSys::Bonus_FrozenNotFound:
					this->_Number_		= (1000.0 * ((this->m_MatchSeq <= 0) ? 1 : this->m_MatchSeq));
					break;

				case ScoreSys::Bonus_BonOBomNotFound:
					this->_Number_		= (500.0 * ((this->m_MatchSeq <= 0) ? 1 : this->m_MatchSeq));
					break;

				default:
					throw std::runtime_error("ScoreSys couldn't find your score request...");
					break;
				}
			}



			this->m_CurrentScore = this->m_CurrentScore + this->_Number_;
		}
		
		//	Animations.
		{
			if (	0 < this->_Number_	)
			{
				//	this->m_ScoresInText[1]->Pulse(1.0 + (this->_Number_ / 10000.0));
			}
		}

		//	Score in characters.
		{
			this->_MyStr_.clear();
			this->_MyStr_		= tls::IntToStr(this->_Number_);

			this->_OffSet_		= (	(((this->_MyStr_.size() - 1) * this->WidthFont) - CandyWidth) / 2.0	);
			this->_OriginX_		= (	((this->_MyStr_.size() - 1) * this->WidthFont ) / 2.0					);



			for (	int i = 0; 
					i < this->_MyStr_.size(); 
					++i	)
			{			
				this->_OriginY_		= 0.0;



				this->m_Scores.push_back(	new ScoreParticle(	_xP + (this->WidthFont * i) - _OffSet_	,
																_yP - (this->CandyHeight / 2.0)			,
																static_cast<int>(this->_MyStr_[i])			,
																_KindID, this->_Number_	)					);
				
				this->m_Scores.at(this->m_Scores.size() - 1)->s_OriginSprite(1, this->_OriginX_);
				this->m_Scores.at(this->m_Scores.size() - 1)->s_OriginSprite(2, this->_OriginY_);



				this->_OriginX_		= this->_OriginX_ - this->WidthFont;
			}
		}
	}
	inline void			TrackMatch()
	{
		TheCandy::_MatchingSensibility_	= (		this->m_MatchSensibility + (this->m_MatchSeq * 0.075)	);
		TheCandy::_Gravity_				= (		this->m_Gravity - (this->m_MatchSeq * 0.0025)			);

		//	Checking and limiting the matching sensibility.
		if (	50.0 < TheCandy::_MatchingSensibility_	)
		{
			//	TheCandy::_MatchingSensibility_ = 50.0;
		}

		//	And for gravity.
		if (	TheCandy::_Gravity_ < -1.5	)
		{
			TheCandy::_Gravity_ = -1.5;
		}
	}
	
	inline void			Animate()
	{
		//	Score animation.
		for (	int i = 0; 
				i < this->m_Scores.size();
				++i	)
		{
			this->m_Scores[i]->AnimateScore();



			if (this->m_Scores[i]->g_ColorPrp(4) <= 0.0)
			{
				tls::EraseElement<ScoreParticle*>(this->m_Scores, i);
			}
		}

		//	Combo animation.
		for (	int i = 0; 
				i < this->m_ScoresInText.size();
				++i	)
		{
			this->m_ScoresInText[i]->Animate();
		}

		//	Enviroment and logic.
		this->TrackMatch();

		//	Score Layout and display.
		this->m_StatsPanel->GatherInfo(this->m_MatchSeq);
		this->m_StatsPanel->LogicDis();
	}


	inline void			CascadeActive()
	{
		this->m_CascadeIsActive		= true;
		this->Cnt_CascadeActive		= 0;
	}	
	inline void			ClockCascade()
	{
		//	This is just the counter.
		{
			if (this->Cnt_CascadeActive < this->Trg_CascadeActive)
			{
				++this->Cnt_CascadeActive;
			}
			else
			{
				this->m_CascadeIsActive		= false;

				this->Cnt_CascadeActive		= this->m_MatchSeq = this->m_Swoints = 0;
				this->m_SwointsVoicePhase	= 1;
			}
		}
	}

	inline void			Voice(	bool SwitchMade	)
	{
		//	Voice selector.
		{
			if (	(this->_SwointTarget_Sweet <= this->m_Swoints) && (this->m_SwointsVoicePhase == 1)	)
			{
				this->_Sound_->Play(snd::SndSys::DelightfulVoices, 1);
				this->m_SwointsVoicePhase	= 2;
			}
			else
			{
				if (	(this->_SwointTarget_Tasty <= this->m_Swoints) && (this->m_SwointsVoicePhase == 2)	)
				{
					this->_Sound_->Play(snd::SndSys::DelightfulVoices, 2);
					this->m_SwointsVoicePhase	= 3;
				}
				else
				{
					if (	(this->_SwointTarget_Delicious <= this->m_Swoints) && (this->m_SwointsVoicePhase == 3)	)
					{
						this->_Sound_->Play(snd::SndSys::DelightfulVoices, 3);
						this->m_SwointsVoicePhase	= 4;
					}
					else
					{
						if (	(this->_SwointTarget_Divine <= this->m_Swoints) && (this->m_SwointsVoicePhase == 4)	)
						{
							this->_Sound_->Play(snd::SndSys::DelightfulVoices, 4);
							this->m_SwointsVoicePhase	= 5;
						}
					}
				}
			}
		}

		//	Counts.
		if (	SwitchMade	)
		{
			this->m_Swoints				= 0;
			//	this->m_MatchSeq			= 0;
			this->m_SwointsVoicePhase	= 1;

			if (	this->m_Swoints < 0	)
			{
				this->m_Swoints = 0;
			}
		}
	}

//	-------------------------------------------
//				Loading functions
//	-------------------------------------------
public:
	inline void			LoadVariables(double _xP_Board, double _yP_Board, int _BoardWidth, int _BoardHeight, int _GridBounds)
	{
		this->xP_Board		= _xP_Board;
		this->yP_Board		= _yP_Board;
		this->BoardWidth	= _BoardWidth;
		this->BoardHeight	= _BoardHeight;
		this->GridBounds	= _GridBounds;
	}
	inline void			LoadAll()
	{
		this->m_HUD				= new LevelHUD(		0.0, 0.0, this->_Sprites_				, 
													LevelHUD::enm_WhatHUD::LollipopMeadow	);

		this->m_StatsPanel		= new _Controller_StatsPanel(	this->_Draw_, this->_Sprites_	);
		this->m_StatsPanel->SetUpEnviroment(this->xP_Board, this->yP_Board, this->BoardWidth, this->BoardHeight, this->GridBounds);

		for (int i = 0; i < 1; ++i)
		{
			this->m_ScoresInText.push_back(new ScoreInText(this->m_StatsPanel->GetPosition(1), this->m_StatsPanel->GetPosition(2), 1));
		}
	}
	
//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Score.
		if (	enm_Draw::_Scores == What	)
		{
			this->_Container_Size_		= this->m_Scores.size();
			this->_What_Sprite_			= spr::enm_At::ScoreFont;



			for (	int i = 0; 
					i < this->_Container_Size_; 
					++i	)
			{
				this->_What_Kind_		= this->m_Scores[i]->g_ID(1);
				this->_What_Measure_	= 0;



				//	Set the position of the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(this->m_Scores[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(this->m_Scores[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);


				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(		sf::Color(		this->m_Scores[i]->g_ColorPrp(1)	,
																															this->m_Scores[i]->g_ColorPrp(2)	,
																															this->m_Scores[i]->g_ColorPrp(3)	,
																															this->m_Scores[i]->g_ColorPrp(4)	)	);

				//	Origin to scale perfectly.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setOrigin(	this->m_Scores[i]->g_OriginSprite(1) + (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Measure_).Third / 2.0	)	,
																											this->m_Scores[i]->g_OriginSprite(2) + (_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(this->_What_Measure_).Fourth / 2.0	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Scores[i]->g_VisualPrp(1)		,
																											this->m_Scores[i]->g_VisualPrp(2)		);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}

		//	Score Layout.
		if (	enm_Draw::_ScoreLayout == What	)
		{
			this->m_StatsPanel->Draw(_Controller_StatsPanel::enm_Draw::_BackPanel);
			this->m_StatsPanel->Draw(_Controller_StatsPanel::enm_Draw::_FrontPanel);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_MatchSequence()
	{
		return this->m_MatchSeq;
	}

	inline std::vector<ScoreParticle*>&			g_Scores()
	{
		return this->m_Scores;
	}
};
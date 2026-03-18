#pragma once

#include		<vector>

#include		"thyObject.h"
#include		"Tools_.h"
#include		"_MyIncludes_.h"

#include		"SoundFactory.h"



class	Fnk_Character : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	std::vector<int>	m_AnmData;

	int					m_CharacterID	= def::enm_Defines::_NOT_INITIALIZED;
	int					m_AnmID			= def::enm_Defines::_NOT_INITIALIZED;

	int					Cnt_Animation	= 0, Trg_Animation = 16;

	bool				m_Hide = false;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Fnk_Character(double _xP, double _yP, bool _Mirror, double _Scale, int _CharacterID, bool _Hide) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_AnmID			= FNF_::enm_ChrStates::Iddle;
		this->m_CharacterID		= _CharacterID;
		this->xFct				= this->yFct = _Scale;
		this->m_Hide			= _Hide;



		if (_Mirror)
		{
			this->xFct = this->xFct * -1;
		}
	}

	~Fnk_Character()
	{
		
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		if (this->Cnt_Animation < this->Trg_Animation)
		{
			++this->Cnt_Animation;
		}
		else
		{
			this->m_AnmID = FNF_::enm_ChrStates::Iddle;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			SetAnimation(int _What)
	{
		this->Cnt_Animation		= 0;
		this->Trg_Animation		= this->m_AnmData[_What];
		this->m_AnmID			= _What;
	}
	inline void			SetCharacterTiming(std::vector<int> _Settings)
	{
		//	Creating the m_AnmData.
		this->m_AnmData.clear();
		
		for (	int i = 0;
				i < _Settings.size(); 
				++i	)
		{
			this->m_AnmData.push_back(_Settings[i]);
		}
	}

	inline int			g_State()
	{
		int		_State_ = Cnt_Animation;
		if (Cnt_Animation >= Trg_Animation)
		{
			_State_ = Trg_Animation - 1;
		}

		return		_State_;
	}
	inline int			g_CharacterID()
	{
		return		this->m_CharacterID;
	}
	inline int			g_AnmID()
	{
		return		this->m_AnmID;
	}
	inline int			g_SpriteOffSet()
	{
		int		_Amount_	= 0;
		int		_OffSet_	= 0;



		switch (this->m_AnmID)
		{
		case def::enm_Directions::Left:
			_Amount_ = 1;
			break;

		case def::enm_Directions::Down:
			_Amount_ = 2;
			break;

		case def::enm_Directions::Up:
			_Amount_ = 3;
			break;

		case def::enm_Directions::Right:
			_Amount_ = 4;
			break;
		}
		for (	int i = 0;
				i < _Amount_; 
				++i	)
		{
			_OffSet_ = _OffSet_ + this->m_AnmData[i];
		}



		return _OffSet_;
	}
	inline bool			g_Hide()
	{
		return		this->m_Hide;
	}
};
/*	||	 ||
	|| G ||
	|| O ||
	||   ||
	|| T ||
	|| O ||
	||	 ||	*/
class	_Controller_FnkCharacters
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<Fnk_Character*>		m_Characters;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			Tme_AnmRate		= 0.05;
	double			Tme_IddleBack	= Tme_AnmRate * 15;

	int				Cnt_Animation	= 0, Trg_Animation = (GAME_LOOP_VALUE * Tme_IddleBack);





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_FnkCharacters()
	{

	}

	~_Controller_FnkCharacters()
	{
		//	Deleting Characters !
		{
			while (!this->m_Characters.empty())
			{
				delete this->m_Characters[0];
				this->m_Characters.erase(this->m_Characters.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddCharacter(	double _xP, double _yP, bool _Mirror, double _Scale		,
										int _CharacterID, std::vector<int> _TimeState			,
										bool _Hide												)
	{
		this->m_Characters.push_back(	new Fnk_Character(_xP, _yP, _Mirror, _Scale, _CharacterID, _Hide)	);

		this->m_Characters[this->m_Characters.size() - 1]->SetCharacterTiming(_TimeState);
	}
	inline void			SetCharacterState(int _What, int _State)
	{
		if (	_What == def::enm_Defines::_SEARCH_ALL	)
		{
			for (	int i = 0; 
					i < this->m_Characters.size(); 
					++i	)
			{
				if (	this->m_Characters[i]->g_AnmID() == FNF_::enm_ChrStates::Iddle	)
				{
					this->m_Characters[i]->SetAnimation(FNF_::enm_ChrStates::Iddle);
				}
			}
		}
		else
		{
			this->m_Characters[_What]->SetAnimation(_State);
		}
	}

	inline void			AnimateChatacters()
	{
		//	Animation interval.
		if (	!(this->Cnt_Animation % static_cast<int>(GAME_LOOP_VALUE * this->Tme_AnmRate))	)
		{
			//	Animation!
			for (	int i = 0; 
					i < this->m_Characters.size(); 
					++i	)
			{
				this->m_Characters[i]->Animate();
			}
		}
		
		//	Iddle setter.
		if (this->Cnt_Animation < this->Trg_Animation)
		{
			++this->Cnt_Animation;
		}
		else
		{
			this->Cnt_Animation = 0;

			this->SetCharacterState(def::enm_Defines::_SEARCH_ALL, FNF_::enm_ChrStates::Iddle);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<Fnk_Character*>&		g_Characters()
	{
		return		this->m_Characters;
	}
};
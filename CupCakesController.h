#pragma once

#include		<vector>

#include		"thyObject.h"
#include		"_MyIncludes_.h"
#include		"Tools_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"SoundFactory.h"
#include		"TheCandy.h"



class		_Controller_CupCakes
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Structs!
//	-------------------------------------------
private:
	struct		_Cupcake_x_Health_
	{
		//	-------------------------------------------
		//					Variables
		//	-------------------------------------------
		TheCandy*		_Cupcake_			= nullptr;
		int				_CurrentHealth_		= 0;

		//	-------------------------------------------
		//			Constructors and Destructor
		//	-------------------------------------------
		_Cupcake_x_Health_(		TheCandy* Cupcake_Linker, int CurrentHealth	)
		{
			this->_Cupcake_			= Cupcake_Linker;
			this->_CurrentHealth_	= CurrentHealth;
		}

		~_Cupcake_x_Health_()
		{

		}
	};

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<_Cupcake_x_Health_*>			m_CupCakes;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	bool			m_StopSound		= false;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	SoundFactory*			_Sounds_	= nullptr;

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
	_Controller_CupCakes(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	,	 
							SoundFactory* _Sound_Ptr							)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sounds_		= _Sound_Ptr;
	}

	~_Controller_CupCakes()
	{
		tls::DeleteVector(this->m_CupCakes);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddCupCake(		TheCandy* _Cupcake_, int Toughness		)
	{
		if (	_Cupcake_->g_ItemID() < STA_::enm_ItemID::CupCake_1	)
		{
			_Cupcake_->s_ItemID(			STA_::enm_ItemID::CupCake_1 + Toughness - 1				);
			this->m_CupCakes.push_back(	new _Cupcake_x_Health_(_Cupcake_, _Cupcake_->g_TotalHP())	);
		}
	}
	inline void			CheckNear(	TheCandy* _Candy_	)
	{
		bool		_CupCakeEaten_	= false;
		int			_iPos_ = _Candy_->g_Pos(1), _jPos_ = _Candy_->g_Pos(2);
		this->_Container_Size_ = this->m_CupCakes.size();



		for (	int i = 0; 
				i < this->_Container_Size_; 
				++i	)
		{
			//	>	Cupcake is licorice caged.
			if (	this->m_CupCakes[i]->_Cupcake_->g_HasBlocker(1)	)
			{
				continue;
			}

			_CupCakeEaten_	= false;



			//	Vertical.
			for (	int k = -1; k <= 1; k = k + 2)
			{
				if (	((_iPos_ + k) == this->m_CupCakes[i]->_Cupcake_->g_Pos(1))		&&
						(_jPos_ == this->m_CupCakes[i]->_Cupcake_->g_Pos(2))			)
				{
					_CupCakeEaten_		= true;
				}
			}

			//	Vertical.
			for (	int k = -1; k <= 1; k = k + 2)
			{
				if (	(_iPos_ == this->m_CupCakes[i]->_Cupcake_->g_Pos(1))			&&
						((_jPos_ + k) == this->m_CupCakes[i]->_Cupcake_->g_Pos(2))		)
				{
					_CupCakeEaten_ = true;
				}
			}



			//	If the cupcake's been eaten.
			if (_CupCakeEaten_)
			{
				this->m_CupCakes[i]->_Cupcake_->HitOne_HP();
			}
		}
	}

	inline void			LogicDis()
	{
		this->m_StopSound	= false;



		for (	int i = 0; 
				i < this->m_CupCakes.size(); 
				++i	)
		{
			//	Checking if the candy is still a cupcake or not.
			if (		(this->m_CupCakes[i]->_Cupcake_->g_ItemID() < STA_::enm_ItemID::CupCake_1)			||
						(STA_::enm_ItemID::CupCake_5 < this->m_CupCakes[i]->_Cupcake_->g_ItemID())			||
					this->m_CupCakes[i]->_Cupcake_->g_ObjectID() == def::enm_Defines::_NOT_INITIALIZED		)
			{
				//	Turns out this candy is not a cupcake.
				this->m_CupCakes.erase(this->m_CupCakes.begin() + i);
			}
			else
			{
				//	Checking the health of the cupcake and thus changing
				//	its current ItemID.
				{
					int			_Health_ = this->m_CupCakes[i]->_Cupcake_->g_InitialHP() - 1;
					if (_Health_ < 0)
					{
						_Health_ = 0;
					}

					this->m_CupCakes[i]->_Cupcake_->s_ItemID(	STA_::enm_ItemID::CupCake_1 + _Health_	);
				}

				//	Checking if the cupcake has been damaged.
				//	<Trigger sound>
				{
					if (	this->m_CupCakes[i]->_Cupcake_->g_TotalHP() != this->m_CupCakes[i]->_CurrentHealth_	)
					{
						//	To avoid sound overlaying multiple times.
						if (	!m_StopSound)
						{
							this->_Sounds_->Play(snd::SndSys::CupCake, 1);
							this->m_StopSound	= true;
						}

						this->m_CupCakes[i]->_CurrentHealth_		= this->m_CupCakes[i]->_Cupcake_->g_TotalHP();
					}
				}
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
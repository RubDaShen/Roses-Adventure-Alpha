#pragma once

#include	"thyGrid_Logic.h"
#include	"VisualGridController.h"
#include	"TheSwitcher.h"

#include	"TheCandy.h"
#include	"Tools_.h"
#include	"_MyIncludes_.h"
#include	"SoundFactory.h"
#include	"Camera.h"
#include	"SpriteFactory.h"
#include	"_Basics_KeyBoard.h"
#include	"SpawnPointController.h"

#include	"CrushingParticle.h"
#include	"StrippedController.h"
#include	"FollowingParticle.h"
#include	"WrappedController.h"
#include	"FishController.h"
#include	"FrozenController.h"
#include	"BonOBomController.h"
#include	"FireworkRocketController.h"
#include	"BubbleGumController.h"
#include	"PoppingCandyController.h"
#include	"Scores.h"
#include	"SpecialMixes.h"
#include	"SurpriseController.h"
#include	"CupCakesController.h"
#include	"LogicalController.h"

#include	<vector>



//	/ / / / / / / / / / / / / / / / / / / / / / / / / / //


//					Remembering list !
//	- - - - - - - - - - - - - - - - - - - - - - - - - - -
//	1.	ItemID equals 1 is to normal candies.
//		>	1:	Normal Candies.
//		>	2:	Stripped Horizontal.
//		>	3:	Stripped Vertical.
//		>	4:	Wrapped
//		>	5:	Wrapped Fuse
//	2.	KindID starts from 1.




//	..::Quick Sort Functions::..
inline int			Partition(std::vector<TheCandy*>& _Vec, int _From, int _To)
{
	TheCandy*		Aux = _Vec[_To];
	int				i = _From - 1;



	for (	int j = _From;
			j < _To; 
			++j	)
	{
		if (_Vec[j]->g_Pos(1) >= Aux->g_Pos(1))
		{
			++i;
			std::swap(_Vec[i], _Vec[j]);
		}
	}

	std::swap(_Vec[i + 1], _Vec[_To]);

	return (i + 1);
}
inline void			QuickSort(std::vector<TheCandy*>& _Vec, int _From, int _To)
{
	int				_myAux_ = 0;



	if (_From < _To)
	{
		_myAux_ = Partition(	_Vec, _From, _To			);
		QuickSort(				_Vec, _From, _myAux_ - 1	);
		QuickSort(				_Vec, _myAux_ + 1, _To		);
	}
}

//	..::Insertion Sort Functions::..
inline void			InsertionSort(std::vector<TheCandy*>& _Vec, int _Size)
{
	TheCandy* key		= nullptr;
	int		j			= 0;

    for (	int i = 1; 
			i < _Size; 
			++i	)
	{
        key		= _Vec[i];
        j		= i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (	(j >= 0) && (_Vec[j]->g_Pos(1) >= key->g_Pos(1)))
		{
            _Vec[j + 1] = _Vec[j];
            --j;
        }

		_Vec[j + 1] = key;
    }
}



class	Board : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Candy		= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double		m_GridBound		= 90.0;
	int			m_InvalidIPos	= -9;

//	-------------------------------------------
//				Auxiliary part
//	-------------------------------------------
private:
	//	Generics.
	int						_Size_Candies_ = 0;

	std::vector<std::vector<int>>		_ATs_Row_;
	std::vector<std::vector<int>>		_ATs_Column_;
	std::vector<int>					_ATs_Swapped_;

	//	Vars for DoSpawn().
	int						_Where_ = 0;

	//	Vars for DoCandies().
	bool					_HitIsOffGrid_ = false;
	bool					_CanFall_ = false;

	int						_At_ = 0;
	int						_MySize_ = 0;

	double					_UpTo_ = 10000.0;
	double					_DownTo_ = 0.0;

//	-------------------------------------------
//		Included variables (Of controllers)
//	-------------------------------------------
private:
	VisualGrid***					m_BoardVisual	= nullptr;
	thyGrid_Logic***				m_BoardLogic	= nullptr;

	std::vector<SpawnPoint*>		m_ToSpawn;		//	TO BE DELETED TO BE DELETED TO BE DELETED
	std::vector<TheCandy*>			m_Candies;

//	-------------------------------------------
//				Board settings
//	-------------------------------------------
private:	
	int						m_BoardWidth = 0;
	int						m_BoardHeight = 0;

//	-------------------------------------------
//				Candies settings
//	-------------------------------------------
private:
	double					m_Roof = 100000.0;

//	-------------------------------------------
//					Switching
//	-------------------------------------------
private:
	Switcher*				m_SwitchController = nullptr;

	bool					m_IsSwapping = false;

//	-------------------------------------------
//					Controllers
//	-------------------------------------------
private:
	_Controller_BoardVisual*		m_CntrlBoardVisual	= nullptr;

	_Controller_SpawnPoints*		m_SpawnPoints		= nullptr;
	_Controller_CrushEffect*		m_CrushEffect		= nullptr;

	_Controller_SpecialMixes*		m_SpecialMixes		= nullptr;

	_Controller_Stripped*			m_Strippeds			= nullptr;
	_Controller_SpecialForm*		m_Prospform			= nullptr;
	_Controller_Wrappeds*			m_Wrappeds			= nullptr;
	_Controller_Fish*				m_Fishes			= nullptr;
	_Controller_FrozenCandy*		m_Frozens			= nullptr;
	_Controller_BonOBom*			m_BonOBoms			= nullptr;
	_Controller_FireworkRocket*		m_FireWorks			= nullptr;
	_Controller_BubbleGum*			m_BubbleGums		= nullptr;
	_Controller_PoppingCandy*		m_PoppingCandies	= nullptr;

	_Controller_Score*				m_Scores		= nullptr;
	_Controller_Coin*				m_Coins			= nullptr;
	_Controller_CupCakes*			m_CupCakes		= nullptr;

//	-------------------------------------------
//				External Controllers
//	-------------------------------------------
private:
	_Controller_Logic*				_Logic_			= nullptr;
	Camera*							_Camera_		= nullptr;

	_Basic_Mouse*					_Mouse_			= nullptr;
	_Basic_KeyBoard*				_KeyBoard_		= nullptr;

	DrawFactory*					_Draw_			= nullptr;
	SpriteFactory*					_Sprites_		= nullptr;
	SoundFactory*					_Sounds_		= nullptr;
	TextFactory*					_Text_			= nullptr;
	ShaderFactory*					_Shader_		= nullptr;

	sql::SQLConnector*				_SQL_			= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;

//	-------------------------------------------
//					Command Center
//	-------------------------------------------
private:
	int			m_SpecialCandy		= STA_::enm_ItemID::FrozenCandy;

	bool		m_SpawnCandies		= true;
	bool		m_FreezeBrain		= false;
	bool		m_FreeSwitch		= true;
	bool		m_CrusherDrag		= false;
	bool		m_MagicClick		= false;
	bool		m_LicoriceCage		= false;
	bool		m_CupCakeBaker		= false;
	bool		m_ShowPos			= false;

	bool		m_IsBrandNew		= true;


//	-------------------------------------------
//				Debugger Options !
//	-------------------------------------------
private:
	inline void				PrintBoardInfo()
	{
		System::Console::SetCursorPosition(0, 0);
		std::cout << "kindID | canMatch | IsSideWays | CanFallCandies in this->m_BoardLogic[i][c]: ";
	
		for (int i = 0; i < m_BoardHeight; i = i + 1)
		{
			for (int j = 0; j < m_BoardWidth; j = j + 1)
			{
				// Color selector.
				switch (this->m_BoardLogic[i][j]->g_KindID())
				{
				case 0:
					System::Console::ForegroundColor = System::ConsoleColor::White;
					break;
	
				case 1:
					System::Console::ForegroundColor = System::ConsoleColor::Red;
					break;
	
				case 2:
					System::Console::ForegroundColor = System::ConsoleColor::DarkYellow;
					break;
	
				case 3:
					System::Console::ForegroundColor = System::ConsoleColor::Yellow;
					break;
	
				case 4:
					System::Console::ForegroundColor = System::ConsoleColor::Green;
					break;
	
				case 5:
					System::Console::ForegroundColor = System::ConsoleColor::Cyan;
					break;
	
				case 6:
					System::Console::ForegroundColor = System::ConsoleColor::DarkCyan;
					break;
	
				case 7:
					System::Console::ForegroundColor = System::ConsoleColor::Blue;
					break;
	
				case 8:
					System::Console::ForegroundColor = System::ConsoleColor::DarkMagenta;
					break;
	
				case 9:
					System::Console::ForegroundColor = System::ConsoleColor::Magenta;
					break;
	
				case 10:
					System::Console::ForegroundColor = System::ConsoleColor::Gray;
					break;
				}
	
				// Print system.
				for (int c = 0; c < 3; c++)
				{
					switch (c)
					{
					case 0:
						System::Console::SetCursorPosition((c * 4 * m_BoardWidth) + (j * 2), i + 1);
						std::cout << this->m_BoardLogic[i][j]->g_KindID() << " ";
						break;
	
					case 1:
						System::Console::SetCursorPosition((c * 4 * m_BoardWidth) + (j * 2), i + 1);
						std::cout << this->m_BoardLogic[i][j]->g_Can(2) << " ";
						break;
	
					case 2:
						System::Console::SetCursorPosition((c * 4 * m_BoardWidth) + (j * 2), i + 1);
						std::cout << this->m_BoardLogic[i][j]->g_Is(4) << " ";
						break;
					}
				}
			}
	
		}
	
		System::Console::ForegroundColor = System::ConsoleColor::White;
	}





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	Board(	_Basic_Mouse* _Mouse_Ptr, _Basic_KeyBoard* _KeyBoard_Ptr	, 
			SoundFactory* _Ptr_SoundFactory, Camera* _Camera_Ptr		,		
			DrawFactory* _Draw_Ptr, SpriteFactory* _Sprites_Ptr			,
			TextFactory* _Text_Ptr, ShaderFactory* _Shader_Ptr			,
			sql::SQLConnector* _SQL_Ptr, _Controller_Logic* _Logic_Ptr	) : thyObject()
	{
		this->_Sounds_		= _Ptr_SoundFactory;
		this->_Mouse_		= _Mouse_Ptr;
		this->_KeyBoard_	= _KeyBoard_Ptr;
		this->_Camera_		= _Camera_Ptr;
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprites_Ptr;
		this->_Text_		= _Text_Ptr;
		this->_Shader_		= _Shader_Ptr;
		this->_SQL_			= _SQL_Ptr;
		this->_Logic_		= _Logic_Ptr;

		this->Ld_Controllers();
	}

	~Board()
	{
		this->Del_Board();
		this->Del_SpawnPoints();
		this->Del_Candies();
		this->Del_Controllers();
		this->Del_Switches();
	}

//	-------------------------------------------
//			Board and Candies Logic
//	-------------------------------------------
public:
	inline void			OptimizeAndReduce()
	{
		_Size_Candies_			 = this->m_Candies.size();


		//	Every programmer knows that if a container like an array, 
		//	vector or any is too large, the for loop will take eons.
		//	That's why I decided to 'factorize' in two groups.
		// 
		//	One group of _Row_ and another of _Column_.
		//		_Column_	[0][1][2][3][...] (BoardWidth)
		//					Every vector inside the _Column_ vector contains positions (at)
		//					of the candies of the main vector. This _Column_ vector is
		//					divided by Columns
		//
		//		_Row_
		//			[0]			Every vector inside the _Row_ vector contains 
		//			[1]			positions (at) of the candies of the main vector. 
		//			[2]			This _Row_ vector is divided by Rows.
		//			[3]			Just like _Column_...
		//			[...]
		//			(BoardHeight)
		//	After all, it is just a method I found to be useful and efficient.				
		{
			//	Clear all the values stored.
			{
				for (int i = 0; i < this->_ATs_Column_.size(); ++i)
				{
					this->_ATs_Column_[i].clear();
				}

				for (int i = 0; i < this->_ATs_Row_.size(); ++i)
				{
					this->_ATs_Row_[i].clear();
				}

				_ATs_Swapped_.clear();
			}

			//	Pushing all the values.
			{
				for (int i = 0; i < _Size_Candies_; ++i)
				{
					if (this->m_Candies[i]->g_Pos(1) >= 0)
					{
						this->_ATs_Row_[this->m_Candies[i]->g_Pos(1)].push_back(i);
					}

					if (this->m_Candies[i]->g_Pos(2) >= 0)
					{
						this->_ATs_Column_[this->m_Candies[i]->g_Pos(2)].push_back(i);
					}

					if (this->m_Candies[i]->g_IsSwapping(1))
					{
						_ATs_Swapped_.push_back(i);
					}
				}
			}
		}
	}

	inline void			DoSpawn()
	{
		if (this->m_SpawnCandies)
		{
			this->m_SpawnPoints->DoSpawn(	this->m_Candies		, 
											this->_ATs_Row_		, 
											this->_ATs_Column_	);
		}
	}
	inline void			IandJ()
	{
		for (int c = 0; c < this->m_Candies.size(); ++c)
		{
			// Blockers and canFall property.
			{
				//	Usually, s_Can takes two parameters. The first one is about which
				//	candy property to change and in this case is about Can_ properties.
				//	Second, is the value of that property.


				this->m_Candies[c]->s_Can(1, true);

				//	In this case, if the candy has a blocker (not being a blocker), or 
				//	this candy is being targeted by a fish, or is wrapping-waiting 
				//	or whatever reason, then this candy cannot fall.
				if (	(!this->m_Candies[c]->g_ItemAllowsSomething(3))							||	//	Is a CupCake.
						(this->m_Candies[c]->g_HasBlocker(1))									||	//	Has a blocker.
						(this->m_Candies[c]->g_TargetedByFish())								||	//	Is targeted by a fish.
						(this->m_Candies[c]->g_Fc_Is(1) == 1)									||	//	Is painting.
						(this->m_Candies[c]->g_Fc_Is(2) == 1)									||	//	Is being painted fase 1.
						(this->m_Candies[c]->g_JustTrigger(2) == def::enm_Triggers::Waiting)	)
				{
 					this->m_Candies[c]->s_Can(1, false);
				}
			}

			//	Actual Proccess !
			{
				//	This part is about setting the iPos and jPos of the candy.
				{
					this->m_Candies[c]->s_Pos(1, round((this->yP - this->m_Candies[c]->g_PositionPrp(2)) / this->m_GridBound));
					this->m_Candies[c]->s_Pos(2, round((this->m_Candies[c]->g_PositionPrp(1) - this->xP) / this->m_GridBound));
				}			

				//	Also, this is to fix if there were any errors.
				//	Mostly, if any Pos turned out to be a negative value.
				{
					if (this->m_Candies[c]->g_Pos(1) < -0.5)
					{
						this->m_Candies[c]->s_Pos(1, m_InvalidIPos);
					}

					if (this->m_Candies[c]->g_Pos(2) < -0.5)
					{
						this->m_Candies[c]->s_Pos(2, m_InvalidIPos);
					}
				}				
			}
		}
	}
	
	inline void			SortItOut()
	{
		//	What this sorting does is to avoid candies to spawn when doing
		//	switching nearby a spawnpoint.
		//	Of course there are way more reasons I used sorting functions,
		//	but for now this is the main reason why... For now...

		//	QuickSort(this->m_Candies, 0, this->m_Candies.size() - 1);
		//	InsertionSort(this->m_Candies, this->m_Candies.size());
	}
	inline void			UpdateBoardState()
	{
		int				_iPos_				= 0;
		int				_jPos_				= 0;
		bool			_AllowsMatching_	= 0;

		this->_Size_Candies_		= this->m_Candies.size();

		

		//	Reseting the status of the board logic.
		{
			for (int i = 0; i < this->m_BoardHeight; ++i)
			{
				for (int j = 0; j < this->m_BoardWidth; ++j)
				{
					this->m_BoardLogic[i][j]->ResetStatus();
				}
			}
		}

		//	Updating the status of the board logic.
		{
			//	-----------------------------------------------
			//		Main update for every cell of the board.
			//	-----------------------------------------------
			for (	int c = 0; 
					c < _Size_Candies_;
					++c	)
			{
				//	-------------------------------------------------------
				//		If a candy has an invalid pos, then don't update
				//				the board status with that candy.
				//	-------------------------------------------------------
				if ((this->m_Candies[c]->g_Pos(1) >= 0) && (this->m_Candies[c]->g_Pos(2) >= 0))
				{			
					_iPos_	=	this->m_Candies[c]->g_Pos(1);
					_jPos_	=	this->m_Candies[c]->g_Pos(2);

					


					//	I had an idea where instead of worrying about checking the canBeMatched
					//	property, a block of code will be responsible to check so, but then I realized
					//	if a candy is already set as cannot be matched then if I modify the value 
					//	because other conditions were met then the original reason to keep the value
					//	as it was is lost.
					_AllowsMatching_ = (		(this->m_Candies[c]->g_Can(3))	&&			//	Candy can be matched?
											(	(!this->m_Candies[c]->g_Is(1))	&&	(		//	Candy is falling?
												(!this->m_Candies[c]->g_Is(2))	||			//	Candy is bouncing?
												(fabs(this->m_Candies[c]->g_PositionPrp(4)) <= (TheCandy::_MatchingSensibility_)))	)	&&
												(!this->m_Candies[c]->g_IsSwapping(1))			&& 
												(!this->m_Candies[c]->g_Fc_Is(2))				&&		//	If it is being painted, then no.
												(!this->m_Candies[c]->g_BoB_Is(2))				&&		//	Nor being fused
												(this->m_Candies[c]->g_ItemAllowsSomething(1)	));		//	This item allows matching?

					this->m_BoardLogic[_iPos_][_jPos_]->UpdateStatus(	this->m_Candies[c]->g_KindID()					,
																		this->m_Candies[c]->g_ItemID()					,
																		c	, _AllowsMatching_							,
																		this->m_Candies[c]->g_HasBlocker(def::enm_Defines::_SEARCH_ALL)	);
				}
			}

			//	-----------------------------------------------
			//			Lastly, for the siding part.
			//	-----------------------------------------------
			for (	int i = 0;
					i < m_BoardHeight;
					++i	)
			{
				for (int j = 0; j < m_BoardWidth; j++)
				{
					if (					(this->m_BoardLogic[i][j]->g_Has(1))						||
											(this->m_BoardLogic[i][j]->g_Is(1))							||
							(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::CupCake_1 )		||
							(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::CupCake_2 )		||
							(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::CupCake_3 )		||
							(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::CupCake_4 )		||
							(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::CupCake_5 )		)
					{ 
						for (	int a = i; 
								a < m_BoardHeight; 
								++a)
						{
							this->m_BoardLogic[a][j]->s_Has(2, true);
						}
					}
				}
			}
		}
	}

	inline void			SwapCandies()
	{
		//	Special mixes.
		{
			using			sMx = SpecialMixWrapper::enm_SpecialMix;



			std::vector<SpecialMixWrapper*>&			_Wrappers_ = this->m_SpecialMixes->g_Wrappers();
			TheCandy*		_Candy_Ptr			= nullptr;
			bool			_Delete_Wrapper_	= false;
			int				_AtPos_				= def::enm_Defines::_NOT_FOUND;



			for (	int i = 0; 
					i < _Wrappers_.size(); 
					++i	)
			{
				_Delete_Wrapper_		= false;



				//	Switching until finding the case.
				switch (	_Wrappers_[i]->g_SpecialMixID()	)
				{
				case	sMx::StrippedH_StrippedH:
					this->m_Strippeds->AddSpecialMix(	_Wrappers_[i]	);
					_Delete_Wrapper_ = true;

					break;

				case	sMx::StrippedH_StrippedV:
					this->m_Strippeds->AddSpecialMix(	_Wrappers_[i]	);
					_Delete_Wrapper_ = true;

					break;

				case	sMx::StrippedH_Wrapped:
					this->m_Strippeds->AddSpecialMix(	_Wrappers_[i]	);
					_Delete_Wrapper_ = true;

					break;

				case	sMx::StrippedH_WrappedFuse:
					this->m_Strippeds->AddSpecialMix(	_Wrappers_[i]	);
					_Delete_Wrapper_ = true;

					break;

				case	sMx::BonOBom_CommonCandy:
					//	Special effects and others.
					this->m_BonOBoms->AddSpecialMix(	_Wrappers_[i]	);

					//	Search the position in vector.
					{
						this->_Container_Size_		= this->m_Candies.size();
						_Candy_Ptr					= _Wrappers_[i]->g_Pointers(0);

						for	(	int i = 0; i < this->_Container_Size_; ++i	)
						{
							if (	this->m_Candies[i]->g_ObjectID() == _Candy_Ptr->g_ObjectID()	)
							{
								_AtPos_		= i;
								break;
							}
						}
					}

					//	Actual tracker since AddTracker takes a lot of
					//	parameters. Or modifiy it later, whatever it takes.
					{
						this->m_BonOBoms->AddTracker(	_Wrappers_[i]->g_Pointers(0), def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT	,
														tls::Vec4<double>(	this->xP, this->yP								, 
																			this->m_BoardWidth * this->m_GridBound			,
																			this->m_BoardHeight * this->m_GridBound		),
														this->m_Candies, _AtPos_, _Wrappers_[i]->g_Pointers(1)->g_KindID()	,
														def::enm_Defines::_SKIP_THIS										);
					}

					_Delete_Wrapper_ = true;

					break;

				case	sMx::BonOBom_StrippedHorizontal:
				case	sMx::BonOBom_StrippedVertical:
				case	sMx::BonOBom_Wrapped:
				case	sMx::BonOBom_WrappedFuse:
				case	sMx::BonOBom_JellyFish:
				case	sMx::BonOBom_StarLight:
				case	sMx::BonOBom_FireWork:
				case	sMx::BonOBom_BubbleGum:
				case	sMx::BonOBom_Popping:
					//	Special effects and others.
					this->m_BonOBoms->AddSpecialMix(	_Wrappers_[i]	);

					//	Search the Bon-O-Bom's position in vector.
					{
						this->_Container_Size_		= this->m_Candies.size();
						_Candy_Ptr					= _Wrappers_[i]->g_Pointers(0);

						for	(	int i = 0; i < this->_Container_Size_; ++i	)
						{
							if (	this->m_Candies[i]->g_ObjectID() == _Candy_Ptr->g_ObjectID()	)
							{
								_AtPos_		= i;
								break;
							}
						}
					}

					//	Actual tracker since AddTracker takes a lot of
					//	parameters. Or modifiy it later, whatever it takes.
					{
						this->m_BonOBoms->AddTracker(	_Wrappers_[i]->g_Pointers(0), def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT	,
														tls::Vec4<double>(	this->xP, this->yP								, 
																			this->m_BoardWidth * this->m_GridBound			,
																			this->m_BoardHeight * this->m_GridBound		),
														this->m_Candies, _AtPos_, _Wrappers_[i]->g_Pointers(1)->g_KindID()	,
														_Wrappers_[i]->g_Pointers(1)->g_ItemID()							);
					}

					_Delete_Wrapper_ = true;

					break;

				case	sMx::FrozenCandy_CommonCandy:
					//	Special effects and others.
					this->m_Frozens->AddSpecialMix(	_Wrappers_[i]	);

					//	Search the position in vector.
					{
						this->_Container_Size_		= this->m_Candies.size();
						_Candy_Ptr					= _Wrappers_[i]->g_Pointers(0);

						for	(	int i = 0; i < this->_Container_Size_; ++i	)
						{
							if (	this->m_Candies[i]->g_ObjectID() == _Candy_Ptr->g_ObjectID()	)
							{
								_AtPos_		= i;
								break;
							}
						}
					}

					//	Actual tracker since AddTracker takes a lot of
					//	parameters. Or modifiy it later, whatever it takes.
					{
						int		_CustomKind_	= _Wrappers_[i]->g_Pointers(1)->g_KindID();
						if (	_CustomKind_ == _Wrappers_[i]->g_Pointers(0)->g_KindID()	)
						{
							_CustomKind_	= def::enm_Defines::_SKIP_THIS;
						}



						this->m_Frozens->AddTracker(	_Wrappers_[i]->g_Pointers(0), def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT	,
														tls::Vec4<double>(	this->xP, this->yP									, 
																			this->m_BoardWidth * this->m_GridBound				,
																			this->m_BoardHeight * this->m_GridBound			),
														this->m_Candies, _AtPos_, _CustomKind_, def::enm_Defines::_SKIP_THIS	);
					}

					_Delete_Wrapper_ = true;
					break;

				case	sMx::FrozenCandy_StrippedHorizontal:
				case	sMx::FrozenCandy_StrippedVertical:
				case	sMx::FrozenCandy_Wrapped:
				case	sMx::FrozenCandy_WrappedFuse:
				case	sMx::FrozenCandy_JellyFish:
				case	sMx::FrozenCandy_StarLight:
				case	sMx::FrozenCandy_FireWork:
				case	sMx::FrozenCandy_BubbleGum:
				case	sMx::FrozenCandy_Popping:
					//	Special effects and others.
					this->m_Frozens->AddSpecialMix(	_Wrappers_[i]	);

					//	Search the position in vector.
					{
						this->_Container_Size_		= this->m_Candies.size();
						_Candy_Ptr					= _Wrappers_[i]->g_Pointers(0);

						for	(	int i = 0; i < this->_Container_Size_; ++i	)
						{
							if (	this->m_Candies[i]->g_ObjectID() == _Candy_Ptr->g_ObjectID()	)
							{
								_AtPos_		= i;
								break;
							}
						}
					}

					//	Actual tracker since AddTracker takes a lot of
					//	parameters. Or modifiy it later, whatever it takes.
					{
						int		_CustomKind_	= _Wrappers_[i]->g_Pointers(1)->g_KindID();
						if (	_CustomKind_ == _Wrappers_[i]->g_Pointers(0)->g_KindID()	)
						{
							_CustomKind_	= def::enm_Defines::_SKIP_THIS;
						}



						this->m_Frozens->AddTracker(	_Wrappers_[i]->g_Pointers(0), def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT	,
														tls::Vec4<double>(	this->xP, this->yP												, 
																			this->m_BoardWidth * this->m_GridBound							,
																			this->m_BoardHeight * this->m_GridBound						),
														this->m_Candies, _AtPos_, _CustomKind_, _Wrappers_[i]->g_Pointers(1)->g_ItemID()	);
					}

					_Delete_Wrapper_ = true;
					break;
				}
				
				//	Part to delete the elemnet of the wrapper
				//	if a case was found.
				if (	_Delete_Wrapper_	)
				{
					tls::EraseElement(_Wrappers_, i);
				}
			}
		}

		//							   ~
		//	Step three is a following-up step from TheSwitcher header...
		// 
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//							Step 3:
		//					 Move those candies!
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//	
		{
			bool	_MatchAhead_		= false;

			int		_Swap_Partner_		= def::enm_Defines::_NOT_FOUND;

			this->_Size_Candies_		= this->m_Candies.size();
			this->m_IsSwapping			= false;



			//	Checker and logical segment.
			for (	int i = 0; 
					i < this->_Size_Candies_;
					++i	)
			{
				_MatchAhead_ = false;






				if (	!this->m_FreeSwitch		)
				{
					//	If the candy is still swapping, then...
					if (	this->m_Candies[i]->g_IsSwapping(2)		)
					{
						this->m_Candies[i]->s_IsSwapping(2, false);

						int			_iPos_	= 0, _jPos_ = 0;
						bool		_Skip_	= false;
						_Swap_Partner_		= def::enm_Defines::_NOT_FOUND;



						//	Getting the swapped partner (if still exists).
						{
							for (	int k = 0;
									k < this->_Size_Candies_;
									++k	)
							{
								if (	this->m_Candies[k]->g_ObjectID() == this->m_Candies[i]->g_OtherSwappedID()	)
								{
									_Swap_Partner_ = k;
									break;
								}
							}
						}

						// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / //

						//	Matching checking...
						{
							if (_Swap_Partner_ != def::enm_Defines::_NOT_FOUND)
							{
								//	Vertical Match Cheking!
								{
									for (	int m = -1; 
											m <= 1; 
											++m	)
									{
										_iPos_		= this->m_Candies[i]->g_Pos(1) + m;
										_jPos_		= this->m_Candies[i]->g_Pos(2);



										if (	(	1 < _iPos_)							&&
												(	_iPos_ < (this->m_BoardHeight - 1))	)
										{
											if (	(this->m_BoardLogic[_iPos_][_jPos_]->g_KindID() == this->m_BoardLogic[_iPos_ - 1][_jPos_]->g_KindID())	&&
													(this->m_BoardLogic[_iPos_][_jPos_]->g_KindID() == this->m_BoardLogic[_iPos_ + 1][_jPos_]->g_KindID())	&&
													(this->m_BoardLogic[_iPos_ - 1][_jPos_]->g_Can(2)		)							&&
													(this->m_BoardLogic[_iPos_][_jPos_]->g_Can(2)			)							&&
													(this->m_BoardLogic[_iPos_ + 1][_jPos_]->g_Can(2)		)							)
											{
												_MatchAhead_		= true;
												this->m_IsSwapping	= false;



												this->m_Candies[i]->s_IsSwapping(1, false);					//	IsSwapping.
												this->m_Candies[i]->s_IsSwapping(3, false);					//	InvalidSwap.

												this->m_Candies[_Swap_Partner_]->s_IsSwapping(1, false);	//	IsSwapping.
												this->m_Candies[_Swap_Partner_]->s_IsSwapping(3, false);	//	InvalidSwap.
											}
										}
									}
								}

								//	Horizontal Match Cheking!
								{
									for (int m = -1;
										m <= 1;
										++m)
									{
										_iPos_ = this->m_Candies[i]->g_Pos(1);
										_jPos_ = this->m_Candies[i]->g_Pos(2) + m;



										if ((1 < _jPos_) &&
											(_jPos_ < (this->m_BoardWidth - 1)))
										{
											if ((this->m_BoardLogic[_iPos_][_jPos_]->g_KindID() == this->m_BoardLogic[_iPos_][_jPos_ - 1]->g_KindID()) &&
												(this->m_BoardLogic[_iPos_][_jPos_]->g_KindID() == this->m_BoardLogic[_iPos_][_jPos_ + 1]->g_KindID()) &&
												(this->m_BoardLogic[_iPos_][_jPos_ - 1]->g_Can(2)) &&
												(this->m_BoardLogic[_iPos_][_jPos_]->g_Can(2)) &&
												(this->m_BoardLogic[_iPos_][_jPos_ + 1]->g_Can(2)))
											{
												_MatchAhead_ = true;
												this->m_IsSwapping = false;



												this->m_Candies[i]->s_IsSwapping(1, false);					//	IsSwapping.
												this->m_Candies[i]->s_IsSwapping(3, false);					//	InvalidSwap.

												this->m_Candies[_Swap_Partner_]->s_IsSwapping(1, false);	//	IsSwapping.
												this->m_Candies[_Swap_Partner_]->s_IsSwapping(3, false);	//	InvalidSwap.
											}
										}
									}
								}



								// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / //

								//	...aeiou...

								// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / //



								// Revert Swapping...
								if (!_MatchAhead_)
								{
									this->m_IsSwapping = true;

									this->m_Candies[i]->s_IsSwapping(1, true);					//	IsSwapping.
									this->m_Candies[i]->s_IsSwapping(3, false);					//	InvalidSwap.

									this->m_Candies[_Swap_Partner_]->s_IsSwapping(1, true);		//	IsSwapping.
									this->m_Candies[_Swap_Partner_]->s_IsSwapping(3, false);	//	InvalidSwap.



									//	Swap back settings!
									{
										this->m_Candies[i]->Reverse_SwapDir(this->m_Candies[_Swap_Partner_]->g_PositionPrp(1),
											this->m_Candies[_Swap_Partner_]->g_PositionPrp(2));
										this->m_Candies[_Swap_Partner_]->Reverse_SwapDir(this->m_Candies[i]->g_PositionPrp(1),
											this->m_Candies[i]->g_PositionPrp(2));
									}

									//	Sound effect.
									{
										this->_Sounds_->Play(snd::SndSys::GoSwitch, 2);
									}
								}
							}
						}
					}
				}
				else
				{
					//	Just set it false as has reached.
					if (	this->m_Candies[i]->g_IsSwapping(2)		)
					{
						this->m_Candies[i]->s_IsSwapping(2, false);
					}
				}

				this->m_Candies[i]->IniCnt_ObjSwitched();
			}

			//	Just move the candy.
			//	Not a expensive operation since just a few candies (or none)
			//	are being moved.
			for (	int i = 0;
					i < this->_Size_Candies_;
					++i	)
			{
				if (	this->m_Candies[i]->g_IsSwapping(1)	)
				{
					this->m_Candies[i]->SwapObject();
					this->m_IsSwapping	= true;
				}
			}
		}

	



		this->m_SwitchController->AnimateFrames();
	}

	inline void			DoCandies()
	{
		//	This function does not eliminates or deletes any candies (objects).
		//	So, to earn a little time, is better to create a variable which stores
		//	the size of the vector.

		//	-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		
		this->_MySize_ = this->m_Candies.size();



		//	-----------------------------------
		//		For loop to check the roof.
		//	-----------------------------------
		for (int c = 0; c < _MySize_; ++c)
		{
			this->m_Candies[c]->SetRoofHit(		false	);



			switch (	this->m_Candies[c]->g_GravityDirection(1)	)
			{
			case		def::enm_Directions::Down:
				this->_UpTo_			= this->m_Roof;
				this->_At_				= -1;
				this->_HitIsOffGrid_	= false;



				//	-----------------------------------------------------------------------------------------------------------
				//						In this for loop, what I'm trying to do is to search the top (roof)
				//						So I won't trespass* other objects. Looking for other candies hitbox.
				//		Rendered -> Using a vector of saved ATs instead another for loop (O(n^2)) to (O(n * k) :| k (!)< n)
				//	-----------------------------------------------------------------------------------------------------------
				for (	int k = 0; 
						k < this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)].size();
						++k	)
				{
					// This is for the same column.
					if (	(this->m_Candies[c]->g_PositionPrp(2) < this->m_Candies[this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k]]->g_PositionPrp(2))		&&
							(this->m_Candies[this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k]]->g_PositionPrp(2) < this->_UpTo_)								&&
							(c != this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k])									)
					{
						this->_UpTo_	= this->m_Candies[this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k]]->g_PositionPrp(2);
						this->_At_		= this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k];
					}
				}


				//	--------------------------------------------------------------
				//		A short loop that will check for off-grids to make 
				//						them act as a roof.
				//		Actually, it is very simple and don't need that much
				//						rendering by now !
				//	--------------------------------------------------------------
				for (	int i = this->m_Candies[c]->g_Pos(1); 
						i >= 0; 
						--i	)
				{
					//	Check whether the grid is off.
					if (	this->m_BoardLogic[i][this->m_Candies[c]->g_Pos(2)]->g_Is(1)	)
					{
						//	If that condition results in true, then make it act as 
						//	a roof. Actually, a break is needed because once it has found
						//	the first roof, there is no need to keep searching.
						if ((this->yP + (this->m_GridBound * i)) > this->_UpTo_)
						{
							this->_UpTo_ = this->yP + (this->m_GridBound * i);
							this->_HitIsOffGrid_ = true;

							break;
						}
					}

				}



				// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / //


	
				//	-----------------------------------------------------
				//			Finally, apply the roof condition.
				//	-----------------------------------------------------
				{
					if ((this->_At_ != -1) && (this->m_Candies[c]->g_Can(1)))
					{
						if (	((this->m_Candies[c]->g_PositionPrp(1)) != (this->_UpTo_))	&& 
								(!this->m_Candies[c]->g_IsSideWays(1))						)
						{
							if ((this->m_Candies[c]->g_PositionPrp(2) + this->m_Candies[c]->g_PositionPrp(4)) > (this->_UpTo_ - this->m_GridBound))
							{
								this->m_Candies[c]->SetRoofHit(		true	);



								if (	_HitIsOffGrid_	)
								{
									this->m_Candies[c]->s_PositionPrp(4, 0);
								}
								else
								{
									//	Absorb the yDpz.
									//	this->m_Candies[_At_]->s_PositionPrp(4, this->m_Candies[_At_]->g_PositionPrp(4) - fabs(this->m_Candies[c]->g_PositionPrp(4) / 100.0));

									//	This happens because the blocker absorbs all the yDpz energy of the candy when hit.
									if (	this->m_Candies[_At_]->ObjectIsStatic()		)
									{
										this->m_Candies[c]->s_PositionPrp(2, this->m_Candies[_At_]->g_PositionPrp(2) - this->m_Candies[_At_]->g_MeasuresPrp(2));
										this->m_Candies[c]->s_PositionPrp(4, 0.0);
									}
									else
									{
										if (	this->m_Candies[c]->g_PositionPrp(4) >= 2.0		)
										{
											this->m_Candies[_At_]->s_PositionPrp(4, this->m_Candies[_At_]->g_PositionPrp(4) + (this->m_Candies[c]->g_PositionPrp(4) * (25.0 / 100.0)));
											this->m_Candies[c]->s_PositionPrp(4, this->m_Candies[c]->g_PositionPrp(4) * 40.0 / 100.0);
											
											//	The other 35/100 is lost due to sound conversion.
										}
									}
								}
							}
						}
					}
				}

				break;
			}
		}

		//	-----------------------------------
		//		For loop to check the ground.
		//	-----------------------------------
		for (int c = 0; c < _MySize_; ++c)
		{
			this->_CanFall_			= true;



			switch (this->m_Candies[c]->g_GravityDirection(1))
			{
			case	def::enm_Directions::Down:
				if ((this->m_Candies[c]->g_Can(1)) && (!this->m_Candies[c]->g_IsSwapping(1)))
				{
					this->_DownTo_		= this->yP - (this->m_GridBound * this->m_BoardHeight);



					//	--------------------------------------------------------------
					//			Here checks for any potentially off-grid.
					//	--------------------------------------------------------------
			 		if (this->m_Candies[c]->g_Pos(1) >= 0)
					{
						for (	int i = this->m_Candies[c]->g_Pos(1); 
								i < this->m_BoardHeight; 
								++i)
						{ 
							if (	this->m_BoardLogic[i][this->m_Candies[c]->g_Pos(2)]->g_Is(1)	)
							{
								this->_DownTo_ = this->yP + (this->m_GridBound * i);
								break;
							}
						}
					}

					//	--------------------------------------------------------------
					//					Then, hits with other candies.
					//	--------------------------------------------------------------
					for (	int k = 0; 
							k < this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)].size(); 
							++k	)
					{
						this->_Where_	=		this->_ATs_Column_[this->m_Candies[c]->g_Pos(2)][k];


						
						//	If _Where_ and c are the same, then continue.
						{
							if (	c == this->_Where_	)
							{
								continue;
							}
						}

						//	If c position is shorter than _Where_, means that _Where_ is like a top
						//	and c is the bottom. I'm looking for other bottoms.
						{
							if (	this->m_Candies[c]->g_PositionPrp(2) < this->m_Candies[this->_Where_]->g_PositionPrp(2)		)
							{
								continue;
							}
						}

						//	Finally, if got here than just compare with the already bottom position.	
						{
							if (	this->_DownTo_ < this->m_Candies[this->_Where_]->g_PositionPrp(2)	)
							{
								this->_DownTo_		= this->m_Candies[this->_Where_]->g_PositionPrp(2);
							}
						}
					}				

					//	--------------------------------------------------------------
					//				About swapping (not the swapped candies)
					//	--------------------------------------------------------------
					for (	int k = 0;
							k < this->_ATs_Swapped_.size();
							++k	)
					{
						this->_Where_				= this->_ATs_Swapped_[k];



						//	Actual proccess...
						{
							//	If to check only the upmost candy (Like finding who is above me).
							if (	(	(	this->m_Candies[this->_Where_]->g_Pos(1)							== (this->m_Candies[c]->g_Pos(1) + 1)	)	&&
										(	this->m_Candies[this->_Where_]->g_Pos(2)							== this->m_Candies[c]->g_Pos(2)		)	)		||
									(	(	(this->m_Candies[this->_Where_]->g_Pos(1) + this->m_InvalidIPos)	== this->m_Candies[c]->g_Pos(1)		)		&&
										(	this->m_Candies[this->_Where_]->g_Pos(2)							== this->m_Candies[c]->g_Pos(2)		)	)		)
							{								
								//	When a candy is being swap, it acts as a block and the candy can't fall.
								//	Or rather falling down to that cell < top >.
								this->_DownTo_ = this->yP - (this->m_GridBound * (this->m_Candies[c]->g_Pos(1) + 1));
							}
						}
					}

					//	--------------------------------------------------------------
					//				Finally, if grid allows candies to fall.
					//	--------------------------------------------------------------
					if (	(0 <= this->m_Candies[c]->g_Pos(1))								&& 
							(this->m_Candies[c]->g_Pos(1) < (this->m_BoardHeight - 1))		)
					{
						if (!this->m_BoardLogic[this->m_Candies[c]->g_Pos(1) + 1][this->m_Candies[c]->g_Pos(2)]->g_Can(1))
						{
							this->_DownTo_ = this->m_Candies[c]->g_PositionPrp(2) - this->m_GridBound;
						}
					}
					
				

					// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / //


					if (this->_CanFall_)
					{
						this->m_Candies[c]->PhysicObject(this->_DownTo_);
					}
				}

				break;
			}
		}
	}
	inline void			SideWays()
	{
		std::vector<TheCandy*> _Candies_;
		//	this->PrintBoardInfo();
		bool		thereIsACandyAboveMe = false;
		bool		hasEnteredAnyway = false;
		int			auxiliarInt_N1 = 0;
		bool		candyStillExist = false;

		for (int j = 0; j < this->m_BoardWidth; j++)
		{
			for (int i = 0; i < this->m_BoardHeight; i++)
			{
				thereIsACandyAboveMe = false;
				hasEnteredAnyway = false;

				//						~ This part is when the grid has void. ~
				if (	(this->m_BoardLogic[i][j]->g_KindID() == STA_::enm_KindID::_Invalid	)	&&
						(this->m_BoardLogic[i][j]->g_ItemID() == STA_::enm_ItemID::Invalid	)	&&
						(this->m_BoardLogic[i][j]->g_Has(2)		)	&&	//	New candies can get there?
						(!this->m_BoardLogic[i][j]->g_Is(4)		)	&&	//	Is SideWays?
						(!this->m_BoardLogic[i][j]->g_Is(1)		)	)	//	Grid off?
				{
					auxiliarInt_N1 = 0;

					for (int c = i; c >= 0; c--)
					{
						if (this->m_BoardLogic[c][j]->g_Is(1))
						{
							auxiliarInt_N1 = c;
							break;
						}
					}

					for (int c = 0; c < this->m_Candies.size(); c++)
					{
						if (((i > this->m_Candies[c]->g_Pos(1)) && (this->m_Candies[c]->g_Pos(1) >= auxiliarInt_N1)) && (j == this->m_Candies[c]->g_Pos(2)))
						{
							_Candies_.push_back(this->m_Candies[c]);
						}
					}
					if (!_Candies_.empty())
						QuickSort(_Candies_, 0, _Candies_.size() - 1);
					for (int c = 0; c < _Candies_.size(); c++)
					{
						//	Has a licorice cage.
						if (		(!_Candies_[c]->g_HasBlocker(1))		&&
								(_Candies_[c]->g_ItemAllowsSomething(3))	)
						{
							thereIsACandyAboveMe = true;
						}
						else
						{
							break;
						}
					}
					
					
					/*
					if (i > 0)
					{
						if (this->m_BoardLogic[i - 1][j]->GET_thisGridIsOff())
						{
							thereIsACandyAboveMe = false;
						}
					}
					*/

					if (!thereIsACandyAboveMe)
					{
						for (int c = 0; c < this->m_Candies.size(); c++)
						{
							if ((((this->m_Candies[c]->g_Pos(1) == (i - 1)) && (this->m_Candies[c]->g_Pos(2) == (j - 1)))				||
								((this->m_Candies[c]->g_Pos(1) == (i - 1)) && (this->m_Candies[c]->g_Pos(2) == (j + 1))))				&&
								(fabs(this->m_Candies[c]->g_PositionPrp(4)) <= 0.01) && (!this->m_Candies[c]->g_IsSideWays(1))		&&
								this->m_Candies[c]->g_Can(1)																		 )
							{
								if ((!this->m_Candies[c]->g_HasBlocker(1)) && (this->m_BoardLogic[i][j]->g_Can(1)))
								{
									hasEnteredAnyway = true;

									// 1. Telling the candy to go sideways.
									this->m_Candies[c]->s_IsSideWays(1, true);

									// 2. Now, where is the way: left or right.
									if (this->m_Candies[c]->g_Pos(2) == (j + 1))
										this->m_Candies[c]->s_SideDirection(def::enm_Directions::Left, this->m_Candies[c]->g_PositionPrp(1) - this->m_GridBound, this->yP - ((this->m_Candies[c]->g_Pos(1) + 1) * this->m_GridBound));
									else
										this->m_Candies[c]->s_SideDirection(def::enm_Directions::Right, this->m_Candies[c]->g_PositionPrp(1) + this->m_GridBound, this->yP - ((this->m_Candies[c]->g_Pos(1) + 1) * this->m_GridBound));

									// 4. Finally, this grid has already a candy ocupant, so stop calling for more candies.
									this->m_Candies[c]->s_SideWaysPos(i, j);

									// This is an experimental side.
									this->m_BoardLogic[i][j]->s_Is(1, true);
									this->m_BoardLogic[i][j]->s_SideWaysID(this->m_Candies[c]->g_ObjectID());

									//this->m_Candies[c]->SET_isBouncing(false);
									this->m_Candies[c]->s_PositionPrp(4, 0.0);
									//this->m_Candies[c]->SET_isFalling(false);

									c = this->m_Candies.size();
								}
							}
						}
					}

					_Candies_.clear();

					if (hasEnteredAnyway)
						i = this->m_BoardHeight;
				}

				if (i < this->m_BoardHeight)
				{
					if (this->m_BoardLogic[i][j]->g_Is(4))
					{
						i = this->m_BoardHeight;
					}
				}
			}
		}
		for (int c = 0; c < this->m_Candies.size(); c++)
		{
			this->m_Candies[c]->MoveToSide();

			if (this->m_Candies[c]->g_HasArrivedSideWays())
			{
				this->m_BoardLogic[this->m_Candies[c]->g_SideWaysPos(1)][this->m_Candies[c]->g_SideWaysPos(2)]->s_Is(1, false);
			}
		}
		for (int i = 0; i < this->m_BoardHeight; i++)
		{
			for (int j = 0; j < this->m_BoardWidth; j++)
			{
				candyStillExist = false;

				if (this->m_BoardLogic[i][j]->g_Is(4))
				{
					for (int c = 0; c < this->m_Candies.size(); c++)
					{
						if (this->m_BoardLogic[i][j]->g_SideWaysID() == this->m_Candies[c]->g_ObjectID())
						{
							candyStillExist = true;
						}
					}

					if (!candyStillExist)
					{
						this->m_BoardLogic[i][j]->s_Is(1, false);
					}
				}
			}
		}
	}
	inline void			MatchSequence()
	{
		
		this->_Size_Candies_		= this->m_Candies.size();


		//	Cascade handler.
		{
			for (	int c = 0;
					c < this->_Size_Candies_;
					++c	)
			{
				if (	(this->m_Candies[c]->g_Is(1))										||		//	Is falling				?	
						(this->m_Candies[c]->g_Is(2))										||		//	Is bouncing				?
						(this->m_Candies[c]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)	||		//	Is wrapped fuse			?
						(this->m_Fishes->g_FishesAreSwimming())								||		//	Fishes are swimming		?
						(this->m_Candies[c]->g_Fc_Is(1))									||		//	Frozen is painting		?
						(this->m_Candies[c]->g_BoB_Is(1))									)		//	Bom-O-Bom is fusing		?
				{
					this->m_Scores->CascadeActive();

					break;
				}
			}


			this->m_Scores->ClockCascade();
		}

		//	Divine voices.
		{
			this->m_Scores->Voice(	this->m_SwitchController->SwitchMade()	);
		}
	}
	inline void			Matches()
	{
		//	this->PrintBoardInfo();

		bool		_MatchOnThisGrid_	= false;
		bool		_SwappedFound_		= false;
		bool		_IsSwappingMatch_	= false;



		//	Frozen candy and Bom-O-Bom.	
		for (int i = 0; i < this->m_BoardHeight; ++i)
		{
			for (int j = 0; j < this->m_BoardWidth; ++j)
			{
				_SwappedFound_			= false;
				_IsSwappingMatch_		= false;
				_MatchOnThisGrid_		= false;



				//	Frozen Candy !
				{
					//	- - - - - - - - - - - - - - -
					//	Frozen Candy Forms - Side 7
					//	- - - - - - - - - - - - - - -

					//	Frozen Side 7 - A!
					if (	(	i < (this->m_BoardHeight - 2)	)				&&
							(	(1 < j) && (j < (this->m_BoardWidth - 2))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2)) &&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC7Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i + c - 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i + c - 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}
							}
						}
					}

					//	Frozen Side 7 - B!
					if (	(	1 < i	)										&&
							(	(1 < j) && (j < (this->m_BoardWidth - 2))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC7Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3: case 4 :
												this->_Where_ = this->m_BoardLogic[i - c + 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i - c + 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i - c][j]->ResetStatus();
								}
							}
						}
					}

					//	Frozen Side 7 - C!
					if (	(	(1 < i) && (i < (this->m_BoardHeight - 2))	)	&&
							(	j < (this->m_BoardWidth - 2)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC7Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i][j + c - 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i][j + c - 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}

					//	Frozen Side 7 - D!
					if (	(	(1 < i) && (i < (this->m_BoardHeight - 2))	)	&&
							(	1 < j	)										&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC7Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i][j - c + 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3: case 4:
												this->_Where_ = this->m_BoardLogic[i][j - c + 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j - c]->ResetStatus();
								}
							}
						}
					}



					//	- - - - - - - - - - - - - - -
					//	Frozen Candy Forms - Side 6
					//	- - - - - - - - - - - - - - -

					//	Frozen Side 6 - A!
					if (	(	i < (this->m_BoardHeight - 1)	)				&&
							(	(1 < j) && (j < (this->m_BoardWidth - 2))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC6Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								if (this->m_BoardLogic[i + 1][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies[this->m_BoardLogic[i + 1][j]->g_CandyAt()]->HitOne_HP();
									this->m_Candies[this->m_BoardLogic[i + 1][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i + c - 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i + c - 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									
									if (	(this->m_BoardLogic[i + 1][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
											(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
									{
										this->m_Candies[this->m_BoardLogic[i + 1][j]->g_CandyAt()]->s_DropCrush(false);
										this->m_Candies[this->m_BoardLogic[i + 1][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
									}									
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
						
								this->m_BoardLogic[i + 1][j]->ResetStatus();						
							}
						}
					}

					//	Frozen Side 6 - B!
					if (	(	0 < i	)										&&
							(	(1 < j) && (j < (this->m_BoardWidth - 2))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC6Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								if (this->m_BoardLogic[i - 1][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies[this->m_BoardLogic[i - 1][j]->g_CandyAt()]->HitOne_HP();
									this->m_Candies[this->m_BoardLogic[i - 1][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}								
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i - c + 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i - c + 2][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									if (	(this->m_BoardLogic[i - 1][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
											(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
									{
										this->m_Candies[this->m_BoardLogic[i - 1][j]->g_CandyAt()]->s_DropCrush(false);
										this->m_Candies[this->m_BoardLogic[i - 1][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
								
								this->m_BoardLogic[i - 1][j]->ResetStatus();
							}
						}
					}

					//	Frozen Side 6 - C!
					if (	(	(1 < i) && (i < (this->m_BoardHeight - 2))	)	&&
							(	j < (this->m_BoardWidth - 1)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC6Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								if (this->m_BoardLogic[i][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies[this->m_BoardLogic[i][j + 1]->g_CandyAt()]->HitOne_HP();
									this->m_Candies[this->m_BoardLogic[i][j + 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}								
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i][j + c - 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i][j + c - 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									if (	(this->m_BoardLogic[i][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
											(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
									{
										this->m_Candies[this->m_BoardLogic[i][j + 1]->g_CandyAt()]->s_DropCrush(false);
										this->m_Candies[this->m_BoardLogic[i][j + 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
									}									
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								this->m_BoardLogic[i][j + 1]->ResetStatus();
							}
						}
					}

					//	Frozen Side 6 - D!
					if (	(	(1 < i) && (i < (this->m_BoardHeight - 2))	)	&&
							(	0 < j	)										&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::FrozenC6Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								if (this->m_BoardLogic[i][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies[this->m_BoardLogic[i][j - 1]->g_CandyAt()]->HitOne_HP();
									this->m_Candies[this->m_BoardLogic[i][j - 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i][j - c + 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0: case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 3:
												this->_Where_ = this->m_BoardLogic[i][j - c + 2]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FrozenC, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FrozenCandy);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									if (	(this->m_BoardLogic[i][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
											(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
									{
										this->m_Candies[this->m_BoardLogic[i][j - 1]->g_CandyAt()]->s_DropCrush(false);
										this->m_Candies[this->m_BoardLogic[i][j - 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								this->m_BoardLogic[i][j - 1]->ResetStatus();
							}
						}
					}
				}

				;

				//	Bom-O-Bom !
				{
					// Vertical Match!
					if ((	(i > 1) && (i < (this->m_BoardHeight - 2)) ) && (!_MatchOnThisGrid_)	)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID()) &&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID()) &&
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::BomOBomMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}		
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BomOBom, 1	);


							
										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BomOBom);							
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.		

										this->m_Prospform->AddParticle(		this->m_Candies[this->_Where_]		);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}
							}
						}
					}

					// Horizontal Match!
					if ((	(j > 1) && (j < (this->m_BoardWidth - 2)) ) && (!_MatchOnThisGrid_)		)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID()) &&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID()) &&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID()) &&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::BomOBomMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}						
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BomOBom, 1	);


							
										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BomOBom);							
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.		

										this->m_Prospform->AddParticle(		this->m_Candies[this->_Where_]		);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -2; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)
										{
											this->m_Candies[this->m_BoardLogic[i][j+ c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -2; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}
				}
			}
		}

		//	Wrappeds, Starlight and FireWork Rockets.
		for (int i = 0; i < this->m_BoardHeight; ++i)
		{
			for (int j = 0; j < this->m_BoardWidth; ++j)
			{
				_SwappedFound_			= false;
				_IsSwappingMatch_		= false;
				_MatchOnThisGrid_		= false;



				//	Wrapped Candy !
				{
					//	- - - - - - - - - - - - - - -
					//	Wrapped Candy Forms - Side T
					//	- - - - - - - - - - - - - - -

					// Wrapped T - A Candy!
					if (	(	i < (this->m_BoardHeight - 2)	)				&&
							(	(0 < j) && (j < (this->m_BoardWidth - 1))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i + c - 1][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i + c - 1][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										c++	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}
							}
						}
					}

					// Wrapped T - B Candy!
					if (	(	1 < i	)										&&
							(	(0 < j) && (j < (this->m_BoardWidth - 1))	)	&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i - c + 1][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i - c + 1][j]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										c++	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i - c][j]->ResetStatus();
								}
							}
						}
					}

					// Wrapped T - C Candy!
					if (	(	(0 < i) && (i < (this->m_BoardHeight - 1))	)	&&
							(	j < (this->m_BoardWidth - 2)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i][j + c - 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i][j + c - 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}

					// Wrapped T - D Candy!
					if (	(	(0 < i) && (i < (this->m_BoardHeight - 1))	)	&&
							(	1 < j	)										&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i][j - c + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2: case 3:
												this->_Where_ = this->m_BoardLogic[i][j - c + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										c++	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j - c]->ResetStatus();
								}
							}
						}
					}



					//	- - - - - - - - - - - - - - -
					//	Wrapped Candy Forms - Side L
					//	- - - - - - - - - - - - - - -

					// Wrapped L - A Candy!
					if (	(	1 < i	)										&&
							(	j < (this->m_BoardWidth - 2)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = 0; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i - c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}

					// Wrapped L - B Candy!
					if (	(	i < (this->m_BoardHeight - 2)	)				&&
							(	j < (this->m_BoardWidth - 2)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i - c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i - c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = 0; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}

					// Wrapped L - C Candy!
					if (	(	i < (this->m_BoardHeight - 2)	)				&&
							(	1 < j	)										&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i - c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j - c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i - c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j - c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = 0; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j - c]->ResetStatus();
								}
							}
						}
					}

					// Wrapped L - D Candy!
					if (	(	1 < i	)										&&
							(	1 < j	)										&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 2][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 2]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 2]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::WrappedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();	



									if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
									{
										_IsSwappingMatch_	= true;



										if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
										{
											_SwappedFound_	= true;
										}
									}
									else
									{
										this->_Where_ = def::enm_Defines::_NOT_FOUND;
									}									
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j - c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -2;
												c < 3;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -2: case -1: case 0:
												this->_Where_ = this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 1: case 2:
												this->_Where_ = this->m_BoardLogic[i][j - c]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(4);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = 0; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i - c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i - c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = 1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j - c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j - c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = 0; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i - c][j]->ResetStatus();
								}

								for (	int c = 1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j - c]->ResetStatus();
								}
							}
						}
					}
				}

				;

				//	Popping Candy!
				{
					// Popping Candy Horizontal !
					if (			(	i < (this->m_BoardHeight - 1)	)				&&	
							(	(	0 < j	) && (	j < (this->m_BoardWidth - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))			&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)			,
														this->m_Candies[_Where_]->g_PositionPrp(2)			,
														ScoreSys::PopppingCandyMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()				);							



							//	Hitpoints stuff...
							{
								for (	int k = 0;
										k < 2; 
										++k	)
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (this->m_BoardLogic[i + k][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
										{
											this->m_Candies[this->m_BoardLogic[i + k][j + c]->g_CandyAt()]->HitOne_HP();
											this->m_Candies[this->m_BoardLogic[i + k][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
										}
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									//	Sorry, this match can't be swapped-match.							
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									//	Sorry, this match can't be swapped-match.		
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int k = 0;
													k < 2; 
													++k	)
											{
												for (	int c = -1; 
														c <= 1; 
														++c	)
												{
													this->_Where_	= this->m_BoardLogic[i + k][j + c]->g_CandyAt();



													if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
													{											
														break;													
													}
													else
													{
														this->_Where_ = def::enm_Defines::_NOT_FOUND;
													}
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::PoppingCandy, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::PoppingCandy);										//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int k = 0;
											k < 2; 
											++k	)
									{
										for (	int c = -1; 
												c <= 1; 
												++c	)
										{
											if (	(this->m_BoardLogic[i + k][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
																			(_Where_ != def::enm_Defines::_NOT_FOUND)				)	
											{
												this->m_Candies[this->m_BoardLogic[i + k][j + c]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + k][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int k = 0;
										k < 2; 
										++k	)
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										this->m_BoardLogic[i + k][j + c]->ResetStatus();
									}
								}
							}
						}
					}

					// Popping Candy Vertical !
					if (			(	j < (this->m_BoardWidth - 1)	)				&&	
							(	(	0 < i	) && (	i < (this->m_BoardHeight - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))			&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)			,
														this->m_Candies[_Where_]->g_PositionPrp(2)			,
														ScoreSys::PopppingCandyMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()				);							



							//	Hitpoints stuff...
							{
								for (	int k = 0;
										k < 2; 
										++k	)
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (this->m_BoardLogic[i + c][j + k]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
										{
											this->m_Candies[this->m_BoardLogic[i + c][j + k]->g_CandyAt()]->HitOne_HP();
											this->m_Candies[this->m_BoardLogic[i + c][j + k]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
										}
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									//	Sorry, this match can't be swapped-match.							
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									//	Sorry, this match can't be swapped-match.		
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int k = 0;
													k < 2; 
													++k	)
											{
												for (	int c = -1; 
														c <= 1; 
														++c	)
												{
													this->_Where_	= this->m_BoardLogic[i + c][j + k]->g_CandyAt();



													if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
													{											
														break;													
													}
													else
													{
														this->_Where_ = def::enm_Defines::_NOT_FOUND;
													}
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::PoppingCandy, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::PoppingCandy);										//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int k = 0;
											k < 2; 
											++k	)
									{
										for (	int c = -1; 
												c <= 1; 
												++c	)
										{
											if (	(this->m_BoardLogic[i + c][j + k]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
																			(_Where_ != def::enm_Defines::_NOT_FOUND)				)	
											{
												this->m_Candies[this->m_BoardLogic[i + c][j + k]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + c][j + k]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int k = 0;
										k < 2; 
										++k	)
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										this->m_BoardLogic[i + c][j + k]->ResetStatus();
									}
								}
							}
						}
					}
				}

				;

				//	Starlight Candy!
				{
					// Plus sign form :D
					if (	(	(0 < i) && (i < this->m_BoardHeight - 1)	)	&&
							(	(0 < j) && (j < this->m_BoardWidth - 1)		)	&&
							(!_MatchOnThisGrid_)							)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)		,
														this->m_Candies[_Where_]->g_PositionPrp(2)		,
														ScoreSys::StarlightMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()			);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c < 5; 
										++c	)
								{
									//	This switch is just a selector, not a big deal.
									switch (c)
									{
									case 0:
										this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();
										break;

									case 1:
										this->_Where_	= this->m_BoardLogic[i - 1][j]->g_CandyAt();
										break;

									case 2:
										this->_Where_	= this->m_BoardLogic[i + 1][j]->g_CandyAt();
										break;

									case 3:
										this->_Where_	= this->m_BoardLogic[i][j - 1]->g_CandyAt();
										break;

									case 4:
										this->_Where_	= this->m_BoardLogic[i][j + 1]->g_CandyAt();
										break;
									}



									if (	_Where_ != def::enm_Defines::_NOT_FOUND	)
									{
										this->m_Candies[_Where_]->HitOne_HP();
										this->m_Candies[_Where_]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 and #2 are when swapped, but this match (by now)
								//	can't be a swapped-matched.
								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = 0;
												c < 5;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case 0:
												this->_Where_	= this->m_BoardLogic[i][j]->g_CandyAt();
												break;

											case 1:
												this->_Where_	= this->m_BoardLogic[i - 1][j]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i + 1][j]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i][j - 1]->g_CandyAt();
												break;

											case 4:
												this->_Where_	= this->m_BoardLogic[i][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_	= def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Wrapped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::Starlight);										//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									int		_Candy_At_	= 0;



									for (	int c = 0; 
											c < 5; 
											++c	)
									{
										//	This switch is just a selector, not a big deal.
										switch (c)
										{
										case 0:
											_Candy_At_ = this->m_BoardLogic[i][j]->g_CandyAt();
											break;

										case 1:
											_Candy_At_ = this->m_BoardLogic[i - 1][j]->g_CandyAt();
											break;

										case 2:
											_Candy_At_ = this->m_BoardLogic[i + 1][j]->g_CandyAt();
											break;

										case 3:
											_Candy_At_ = this->m_BoardLogic[i][j - 1]->g_CandyAt();
											break;

										case 4:
											_Candy_At_ = this->m_BoardLogic[i][j + 1]->g_CandyAt();
											break;
										}

										

										if (	(_Candy_At_ != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)		)
										{
											this->m_Candies[_Candy_At_]->s_DropCrush(false);
											this->m_Candies[_Candy_At_]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = 0; 
										c < 5; 
										++c	)
								{
									//	This switch is just a selector, not a big deal.
									switch (c)
									{
									case 0:
										this->m_BoardLogic[i][j]->ResetStatus();
										break;

									case 1:
										this->m_BoardLogic[i - 1][j]->ResetStatus();
										break;

									case 2:
										this->m_BoardLogic[i + 1][j]->ResetStatus();
										break;

									case 3:
										this->m_BoardLogic[i][j - 1]->ResetStatus();
										break;

									case 4:
										this->m_BoardLogic[i][j + 1]->ResetStatus();
										break;
									}
								}
							}
						}
					}
				}

				;

				//	FireWork Candy!
				{
					//	Horizontal Up (Side A).
					if (	(	(0 < j) && (j < (this->m_BoardWidth - 2)) )		&&
											(0 < i)								&&
										(!_MatchOnThisGrid_)					)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())		&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j + 1]->g_Can(2))	)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::FireworkMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									if (this->m_BoardLogic[i - 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i - 1][j + c - 3]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i - 1][j + c - 3]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FireWorkRocket, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FireWorkRocket);									//	Setting the itemID.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 4; 
											++c	)
									{
										if (c < 3)
										{
											if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
										else
										{
											if (	(this->m_BoardLogic[i - 1][j + c - 3]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i - 1][j + c - 3]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i - 1][j + c - 3]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									this->m_BoardLogic[i - 1][j + c]->ResetStatus();
								}
							}
						}
					}

					//	Horizontal Down (Side B).
					if (	(	(0 < j) && (j < (this->m_BoardWidth - 2)) )		&&
									(i < (this->m_BoardHeight - 1))				&&
										(!_MatchOnThisGrid_)					)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())		&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))	)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::FireworkMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + 1][j + c - 3]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + 1][j + c - 3]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FireWorkRocket, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FireWorkRocket);									//	Setting the itemID.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 4; 
											++c	)
									{
										if (c < 3)
										{
											if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
										else
										{
											if (	(this->m_BoardLogic[i + 1][j + c - 3]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i + 1][j + c - 3]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + 1][j + c - 3]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									this->m_BoardLogic[i + 1][j + c]->ResetStatus();
								}
							}
						}
					}

					//	Vertical Left (Side C).
					if (						(0 < j)							&&
							(	(0 < i) && (i < (this->m_BoardHeight - 2)) )		&&
										(!_MatchOnThisGrid_)					)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())		&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j - 1]->g_Can(2))	)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::FireworkMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + c - 3][j - 1]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + c - 3][j - 1]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FireWorkRocket, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FireWorkRocket);									//	Setting the itemID.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 4; 
											++c	)
									{
										if (c < 3)
										{
											if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
										else
										{
											if (	(this->m_BoardLogic[i + c - 3][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i + c - 3][j - 1]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + c - 3][j - 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j - 1]->ResetStatus();
								}
							}
						}
					}

					//	Vertical Right (Side D).
					if (			(j < (this->m_BoardWidth - 1))				&&
							(	(0 < i) && (i < (this->m_BoardHeight - 2)) )		&&
										(!_MatchOnThisGrid_)					)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())		&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))	)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::FireworkMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + c - 3][j + 1]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 4;
												++c	)
										{
											if (c < 3)
											{
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
											}
											else
											{
												this->_Where_	= this->m_BoardLogic[i + c - 3][j + 1]->g_CandyAt();
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FireWorkRocket, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::FireWorkRocket);									//	Setting the itemID.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 4; 
											++c	)
									{
										if (c < 3)
										{
											if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
										else
										{
											if (	(this->m_BoardLogic[i + c - 3][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
													(_Where_ != def::enm_Defines::_NOT_FOUND)										)
											{
												this->m_Candies[this->m_BoardLogic[i + c - 3][j + 1]->g_CandyAt()]->s_DropCrush(false);
												this->m_Candies[this->m_BoardLogic[i + c - 3][j + 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
											}
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = 0; 
										c < 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j + 1]->ResetStatus();
								}
							}
						}
					}
				}
			}
		}
		
		//	Srippeds, BubbleGums, fishes and matches.
		for (int i = 0; i < this->m_BoardHeight; ++i)
		{
			for (int j = 0; j < this->m_BoardWidth; ++j)
			{
				_SwappedFound_			= false;
				_IsSwappingMatch_		= false;
				_MatchOnThisGrid_		= false;

							

				//	Stripped Candy matching !
				{
					// Vertical Match!
					if ((	(i > 0) && (i < (this->m_BoardHeight - 2)) ) && (!_MatchOnThisGrid_)	)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID()) &&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 2][j]->g_KindID()) &&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i + 2][j]->g_Can(2))		)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::StrippedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Stripped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID((_IsSwappingMatch_) ? 2 : 3);								//	Set whether a hrz. or vrt. stripped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}
							}
						}
					}

					// Horizontal Match!
					if ((	(j > 0) && (j < (this->m_BoardWidth - 2)) ) && (!_MatchOnThisGrid_)		)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID()) &&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 2]->g_KindID()) &&
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 2]->g_Can(2))		)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2),
														ScoreSys::StrippedMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c <= 2;
												++c	)
										{
											this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::Stripped, 1	);



										this->m_Candies[this->_Where_]->s_ItemID((_IsSwappingMatch_) ? 3 : 2);								//	Set whether a hrz. or vrt. stripped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 2; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)
										{
											this->m_Candies[this->m_BoardLogic[i][j+ c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 2; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}
							}
						}
					}
				}
				
				;

				//	BubbleGum matching !
				{
					// BubbleGum Side A !
					if (						(	0 < i	)							&&	
							(	(	0 < j	) && (	j < (this->m_BoardWidth - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)		,
														this->m_Candies[_Where_]->g_PositionPrp(2)		,
														ScoreSys::BubbleGumMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()			);							



							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									if (this->m_BoardLogic[i - 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = -1;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}								
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i - 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i - 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BubbleGum, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BubbleGum);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = -1; 
											c <= 1; 
											c = c + 2	)
									{
										if (	(this->m_BoardLogic[i - 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i - 1][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									this->m_BoardLogic[i - 1][j + c]->ResetStatus();
								}
							}
						}
					}

					// BubbleGum Side B !
					if (				(	i < (this->m_BoardHeight - 1)	)			&&	
							(	(	0 < j	) && (	j < (this->m_BoardWidth - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)		,
														this->m_Candies[_Where_]->g_PositionPrp(2)		,
														ScoreSys::BubbleGumMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()			);							



							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									if (this->m_BoardLogic[i + 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = -1;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}								
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i + 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i][j + c]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i + 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BubbleGum, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BubbleGum);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = -1; 
											c <= 1; 
											c = c + 2	)
									{
										if (	(this->m_BoardLogic[i + 1][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + 1][j + c]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									this->m_BoardLogic[i][j + c]->ResetStatus();
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									this->m_BoardLogic[i + 1][j + c]->ResetStatus();
								}
							}
						}
					}

					// BubbleGum Side C !
					if (						(	0 < j	)							&&	
							(	(	0 < i	) && (	i < (this->m_BoardHeight - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j - 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j - 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j - 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)		,
														this->m_Candies[_Where_]->g_PositionPrp(2)		,
														ScoreSys::BubbleGumMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()			);							



							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									if (this->m_BoardLogic[i + c][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = -1;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}								
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j - 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j - 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j - 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BubbleGum, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BubbleGum);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = -1; 
											c <= 1; 
											c = c + 2	)
									{
										if (	(this->m_BoardLogic[i + c][j - 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j - 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									this->m_BoardLogic[i + c][j - 1]->ResetStatus();
								}
							}
						}
					}

					// BubbleGum Side D !
					if (				(	j < (this->m_BoardWidth - 1)	)			&&	
							(	(	0 < i	) && (	i < (this->m_BoardHeight - 1))	)	&&
											(!_MatchOnThisGrid_)						)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID())	&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i - 1][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))		)
						{
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)		,
														this->m_Candies[_Where_]->g_PositionPrp(2)		,
														ScoreSys::BubbleGumMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()			);							



							//	Hitpoints stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									if (this->m_BoardLogic[i + c][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = -1;
											c <= 1;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();	



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}								
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j + 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = -1;
												c < 4;
												++c	)
										{
											//	This switch is just a selector, not a big deal.
											switch (c)
											{
											case -1: case 0: case 1:
												this->_Where_	= this->m_BoardLogic[i + c][j]->g_CandyAt();
												break;

											case 2:
												this->_Where_	= this->m_BoardLogic[i - 1][j + 1]->g_CandyAt();
												break;

											case 3:
												this->_Where_	= this->m_BoardLogic[i + 1][j + 1]->g_CandyAt();
												break;
											}



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{											
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::BubbleGum, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::BubbleGum);														//	Set a wrapped candy.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = -1; 
											c <= 1; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}

									for (	int c = -1; 
											c <= 1; 
											c = c + 2	)
									{
										if (	(this->m_BoardLogic[i + c][j + 1]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)										)	
										{
											this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + c][j + 1]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}							

							//	Board stuff...
							{
								for (	int c = -1; 
										c <= 1; 
										++c	)
								{
									this->m_BoardLogic[i + c][j]->ResetStatus();
								}

								for (	int c = -1; 
										c <= 1; 
										c = c + 2	)
								{
									this->m_BoardLogic[i + c][j + 1]->ResetStatus();
								}
							}
						}
					}
				}

				;

				//	Jelly Fish matching !
				{
					// Jelly Fish 4 - O Candy!
					if (	(	i < (this->m_BoardHeight - 1)	)				&&
							(	j < (this->m_BoardWidth - 1)	)				&&
							(!_MatchOnThisGrid_)								)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID())		&& 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID())		&&
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j + 1]->g_KindID())	&&
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i][j + 1]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		&&
								(this->m_BoardLogic[i + 1][j + 1]->g_Can(2))	)
						{						
							_MatchOnThisGrid_		= true;
							_SwappedFound_			= false;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1) + (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														this->m_Candies[_Where_]->g_PositionPrp(2) - (this->m_Candies[_Where_]->g_MeasuresPrp(2) / 2.0),
														ScoreSys::Fishy4Match, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);							





							//	Hitpoints stuff...
							{
								for (	int c = 0; 
										c < 4; 
										++c	)
								{
									if (this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
									{
										this->m_Candies[this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt()]->HitOne_HP();
										this->m_Candies[this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt()]->s_InstaState(TheCandy::enm_InstaState::IsMatched);
									}
								}
							}
							
							//	Swapped candies stuff...
							{
								//	Step #1 :	Find swapped candies
								{
									for (	int c = 0;
											c < 4;
											++c	)
									{	
										this->_Where_	= this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt();



										if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
										{
											_IsSwappingMatch_	= true;



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
											{
												_SwappedFound_	= true;

												break;
											}
										}
										else
										{
											this->_Where_ = def::enm_Defines::_NOT_FOUND;
										}
									}
								}

								//	Step #2 :	If swappeds are busy, then find any other candy.
								{
									if (!_SwappedFound_)
									{
										for (	int c = 0;
												c < 4;
												++c	)
										{	
											this->_Where_	= this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt();



											if (	(this->m_Candies[this->_Where_]->g_IsSwapping(4))	)
											{
												_IsSwappingMatch_	= true;



												if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1))
												{
													_SwappedFound_	= true;

													break;
												}
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Step #3 :	If no swappeds, then find any.
								{
									if (!_SwappedFound_)
									{
										for (	int c = 0;
												c < 4;
												++c	)
										{	
											this->_Where_	= this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt();



											if (	(this->m_Candies[this->_Where_]->g_ItemID() == 1)	)
											{
												break;													
											}
											else
											{
												this->_Where_ = def::enm_Defines::_NOT_FOUND;
											}
										}
									}
								}

								//	Finally, assign properties.
								{
									if (this->_Where_ != def::enm_Defines::_NOT_FOUND)
									{
										this->_Sounds_->Play(		snd::SndSys::FishySound, 1	);



										this->m_Candies[this->_Where_]->s_ItemID(STA_::enm_ItemID::JellyFish);								//	Set a jelly fish.
										this->m_Candies[this->_Where_]->AddOne_HP(1);														//	Add one HP to candy.
										this->m_Candies[this->_Where_]->Trigger_SpecialCandyCreated(this->m_Prospform->g_FollowTime());		//	Pretty obvious.	
									
										this->m_Prospform->AddParticle(	this->m_Candies[this->_Where_]	);				//	Prospform exception.
									}
								}



								//	Prosform (not an actual logic matcher).
								{
									for (	int c = 0; 
											c < 4; 
											++c	)
									{
										if (	(this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)	&&
												(_Where_ != def::enm_Defines::_NOT_FOUND)														)
										{
											this->m_Candies[this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt()]->s_DropCrush(false);
											this->m_Candies[this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->g_CandyAt()]->s_LinkerProspform(this->m_Candies[_Where_]);
										}
									}
								}
							}

							//	Board stuff...
							{
								for (	int c = 0; 
										c < 4; 
										++c	)
								{
									this->m_BoardLogic[i + (c / 2)][j + (c % 2)]->ResetStatus();
								}
							}
						}
					}
				}

				;

				//	Three matching !
				{
					// Vertical Match!
					if ((	(i > 0) && (i < (this->m_BoardHeight - 1)) ) && (!_MatchOnThisGrid_)	)
					{
						if (	(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i - 1][j]->g_KindID()) && 
								(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i + 1][j]->g_KindID()) &&
								(this->m_BoardLogic[i - 1][j]->g_Can(2))		&& 
								(this->m_BoardLogic[i][j]->g_Can(2))			&& 
								(this->m_BoardLogic[i + 1][j]->g_Can(2))		)
						{						
							_MatchOnThisGrid_		= true;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::BasicMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);
							this->_Sounds_->Play(	snd::SndSys::MatchSound, 0	);





							for (	int c = -1; 
									c <= 1; 
									c++	)
							{
								if (this->m_BoardLogic[i + c][j]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies.at(this->m_BoardLogic[i + c][j]->g_CandyAt())->HitOne_HP();
									this->m_Candies.at(this->m_BoardLogic[i + c][j]->g_CandyAt())->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}
							}

							for (	int c = -1; 
									c <= 1; 
									c++	)
							{
								this->m_BoardLogic[i + c][j]->ResetStatus();
							}
						}
					}

					// Horizontal Match!
					if ((	(j > 0) && (j < (this->m_BoardWidth - 1)) ) && (!_MatchOnThisGrid_)	)
					{
						if ((this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j - 1]->g_KindID()) &&
							(this->m_BoardLogic[i][j]->g_KindID() == this->m_BoardLogic[i][j + 1]->g_KindID()) &&
							(this->m_BoardLogic[i][j - 1]->g_Can(2))	&&
							(this->m_BoardLogic[i][j]->g_Can(2))		&&
							(this->m_BoardLogic[i][j + 1]->g_Can(2)		)	)
						{
							_MatchOnThisGrid_		= true;
							this->_Where_			= this->m_BoardLogic[i][j]->g_CandyAt();

							this->m_Scores->AddScore(	this->m_Candies[_Where_]->g_PositionPrp(1)	,
														this->m_Candies[_Where_]->g_PositionPrp(2)	,
														ScoreSys::BasicMatch, def::enm_Defines::_USE_DEFAULT, true	,
														this->m_Candies[_Where_]->g_KindID()		);
							this->_Sounds_->Play(	snd::SndSys::MatchSound, 0	);





							for (	int c = -1; 
									c <= 1; 
									c++	)
							{
								if (this->m_BoardLogic[i][j + c]->g_CandyAt() != def::enm_Defines::_NOT_FOUND)
								{
									this->m_Candies.at(this->m_BoardLogic[i][j + c]->g_CandyAt())->HitOne_HP();
									this->m_Candies.at(this->m_BoardLogic[i][j + c]->g_CandyAt())->s_InstaState(TheCandy::enm_InstaState::IsMatched);
								}
							}

							for (	int c = -1; 
									c <= 1; 
									c++	)
							{
								this->m_BoardLogic[i][j + c]->ResetStatus();
							}
						}
					}
				}			
			}
		}
	}
	inline void			SpecialCandies()
	{
		//	.:.Logical Section.:.
		
		//	Stripped Candy.
		{
			//	Lighning particles.
			{
				std::vector<StrippedLightningParticle*>*		_Lightning_		= &this->m_Strippeds->g_Vec_Lightning();



				for (	int i = 0; 
						i < _Lightning_->size();
						++i	)
				{
					//	A particle got out of screen.
					if (	(_Lightning_->at(i)->g_PositionPrp(1) <= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::LeftBorder) - 100.0))	|| 
							(_Lightning_->at(i)->g_PositionPrp(1) >= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::RightBorder) + 100.0))	||
							(_Lightning_->at(i)->g_PositionPrp(2) <= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Floor) - 100.0))			||
							(_Lightning_->at(i)->g_PositionPrp(2) >= (this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Cieling) + 100.0))		)	
					{
						tls::EraseElement<StrippedLightningParticle*>(		*_Lightning_, i		);
					}
					else
					{
						//	Collision part.
						//	Free for all or use a vector.
						{
							if (	_Lightning_->at(i)->g_CollisionForAll()	)
							{
								//	Check collision.
								{
									this->_Size_Candies_		= this->m_Candies.size();



									for (	int k = 0;
											k < this->_Size_Candies_;
											++k	)
									{
										if (	tls::CollidesWith(	_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)	,
																	_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2)	,
																	_Lightning_->at(i)->g_MeasuresPrp(1), _Lightning_->at(i)->g_MeasuresPrp(2)		,
																	this->m_Candies[k]->g_PositionPrp(1), this->m_Candies[k]->g_PositionPrp(2)		,
																	this->m_Candies[k]->g_MeasuresPrp(1), this->m_Candies[k]->g_MeasuresPrp(2)		)	)
										{
											if (	(this->m_Candies[k]->g_Pos(1) >= 0)				&&		//	I
													(this->m_Candies[k]->g_Pos(2) >= 0)				&&		//	J
													(!this->m_Candies[k]->g_Is(5))					&&		//	Can't be invincible.
													(this->m_Candies[k]->g_Can(2))					)		//	Can be crushed.
											{
												this->m_Scores->AddScore(	this->m_Candies[k]->g_PositionPrp(1)	, 
																			this->m_Candies[k]->g_PositionPrp(2)	, 
																			ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false			, 
																			this->m_Candies[k]->g_KindID()			);



												this->m_Candies[k]->HitOne_HP();							//	Hit one HP.
												this->m_Candies[k]->s_Is(5, true);							//	Set invincible
												this->m_Candies[k]->SetTrg_IsInvincible(def::enm_Defines::_USE_DEFAULT);		//	for a moment.
												this->m_Candies[k]->SetCrushedAngle(	(_Lightning_->at(i)->g_ID(2) == def::enm_Directions::Right) ? 0.0 : 180.0	);
												this->m_Candies[k]->s_ExtraSpeed(	_Lightning_->at(i)->g_PositionPrp(3)	,
																					_Lightning_->at(i)->g_PositionPrp(4)	);

												this->m_BoardLogic[this->m_Candies[k]->g_Pos(1)][this->m_Candies[k]->g_Pos(2)]->s_Can(1, false);
											}
										}
									}

								}

								//	Paint board.
								{
									for (	int k = 0;
											k < this->m_BoardHeight;
											++k	)
									{
										for (	int l = 0;
												l < this->m_BoardWidth;
												++l	)
										{
											if (	tls::CollidesWith(	this->m_BoardVisual[k][l]->g_PositionPrp(1), this->m_BoardVisual[k][l]->g_PositionPrp(2)	,
																		this->m_BoardVisual[k][l]->g_MeasuresPrp(1), this->m_BoardVisual[k][l]->g_MeasuresPrp(2)	,
																		_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)				,
																		_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2)				,
																		_Lightning_->at(i)->g_MeasuresPrp(2), _Lightning_->at(i)->g_MeasuresPrp(2)					)	)
											{
												this->m_BoardVisual[k][l]->UseColorKind(	_Lightning_->at(i)->g_ID(1)		);
											}
										}
									}
								}
							}
							else
							{
								if (	(_Lightning_->at(i)->g_ID(2) == def::enm_Directions::Left)	||
										(_Lightning_->at(i)->g_ID(2) == def::enm_Directions::Right)	)
								{
									//	Check collision.
									{
										if (			(0 <= _Lightning_->at(i)->g_Pos(1))				&& 
												(_Lightning_->at(i)->g_Pos(1) < this->m_BoardHeight)	)
										{
											for (	int k = 0;
													k < this->_ATs_Row_[_Lightning_->at(i)->g_Pos(1)].size();
													++k	)
											{
												this->_Where_		= this->_ATs_Row_[_Lightning_->at(i)->g_Pos(1)][k];



												if (	tls::CollidesWith(	_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)							,
																			_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2)							,
																			_Lightning_->at(i)->g_MeasuresPrp(1), _Lightning_->at(i)->g_MeasuresPrp(2)								,
																			this->m_Candies[this->_Where_]->g_PositionPrp(1), this->m_Candies[this->_Where_]->g_PositionPrp(2)		,
																			this->m_Candies[this->_Where_]->g_MeasuresPrp(1), this->m_Candies[this->_Where_]->g_MeasuresPrp(2)		)	)
												{
													if (	(this->m_Candies[this->_Where_]->g_Pos(1) >= 0)				&&		//	I
															(this->m_Candies[this->_Where_]->g_Pos(2) >= 0)				&&		//	J
															(!this->m_Candies[this->_Where_]->g_Is(5))					&&		//	Can't be invincible.
															(this->m_Candies[this->_Where_]->g_Can(2))					)		//	Can be crushed.
													{
														this->m_Scores->AddScore(	this->m_Candies[this->_Where_]->g_PositionPrp(1)	, 
																					this->m_Candies[this->_Where_]->g_PositionPrp(2)	, 
																					ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false			, 
																					this->m_Candies[this->_Where_]->g_KindID()			);



														this->m_Candies[this->_Where_]->HitOne_HP();							//	Hit one HP.
														this->m_Candies[this->_Where_]->s_Is(5, true);							//	Set invincible
														this->m_Candies[this->_Where_]->SetTrg_IsInvincible(def::enm_Defines::_USE_DEFAULT);		//	for a moment.
														this->m_Candies[this->_Where_]->SetCrushedAngle(	(_Lightning_->at(i)->g_ID(2) == def::enm_Directions::Right) ? 0.0 : 180.0	);
														this->m_Candies[this->_Where_]->s_ExtraSpeed(	_Lightning_->at(i)->g_PositionPrp(3)	,
																										_Lightning_->at(i)->g_PositionPrp(4)	);
													
														this->m_BoardLogic[this->m_Candies[this->_Where_]->g_Pos(1)][this->m_Candies[this->_Where_]->g_Pos(2)]->s_Can(1, false);
													}
												}
											}
										}
									}

									//	Paint board.
									{
										if (			(0 <= _Lightning_->at(i)->g_Pos(1))				&& 
												(_Lightning_->at(i)->g_Pos(1) < this->m_BoardHeight)	)
										{
											this->_Where_ = _Lightning_->at(i)->g_Pos(1);



											for (	int k = 0;
													k < this->m_BoardWidth;
													++k	)
											{
												if (	tls::CollidesWith(	this->m_BoardVisual[this->_Where_][k]->g_PositionPrp(1), this->m_BoardVisual[this->_Where_][k]->g_PositionPrp(2)	,
																			this->m_BoardVisual[this->_Where_][k]->g_MeasuresPrp(1), this->m_BoardVisual[this->_Where_][k]->g_MeasuresPrp(2)	,
																			_Lightning_->at(i)->g_PositionPrp(1) + ((this->m_GridBound - _Lightning_->at(i)->g_MeasuresPrp(1)) / 2.0)			,
																			_Lightning_->at(i)->g_PositionPrp(2) - ((this->m_GridBound - _Lightning_->at(i)->g_MeasuresPrp(2)) / 2.0)			,
																			_Lightning_->at(i)->g_MeasuresPrp(2), _Lightning_->at(i)->g_MeasuresPrp(2)											)	)
												{
													this->m_BoardVisual[this->_Where_][k]->UseColorKind(_Lightning_->at(i)->g_ID(1));
												}
											}
										}
									}
								}
								else
								{
									//	Check collision.
									{
										if (			(0 <= _Lightning_->at(i)->g_Pos(2))				&&
												(_Lightning_->at(i)->g_Pos(1) < this->m_BoardWidth)	)
										{
											for (	int k = 0;
													k < this->_ATs_Column_[_Lightning_->at(i)->g_Pos(2)].size();
													++k	)
											{
												this->_Where_ = this->_ATs_Column_[_Lightning_->at(i)->g_Pos(2)][k];



												if (tls::CollidesWith(	_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)							,
																		_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2)							,
																		_Lightning_->at(i)->g_MeasuresPrp(1), _Lightning_->at(i)->g_MeasuresPrp(2)								,
																		this->m_Candies[this->_Where_]->g_PositionPrp(1), this->m_Candies[this->_Where_]->g_PositionPrp(2)		,
																		this->m_Candies[this->_Where_]->g_MeasuresPrp(1), this->m_Candies[this->_Where_]->g_MeasuresPrp(2))		)
												{
													if (	(this->m_Candies[this->_Where_]->g_Pos(1) >= 0)			&&		//	I
															(this->m_Candies[this->_Where_]->g_Pos(2) >= 0)			&&		//	J
															(!this->m_Candies[this->_Where_]->g_Is(5))				&&		//	Can't be invincible.
															(this->m_Candies[this->_Where_]->g_Can(2))				)		//	Can be crushed
													{
														this->m_Scores->AddScore(	this->m_Candies[this->_Where_]->g_PositionPrp(1)	,
																					this->m_Candies[this->_Where_]->g_PositionPrp(2)	,
																					ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false			,
																					this->m_Candies[this->_Where_]->g_KindID()			);



														this->m_Candies[this->_Where_]->HitOne_HP();							//	Hit one HP.
														this->m_Candies[this->_Where_]->s_Is(5, true);							//	Set invincible
														this->m_Candies[this->_Where_]->SetTrg_IsInvincible(def::enm_Defines::_USE_DEFAULT);		//	for a moment.
														this->m_Candies[this->_Where_]->SetCrushedAngle(	(_Lightning_->at(i)->g_ID(2) == def::enm_Directions::Up) ? 90.0 : 270.0	);
														this->m_Candies[this->_Where_]->s_ExtraSpeed(			_Lightning_->at(i)->g_PositionPrp(3)	,
																												_Lightning_->at(i)->g_PositionPrp(4)	);

														this->m_BoardLogic[this->m_Candies[this->_Where_]->g_Pos(1)][this->m_Candies[this->_Where_]->g_Pos(2)]->s_Can(1, false);
													}
												}
											}
										}
									}

									//	Paint board.
									{
										if (			(0 <= _Lightning_->at(i)->g_Pos(2))				&&
												(_Lightning_->at(i)->g_Pos(1) <= this->m_BoardWidth)	)
										{
											this->_Where_ = _Lightning_->at(i)->g_Pos(2);



											for (	int k = 0;
													k < this->m_BoardHeight;
													++k	)
											{
												if (	tls::CollidesWith(	this->m_BoardVisual[k][this->_Where_]->g_PositionPrp(1), this->m_BoardVisual[k][this->_Where_]->g_PositionPrp(2)	,
																			this->m_BoardVisual[k][this->_Where_]->g_MeasuresPrp(1), this->m_BoardVisual[k][this->_Where_]->g_MeasuresPrp(2)	,
																			_Lightning_->at(i)->g_PositionPrp(1) + ((this->m_GridBound - _Lightning_->at(i)->g_MeasuresPrp(1)) / 2.0)			,
																			_Lightning_->at(i)->g_PositionPrp(2) - ((this->m_GridBound - _Lightning_->at(i)->g_MeasuresPrp(2)) / 2.0)			,
																			_Lightning_->at(i)->g_MeasuresPrp(2), _Lightning_->at(i)->g_MeasuresPrp(2))											)
												{
													this->m_BoardVisual[k][this->_Where_]->UseColorKind(_Lightning_->at(i)->g_ID(1));
												}
											}
										}
									}
								};
							};
						};

						//	Move particle.
						{
							_Lightning_->at(i)->DoParticle();
						}

						//	Then, create sparkles.
						{
							this->m_Strippeds->AddSparkle(	_Lightning_->at(i)	);
						}

						//	Light explosion.
						{
							if (	_Lightning_->at(i)->g_LightExplodes()	)
							{
								//	Collision detection.
								{
									int			_Counter_ = 0.0;



									//	---------------------------------------------------
									//		Segment delegated to search collisions.
									//						m_Candy
									//	---------------------------------------------------
									{
										for (	int k = 0; 
												k < this->m_Candies.size(); 
												++k	)
										{
											if (	tls::CollidesWith(	(_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)) - (m_GridBound * (_Lightning_->at(i)->g_Expladious() - 1.5))	,
																		(_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2)) + (m_GridBound * (_Lightning_->at(i)->g_Expladious() - 1.5))	,
																		m_GridBound * ((_Lightning_->at(i)->g_Expladious() - 1.0) * 2.0)					,
																		m_GridBound * ((_Lightning_->at(i)->g_Expladious() - 1.0) * 2.0)					,
																		this->m_Candies[k]->g_PositionPrp(1), this->m_Candies[k]->g_PositionPrp(2)			, 
																		this->m_Candies[k]->g_MeasuresPrp(1), this->m_Candies[k]->g_MeasuresPrp(2)			)	)			
											{
												if (					(i != k)				&&
														(this->m_Candies[k]->g_Can(2))			&&
														(this->m_Candies[k]->g_Pos(1) >= 0)		&&
														(this->m_Candies[k]->g_Pos(2) >= 0)		)							
												{
													this->m_Candies[k]->HitOne_HP();

													//	Adding scores.
													{
														this->m_Scores->AddScore(	this->m_Candies[k]->g_PositionPrp(1)		, 
																					this->m_Candies[k]->g_PositionPrp(2)		, 
																					ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	, 
																					this->m_Candies[k]->g_KindID()				);
													}

													//	Crushed event.
													{
														this->m_Candies[k]->CalculateCrushedAngle(	_Lightning_->at(i)->g_PositionPrp(1) + (_Lightning_->at(i)->g_SpriteMeasures(1) * 0.5)	,
																									_Lightning_->at(i)->g_PositionPrp(2) - (_Lightning_->at(i)->g_SpriteMeasures(2) * 0.5)	);
														this->m_Candies[k]->s_ExtraSpeed(			this->m_Wrappeds->g_Data(4), this->m_Wrappeds->g_Data(4)	);
													}



													++_Counter_;
												}
												
											}

											//	Kinda, to make it less laggy.
											if (_Counter_ >= 12)
											{
												break;
											}
										}
									}   

									//	---------------------------------------------------
									//			Segment delegated to make effects.
									//						m_BoardVisual
									//	---------------------------------------------------
									{
										//	Setting the new iPos and jPos of the candy.
										int		_I_		= round(	(this->yP - (_Lightning_->at(i)->g_PositionPrp(2) + _Lightning_->at(i)->g_HitBoxPosition(2))) / this->m_GridBound	);
										int		_J_		= round(	((_Lightning_->at(i)->g_PositionPrp(1) + _Lightning_->at(i)->g_HitBoxPosition(1)) - this->xP) / this->m_GridBound	);



										for (	int m = -1; m <= 1; ++m	)
										{
											for (	int n = -1; n <= 1; ++n	)
											{
												if (	((0 <= (_I_ + m)) && ((_I_ + m) < (this->m_BoardHeight)))	&&
														((0 <= (_J_ + n)) && ((_J_ + n) < (this->m_BoardWidth)))	)
												{
													this->m_BoardVisual[_I_ + m][_J_ + n]->UseColorKind(	_Lightning_->at(i)->g_ID(1)		);
												}
											}
										}
									}
								}

								//	Explosion push.
								{
									for (	int k = 0; 
											k < this->m_Candies.size(); 
											++k	)
									{
										switch (	this->m_Candies[k]->g_GravityDirection(1)	)
										{
										case		def::enm_Directions::Down:
											//	---------------------------------------------------
											//		Segment delegated to search collisions.
											//						m_Candy
											//	---------------------------------------------------
											{
												//	Upper detection.
												if (	(_Lightning_->at(i)->g_PositionPrp(2) <= this->m_Candies[k]->g_PositionPrp(2))	&&
														(	((_Lightning_->at(i)->g_Pos(2) - 1) <= this->m_Candies[k]->g_Pos(2)	)		&&
														(	this->m_Candies[k]->g_Pos(2) <= (_Lightning_->at(i)->g_Pos(2) + 1)  )		)	)
												{	
													if (	this->m_Candies[k]->g_Can(1)	)
													{
														this->m_Candies[k]->s_PositionPrp(4, this->m_Candies[k]->g_PositionPrp(4) + this->m_Wrappeds->g_Data(2));
													}					
												}
											}  
										
											break;
										}
									}
								}

								//	Sound part.
								{
									this->_Sounds_->Play(snd::SndSys::Wrapped, 3);
								}

								//	Delete this lightning.
								{
									tls::EraseElement<StrippedLightningParticle*>(		*_Lightning_, i		);
								}
							}
						}
					}
				}
			}
		};

		//	Wrapped Candy.
		{
			//	This part is to explode the wrapped fuse.
			{	
				this->m_Wrappeds->EnableCounter();
				this->_Size_Candies_		= this->m_Candies.size();



				//	Searching for action.
				{
					for (	int i = 0;
							i < this->_Size_Candies_;
							++i	)
					{
						if (	(this->m_Candies[i]->g_Is(1))											||		//	Is falling									?	
								(this->m_Candies[i]->g_Is(2))											||		//	Is bouncing									?
								(this->m_Candies[i]->g_IsSwapping(1))									||		//	Is swapping									?
								(this->m_Fishes->g_FishesAreSwimming())									||		//	Is fish swimming							?
								(this->m_Candies[i]->g_Fc_Is(1))										||		//	Is frozen in action							?
								(this->m_Candies[i]->g_BoB_Is(1))										||		//	Is Bom-O-Bom in action too					?
								(this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::Waiting)	||		//	Wrapped candy or BubbleGum is exploding		?
								(!this->m_FireWorks->g_IsEmpty())										)		//	Are there any fireworks						?
						{		
							this->m_Wrappeds->ResetCounter();
							break;
						}
					}
				}

				//	Triggering the explosions.
				{
					if (	this->m_Wrappeds->g_Trigger(1) == def::enm_Triggers::Activated	)
					{
						for (	int i = 0;
								i < this->_Size_Candies_;
								++i	)
						{
							if (this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)
							{
								this->m_Candies[i]->HitOne_HP();
								this->m_Candies[i]->s_Can(2, true);
							}
						}
					}
				}
			}
		}

		//	Frozen Candy.
		{
			this->m_Frozens->DoTrackers(	this->m_Candies	);
		}

		//	Bom-O-Bom.
		{
			this->m_BonOBoms->DoTrackers(	this->m_Candies	);
		}

		//	Popping candies.
		{
			this->m_PoppingCandies->DoTrackers(		this->m_Candies		);
		}
	}
	inline void			CrushingTime()
	{
		//	--------------------------------------------------------------
		//		   This 'if' is when candies are about to be crushed.
		//		One condition is that they are called to be crushed...
		//					...and they can be crushed.
		//	--------------------------------------------------------------
		for (int i = 0; i < this->m_Candies.size(); ++i)
		{
			//	For those candies that are erased instantly.
			if (	this->m_Candies[i]->g_InstaDelete()		)
			{
				tls::EraseElement(this->m_Candies, i);
				continue;
			}

			//	InstaStatus:	Get your matched, crushed, anything...
			{
				//	Candies that were matched recently.
				if (	(	(this->m_Candies[i]->g_InstaState() == TheCandy::enm_InstaState::IsMatched)		||
							(this->m_Candies[i]->g_InstaState() == TheCandy::enm_InstaState::EatenByFish)		||
							(this->m_Candies[i]->g_InstaState() == TheCandy::enm_InstaState::FusedByBoB)		)	&&
						(this->m_Candies[i]->g_ItemID() < STA_::enm_ItemID::CupCake_1)							)
				{	
					//	Cupcake destruction.
					this->m_CupCakes->CheckNear(	this->m_Candies[i]		);
				}
			}

			//	Can be crushed?
			if (this->m_Candies[i]->g_Can(2))
			{
				// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				//	We split normal candies and special candies when crushed.
				// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				if (this->m_Candies[i]->g_TotalHP() <= 0)
				{		
					if (	this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::CommonCandy		)
					{
						//	This is just about the crushing particles.
						{
							if (	this->m_Candies[i]->g_DropCrush()	)
							{
								this->m_CrushEffect->AddCrush(	this->m_Candies[i]	);
							}
						}
						
						//	This is about the special projectile form... (prospform for short)
						{
							if (	!this->m_Candies[i]->g_DropCrush()	)
							{
								this->m_Prospform->AddParticle(		this->m_Candies[i]->g_PositionPrp(1)	,
																	this->m_Candies[i]->g_PositionPrp(2)	,
																	this->m_Candies[i]->g_LinkerProspform()	);
							}
						}

						//	Random spawns like: Coins.
						{
							if (	this->m_Candies[i]->g_DropCrush()	)
							{
								this->m_Coins->AddCoin(this->m_Candies[i]);
							}
						}



						tls::EraseElement<TheCandy*>(this->m_Candies, i);
					}
					else
					{
						switch (	this->m_Candies[i]->g_ItemID()	)
						{
						case		STA_::enm_ItemID::StrippedH:
							//	Valid iPos and jPos.
							{
								if (	(this->m_Candies[i]->g_Pos(1) < 0)		||
										(this->m_Candies[i]->g_Pos(2) < 0)		)
								{
									break;
								}
							}

							//	Adding lightnings.
							{
								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Left													,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0		)	,
																	false																		);

								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Right													,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0		)	,
																	false																		);
							}

							//	Board Stuff.
							{
								for (	int k = 0; 
										k < this->m_BoardWidth; 
										++k)
								{								
									this->m_BoardLogic[this->m_Candies[i]->g_Pos(1)][k]->s_Can(1, false);
								}
							}

							//	Deleting candy.
							{
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
							}

							//	Sound part.
							{
								this->_Sounds_->Play(snd::SndSys::Stripped, 2);
							}

							break;

						case		STA_::enm_ItemID::StrippedV:
							//	Valid iPos and jPos.
							{
								if ((this->m_Candies[i]->g_Pos(1) < 0) ||
									(this->m_Candies[i]->g_Pos(2) < 0))
								{
									break;
								}
							}

							//	Adding lightnings.
							{
								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Up																,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);

								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Down															,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)								, 
																					this->m_Candies[i]->g_Pos(2)								),	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);
							}

							//	Board Stuff.
							{
								for (	int k = 0; 
										k < this->m_BoardHeight; 
										++k)
								{
									this->m_BoardLogic[k][this->m_Candies[i]->g_Pos(2)]->s_Can(1, false);
								}
							}

							//	Deleting candy.
							{
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
							}

							//	Sound part.
							{
								this->_Sounds_->Play(snd::SndSys::Stripped, 2);
							}

							break;

						case		STA_::enm_ItemID::WrappedCandy:
							//	Basic triggering the explosion.
							{	
								//	Play charging sound.
								{
									if (this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::NotInitialized)
									{
										this->_Sounds_->Play(snd::SndSys::Wrapped, 2);
									}
								}

								this->m_Candies[i]->Trigger_WrappedExplosion(	this->m_Wrappeds->g_Timing(1)	);
							} 

							//	Checking for the trigger.
							{
								if (	this->m_Candies[i]->g_Trigger(2) == def::enm_Triggers::Activated	)
								{
									//	Collision detection.
									{
										int			_Counter_ = 0.0;



										//	---------------------------------------------------
										//		Segment delegated to search collisions.
										//						m_Candy
										//	---------------------------------------------------
										{
											for (	int k = 0; 
													k < this->m_Candies.size(); 
													++k	)
											{
												//	Basic collision.
												if (	tls::CollidesWith(	this->m_Candies[i]->g_PositionPrp(1) - (this->m_Candies[i]->g_MeasuresPrp(1) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																			this->m_Candies[i]->g_PositionPrp(2) + (this->m_Candies[i]->g_MeasuresPrp(2) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																			this->m_Candies[i]->g_MeasuresPrp(1) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0)									, 
																			this->m_Candies[i]->g_MeasuresPrp(2) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0),
																			this->m_Candies[k]->g_PositionPrp(1), this->m_Candies[k]->g_PositionPrp(2)				, 
																			this->m_Candies[k]->g_MeasuresPrp(1)													, 
																			this->m_Candies[k]->g_MeasuresPrp(2))													)	
												{
													if (					(i != k)							&&
															(this->m_Candies[k]->g_Can(2))						&&
															(this->m_Candies[k]->g_Pos(1) >= 0)					&&		
															(this->m_Candies[k]->g_Pos(2) >= 0)					)					
													{
														this->m_Candies[k]->HitOne_HP();

														//	Adding scores.
														{
															this->m_Scores->AddScore(	this->m_Candies[k]->g_PositionPrp(1)		, 
																						this->m_Candies[k]->g_PositionPrp(2)		, 
																						ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	, 
																						this->m_Candies[k]->g_KindID()				);
														}
														
														//	Crushed event.
														{
															this->m_Candies[k]->CalculateCrushedAngle(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_SpriteMeasures(1) * 0.5)	,
																										this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_SpriteMeasures(2) * 0.5)	);
															this->m_Candies[k]->s_ExtraSpeed(			this->m_Wrappeds->g_Data(3), this->m_Wrappeds->g_Data(3)	);
														}



														++_Counter_;
													}
													
												}

												//	Kinda, to make it less laggy.
												if (_Counter_ >= 12)
												{
													break;
												}
											}
										}   

										//	---------------------------------------------------
										//			Segment delegated to make effects.
										//						m_BoardVisual
										//	---------------------------------------------------
										{
											int		_I_ = this->m_Candies[i]->g_Pos(1);
											int		_J_ = this->m_Candies[i]->g_Pos(2);



											for (int m = -1; m <= 1; ++m)
											{
												for (int n = -1; n <= 1; ++n)
												{
													if (((0 <= (_I_ + m)) && ((_I_ + m) < (this->m_BoardHeight))) &&
														((0 <= (_J_ + n)) && ((_J_ + n) < (this->m_BoardWidth))))
													{
														this->m_BoardVisual[_I_ + m][_J_ + n]->UseColorKind(this->m_Candies[i]->g_KindID());
													}
												}
											}
										}
									}

									//	Explosion push.
									{
										for (	int k = 0; 
												k < this->m_Candies.size(); 
												++k	)
										{
											switch (	this->m_Candies[k]->g_GravityDirection(1)	)
											{
											case		def::enm_Directions::Down:
												//	---------------------------------------------------
												//		Segment delegated to search collisions.
												//						m_Candy
												//	---------------------------------------------------
												{
													//	Upper detection.
													if (	(this->m_Candies[i]->g_PositionPrp(2) <= this->m_Candies[k]->g_PositionPrp(2))	&&
															(	((this->m_Candies[i]->g_Pos(2) - 1) <= this->m_Candies[k]->g_Pos(2)	)		&&
															(	this->m_Candies[k]->g_Pos(2) <= (this->m_Candies[i]->g_Pos(2) + 1)  )		)	)
													{	
														if (	this->m_Candies[k]->g_Can(1)	)
														{
															this->m_Candies[k]->s_PositionPrp(4, this->m_Candies[k]->g_PositionPrp(4) + this->m_Wrappeds->g_Data(1));
														}					
													}
												}  
											
												break;
											}
										}
									}

									//	Second phase of the wrapped candy.
									{
										this->m_Candies[i]->s_ItemID(5);			//	Now, it is a wrapped fuse.
										this->m_Candies[i]->AddOne_HP(1);			//	Add one HP.
										this->m_Candies[i]->s_Can(3, false);		//	Finally, set that can't be matched.
										this->m_Candies[i]->s_Can(2, false);		//	And set that can't be crushed.
										this->m_Candies[i]->EnableShaking(true);	//	Shaking.

										this->m_Wrappeds->AddWrapped(	this->m_Candies[i]	);
									}

									//	Sound part.
									{
										this->_Sounds_->Play(snd::SndSys::Wrapped, 3);
									}
								}
							}
							
							break;

						case STA_::enm_ItemID::WrappedFuse:
							//	Go and make an explosion >:D
							{
								//	Collision detection.
								{
									int			_Counter_ = 0.0;



									//	---------------------------------------------------
									//		Segment delegated to search collisions.
									//						m_Candy
									//	---------------------------------------------------
									{
										for (	int k = 0; 
												k < this->m_Candies.size(); 
												++k	)
										{
											if (	tls::CollidesWith(	this->m_Candies[i]->g_PositionPrp(1) - (this->m_Candies[i]->g_MeasuresPrp(1) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																		this->m_Candies[i]->g_PositionPrp(2) + (this->m_Candies[i]->g_MeasuresPrp(2) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																		this->m_Candies[i]->g_MeasuresPrp(1) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0)									,
																		this->m_Candies[i]->g_MeasuresPrp(2) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0)									,
																		this->m_Candies[k]->g_PositionPrp(1), this->m_Candies[k]->g_PositionPrp(2)				, 
																		this->m_Candies[k]->g_MeasuresPrp(1)													, 
																		this->m_Candies[k]->g_MeasuresPrp(2))													)			
											{
												if (					(i != k)				&&
														(this->m_Candies[k]->g_Can(2))			&&
														(this->m_Candies[k]->g_Pos(1) >= 0)		&&
														(this->m_Candies[k]->g_Pos(2) >= 0)		)							
												{
													this->m_Candies[k]->HitOne_HP();

													//	Adding scores.
													{
														this->m_Scores->AddScore(	this->m_Candies[k]->g_PositionPrp(1)		, 
																					this->m_Candies[k]->g_PositionPrp(2)		, 
																					ScoreSys::NormalCandy, def::enm_Defines::_USE_DEFAULT, false	, 
																					this->m_Candies[k]->g_KindID()				);
													}

													//	Crushed event.
													{
														this->m_Candies[k]->CalculateCrushedAngle(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_SpriteMeasures(1) * 0.5)	,
																									this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_SpriteMeasures(2) * 0.5)	);
														this->m_Candies[k]->s_ExtraSpeed(			this->m_Wrappeds->g_Data(4), this->m_Wrappeds->g_Data(4)	);
													}



													++_Counter_;
												}
												
											}

											//	Kinda, to make it less laggy.
											if (_Counter_ >= 12)
											{
												break;
											}
										}
									}   

									//	---------------------------------------------------
									//			Segment delegated to make effects.
									//						m_BoardVisual
									//	---------------------------------------------------
									{
										int		_I_ = this->m_Candies[i]->g_Pos(1);
										int		_J_ = this->m_Candies[i]->g_Pos(2);



										for (int m = -1; m <= 1; ++m)
										{
											for (int n = -1; n <= 1; ++n)
											{
												if (	((0 <= (_I_ + m)) && ((_I_ + m) < (this->m_BoardHeight)))	&&
														((0 <= (_J_ + n)) && ((_J_ + n) < (this->m_BoardWidth)))	)
												{
													this->m_BoardVisual[_I_ + m][_J_ + n]->UseColorKind(this->m_Candies[i]->g_KindID());
												}
											}
										}
									}
								}

								//	Explosion push.
								{
									for (	int k = 0; 
											k < this->m_Candies.size(); 
											++k	)
									{
										switch (	this->m_Candies[k]->g_GravityDirection(1)	)
										{
										case		def::enm_Directions::Down:
											//	---------------------------------------------------
											//		Segment delegated to search collisions.
											//						m_Candy
											//	---------------------------------------------------
											{
												//	Upper detection.
												if (	(this->m_Candies[i]->g_PositionPrp(2) <= this->m_Candies[k]->g_PositionPrp(2))	&&
														(	((this->m_Candies[i]->g_Pos(2) - 1) <= this->m_Candies[k]->g_Pos(2)	)		&&
														(	this->m_Candies[k]->g_Pos(2) <= (this->m_Candies[i]->g_Pos(2) + 1)  )		)	)
												{	
													if (	this->m_Candies[k]->g_Can(1)	)
													{
														this->m_Candies[k]->s_PositionPrp(4, this->m_Candies[k]->g_PositionPrp(4) + this->m_Wrappeds->g_Data(2));
													}					
												}
											}  
										
											break;
										}
									}
								}

								//	Candy ends here...
								{
									tls::EraseElement<TheCandy*>(this->m_Candies, i);
								}

								//	Sound part.
								{
									this->_Sounds_->Play(snd::SndSys::Wrapped, 3);
								}
							}

							break;

						case STA_::enm_ItemID::JellyFish:
							//	Controller part.
							{
								this->m_Fishes->AddFish(	this->m_Candies[i], this->m_Candies	);
							}

							//	Deleting candy.
							{
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
							}

							//	Sound part.
							{
								this->_Sounds_->Play(snd::SndSys::FishySound, 2);
							}	

							break;

						case STA_::enm_ItemID::FrozenCandy:
							//	If the candy is already crushed, then don't 
							//	crush it again.
							//	Also, a canBeCrushed guard is on the line.
							{
								if (	!this->m_Candies[i]->g_Fc_Is(1)	)
								{
									//	Controller part.
									{
										this->m_Frozens->AddTracker(	this->m_Candies[i], def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT					,	
																		tls::Vec4<double>(	this->xP, this->yP							, 
																							this->m_BoardWidth * this->m_GridBound		,
																							this->m_BoardHeight * this->m_GridBound	),
																		this->m_Candies, i												,
																		def::enm_Defines::_SKIP_THIS, def::enm_Defines::_SKIP_THIS		);
									}
								}
							}

							break;

						case STA_::enm_ItemID::BomOBom:
							//	Same as Frozen Candy but for the Bom-O-Bom case.
							{
								if (	!this->m_Candies[i]->g_BoB_Is(1)	)
								{
									//	Controller part.
									{
										this->m_BonOBoms->AddTracker(	this->m_Candies[i], def::enm_Defines::_USE_DEFAULT, def::enm_Defines::_USE_DEFAULT					, 
																		tls::Vec4<double>(	this->xP, this->yP							, 
																							this->m_BoardWidth * this->m_GridBound		,
																							this->m_BoardHeight * this->m_GridBound	),	
																		this->m_Candies, i, 
																		def::enm_Defines::_SKIP_THIS, def::enm_Defines::_SKIP_THIS		);
									}
								}
							}

							break;

						case STA_::enm_ItemID::Starlight:
							//	Valid iPos and jPos.
							{
								if (	(this->m_Candies[i]->g_Pos(1) < 0)		||
										(this->m_Candies[i]->g_Pos(2) < 0)		)
								{
									break;
								}
							}

							//	Adding lightnings.
							{
								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Left															,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);

								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Right															,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);
								
								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,	
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Up																,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)								, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);

								this->m_Strippeds->AddLightning(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_PositionPrp(2) - (this->m_GridBound / 2.0)			,
																	this->m_Candies[i]->g_KindID()												,
																	def::enm_Directions::Down															,
																	tls::Vec2<int>(	this->m_Candies[i]->g_Pos(1)	, 
																					this->m_Candies[i]->g_Pos(2)	)							,	
																	false, tls::Vec2<double>(1.0, 1.0)											,				
																	tls::Vec2<double>(	-this->m_Strippeds->g_LightningMeasures(1) / 2.0		, 
																						this->m_Strippeds->g_LightningMeasures(2) / 2.0			)		,
																	false																		);
							}

							//	Board Stuff.
							{
								//	Horizontal	........
								for (	int k = 0; 
										k < this->m_BoardWidth; 
										++k)
								{								
									this->m_BoardLogic[this->m_Candies[i]->g_Pos(1)][k]->s_Can(1, false);
								}

								//					:
								//	Vertical		:
								for (	int k = 0;
										k < this->m_BoardHeight;
										++k	)
								{
									this->m_BoardLogic[k][this->m_Candies[i]->g_Pos(2)]->s_Can(1, false);
								}
							}

							//	Deleting candy.
							{
								this->m_Strippeds->AddRememberStarLight(	this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0),
																			this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0),
																			this->m_Candies[i]->g_KindID()			);
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
							}

							//	Sound part.
							{
								this->_Sounds_->Play(snd::SndSys::Stripped, 2);
							}

							break;

						case STA_::enm_ItemID::FireWorkRocket:
							//	Spawning the firework.
							{
								this->m_FireWorks->SpawnFireWork(	this->m_Candies[i]		,
																	this->m_GridBound		);
							}

							//	Deleting candy.
							{
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
							}

							//	Sound part.
							{
								this->_Sounds_->Play(snd::SndSys::FireWorkRocket, 2);
							}

							break;

						case STA_::enm_ItemID::BubbleGum:
							//	Basic triggering the explosion.
							{	
								//	Play charging sound.
								{
									if (this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::NotInitialized)
									{
										this->_Sounds_->Play(snd::SndSys::Wrapped, 2);
									}
								}

								this->m_Candies[i]->Trigger_WrappedExplosion(this->m_Wrappeds->g_Timing(1));
							} 

							//	Checking for the trigger.
							{
								if (	this->m_Candies[i]->g_Trigger(2) == def::enm_Triggers::Activated	)
								{
									//	Collision detection (Paint part).
									{
										int			_Counter_ = 0.0;



										//	---------------------------------------------------
										//		Segment delegated to search collisions.
										//						m_Candy
										//	---------------------------------------------------
										{
											for (	int k = 0; 
													k < this->m_Candies.size(); 
													++k	)
											{
												//	Basic collision.
												if (	tls::CollidesWith(	this->m_Candies[i]->g_PositionPrp(1) - (this->m_Candies[i]->g_MeasuresPrp(1) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																			this->m_Candies[i]->g_PositionPrp(2) + (this->m_Candies[i]->g_MeasuresPrp(2) * (this->m_Candies[i]->g_Expladious() - 1.5))	,
																			this->m_Candies[i]->g_MeasuresPrp(1) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0)									, 
																			this->m_Candies[i]->g_MeasuresPrp(2) * ((this->m_Candies[i]->g_Expladious() - 1.0) * 2.0),
																			this->m_Candies[k]->g_PositionPrp(1), this->m_Candies[k]->g_PositionPrp(2)				, 
																			this->m_Candies[k]->g_MeasuresPrp(1)													, 
																			this->m_Candies[k]->g_MeasuresPrp(2))													)	
												{
													if (					(i != k)							&&
															(this->m_Candies[k]->g_Can(2))						&&
															(this->m_Candies[k]->g_Pos(1) >= 0)					&&		
															(this->m_Candies[k]->g_Pos(2) >= 0)					)					
													{
														//	Painting event.
														{
															this->m_Candies[k]->s_KindID(	this->m_Candies[i]->g_KindID()	);
															this->m_Candies[k]->SetTrg_CanBeMatched(	0.4		);
														}



														++_Counter_;
													}
													
												}

												//	Kinda, to make it less laggy.
												if (_Counter_ >= 12)
												{
													break;
												}
											}
										}   

										//	---------------------------------------------------
										//			Segment delegated to make effects.
										//						m_BoardVisual
										//	---------------------------------------------------
										{
											int		_I_ = this->m_Candies[i]->g_Pos(1);
											int		_J_ = this->m_Candies[i]->g_Pos(2);



											for (int m = -1; m <= 1; ++m)
											{
												for (int n = -1; n <= 1; ++n)
												{
													if (((0 <= (_I_ + m)) && ((_I_ + m) < (this->m_BoardHeight))) &&
														((0 <= (_J_ + n)) && ((_J_ + n) < (this->m_BoardWidth))))
													{
														this->m_BoardVisual[_I_ + m][_J_ + n]->UseColorKind(this->m_Candies[i]->g_KindID());
													}
												}
											}
										}
									}

									//	Deleting candy.
									{
										tls::EraseElement<TheCandy*>(this->m_Candies, i);
									}

									//	Sound part.
									{
										this->_Sounds_->Play(snd::SndSys::Wrapped, 3);
									}
								}
							}
							
							break;

						case STA_::enm_ItemID::PoppingCandy:
							//	If the candy is already crushed, then don't 
							//	crush it again.
							//	Also, a canBeCrushed guard is on the line.
							//	Applies for Frozen Candies, Bom-o-Bon and Popping Candies.
							{
								if (	!this->m_Candies[i]->g_Ppc_Is(1)	)
								{
									//	Controller part.
									{
										this->m_PoppingCandies->AddTracker(		this->m_Candies[i]		);
									}
								}
							}
							
							break;

						case STA_::enm_ItemID::CupCake_1:
							//	Basic syntax.
							//	May add a controller for this.
							{
								tls::EraseElement<TheCandy*>(this->m_Candies, i);
								break;
							}
						}
					}
				}
			}
		}
	}
		
	inline void			Clocks()
	{
		//	Board clocks.
		{
			for (	int i = 0; 
					i < this->m_BoardHeight; 
					++i	)
			{
				for (	int j = 0; 
						j < this->m_BoardWidth;
						++j	)
				{
					this->m_BoardLogic[i][j]->StartObjectCanFall();
					this->m_BoardVisual[i][j]->ColorEffect();
				}
			}
		}

		//	Candies clocks.
		{
			this->_Size_Candies_ = this->m_Candies.size();



			for (	int i = 0; 
					i < this->_Size_Candies_; 
					++i	)
			{
				//	Counters.
				{
					this->m_Candies[i]->IniCnt_IsInvincible()			;
					this->m_Candies[i]->IniCnt_CanFall()				;
					this->m_Candies[i]->IniCnt_CanBeCrushed()			;
					this->m_Candies[i]->IniCnt_CanBeMatched()			;
					this->m_Candies[i]->IniCnt_IsHidden()				;
					this->m_Candies[i]->IniCnt_InnerTime()				;
				}

				//	Triggers.
				{
					this->m_Candies[i]->IniTgg_IsOld()					;		
					this->m_Candies[i]->IniTgg_ExplodeNow()				;
				}

				//	Reset States.
				{
					this->m_Candies[i]->ResetInstaStates()				;
				}
			}
		}

		//	Controllers clocks.
		{
			//	Wrapped controller.
			{
				this->m_Wrappeds->StartCounter();
			}
		}
	}
	inline void			Animator()
	{
		//	.:.Logical Section.:.
		this->m_CupCakes->LogicDis();

		//	.:.Animations.:.
		this->m_CrushEffect->Animate()										;
		this->m_Scores->Animate()											;
		this->m_Prospform->Animate()										;
		this->m_Strippeds->Animate()										;
		this->m_Wrappeds->Animate()											;	
		this->m_Fishes->Animate(this->m_Candies)							;
		this->m_Frozens->Animate(this->m_BoardVisual)						;
		this->m_BonOBoms->Animate(this->m_BoardVisual)						;
		this->m_FireWorks->Animate(this->m_BoardLogic, this->m_Candies)		;
		this->m_PoppingCandies->Animate(this->m_Candies)					;
		this->m_Coins->Animate()											;
	}

//	-------------------------------------------
//				About spawn points
//	-------------------------------------------
public:
	inline void			CreateSpawnPoints() 
	{
		//	Once this function is called, the first thing to do is to update
		//	the internal values of the SpawnPoints controller.
		this->m_SpawnPoints->UpdateBoardValues(this->xP, this->yP, this->m_BoardWidth, this->m_BoardHeight);

		//	Then, of course, create the spawnpoints.
		this->m_SpawnPoints->CreateSpawnPoints();
	}

//	-------------------------------------------
//			About external effects
//	-------------------------------------------
public:
	inline void			SlowMotionFlashBang(	int Finished	)
	{
		
	}
	inline bool			IsBrandNew()
	{
		return		this->m_IsBrandNew;
	}

//	-------------------------------------------
//		  Loading and updating functions !
//	-------------------------------------------
public:
	inline void			CreateBoard(int _BoardWidth, int _BoardHeight, double OffSetX, double OffSetY)
	{
		this->m_IsBrandNew	= false;



		//	Re-positioning the board.
		{
			this->m_BoardWidth		= _BoardWidth;
			this->m_BoardHeight		= _BoardHeight;

			this->xP	= -((this->m_BoardWidth * this->m_GridBound) / 2.0);
			this->yP	= (this->_Draw_->g_WindowBounds(2) + (this->m_BoardHeight * this->m_GridBound)) / 2.0;
		}

		//	Creating the board (Logic).
		{
			if (this->m_BoardLogic == nullptr)
			{
				this->m_BoardLogic = new thyGrid_Logic * *[_BoardHeight];

				for (int i = 0; i < _BoardHeight; ++i)
				{
					this->m_BoardLogic[i] = new thyGrid_Logic * [_BoardWidth];

					for (int j = 0; j < _BoardWidth; ++j)
					{
						this->m_BoardLogic[i][j] = new thyGrid_Logic(1);
					}
				}
			}
		}

		//	Vectors of factorizing.
		{
			for (	int i = 0; 
					i < this->m_BoardWidth; 
					++i	)
			{
				this->_ATs_Column_.push_back(	std::vector<int>()		);
			}

			for (	int i = 0; 
					i < this->m_BoardHeight; 
					++i	)
			{
				this->_ATs_Row_.push_back(		std::vector<int>()		);
			}
		}



		this->CreateSpawnPoints();

		this->m_CntrlBoardVisual->GenerateBoard(	this->xP, this->yP, this->m_BoardHeight, this->m_BoardWidth, OffSetX, OffSetY		);
		this->m_FireWorks->SetBoardBounds(				this->m_BoardWidth, this->m_BoardHeight											);
		this->m_Scores->LoadVariables(this->xP, this->yP, this->m_BoardWidth, this->m_BoardHeight, this->m_GridBound);
		this->m_Scores->LoadAll();

		this->m_BoardVisual		= this->m_CntrlBoardVisual->g_VisualGrid();
	}
	
	inline void			Ld_Controllers()
	{	
		this->m_SpawnPoints			= new _Controller_SpawnPoints();
		this->m_CrushEffect			= new _Controller_CrushEffect(this->_Draw_, this->_Sprites_);
		this->m_Prospform			= new _Controller_SpecialForm(this->_Draw_, this->_Sprites_);
		this->m_SpecialMixes		= new _Controller_SpecialMixes();
		this->m_CntrlBoardVisual	= new _Controller_BoardVisual(this->_Draw_, this->_Sprites_);
		this->m_Coins				= new _Controller_Coin(this->_Draw_, this->_Sprites_, this->_Sounds_, this->_Mouse_, this->_SQL_);
		this->m_CupCakes			= new _Controller_CupCakes(this->_Draw_, this->_Sprites_, this->_Sounds_);
		this->m_SwitchController	= new Switcher(this->_Draw_, this->_Sprites_, this->_Sounds_);

		this->m_Strippeds		= new _Controller_Stripped(this->m_GridBound, this->m_GridBound, this->_Draw_, this->_Sprites_, this->_Sounds_);
		this->m_Scores			= new _Controller_Score(this->_Draw_, this->_Sprites_, this->_Text_, this->_Sounds_);
		this->m_Wrappeds		= new _Controller_Wrappeds(this->_Draw_, this->_Sprites_, this->_Sounds_);
		this->m_Fishes			= new _Controller_Fish(this->_Draw_, this->_Sprites_, this->_Sounds_, this->_Shader_, this->m_Scores);
		this->m_Frozens			= new _Controller_FrozenCandy(this->_Draw_, this->_Sprites_, this->_Sounds_, this->m_Scores, this->m_SpawnPoints);
		this->m_BonOBoms		= new _Controller_BonOBom(this->_Sounds_, this->m_Scores, this->m_SpawnPoints, this->_Draw_, this->_Sprites_);
		this->m_FireWorks		= new _Controller_FireworkRocket(this->_Draw_, this->_Sprites_, this->_Sounds_, this->m_Scores);
		this->m_BubbleGums		= new _Controller_BubbleGum();
		this->m_PoppingCandies	= new _Controller_PoppingCandy(this->_Sounds_, this->m_Scores, this->_Draw_, this->_Sprites_);
	}
	inline void			Del_Board()
	{
		//	Deleting boards to create a new one.
		{
			//	Both Boards !
			{
				if (this->m_BoardLogic != nullptr)
				{
					for (int i = 0; i < this->m_BoardHeight; ++i)
					{
						for (int j = 0; j < this->m_BoardWidth; ++j)
						{
							delete this->m_BoardLogic[i][j];
						}

						delete[] this->m_BoardLogic[i];
					}
					delete[] this->m_BoardLogic;
				}
				if (this->m_BoardVisual != nullptr)
				{
					for (int i = 0; i < this->m_BoardHeight; ++i)
					{
						for (int j = 0; j < this->m_BoardWidth; ++j)
						{
							delete this->m_BoardVisual[i][j];
						}

						delete[] this->m_BoardVisual[i];
					}
					delete[] this->m_BoardVisual;
				}
			}

			//	_ATs_ColumnAndRow_
			{
				for (int i = 0; i < this->_ATs_Column_.size(); ++i)
				{
					this->_ATs_Column_[i].clear();
				}
				this->_ATs_Column_.clear();

				for (int i = 0; i < this->_ATs_Row_.size(); ++i)
				{
					this->_ATs_Row_[i].clear();
				}
				this->_ATs_Row_.clear();
			}
		}
	}
	inline void			Del_SpawnPoints()
	{
		while (!this->m_ToSpawn.empty())
		{
			delete this->m_ToSpawn[0];
			this->m_ToSpawn.erase(this->m_ToSpawn.begin() + 0);
		}
	}
	inline void			Del_Candies()
	{
		//	Candies !
		{
			while (!this->m_Candies.empty())
			{
				delete this->m_Candies[0];
				this->m_Candies.erase(this->m_Candies.begin() + 0);
			}
		}		

		//	_ATs_Row_ !
		{
			this->_ATs_Row_.clear();
			for (int i = 0; i < m_BoardWidth; ++i)
			{
				this->_ATs_Row_[i].clear();
			}
		}	

		//	_ATs_Column_ !
		{
			this->_ATs_Column_.clear();
			for (int i = 0; i < m_BoardHeight; ++i)
			{
				this->_ATs_Column_[i].clear();
			}
		}
	}
	inline void			Del_Controllers()
	{
		//	Candies !
		{
			if (this->m_CrushEffect != nullptr)
			{
				delete this->m_CrushEffect;
			}

			if (this->m_Prospform != nullptr)
			{
				delete this->m_Prospform;
			}

			tls::Delete(this->m_SpawnPoints);
		}

		//	Stripped !
		{
			if (this->m_Strippeds != nullptr)
			{
				delete this->m_Strippeds;
			}
		}

		//	Wrappeds !
		{
			if (this->m_Wrappeds != nullptr)
			{
				delete this->m_Wrappeds;
			}
		}

		//	Fishes !
		{
			if (this->m_Fishes != nullptr)
			{
				delete this->m_Fishes;
			}
		}

		//	Frozen Candies !
		{
			if (this->m_Frozens != nullptr)
			{
				delete this->m_Frozens;
			}
		}

		//	Bom-O-Boms !
		{
			tls::Delete(this->m_BonOBoms);
		}

		tls::Delete(this->m_FireWorks);
		tls::Delete(this->m_BubbleGums);
		tls::Delete(this->m_PoppingCandies);
		tls::Delete(this->m_SpecialMixes);
		tls::Delete(this->m_CntrlBoardVisual);
		tls::Delete(this->m_Coins);

		//	Score !
		{
			if (this->m_Scores != nullptr)
			{
				delete this->m_Scores;
			}
		}
	}
	inline void			Del_Switches()
	{
		//	Erasing Switch Controller...
		{
			if (this->m_SwitchController != nullptr)
			{
				delete this->m_SwitchController;
			}
		}
	}

//	-------------------------------------------
//			All about interactions.
//	-------------------------------------------
public:
	inline void			MouseStuff()
	{
		//	An useful tool :D
		if (0)
		{
			System::Console::SetCursorPosition(0, 0);

			std::cout << "xP Move: " << this->_Mouse_->g_Position_Camera(1, 1, this->_Camera_) << " | yP Move: " << this->_Mouse_->g_Position_Camera(1, 2, this->_Camera_) << "       \n";
			std::cout << "xP Pressed: " << this->_Mouse_->g_Position_Camera(2, 1, this->_Camera_) << " | yP Pressed: " << this->_Mouse_->g_Position_Camera(2, 2, this->_Camera_) << "       \n";
			std::cout << "xP Relased: " << this->_Mouse_->g_Position_Camera(3, 1, this->_Camera_) << " | yP Released: " << this->_Mouse_->g_Position_Camera(3, 2, this->_Camera_) << "       \n";

			std::cout << "Zoom: " << this->_Camera_->g_ZoomFactor();
		}

		//	Crusher drag.
		if (	(this->m_CrusherDrag) && (this->_Mouse_->g_Is(1))	)
		{
			this->_Size_Candies_ = this->m_Candies.size();



			for (	int i = 0;
					i < this->_Size_Candies_;
					++i	)
			{
				if (	tls::CollidesWith(	this->_Mouse_->g_Position(2, 1), this->_Mouse_->g_Position(2, 2), 1, 1,
											this->m_Candies[i]->g_PositionPrp(1), this->m_Candies[i]->g_PositionPrp(2),
											this->m_Candies[i]->g_MeasuresPrp(1), this->m_Candies[i]->g_MeasuresPrp(2)	)	)
				{
					this->m_Candies[i]->HitOne_HP();
					this->m_Candies[i]->s_Can(2, true);
					this->m_Scores->AddScore(	this->m_Candies[i]->g_PositionPrp(1)	, 
												this->m_Candies[i]->g_PositionPrp(2)	,
												ScoreSys::CustomScore, 10, false		,
												this->m_Candies[i]->g_KindID()			);
				}
			}

			return;
		}

		//	Magic clicks.
		if (	(this->m_MagicClick) && (this->_Mouse_->g_Is(1))	)
		{
			this->_Size_Candies_ = this->m_Candies.size();



			for (	int i = 0;
					i < this->_Size_Candies_;
					++i	)
			{
				if (	tls::CollidesWith(	this->_Mouse_->g_Position(2, 1), this->_Mouse_->g_Position(2, 2), 1, 1,
											this->m_Candies[i]->g_PositionPrp(1), this->m_Candies[i]->g_PositionPrp(2),
											this->m_Candies[i]->g_MeasuresPrp(1), this->m_Candies[i]->g_MeasuresPrp(2)	)	)
				{
					this->m_Candies[i]->s_ItemID(	this->m_SpecialCandy	);
				}
			}

			return;
		}

		//	Licorice Cage.
		if (	(this->m_LicoriceCage) && (this->_Mouse_->g_Is(1))	)
		{
			this->_Size_Candies_ = this->m_Candies.size();



			for (	int i = 0;
					i < this->_Size_Candies_;
					++i	)
			{
				if (	tls::CollidesWith(	this->_Mouse_->g_Position(2, 1), this->_Mouse_->g_Position(2, 2), 1, 1,
											this->m_Candies[i]->g_PositionPrp(1), this->m_Candies[i]->g_PositionPrp(2),
											this->m_Candies[i]->g_MeasuresPrp(1), this->m_Candies[i]->g_MeasuresPrp(2)	)	)
				{
					this->m_Candies[i]->s_Blocker(1);
				}
			}

			return;
		}

		//	Cupcake Baker.
		if (	(this->m_CupCakeBaker) && (this->_Mouse_->g_Is(1))	)
		{
			this->_Size_Candies_ = this->m_Candies.size();



			for (	int i = 0;
					i < this->_Size_Candies_;
					++i	)
			{
				if (	tls::CollidesWith(	this->_Mouse_->g_Position(2, 1), this->_Mouse_->g_Position(2, 2), 1, 1,
											this->m_Candies[i]->g_PositionPrp(1), this->m_Candies[i]->g_PositionPrp(2),
											this->m_Candies[i]->g_MeasuresPrp(1), this->m_Candies[i]->g_MeasuresPrp(2)	)	)
				{
					this->m_CupCakes->AddCupCake(	this->m_Candies[i], 5	);
				}
			}

			return;
		}


		//	Actual switchings and swappings.
		this->m_SwitchController->DoSwitching(	this->m_Candies, this->_Mouse_, this->_Camera_,
												tls::Vec4<double>(	this->xP, this->yP, this->m_BoardWidth, this->m_BoardHeight),
												this->m_SpecialMixes);

		//	Coins and surprises.
		this->m_Coins->MouseStuff();
	}
	inline void			KeyBoardStuff()
	{
		//	Management for FreezeBrain.
		{
			if (	this->_KeyBoard_->g_Key(kyb::Key::_Space_)->g_Is(3)	)
			{
				this->m_FreezeBrain		= !this->m_FreezeBrain;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::C)->g_Is(3)		)
			{	
				this->m_CrusherDrag		= !this->m_CrusherDrag;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::W)->g_Is(3)		)
			{
				this->m_MagicClick		= !this->m_MagicClick;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::F)->g_Is(3)		)
			{
				this->m_FreeSwitch		= !this->m_FreeSwitch;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::L)->g_Is(3)		)
			{
				this->m_LicoriceCage	= !this->m_LicoriceCage;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::K)->g_Is(3)		)
			{
				this->m_CupCakeBaker	= !this->m_CupCakeBaker;
			}

			if (	this->_KeyBoard_->g_Key(kyb::Key::P)->g_Is(3)		)
			{
				this->m_ShowPos			= !this->m_ShowPos;
			}
		}
	}

//	-------------------------------------------
//				Drawing part.
//	-------------------------------------------
public:
	//	Draw the candies.
	inline void			Draw(	int What	)
	{
		//	Candy.
		if (	enm_Draw::_Candy == What	)
		{
			this->_Container_Size_		= this->m_Candies.size();

			int								_Kind_					= 0;
			int								_SpriteID_Candy			= 0;

			float							_AlphaGlow_				= 0.0;
			double							_Shake_					= 0.0;		//	Variable just for shaking.
			double							_Iddling_				= 0.0;		//	When is waiting or something.
			double							_Expand_				= 0.0;		//	Extra value to add when scaling.
			float							_Starlight_Expand_		= 0.0f;

			int								_SpriteID_CandyGlow		= spr::enm_At::CandiesGlow;



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				_Kind_				= this->m_Candies[i]->g_KindID() - 1;
				_SpriteID_Candy		= this->m_Candies[i]->g_ItemID() + spr::enm_At::Candies - 1;


				_Shake_				=	(			(		this->m_Candies[i]->g_Is(11)		) ? 
											(tls::Oscilate((this->m_Candies[i]->g_InnerTime(1) / 1.5)) * this->m_Wrappeds->g_Data(6)) : 0.0);
				_Iddling_			=	(	(	this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::Waiting	) ? 
											(this->m_Candies[i]->g_InnerTime(2) * (0.3 * (0.5 / this->m_Wrappeds->g_Timing(1))) * std::cos(this->m_Candies[i]->g_InnerTime(2) / (2.5 * (this->m_Wrappeds->g_Timing(1) / 0.5)))	) : 0.0);
				_Iddling_			+=	(	(	this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::JellyFish	) ?
											(	this->m_Fishes->g_SpriteSpin() ) : 0.0			);
				_Iddling_			=	(	(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::BubbleGum) ? 0.0 : _Iddling_);
				_Expand_			=	(	(	this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::Waiting	) ?
											( (this->m_Wrappeds->g_Data(5) / (this->m_Wrappeds->g_Timing(1) * GAME_LOOP_VALUE)) * this->m_Candies[i]->g_InnerTime(2)) : 0.0);



				if (!this->m_Candies[i]->g_Is(10))		//	Is hidden?
				{
					//	Starlight drawings.
					{
						if (	this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::Starlight	)
						{
							_Starlight_Expand_		= tls::Oscilate(this->m_Candies[i]->g_InnerTime(1) / (GAME_LOOP_VALUE * 0.4), 20) - 0.75;



							//	Set position to the sprite.
							_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0)	+ _Shake_	,
																														this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_ + _Starlight_Expand_	,
																														this->m_Candies[i]->g_VisualPrp(2) + _Expand_	+ _Starlight_Expand_	);
								
							//	Spining.
							_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_		);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)),
																														tls::FixPos_Y(	_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



							this->_Draw_->Draw(_Sprites_->g_Sprite(spr::enm_At::StL_Contents)->g_Sprites()->at(_Kind_));
						}
					}

					//	Just the glow of a candy.
					{
						if (	(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::StrippedH)		||
								(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::StrippedV)		||
								(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)	||
								(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::Starlight)	)
						{
							//	About candy glow.
							{
								_AlphaGlow_		= tls::Oscilate(this->m_Candies[i]->g_InnerTime(1) / (GAME_LOOP_VALUE * 0.5), 3.0) * 255.0;

								if (this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)
								{
									_AlphaGlow_		= 190.0f;
								}
							}



							//	Set position to the sprite.
							_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0)	+ _Shake_	,
																												this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

							//	Applying color properties.
							_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->setColor(		sf::Color(	this->m_Candies[i]->g_ColorPrp(1)	,
																															this->m_Candies[i]->g_ColorPrp(2)	,
																															this->m_Candies[i]->g_ColorPrp(3)	,
																															_AlphaGlow_						)	);
							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_		,
																												this->m_Candies[i]->g_VisualPrp(2) + _Expand_		);

							//	Spining.
							_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_		);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)),
																												tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



							if (	this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::Starlight	)
							{
								this->_Draw_->DrawBlend(	_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)	);
							}
							else
							{
								this->_Draw_->Draw(			_Sprites_->g_Sprite(_SpriteID_CandyGlow)->g_Sprites()->at(_Kind_)	);
							}
						}
					}

					//	Actual candies.
					{
						switch (	this->m_Candies[i]->g_ItemID()	)
						{
						case STA_::enm_ItemID::CommonCandy:	case STA_::enm_ItemID::StrippedH:		case STA_::enm_ItemID::StrippedV: 
						case STA_::enm_ItemID::WrappedCandy:	case STA_::enm_ItemID::WrappedFuse:	case STA_::enm_ItemID::JellyFish:
						case STA_::enm_ItemID::FrozenCandy:	case STA_::enm_ItemID::Starlight:		case STA_::enm_ItemID::FireWorkRocket:
						case STA_::enm_ItemID::BubbleGum:		case STA_::enm_ItemID::PoppingCandy:
							{
								//	Set position to the sprite.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0) + _Shake_	,
																												this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1)	,
																												this->m_Candies[i]->g_VisualPrp(2)	);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_	,
																												this->m_Candies[i]->g_VisualPrp(2) + _Expand_	);

								//	Spining.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_);

								//	Fix position to properly render on screen.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)),
																												tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



								if (	(this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::BubbleGum)			&&
										(this->m_Candies[i]->g_JustTrigger(2) == def::enm_Triggers::Waiting)	)
								{
									this->_Shader_->s_Uniform_RadialZoom(	this->m_Candies[i]->g_InnerTime(2), tls::Vec4<float>(		_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getTextureRect().left	,
																																	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getTextureRect().top	,
																																	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getTextureRect().width	,
																																	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getTextureRect().height	)	);



									this->_Draw_->DrawShader(_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_), this->_Shader_->g_Shader(shd::MyShaders::RadialZoom));
								}
								else
								{
									this->_Draw_->Draw(_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_));
								}
							}

							break;

						case STA_::enm_ItemID::BomOBom:
							{
								//	_Kind_ changes depending on the phase of the iddling.
								//	0 for normal, and 1 and 2 for animation.
								_Kind_ = 0;
								


								//	Set position to the sprite.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0) + _Shake_	,
																												this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1)	,
																												this->m_Candies[i]->g_VisualPrp(2)	);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_	,
																												this->m_Candies[i]->g_VisualPrp(2) + _Expand_	);

								//	Spining.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_);

								//	Fix position to properly render on screen.
								_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)),
																												tls::FixPos_Y(	_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



								this->_Draw_->Draw(		_Sprites_->g_Sprite(_SpriteID_Candy)->g_Sprites()->at(_Kind_)	);
							}

							break;

						case STA_::enm_ItemID::CupCake_1:
						case STA_::enm_ItemID::CupCake_2:
						case STA_::enm_ItemID::CupCake_3:
						case STA_::enm_ItemID::CupCake_4:
						case STA_::enm_ItemID::CupCake_5:
							{
								this->_What_Sprite_		= spr::enm_At::CupCakes;
								this->_What_Kind_		= this->m_Candies[i]->g_ItemID() - STA_::enm_ItemID::CupCake_1;



								//	Set position to the sprite.
								_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0) + _Shake_	,
																																this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1)	,
																															this->m_Candies[i]->g_VisualPrp(2)	);

								//	Then goes the shrinking model.
								_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_	,
																															this->m_Candies[i]->g_VisualPrp(2) + _Expand_	);

								//	Spining.
								_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_);

								//	Fix position to properly render on screen.
								_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1)),
																																tls::FixPos_Y(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



								this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)	);
							}
						}
					} 

					//	Glow of the Frozen Candies.
					{
						if (	this->m_Candies[i]->g_ItemID() == STA_::enm_ItemID::FrozenCandy		)
						{
							//	About candy glow.
							if (	this->m_Candies[i]->g_Fc_Is(1)	)
							{
								_AlphaGlow_		= tls::Oscilate(this->m_Candies[i]->g_InnerTime(1) / (GAME_LOOP_VALUE * 0.15), 2.0) * 255.0;
							}
							else
							{
								_AlphaGlow_		= tls::Oscilate(this->m_Candies[i]->g_InnerTime(1) / (GAME_LOOP_VALUE * 0.35), 4.0) * 255.0;
							}



							//	Set position to the sprite.
							_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0)	+ _Shake_	,
																																				this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)				);

							//	Applying color properties.
							_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->setColor(		sf::Color(	this->m_Candies[i]->g_ColorPrp(1)	,
																																						this->m_Candies[i]->g_ColorPrp(2)	,
																																						this->m_Candies[i]->g_ColorPrp(3)	,
																																						_AlphaGlow_						)	);
							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_		,
																																			this->m_Candies[i]->g_VisualPrp(2) + _Expand_		);

							//	Spining.
							_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->setRotation(		this->m_Candies[i]->g_RotationPrp(1) + _Iddling_		);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																																				tls::FixPos_Y(	_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



						
							this->_Draw_->DrawBlend(	_Sprites_->g_Sprite(spr::enm_At::GlowParticles)->g_Sprites()->at(GlowID::FrozenCandyBackGlow)	);
						}
					}	

					//	Blockers.
					{
						if (	this->m_Candies[i]->g_HasBlocker(1)		)
						{
							//	Set position to the sprite.
							_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)->setPosition(		this->m_Candies[i]->g_PositionPrp(1) + (this->m_Candies[i]->g_MeasuresPrp(1) / 2.0)	,
																												this->m_Candies[i]->g_PositionPrp(2) - (this->m_Candies[i]->g_MeasuresPrp(2) / 2.0)	);

							//	Then goes the shrinking model.
							_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)->setScale(		this->m_Candies[i]->g_VisualPrp(1) + _Expand_		,
																											this->m_Candies[i]->g_VisualPrp(2) + _Expand_		);

							//	Fix position to properly render on screen.
							_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)->setPosition(		tls::FixPos_X(	_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);



						
							this->_Draw_->Draw(	_Sprites_->g_Sprite(spr::enm_At::Blockers)->g_Sprites()->at(0)	);
						}
					}
				}
				if (this->m_ShowPos)
				{
					this->_Text_->g_Text(fnt::enm_At::Mojangles)->setString(tls::IntToStr(i));
					this->_Text_->g_Text(fnt::enm_At::Mojangles)->setCharacterSize(25);
					this->_Text_->g_Text(fnt::enm_At::Mojangles)->setOutlineThickness(3);
					this->_Text_->g_Text(fnt::enm_At::Mojangles)->setPosition(	tls::FixPos_X(this->m_Candies[i]->g_PositionPrp(1), this->_Draw_->g_WorldBounds(1)	)	,
																				tls::FixPos_Y(this->m_Candies[i]->g_PositionPrp(2), this->_Draw_->g_WorldBounds(2)	)	);
					this->_Draw_->DrawText(this->_Text_->g_Text(fnt::enm_At::Mojangles));
				}
			}
		}
	}

	//	Draw everything (candies, effects, board, ...)
	inline void			DrawAll()
	{
		this->m_Scores->Draw(				_Controller_Score::enm_Draw::_ScoreLayout					);
		this->m_CntrlBoardVisual->Draw(		_Controller_BoardVisual::enm_Draw::_Board					);
		this->m_CrushEffect->Draw(			_Controller_CrushEffect::enm_Draw::_SquareGlow				);
		this->Draw(							Board::enm_Draw::_Candy										);
		this->m_Frozens->Draw(				_Controller_FrozenCandy::enm_Draw::_Splash					);
		this->m_Fishes->Draw(				_Controller_Fish::enm_Draw::_FishTarget						);
		this->m_SwitchController->Draw(		Switcher::enm_Draw::_SelectionFrame							);
		this->m_Prospform->Draw(			_Controller_SpecialForm::enm_Draw::_Prospform				);
		this->m_CrushEffect->Draw(			_Controller_CrushEffect::enm_Draw::_CrushEffect				);
		this->m_CrushEffect->Draw(			_Controller_CrushEffect::enm_Draw::_Glow					);
		this->m_Coins->Draw(				_Controller_Coin::enm_Draw::_Coin							);
		this->m_Wrappeds->Draw(				_Controller_Wrappeds::enm_Draw::_Stars						);
		this->m_Strippeds->Draw(			_Controller_Stripped::enm_Draw::_Remember					);
		this->m_Strippeds->Draw(			_Controller_Stripped::enm_Draw::_Sparkle					);
		this->m_Strippeds->Draw(			_Controller_Stripped::enm_Draw::_Lightning					);
		this->m_Strippeds->Draw(			_Controller_Stripped::enm_Draw::_Mixes						);
		this->m_PoppingCandies->Draw(		_Controller_PoppingCandy::enm_Draw::_PoppingCracker			);
		this->m_PoppingCandies->Draw(		_Controller_PoppingCandy::enm_Draw::_Spark					);
		this->m_FireWorks->Draw(			_Controller_FireworkRocket::enm_Draw::_FireWorkRocket		);
		this->m_FireWorks->Draw(			_Controller_FireworkRocket::enm_Draw::_BigGlow				);
		this->m_FireWorks->Draw(			_Controller_FireworkRocket::enm_Draw::_FireWorkEmber		);
		this->m_BonOBoms->Draw(				_Controller_BonOBom::enm_Draw::_LightBon					);
		this->m_Fishes->Draw(				_Controller_Fish::enm_Draw::_Sparkmoke						);
		this->m_Fishes->Draw(				_Controller_Fish::enm_Draw::_Bubbles						);
		this->m_Fishes->Draw(				_Controller_Fish::enm_Draw::_JellyFish						);
		this->m_Frozens->Draw(				_Controller_FrozenCandy::enm_Draw::_Sparkmoke				);
		this->m_Frozens->Draw(				_Controller_FrozenCandy::enm_Draw::_Sparkle					);
		this->m_Frozens->Draw(				_Controller_FrozenCandy::enm_Draw::_Frojectile				);
		this->m_Scores->Draw(				_Controller_Score::enm_Draw::_Scores						);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline VisualGrid*			g_BoardVisual(int _i, int _j)
	{
		return this->m_BoardVisual[_i][_j];
	}
	inline int					g_BoardMeasure(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return		this->m_BoardWidth;

		case 2:
			return		this->m_BoardHeight;
		}
	}
	inline double				g_BoardBounds(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return		this->m_GridBound;

		case 2:
			return		this->m_GridBound;
		}
	}

	inline std::vector<TheCandy*>&		g_Candies()
	{
		//	I know that this is kinda unsafe, but if a just pass a copy
		//	of the whole vector it will be laggy. However, I'm aware of
		//	this little problem.

		return this->m_Candies;
	}
	inline _Controller_CrushEffect*		g_Cntrl_Crush()
	{
		return this->m_CrushEffect;
	}
	inline _Controller_SpecialForm*		g_Cntrl_Prosform()
	{
		return this->m_Prospform;
	}
	inline _Controller_Score*			g_Cntrl_Score()
	{
		return this->m_Scores;
	}
	inline _Controller_Stripped*		g_Cntrl_Stripped()
	{
		return this->m_Strippeds;
	}
	inline _Controller_Wrappeds*		g_Cntrl_Wrappeds()
	{
		return this->m_Wrappeds;
	}
	inline _Controller_Fish*			g_Cntrl_Fishes()
	{
		return this->m_Fishes;
	}
	inline _Controller_FrozenCandy*		g_Cntrl_Frozens()
	{
		return		this->m_Frozens;
	}
	inline _Controller_BonOBom*			g_Cntrl_BonOBom()
	{
		return			this->m_BonOBoms;
	}
	inline _Controller_FireworkRocket*	g_Cntrl_Fireworks()
	{
		return		this->m_FireWorks;
	}
	inline _Controller_PoppingCandy*	g_Cntrl_PoppingCandies()
	{
		return		this->m_PoppingCandies;
	}

	inline Switcher*			g_SwitchController()
	{
		return this->m_SwitchController;
	}



	inline bool					g_FreezeBrain()
	{
		return this->m_FreezeBrain;
	}
};
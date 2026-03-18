#pragma once

#include		<iostream>
#include		<array>

#include		<SFML/Audio.hpp>
#include		<SFML/Window.hpp>

#include		"_MyIncludes_.h"
#include		"LogicalController.h"



namespace snd
{
	enum SndSys
	{
		MatchSound = 0		,
		GoSwitch			,
		Stripped			,
		Wrapped				,
		FishySound			,
		FrozenC				,
		BomOBom				,
		StarLight			,
		FireWorkRocket		,
		BubbleGum			,
		PoppingCandy		,
		Coin				,
		Surprise			,
		CupCake				,
		DelightfulVoices	,
	};
	
	enum MyPlayList
	{
		MainMenu	= 1,
		InGame		= 2,
	
		ItsComplicated				= 10,
		Unwind						= 11,
		AfterLife					= 12,
		TakerOverMedley				= 13,
		DonnieSoft					= 14,
		ItsComplicatedSayorMix		= 15,

		MaryOnACross		= 20,
		AfterDark			= 21,
		HymnForTheWeekend	= 22,
		BlitzMode			= 23,
		PandaEyesColorblind	= 24,
	};
}


class	SoundFactory
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const int			$_Arr_Size_		= _Mx_Int7 - 1;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	std::array<sf::Sound*, (_Mx_Int7 - 1)>*				m_SoundPlayer;
	std::vector<sf::SoundBuffer>						m_MySounds;

	sf::Music											m_MyMusic;

	double				m_PitchSound	= 0.85;
	double				m_PitchMusic	= 0.85;

	int					m_WhatMusic		= def::enm_Defines::_NOT_INITIALIZED;

//	-------------------------------------------
//				Auxiliars and counters
//	-------------------------------------------
private:
	sf::Sound*			_Which_ = nullptr;

	int					Cnt_PlayDelay	= 0, Trg_PlayDelay = 0;
	bool				Ini_PlayDelay	= false;

//	-------------------------------------------
//				External and Linkers
//	-------------------------------------------
private:
	_Controller_Logic*		_Logic_ = nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	SoundFactory(	_Controller_Logic* _Logic_Ptr	)
	{
		this->_Logic_	= _Logic_Ptr;



		//	Initializing Arr_SoundPlayer.
		{
			this->m_SoundPlayer = new std::array<sf::Sound*, (_Mx_Int7 - 1)>;



			for (	int i = 0; 
					i < this->$_Arr_Size_;
					++i	)
			{
				this->m_SoundPlayer->at(i) = new sf::Sound();
			}
		}
	}

	~SoundFactory()
	{
		//	Erasing Arr_SoundPlayer.
		{
			for (	int i = 0;
					i < this->$_Arr_Size_;
					++i	)
			{
				delete this->m_SoundPlayer->at(i);
			}



			delete this->m_SoundPlayer;
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Ld_Sounds(std::array<sf::SoundBuffer, Arr_SA_SB_Size> _Sounds)
	{
		//	Pushing all the match sequence sounds !
		{
			for (	int i = 0;
					i < 11;
					++i	)
			{
				m_MySounds.push_back(_Sounds[i]);
			}		
		}

		//	Let's do the switching sounds :D !
		{
			m_MySounds.push_back(_Sounds[12]);
			m_MySounds.push_back(_Sounds[11]);
		}

		//	Then go with stripped candies.
		{
			m_MySounds.push_back(_Sounds[18]);
			m_MySounds.push_back(_Sounds[19]);
		}

		//	Get those wrapped sounds.
		{
			m_MySounds.push_back(_Sounds[20]);
			m_MySounds.push_back(_Sounds[21]);
			m_MySounds.push_back(_Sounds[22]);
			m_MySounds.push_back(_Sounds[23]);
		}

		//	Sounds for the jelly fish.
		{
			m_MySounds.push_back(_Sounds[32]);
			m_MySounds.push_back(_Sounds[33]);
		}

		//	My favorite, frozen candies.
		{
			m_MySounds.push_back(_Sounds[28]);
			m_MySounds.push_back(_Sounds[29]);
			m_MySounds.push_back(_Sounds[30]);
			m_MySounds.push_back(_Sounds[31]);
		}

		//	Delicious Bom-O-Bom.
		{
			m_MySounds.push_back(_Sounds[24]);
			m_MySounds.push_back(_Sounds[27]);
			m_MySounds.push_back(_Sounds[26]);
			m_MySounds.push_back(_Sounds[25]);
		}

		//	Explosive ahead: Firework Rockets.
		{
			m_MySounds.push_back(_Sounds[20]);
			m_MySounds.push_back(_Sounds[34]);
			m_MySounds.push_back(_Sounds[36]);
		}

		//	BubbleGum. Yum!
		{
			m_MySounds.push_back(_Sounds[20]);
			m_MySounds.push_back(_Sounds[34]);
			m_MySounds.push_back(_Sounds[36]);
		}

		//	Popping Candy!
		{
			m_MySounds.push_back(_Sounds[20]);
			m_MySounds.push_back(_Sounds[34]);
			m_MySounds.push_back(_Sounds[36]);
		}

		//	Coin.
		{
			m_MySounds.push_back(_Sounds[37]);
			m_MySounds.push_back(_Sounds[38]);
		}

		//	Surprise.
		{
			m_MySounds.push_back(_Sounds[39]);
			m_MySounds.push_back(_Sounds[34]);
		}

		//	CupCake.
		{
			m_MySounds.push_back(_Sounds[41]);
		}

		//	Delightful voices.
		{
			m_MySounds.push_back(_Sounds[14]);
			m_MySounds.push_back(_Sounds[15]);
			m_MySounds.push_back(_Sounds[16]);
			m_MySounds.push_back(_Sounds[17]);
		}
	}

	inline int			Play(int _What, int _OffSet)
	{
		int			_Number_ = def::enm_Defines::_NOT_FOUND;



		//	Searching the available player.
		{
			_Which_ = nullptr;



			for (	int i = 0; 
					i < this->$_Arr_Size_; 
					i++	)
			{
				if (	this->m_SoundPlayer->at(i)->getStatus() != sf::SoundSource::Playing	)
				{
					_Which_		= this->m_SoundPlayer->at(i);
					_Number_	= i;

					break;
				}
			}
		}

		//	Not found exception.
		{
			if (_Which_ == nullptr)
			{
				return _Number_;
			}
		}

		//	Selecting sound buffer part and play.
		{
			switch (_What)
			{
			case snd::SndSys::MatchSound:
				_Which_->setBuffer(this->m_MySounds[	((_OffSet < 10) ? _OffSet : 10)	]	);
				break;

			case snd::SndSys::GoSwitch:
				//	_OffSet value:
				//		1:	Normal Switch.
				//		2:	Negative Switch.
				_Which_->setBuffer(this->m_MySounds[	11 + _OffSet - 1	]	);
				break;

			case snd::SndSys::Stripped:
				//	_OffSet value:
				//		1:	Stripped created.
				//		2:	Stripped pop.
				_Which_->setBuffer(this->m_MySounds[	13 + _OffSet - 1	]	);
				break;

			case snd::SndSys::Wrapped:
				//	_OffSet value:
				//		1:	Wrapped created.
				//		2:	Wrapped charging.
				//		3:	Wrapped explode.
				//		4:	Wrapped fuse.
				_Which_->setBuffer(this->m_MySounds[	15 + _OffSet - 1	]	);
				break;

			case snd::SndSys::FishySound:
				//	_OffSet value:
				//		1:	Fish created.
				//		2:	Fish swim.
				_Which_->setBuffer(this->m_MySounds[	19 + _OffSet - 1	]	);
				break;

			case snd::SndSys::FrozenC:
				//	_OffSet value:
				//		1:	Frozen created.
				//		2:	Frozen burst.
				//		3:	Frozen hit.
				//		4:	Frozen crush.
				_Which_->setBuffer(this->m_MySounds[21 + _OffSet - 1]);
				break;

			case snd::SndSys::BomOBom:
				//	_OffSet value:
				//		1:	BomOBom created.
				//		2:	BomOBom fuses.
				//		3:	BomOBom hit.
				//		4:	BomOBom crush.
				_Which_->setBuffer(this->m_MySounds[25 + _OffSet - 1]);
				break;

			case snd::SndSys::FireWorkRocket:
				//	_OffSet value:
				//		1:	Firework created.
				//		2:	Firework launch.
				//		3:	Firework explosion simple.
				_Which_->setBuffer(this->m_MySounds[29 + _OffSet - 1]);
				break;

			case snd::SndSys::BubbleGum:
				//	_OffSet value:
				//		1:	BubbleGum created.
				//		2:	BubbleGum growing.
				//		3:	BubbleGum explosion.
				_Which_->setBuffer(this->m_MySounds[32 + _OffSet - 1]);
				break;

			case snd::SndSys::PoppingCandy:
				//	_OffSet value:
				//		1:	PoppingCandy created.
				//		2:	PoppingCandy popping.
				//		3:	PoppingCandy dies.
				_Which_->setBuffer(this->m_MySounds[35 + _OffSet - 1]);
				break;

			case snd::SndSys::Coin:
				//	_OffSet value:
				//		1:	Coin spawns.
				//		2:	Coin picking.
				_Which_->setBuffer(this->m_MySounds[38 + _OffSet - 1]);
				break;

			case snd::SndSys::Surprise:
				//	_OffSet value:
				//		1:	Surprise spawns.
				//		2:	Surprise picking.
				_Which_->setBuffer(this->m_MySounds[40 + _OffSet - 1]);
				break;

			case snd::SndSys::CupCake:
				//	_OffSet value:
				//		1:	Cupcake Eaten.
				_Which_->setBuffer(this->m_MySounds[42 + _OffSet - 1]);
				break;

			case snd::SndSys::DelightfulVoices:
				//	_OffSet value:
				//		1:	Sweet.
				//		2:	Tasty.
				//		3:	Delicious.
				//		4:	Divine.
				_Which_->setBuffer(this->m_MySounds[43 + _OffSet - 1]);
				break;

			default:
				throw	std::runtime_error("Sound couldn't be found! Returning...");
				break;
			}
			


			_Which_->play();
		}

		return	_Number_;
	}
	inline void			SetMusic(int _What, double _Time_In_Seconds)
	{
		if (_What < 0)
		{
			this->m_WhatMusic		= def::enm_Defines::_NOT_INITIALIZED;
		}
		else
		{
			this->m_WhatMusic		= _What;
		}

		this->Trg_PlayDelay		= _Time_In_Seconds * (GAME_LOOP_VALUE);
		this->Ini_PlayDelay		= true;
	}
	inline void			AtPlayer_Stop(int _Where)
	{
		if ((0 > _Where) || ($_Arr_Size_ < _Where))
		{
			return;
		}

		this->m_SoundPlayer->at(_Where)->stop();
	}
	inline void			TrackPace()
	{
		//	Updating all sound pitch values.
		{
			if (	this->_Logic_->GameLoopIsChanging()		)
			{
				//	this->m_PitchSound		= ((_Controller_Logic::_ogLpV_ / _Controller_Logic::_gLpVal_) * 0.7) + 0.3;
				this->m_PitchSound		= _Controller_Logic::_ogLpV_ / _Controller_Logic::_gLpVal_;



				for (	int i = 0;
						i < this->$_Arr_Size_;
						i++	)
				{
					this->m_SoundPlayer->at(i)->setPitch(this->m_PitchSound);
				}
			}
		}

		//	Now for the music.
		{
			if (	this->_Logic_->GameLoopIsChanging()		)
			{
				this->m_PitchSound		= ((_Controller_Logic::_ogLpV_ / _Controller_Logic::_gLpVal_) * 0.3) + 0.7;
				//	this->m_PitchSound		= ((_Controller_Logic::_ogLpV_ / _Controller_Logic::_gLpVal_) * 0.35) + 0.65;



				this->m_MyMusic.setPitch(this->m_PitchSound);
			}
		}
	}
	inline void			LogicDis()
	{
		this->TrackPace();
	}

	inline void			IniCnt_PlayMusic()
	{
		if (this->Ini_PlayDelay)
		{
			if (this->Cnt_PlayDelay < this->Trg_PlayDelay)
			{
				++this->Cnt_PlayDelay;
			}
			else
			{
				this->Cnt_PlayDelay = this->Trg_PlayDelay = 0;
				this->Ini_PlayDelay = false;



				//	Before selecting the music.
				{
					this->m_MyMusic.stop();
				}

				//	Selecting sound buffer part and play.
				{
					switch (this->m_WhatMusic)
					{
					case snd::MyPlayList::MainMenu:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Game Songs\\CCFS - Menu Music.ogg");
						break;

					case snd::MyPlayList::InGame:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Game Songs\\inGameMusic.ogg");
						break;



					case snd::MyPlayList::ItsComplicated:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\Its Complicated.ogg");
						break;

					case snd::MyPlayList::Unwind:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\Unwind.ogg");
						break;

					case snd::MyPlayList::AfterLife:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\TheresThreeOfThemNow Afterlife - AjTheFunky.ogg");
						break;

					case snd::MyPlayList::TakerOverMedley:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\Doki Doki Takeover Plus - Takeover Medley.ogg");
						break;

					case snd::MyPlayList::DonnieSoft:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\Donnie Soft.ogg");
						break;

					case snd::MyPlayList::ItsComplicatedSayorMix:
						this->m_MyMusic.openFromFile("_Resources_\\FridayNightFunking\\Music\\Its Complicated - Sayori Mix.ogg");
						break;



					case snd::MyPlayList::MaryOnACross:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Various Songs\\MaryOnACross.ogg");
						break;

					case snd::MyPlayList::AfterDark:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Various Songs\\Mr. - Kitty - After - Dark.ogg");
						break;

					case snd::MyPlayList::HymnForTheWeekend:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Various Songs\\Hymn for the Weekend - Coldplay.ogg");
						break;

					case snd::MyPlayList::BlitzMode:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Various Songs\\Blitz Mode.ogg");
						break;

					case snd::MyPlayList::PandaEyesColorblind:
						this->m_MyMusic.openFromFile("_Resources_\\SoundAndMusic\\Songs\\Various Songs\\Panda Eyes - Colorblind.ogg");
						break;
					}
				}

				//	Finally, add some touches.
				{
					if (	0 <= m_WhatMusic	)
					{
						this->m_MyMusic.setLoop(true);
						this->m_MyMusic.setPitch(this->m_PitchMusic);

						this->m_MyMusic.play();
					}
				}
			}
		}
	}
};
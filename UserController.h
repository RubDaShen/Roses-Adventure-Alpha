#pragma once


#include		<string>
#include		<thread>

#include		"thyObject.h"
#include		"Tools_.h"
#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"SQLStuff.h"
#include		"LiviconHUD.h"



class		UserIcon : public thyObject
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
	UserIcon(	double _xP, double _yP	) : thyObject(	_xP, _yP, def::enm_ObjectType::Generic	)
	{

	}

	~UserIcon()
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
	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
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

class		UserProperties
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	tls::String*		m_Username					= nullptr;
	std::string			m_Buffer_Username;
	bool				m_FetchingUsername			= true;
	int					m_UsernameReadyCounter		= 0;

	int					m_UsernameSpecialColor		= 0;

//	-------------------------------------------
//				Other Variables
//	-------------------------------------------
private:
	double		yPosGap				= 5.0;

	int			_Container_Size		= 0;

//	-------------------------------------------
//					Functions
//	-------------------------------------------
private:
	inline void			fn_PaintCharacter(int Where, int R, int G, int B)
	{
		this->m_Username->at(Where)->s_ColorPrp(1, R);
		this->m_Username->at(Where)->s_ColorPrp(2, G);
		this->m_Username->at(Where)->s_ColorPrp(3, B);
	}





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	UserProperties()
	{
		this->LoadAll();
	}

	~UserProperties()
	{
		this->DeleteAll();
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			LoadAll()
	{
		this->m_Username	= new tls::String();
		this->m_Username->SetLetterSpacing(5);
	}
	inline void			DeleteAll()
	{
		tls::Delete(this->m_Username);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			ColorUsername()
	{
		int		First		= 0;
		int		Second		= 0;
		int		Third		= 0;



		switch (	this->m_UsernameSpecialColor	)
		{
		case	20:
			this->_Container_Size		= this->m_Username->size();

			//	If the name is too short (1)
			//	then do this exception.
			if (	this->_Container_Size < 2	)
			{
				this->fn_PaintCharacter(0, 255, 255, 255);
			}
			//	Else, apply a for loop 
			//	and a algorithm.
			else
			{
				First	= (_Container_Size + 1) / 3;
				//	Second.
				{
					if (	((_Container_Size) % 2) == 0	)
					{
						Second		= ((_Container_Size / 2) + 1) / 3;
					}
					else
					{
						Second		= ((_Container_Size / 6) * 2) + 1;
					}
				}
				Third	= (_Container_Size + 1) / 3;



				for (	int i = 0; i < First; ++i	)
				{
					this->fn_PaintCharacter(i, 0, 170, 170);
				}

				for (	int i = 0; i < Second; ++i	)
				{
					this->fn_PaintCharacter(i + First, 0, 255, 255);
				}

				for (	int i = 0; i < Third; ++i	)
				{
					this->fn_PaintCharacter(i + First + Second, 255, 255, 255);
				}
			}

			break;
		}
	}
	
	inline void			LogicDis()
	{
		//	Username color.
		if (	this->m_UsernameReadyCounter == 2	)
		{
			this->ColorUsername();
			this->AddUsernameCounter();
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline tls::String*		GetUsername()
	{
		return		this->m_Username;
	}
	inline std::string*		GetBuffer()
	{
		return		&this->m_Buffer_Username;
	}

	inline void			UseBuffer(	UserIcon* IconPtr	)
	{
		//	Write.
		this->m_Username->Write(	this->m_Buffer_Username, 5.0, false, true, fnt::enm_FontType::CommonFont		);

		//	Position.
		{
			//	m_Username->x
			double IconWidth		= IconPtr->g_SpriteMeasures(1);
			double TextWidth		= this->m_Username->GetStringMeasure(1);
			double WidthDifference	= (IconWidth - TextWidth) / 2.0;
			double xFinalPos		= IconPtr->g_PositionPrp(1) + WidthDifference;
			this->m_Username->s_PositionPrp(1, xFinalPos);

			//	Life_Text->y
			double yInitialPos		= IconPtr->g_PositionPrp(2);
			double TextHeight		= this->m_Username->GetStringMeasure(2);
			double yFinalPos		= IconPtr->g_PositionPrp(2) + TextHeight + this->yPosGap;
			this->m_Username->s_PositionPrp(2, yFinalPos);
		}

		//	Repos.
		this->m_Username->RePos();
	}
	inline void			AddUsernameCounter()
	{
		++this->m_UsernameReadyCounter;
	}
	inline void			SetUsernamePosition(double _xP, double _yP)
	{
		this->m_Username->s_PositionPrp(1, _xP);
		this->m_Username->s_PositionPrp(2, _yP);

		this->m_Username->RePos();
	}

	inline void			SetUsernameFlag(	int What, bool Value	)
	{
		switch (	What	)
		{
		case	1:
			this->m_FetchingUsername	= Value;
		}
	}
	inline bool			GetUsernameFlag(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		this->m_FetchingUsername;
		}
	}


	inline int*			GetRef_UserSpecialColor()
	{
		return		&this->m_UsernameSpecialColor;
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
class		_Controller_User
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
		_Icon			= 0,
		_Username		= 1,
		_LiviconHUD		= 2,
	};

	enum	enm_QueryCall
	{
		_UserName			= 0,
		_UserLifes			= 1,
		_UserSpecialColor	= 2,
		_UserCoins			= 3,
	};

	enum	enm_Logic
	{
		_Queries			= 0,
		_Livicon			= 1,
		_UserProperties		= 2,
	};




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const int		m_NumberQueries		= 4;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	UserIcon*			m_UserIcon			= nullptr;
	UserProperties*		m_UserProperties	= nullptr;

	_Controller_LiviconHUD*		m_LiviconHUD	= nullptr;

//	-------------------------------------------
//				Other Variables
//	-------------------------------------------
private:
	int				m_NameBelowIcon = 0;

	tls::String*	m_PointerToUsername	= nullptr;

//	-------------------------------------------
//			Threading and Concurrency
//	-------------------------------------------
private:
	std::array<int, 4>		m_QueryStatus{};

	int			m_ExecuteThread = 0;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	TextFactory*			_Text_		= nullptr;

	sql::SQLConnector*		_SQL_		= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;

//	-------------------------------------------
//				Private	Functions
//	-------------------------------------------
public:
	inline void			inThread_LaunchQuery(	const std::string& QueryString		,
												int WhatQuery						)
	{
		this->m_QueryStatus[WhatQuery]		= this->_SQL_->ExecuteQuery(QueryString, WhatQuery);
	}
	

	inline void			inThread_SetUserName(			int WhatQuery		)
	{
		this->m_UserProperties->SetUsernameFlag(1, true);
		//	-_-_-_-_-_-_-_-_-_-_-_-
		this->m_UserProperties->GetBuffer()->clear();
		this->m_QueryStatus[WhatQuery]		= this->_SQL_->GetString(	1, *this->m_UserProperties->GetBuffer(), WhatQuery);
		this->m_UserProperties->UseBuffer(this->m_UserIcon);
		this->m_UserProperties->AddUsernameCounter();
		++this->m_ExecuteThread;
		//	-_-_-_-_-_-_-_-_-_-_-_-
		this->m_UserProperties->SetUsernameFlag(1, false);
	}
	inline void			inThread_SetUserLifes(			int WhatQuery		)
	{
		this->m_QueryStatus[WhatQuery]		= this->_SQL_->GetInteger(1, this->m_LiviconHUD->g_LifeIcon()->gRef_Life(), WhatQuery);
		++this->m_ExecuteThread;
	}
	inline void			inThread_SetUserSpecialColor(	int WhatQuery		)
	{
		this->m_QueryStatus[WhatQuery]		= this->_SQL_->GetInteger(1, this->m_UserProperties->GetRef_UserSpecialColor(), WhatQuery);
		this->m_UserProperties->AddUsernameCounter();
		++this->m_ExecuteThread;
	}
	inline void			inThread_SetUserCoins(			int WhatQuery		)
	{
		this->m_QueryStatus[WhatQuery]		= this->_SQL_->GetInteger(1, this->m_LiviconHUD->g_CoinIcon()->gRef_Coins(), WhatQuery);
		++this->m_ExecuteThread;
	}





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_User(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	,	
						TextFactory* _Text_Ptr, sql::SQLConnector* _SQL_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Text_		= _Text_Ptr;
		this->_SQL_			= _SQL_Ptr;



		this->LoadAll();
	}

	~_Controller_User()
	{
		tls::Delete(	this->m_UserIcon	);
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void		LoadAll()
	{
		this->CreateIcon();

		this->m_LiviconHUD		= new _Controller_LiviconHUD(this->_Draw_, this->_Sprites_);

		for (	int i = 0; 
				i < this->m_NumberQueries; 
				++i	)
		{
			this->m_QueryStatus[i]		= sql::enm_QueryStatus::NotRunnning;
		}

	}
	inline void		CreateIcon()
	{
		int		xOffSet		= 75;
		int		yOffSet		= 150;

		int		IconWidth		= this->_Sprites_->g_Sprite(spr::enm_At::UserUser)->g_Measures()->at(0).Third;
		int		IconHeight		= this->_Sprites_->g_Sprite(spr::enm_At::UserUser)->g_Measures()->at(0).Fourth;

		double		xP = this->_Draw_->GetCameraLimits(def::enm_CameraLimits::LeftBorder) + xOffSet;
		double		yP = this->_Draw_->GetCameraLimits(def::enm_CameraLimits::Floor) + IconHeight + yOffSet;



		this->m_UserIcon		= new UserIcon(xP, yP);
		this->m_UserIcon->s_SpriteMeasures(1, IconWidth);
		this->m_UserIcon->s_SpriteMeasures(2, IconHeight);

		this->m_NameBelowIcon	= (IconHeight * 0.5) + 50;



		this->m_UserProperties	= new UserProperties();
	}

//	-------------------------------------------
//				Query Functions
//	-------------------------------------------
public:
	inline void		CallQuery(	int What	)
	{
		//	Inside this class, we don't care if
		//	the connection to the database is successfully
		//	reached; query flag values will manage that.
		//	Just call the queries.
		std::thread		thr_WorkerThread;



		switch (	What	)
		{
		case	enm_QueryCall::_UserName:
			//	Query ready to be called and ask the user name.
			{
				//	1.	Thread initializing:
				//		The thread should request the query and therefore return if the
				//		the query was successfully executed.
				//		Using multiple threads for more efficient*.
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_LaunchQuery, this, "SELECT usr.NickName FROM Users as usr WHERE usr.UserID = 3", What);

				//	2.	Detach:
				//		Detach the thread so the flow of the programm
				//		keeps as normal.
				thr_WorkerThread.detach();

				//	3.	Flag:
				//		Set the flag to query executed but
				//		the successful query is not true yet.
				this->m_QueryStatus[What]	= sql::enm_QueryStatus::Asking;
			}
			break;

		case	enm_QueryCall::_UserLifes:
			//	Query ready to be called and ask the user name.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_LaunchQuery, this, "SELECT [MyFirstDataBase].[dbo].fn_GetLife(3)", What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]	= sql::enm_QueryStatus::Asking;
			}
			break;

		case	enm_QueryCall::_UserSpecialColor:
			//	Query ready to be called and ask the user name.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_LaunchQuery, this, "SELECT [MyFirstDataBase].[dbo].fn_GetUserSpecialColor(3)", What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]	= sql::enm_QueryStatus::Asking;
			}
			break;

		case	enm_QueryCall::_UserCoins:
			//	Query ready to be called and ask the user name.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_LaunchQuery, this, "SELECT [MyFirstDataBase].[dbo].fn_GetUserCoins(3)", What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]	= sql::enm_QueryStatus::Asking;
			}
			break;
		}
	}
	inline void		ObtainInfoFromQuery(	int What	)
	{
		//	The second part, once the query asked for information
		//	as planned, now it's time to get that info.
		//	This switch does that.
		std::thread		thr_WorkerThread;



		switch (	What	)
		{
		case	enm_QueryCall::_UserName:
			//	Query ready to get the information requested.
			{
				//	1.	Thread initializing:
				//		The thread should now get the information
				//		it effectively got from.
				thr_WorkerThread = std::thread(	&_Controller_User::inThread_SetUserName, this, What);

				//	2.	Detach:
				//		Detach the thread so the flow of the programm
				//		keeps as normal.
				thr_WorkerThread.detach();

				//	3.	Flag:
				//		Set the flag to query done.
				//		'Done' means the query's job is done.
				this->m_QueryStatus[What]		= sql::enm_QueryStatus::GettingInfo;
			}
			break;

		case	enm_QueryCall::_UserLifes:
			//	Query ready to get the information requested.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_SetUserLifes, this, What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]		= sql::enm_QueryStatus::GettingInfo;
			}
			break;

		case	enm_QueryCall::_UserSpecialColor:
			//	Query ready to get the information requested.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_SetUserSpecialColor, this, What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]		= sql::enm_QueryStatus::GettingInfo;
			}
			break;

		case	enm_QueryCall::_UserCoins:
			//	Query ready to get the information requested.
			{
				//	1.	Thread initializing:
				thr_WorkerThread	= std::thread(	&_Controller_User::inThread_SetUserCoins, this, What);

				//	2.	Detach:
				thr_WorkerThread.detach();

				//	3.	Flag:
				this->m_QueryStatus[What]		= sql::enm_QueryStatus::GettingInfo;
			}
			break;
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		LogicDis(	int What	)
	{
		//	Query part.
		if (		What == enm_Logic::_Queries		)
		{
			//	Everytime, if possible, execute 
			//	all queries to get the user information.
			//	Once query success, stop calling it.
			if (	this->m_ExecuteThread < this->m_NumberQueries	)
			{
				//	If not initialized, then launch query.
				if (	(this->m_QueryStatus[this->m_ExecuteThread] == sql::enm_QueryStatus::NotRunnning)		||
						(this->m_QueryStatus[this->m_ExecuteThread] == sql::enm_QueryStatus::ErrorWhenAsking)	)
				{
					this->CallQuery(this->m_ExecuteThread);
				}

				//	If query success, then get that delicious info.
				if (	this->m_QueryStatus[this->m_ExecuteThread] == sql::enm_QueryStatus::ReadyToPair		)
				{
					this->ObtainInfoFromQuery(this->m_ExecuteThread);
				}
			}
		}

		//	Livicon part.
		if (		What == enm_Logic::_Livicon		)
		{
			this->m_LiviconHUD->LogicDis();
		}

		//	User properties.
		if (	What == enm_Logic::_UserProperties	)
		{
			this->m_UserProperties->LogicDis();
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	User Icon.
		if (	enm_Draw::_Icon == What		)
		{
			this->_What_Sprite_			= spr::enm_At::UserUser;
			this->_What_Kind_			= 0;



			//	Set position to the sprite.
			_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	m_UserIcon->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																										tls::FixPos_Y(	m_UserIcon->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);



			this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));		
		}

		//	User Name.
		if (	enm_Draw::_Username == What		)
		{
			if (	!this->m_UserProperties->GetUsernameFlag(1)		)
			{
				this->_What_Sprite_			= spr::enm_At::CommonFont;
				this->m_PointerToUsername	= this->m_UserProperties->GetUsername();
				this->_Container_Size_		= this->m_PointerToUsername->size();
				
				

				for (	int i = 0; 
						i < this->_Container_Size_;
						++i	)
				{
					this->_What_Kind_	= this->m_PointerToUsername->at(i)->g_CharID();
					
					
					
					//	Set position to the sprite.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	this->m_PointerToUsername->at(i)->g_PositionPrp(1) + ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Third / 2.0) * this->m_PointerToUsername->at(i)->g_VisualPrp(1)	),
																												this->m_PointerToUsername->at(i)->g_PositionPrp(2) - ((_Sprites_->g_Sprite(this->_What_Sprite_)->g_Measures()->at(0).Fourth / 2.0) * this->m_PointerToUsername->at(i)->g_VisualPrp(2)	)	);
					
					//	Then goes the shrinking model.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_PointerToUsername->at(i)->g_VisualPrp(1)		,
																												this->m_PointerToUsername->at(i)->g_VisualPrp(2)		);
					
					//	Applying color properties.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_PointerToUsername->at(i)->g_ColorPrp(1)	,
																														this->m_PointerToUsername->at(i)->g_ColorPrp(2)	,
																														this->m_PointerToUsername->at(i)->g_ColorPrp(3)	,
																														this->m_PointerToUsername->at(i)->g_ColorPrp(4)	)	);

					//	Fix position to properly render on screen.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().x, this->_Draw_->g_WorldBounds(1))	,
																												tls::FixPos_Y(	_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->getPosition().y, this->_Draw_->g_WorldBounds(2))	);
					
					
					
					//	Draw it.
					this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_), false		);
				}
			}
		}

		//	Lifes and Coins.
		if (	enm_Draw::_LiviconHUD == What	)
		{
			this->m_LiviconHUD->Draw(	_Controller_LiviconHUD::enm_Draw::_Panel	);
			this->m_LiviconHUD->Draw(	_Controller_LiviconHUD::enm_Draw::_Life		);
			this->m_LiviconHUD->Draw(	_Controller_LiviconHUD::enm_Draw::_Coin		);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
};
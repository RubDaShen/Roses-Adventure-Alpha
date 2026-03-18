#pragma once
#include	"Tools_.h"
#include	"_MyIncludes_.h"
#include	"TheCandy.h"

#include	<vector>



class		FollowingParticle : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const double		_FollowTime_			= (GAME_LOOP_VALUE * 0.15);		//	Given in iterations.

//	-------------------------------------------
//				Important values
//	-------------------------------------------
private:
	TheCandy*		m_Linker	= nullptr;

	int				m_KindID	= def::enm_Defines::_NOT_INITIALIZED;
	int				m_LinkedID	= def::enm_Defines::_NOT_INITIALIZED;

	double			m_xTarget	= 0.0;
	double			m_yTarget	= 0.0;

	bool			m_HasArrived	= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	FollowingParticle(double _xP, double _yP, TheCandy* _MyPtr) : thyObject(_xP, _yP, def::enm_ObjectType::Prospform)
	{
		//	Important values.
		{
			this->m_Linker		= _MyPtr;
			this->m_LinkedID	= _MyPtr->g_ObjectID();
			this->m_KindID		= _MyPtr->g_KindID();

			this->_W			= this->m_Linker->g_MeasuresPrp(1);
			this->_H			= this->m_Linker->g_MeasuresPrp(2);
		}

		//	Fixing position values.
		{
			this->m_xTarget		= this->m_Linker->g_PositionPrp(1);
			this->m_yTarget		= this->m_Linker->g_PositionPrp(2);

			this->xS			= fabs(this->m_xTarget - this->xP) / this->_FollowTime_;
			this->yS			= fabs(this->m_yTarget - this->yP) / this->_FollowTime_;
		}
		
		//	Fixing shrinking values.
		{
			double		_OrgVal_ = -0.55;



			this->xFct		= this->yFct = 1.25;
			this->xFctS		= _OrgVal_ / this->_FollowTime_;
		}
	}

	~FollowingParticle()
	{

	}

//	-------------------------------------------
//					Functions !
//	-------------------------------------------
public:
	inline void			DoFollow()
	{
		//	Recalculating...
		{
			if (	this->m_LinkedID == this->m_Linker->g_ObjectID()	)
			{
				this->m_xTarget		= this->m_Linker->g_PositionPrp(1);
				this->m_yTarget		= this->m_Linker->g_PositionPrp(2);
			}
			else
			{
				this->m_HasArrived = true;
				this->m_Linker = nullptr;

				return;
			}
		}

		//	Chasing an object.
		{
			//	Case for xP...
			{
				if (	(this->xP + this->xS) < this->m_xTarget	)
				{
					this->xP	= this->xP + this->xS;
					this->xS	= this->xS + this->xA;
				}
				else
				{
					if (	(this->xP - this->xS) > this->m_xTarget	)
					{
						this->xP	= this->xP - this->xS;
						this->xS	= this->xS + this->xA;
					}
					else
					{
						this->xP	= this->m_xTarget;
					}
				}
			}

			//	Case for yP...
			{
				if (	(this->yP + this->yS) < this->m_yTarget	)
				{
					this->yP	= this->yP + this->yS;
					this->yS	= this->yS + this->yA;
				}
				else
				{
					if (	(this->yP - this->yS) > this->m_yTarget	)
					{
						this->yP	= this->yP - this->yS;
						this->yS	= this->yS + this->yA;
					}
					else
					{
						this->yP	= this->m_yTarget;
					}
				}
			}
		}	

		//	Shrinking part.
		{
			this->xFct	= this->xFct + this->xFctS;
			this->yFct	= this->xFct;



			if (	(this->xFct <= 0.5) || (this->yFct <= 0.5)	)
			{
				this->m_HasArrived	= true;
				return;
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters !
//	-------------------------------------------
public:
	inline void			s_ID(int _What, int _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_KindID = _Val;
			break;
		}
	}

	inline int			g_ID(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		this->m_KindID;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}

	}
	inline bool			g_HasArrived()
	{
		return this->m_HasArrived;
	}

	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case 1:
			return		(this->xP + (this->_W * 0.5));

		case 2:
			return		(this->yP - (this->_H * 0.5));

		default:
			return		(def::enm_Defines::_NOT_FOUND);
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
class _Controller_SpecialForm
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
		_Prospform		= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Containers
//	-------------------------------------------
private:
	std::vector<FollowingParticle*>			m_SpecialForm;

//	-------------------------------------------
//			Variables and constants
//	-------------------------------------------
private:
	double				_FollowTime_	= 0.15;
	int					_TotalKind_		= 10;

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
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_SpecialForm(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
	}

	~_Controller_SpecialForm()
	{
		
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				AddParticle(double _xP, double _yP, TheCandy* _Des)
	{
		if (	(0 <= _Des->g_KindID()) && (_Des->g_KindID() <= this->_TotalKind_)	)
		{
			this->m_SpecialForm.push_back(new FollowingParticle(_xP, _yP, _Des));
		}
		
	}
	inline void				AddParticle(TheCandy* _Des)
	{
		if (	(0 <= _Des->g_KindID()) && (_Des->g_KindID() <= this->_TotalKind_)	)
		{
			this->m_SpecialForm.push_back(new FollowingParticle(_Des->g_PositionPrp(1), _Des->g_PositionPrp(2), _Des));
		}		
	}

	inline void				Animate()
	{
		for (	int i = 0;
				i < this->m_SpecialForm.size();
				++i	)
		{
			this->m_SpecialForm[i]->DoFollow();



			//	Erasing when done.
			{
				if (	(this->m_SpecialForm[i]->g_HasArrived())		)
				{
					tls::EraseElement<FollowingParticle*>(this->m_SpecialForm, i);
				}
			}
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void				Draw(	int What	)
	{
		//	Prospform.
		if (	enm_Draw::_Prospform == What	)
		{
			this->_What_Sprite_			= spr::enm_At::Candies;
			this->_Container_Size_		= this->m_SpecialForm.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				this->_What_Kind_				= this->m_SpecialForm[i]->g_ID(1) - 1;



				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(	this->m_SpecialForm[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(	this->m_SpecialForm[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_SpecialForm[i]->g_VisualPrp(1)	,
																											this->m_SpecialForm[i]->g_VisualPrp(2)	);
				


				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}
	
//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double				g_FollowTime()
	{
		return	this->_FollowTime_;
	}
};
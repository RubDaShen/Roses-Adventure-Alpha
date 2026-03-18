#pragma once
#include	"Tools_.h"
#include	"_MyIncludes_.h"
#include	"TheCandy.h"
#include	"AfterGlows.h"
#include	"SoundFactory.h"

#include	<vector>



class		WrappedContainer
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	TheCandy*		m_Object_Ptr		= nullptr;
	int				m_Unique_ID			= def::enm_Defines::_NOT_INITIALIZED;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	WrappedContainer(TheCandy* _Your_Ptr)
	{
		this->m_Object_Ptr	= _Your_Ptr;
		this->m_Unique_ID	= _Your_Ptr->g_ObjectID();
	}

	~WrappedContainer()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline TheCandy*		g_Pointer()
	{
		return this->m_Object_Ptr;
	}
	inline int				g_UniqueID()
	{
		return this->m_Unique_ID;
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
class		_Controller_Wrappeds
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Stars		= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:	
	std::vector<WrappedContainer*>		m_Wrappeds;
	std::vector<GlowParticle*>			m_Stars;

//	-------------------------------------------
//				Variables and constants
//	-------------------------------------------
private:
	int			Tgg_ExplodeFuse			= def::enm_Triggers::NotInitialized;

	int			Rnd_Speed_From			= 3;
	int			Rnd_Speed_To			= 7;
	int			Rnd_Stars				= 2;

	int			Cnt_ExplodeFuse			= 0;

	double		m_WrappedExpand			= 0.65;
	double		m_XtraRadious			= 35.0;
	double		m_LifeTime				= 0.5;
	double		m_WrappedShake			= 3.0;

	double		m_WrappedCandyWait		= 0.4;
	double		m_WrappedFuseWait		= 0.25;

	double		m_WrappedForce			= 4.0;
	double		m_WrappedFuseForce		= 4.0;

	double		m_SpeedWrapeed			= 3.0;
	double		m_SpeedWrappedFuse		= 2.0;

//	-------------------------------------------
//				Outside and Linkers
//	-------------------------------------------
private:
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;
	SoundFactory*			_Sound_		= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;

	int			Cnt_PlayAgain = GAME_LOOP_VALUE * 2.0, Trg_PlayAgain = GAME_LOOP_VALUE * 1.95;
	int			_Where_Player = 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Controller_Wrappeds(	DrawFactory* _Draw_Ptr		, 
							SpriteFactory* _Sprite_Ptr	,	 
							SoundFactory* _Sound_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sound_		= _Sound_Ptr;
	}

	~_Controller_Wrappeds()
	{
		//	Deleting Wrappeds !
		{
			while (!this->m_Wrappeds.empty())
			{
				delete this->m_Wrappeds[0];
				this->m_Wrappeds.erase(this->m_Wrappeds.begin() + 0);
			}
		}

		//	Deleting Stars !
		{
			while (!this->m_Stars.empty())
			{
				delete this->m_Stars[0];
				this->m_Stars.erase(this->m_Stars.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				AddWrapped(TheCandy* _Des)
	{
		this->m_Wrappeds.push_back(	new WrappedContainer(_Des)	);
	}
	inline void				CheckWrappers()
	{
		for (	int i = 0; 
				i < this->m_Wrappeds.size(); 
				++i	)
		{
			//	Erasing the wrapped container when done.
			{
				if (this->m_Wrappeds[i]->g_Pointer()->g_ObjectID() != this->m_Wrappeds[i]->g_UniqueID())
				{
					tls::EraseElement<WrappedContainer*>(this->m_Wrappeds, i);
					continue;
				}
			}		

			//	Add some particles.
			{
				//	About the stars.
				{
					if (	!tls::Random(0, this->Rnd_Stars)	)
					{
						this->AddStar(this->m_Wrappeds[i]->g_Pointer());
					}
				}
			}
		}
	}
	
	inline void				AddStar(TheCandy* _Des)
	{
		double			_Angle_			= tls::DegToRad(	tls::Random(0, 360)		);
		double			_Speed_			= tls::Random(		this->Rnd_Speed_From, this->Rnd_Speed_To) / 2.0;
		double			_Aceleration_	= -0.005;

		double			_xP_			= _Des->g_PositionPrp(1) + (_Des->g_MeasuresPrp(1) / 2.0) + (std::cos(_Angle_) * this->m_XtraRadious);
		double			_yP_			= _Des->g_PositionPrp(2) - (_Des->g_MeasuresPrp(2) / 2.0) + (std::sin(_Angle_) * this->m_XtraRadious);



		//	Creating the star.
		{
			this->m_Stars.push_back(	new GlowParticle(	_xP_, _yP_, tls::Random(6, 7),
															AnmGlow::LinearMovement, _Des->g_KindID()	)	);
		}

		//	Setting all up.
		{
			this->m_Stars[this->m_Stars.size() - 1]->s_Pos_WithContainer(		tls::Vec4<double>(	_Speed_ * std::cos(_Angle_)			,
																									_Speed_ * std::sin(_Angle_)			,
																									_Aceleration_ * std::cos(_Angle_)	,
																									_Aceleration_ * std::sin(_Angle_)	)	);
			this->m_Stars[this->m_Stars.size() - 1]->s_Opacity_WithContainer(	tls::Vec3<double>(	255.0														, 
																									( - 255.0 / (GAME_LOOP_VALUE * this->m_LifeTime)) * _Speed_	,
																									0.0															)	);
			this->m_Stars[this->m_Stars.size() - 1]->s_Rotation_WithContainer(	tls::Vec3<double>(	0.0											, 
																									2.0 * tls::UnityRound(std::cos(_Angle_)		),
																									0.0											)	);
			this->m_Stars[this->m_Stars.size() - 1]->s_Visual_WithContainer(	tls::Vec2<double>(	1.0															, 
																									( - 1.0 / (GAME_LOOP_VALUE * this->m_LifeTime)) * _Speed_	)	);
		}
	}

	inline void				Animate()
	{
		//	Wrappers part.
		{
			this->CheckWrappers();
		}
		
		//	Actual animation part.
		{
			for (	int i = 0;
					i < this->m_Stars.size();
					++i	)
			{
				this->m_Stars[i]->AnimateParticle();



				//	Erasing when done.
				{
					if (	(this->m_Stars[i]->g_ColorPrp(4) <= 0.0)		)
					{
						tls::EraseElement<GlowParticle*>(this->m_Stars, i);
					}
				}
			}
		}
	}


	inline void				EnableCounter()
	{
		if (this->Tgg_ExplodeFuse != def::enm_Triggers::Activated)
		{
			this->Tgg_ExplodeFuse = def::enm_Triggers::Waiting;
		}
	}
	inline void				ResetCounter()
	{
		this->Tgg_ExplodeFuse	= def::enm_Triggers::NotInitialized;
		this->Cnt_ExplodeFuse	= 0;
	}
	inline void				StartCounter()
	{
		//	Fuses explode.
		if (	this->Tgg_ExplodeFuse == def::enm_Triggers::Waiting	)
		{
			if (this->Cnt_ExplodeFuse < (GAME_LOOP_VALUE * this->m_WrappedFuseWait))
			{
				++this->Cnt_ExplodeFuse;
			}
			else
			{
				this->Cnt_ExplodeFuse	= 0;
				this->Tgg_ExplodeFuse	= def::enm_Triggers::Activated;
			}
		}

		//	Fusing song.
		{
			if (this->m_Wrappeds.size() != 0)
			{
				if (this->Cnt_PlayAgain < this->Trg_PlayAgain)
				{
					++this->Cnt_PlayAgain;
				}
				else
				{
					this->_Where_Player = this->_Sound_->Play(snd::SndSys::Wrapped, 4);

					this->Cnt_PlayAgain = 0;
				}
			}
			else
			{
				this->_Sound_->AtPlayer_Stop(this->_Where_Player);
				this->Cnt_PlayAgain		= this->Trg_PlayAgain;
				this->_Where_Player		= def::enm_Defines::_NOT_FOUND;
			}
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void				Draw(	int What	)
	{
		//	Stars.
		if (	enm_Draw::_Stars == What	)
		{
			this->_What_Sprite_			= spr::enm_At::GlowParticles;
			this->_Container_Size_		= this->m_Stars.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				this->_What_Kind_		= this->m_Stars[i]->g_GlowID();



				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(	tls::FixPos_X(	this->m_Stars[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																											tls::FixPos_Y(	this->m_Stars[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_Stars[i]->g_ColorPrp(1)	,
																													this->m_Stars[i]->g_ColorPrp(2)	, 
																													this->m_Stars[i]->g_ColorPrp(3)	, 
																													this->m_Stars[i]->g_ColorPrp(4)	)	);

				//	Spining.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setRotation(	this->m_Stars[i]->g_RotationPrp(1)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Stars[i]->g_VisualPrp(1)	,
																											this->m_Stars[i]->g_VisualPrp(2)	);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}
	
//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<GlowParticle*>&			g_Vec_Stars()
	{
		return this->m_Stars;
	}

	inline double		g_Timing(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_WrappedCandyWait;

		case 2:
			return this->m_WrappedFuseWait;
		}
	}
	inline double		g_Data(int _What)
	{
		switch (_What)
		{
		case 1:
			return	this->m_WrappedForce;

		case 2:
			return	this->m_WrappedFuseForce;

		case 3:
			return	this->m_SpeedWrapeed;

		case 4:
			return	this->m_SpeedWrappedFuse;

		case 5:
			return	this->m_WrappedExpand;

		case 6:
			return	this->m_WrappedShake;
		}
	}
	inline int			g_Trigger(int _What)
	{
		int*		_Aux_Val	= nullptr;
		int			_Org_Value	= def::enm_Triggers::_Unknown;



		//	Selecting what trigger to use.
		{
			switch (_What)
			{
			case 1:
				_Aux_Val = &this->Tgg_ExplodeFuse;
				break;

			default:
				throw std::runtime_error("_Aux_Val is not pointing to any value.");
			}
		}

		//	Then checks for trigger value.
		{
			_Org_Value = *_Aux_Val;



			if (*_Aux_Val == def::enm_Triggers::Activated)
			{
				*_Aux_Val = def::enm_Triggers::NotInitialized;
			}
		}

		//	Finally, return.
		{
			return _Org_Value;
		}
	}
};
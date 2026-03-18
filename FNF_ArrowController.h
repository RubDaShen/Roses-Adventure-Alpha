#pragma once

#include		<iostream>
#include		<fstream>
#include		<string>

#include		"thyObject.h"
#include		"Tools_.h"
#include		"_MyIncludes_.h"
#include		"FNF_CharacterController.h"
#include		"SoundFactory.h"



class		Fnk_Arrow : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int			m_ArrowDirection	= def::enm_Defines::_NOT_INITIALIZED;
	int			m_ArrowType			= def::enm_Defines::_NOT_INITIALIZED;

	double		_Scale_Org			= 0.75;

	bool		m_CanAnimate		= true;
	int			m_ArrowSide			= def::enm_Defines::_NOT_INITIALIZED;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Fnk_Arrow(	double _xP, double _yP, double _Speed		, 
				int _ArrowDirection, bool _IsDownScrolling	,
				int _ArrowType, bool _CanAnimate, int _L_R	) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_ArrowDirection	= _ArrowDirection;
		this->yS				= _Speed;
		this->m_ArrowType		= _ArrowType;
		this->m_CanAnimate		= _CanAnimate;
		this->m_ArrowSide		= _L_R;

		switch (this->m_ArrowType)
		{
		case 1:
			this->_W	= 155.0 * this->_Scale_Org;
			this->_H	= 155.0 * this->_Scale_Org;
			break;

		case 2:
			this->_W	= 50.0 * this->_Scale_Org;
			this->_H	= 44.0 * this->_Scale_Org;
			break;

		case 3:
			this->_W	= 0.0 * this->_Scale_Org;
			this->_H	= 0.0 * this->_Scale_Org;
			break;
		}



		//	Setting some variables.
		this->xFct		= this->yFct = 0.75;
		tls::SetRGB_FNF(	this->m_ArrowDirection, this->R_col, this->G_col, this->B_col	);	
		if (this->m_ArrowType == 1)
		{
			switch (this->m_ArrowDirection)
			{
			case def::enm_Directions::Up:
				this->rotationDegree = 270.0;
				break;

			case def::enm_Directions::Left:
				this->rotationDegree = 180.0;
				break;

			case def::enm_Directions::Down:
				this->rotationDegree = 90.0;
				break;
			}
		}
		if (		(_IsDownScrolling)		&& 
				(this->m_ArrowType == 3)	)
		{
			this->rotationDegree = 180.0;
		}
	}

	~Fnk_Arrow()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			MoveArrow()
	{
		//	Position.
		{
			this->xP		= this->xP + this->xS;
			this->yP		= this->yP + this->yS;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_ArrowDirection()
	{
		return this->m_ArrowDirection;
	}
	inline int			g_ArrowDir_InArray()
	{
		switch (this->m_ArrowDirection)
		{
		case 1:
			return  def::enm_Directions::Left - 1;
			break;

		case 2:
			return def::enm_Directions::Down - 1;
			break;

		case 3:
			return def::enm_Directions::Up - 1;
			break;

		case 4:
			return def::enm_Directions::Right - 1;
			break;
		}
	}

	inline int			g_ArrowType()
	{
		return this->m_ArrowType;
	}
	inline bool			g_CanAnimate()
	{
		return this->m_CanAnimate;
	}
	inline int			g_ArrowSide()
	{
		return		this->m_ArrowSide;
	}
};
class		Fnk_HitBlock : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	int			m_ArrowDirection	= def::enm_Defines::_NOT_INITIALIZED;

//	-------------------------------------------
//				[2] Anima-variables
//	-------------------------------------------
private:
	int			Cnt_Animation	= 0, Trg_Animation = 144;

	int			Itr_Time_Col	= GAME_LOOP_VALUE;
	int			Itr_Time_Scale	= GAME_LOOP_VALUE / 10;
	int			Itr_Time_Glow	= GAME_LOOP_VALUE / 2;

	double		_R_Org = 0.0, _G_Org = 0.0, _B_Org = 0.0;
	double		_Scale_Org		= 0.75;
	double		_Opacity_Org	= 255.0;


	double		_Glow_Opacity	= 0.0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Fnk_HitBlock(double _xP, double _yP, int _ArrowDirection) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->xFct		= this->yFct = this->_Scale_Org;
		this->_W		= 155.0 * this->_Scale_Org;
		this->_H		= 155.0 * this->_Scale_Org;

		//	Update some values.
		tls::SetRGB_FNF(	def::enm_Directions::_None_, this->R_col, this->G_col, this->B_col	);
		this->_R_Org	= this->R_col;
		this->_G_Org	= this->G_col;
		this->_B_Org	= this->B_col;
		
		this->m_ArrowDirection	= _ArrowDirection;
		switch (this->m_ArrowDirection)
		{
		case def::enm_Directions::Up:
			this->rotationDegree = 270.0;
			break;

		case def::enm_Directions::Left:
			this->rotationDegree = 180.0;
			break;

		case def::enm_Directions::Down:
			this->rotationDegree = 90.0;
			break;
		}
	}

	~Fnk_HitBlock()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			MoveArrow()
	{
		//	Position.
		{
			this->xP		= this->xP + this->xS;
			this->yP		= this->yP + this->yS;
		}
	}
	inline void			Animate()
	{
		if (this->Cnt_Animation < this->Trg_Animation)
		{
			this->R_col			= this->R_col + ((this->_R_Org - this->R_col) / this->Itr_Time_Col);
			this->G_col			= this->G_col + ((this->_G_Org - this->G_col) / this->Itr_Time_Col);
			this->B_col			= this->B_col + ((this->_B_Org - this->B_col) / this->Itr_Time_Col);

			this->_Glow_Opacity	= this->_Glow_Opacity + (-this->_Glow_Opacity / this->Itr_Time_Glow);

			this->xFct			= this->xFct + ((this->_Scale_Org - this->xFct) / this->Itr_Time_Scale);
			this->yFct			= this->xFct;
		}
		else
		{
			this->R_col		= this->_R_Org;
			this->G_col		= this->_G_Org;
			this->B_col		= this->_B_Org;

			this->xFct		= this->yFct = this->_Scale_Org;

			this->_Glow_Opacity = 0.0;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			SetAnimation()
	{
		this->Cnt_Animation		= 0;

		tls::SetRGB_FNF(this->m_ArrowDirection, this->R_col, this->G_col, this->B_col);
		this->xFct				= this->yFct = this->_Scale_Org + 0.25;
		this->_Glow_Opacity		= this->_Opacity_Org;
	}

	inline int			g_ArrowDirection()
	{
		return this->m_ArrowDirection;
	}
	inline double		g_GlowOpacity()
	{
		return		this->_Glow_Opacity;
	}
};
/*	||	 ||
	|| G ||
	|| O ||
	||   ||
	|| T ||
	|| O ||
	||	 ||	*/
class _Controller_FnkArrows : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			[0] Containers and external
//	-------------------------------------------
private:
	std::vector<Fnk_Arrow*>			m_Arrows;
	std::vector<Fnk_HitBlock*>		m_Hitblock;

//	-------------------------------------------
//			[1] Auxiliar Variables
//	-------------------------------------------
private:
	std::vector<Fnk_Arrow*>			m_SimpleArrows;

	int				_Size_					= 0;
	bool			_CollisionDetected_		= false;

//	-------------------------------------------
//				[2] Variables
//	-------------------------------------------
private:
	double				m_ArrowDistance			= 0.0;
	double				m_ArrowSpeed			= 1.0;
	double				_Scale_Org_				= 0.75;

	int					m_InnerTime				= 0;

	bool				m_IsDownScrolling		= true;

//	-------------------------------------------
//				[3] Audio variables
//	-------------------------------------------
private:
	SoundFactory*		_Sound_ = nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_FnkArrows(double _xP, double _yP, SoundFactory* _Sound_Ptr, bool _IsDownScrolling) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->_Sound_				= _Sound_Ptr;
		this->m_IsDownScrolling		= _IsDownScrolling;
	}

	~_Controller_FnkArrows()
	{
		//	Deleting Arrows !
		{
			while (!this->m_Arrows.empty())
			{
				delete this->m_Arrows[0];
				this->m_Arrows.erase(this->m_Arrows.begin() + 0);
			}
		}

		//	Deleting HitBlocks !
		{
			while (!this->m_Hitblock.empty())
			{
				delete this->m_Hitblock[0];
				this->m_Hitblock.erase(this->m_Hitblock.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			MoveArrows(_Controller_FnkCharacters* _Characters)
	{
		this->m_SimpleArrows.clear();



		for (	int i = 0; 
				i < this->m_Arrows.size();
				++i	)
		{
			this->_CollisionDetected_ = false;



			//	Just move them all.
			this->m_Arrows[i]->MoveArrow();

			//	Here checking the collision.
			{
				//	Scrolling means that arrows are falling, therefore
				//	only when the arrow is lower than the hitblocks means that
				//	it indeed is about to hit it.
				if (	this->m_IsDownScrolling )
				{
					//	Collision detection.
					{
						if (	this->m_Arrows[i]->g_ArrowType() == 1	)
						{
							if (	this->m_Arrows[i]->g_PositionPrp(2) <= this->yP	)
							{
								this->_CollisionDetected_ = true;
							}
						}
						else
						{
							if (	this->m_Arrows[i]->g_PositionPrp(2) <= (this->yP - (110.0 * 0.5 * this->_Scale_Org_))	)
							{
								this->_CollisionDetected_ = true;
							}
						}
					}			
				}
				//	If it is not, then means that arrows are going up and
				//	when the arrow is higher than hits, means that... hit ;-;
				else
				{
					//	Collision detection.
					{
						if (	this->m_Arrows[i]->g_ArrowType() == 1	)
						{
							if (	this->m_Arrows[i]->g_PositionPrp(2) >= this->yP	)
							{
								this->_CollisionDetected_ = true;
							}
						}
						else
						{
							if (	this->m_Arrows[i]->g_PositionPrp(2) >= (this->yP - (110.0 * 0.5 * this->_Scale_Org_))	)
							{
								this->_CollisionDetected_ = true;
							}
						}
					}
				}		


				//	Then do some things if detected.
				if (this->_CollisionDetected_)
				{
					//	Check if arrow animates.
					{
						if (	this->m_Arrows[i]->g_CanAnimate()	)
						{
							this->m_Hitblock[this->m_Arrows[i]->g_ArrowDir_InArray()]->SetAnimation();

							_Characters->SetCharacterState(this->m_Arrows[i]->g_ArrowSide() - 1, this->m_Arrows[i]->g_ArrowDirection());	
						}
					}

					//	Proceed to deleeeete.
					tls::EraseElement<Fnk_Arrow*>(this->m_Arrows, i);
					continue;
				}		
			}

			//	Adding to the vector (Just for draw purposes).
			{
				if (	this->m_Arrows[i]->g_ArrowType() == 1	)
				{
					this->m_SimpleArrows.push_back(		this->m_Arrows[i]	);
				}
			}
		}



		++m_InnerTime;
	}
	inline void			Animate()
	{
		//	HitBlocks animation.
		{
			for (	int i = 0; 
					i < this->m_Hitblock.size(); 
					++i	)
			{
				this->m_Hitblock[i]->Animate();
			}
		}
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_HitBlocks(double _Distance)
	{
		this->m_ArrowDistance	= _Distance;



		//	Creating all the HitBlocks.
		{
			int			_Direction_ = 0;



			for (	int i = 0; 
					i < 4; 
					++i	)
			{
				//	Choosing the arrow direction.
				switch (i + 1)
				{
				case 1:
					_Direction_ = def::enm_Directions::Left;
					break;

				case 2:
					_Direction_ = def::enm_Directions::Down;
					break;

				case 3:
					_Direction_ = def::enm_Directions::Up;
					break;

				case 4:
					_Direction_ = def::enm_Directions::Right;
					break;
				}

				//	Actual creation.
				this->m_Hitblock.push_back(	new Fnk_HitBlock(	this->xP + (i * this->m_ArrowDistance)	, 
																this->yP								, 
																_Direction_)							);
			}
		}
	}
	inline void			Ld_Arrows(	double _SpeedFactor, int _LeftOrRight	)
	{
		//	----------------------------------------------------------------
		//		The left or right value is just to determine which file
		//				to use, since there are two sides...
		//					1 means left and 2 means right
		//	----------------------------------------------------------------
		
		//	Just calculating the speed.
		{
			this->m_ArrowSpeed		= this->m_ArrowSpeed * (_SpeedFactor) * ((this->m_IsDownScrolling) ? -1.0 : 1.0);
		}

		//	Here is the actual reading.
		{
			//	Variables to be used.
			const std::string		_R_FNF_NSc_			= "_Resources_\\FridayNightFunking\\NotesAndScripts\\";
			const std::string		_Unwind_			= "Unwind\\";

			std::fstream		File_;
			std::string			_Buffer_;

			char*				_Reader_Character	= new char;





			//	-------------------::..
			File_.open(_R_FNF_NSc_ + _Unwind_ + ((_LeftOrRight == 1) ? "l_Notes.rub" : "r_Notes.rub"));
			//	-----------------------------------------------------

			if (	!File_.is_open()	)
			{
				tls::SetColor(	tls::Colors::_Red	);
				std::cout << "Couldn't open data file. Starting from default...\n";
				tls::ResetColor();
			}
			else
			{
				//	Reading each line.
				while (		!File_.eof()	)
				{
					//	Reinterpret _Buffer_ (Proccess of reading).
					{
						//	----------------------------------------------------------------
						//							..::Meanings::..
						//	----------------------------------------------------------------
						//		Example: 100, 1, 0.25,
						//		1	Read until you find a ',' (comma).
						//		2	Keep, just read a single character (Direction).
						//		3	Then, read a double (Time).
						//		4	Repeat.
						//	----------------------------------------------------------------

						const int		_Maximum_Tries_		= 11;
						int				_Counter_			= 0;

						int				_yPos_			= 0;
						int				_Direction_		= 0;
						double			_Time_			= 0.0;



						//	Read for 'yP'.
						{		
							//	Getting the string from file.
							{
								File_.read(		_Reader_Character, 1	);

								while (	(_Counter_ < _Maximum_Tries_)	&&
										(*_Reader_Character != ','	)	)
								{					
									_Buffer_.push_back(*_Reader_Character);
									File_.read(_Reader_Character, 1);

									++_Counter_;
								}

								_Counter_ = 0;
							}

							//	Transform that string into a number.
							{
								_yPos_	= tls::StrToInt(_Buffer_, false);
							}

							//	Some touches.
							{
								_Buffer_.clear();
							}
						}

						//	Read for 'Direction'.
						{		
							//	Getting the string from file.
							{
								File_.read(		_Reader_Character, 1	);

								while (	(_Counter_ < _Maximum_Tries_)	&&
										(*_Reader_Character != ','	)	)
								{					
									_Buffer_.push_back(*_Reader_Character);
									File_.read(_Reader_Character, 1);

									++_Counter_;
								}

								_Counter_ = 0;
							}

							//	Transform that string into a number.
							{
								_Direction_	= tls::StrToInt(_Buffer_, false);
							}

							//	Some touches.
							{
								_Buffer_.clear();
							}
						}

						//	Read for 'Time'.
						{		
							//	Getting the string from file.
							{
								File_.read(		_Reader_Character, 1	);

								while (	(_Counter_ < _Maximum_Tries_)	&&
										(*_Reader_Character != ','	)	)
								{					
									_Buffer_.push_back(*_Reader_Character);
									File_.read(_Reader_Character, 1);

									++_Counter_;
								}

								_Counter_ = 0;
							}

							//	Transform that string into a number.
							{
								_Time_	= tls::StrToDouble(_Buffer_);
							}

							//	Some touches.
							{
								_Buffer_.clear();
								_Counter_ = 0;
							}
						}

						//	Once read, create arrow.
						{
							//	Fixes xP.
							double		_xPos_ = 0.0;
							switch (_Direction_)
							{
							case def::enm_Directions::Up:
								_xPos_ = this->xP + (2 * this->m_ArrowDistance);
								break;

							case def::enm_Directions::Down:
								_xPos_ = this->xP + (1 * this->m_ArrowDistance);
								break;

							case def::enm_Directions::Left:
								_xPos_ = this->xP;
								break;

							case def::enm_Directions::Right:
								_xPos_ = this->xP + (3 * this->m_ArrowDistance);
								break;
							}


							//	Fixes yP.
							_yPos_ = this->yP + (_yPos_ * _SpeedFactor);
							if (!this->m_IsDownScrolling)
							{
								_yPos_ = this->yP - _yPos_;
							}


							//	Creating and updating.
							{
								//	When time is 0 means that is a single arrow, no a long one.
								//	Else, create a long arrow.
								if (_Time_ == 0.0)
								{
									this->m_Arrows.push_back(	new Fnk_Arrow(	_xPos_, _yPos_, this->m_ArrowSpeed		,
																				_Direction_, this->m_IsDownScrolling	,
																				1, true, _LeftOrRight				)	);
								}
								else
								{
									int			_Height_		= (44 * _Scale_Org_) - 1;
									int			_Amount_		= (std::fabs(this->m_ArrowSpeed) * GAME_LOOP_VALUE * _Time_) / _Height_;
									double		_Aux_yPos_		= 0.0;

									

									//	The actual arrow.
									this->m_Arrows.push_back(	new Fnk_Arrow(	_xPos_, _yPos_, this->m_ArrowSpeed		,
																				_Direction_, this->m_IsDownScrolling	,
																				1, true, _LeftOrRight					)	);
									
									//	And its length.
									for (	int i = 0; 
											i < _Amount_;
											++i	)
									{
										//	yP calculation
										if (this->m_IsDownScrolling)
										{
											_yPos_ = _yPos_ + _Height_;
										}
										else
										{
											_yPos_ = _yPos_ - _Height_;
										}

										//	Last fix.
										_Aux_yPos_ = _yPos_ - (155 * 0.5 * _Scale_Org_);

										//	The long arrow.
										this->m_Arrows.push_back(	new Fnk_Arrow(	_xPos_ + (135 * _Scale_Org_ * 0.5), _Aux_yPos_, this->m_ArrowSpeed		,			
																					_Direction_, this->m_IsDownScrolling, 2									, 
																					!(i % 5)																,
																					_LeftOrRight															)	);
									}

									//	The tail arrow, but also a...
									//	Last fix.
									_Aux_yPos_ = _yPos_ + ((this->m_IsDownScrolling) ? (_Height_ - (64 * _Scale_Org_)) : (-_Height_ - (64 * _Scale_Org_)));

									this->m_Arrows.push_back	(new Fnk_Arrow(		_xPos_ + (135 * _Scale_Org_ * 0.5), _Aux_yPos_							,
																					this->m_ArrowSpeed, _Direction_, this->m_IsDownScrolling, 3				,
																					true																	,
																					_LeftOrRight															)	);
								}	
							}
						


							File_.read(_Reader_Character, 1);
						}
					}
				}
				






				//	-------------------::..
				File_.close();
				//	-----------------------------------------------------
			}

			//	-------------------::..
			//	Here you close the file...
			//	-----------------------------------------------------

			//	Deleting everything that has been used.
			{
				delete		_Reader_Character;
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<Fnk_HitBlock*>&			g_Vec_HitBlock()
	{
		return this->m_Hitblock;
	}

	inline std::vector<Fnk_Arrow*>&				g_Vec_Arrows()
	{
		return this->m_Arrows;
	}
	inline std::vector<Fnk_Arrow*>&				g_Vec_SimpleArrows()
	{
		return this->m_SimpleArrows;
	}
};
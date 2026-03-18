#pragma once

#include		<vector>

#include		"thyObject.h"
#include		"_MyIncludes_.h"
#include		"Tools_.h"
#include		"TheCandy.h"



//	---------::..
//	Don't confuse with SpawnPointTracker.
//	That one is for Frozen candies and Bom-O-Boms.
//	------------------------------------------------::..

struct		ColorPallette
{
//	-------------------------------------------
//					Variables
//	-------------------------------------------
	int			Color		= 0;
	bool		Active		= 0;

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
	ColorPallette(int _Color, bool _Active)
	{
		this->Color		= _Color;
		this->Active	= _Active;
	}

	~ColorPallette()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
};
class		SpawnPoint : public thyObject
{
//	What is m_SpawnDirection?
//		m_SpawnDirection is basically where candies will go
//		and how gravity will be applied to them. It's not that
//		complicated.

//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	int			_TotalKind_ = 10;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	std::vector<ColorPallette*>			m_ColorPallette;

	int				m_iPos = 0, m_jPos	= 0;
	int				m_SpawnDirection	= 0;
	int				m_ColorPicker		= 1;	//	How many colors to pick up.

	bool			m_Spawn = false;
	bool			m_IsTop = false;

//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	std::vector<int>		_AvailablePool_;

	int						_ChoosenColor_ = 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	SpawnPoint(double _xP, double _yP, int _iPos, int _jPos, int _Direction, int _ColorPicker, bool _Spawn, int RandomColors)
	{
		this->xP				= _xP;
		this->yP				= _yP;

		this->m_iPos			= _iPos;
		this->m_jPos			= _jPos;
		this->m_SpawnDirection	= _Direction;
		this->m_ColorPicker		= _ColorPicker;

		this->m_Spawn			= _Spawn;

		//	Color Pallette !
		{
			//	Initializing the color pallette.
			{
				for (	int i = 0; 
						i < this->_TotalKind_; 
						++i	)
				{
					this->m_ColorPallette.push_back(	new ColorPallette(0, true)	);
				}
			}

			//	By default, this is the set of colors.
			{
				//	Colors !		(	First set	)
				switch (	RandomColors	)
				{
				case	0:
					this->m_ColorPallette[0]->Color		= 1;
					this->m_ColorPallette[1]->Color		= 6;
					this->m_ColorPallette[2]->Color		= 3;
					this->m_ColorPallette[3]->Color		= 4;
					this->m_ColorPallette[4]->Color		= 2;
					this->m_ColorPallette[5]->Color		= 8;
					this->m_ColorPallette[6]->Color		= 7;
					this->m_ColorPallette[7]->Color		= 5;
					this->m_ColorPallette[8]->Color		= 9;
					this->m_ColorPallette[9]->Color		= 10;
					break;

				case	1:
					this->m_ColorPallette[0]->Color		= 1;
					this->m_ColorPallette[1]->Color		= 2;
					this->m_ColorPallette[2]->Color		= 3;
					this->m_ColorPallette[3]->Color		= 4;
					this->m_ColorPallette[4]->Color		= 5;
					this->m_ColorPallette[5]->Color		= 6;
					this->m_ColorPallette[6]->Color		= 7;
					this->m_ColorPallette[7]->Color		= 8;
					this->m_ColorPallette[8]->Color		= 9;
					this->m_ColorPallette[9]->Color		= 10;
					break;

				case	2:
					this->m_ColorPallette[0]->Color		= 8;
					this->m_ColorPallette[1]->Color		= 2;
					this->m_ColorPallette[2]->Color		= 5;
					this->m_ColorPallette[3]->Color		= 1;
					this->m_ColorPallette[4]->Color		= 7;
					this->m_ColorPallette[5]->Color		= 10;
					this->m_ColorPallette[6]->Color		= 4;
					this->m_ColorPallette[7]->Color		= 6;
					this->m_ColorPallette[8]->Color		= 3;
					this->m_ColorPallette[9]->Color		= 9;
					break;
				}
			}

			//	Final touches.
			{
				_AvailablePool_.reserve(	this->_TotalKind_	);

				this->UpdateAvailablePool();
			}
		}
	}

	~SpawnPoint()
	{
		tls::DeleteVector(this->m_ColorPallette);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline int			g_RandomColor()
	{
		this->_ChoosenColor_ = this->m_ColorPallette[_AvailablePool_[tls::Random(0, this->_AvailablePool_.size() - 1)]]->Color;
		return		this->_ChoosenColor_;
	}

	inline void			UpdateAvailablePool()
	{
		_AvailablePool_.clear();

		for (	int i = 0; 
				i < this->m_ColorPicker; 
				++i	)
		{
			if (	this->m_ColorPallette[i]->Active	)
			{ 
				_AvailablePool_.emplace_back(i);
			}
		}		
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void			s_Is(int _What, bool _Val)
	{
		switch (_What)
		{
		case 1:
			this->m_IsTop = _Val;
			break;
		}
	}

	inline int			g_Pos(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->m_iPos;

		case 2:
			return this->m_jPos;

		default:
			return -1;
		}
	}
	inline int			g_SpawnDirection()
	{
		return this->m_SpawnDirection;
	}
	inline bool			g_Spawn()
	{
		return this->m_Spawn;
	}
	inline bool			g_Is(int _What)
	{
		switch (_What)
		{
		case 1:
			return this->m_IsTop;

		default:
			return def::enm_Defines::_NOT_FOUND;
		}
	}

	inline std::vector<int>&				g_AvailablePool()
	{
		return		this->_AvailablePool_;
	}
	inline ColorPallette*					g_ColorPallette(int _What_Color)
	{
		//	Returns the position of that color in the vector.
		//	If I choose yellow, this function will search through
		//	the whole vector and return that color pallette.

		for (	int i = 0; 
				i < this->_TotalKind_; 
				++i	)
		{
			if (	this->m_ColorPallette[i]->Color == _What_Color	)
			{
				return		this->m_ColorPallette[i];
			}
		}

		return		this->m_ColorPallette[0];
	}
	inline int								g_ColorPalletteInArray(int _What_Color)
	{
		//	Return the position of the array of the given color.

		for (	int i = 0; 
				i < this->_TotalKind_; 
				++i	)
		{
			if (	this->m_ColorPallette[i]->Color == _What_Color	)
			{
				return		i;
			}
		}

		return		def::enm_Defines::_NOT_FOUND;
	}
	inline bool								AllBlocked()
	{
		bool		_AllColorsOff_ = true;



		for (	int i = 0;
				i < this->m_ColorPicker; 
				++i	)
		{
			if (	this->m_ColorPallette[i]->Active	)
			{
				_AllColorsOff_ = false;
				break;
			}
		}



		return	_AllColorsOff_;
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
class		_Controller_SpawnPoints
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double		_GridBound_		= 90.0;
	int			_TotalKind_		= 10;
	int			_InvalidIPos_	= -9;

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<SpawnPoint*>		m_SpawnPoints;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		_xPos_			= 0.0,	_yPos_ = 0.0;
	int			_BoardWidth_	= 0,	_BoardHeight_ = 0;
	int			_ColorAmount_	= 4;
	bool		_AllItems_		= false;

//	-------------------------------------------
//				Auxiliar Variables
//	-------------------------------------------
private:
	double		_xCommonSpeed_		= 0.0;
	double		_yCommonSpeed_		= 0.0;

	int			_Size_SpawnPoints_		= 0;
	int			_Aux_Size_				= 0;
	int			_Reference_				= 0;
	int			_Where_					= 0;
	int			_TopValue_				= 0;
	int			_Aux_TopValue_			= 0;
	int			_RandomColorsPallette_	= 0;

	bool		_HitSpawnPoint_		= false;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_SpawnPoints()
	{

	}

	~_Controller_SpawnPoints()
	{
		tls::DeleteVector(this->m_SpawnPoints);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddSpawnPoint(	int _Where_iPos, int _Where_jPos, int _SpawnDirection, int _IsActive	) 
	{
		//	--------------------------------------------------
		//				Creating a SpawnPoint.
		//	--------------------------------------------------
		this->m_SpawnPoints.push_back(new SpawnPoint(	this->_xPos_ + (_Where_jPos * this->_GridBound_)			, 
														this->_yPos_ + (_Where_iPos * this->_GridBound_)			,
														_Where_iPos, _Where_jPos, _SpawnDirection, _ColorAmount_	,
														_IsActive, _RandomColorsPallette_							)	);


		//	------------------------------------------------------------------
		//		If the SpawnPoint is located at a top (or where candies)
		//		can freely get off the board, then that Spawn point 
		//			will have an extra condition when spawning.
		//	------------------------------------------------------------------
		if (	((_Where_iPos == 0) || (_Where_iPos == (this->_BoardWidth_ - 1)))		||
				((_Where_jPos == 0) || (_Where_jPos == (this->_BoardHeight_ - 1)))		)
		{
			this->m_SpawnPoints[this->m_SpawnPoints.size() - 1]->s_Is(1, true);
		}


		//	------------------------------------------------------------------
		//		Then, acording to it's _SpawnDirection, the SpawnPoint will
		//						be repositioned.
		//	------------------------------------------------------------------
		int			_Where_ = this->m_SpawnPoints.size() - 1;



		switch (_SpawnDirection)
		{
		case def::enm_Directions::Up:
			//	Position!
			{
				this->m_SpawnPoints[_Where_]->s_PositionPrp(1, this->m_SpawnPoints[_Where_]->g_PositionPrp(1) + (this->_GridBound_ / 2.0));
				this->m_SpawnPoints[_Where_]->s_PositionPrp(2, this->m_SpawnPoints[_Where_]->g_PositionPrp(2) - this->_GridBound_);
			}

			//	Width and Height.
			{
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(1, 1);
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(2, this->_GridBound_);
			}

			break;

		case def::enm_Directions::Down:
			//	Position!
			{
				this->m_SpawnPoints[_Where_]->s_PositionPrp(1, this->m_SpawnPoints[_Where_]->g_PositionPrp(1) + (this->_GridBound_ / 2.0));
				this->m_SpawnPoints[_Where_]->s_PositionPrp(2, this->m_SpawnPoints[_Where_]->g_PositionPrp(2) + this->_GridBound_);
			}

			//	Width and Height.
			{
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(1, 1);
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(2, this->_GridBound_);
			}
			
			break;

		case def::enm_Directions::Left:
			//	Position!
			{
				this->m_SpawnPoints[_Where_]->s_PositionPrp(1, this->m_SpawnPoints[_Where_]->g_PositionPrp(1) + this->_GridBound_);
				this->m_SpawnPoints[_Where_]->s_PositionPrp(2, this->m_SpawnPoints[_Where_]->g_PositionPrp(2) - (this->_GridBound_ / 2.0));
			}

			//	Width and Height.
			{
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(1, this->_GridBound_);
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(2, 1);
			}

			break;

		case def::enm_Directions::Right:
			//	Position!
			{
				this->m_SpawnPoints[_Where_]->s_PositionPrp(1, this->m_SpawnPoints[_Where_]->g_PositionPrp(1) - this->_GridBound_);
				this->m_SpawnPoints[_Where_]->s_PositionPrp(2, this->m_SpawnPoints[_Where_]->g_PositionPrp(2) - (this->_GridBound_ / 2.0));				
			}

			//	Width and Height.
			{
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(1, this->_GridBound_);
				this->m_SpawnPoints[_Where_]->s_MeasuresPrp(2, 1);
			}

			break;
		}
	}
	inline void			CreateSpawnPoints()
	{
		for (	int i = 0;
				i < this->_BoardWidth_;
				++i	)
		{
			this->AddSpawnPoint(0, i, def::enm_Directions::Down, true);
		}
	}
	
	//	Partial solution.
	inline int			GetRandomItem()
	{
		int				_RandomItem_ = tls::Random(STA_::enm_ItemID::CommonCandy, STA_::enm_ItemID::PoppingCandy);

		if (	_RandomItem_ == STA_::enm_ItemID::WrappedFuse	)
		{
			_RandomItem_		= STA_::enm_ItemID::CommonCandy;
		}

		if (	!this->_AllItems_	)
		{
			return		STA_::enm_ItemID::CommonCandy;
		}

		return		_RandomItem_;
	}

	inline void			DoSpawn(	std::vector<TheCandy*>&				_Candies		,
									std::vector<std::vector<int>>&		_ATs_Row_		,
									std::vector<std::vector<int>>&		_ATs_Column_	)
	{
		this->_Size_SpawnPoints_		= this->m_SpawnPoints.size();



		for (int k = 0; k < _Size_SpawnPoints_; ++k)
		{
			this->_HitSpawnPoint_		= false;
			this->_xCommonSpeed_		= 0.0;
			this->_yCommonSpeed_		= 0.0;



			//	If this spawn point allows to spawn candies, and if they spawn pos are valid.
			if	(							this->m_SpawnPoints[k]->g_Spawn()												&&
				(	(this->m_SpawnPoints[k]->g_Pos(1) >= 0) && (this->m_SpawnPoints[k]->g_Pos(1) < this->_BoardHeight_)	)	&&
				(	(this->m_SpawnPoints[k]->g_Pos(2) >= 0) && (this->m_SpawnPoints[k]->g_Pos(2) < this->_BoardWidth_)	)	)
			{
				//	In a few words, if the spawnpoint collides with a candy,
				//	then the spawnpoint cannot spawn any candies.
				{
					int			_Size_Candies = _Candies.size();



					for (	int i = _Size_Candies - 1;
							i >= 0;
							--i	)
					{
						//	Basic collision.
						if (tls::CollidesWith(	this->m_SpawnPoints[k]->g_PositionPrp(1), this->m_SpawnPoints[k]->g_PositionPrp(2),
												this->m_SpawnPoints[k]->g_MeasuresPrp(1), this->m_SpawnPoints[k]->g_MeasuresPrp(2),
												_Candies[i]->g_PositionPrp(1), _Candies[i]->g_PositionPrp(2),
												_Candies[i]->g_MeasuresPrp(1), _Candies[i]->g_MeasuresPrp(2)	)	)
						{
							this->_HitSpawnPoint_ = true;
							break;
						}

						//	Top condition.
						if (this->m_SpawnPoints[k]->g_Is(1))
						{
							//	Searching.
							switch (this->m_SpawnPoints[k]->g_SpawnDirection())
							{							
							case def::enm_Directions::Up:
								if (_Candies[i]->g_PositionPrp(2) <= this->m_SpawnPoints[k]->g_PositionPrp(2))
								{
									this->_HitSpawnPoint_ = true;
								}
								break;

							case def::enm_Directions::Down:
								if (	(_Candies[i]->g_PositionPrp(2)				>= 
										(this->m_SpawnPoints[k]->g_PositionPrp(2) + this->m_SpawnPoints[k]->g_MeasuresPrp(2)))		&&
										(_Candies[i]->g_Pos(2) == this->m_SpawnPoints[k]->g_Pos(2))						)
								{
									this->_HitSpawnPoint_ = true;
								}
								break;

							case def::enm_Directions::Left:
								if (_Candies[i]->g_PositionPrp(1) >= this->m_SpawnPoints[k]->g_PositionPrp(1))
								{
									this->_HitSpawnPoint_ = true;
								}
								break;

							case def::enm_Directions::Right:
								if (_Candies[i]->g_PositionPrp(1) <= this->m_SpawnPoints[k]->g_PositionPrp(1))
								{
									this->_HitSpawnPoint_ = true;
								}
								break;
							}

							//	If found, end this loop.
							if (this->_HitSpawnPoint_)
							{
								break;
							}
						}	
					}


				}

				//	This is a swapping condition...
				//	Works only for gravity type (Down).
				{
					if (!_ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)].empty())
					{
						_Aux_Size_		= _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)].size();
						_TopValue_		= _Candies[_ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][_Aux_Size_ - 1]]->g_Pos(1);
						_Where_			= _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][_Aux_Size_ - 1];
						


						for (	int a = 0; 
								a < _Aux_Size_;
								++a	)
						{
							_Aux_TopValue_	= _Candies[_ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][a]]->g_Pos(1);


					
							if (	_TopValue_ <= 0	)
							{
								break;
							}

							if (	_TopValue_ > _Aux_TopValue_			)
							{
								_TopValue_		= _Aux_TopValue_;
								_Where_			= _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][a];
							}
						}




						if (	_Candies[_Where_]->g_Pos(1) == this->m_SpawnPoints[k]->g_Pos(1)	)
						{
							if (_Candies[_Where_]->g_IsSwapping(1))
							{
								this->_HitSpawnPoint_ = true;
							}
						}
					}
				}





				//	Finding any candy that can be compared.
				{
					if (!_HitSpawnPoint_)
					{
						_Where_			= def::enm_Defines::_NOT_FOUND;
						_Reference_		= def::enm_Defines::_NOT_FOUND;

						double			_Highest_ = 0.0;
						double			_Lowest_ = 0.0;



						switch (this->m_SpawnPoints[k]->g_SpawnDirection())
						{
						case def::enm_Directions::Down:
							//	Getting which candy is the lowest to compare with.
							{
								for (	int i = 0;
										i < _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)].size();
										++i)
								{
									_Where_		= _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][i];



									if (_Candies[_Where_]->g_PositionPrp(2) < _Lowest_)
									{
										_Lowest_ = _Candies[_Where_]->g_PositionPrp(2);
									}
								}
							}

							//	Getting which candy is the highest to use as reference.
							{
								_Highest_ = _Lowest_;



								for (	int i = 0;
										i < _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)].size();
										++i	)
								{
									_Where_ = _ATs_Column_[this->m_SpawnPoints[k]->g_Pos(2)][i];



									if (_Candies[_Where_]->g_PositionPrp(2) > _Highest_)
									{
										_Highest_ = _Candies[_Where_]->g_PositionPrp(2);
										_Reference_ = _Where_;
									}
								}
							}

							break;
						}
					}
				}

				//	If _Hit_ is true, means that a candy is obstructing the
				//	spawnpoint, otherwise meaning that can spawn freely.
				{
					if (!this->_HitSpawnPoint_)
					{
						//	Creating the candy.
						{		
							_Candies.push_back(new TheCandy(	this->m_SpawnPoints[k]->g_PositionPrp(1)	,
																this->m_SpawnPoints[k]->g_PositionPrp(2)	,
																this->m_SpawnPoints[k]->g_RandomColor()		, 
																this->GetRandomItem()						,
																this->m_SpawnPoints[k]->g_Pos(1)			,
																this->m_SpawnPoints[k]->g_Pos(2)			)	);					
						}

						//	Last fixes.
						{
							//	Position fix.
							{
								this->_Where_ = _Candies.size() - 1;
								switch (this->m_SpawnPoints[k]->g_SpawnDirection())
								{
								case def::enm_Directions::Up:
									//	Position!
									{
										_Candies[_Where_]->s_PositionPrp(1, _Candies[_Where_]->g_PositionPrp(1) - (this->_GridBound_ / 2.0));
									}

									break;

								case def::enm_Directions::Down:
									//	Position!
									{
										_Candies[_Where_]->s_PositionPrp(1, _Candies[_Where_]->g_PositionPrp(1) - (this->_GridBound_ / 2.0));
									}

									break;								

								case def::enm_Directions::Left:
									//	Position!
									{
										_Candies[_Where_]->s_PositionPrp(2, _Candies[_Where_]->g_PositionPrp(2) + (this->_GridBound_ / 2.0));
									}

									break;

								case def::enm_Directions::Right:
									//	Position!
									{
										_Candies[_Where_]->s_PositionPrp(2, _Candies[_Where_]->g_PositionPrp(2) + (this->_GridBound_ / 2.0));
									}

									break;
								}
							}

							//	Speed fix.
							{
								_Where_ = _Candies.size() - 1;
								_Candies[_Where_]->s_GravityDirection(1, this->m_SpawnPoints[k]->g_SpawnDirection());

								if (_Reference_ != def::enm_Defines::_NOT_FOUND)
								{
									if (_Candies[_Where_]->g_GravityDirection(1) == _Candies[_Reference_]->g_GravityDirection(1))
									{
										this->_xCommonSpeed_ = _Candies[_Reference_]->g_PositionPrp(3);
										this->_yCommonSpeed_ = _Candies[_Reference_]->g_PositionPrp(4);



										_Candies[_Where_]->s_PositionPrp(3, this->_xCommonSpeed_);
										_Candies[_Where_]->s_PositionPrp(4, this->_yCommonSpeed_);

										_Candies[_Where_]->s_Is(1, true);
									}
								}
							}
						}
					}	
				}
			}
		}
	}

	inline void			LockKind(		int _What_Kind		)
	{
		this->_Size_SpawnPoints_ = this->m_SpawnPoints.size();


		
		//	Set as false the active value color.
		{
			for (	int i = 0; 
					i < this->_Size_SpawnPoints_; 
					++i	)
			{
				//	Set as inactive.
				this->m_SpawnPoints[i]->g_ColorPallette(_What_Kind)->Active = false;

				//	But if all colors are off, then unlock this one.
				if (	this->m_SpawnPoints[i]->AllBlocked()	)
				{
					this->m_SpawnPoints[i]->g_ColorPallette(_What_Kind)->Active = true;
				}
			}
		}

		//	After a color was locked, then update the available pool.
		{
			int		_Size_ = this->m_SpawnPoints.size();



			for (	int i = 0; 
					i < _Size_;
					++i	)
			{
				this->m_SpawnPoints[i]->UpdateAvailablePool();
			}
		}
	}
	inline void			UnlockKind(		int _What_Kind		)
	{
		this->_Size_SpawnPoints_ = this->m_SpawnPoints.size();



		//	Set as true the active value color.
		{
			for (	int i = 0; 
					i < this->_Size_SpawnPoints_; 
					++i	)
			{
				this->m_SpawnPoints[i]->g_ColorPallette(_What_Kind)->Active = true;
			}
		}

		//	After a color was locked, then update the available pool.
		{
			int		_Size_ = this->m_SpawnPoints.size();



			for (	int i = 0; 
					i < _Size_;
					++i	)
			{
				this->m_SpawnPoints[i]->UpdateAvailablePool();
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void				UpdateBoardValues(double _xP, double _yP, int _BoardWidth, int _BoardHeight)
	{
		this->_xPos_			= _xP;
		this->_yPos_			= _yP;
		this->_BoardWidth_		= _BoardWidth;
		this->_BoardHeight_		= _BoardHeight;
	}

	inline SpawnPoint*			g_SpawnPoint(int _What)
	{
		return		this->m_SpawnPoints[_What];
	}
	inline bool					g_ColorIsInPallette(int _What_Color)
	{
		//	_What_Color is given in Kind.
		//	6 means Cyan, 3 means Yellow and so on...

		//	By now, I'm just taking the first SpawnPoint.

		if (	this->m_SpawnPoints[0]->g_ColorPalletteInArray(_What_Color) < this->_ColorAmount_	)
		{
			return		true;
		}

		return		false;
	}
};
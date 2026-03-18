#pragma once

#include		<chrono>

#include		"thyObject.h"
#include		"MemoryUsage.h"
#include		"Tools_.h"
#include		"_MyIncludes_.h"

#include		"DrawFactory.h"
#include		"SpriteFactory.h"
#include		"LogicalController.h"



class		FPS__ : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Chrono Variables (Time)
//	-------------------------------------------
private:
	std::chrono::steady_clock::time_point		m_Start;
	std::chrono::steady_clock::time_point		m_End;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double				m_Value			= 0.0;
	int					m_TickUpdate	= (144 / 20);
	int					m_InnerTime		= 0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FPS__(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~FPS__()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoTracking()
	{	
		//	First, let's get the time.
		{
			this->m_End			= std::chrono::high_resolution_clock::now();
		}

		//	Then, do some calculus to get the actual value.
		{
			if (	(this->m_InnerTime % this->m_TickUpdate) == 0	)
			{
				this->m_Value		= std::chrono::duration_cast<std::chrono::microseconds>(this->m_End - this->m_Start).count();
				this->m_Value		= 1000000.0 / this->m_Value;
			}
		}

		//	Finally, save the time from now.
		{
			this->m_Start		= std::chrono::high_resolution_clock::now();
		}
		


		++this->m_InnerTime;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline double			g_Value()
	{
		return		this->m_Value;
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
class		_Controller_Statistics
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	FPS__*				m_FPS = nullptr;
	MemoryUsage__*		m_Memory = nullptr;

//	-------------------------------------------
//			Window variables and more
//	-------------------------------------------
private:
	double			_Win_W = 0.0, _Win_H = 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_InnerTime		= 0.0;

//	-------------------------------------------
//				External and Linkers
//	-------------------------------------------
private:
	DrawFactory*		_Draw_	= nullptr;
	TextFactory*		_Text_	= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Statistics( DrawFactory* _Draw_Ptr, TextFactory* _Text_Ptr )
	{
		//	Linking controllers and factories.
		{
			this->_Draw_	= _Draw_Ptr;
			this->_Text_	= _Text_Ptr;
		}

		//	Updating some values.
		{
			this->_Win_W	= this->_Draw_->g_WindowBounds(1);
			this->_Win_H	= this->_Draw_->g_WindowBounds(2);
		}

		this->Ld_All();
	}

	~_Controller_Statistics()
	{
		this->Del_All();
	}


//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_All()
	{
		//	Loading the FPS__.
		{
			this->m_FPS = new FPS__(	tls::Scale(1800, this->_Win_W) * 15.		, 
										tls::Scale(1000, this->_Win_H) * 15.0		);
		}

		//	Loading the MemoryUsage__.
		{
			this->m_Memory = new MemoryUsage__(		tls::Scale(1800, this->_Win_W) * 160.0	,
													tls::Scale(1000, this->_Win_H) * 15.0	);
		}
	}
	inline void			Del_All()
	{
		tls::Delete(this->m_FPS);
		tls::Delete(this->m_Memory);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoStatistics()
	{
		//	FPS part.
		{
			this->m_FPS->DoTracking();
		}



		this->m_InnerTime	= this->m_InnerTime + (1.0 / _Controller_Logic::_ogLpV_);
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			DrawStatistics()
	{
		//	Drawing the FPS counter.
		{
			//	Setting the string!
			this->_Text_->g_Text(0)->setString(		"Star Adventure v.0.0.3.2605 InDev     FPS " + tls::DoubleToStr(this->m_FPS->g_Value(), 2)	);

			//	Size, Outline, etc...
			{
				_Text_->g_Text(0)->setCharacterSize(		20		);
				_Text_->g_Text(0)->setOutlineThickness(		0		);
			}

			//	Positional value!
			this->_Text_->g_Text(0)->setPosition(	this->m_FPS->g_PositionPrp(1)	, 
													this->m_FPS->g_PositionPrp(2)	);



			//	Draw it!
			this->_Draw_->DrawText(this->_Text_->g_Text(0), false);
		}

		//	Drawing the Memory Usage.
		{
			//	Setting the string!
			this->_Text_->g_Text(0)->setString(		"Memory " + tls::DoubleToStr(	this->m_Memory->g_MemoryUsage(2), 3	) + " MB"	);

			//	Size, Outline, etc...
			{
				_Text_->g_Text(0)->setCharacterSize(		20		);
				_Text_->g_Text(0)->setOutlineThickness(		0		);
			}

			//	Positional value!
			this->_Text_->g_Text(0)->setPosition(	this->m_Memory->g_PositionPrp(1) + 375.0	,
													this->m_Memory->g_PositionPrp(2)			);



			//	Draw it!
			this->_Draw_->DrawText(this->_Text_->g_Text(0), false);
		}

		//	Drawing the Memory Usage.
		{
			//	Setting the string!
			this->_Text_->g_Text(0)->setString(		"Server Time: " + tls::DoubleToStr(	this->m_InnerTime, 3	) + " s"	);

			//	Size, Outline, etc...
			{
				_Text_->g_Text(0)->setCharacterSize(		20		);
				_Text_->g_Text(0)->setOutlineThickness(		0		);
			}

			//	Positional value!
			this->_Text_->g_Text(0)->setPosition(	740.0, this->m_FPS->g_PositionPrp(2)	);



			//	Draw it!
			this->_Draw_->DrawText(this->_Text_->g_Text(0), false);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline FPS__*				g_FPS()
	{
		return		this->m_FPS;
	}
	inline MemoryUsage__*		g_Memory()
	{
		return		this->m_Memory;
	}
};
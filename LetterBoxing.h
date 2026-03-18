#pragma once

#include	<vector>

#include	"thyObject.h"
#include	"_MyIncludes_.h"
#include	"Tools_.h"



class		LetterBox : public thyObject
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
	LetterBox(double _xP, double _yP, double _Width, double _Height, double _xFct, double _yFct) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->_W	= _Width;
		this->_H	= _Height;
		this->xFct	= _xFct;
		this->yFct	= _yFct;

		this->R_col		= this->G_col = this->B_col = 0.0;
		this->A_alpha	= 0.0;
	}

	~LetterBox()
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
class		_Controller_LetterBoxes
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<LetterBox*>			m_Bars;

//	-------------------------------------------
//				Constants and more
//	-------------------------------------------
private:
	double		$_xGround = 0.0, $_yGround = 0.0;
	double		$_WindowW = 0.0, $_WindowH = 0.0;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double		m_OffSet_Y		= 100;
	double		m_BarsWidth		= 0.0, m_BarsHeight = 150;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_LetterBoxes(double _WindowWidth, double _WindowHeight, double _xGround, double _yGround)
	{
		//	Loading important bounds.
		{
			this->$_xGround		= _xGround;
			this->$_yGround		= _yGround;
			this->$_WindowW		= _WindowWidth;
			this->$_WindowH		= _WindowHeight;
		}


		this->Ld_Everything();
	}

	~_Controller_LetterBoxes()
	{
		this->Del_Everything();
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				Ld_Everything()
	{
		//	Loading the bars measures.
		{
			this->m_BarsWidth	= this->$_WindowW;
			this->m_BarsHeight	= this->m_BarsHeight * (this->$_WindowH / 1000.0);
		}

		//	Creating the Bars.
		{
			//	Of course the main purpose is to create two bars.
			//	But you can always create more.
			//	The default is two.
			double		xFct = (this->$_WindowW / 1800.0);
			double		yFct = (this->$_WindowH / 1000.0) * (this->m_BarsHeight / 100.0);



			//	Creating the first bar.
			this->m_Bars.push_back(		new LetterBox(	tls::TransformPos_X(0, this->$_xGround)					, 
														tls::TransformPos_Y(0, this->$_yGround) + m_OffSet_Y	,
														this->m_BarsWidth, this->m_BarsHeight					,
														xFct, yFct												)	);

			//	Creating the second bar.
			this->m_Bars.push_back(		new LetterBox(	tls::TransformPos_X(0, this->$_xGround	)												,
														tls::TransformPos_Y(this->$_WindowH, this->$_yGround) + this->m_BarsHeight - m_OffSet_Y	,
														this->m_BarsWidth, this->m_BarsHeight													,
														xFct, yFct																				)	);
		}
	}
	inline void				Del_Everything()
	{
		//	Deleting Bars !
		{
			while (!this->m_Bars.empty())
			{
				delete		this->m_Bars[0];
				this->m_Bars.erase(this->m_Bars.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<LetterBox*>&				g_Vec_Bars()
	{
		return this->m_Bars;
	}
};
#pragma once

#include	"thyObject.h"
#include	"thyEffect.h"



class		FancyLogo : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	thyEffect*		m_MyEffect = nullptr;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	FancyLogo(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		//	Creating the effect.
		this->m_MyEffect = new thyEffect();
	}

	~FancyLogo()
	{
		//	Deleting the effect.
		delete		this->m_MyEffect;
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Animate()
	{
		//	Run all possible effects.
		{
			this->m_MyEffect->FadeIO();
		}

		//	Set effects properties.
		{
			this->A_alpha = this->m_MyEffect->g_FIO(1);
		}
	}

	inline void			Set_FadeIO(		double _From, double _Top, double _Down		,
										double _Time_Frm_Top, double _Time_Top_Dwn	)
	{
		this->m_MyEffect->Ini_FadeInOut(	_From, _Top, _Down, _Time_Frm_Top, _Time_Top_Dwn	);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline bool			g_AnimationEnd()
	{
		return			this->m_MyEffect->g_FIO(3);
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
class	_Controller_Logo
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				[0] Constants
//	-------------------------------------------
private:
	double			$_Window_W = 0.0, $_Window_H = 0.0;

//	-------------------------------------------
//				[1] Variables
//	-------------------------------------------
private:
	std::vector<FancyLogo*>			m_Logos;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_Logo(double _Win_W, double _Win_H)
	{
		this->$_Window_W	= _Win_W;
		this->$_Window_H	= _Win_H;

		this->Ld_Logos();
	}

	~_Controller_Logo()
	{
		//	Deleting Logos !
		{
			while (!this->m_Logos.empty())
			{
				delete		this->m_Logos[0];
				this->m_Logos.erase(this->m_Logos.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//				Loading	Functions
//	-------------------------------------------
public:
	inline void			Ld_Logos()
	{
		//	The main logo.
		{
			this->m_Logos.push_back(	new FancyLogo(0, this->$_Window_H / 2.0)	);
		}
	}

//	-------------------------------------------
//				Functions
//	-------------------------------------------
public:
	inline void			s_Anm_FadeIO(int _What, double _From, double _To, double _Down	,	 
												double _Tm_From_To, double _Tm_To_Down	)
	{
		this->m_Logos[_What]->Set_FadeIO(_From, _To, _Down, _Tm_From_To, _Tm_To_Down);
	}

	inline void			Animate()
	{
		for (	int i = 0;
				i < this->m_Logos.size();
				++i	)
		{
			this->m_Logos[i]->Animate();
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<FancyLogo*>&			g_Vec_Logos()
	{
		return		this->m_Logos;
	}
};
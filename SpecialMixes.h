#pragma once

#include	<vector>

#include	"TheCandy.h"
#include	"_MyIncludes_.h"
#include	"Tools_.h"



class		SpecialMixWrapper
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_SpecialMix
	{
		None						= 0,

		StrippedH_StrippedH			= 1,
		StrippedH_StrippedV			= 2,
		StrippedH_Wrapped			= 3,
		StrippedH_WrappedFuse		= 4,

		BonOBom_CommonCandy			= 5,
		BonOBom_StrippedHorizontal	= 6,
		BonOBom_StrippedVertical	= 7,
		BonOBom_Wrapped				= 8,
		BonOBom_WrappedFuse			= 9,
		BonOBom_JellyFish			= 10,
		BonOBom_StarLight			= 11,
		BonOBom_FireWork			= 12,
		BonOBom_BubbleGum			= 13,
		BonOBom_Popping				= 14,

		FrozenCandy_CommonCandy			= 15,
		FrozenCandy_StrippedHorizontal	= 16,
		FrozenCandy_StrippedVertical	= 17,
		FrozenCandy_Wrapped				= 18,
		FrozenCandy_WrappedFuse			= 19,
		FrozenCandy_JellyFish			= 20,
		FrozenCandy_StarLight			= 21,
		FrozenCandy_FireWork			= 22,
		FrozenCandy_BubbleGum			= 23,
		FrozenCandy_Popping				= 24,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	std::vector<TheCandy*>		m_Pointers;

	int							m_SpecialMixID;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	SpecialMixWrapper(	TheCandy* _Pointer_One, TheCandy* _Pointer_Two, int _SpecialMix_ID	)
	{
		//	Pointer_One points to the first selected candy,
		//	while the Pointer_Two points to the second selected candy.
		//	Applies also for the Direction vector.
		//	This is explicit but so you know.

		//	Pushing the pointers.
		this->m_Pointers.push_back(		_Pointer_One		);
		this->m_Pointers.push_back(		_Pointer_Two		);

		//	IDs.
		this->m_SpecialMixID	= _SpecialMix_ID;
	}

	~SpecialMixWrapper()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Proccess()
	{
		//	Proccess all your inputs.
		//	More description comming soon...

		using		sMx = SpecialMixWrapper::enm_SpecialMix;

		this->m_Pointers[0]->s_Is(		7, true		);
		this->m_Pointers[1]->s_Is(		7, true		);



		switch (	this->m_SpecialMixID	)
		{
		case		sMx::StrippedH_StrippedH:
			//	Hide these candies.
			{
				this->m_Pointers[0]->HideCandy(		true	);
				this->m_Pointers[1]->HideCandy(		true	);
			}
			break;

		case		sMx::StrippedH_StrippedV:
			//	Hide these candies.
			{
				this->m_Pointers[0]->HideCandy(		true	);
				this->m_Pointers[1]->HideCandy(		true	);
			}
			break;

		case		sMx::StrippedH_Wrapped:
			//	Hide these candies.
			{
				this->m_Pointers[0]->HideCandy(		true	);
				this->m_Pointers[1]->HideCandy(		true	);
			}
			break;

		case		sMx::StrippedH_WrappedFuse:
			//	Hide these candies.
			{
				this->m_Pointers[0]->HideCandy(		true	);
				this->m_Pointers[1]->HideCandy(		true	);
			}
			break;

		case		sMx::BonOBom_CommonCandy:
			//	Set some values of common candies.
			{
				this->m_Pointers[1]->s_Is(7, false);
			}
			break;

		case		sMx::BonOBom_StrippedHorizontal:
			//	Set some values of common candies.
			{
				this->m_Pointers[1]->s_Is(7, false);
			}
			break;

		case		sMx::BonOBom_StrippedVertical:
			//	Set some values of common candies.
			{
				this->m_Pointers[1]->s_Is(7, false);
			}
			break;

		case		sMx::FrozenCandy_CommonCandy:
			//	Set some values of common candies.
			{
				this->m_Pointers[1]->s_Is(7, false);
			}
			break;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline TheCandy*			g_Pointers(int _What)	const
	{
		return		this->m_Pointers[_What];
	}
	inline int					g_SpecialMixID()		const
	{
		return		this->m_SpecialMixID;
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
class		_Controller_SpecialMixes
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	std::vector<SpecialMixWrapper*>		m_Wrappers;

//	-------------------------------------------
//				External Controllers
//	-------------------------------------------
private:





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_SpecialMixes()
	{

	}

	~_Controller_SpecialMixes()
	{
		tls::DeleteVector(this->m_Wrappers);
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AddWrapper(		TheCandy* _First_Pointer		, 
										TheCandy* _Second_Pointer		,
										int _SpecialMixID				)
	{
		//	Adding a wrapper.
		this->m_Wrappers.push_back(		new SpecialMixWrapper(_First_Pointer, _Second_Pointer, _SpecialMixID)	);

		//	Binding linkers and proccessing request.
		this->m_Wrappers[this->m_Wrappers.size() - 1]->Proccess();
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<SpecialMixWrapper*>&			g_Wrappers()
	{
		return		this->m_Wrappers;
	}
};
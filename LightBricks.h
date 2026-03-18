#pragma once

#include	<vector>

#include	"thyObject.h"
#include	"Tools_.h"
#include	"_MyIncludes_.h"
#include	"BackGrounds.h"



//	[Deprecated class, or at least not updated]
class		LightLayer : public thyObject
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
	LightLayer(double _xP, double _yP, double _xFct, double _yFct) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->xFct		= _xFct;
		this->yFct		= _yFct;
	}

	~LightLayer()
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
class		_Controller_LightBricks
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:
	std::vector<BackGround*>			m_Lights;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:

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
//			Constructors and Destructor
//	-------------------------------------------
public:
	_Controller_LightBricks(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;



		this->Ld_Everything();
	}

	~_Controller_LightBricks()
	{
		this->Del_Everything();
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				Ld_Everything()
	{
		//	Loading the smooth layer.
		{			
			this->m_Lights.push_back(	new BackGround(	tls::TransformPos_X(0.0, this->_Draw_->g_WorldBounds(1))		,
														tls::TransformPos_Y(0.0, this->_Draw_->g_WorldBounds(2))		,
														3, spr::OnScreen												)	);

			this->m_Lights[0]->s_Color_WithContainer(	tls::Vec4<double>(0xc2, 0x1d, 0x9e, 75.0)	);
			this->m_Lights[0]->ScaleToFit(				this->_Sprites_, this->_Draw_				);
		}
	}
	inline void				Del_Everything()
	{
		tls::DeleteVector(this->m_Lights);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline std::vector<BackGround*>&				g_Vec_LightLayers()
	{
		return		this->m_Lights;
	}
};
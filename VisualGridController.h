#pragma once

#include		"thyObject.h"
#include		"SpriteFactory.h"
#include		"DrawFactory.h"



class		VisualGrid : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_Cnt_ColA
	{
		_Cnt_R_col = 1	,
		_Cnt_G_col		,
		_Cnt_B_col		,
		_Cnt_A_alpha	,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	double				Cnt_R_col = 0, Cnt_G_col = 0, Cnt_B_col = 0, Cnt_A_alpha = 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	VisualGrid(	double _xP, double _yP, double _Width, double _Height	) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->_W = _Width, this->_H = _Height;

		this->Col_s			= 1.15;
		this->Alpha_s		= 0.2;
	}

	~VisualGrid()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void		ColorEffect()
	{
		// - - - R E D - - -
		if (this->Cnt_R_col > this->R_col)
		{
			this->Cnt_R_col -= this->Col_s;
		}
		else
		{
			if (this->Cnt_R_col < this->R_col)
			{
				this->Cnt_R_col += this->Col_s;
			}
			else
			{
				this->Cnt_R_col = this->R_col;
			}
		}

		// - - - G R E E N - - -
		if (this->Cnt_G_col > this->G_col)
		{
			this->Cnt_G_col -= this->Col_s;
		}
		else
		{
			if (this->Cnt_G_col < this->G_col)
			{
				this->Cnt_G_col += this->Col_s;
			}
			else
			{
				this->Cnt_G_col = this->G_col;
			}
		}

		// - - - B L U E - - -
		if (this->Cnt_B_col > this->B_col)
		{
			this->Cnt_B_col -= this->Col_s;
		}
		else
		{
			if (this->Cnt_B_col < this->B_col)
			{
				this->Cnt_B_col += this->Col_s;
			}
			else
			{
				this->Cnt_B_col = this->B_col;
			}
		}

		// - - - A L P H A - - -
		if (this->Cnt_A_alpha > this->A_alpha)
		{
			this->Cnt_A_alpha -= this->Alpha_s;
		}
		else
		{
			if (this->Cnt_A_alpha < this->A_alpha)
			{
				this->Cnt_A_alpha += this->Alpha_s;
			}
			else
			{
				this->Cnt_A_alpha = this->A_alpha;
			}
		}
	}
	inline void		SaveColors()
	{
		this->Cnt_R_col		= this->R_col;
		this->Cnt_G_col		= this->G_col;
		this->Cnt_B_col		= this->B_col;
		this->Cnt_A_alpha	= this->A_alpha;
	}
	inline void		UseColorKind(int _Kind)
	{
		this->Cnt_A_alpha	= 255;
		this->Col_s			= 1.15;

		switch (_Kind)
		{
		case STA_::enm_KindID::_White:		// W h i t e 
			this->Cnt_R_col = 0xff, this->Cnt_G_col = 0xff, this->Cnt_B_col = 0xff;
			this->Col_s = 0.7;
			break;

		case 1:		// R e d 
			this->Cnt_R_col = 0xff, this->Cnt_G_col = 0x00, this->Cnt_B_col = 0x00;
			break;

		case 2:		// O r a n g e 
			this->Cnt_R_col = 0xff, this->Cnt_G_col = 0x72, this->Cnt_B_col = 0x00;
			break;

		case 3:		// Y e l l o w
			this->Cnt_R_col = 0xff, this->Cnt_G_col = 0xf0, this->Cnt_B_col = 0x00;
			break;

		case 4:		// G r e e n
			this->Cnt_R_col = 0x00, this->Cnt_G_col = 0xff, this->Cnt_B_col = 0x06;
			break;

		case 5:		// A q u a m a r i n e
			this->Cnt_R_col = 0x00, this->Cnt_G_col = 0xff, this->Cnt_B_col = 0xa8;
			break;

		case 6:		// C y a n 
			this->Cnt_R_col = 0x0d, this->Cnt_G_col = 0xff, this->Cnt_B_col = 0xf7;
			break;

		case 7:		// B l u e
			this->Cnt_R_col = 0x00, this->Cnt_G_col = 0x1e, this->Cnt_B_col = 0xff;
			break;

		case 8:		// P u r p l e
			this->Cnt_R_col = 0x73, this->Cnt_G_col = 0x20, this->Cnt_B_col = 0x9e;
			this->Col_s = 0.7;
			break;

		case 9:		// P i n k
			this->Cnt_R_col = 0xf0, this->Cnt_G_col = 0x00, this->Cnt_B_col = 0xff;
			break;

		case 10:	// C h o c o l a t e
			this->Cnt_R_col = 0xa0, this->Cnt_G_col = 0x70, this->Cnt_B_col = 0x5f;
			break;
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void		s_Cnt_ColA(int _Which, double _Val)
	{
		switch (_Which)
		{
		case 1:
			this->Cnt_R_col = _Val;
			break;

		case 2:
			this->Cnt_G_col = _Val;
			break;

		case 3:
			this->Cnt_B_col = _Val;
			break;

		case 4:
			this->Cnt_A_alpha = _Val;
			break;
		}
	}
	inline double	g_Cnt_ColA(int _Which)
	{
		switch (_Which)
		{
		case 1:
			return this->Cnt_R_col;

		case 2:
			return this->Cnt_G_col;

		case 3:
			return this->Cnt_B_col;

		case 4:
			return this->Cnt_A_alpha;
		}
	}

	inline int		g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case 1:
			return		(this->xP + (this->_W * 0.5));

		case 2:
			return		(this->yP - (this->_H * 0.5));

		default:
			return		def::enm_Defines::_NOT_FOUND;
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
class		_Controller_BoardVisual
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//						Enums
//	-------------------------------------------
public:
	enum		enm_Draw
	{
		_Board		= 0,
	};




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	VisualGrid***		m_BoardVisual = nullptr;

	int			m_BoardHeight		= 0;
	int			m_BoardWidth		= 0;

	double		xP = 0, yP = 0;
	double		GridHeight = 90.0, GridWidth = 90.0;

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
	_Controller_BoardVisual(	DrawFactory* _Draw_Ptr, SpriteFactory* _Sprite_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
	}

	~_Controller_BoardVisual()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			GenerateBoard(	double xPos, double yPos, int Height, int Width, double OffSetX, double OffSetY	)
	{
		this->xP				= xPos;
		this->yP				= yPos;
		this->m_BoardHeight		= Height;
		this->m_BoardWidth		= Width;



		//	Creating the Board (Visual).
		{
			this->m_BoardVisual = new VisualGrid * * [this->m_BoardHeight];



			for (	int i = 0; 
					i < this->m_BoardHeight; 
					++i	)
			{
				this->m_BoardVisual[i]		= new VisualGrid * [this->m_BoardWidth];



				for (	int j = 0; 
						j < this->m_BoardWidth; 
						++j	)
				{
					this->m_BoardVisual[i][j]		= new VisualGrid(	this->xP + (j * this->GridWidth) + OffSetX		, 
																		this->yP - (i * this->GridHeight) + OffSetY		, 
																		this->GridWidth, this->GridHeight				);
				}
			}
		}
		
		//	Color path.
		{
			for (	int i = 0; 
					i < this->m_BoardHeight; 
					++i	)
			{
				for (	int j = 0; 
						j < this->m_BoardWidth; 
						++j	)
				{
					//	PathID number 1.
					if (	((i + j) % 2) == 1	)
					{
						this->m_BoardVisual[i][j]->s_ColorPrp(1, 0x30);
						this->m_BoardVisual[i][j]->s_ColorPrp(2, 0x9a);
						this->m_BoardVisual[i][j]->s_ColorPrp(3, 0xe5);
						this->m_BoardVisual[i][j]->s_ColorPrp(4, 185);
					}
					else
					{
						this->m_BoardVisual[i][j]->s_ColorPrp(1, 0x30);
						this->m_BoardVisual[i][j]->s_ColorPrp(2, 0x7e);
						this->m_BoardVisual[i][j]->s_ColorPrp(3, 0xb5);
						this->m_BoardVisual[i][j]->s_ColorPrp(4, 185);
					}

					//	Saving colors.
					this->m_BoardVisual[i][j]->SaveColors();
				}
			}
		}
	}

//	-------------------------------------------
//					Draw
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Board.
		if (	What == enm_Draw::_Board		)
		{
			this->_What_Sprite_		= spr::enm_At::Board;
			this->_What_Kind_		= 0;



			for (	int i = 0; i < this->m_BoardHeight; ++i	)
			{
				for (	int j = 0; j < this->m_BoardWidth; ++j	)
				{
					//	Set position to the sprite.
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(	this->m_BoardVisual[i][j]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																													tls::FixPos_Y(	this->m_BoardVisual[i][j]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

					//	Here all your color, scale, and more !
					_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_BoardVisual[i][j]->g_Cnt_ColA(1)	,
																														this->m_BoardVisual[i][j]->g_Cnt_ColA(2)	,
																														this->m_BoardVisual[i][j]->g_Cnt_ColA(3)	,
																														this->m_BoardVisual[i][j]->g_Cnt_ColA(4)	)	);

					//	Draw it.
					this->_Draw_->Draw(		_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)	);
				}
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline VisualGrid***	g_VisualGrid()
	{
		return		this->m_BoardVisual;
	}
};
#pragma once

#include	<Windows.h>
#include	<vector>

#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include	<SFML/Window.hpp>

#include	"Camera.h"
#include	"ShaderFactory.h"



namespace drw
{
	enum MyCamera
	{
		MainCamera		= 0,
		MapCamera		= 1,
		WorldCamera		= 2,
		LevelCamera		= 3,

		_Cameras_Size_		,		
	};

	enum MyCanvas
	{
		MainTexture			= 0,
		FireWorkCanvas		= 1,
		FinalTexture		= 2,



		RenderTexture_Size
	};

	enum CanvasCommand
	{
		InvalidCommand		= 0,

		FadeOff
	};
}

class	DrawFactory
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum	Axis
	{
		x = 1,
		y = 2,
		z = 3
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//				Rendering Variables
//	-------------------------------------------
private:
	std::vector<Camera*>				m_Cameras_;

	sf::RenderWindow*					m_Window_		= nullptr;
	std::vector<sf::RenderTexture*>		m_Textures_;
	std::vector<sf::Sprite*>			m_SpritesRender_;

	sf::Image*							m_Icon;

	sf::View*				m_View = nullptr;

	sf::Sprite				m_RenderSprite;

	sf::Shader				m_LessOpactiy;	
	sf::Shader				m_AlphaBlending;
	sf::Shader				m_Vintage;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	double			m_WindowW = 0.0,	m_WindowH = 0.0;
	double			xGround = 0.0,		yGround = 0.0;

	bool			m_IsFullScreen		= true;
	bool			m_DrawOnTexture		= true;

//	-------------------------------------------
//				Draw variables
//	-------------------------------------------
private:
	int				m_WidthTexture		= 0, m_HeightTexture = 0;

	double			m_CommonFactor		= 1.0;
	double			m_xP_Render			= 0.0,		m_yP_Render = 0.0;

	int				_WhatCamera_					= drw::MyCamera::MainCamera;

	int				_WhatRenderTexture_				= 0;
	int				_WhatCommand_RenderTexture_		= 0;

//	-------------------------------------------
//				Shaders Variables
//	-------------------------------------------
private:
	bool			m_VintageOn = false;

//	-------------------------------------------
//				Animation variables
//	-------------------------------------------
private:
	bool			ChangingOn			= false;
	int				Cnt_ChangeCamera	= 0, Trg_ChangeCamera = 0;
	int				CameraChange_Queue	= 0;
	bool			Activate = false;
	





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	DrawFactory(double _xGround, double _yGround, bool _IsFullScreen)
	{
		this->m_IsFullScreen	= _IsFullScreen;
		this->m_WindowW			= (	(this->m_IsFullScreen) ? sf::VideoMode::getDesktopMode().width : 1800.0		);
		this->m_WindowH			= (	(this->m_IsFullScreen) ? sf::VideoMode::getDesktopMode().height : 1000.0	);
		this->xGround			= _xGround;
		this->yGround			= _yGround;
		this->m_WidthTexture	= this->m_WindowW;
		this->m_HeightTexture	= this->m_WindowH;


		this->Ld_Context();
	}

	~DrawFactory()
	{
		this->Del_All();
	}

//	-------------------------------------------
//			Linker and external functions
//	-------------------------------------------
public:
	inline void				Ld_Context()
	{
		//	Creating the Window (This is of so much importance).
		{
			this->m_Window_ = new sf::RenderWindow(		sf::VideoMode(this->m_WindowW, this->m_WindowH)							, 
														"Star Adventure   v. 0.0.3"												, 
														((this->m_IsFullScreen) ? sf::Style::Fullscreen : sf::Style::Default	)		);

			this->m_Icon	= new sf::Image();
			this->m_Icon->loadFromFile("_Resources_\\Textures\\LogoAndStuff\\cnLDPWRTsnlink.png");
			this->m_Window_->setIcon(	this->m_Icon->getSize().x, this->m_Icon->getSize().y, this->m_Icon->getPixelsPtr()	);
			


			//	/ / / / / / / / / / / / / / / / / / / /

			
			//	this->m_AuxTexture		= new sf::Texture();
			//	this->m_AuxTexture->create(		this->m_WindowW, this->m_WindowH);
			//	this->m_AuxTexture->setSmooth(true);
			//	
			//	this->m_AuxMainTexture	= new sf::Texture();
			//	this->m_AuxMainTexture->create(this->m_WindowW, this->m_WindowH);
			//	this->m_AuxMainTexture->setSmooth(true);
		}

		//	Load the sprite for rendering.
		{
			for (	int i = 0; 
					i < drw::MyCanvas::RenderTexture_Size; 
					++i	)
			{
				this->m_SpritesRender_.push_back(	new sf::Sprite()	);
			}
		}
	
		//	Then goes the render textures (As many as you want).
		{
			//	Linking the texture.
			for (	int i = 0; 
					i < drw::MyCanvas::RenderTexture_Size; 
					++i	)
			{
				//	Main Render Texture.
				this->m_Textures_.push_back(new sf::RenderTexture());
				this->m_Textures_[i]->create(this->m_WindowW, this->m_WindowH);
				this->m_Textures_[i]->setSmooth(true);

				this->m_SpritesRender_[i]->setTexture(	this->m_Textures_[i]->getTexture()	);
			}

			this->m_RenderSprite.setTexture(	this->m_Textures_[1]->getTexture()	);
		}

		//	Shaders to load.
		{
			this->m_LessOpactiy.loadFromFile("_Resources_\\Shaders\\LessOpacity.frag", sf::Shader::Fragment);
			this->m_AlphaBlending.loadFromFile("_Resources_\\Shaders\\AlphaBlending.frag", sf::Shader::Fragment);
			this->m_Vintage.loadFromFile("_Resources_\\Shaders\\Vintage.frag", sf::Shader::Fragment);
		}

		//	Finally, the view.
		{
			this->m_View = new sf::View();
		}

		//	Cameras!!!
		{
			for (	int i = 0; 
					i < drw::MyCamera::_Cameras_Size_;
					++i	)
			{
				this->m_Cameras_.push_back(	nullptr	);
			}
		}
	}
	inline void				Del_All()
	{
		//	Deleting the window.
		{
			if (this->m_Window_ != nullptr)
			{
				delete		this->m_Window_;
			}
		}

		//	Deleting all the textures.
		{
			while (!this->m_Textures_.empty())
			{
				delete		this->m_Textures_[0];
				this->m_Textures_.erase(this->m_Textures_.begin() + 0);
			}
		}

		//	Deleting the sprite render.
		{
			tls::DeleteVector(this->m_SpritesRender_);
		}

		//	Deleting the view
		{
			tls::Delete(this->m_View);
		}

		tls::Delete(this->m_Icon);
	}

//	-------------------------------------------
//				Actual functions
//	-------------------------------------------
public:
	//	Run some code here like timers, events, etc...
	inline void			LogicDis()
	{
		//	About camera changing.
		//	Movements, scaling, etc.
		{
			if (this->ChangingOn)
			{
				if (this->Cnt_ChangeCamera < this->Trg_ChangeCamera)
				{
					++this->Cnt_ChangeCamera;
				}
				else
				{
					this->Cnt_ChangeCamera	= 0;
					this->_WhatCamera_		= this->CameraChange_Queue;
					this->ChangingOn		= false;
				}	
			}
		}



		//	Firework rocket.
		//	Custom effect for the firework canvas.
		{
			
			this->m_Textures_[drw::MyCanvas::FireWorkCanvas]->draw(this->m_RenderSprite, &this->m_LessOpactiy);
		}
	}

	//	Draw directly to the window.
	inline void			DrawWindow(	sf::Sprite* _YourSprite	)
	{
		//	Actual drawing whether on texture or window.
		this->m_Window_->draw(*_YourSprite);
	}

	//	Basic draw (Just sprites).
	inline void			Draw(	sf::Sprite* _YourSprite		, 
								bool _UseCamera = true		, 
								int _WhichLayer = 0			)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{
			_YourSprite->setPosition(	_YourSprite->getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1),
										_YourSprite->getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(*_YourSprite);
	}

	//	Blending draw (Blend colors).
	inline void			DrawBlend(	sf::Sprite* _YourSprite		, 
									bool _UseBlending = true	,
									bool _UseCamera = true		, 
									int _WhichLayer = 0			)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			_YourSprite->setPosition(	_YourSprite->getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1)	,
										_YourSprite->getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(*_YourSprite, sf::BlendAdd);
	}

	//	Blending draw (Blend colors).
	inline void			DrawCustomBlend(	sf::Sprite* _YourSprite		, 
											bool _UseBlending = true	,
											bool _UseCamera = true		, 
											int _WhichLayer = 0			)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			_YourSprite->setPosition(	_YourSprite->getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1)	,
										_YourSprite->getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(*_YourSprite, sf::BlendAlpha);
	}

	//	Text draw (For Text purposes).
	inline void			DrawText(	sf::Text* _YourText			,
									bool _UseCamera = true		, 
									int _WhichLayer = 0			)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			_YourText->setPosition(		_YourText->getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1)	,
										_YourText->getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(*_YourText);
	}

	//	Vertex Array draw.
	inline void			DrawVertexArray(	sf::VertexArray _VertexArray					,
											sf::PrimitiveType _PrimitiveType = sf::Lines	,
											bool _UseCamera = true							, 
											int _WhichLayer = 0								)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			for (	int i = 0; 
					i < _VertexArray.getVertexCount(); 
					++i	)
			{
				_VertexArray[i].position.x	= _VertexArray[i].position.x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1);
				_VertexArray[i].position.y	= _VertexArray[i].position.y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2);
			}
		}

		//	Setting the type of primitive
		_VertexArray.setPrimitiveType(		_PrimitiveType		);

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(	_VertexArray	);
	}

	//	Shapes draw.
	inline void			DrawRectangleShape(	sf::RectangleShape _RectangleShape		,
											bool _UseCamera = true					, 
											int _WhichLayer = 0						)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			_RectangleShape.setPosition(	_RectangleShape.getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1)	,
											_RectangleShape.getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(	_RectangleShape		);
	}

	//	Normal draw (With shaders).
	inline void			DrawShader(	sf::Sprite* _YourSprite		, 
									sf::Shader& _YourShader		,
									bool _UseCamera = true		, 
									int _WhichLayer = 0			)
	{
		//	If the draw call uses camera.
		if (_UseCamera)
		{ 
			_YourSprite->setPosition(	_YourSprite->getPosition().x - this->m_Cameras_[this->_WhatCamera_]->g_Position(1)	,
										_YourSprite->getPosition().y + this->m_Cameras_[this->_WhatCamera_]->g_Position(2)	);
		}

		//	Actual drawing whether on texture or window.
		this->m_Textures_[_WhichLayer]->draw(*_YourSprite, &_YourShader);
	}

	//	This function render the render textures ready to go.
	inline void			RenderTextures()
	{
		//	Render the textures so the content can be drawn.
		{
			for (	int i = 0; 
					i < drw::MyCanvas::RenderTexture_Size; 
					++i	)
			{
				this->m_Textures_[i]->display();
			}
		}
	}

	//	Display function. This function displays all the textures.
	inline void			RenderWindow()
	{
		int		_At_ = drw::MyCanvas::RenderTexture_Size - 1;



		//	Final Texture part.
		{
			for (	int i = 0;
					i < drw::MyCanvas::RenderTexture_Size - 1;
					++i	)
			{
				//	Draw the sprite.
				//	Apply some shaders as well.
				{
					if (	i == drw::MyCanvas::FireWorkCanvas	)
					{			
						this->m_AlphaBlending.setUniform("ForeignTexture", this->m_Textures_[0]->getTexture());
						this->m_Textures_[_At_]->draw(*this->m_SpritesRender_[i], &this->m_AlphaBlending);
					}   
					else
					{
						this->m_Textures_[_At_]->draw(*this->m_SpritesRender_[i]);
					}
				}
			}
		}	

		//	Render on Window.
		{
			//	Setting the positional values.
			this->m_SpritesRender_[_At_]->setPosition(	this->m_xP_Render, this->m_yP_Render	);

			//	Shrinking model.
			this->m_SpritesRender_[_At_]->setScale(	this->m_CommonFactor, this->m_CommonFactor	);

			//	Draw.
			this->m_Window_->draw(*this->m_SpritesRender_[_At_], &this->m_Vintage);
		}
	}

	//	Display all the content to the window.
	inline void			Display()
	{
		//	Finally, display.
		this->m_Window_->display();
	}

//	-------------------------------------------
//				Other functions
//	-------------------------------------------
public:
	//	Cameras and linkers.
	inline void			LinkCamera(Camera* _Camera_Ptr, int _Where = 0)
	{
		this->m_Cameras_[_Where] = _Camera_Ptr;
	}
	inline void			UseCamera(int _What, double _OffSet_Time = 0.0)
	{
		this->ChangingOn			= true;
		this->CameraChange_Queue	= _What;

		this->Cnt_ChangeCamera		= 0;
		this->Trg_ChangeCamera		= GAME_LOOP_VALUE * _OffSet_Time;
	}

	//	About view mechanics.
	inline void			UseView(int _WhatTexture = 0, int _WhatCamera = 0)
	{
		//	Set the size of the view (The whole window).
		this->m_View->setSize(this->m_WindowW, this->m_WindowH);

		//	Then center it at the middle.
		this->m_View->setCenter(	tls::FixPos_X(this->m_Cameras_[_WhatCamera]->g_Center(1), xGround)		,
									tls::FixPos_Y(this->m_Cameras_[_WhatCamera]->g_Center(2), yGround)		);

		//	Set zoom if there were any zoom animation.
		this->m_View->zoom(	this->m_Cameras_[_WhatCamera]->g_ZoomFactor()	);

		//	Apply to the current render.
		if (this->m_DrawOnTexture)
		{
			this->m_Textures_[_WhatTexture]->setView(	*this->m_View	);
		}
		else
		{
			this->m_Window_->setView(	*this->m_View	);
		}
	}
	inline void			ResetView(int _WhatTexture = 0)
	{
		//	Resize the actual view.
		this->m_View->setSize(	this->m_WindowW, this->m_WindowH	);

		//	Recenter the view as new.
		this->m_View->setCenter(	this->m_WindowW / 2.0, this->m_WindowH / 2.0	);

		//	Apply the view.
		this->m_Textures_[_WhatTexture]->setView(*this->m_View);
	}

	//	When the window is resized.
	inline void			ResizeEvent(sf::Event*	_Event)
	{
		//	The window itself is being resized just to
		//	stop the window to stretch textures and images.
		{
			sf::FloatRect		VisibleArea(	0, 0, _Event->size.width, _Event->size.height	);
			this->m_Window_->setView(	sf::View(VisibleArea)	);
		}

		//	Calculating the factors.
		{
			//	These other factors are draw purposes (not meant to be shared).
			{
				this->m_CommonFactor	= _Event->size.width / 1800.0;
                this->m_yP_Render		= (_Event->size.height - (this->m_CommonFactor * 1000.0)) / 2.0;
				this->m_xP_Render		= 0.0;

                if (	(1000.0 * this->m_CommonFactor) > _Event->size.height	)
                {
					this->m_CommonFactor = _Event->size.height / 1000.0;

					this->m_xP_Render = (_Event->size.width - (this->m_CommonFactor * 1800.0)) / 2.0;
					this->m_yP_Render = 0;
                }
			}
		}
	}

	//	The original window size is 1800x1000, and if the window
	//	is resized or idk, then this function will return the current scaling
	//	to scale all the objects and stuff.
	inline double		GetScale(	int _What_Scale	)
	{
		switch (_What_Scale)
		{
		case DrawFactory::Axis::x:
			return		(this->m_WindowW / 1800.0);

		case DrawFactory::Axis::y:
			return		(this->m_WindowH / 1000.0);

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}

	//	Get the camera limits. This is for the window limits.
	inline double		GetCameraLimits(	int What	)
	{
		switch (	What	)
		{
		case	def::enm_CameraLimits::Cieling:
			return		(this->yGround);

		case	def::enm_CameraLimits::Floor:
			return		(0.0);

		case	def::enm_CameraLimits::LeftBorder:	
			return		(-this->xGround);

		case	def::enm_CameraLimits::RightBorder:
			return		(this->xGround);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void					SetVintageFilterValues(		int What, double Val	)
	{
		switch (	What	)
		{
		case	1:
			//	Use Vintage Filter.
			if (	Val != 0.0	)
			{
				this->m_VintageOn	= true;
			}
			else
			{
				this->m_VintageOn	= false;
			}

			//	Set Uniform.
			this->m_Vintage.setUniform("Time", static_cast<float>(Val));
			break;
		}
	}

	inline Camera*				g_Camera(int _WhatCamera)
	{
		return			this->m_Cameras_[_WhatCamera];
	}
	inline Camera*				g_CurrentCamera()
	{
		return			this->m_Cameras_[this->_WhatCamera_];
	}
	inline sf::RenderWindow*	g_Window()
	{
		return			this->m_Window_;
	}

	inline double				g_WindowBounds(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->m_WindowW;

		case 2:
			return		this->m_WindowH;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline double				g_WorldBounds(int _What)
	{
		switch (_What)
		{
		case 1:
			return		this->xGround;

		case 2:
			return		this->yGround;

		default:
			return		def::enm_Defines::_NOT_FOUND;
		}
	}
	inline double				Transform(int _What, double _Mouse_Pos)
	{
		switch (_What)
		{
		case 1:		//	Transforming xPos
			_Mouse_Pos = _Mouse_Pos - this->m_xP_Render;
			_Mouse_Pos = _Mouse_Pos / this->m_CommonFactor;
			return		_Mouse_Pos;

		case 2:		//	Transforming yPos
			_Mouse_Pos = _Mouse_Pos - this->m_yP_Render;
			_Mouse_Pos = _Mouse_Pos / this->m_CommonFactor;
			return		_Mouse_Pos;
		}
	}
};
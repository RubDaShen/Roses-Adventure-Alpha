#pragma once
#include	<iostream>
#include	<array>
#include	<string>

#include	<SFML/Graphics.hpp>
#include	<SFML/Window.hpp>

#include	"Tools_.h"



namespace shd
{
	enum MyShaders
	{
		SwimmingFish	= 0	,
		Brightness		= 1	,
		Vintage			= 2	,
		LessOpacity		= 3	,
		RadialZoom		= 4	,
	};
}

class	ShaderFactory
{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	sf::Shader		_SwimmingFish_;
	sf::Shader		_Brightness_;
	sf::Shader		_Vintage_;
	sf::Shader		_LessOpactity_;
	sf::Shader		_RadialZoom_;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	ShaderFactory()
	{
		this->Ld_Shaders();
	}

	~ShaderFactory()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			Ld_Shaders()
	{
		const std::string		_R_Shd_ = "_Resources_\\Shaders\\";



		//	Loading the fish swimming shader.
		{
			this->_SwimmingFish_.loadFromFile(_R_Shd_ + "SwimmingFish.frag", sf::Shader::Fragment);
		}

		//	Loading the brightness shader.
		{
			this->_Brightness_.loadFromFile(_R_Shd_ + "Brightness.frag", sf::Shader::Fragment);
		}

		//	Loading the vintage effect shader.
		{
			this->_Vintage_.loadFromFile(_R_Shd_ + "Vintage.frag", sf::Shader::Fragment);
		}

		//	Loading the opacity shader.
		{
			this->_LessOpactity_.loadFromFile(_R_Shd_ + "LessOpacity.frag", sf::Shader::Fragment);
		}

		//	Loading the opacity shader.
		{
			this->_RadialZoom_.loadFromFile(_R_Shd_ + "RadialZoom.frag", sf::Shader::Fragment);
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void				s_Uniform_SwimmingFish(float _Time, tls::Vec4<float> _TextureRect)
	{
		this->_SwimmingFish_.setUniform("_Time_", _Time);
		this->_SwimmingFish_.setUniform("Boundaries", sf::Glsl::Vec4(	_TextureRect.First	,
																		_TextureRect.Second	,	
																		_TextureRect.Third	, 
																		_TextureRect.Fourth	)	);
	}
	inline void				s_Uniform_Brightness(float Brightness, float Alpha = 1.0f)
	{
		this->_Brightness_.setUniform("_Brightness_", Brightness);
		this->_Brightness_.setUniform("_Alpha_", Alpha);
	}
	inline void				s_Uniform_RadialZoom(float _Time, tls::Vec4<float> _TextureRect)
	{
		this->_RadialZoom_.setUniform("_Time_", _Time);
		this->_RadialZoom_.setUniform("Boundaries", sf::Glsl::Vec4(		_TextureRect.First	,
																		_TextureRect.Second	,
																		_TextureRect.Third	,
																		_TextureRect.Fourth	)	);
	}

	inline sf::Shader&		g_Shader(int _What)
	{
		switch (_What)
		{
		case	shd::MyShaders::SwimmingFish:
			return		this->_SwimmingFish_;

		case	shd::MyShaders::Brightness:
			return		this->_Brightness_;

		case	shd::MyShaders::Vintage:
			return		this->_Vintage_;

		case	shd::MyShaders::LessOpacity:
			return		this->_LessOpactity_;

		case	shd::MyShaders::RadialZoom:
			return		this->_RadialZoom_;

		default:
			throw std::runtime_error("Couldn't find the requested shaders. Returning...");
		}
	}
};
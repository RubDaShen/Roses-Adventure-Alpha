#pragma once

#include	<iostream>
#include	<string>
#include	<vector>
#include	<Windows.h>

#include	"thyObject.h"
#include	"_MyIncludes_.h"




//	Relying on:
//		fnt::enm_FontType::~	as default values

//	->Tools (tls) and utilities.
namespace tls
{
	//	-----------------------
	//	..::### Enums ###::..
	//	-----------------------
	enum _Quadrant_
	{
		FirstQuadrant = 1, SecondQuadrant, ThirdQuadrant, FourthQuadrant
	};
	enum Colors
	{
		_White,
		_Red,
		_Yellow,
		_Green,
		_Cyan,
		_Blue,
		_Magenta,
		_Gray,
		_DarkGray,
		_Black,
	};





	//	-------------------------
	//	..::### Functions ###::..
	//	-------------------------

	//	Set the console's cursor in a specified position.
	inline void SetCursor(int xP, int yP)
	{
		System::Console::SetCursorPosition(xP, yP);
	}

	//	Clears the line. Tha 's  ll abo   t    f    ...
	inline void ClearLine()
	{
		std::cout << "                                                                    ";
	}

	//	Hide console's cursor.
	inline void HideCursor(bool _Hide)
	{
		System::Console::CursorVisible = (!_Hide);
	}

	//	Set Console Color in a easy way!
	//	_Which: Just use tls::Colors::~ to use one.
	inline void SetColor(const int _Which)
	{
		switch (_Which)
		{
		case Colors::_White:
			System::Console::ForegroundColor = System::ConsoleColor::White;
			break;

		case Colors::_Red:
			System::Console::ForegroundColor = System::ConsoleColor::Red;
			break;

		case Colors::_Yellow:
			System::Console::ForegroundColor = System::ConsoleColor::Yellow;
			break;

		case Colors::_Green:
			System::Console::ForegroundColor = System::ConsoleColor::Green;
			break;

		case Colors::_Cyan:
			System::Console::ForegroundColor = System::ConsoleColor::Cyan;
			break;

		case Colors::_Blue:
			System::Console::ForegroundColor = System::ConsoleColor::Blue;
			break;

		case Colors::_Magenta:
			System::Console::ForegroundColor = System::ConsoleColor::Magenta;
			break;

		case Colors::_Gray:
			System::Console::ForegroundColor = System::ConsoleColor::Gray;
			break;

		case Colors::_DarkGray:
			System::Console::ForegroundColor = System::ConsoleColor::DarkGray;
			break;

		case Colors::_Black:
			System::Console::ForegroundColor = System::ConsoleColor::Black;
			break;
		}
	}

	//	Set Console 'BackGround' Color~
	//	_Which: Just use tls::Colors::~ to use one.
	inline void SetBackColor(const int _Which)
	{
		switch (_Which)
		{
		case Colors::_White:
			System::Console::BackgroundColor = System::ConsoleColor::White;
			break;

		case Colors::_Red:
			System::Console::BackgroundColor = System::ConsoleColor::Red;
			break;

		case Colors::_Yellow:
			System::Console::BackgroundColor = System::ConsoleColor::Yellow;
			break;

		case Colors::_Green:
			System::Console::BackgroundColor = System::ConsoleColor::Green;
			break;

		case Colors::_Cyan:
			System::Console::BackgroundColor = System::ConsoleColor::Cyan;
			break;

		case Colors::_Blue:
			System::Console::BackgroundColor = System::ConsoleColor::Blue;
			break;

		case Colors::_Magenta:
			System::Console::BackgroundColor = System::ConsoleColor::Magenta;
			break;

		case Colors::_Gray:
			System::Console::BackgroundColor = System::ConsoleColor::Gray;
			break;

		case Colors::_DarkGray:
			System::Console::BackgroundColor = System::ConsoleColor::DarkGray;
			break;

		case Colors::_Black:
			System::Console::BackgroundColor = System::ConsoleColor::Black;
			break;
		}
	}

	//	Set console to white by default.
	inline void ResetColor()
	{
		System::Console::ForegroundColor = System::ConsoleColor::White;
	}

	//	Center the object to the center of the screen.
	//	Returns: If ObjSz = width, then will return width position centered.
	//	         If ObjSz = height, then will return height position centered.
	inline double		CenterObj(double ScrSz, double ObjSz)
	{
		return (ScrSz - ObjSz) / 2.0;
	}

	//	_Where: 1 -> Left Up, 2 -> Right Up, 3 -> Left Down, 4 -> Right Down.
	//	This function is for ScrnObj oriented only!
	inline double		CenterObjTo(int _Where, double ScrSz, double ObjSz, double _OffSet)
	{
		switch (_Where)
		{
		case 1:
			return ScrSz - ObjSz + _OffSet;

		case 2:
			return ScrSz - ObjSz + _OffSet;

		case 3:
			return ScrSz - ObjSz + _OffSet;

		case 4:
			return ScrSz - ObjSz + _OffSet;
		}
	}

	//	Print a message in the System::Console.
	inline void			MessageConsole(const std::string _YourMessage, bool _EndLine)
	{
		std::cout << _YourMessage << ((_EndLine) ? "\n" : "");
	}

	//	Do the pythagoras theorem : Asks for two variables.
	inline double		DoPhytagoras(const double _FirstSide, const double _SecondSide)
	{
		return sqrt(pow(_FirstSide, 2) + pow(_SecondSide, 2));
	}

	//	Check Collision.
	inline bool			CollidesWith(	const double x, const double y, const double w, const double h,
										const double a, const double b, const double c, const double d)
	{
		if (	(	(	(	(x <= a)		&&	(a <= (x + w))			)	&&	(	((y - h) <= b)			&& (b <= y)				)	)		|| 
					(	(	(x <= (a + c))	&&	((a + c) <= (x + w))	)	&&	(	((y - h) <= b)			&& (b <= y)				)	)		||
					(	(	(x <= a)		&&	(a <= (x + w))			)	&&	(	((y - h) <= (b - d))	&& ((b - d) <= y)		)	)		||
					(	(	(x <= (a + c))	&&	((a + c) <= (x + w))	)	&&	(	((y - h) <= (b - d))	&& ((b - d) <= y)		)	)		)	||
				(	(	(	(a <= x)		&&	(x <= (a + c))			)	&&	(	((b - d) <= y)			&& (y <= b)				)	)		||
					(	(	(a <= (x + w))	&&	((x + w) <= (a + c))	)	&&	(	((b - d) <= y)			&& (y <= b)				)	)		||
					(	(	(a <= x)		&&	(x <= (a + c))			)	&&	(	((b - d) <= (y - h))	&& ((y - h) <= b)		)	)		||
					(	(	(a <= (x + w))	&&	((x + w) <= (a + c))	)	&&	(	((b - d) <= (y - h))	&& ((y - h) <= b)		)	)		)	)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//	Fix or normalize the position to convert the current value in
	//	a window screen position.
	inline int		FixPos_X(double _Pos, double _xGround)
	{
		return	(_xGround + _Pos);
	}
	inline int		FixPos_Y(double _Pos, double _yGround)
	{
		return	(_yGround - _Pos);
	}

	//	Tranform coordinates of the window to world coordinates.
	inline double		TransformPos_X(double _Pos, double _xGround)
	{
		return (_Pos - _xGround);
	}
	inline double		TransformPos_Y(double _Pos, double _yGround)
	{
		return (_yGround - _Pos);
	}

	//	Scale to anything.
	//	I have this value (CurrentMeasure) and I want it to fit up to (ScaleTo)
	//	i.e. 100 (CurrentMeasure) scale to fit in 200 (ScaleTo).
	inline double		Scale(double CurrentMeasure, double ScaleTo)
	{
		return (ScaleTo / CurrentMeasure);
	}

	//	Convert all the characters of a string to uppercase or lowercase.
	//	1: UpperCase, 2: LowerCase
	inline void ToUppLow(std::string& _YourString, int _Opt)
	{
		for (int i = 0; i < _YourString.size(); i++)
		{
			if ((_YourString.at(i) >= 97) && (_YourString.at(i) <= 122) && (_Opt == 1))
				_YourString.at(i) = _YourString.at(i) - 32;
			else
				if ((_YourString.at(i) >= 65) && (_YourString.at(i) <= 90) && (_Opt == 2))
					_YourString.at(i) = _YourString.at(i) + 32;
		}
	}

	//	Sum all the elements from a string.
	inline int SumStrElms(const std::string& _YourString)
	{
		int _Aux = 0;

		for (int i = 0; i < _YourString.size(); i++)
			_Aux += static_cast<int>(_YourString.at(i));

		return _Aux;
	}

	//	Replace certain character of a string.
	inline void ReplaceStrElms(std::string& _YourString, const char CharacterToReplace, const char CharacterToUse)
	{
		for (int i = 0; i < _YourString.size(); i++)
		{
			if (_YourString[i] == CharacterToReplace)
				_YourString[i] = CharacterToUse;
		}
	}

	//	Convert a string to a positive int.
	//	Warning: Numbers will only be used, any other character will be skipped.
	inline int StrToInt(const std::string& _YourString, bool Reverse = false)
	{
		std::string		AuxStr = _YourString;

		int				StrSz = _YourString.size();
		int				Num = 0;

		bool			AllNumbers = true;



		for (int i = 0; i < AuxStr.size(); i++)
		{
			if ((AuxStr[i] < 48) || (AuxStr[i] > 57))
			{
				AllNumbers = false;
			}
		}


		if (!AllNumbers)
		{
			AuxStr.clear();

			for (int i = 0; i < StrSz; i++)
			{
				if ((_YourString[i] >= 48) && (_YourString[i] <= 57))
					AuxStr.push_back(_YourString[i]);
			}

			StrSz = AuxStr.size();
		}

		if (Reverse)
		{
			int			AuxNum = 0;
			int			StrSz = AuxStr.size();

			for (int i = StrSz - 1; i >= 0; i--)
			{
				Num += (AuxStr[i] - 48) * pow(10, StrSz - AuxNum - 1);
				AuxNum++;
			}
		}
		else
		{
			for (int i = 0; i < AuxStr.size(); i++)
			{
				Num += (AuxStr[i] - 48) * pow(10, StrSz - i - 1);
			}
		}

		return Num;
	}

	//	Convert a string to a positive double.
	//	Warning: Numbers and the period, any other character will be skipped.
	inline double StrToDouble(const std::string& _YourString)
	{
		std::string		AuxStr;

		bool			PeriodFound		= false;
		bool			IsNegative		= false;

		int				IntPart = 0, DecimalPart = 0;
		int				Cnt_IntPart = 0, Cnt_DecPart = 0;

		//	Find if the string contains a negative sign.
		//	Just will take count of the first character.
		//	Anything else will be ignored.
		{
			if (!_YourString.empty())
			{
				IsNegative = (_YourString[0] == '-');
			}
		}
		
		//	Normalize string. (A single period and numbers)
		{
			for (int i = 0; i < _YourString.size(); ++i)
			{
				if ((_YourString[i] == 46))
				{
					if (!PeriodFound)
					{
						PeriodFound = true;
						AuxStr.push_back(_YourString[i]);
					}
					else
						break;
				}

				if (((_YourString[i] >= 48) && (_YourString[i] <= 57)))
				{
					AuxStr.push_back(_YourString[i]);
				}
			}

			if (AuxStr == ".")
				return 0;
		}

		//	AuxStr to Double.
		{
			//	Int part.
			for (int i = 0; i < AuxStr.size(); ++i)
			{
				if (AuxStr[i] != 46)
				{
					IntPart = (AuxStr[i] - 48) + (10 * IntPart);
					++Cnt_IntPart;
				}
				else
					break;
			}

			//	Decimal part.
			for (int i = Cnt_IntPart + 1; i < AuxStr.size(); ++i)
			{
				DecimalPart = (AuxStr[i] - 48) + (10 * DecimalPart);
				++Cnt_DecPart;
			}
		}

		//	Joining parts.
		{
			return ( (IntPart + (DecimalPart / (pow(10, Cnt_DecPart)))) * (	(IsNegative) ? -1.0 : 1.0)	);
		}

	}


	//	Invert the elements of a std::string.
	//	Str = {'r', 'u', 'b'} -> {'b', 'u', 'r'}
	inline void InvertStr(std::string& _YourString)
	{
		int			Size = _YourString.size();
		char		Aux = NULL;



		for (	int i = 0; 
				i < (Size / 2); 
				++i	)
		{
			Aux								= _YourString.at(i);
			_YourString.at(i)				= _YourString.at(Size - 1 - i);
			_YourString.at(Size - 1 - i)	= Aux;
		}
	}

	//	Convert a integer into a std::string.
	inline std::string IntToStr(int _YourInt)
	{
		if (_YourInt == 0)
		{
			return "0";
		}
		else
		{
			std::string		_Str;
			bool			IsNegative = (_YourInt < 0);

			

			//	Fixes if it is negative.
			if (IsNegative)
			{
				_YourInt *= -1;
			}

			//	To string!
			while (_YourInt)
			{
				_Str.push_back((_YourInt % 10) + 48);

				_YourInt = _YourInt / 10;
			}

			//	Invert string.
			tls::InvertStr(_Str);

			//	Finally, if it was negative.
			if (IsNegative)
			{
				_Str.insert(_Str.begin() + 0, '-');
			}



			return _Str;
		}	
	}

	//	Collision detection for a single point to a circle.
	inline bool IsPointInCircle(double a, double b, double x, double y, double r)
	{
		return (	(	((a - x) * (a - x)) + ((b - y) * (b - y))	) < (r * r)	);
	}

	//	Collision detection for a whole rectangle to a circle.
	inline bool RectangleCollidesWithCircle(double a, double b, double c, double d, double x, double y, double r)
	{
		return (	IsPointInCircle(a, b, x, y, r)			||
					IsPointInCircle(a + c, b, x, y, r)		||
					IsPointInCircle(a, b - d, x, y, r)		||
					IsPointInCircle(a + c, b - d, x, y, r)	);
	}

	//	Get a random number.
	//	This function is fixed meaning that if you pass a range
	//	from 1 to 3, you'll get a number from that interval.
	//	Not 1 to 2 like other random functions.
	inline int Random(int _From, int _To)
	{
		if (_From >= _To)
		{
			return _From;
		}
		else
		{
			return ((std::rand() % (_To - _From + 1)) + _From);
		}	
	}

	//	If your input is 50 then you have a 50% chance of getting true.
	//	If your input is 33.3333... then you have a 1/3 of getting true.
	//	_Precision is the decimals that will be taken as part of the prob.
	inline bool Probability(double _Porcentaje, double _Precision = 1)
	{
		return (	((tls::Random(0, 100 * std::pow(10, _Precision)) / std::pow(10, _Precision)) < _Porcentaje	) ? true : false);
	}

	//	Convert a number from 'degrees' to 'radians'.
	inline double DegToRad(const double _Degrees)
	{
		return (_Degrees * (_Pi_ / 180.0));
	}

	//	Convert a number from 'radians' to 'degrees'.
	inline double RadToDeg(const double _Rad)
	{
		return (_Rad * (180.0 / _Pi_));
	}

	//	Round any value to make it minus or positive one.
	inline double UnityRound(const double _Val)
	{
		if (_Val < 0.0)
		{
			return -1.0;
		}

		if (_Val > 0.000000001)
		{
			return 1.0;
		}

		return 0.0;
	}

	//	Convert your floating value into a string.
	inline std::string DoubleToStr(double _YourFloatingValue, double _Precision)
	{
		if (_YourFloatingValue == 0)
		{
			return "0.0";
		}
		else
		{
			std::string		_Str_Int;
			std::string		_Str_Floating;
			std::string		_Str_Final;
			bool			IsNegative = (_YourFloatingValue < 0.0);		



			//	Fixes if it is negative.
			{
				if (IsNegative)
				{
					_YourFloatingValue *= -1;
				}
			}

			//	To string!
			{
				int				_Int_Part			= static_cast<int>(_YourFloatingValue);
				double			_Floating_Part		= _YourFloatingValue - _Int_Part;



				//	Int part.
				if (_Int_Part == 0)
				{
					_Str_Int.push_back('0');
				}
				while (_Int_Part)
				{
					_Str_Int.push_back((_Int_Part % 10) + 48);

					_Int_Part = _Int_Part / 10;
				}
				

				//	Floating part.
				_Int_Part = (_Floating_Part * std::pow(10, _Precision));
				while (_Int_Part)
				{
					_Str_Floating.push_back((_Int_Part % 10) + 48);

					_Int_Part = _Int_Part / 10;
				}

				//	Concadenating strings.
				{
					tls::InvertStr(_Str_Int);
					
					//	Fixing floating extra zeros.
					{				
						_Int_Part = (_Floating_Part * std::pow(10, _Precision));


						if (_Int_Part == 0)
						{
							for (	int i = 0; 
									i < _Precision;
									++i	)
							{
								_Str_Floating.push_back('0');
							}
							
						}
						else
						{
							while (_Int_Part < std::pow(10, _Precision - 1))
							{
								_Str_Floating.push_back('0');
								_Int_Part = _Int_Part * 10;
							}
						}


						tls::InvertStr(_Str_Floating);
					}


				
					_Str_Final = _Str_Int + "." + _Str_Floating;
				}
			}


			//	Finally, if it was negative.
			{
				if (IsNegative)
				{
					_Str_Final.insert(_Str_Final.begin() + 0, '-');
				}
			}



			return _Str_Final;
		}
	}

	//	Find an angle (rad or deg) using of two points.
	inline double FindAngle(double xP, double yP, double _xP, double _yP, bool _UseRad)
	{
		double		_Desire_Angle_ = 0.0;



		//	90 and 270 deg. Both are divided by 0 when finding them.
		{
			if (	((_xP - xP) == 0.0) && (yP < _yP)	)
			{
				_Desire_Angle_ = 90.0;	

				return ((_UseRad) ? tls::DegToRad(_Desire_Angle_) : _Desire_Angle_);
			}
			else
			{
				if (	((_xP - xP) == 0.0) && (yP > _yP)	)
				{
					_Desire_Angle_ = 270.0;

					return ((_UseRad) ? tls::DegToRad(_Desire_Angle_) : _Desire_Angle_);
				}
				else
				{
					if (	((_xP - xP) == 0.0) && ((yP - _yP) == 0.0)	)
					{
						_Desire_Angle_ = 0.0;

						return ((_UseRad) ? tls::DegToRad(_Desire_Angle_) : _Desire_Angle_);
					}
				}
			}



			
		}

		//	For any other angle.
		{
			double		_Angle_ = tls::RadToDeg(	std::atan( (_yP - yP) / (_xP - xP)) );
			_Desire_Angle_		= _Angle_;



			if (	(_xP < xP) 	)
			{
				_Desire_Angle_ = (_Angle_ + 180.0);
			}
			else
			{
				if (	(_xP > xP) && (_yP < yP)	)
				{
					_Desire_Angle_ = (360.0 + _Angle_);
				}		
			}



			return ((_UseRad) ? tls::DegToRad(_Desire_Angle_) : _Desire_Angle_);
		}	
	}

	//	For example: angle = 725 -- tls -- angle = 5.
	inline double FixAngle(double _Angle_, bool _IsDegrees)
	{
		//	Negative values not implemented yet.

		if (_IsDegrees)
		{
			while ((_Angle_ - 360.0) > 0.0)
			{
				_Angle_ = _Angle_ - 360.0;
			}

			return _Angle_;
		}
		else
		{
			while ((_Angle_ - _Pi_) > 0.0)
			{
				_Angle_ = _Angle_ - _Pi_;
			}

			return _Angle_;
		}
	}

	//	Find the cuadrant of a given angle.
	//	OffSet is actually like a rotation to seek for a quadrant.
	//	Positive values mean a counterclockwise rotation.
	//	Works for degrees values by the time.
	inline int FindQuadrant(double _Angle_)
	{
		_Angle_ = tls::FixAngle(_Angle_, true);
		if (_Angle_ < 0.0)
		{
			_Angle_ = 360.0 + _Angle_;
		}



		if (	(0.0 <= _Angle_) && (_Angle_ <= 90.0)	)
		{
			return tls::_Quadrant_::FirstQuadrant;
		}

		if (	(90.0 < _Angle_) && (_Angle_ <= 180.0 )	)
		{
			return tls::_Quadrant_::SecondQuadrant;
		}

		if (	(180.0 < _Angle_) && (_Angle_ <= 270.0)	)
		{
			return tls::_Quadrant_::ThirdQuadrant;
		}

		if (	(270.0 < _Angle_) && (_Angle_ <= 360.0)	)
		{
			return tls::_Quadrant_::FourthQuadrant;
		}
	}

	//	Checks if an object is off screen so there is no need
	//	to render the sprite of the object.
	//	<UNDER CONSTRUCTION>
	inline bool CheckOffScreen(	int _Window_W, int _Window_H					, 
								double _xP, double _yP, double _W, double _H	)
	{
		if (	(	(	(_xP + _W) < (-_Window_W / 2.0)	)	||
					(	(_Window_W / 2.0) < _xP)			)	||
				(	(	_yP < 0			)					|| 
					(	_Window_H < (_yP - _H))				)	)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//	Calculate the distance (lenght) from two points.
	inline double Lenght(double xP, double yP, double xTarget, double yTarget)
	{
		return		tls::DoPhytagoras(xP - xTarget, yP - yTarget);
	}





	//	----------------------------------------------------------
	//	..::### Specific Functions in a specific Situation ###::..
	//	----------------------------------------------------------
	
	//	Erase-an-element-in-vector function! Note that this function works for
	//	non-pointer vectors. At least...
	template<typename Ty_>
	inline void		EraseElement(std::vector<Ty_>& _MyVec, int& _Where)
	{
		delete			_MyVec[_Where];
		_MyVec.erase(_MyVec.begin() + _Where);
		--_Where;
	}

	//	Deletes an object pointed by a pointer. (Pretty obvious)
	template<typename Ty_>
	inline void		Delete(Ty_ _Ptr)
	{
		if (_Ptr != nullptr)
		{
			delete		_Ptr;
		}
	}

	//	Deletes all contents of the vector.
	template<typename Ty_>
	inline void		DeleteVector(std::vector<Ty_>& _Ptr)
	{
		while (		!_Ptr.empty()	)
		{
			delete		_Ptr[0];
			_Ptr.erase(_Ptr.begin() + 0);
		}
	}


	//	Set colors of the available candies :D
	inline void		SetRGB(int _KindID, double& _R, double& _G, double& _B)
	{
		switch (_KindID)
		{
		case STA_::enm_KindID::_White:
			_R = 0xff, _G = 0xff, _B = 0xff;
			break;

		case STA_::enm_KindID::_Red:
			_R = 0xff, _G = 0x00, _B = 0x00;
			break;

		case STA_::enm_KindID::_Orange:
			_R = 0xff, _G = 0x72, _B = 0x00;
			break;

		case STA_::enm_KindID::_Yellow:
			_R = 0xff, _G = 0xf0, _B = 0x00;
			break;

		case STA_::enm_KindID::_Green:
			_R = 0x00, _G = 0xff, _B = 0x06;
			break;

		case STA_::enm_KindID::_Aquamarine:
			_R = 0x00, _G = 0xff, _B = 0xa8;
			break;

		case STA_::enm_KindID::_Cyan:
			_R = 0x0d, _G = 0xff, _B = 0xf7;
			break;

		case STA_::enm_KindID::_Blue:
			_R = 0x00, _G = 0x1e, _B = 0xff;
			break;

		case STA_::enm_KindID::_Purple:
			_R = 0x73, _G = 0x20, _B = 0x9e;
			break;

		case STA_::enm_KindID::_Pink:
			_R = 0xf0, _G = 0x00, _B = 0xff;
			break;

		case STA_::enm_KindID::_Chocolate:
			_R = 0xa0, _G = 0x70, _B = 0x5f;
			break;
		}
	}

	//	Set colors for FNF arrows.
	inline void		SetRGB_FNF(int _Direction, double& _R, double& _G, double& _B)
	{
		switch (_Direction)
		{
		case def::enm_Directions::_None_:
			_R = 0x7b, _G = 0xa5, _B = 0xaf;
			break;

		case def::enm_Directions::Up:
			_R = 0x00, _G = 0xfa, _B = 0x00;
			break;

		case def::enm_Directions::Down:
			_R = 0x00, _G = 0xff, _B = 0xff;
			break;

		case def::enm_Directions::Left:
			_R = 0xdf, _G = 0x4a, _B = 0x9d;
			break;

		case def::enm_Directions::Right:
			_R = 0xff, _G = 0x36, _B = 0x3d;
			break;
		}
	}

	//	Set colors of the available candies :D
	inline int		GetPunctualRGB(int _KindID, int _What)
	{
		switch (_KindID)
		{
		case STA_::enm_KindID::_White:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0xff;

			case 3:
				return 0xff;
			}

		case STA_::enm_KindID::_Red:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0x00;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Orange:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0x72;

			case 3:
				return 0x00;
			}

		case STA_::enm_KindID::_Yellow:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0xf0;

			case 3:
				return 0x00;
			}

		case STA_::enm_KindID::_Green:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xff;

			case 3:
				return 0x06;
			}

		case STA_::enm_KindID::_Aquamarine:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xff;

			case 3:
				return 0xa8;
			}

		case STA_::enm_KindID::_Cyan:
			switch (_What)
			{
			case 1:
				return 0x0d;

			case 2:
				return 0xff;

			case 3:
				return 0xf7;
			}

		case STA_::enm_KindID::_Blue:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0x1e;

			case 3:
				return 0xff;
			}

		case STA_::enm_KindID::_Purple:
			switch (_What)
			{
			case 1:
				return 0x73;

			case 2:
				return 0x20;

			case 3:
				return 0x9e;
			}

		case STA_::enm_KindID::_Pink:
			switch (_What)
			{
			case 1:
				return 0xf0;

			case 2:
				return 0x00;

			case 3:
				return 0xff;
			}

		case STA_::enm_KindID::_Chocolate:
			switch (_What)
			{
			case 1:
				return 0xa0;

			case 2:
				return 0x70;

			case 3:
				return 0x5f;
			}
		}
	}

	//	Like set RGB but you Get the color (the actual colors).
	inline int		GetRGB(int _KindID, int _What)
	{
		switch (_KindID)
		{
		case STA_::enm_KindID::_White:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0xff;

			case 3:
				return 0xff;
			}
			break;

		case STA_::enm_KindID::_Red:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0x00;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Orange:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0x6e;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Yellow:
			switch (_What)
			{
			case 1:
				return 0xff;

			case 2:
				return 0xd2;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Green:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xa5;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Aquamarine:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xec;

			case 3:
				return 0xb2;
			}
			break;

		case STA_::enm_KindID::_Cyan:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xe4;

			case 3:
				return 0xef;
			}
			break;

		case STA_::enm_KindID::_Blue:
			switch (_What)
			{
			case 1:
				return 0x0e;

			case 2:
				return 0x1c;

			case 3:
				return 0x95;
			}
			break;

		case STA_::enm_KindID::_Purple:
			switch (_What)
			{
			case 1:
				return 0x86;

			case 2:
				return 0x1a;

			case 3:
				return 0xa2;
			}
			break;

		case STA_::enm_KindID::_Pink:
			switch (_What)
			{
			case 1:
				return 0xd0;

			case 2:
				return 0x7e;

			case 3:
				return 0xb4;
			}
			break;

		case STA_::enm_KindID::_Chocolate:
			switch (_What)
			{
			case 1:
				return 0x81;

			case 2:
				return 0x51;

			case 3:
				return 0x31;
			}
			break;
		}
	}

	//	Dark colors (shadows).
	inline int		GetDarkRGB(int _KindID, int _What)
	{
		switch (_KindID)
		{
		case STA_::enm_KindID::_White:
			switch (_What)
			{
			case 1:
				return 0x8a;

			case 2:
				return 0x8a;

			case 3:
				return 0x8a;
			}
			break;

		case STA_::enm_KindID::_Red:
			switch (_What)
			{
			case 1:
				return 0x9c;

			case 2:
				return 0x00;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Orange:
			switch (_What)
			{
			case 1:
				return 0x99;

			case 2:
				return 0x3f;

			case 3:
				return 0x0a;
			}
			break;

		case STA_::enm_KindID::_Yellow:
			switch (_What)
			{
			case 1:
				return 0xe7;

			case 2:
				return 0xaf;

			case 3:
				return 0x00;
			}
			break;

		case STA_::enm_KindID::_Green:
			switch (_What)
			{
			case 1:
				return 0x0b;

			case 2:
				return 0x99;

			case 3:
				return 0x13;
			}
			break;

		case STA_::enm_KindID::_Aquamarine:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xa5;

			case 3:
				return 0x80;
			}
			break;

		case STA_::enm_KindID::_Cyan:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0xb2;

			case 3:
				return 0xac;
			}
			break;

		case STA_::enm_KindID::_Blue:
			switch (_What)
			{
			case 1:
				return 0x00;

			case 2:
				return 0x0e;

			case 3:
				return 0x9c;
			}
			break;

		case STA_::enm_KindID::_Purple:
			switch (_What)
			{
			case 1:
				return 0x59;

			case 2:
				return 0x18;

			case 3:
				return 0x83;
			}
			break;

		case STA_::enm_KindID::_Pink:
			switch (_What)
			{
			case 1:
				return 0xb4;

			case 2:
				return 0x56;

			case 3:
				return 0x94;
			}
			break;

		case STA_::enm_KindID::_Chocolate:
			switch (_What)
			{
			case 1:
				return 0x81;

			case 2:
				return 0x51;

			case 3:
				return 0x31;
			}
			break;
		}
	}

	//	Use the cos or sin function to oscilate a value...
	//	This functions returns -1 to 1 if _Factor is set by default.
	inline double	Oscilate(double _Time, double _Factor = 1.0)
	{
		if (_Factor == 0.0)
		{
			throw		std::runtime_error("Woops... Divided by 0.");
		}

		return	(((_Factor - 1.0) + std::cos(_Time)) / _Factor);
	}

	//	Smooth movement.
	//	Don't forget that InnerTime is given in iterations!
	//	Not seconds.
	inline double	SmoothMove(double _CurrentValue, double _To, double _InnerTime)
	{
		return		(	_CurrentValue + ((_To - _CurrentValue) / (_InnerTime * 0.185))	);
	}

	//	Explicit description xd.
	template<typename Ty>
	inline bool		check_if_null(Ty* _object_pointer)
	{
		if (	_object_pointer == nullptr	)
		{
			return	true;
		}

		return false;
	}





	//	-----------------------
	//	..::### Classes ###::..
	//	-----------------------

	//	- - - Vec2 - - -
	template<typename Ty_>
	class Vec2
	{
	public:
		//	-> Vars.
		Ty_				First = 0;
		Ty_				Second = 0;

		//	-> Initializers.
		Vec2()
		{

		}
		Vec2(Ty_ _First, Ty_ _Second) : First(_First), Second(_Second)
		{

		}

		~Vec2()
		{

		}

		//	-> Functions.
	};

	//	- - - Vec2 - - -
	template<typename Ty_>
	class Vec3
	{
	public:
		//	-> Vars.
		Ty_				First = 0;
		Ty_				Second = 0;
		Ty_				Third = 0;

		//	-> Initializers.
		Vec3()
		{

		}
		Vec3(Ty_ _First, Ty_ _Second, Ty_ _Third) : First(_First), Second(_Second), Third(_Third)
		{

		}

		~Vec3()
		{

		}

		//	-> Functions.
		inline Ty_&			at(int _Where)
		{
			switch (_Where)
			{
			case 1:
				return		this->First;

			case 2:
				return		this->Second;

			case 3:
				return		this->Third;

			default:
				throw		std::runtime_error("I can't find it :c");
			}
		}
	};

	//	- - - Vec4 - - -
	template<typename Ty_>
	class Vec4
	{
	public:
		//	-> Vars.
		Ty_				First = 0;
		Ty_				Second = 0;
		Ty_				Third = 0;
		Ty_				Fourth = 0;

		//	-> Initializers.
		Vec4()
		{

		}
		Vec4(Ty_ _First, Ty_ _Second, Ty_ _Third, Ty_ _Fourth) : First(_First), Second(_Second), Third(_Third), Fourth(_Fourth)
		{

		}

		~Vec4()
		{

		}

		//	-> Functions.
		inline Ty_&			at(int _Where)
		{
			switch (_Where)
			{
			case 1:
				return		this->First;

			case 2:
				return		this->Second;

			case 3:
				return		this->Third;

			case 4:
				return		this->Fourth;

			default:
				throw		std::runtime_error("I can't find it :c");
			}
		}
	};

	//	- - - Vec6 - - -
	template<typename Ty_>
	class Vec6
	{
	public:
		//	-> Vars.
		Ty_				First	= 0;
		Ty_				Second	= 0;
		Ty_				Third	= 0;
		Ty_				Fourth	= 0;
		Ty_				Fifth	= 0;
		Ty_				Sixth	= 0;

		//	-> Initializers.
		Vec6()
		{

		}
		Vec6(Ty_ _First, Ty_ _Second, Ty_ _Third, Ty_ _Fourth, Ty_ _Fifth, Ty_ _Sixth) : First(_First), Second(_Second), Third(_Third), Fourth(_Fourth), Fifth(_Fifth), Sixth(_Sixth)
		{

		}

		~Vec6()
		{

		}

		//	-> Functions.
	};

	//	- - - Char - - -
	class		Char : public thyObject
	{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Private side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	
	//	-------------------------------------------
	//					Containers
	//	-------------------------------------------
	private:
		int			m_charID	= 0;
		int			m_FontType	= 0;

		double		xRef		= 0.0;
		double		yRef		= 0.0;
		double		m_FontSize	= 17;		//	17 is considered as normal size (age c:).

	//	-------------------------------------------
	//					Functions
	//	-------------------------------------------
	private:
		inline void			fn_SetMeasureByFontType(	int WhatFont	)
		{
			double		_TallestCharacterH_ = 125.0;



			switch (	WhatFont	)
			{
			case	0:
				this->_W = 66, this->_H = 100; 
				break;

			case	1:
				//	The 0.0, 0.0 (origin) is the tallest character.
				switch (	this->m_charID	)
				{
				case	97:		//	a
					this->_W	= 69.0;
					this->_H	= 88.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	98:		//	b
					this->_W	= 77.0;
					this->_H	= 119.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	99:		//	c
					this->_W	= 76.0;
					this->_H	= 84.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	100:	//	d
					this->_W	= 72.0;
					this->_H	= 123.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	101:	//	e
					this->_W	= 78.0;
					this->_H	= 85.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	102:	//	f
					this->_W	= 60.0;
					this->_H	= 124.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	103:	//	g
					this->_W	= 73.0;
					this->_H	= 130.0;
					this->fn_LowerCharacterRef(-38.0);
					break;

				case	104:	//	h
					this->_W	= 73.0;
					this->_H	= 125.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	105:	//	i
					this->_W	= 21.0;
					this->_H	= 102.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	106:	//	j
					this->_W	= 50.0;
					this->_H	= 119.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	107:	//	k
					this->_W	= 63.0;
					this->_H	= 115.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	108:	//	l
					this->_W	= 49.0;
					this->_H	= 114.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	109:	//	m
					this->_W	= 124.0;
					this->_H	= 76.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	110:	//	n
					this->_W	= 75.0;
					this->_H	= 78.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	111:	//	o
					this->_W	= 78.0;
					this->_H	= 78.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	112:	//	p
					this->_W	= 69.0;
					this->_H	= 125.0;
					this->fn_LowerCharacterRef(-39.0);
					break;

				case	113:	//	q
					this->_W	= 69.0;
					this->_H	= 125.0;
					this->fn_LowerCharacterRef(-39.0);
					break;

				case	114:	//	r
					this->_W	= 70.0;
					this->_H	= 83.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	115:	//	s
					this->_W	= 77.0;
					this->_H	= 83.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	116:	//	t
					this->_W	= 53.0;
					this->_H	= 114.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	117:	//	u
					this->_W	= 80.0;
					this->_H	= 78.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	118:	//	v
					this->_W	= 83.0;
					this->_H	= 77.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	119:	//	w
					this->_W	= 119.0;
					this->_H	= 82.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	120:	//	x
					this->_W	= 85.0;
					this->_H	= 84.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;

				case	121:	//	y
					this->_W	= 75.0;
					this->_H	= 112.0;
					this->fn_LowerCharacterRef(-42.0);
					break;

				case	122:	//	z
					this->_W	= 78.0;
					this->_H	= 78.0;
					this->fn_AdjustCharacterRef(_TallestCharacterH_);
					break;
				}
				break;
			}
		}
		inline void			fn_AdjustCharacterRef(		double Tallest	)
		{
			this->yRef		= this->_H - Tallest;
		}
		inline void			fn_LowerCharacterRef(		double HowMuch	)
		{
			this->yRef		= HowMuch;
		}





	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//			Constructors and Destructor
	//	-------------------------------------------
	public:
		Char(	int _charID, double _FontSize, int WhatFont	)
		{
			this->m_charID		= _charID;
			this->m_FontSize	= _FontSize;
			this->m_FontType	= WhatFont;
			

			this->xFct			= tls::Scale(17, _FontSize);
			this->yFct			= this->xFct;
			this->fn_SetMeasureByFontType(WhatFont);
		}

		~Char()
		{

		}

	//	-------------------------------------------
	//				Setters and Getters
	//	-------------------------------------------
	public:
		inline void			s_CharID(int _CharID)
		{
			this->m_charID = _CharID;
		}
		inline void			s_FontSize(double _FontSize)
		{
			this->m_FontSize = _FontSize;
		}

		inline int			g_CharID()		const 
		{
			return this->m_charID;
		}
		inline double		g_FontSize()	const
		{
			return this->m_FontSize;
		}
		inline int			g_FontType()	const
		{
			return		this->m_FontType;
		}

		inline double		g_PosRef(	int What	)
		{
			switch (	What	)
			{
			case	1:
				return		this->xRef;

			case	2:
				return		this->yRef;

			default:
				return		def::enm_Defines::_NOT_FOUND;
			}
		}
	};

	//	- - - String - - -
	class		String : public thyObject
	{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Private side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	
	//	-------------------------------------------
	//					Containers
	//	-------------------------------------------
	private:
		std::vector<tls::Char*>			m_String;

	//	-------------------------------------------
	//					Variables
	//	-------------------------------------------
	private:
		unsigned int		m_Size				= 0;	
		int					m_LetterSpacing		= 0;
		int					m_EndLineSpacing	= 0;





	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//			Constructors and Destructor
	//	-------------------------------------------
	public:
		String() {}

		~String()
		{
			tls::DeleteVector(this->m_String);
		}

	//	-------------------------------------------
	//					Functions
	//	-------------------------------------------
	public:
		inline void					Clear()
		{
			tls::DeleteVector(	this->m_String	);
		}
		inline void					Write(	const std::string& _Str, double _FontSize = 17		,
											bool RePos = false, bool ClearString = false		,
											int WhatFont = 0									)
		{
			//	If clearing.
			if (	ClearString	)
			{
				this->Clear();
			}

			//	Adding characters.
			for (	int i = 0; i < _Str.size(); ++i	)
			{
				this->m_String.push_back(	new tls::Char(static_cast<int>(_Str[i]), _FontSize, WhatFont)	);
			}

			//	If RePos.
			if (	RePos	)
			{
				this->RePos();
			}
		}
		inline void					RePos()
		{
			//	Updates:
			//	Has some flaws, but it's just 
			//	a thing or two to be added.
			//	Nothing serious.

			double		IterativeWidth	= 0.0;
			bool		IsEndLine		= false;
			int			Cnt_EndLine		= 0;
			int			Cnt_Characters	= 0;
			this->m_Size		= this->m_String.size();



			//	Then, fixing every character position for printing on the screen.
			for (int i = 0; i < this->m_Size; ++i)
			{
				//	If there is an endline, then increase the counter.
				{
					IsEndLine = false;
			
					if (this->m_String[i]->g_CharID() == 10)
					{
						++Cnt_EndLine;
						Cnt_Characters	= 0;
						IsEndLine		= true;
					}
				}		
			
				//	Setting pos for every character.
				{
					this->m_String[i]->s_VisualPrp(		1, tls::Scale(17.0, this->m_String[i]->g_FontSize())		);
					this->m_String[i]->s_VisualPrp(		2, tls::Scale(17.0, this->m_String[i]->g_FontSize())		);



					//	All characters share the same width and height.
					if (	this->m_String[i]->g_FontType() == 0	)
					{	
						this->m_String[i]->s_PositionPrp(		1,	this->xP + ((Cnt_Characters * (this->m_LetterSpacing + this->m_String[i]->g_MeasuresPrp(1)))) * (this->m_String[i]->g_VisualPrp(1))		);
						this->m_String[i]->s_PositionPrp(		2,	this->yP + (this->m_String[i]->g_PosRef(2) * this->m_String[i]->g_VisualPrp(2)) - 
																	((Cnt_EndLine * (this->m_EndLineSpacing + this->m_String[i]->g_MeasuresPrp(2)))) * (this->m_String[i]->g_VisualPrp(2))	);	
					}
					//	Each character has its own measures.
					else
					{
						this->m_String[i]->s_PositionPrp(		1,	this->xP + IterativeWidth	);
						this->m_String[i]->s_PositionPrp(		2,	this->yP + (this->m_String[i]->g_PosRef(2) * this->m_String[i]->g_VisualPrp(2)) - 
																	((Cnt_EndLine * (this->m_EndLineSpacing + this->m_String[i]->g_MeasuresPrp(2)))) * (this->m_String[i]->g_VisualPrp(2))	);
					}



					IterativeWidth	= IterativeWidth + ((this->m_LetterSpacing + this->m_String[i]->g_MeasuresPrp(1)) * this->m_String[i]->g_VisualPrp(1));
				}
			
				//	Final touches...
				{
					if (!IsEndLine)
					{
						++Cnt_Characters;
					}
				}
			
			}
		}

	//	-------------------------------------------
	//				Common Functions
	//	-------------------------------------------
	public:
		inline Char*				at(unsigned int _Where)
		{
			return		this->m_String[_Where];
		}
		inline unsigned int			size()
		{
			return		this->m_String.size();
		}

	//	-------------------------------------------
	//				Setters and Getters
	//	-------------------------------------------
	public:
		inline double			GetStringMeasure(	int What	)
		{
			//	Returning if string is empty.
			if (	this->m_String.empty()	)
			{
				return	0.0;
			}

			//	Else, continue.
			double		Measure			= 0.0;
			double		TallestChar		= 0.0;



			switch (	What	)
			{
			case 1:
				this->m_Size	= this->m_String.size();

				for (	int i = 0; 
						i < this->m_Size; 
						++i	)
				{
					Measure		= Measure + (this->m_String[i]->g_VisualPrp(1) * (this->m_String[i]->g_MeasuresPrp(1) + this->m_LetterSpacing));
				}
				
				return	Measure;

			case 2:
				//	Not implemented for endlines yet.
				this->m_Size	= this->m_String.size();
				TallestChar		= this->m_String[0]->g_MeasuresPrp(2) * this->m_String[0]->g_VisualPrp(2);

				for (	int i = 0; 
						i < this->m_Size; 
						++i	)
				{
					//	Normal font: All chars shares same measures.
					if (	this->m_String[i]->g_FontType() == 0	)
					{
						Measure		= this->m_String[i]->g_MeasuresPrp(2) * this->m_String[i]->g_VisualPrp(2);
					}
					//	Custom: All chars has differente measures.
					else
					{
						if (	TallestChar	< (this->m_String[i]->g_MeasuresPrp(2) * this->m_String[0]->g_VisualPrp(2))		)
						{
							TallestChar = this->m_String[i]->g_MeasuresPrp(2) * this->m_String[0]->g_VisualPrp(2);
						}
					}
				}

				if (	Measure < TallestChar	)
				{
					return		TallestChar;
				}
				else
				{
					return		Measure;
				}
				
				break;
			}
		}
		inline void				SetLetterSpacing(	int Value	)
		{
			this->m_LetterSpacing = Value;
		}
	};
}

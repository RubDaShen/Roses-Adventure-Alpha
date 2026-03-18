#pragma once
#include	"thyObject.h"
#include	"thyAnm.h"
#include	"thyEffect.h"



class	Ld_SandTimer : public thyObject
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
	Ld_SandTimer(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~Ld_SandTimer()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void				Animate()
	{
		this->rotationDegree = this->rotationDegree + 2.0;
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:

};
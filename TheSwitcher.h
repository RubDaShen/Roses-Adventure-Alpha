#pragma once

#include	<iostream>
#include	<vector>
#include	<utility>

#include	"thyObject.h"
#include	"_Basics_Mouse.h"
#include	"Tools_.h"
#include	"SoundFactory.h"
#include	"SpecialMixes.h"



class		_Selection_Frame : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_FrameAnimation
	{
		Default			= 0,
		SpecialMix		= 1,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	TheCandy*	m_Linker				= nullptr;

	int			m_KindID				= def::enm_Defines::_NOT_INITIALIZED;
	int			m_Linker_ID				= def::enm_Defines::_NOT_INITIALIZED;
	int			m_AnimationID			= enm_FrameAnimation::Default;

	double		m_Time					= 0.0;
	double		m_Where_xP				= 0.0, m_Where_yP = 0.0;

	bool		m_IddleAnimation		= true;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	_Selection_Frame(	double _xP, double _yP, int _KindID, TheCandy* _Bind_	) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{
		this->m_KindID			= _KindID;
		this->m_Linker			= _Bind_;
		this->m_Linker_ID		= this->m_Linker->g_ObjectID();

		this->_W	= this->_H = 90.0;
	}

	~_Selection_Frame()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			AnimateFrame()
	{
		this->m_Time = this->m_Time + 0.025;



		//	Linker part.
		{
			if (this->m_Linker != nullptr)
			{
				if (this->m_Linker_ID == this->m_Linker->g_ObjectID())
				{
					switch (	this->m_AnimationID		)
					{
					case enm_FrameAnimation::Default:
						this->xP = m_Linker->g_PositionPrp(1);
						this->yP = m_Linker->g_PositionPrp(2);

						break;
					}
				}
			}
		}

		//	Opacity.
		{
			this->A_alpha = this->A_alpha + this->Alpha_s;

			if (this->A_alpha <= 0.0)
			{
				this->Alpha_a = 0.0;
			}
		}

		//	Shrinking part.
		{
			if (this->m_IddleAnimation)
			{
				this->xFct = (15.0 + std::cos(this->m_Time)) / 16.0;			
			}
			else
			{
				switch (	this->m_AnimationID		)
				{
				case	enm_FrameAnimation::Default:
					this->xFct		= (1.0 / (1.0 + (this->m_Time / 5.0))) + 0.4;

					break;

				case	enm_FrameAnimation::SpecialMix:
					this->xFct		= this->xFct + this->xFctS;
					this->xFctS		= this->xFctS + this->xFctA;

					break;
				}
				
			}

			this->yFct = this->xFct;
		}
	}		
	inline void			ActivateKind(	bool _Frame_Is_Lost_, int _AnimationID	)
	{
		this->m_AnimationID		= _AnimationID;



		switch (	this->m_AnimationID	)
		{
		case enm_FrameAnimation::Default:
			this->Alpha_s				= -2.0;
			this->m_IddleAnimation		= false;
			this->xFct					= this->yFct = 1.12;
			this->xFctS					= -0.0012;
			this->m_Time				= 0.0;

			break;

		case enm_FrameAnimation::SpecialMix:
			this->Alpha_s				= -4.0;
			this->m_IddleAnimation		= false;
			this->xFct					= this->yFct = 1.0;
			this->xFctS					= 0.04;
			this->xFctA					= -0.00125;
			this->m_Time				= 0.0;

			break;
		}

		if (	_Frame_Is_Lost_	)
		{
			this->m_KindID = 0;
		}

		tls::SetRGB(this->m_KindID, this->R_col, this->G_col, this->B_col);
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline int			g_SpritePosition(	int What	)
	{
		switch (	What	)
		{
		case	1:
			return		(this->xP + (this->_W * 0.5));

		case	2:
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
class		Switcher
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//					 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Enums!
//	-------------------------------------------
public:
	enum		enm_SwitchingOrder
	{
		None	= 0,
		First	= 1,
		Second	= 2,
	};
	enum		enm_Draw
	{
		_SelectionFrame		= 0,
	};





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	int				_GridBound_		= 90;
	double			_SpeedLimit_	= 0.0;

//	-------------------------------------------
//				Included variables
//	-------------------------------------------
private:
	std::vector<_Selection_Frame*>		m_Frames;

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:
	int				m_Cnt_Selected	= 0, m_Trg_Selected = 2;

	double			m_DragAmt		= 50.0;

	bool			m_FreeSwitch	= false;
	bool			m_SwitchMade	= false;

//	-------------------------------------------
//				Other variables
//	-------------------------------------------
private:
	bool		_AllDone_			= false;
	bool		_DropDrag_			= false;
	bool		_IsBlocked_			= false;
	bool		_IsFirstChoose_		= true;
	bool		_Candy_Not_Exist_	= false;
	bool		_Skip_				= false;
	bool		_CanUnselect_		= false;
	bool		_GoAndUnselect_		= false;
	
	int			_Size_Candies_		= 0;
	int			_Which_AT_			= 0,	_Which_ID_		= 0;
	int			_With_AT_			= 0,	_With_ID_		= 0;

	double		_Current_xP_		= 0.0,	_Current_yP_	= 0.0;

//	-------------------------------------------
//			[4] Outside and Linkers
//	-------------------------------------------
private:
	SoundFactory*			_Sound_		= nullptr;
	DrawFactory*			_Draw_		= nullptr;
	SpriteFactory*			_Sprites_	= nullptr;

	int			_What_Sprite_		= 0;
	int			_What_Kind_			= 0;
	int			_Container_Size_	= 0;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	Switcher(	DrawFactory* _Draw_Ptr		,
				SpriteFactory* _Sprite_Ptr	,
				SoundFactory* _Sound_Ptr	)
	{
		this->_Draw_		= _Draw_Ptr;
		this->_Sprites_		= _Sprite_Ptr;
		this->_Sound_		= _Sound_Ptr;
	}

	~Switcher()
	{
		//	Erasing m_Frames.
		{
			while (!this->m_Frames.empty())
			{
				delete		this->m_Frames[0];
				this->m_Frames.erase(this->m_Frames.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoSwitching(	std::vector<TheCandy*>&	_Candies_			, 
										_Basic_Mouse*				_Mouse_				,
										Camera*						_Camera				,
										const tls::Vec4<double>&	_Board_				,
										_Controller_SpecialMixes*	_SpecialMixes_		)
	{		
		this->_Size_Candies_		= _Candies_.size();
		this->_Candy_Not_Exist_		= false;
		this->m_SwitchMade			= false;



		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//							Step 1:
		//			Find and select a candy (Just the first candy).
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		{
			//	If mouse is pressed (obviously).
			if ( (_Mouse_->g_Is(1)) && (this->_IsFirstChoose_) && (!this->_AllDone_))
			{
				//	Check if position of mouse is clicking the board.
				if (	tls::CollidesWith(	_Mouse_->g_Position_Camera(2, 1, _Camera), _Mouse_->g_Position_Camera(2, 2, _Camera), 1, 1,
											_Board_.First, _Board_.Second, 
											(_Board_.Third * this->_GridBound_), (_Board_.Fourth * this->_GridBound_)	)	)
				{ 
					_Which_AT_						= def::enm_Defines::_NOT_FOUND;

					this->_Size_Candies_			= _Candies_.size();
					this->_CanUnselect_				= this->_GoAndUnselect_ = false;



					//	Now, check for any candy that is being selected.
					{
						for (	int i = 0; 
								i < this->_Size_Candies_; 
								++i	)
						{
							this->_Skip_ = false;



							//	Speed condition.
							{
								if (	(fabs(_Candies_[i]->g_PositionPrp(3)) != _SpeedLimit_)	||
										(fabs(_Candies_[i]->g_PositionPrp(4)) != _SpeedLimit_)	)
								{
									this->_Skip_ = true;
								}
							}

							//	Swapping condition.
							{
								if (	_Candies_[i]->g_IsSwapping(1)	)
								{
									this->_Skip_ = true;
								}
							}

							//	Falling condition.
							{
								if (	_Candies_[i]->g_Is(1)	)
								{
									this->_Skip_ = true;
								}
							}

							//	If it is targeted by a fish, then not.
							{
								if (	_Candies_[i]->g_TargetedByFish()	)
								{
									this->_Skip_ = true;
								}
							}

							//	If it doesn't have a licorice cage.
							{
								if (	_Candies_[i]->g_HasBlocker(1)		)
								{
									this->_Skip_ = true;
								}
							}

							//	If it doesn't have a licorice cage.
							{
								if (	_Candies_[i]->g_ItemAllowsSomething(4)		)
								{
									this->_Skip_ = true;
								}
							}

							//	Basic collision.
							{
								if (	tls::CollidesWith(	_Mouse_->g_Position_Camera(2, 1, _Camera), _Mouse_->g_Position_Camera(2, 2, _Camera), 1, 1,
															_Candies_[i]->g_PositionPrp(1), _Candies_[i]->g_PositionPrp(2),
															_Candies_[i]->g_MeasuresPrp(1), _Candies_[i]->g_MeasuresPrp(2)	)	&&
																			(!this->_Skip_)										)
								{
									this->_IsFirstChoose_	= false;
									this->_CanUnselect_		= true;
									this->_Current_xP_		= _Mouse_->g_Position_Camera(2, 1, _Camera);
									this->_Current_yP_		= _Mouse_->g_Position_Camera(2, 2, _Camera);

									_Which_ID_				= _Candies_[i]->g_ObjectID();
									_Which_AT_				= i;

									break;
								}
							}
						}
					}


					if (_Which_AT_ != def::enm_Defines::_NOT_FOUND)
					{
						this->AddFrame(		_Candies_[_Which_AT_]->g_PositionPrp(1)	,
											_Candies_[_Which_AT_]->g_PositionPrp(2)	, 
											_Candies_[_Which_AT_]->g_KindID()		,
											_Candies_[_Which_AT_]);
					}
				}
			}
		};

		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//							Step 1.5:
		//						Candies deselection*
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		{
			//	Unpress handling.
			{
				if ((this->_CanUnselect_) && (!_GoAndUnselect_))
				{
					this->_GoAndUnselect_ = !_Mouse_->g_Is(1);
				}			
			}

			//	If mouse is pressed (obviously).
			if (	(_Mouse_->g_Is(1)) && (!this->_IsFirstChoose_) && (this->_CanUnselect_) && (this->_GoAndUnselect_) && (!this->_AllDone_))
			{

				_Which_AT_				= def::enm_Defines::_NOT_FOUND;
				this->_Size_Candies_	= _Candies_.size();



				//	Then, check if that selected candy was the same as selected.
				{
					for (	int i = 0;
							i < this->_Size_Candies_;
							++i	)
					{
						this->_Skip_ = false;



						//	Basic collision.
						{
							if (	tls::CollidesWith(	_Mouse_->g_Position_Camera(2, 1, _Camera), _Mouse_->g_Position_Camera(2, 2, _Camera), 1, 1,
														_Candies_[i]->g_PositionPrp(1), _Candies_[i]->g_PositionPrp(2),
														_Candies_[i]->g_MeasuresPrp(1), _Candies_[i]->g_MeasuresPrp(2)	)		&&
																				(!this->_Skip_)									)
							{
								this->_With_ID_ = _Candies_[i]->g_ObjectID();



								if ((this->_CanUnselect_) && (this->_With_ID_ == this->_Which_ID_))
								{
									this->_GoAndUnselect_		= this->_CanUnselect_ = false;
									this->_IsFirstChoose_		= true;
									this->_AllDone_				= true;
			
									this->ActivateLastFrame(0, true);

									break;
								}
							}
						}
					}
				}			
			}
		}


		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//							Step 2:
		//				Find the other candy (Make a pair).
		//					Using moving mouse :D
		//	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		{
			if (	(	(_Mouse_->g_Position_Camera(1, 1, _Camera) < (this->_Current_xP_ - this->m_DragAmt))	||
						(_Mouse_->g_Position_Camera(1, 1, _Camera) > (this->_Current_xP_ + this->m_DragAmt))	)		||
					(	(_Mouse_->g_Position_Camera(1, 2, _Camera) < (this->_Current_yP_ - this->m_DragAmt))	||
						(_Mouse_->g_Position_Camera(1, 2, _Camera) > (this->_Current_yP_ + this->m_DragAmt))	)		)
			{
				if (!this->_IsFirstChoose_)
				{
					this->_DropDrag_ = true;
				}
			}


			

			if ( (this->_DropDrag_)	&& (!this->_IsFirstChoose_) && (!this->_AllDone_) )
			{
				//	Moving and cancelation verification.
				{ 
					//	First, check where the mouse moves.
					{
						if (	(	(_Mouse_->g_Position_Camera(1, 1, _Camera) < (this->_Current_xP_ - this->m_DragAmt))	||
									(_Mouse_->g_Position_Camera(1, 1, _Camera) > (this->_Current_xP_ + this->m_DragAmt))	)		||
								(	(_Mouse_->g_Position_Camera(1, 2, _Camera) < (this->_Current_yP_ - this->m_DragAmt))	||
									(_Mouse_->g_Position_Camera(1, 2, _Camera) > (this->_Current_yP_ + this->m_DragAmt))	)		)
						{
							double			_Angle_		=	tls::FindAngle(	_Current_xP_, _Current_yP_					, 
																			_Mouse_->g_Position_Camera(1, 1, _Camera)	, 
																			_Mouse_->g_Position_Camera(1, 2, _Camera)	,
																			false										);
							int				_Quadrant_		=	tls::FindQuadrant(_Angle_ + 45.0);
							bool			_SpecialMix_	= false;


							this->_AllDone_			= true;													
							this->_DropDrag_		= false;
							this->_Which_AT_		= def::enm_Defines::_NOT_FOUND;
							this->_With_AT_			= def::enm_Defines::_NOT_FOUND;




							//	Finding the first candy and the second one (if they both exist too).
							{
								//	Finding the first candy !
								{
									for (	int i = 0;
											i < this->_Size_Candies_;
											++i	)
									{
										if (this->_Which_ID_ == _Candies_[i]->g_ObjectID())
										{
											this->_Which_AT_ = i;
											break;
										}
									}
								}

								//	Finding the second candy !
								{
									//	Which?
									if (	this->_Which_AT_ != def::enm_Defines::_NOT_FOUND	)
									{
										int		_iPos_Des	= _Candies_[_Which_AT_]->g_Pos(1);
										int		_jPos_Des	= _Candies_[_Which_AT_]->g_Pos(2);

										switch (_Quadrant_)
										{
										case tls::_Quadrant_::FirstQuadrant:
											++_jPos_Des;
											break;

										case tls::_Quadrant_::SecondQuadrant:
											--_iPos_Des;
											break;

										case tls::_Quadrant_::ThirdQuadrant:
											--_jPos_Des;
											break;

										case tls::_Quadrant_::FourthQuadrant:
											++_iPos_Des;
											break;
										}



										for (	int i = 0;
												i < this->_Size_Candies_;
												++i	)
										{
											this->_Skip_				= false;
											this->_Candy_Not_Exist_		= true;



											//	Speed condition.
											{
												if (	(fabs(_Candies_[i]->g_PositionPrp(3)) != _SpeedLimit_) ||
														(fabs(_Candies_[i]->g_PositionPrp(4)) != _SpeedLimit_)	)
												{
													this->_Skip_ = true;
												}
											}

											//	Swapping condition.
											{
												if (	_Candies_[i]->g_IsSwapping(1)	)
												{
													this->_Skip_ = true;
												}
											}

											//	Falling condition.
											{
												if (	_Candies_[i]->g_Is(1)	)
												{
													this->_Skip_ = true;
												}
											}

											//	If it is targeted by a fish, then not.
											{
												if (	_Candies_[i]->g_TargetedByFish()	)
												{
													this->_Skip_ = true;
												}
											}

											//	If it doesn't have a licorice cage.
											{
												if (	_Candies_[i]->g_HasBlocker(1)		)
												{
													this->_Skip_ = true;
												}
											}

											//	If it doesn't have a licorice cage.
											{
												if (	_Candies_[i]->g_ItemAllowsSomething(4)		)
												{
													this->_Skip_ = true;
												}
											}


											//	Checking the in-board position of the selected candy.
											{
												if ((_Candies_[i]->g_Pos(1) == _iPos_Des) && (_Candies_[i]->g_Pos(2) == _jPos_Des) && (!this->_Skip_))
												{
													this->_Candy_Not_Exist_		= false;
													this->_With_AT_				= i;

													break;
												}
											}
										}
									}
									else
									{
										this->ActivateLastFrame(0, true);

										this->_Candy_Not_Exist_ = true;
									}



									//	With?
									if (	this->_With_AT_ == def::enm_Defines::_NOT_FOUND	)
									{
										this->ActivateLastFrame(0, true);

										this->_Candy_Not_Exist_ = true;
									}
								}
							}

							//	Then, config this candies...
							{
								//	List!
								//		1.	IsSwapping
								//		2.	SwapDirection
								//		3.	SwapDes
								//		4.	SwappedID
								//		5.	InvalidSwap
								//		6.	SwitchOrder

								if (!this->_Candy_Not_Exist_)
								{
									//	SwapDirection = Quadrant;
									switch (_Quadrant_)
									{
									case tls::_Quadrant_::FirstQuadrant:
										_Candies_[this->_Which_AT_]->s_SwapDirection(	def::enm_Directions::Right	);
										_Candies_[this->_With_AT_]->s_SwapDirection(	def::enm_Directions::Left	);

										break;

									case tls::_Quadrant_::SecondQuadrant:
										_Candies_[this->_Which_AT_]->s_SwapDirection(	def::enm_Directions::Up		);
										_Candies_[this->_With_AT_]->s_SwapDirection(	def::enm_Directions::Down	);

										break;

									case tls::_Quadrant_::ThirdQuadrant:
										_Candies_[this->_Which_AT_]->s_SwapDirection(	def::enm_Directions::Left	);
										_Candies_[this->_With_AT_]->s_SwapDirection(	def::enm_Directions::Right	);

										break;

									case tls::_Quadrant_::FourthQuadrant:
										_Candies_[this->_Which_AT_]->s_SwapDirection(	def::enm_Directions::Down	);
										_Candies_[this->_With_AT_]->s_SwapDirection(	def::enm_Directions::Up		);

										break;
									}

									//	- - - - - - - - - - - - - - - - - - - - - - - - - -

									//	No matter what set up this values.
									{
										//	SwapDes = this;
										_Candies_[this->_Which_AT_]->s_SwapDes(			_Candies_[this->_With_AT_]->g_PositionPrp(1)	, 
																						_Candies_[this->_With_AT_]->g_PositionPrp(2)	);
										_Candies_[this->_With_AT_]->s_SwapDes(			_Candies_[this->_Which_AT_]->g_PositionPrp(1)	,
																						_Candies_[this->_Which_AT_]->g_PositionPrp(2)	);

										//	SwitchOrder = this;
										_Candies_[this->_Which_AT_]->s_SwitchOrder(		Switcher::enm_SwitchingOrder::First		);
										_Candies_[this->_With_AT_]->s_SwitchOrder(		Switcher::enm_SwitchingOrder::Second	);

										//	IsSwapping = true;
										_Candies_[this->_Which_AT_]->s_IsSwapping(		1, true	);
										_Candies_[this->_With_AT_]->s_IsSwapping(		1, true	);

										//	SwappedID = this;
										_Candies_[this->_Which_AT_]->s_OtherSwappedID(	_Candies_[this->_With_AT_]->g_ObjectID()	);
										_Candies_[this->_With_AT_]->s_OtherSwappedID(	_Candies_[this->_Which_AT_]->g_ObjectID()	);

										//	InvalidSwap = this;
										_Candies_[this->_Which_AT_]->s_IsSwapping(		3, !this->m_FreeSwitch);
										_Candies_[this->_With_AT_]->s_IsSwapping(		3, !this->m_FreeSwitch);
									}

									//	Before going on. Let's check if the swapped candies
									//	are special candies.
									{
										using		sMx		= SpecialMixWrapper::enm_SpecialMix;
										using		swOrd	= Switcher::enm_SwitchingOrder;



										//	.....................
										//	....Special mixes....
										//	.....................
										//	There are a lot of special mixes.
										//	I'll go in order, starting first with stripped candies.
										//	_Which_AT_	=>	First.
										//	_With_AT_	=>	Second.

										//	Stripped Horizontal Candy.
										{
											//	Stripped Horizotal + Stripped Horizontal.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH)			)
												{ 
													//	Say: These candies can't be crushed nor matched nor moved.
													{
														_Candies_[this->_Which_AT_]->s_Can(		2, false	);
														_Candies_[this->_With_AT_]->s_Can(		2, false	);

														_Candies_[this->_Which_AT_]->s_Can(		3, false	);
														_Candies_[this->_With_AT_]->s_Can(		3, false	);
													}

													//	Then add these special candies to the controller.
													{
														_SpecialMixes_->AddWrapper(_Candies_[this->_Which_AT_],
															_Candies_[this->_With_AT_],
															sMx::StrippedH_StrippedH);
													}

													//	Little things.
													{
														_SpecialMix_ = true;
													}
												}
											}

											//	Stripped Horizotal + Stripped Vertical.
											{
												if ((_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH) &&
													(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedV))
												{
													//	Say: These candies can't be crushed nor matched.
													{
														_Candies_[this->_Which_AT_]->s_Can(2, false);
														_Candies_[this->_With_AT_]->s_Can(2, false);

														_Candies_[this->_Which_AT_]->s_Can(3, false);
														_Candies_[this->_With_AT_]->s_Can(3, false);
													}

													//	Then add these special candies to the controller.
													{
														_SpecialMixes_->AddWrapper(_Candies_[this->_Which_AT_],
															_Candies_[this->_With_AT_],
															sMx::StrippedH_StrippedV);
													}

													//	Little things.
													{
														_SpecialMix_ = true;
													}
												}
											}

											//	Stripped Horizotal + Wrapped Candy.
											{
												if ((_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH) &&
													(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedCandy))
												{
													//	Say: These candies can't be crushed nor matched.
													{
														_Candies_[this->_Which_AT_]->s_Can(2, false);
														_Candies_[this->_With_AT_]->s_Can(2, false);

														_Candies_[this->_Which_AT_]->s_Can(3, false);
														_Candies_[this->_With_AT_]->s_Can(3, false);
													}

													//	Then add these special candies to the controller.
													{
														_SpecialMixes_->AddWrapper(_Candies_[this->_Which_AT_],
															_Candies_[this->_With_AT_],
															sMx::StrippedH_Wrapped);
													}

													//	Little things.
													{
														_SpecialMix_ = true;
													}
												}
											}

											//	Stripped Horizotal + Wrapped Fuse.
											{
												if ((_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH) &&
													(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedFuse))
												{
													//	Say: These candies can't be crushed nor matched.
													{
														_Candies_[this->_Which_AT_]->s_Can(2, false);
														_Candies_[this->_With_AT_]->s_Can(2, false);

														_Candies_[this->_Which_AT_]->s_Can(3, false);
														_Candies_[this->_With_AT_]->s_Can(3, false);
													}

													//	Then add these special candies to the controller.
													{
														_SpecialMixes_->AddWrapper(_Candies_[this->_Which_AT_],
															_Candies_[this->_With_AT_],
															sMx::StrippedH_WrappedFuse);
													}

													//	Little things.
													{
														_SpecialMix_ = true;
													}
												}
											};
										};

										//	Bon-O-Bom.
										{
											//	Bon-O-Bom + Common Candy.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::CommonCandy)	)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]	,
																						_Candies_[this->_With_AT_]	,
																						sMx::BonOBom_CommonCandy	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Stripped Horizontal.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_StrippedHorizontal	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Stripped Vertical.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedV)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_StrippedVertical	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Wrapped.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)			&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedCandy)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_Wrapped			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Wrapped Fuse.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)			&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_WrappedFuse		);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Jelly Fish.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)				&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::JellyFish)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_JellyFish			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + Starlight.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::Starlight)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_StarLight			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + FireWorkRocket.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)				&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::FireWorkRocket)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_FireWork			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + BubbleGum.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::BubbleGum)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_BubbleGum			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Bon-O-Bom + PoppingCandy.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::BomOBom)			&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::PoppingCandy)		)
												{ 
													//	The Bon-O-Bom shouldn't be fusing.
													if (	!_Candies_[this->_Which_AT_]->g_BoB_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched nor moved.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);
															_Candies_[this->_With_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::BonOBom_Popping			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											};
										};

										//	Frozen Candy.
										{
											//	Frozen Candy + Common Candy.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::CommonCandy)		)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]		,
																						_Candies_[this->_With_AT_]		,
																						sMx::FrozenCandy_CommonCandy	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Stripped Horizontal.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedH)		)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_StrippedHorizontal	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Stripped Vertical.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::StrippedV)			)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_StrippedVertical	);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Wrapped.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedCandy)		)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_Wrapped			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Wrapped Fuse.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::WrappedFuse)		)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_WrappedFuse		);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Jelly Fish.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::JellyFish)			)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_JellyFish			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + StarLight.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::Starlight)			)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_StarLight			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + FireWork.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::FireWorkRocket)	)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_FireWork			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + BubbleGum.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::BubbleGum)			)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_BubbleGum			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}

											//	Frozen Candy + Popping Candy.
											{
												if (	(_Candies_[this->_Which_AT_]->g_ItemID() == STA_::enm_ItemID::FrozenCandy)		&&
														(_Candies_[this->_With_AT_]->g_ItemID() == STA_::enm_ItemID::PoppingCandy)		)
												{ 
													//	The Frozen Candy shouldn't be painting.
													if (	!_Candies_[this->_Which_AT_]->g_Fc_Is(1)	)
													{
														//	Say: These candies can't be crushed nor matched.
														{
															_Candies_[this->_Which_AT_]->s_Can(		2, false	);

															_Candies_[this->_Which_AT_]->s_Can(		3, false	);
															_Candies_[this->_With_AT_]->s_Can(		3, false	);
														}

														//	Then add these special candies to the controller.
														{
															_SpecialMixes_->AddWrapper(	_Candies_[this->_Which_AT_]			,
																						_Candies_[this->_With_AT_]			,
																						sMx::FrozenCandy_Popping			);
														}

														//	Little things.
														{
															_SpecialMix_ = true;
														}
													}
												}
											}
										}
									}
									
									

									//	- - - - - - - - - - - - - - - - - - - - - - - - - -

									//	Adding a frame.
									{
										if (	_With_AT_ != def::enm_Defines::_NOT_FOUND	)
										{
											this->AddFrame(		_Candies_[_With_AT_]->g_PositionPrp(1)	,
																_Candies_[_With_AT_]->g_PositionPrp(2)	,
																_Candies_[_With_AT_]->g_KindID()		,
																_Candies_[_With_AT_]					);

											//	Frame animation.
											if (	_SpecialMix_	)
											{
												this->ActivateLastFrame(0, false, _Selection_Frame::enm_FrameAnimation::SpecialMix);
												this->ActivateLastFrame(1, false, _Selection_Frame::enm_FrameAnimation::SpecialMix);
											}
											else
											{
												this->ActivateLastFrame(0, false);
												this->ActivateLastFrame(1, false);
											}
											
											//	Flag for 'Switched elements'.
											this->m_SwitchMade		= true;
										}							
									}

									//	Sound part.
									{
										this->_Sound_->Play(snd::SndSys::GoSwitch, 1);
									}
								}
								else
								{
									//	If candy not exist (The first one).
									//	Then delete that frame attached to it.
									this->ActivateLastFrame(0, true);
								}
							}
						}
					}
				}
			}	

			if (this->_AllDone_ && (!_Mouse_->g_Is(1)))
			{
				this->_IsFirstChoose_	= true;
				this->_AllDone_			= false;
			}
		}
	}


	inline void			AddFrame(double _xP, double _yP, int _KindID, TheCandy* _Linker_)
	{
		this->m_Frames.push_back(new _Selection_Frame(_xP, _yP, _KindID, _Linker_));
	}
	inline void			ActivateLastFrame(int OffSet, bool _Frame_Is_Lost_, int _AnimationID = _Selection_Frame::enm_FrameAnimation::Default)
	{
		//	Checking if OffSet is not out of range.
		if (	OffSet <= 0	)
		{
			OffSet = 0;
		}

		//	Actual activation.
		this->m_Frames[this->m_Frames.size() - (1 + OffSet)]->ActivateKind(_Frame_Is_Lost_, _AnimationID);
	}

	inline void			AnimateFrames()
	{
		for (	int i = 0; 
				i < this->m_Frames.size(); 
				++i	)
		{
			this->m_Frames[i]->AnimateFrame();



			if (this->m_Frames[i]->g_ColorPrp(4) <= 0.0)
			{
				tls::EraseElement<_Selection_Frame*>(this->m_Frames, i);
			}
		}
	}

//	-------------------------------------------
//				Drawing Functions
//	-------------------------------------------
public:
	inline void			Draw(	int What	)
	{
		//	Selection Frame.
		if (	enm_Draw::_SelectionFrame == What	)
		{	
			this->_What_Sprite_			= spr::enm_At::Board;
			this->_What_Kind_			= 1;
			this->_Container_Size_		= this->m_Frames.size();



			for (	int i = 0; i < this->_Container_Size_; ++i	)
			{
				//	Set position to the sprite.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setPosition(		tls::FixPos_X(	this->m_Frames[i]->g_SpritePosition(1), this->_Draw_->g_WorldBounds(1)	)	,
																												tls::FixPos_Y(	this->m_Frames[i]->g_SpritePosition(2), this->_Draw_->g_WorldBounds(2)	)	);

				//	Applying color properties.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setColor(	sf::Color(	this->m_Frames[i]->g_ColorPrp(1)	,
																													this->m_Frames[i]->g_ColorPrp(2)	,
																													this->m_Frames[i]->g_ColorPrp(3)	,
																													this->m_Frames[i]->g_ColorPrp(4)	)	);

				//	Then goes the shrinking model.
				_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_)->setScale(		this->m_Frames[i]->g_VisualPrp(1)		,
																											this->m_Frames[i]->g_VisualPrp(2)		);



				this->_Draw_->Draw(_Sprites_->g_Sprite(this->_What_Sprite_)->g_Sprites()->at(this->_What_Kind_));
			}
		}
	}

//	-------------------------------------------
//			Setters and Getters
//	-------------------------------------------
public:
	inline bool			SwitchMade()
	{
		return		this->m_SwitchMade;
	}
};	
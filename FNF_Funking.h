#pragma once

#include		"Tools_.h"
#include		"_MyIncludes_.h"
#include		"_Basics_KeyBoard.h"
#include		"_Basics_Mouse.h"
#include		"Camera.h"

#include		"FNF_ArrowController.h"
#include		"FNF_CharacterController.h"

#include		<sstream>
#include		<fstream>
#include		<string>



class		NotesRecorder
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Constants
//	-------------------------------------------
private:
	const int			$_ArrowsSize	= 4;
	const double		$_LongTime		= 0.3;

//	-------------------------------------------
//				Writing Variables
//	-------------------------------------------
private:
	std::fstream		File_;
	std::string			_Buffer_;

	bool			m_FileIsOpen		= false;
	int				m_IsRecordingNotes	= 2;		//	1: Notes, 2: Camera

//	-------------------------------------------
//				Set Variables
//	-------------------------------------------
private:
	int*			m_KeyBindings	= nullptr;
	int				m_InnerTime		= 0;




//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	NotesRecorder(const std::string _KeyBindings_)
	{
		this->m_KeyBindings		= new int[this->$_ArrowsSize];

		this->UpdateKeysBindings(_KeyBindings_);
	}

	~NotesRecorder()
	{
		//	Deleting KeyBindings.
		{
			if (this->m_KeyBindings != nullptr)
			{
				delete[] m_KeyBindings;
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			StartRecording(		_Basic_KeyBoard* _KeyBoard_)
	{
		for (	int i = 0; 
				i < this->$_ArrowsSize; 
				++i	)
		{
			if (	_KeyBoard_->g_Key(this->m_KeyBindings[i])->g_Is(2) 	)
			{
				int			_Direction_		= 0;
				double		_Time_			= _KeyBoard_->g_Key(this->m_KeyBindings[i])->g_PressedTime();
				double		_xMoveAmount_	= 350.0;
				double		_yMoveAmount_	= 150.0;



				//	Direction finder.
				switch (i)
				{
				case 0:
					_Direction_		= def::enm_Directions::Left;
					_xMoveAmount_	= _xMoveAmount_ * -1.0;
					break;

				case 1:
					_Direction_		= def::enm_Directions::Down;
					_yMoveAmount_	= _yMoveAmount_ * -1.0;
					break;

				case 2:
					_Direction_ = def::enm_Directions::Up;
					break;

				case 3:
					_Direction_ = def::enm_Directions::Right;
					break;
				}

				//	Writing on file.
				{
					switch (this->m_IsRecordingNotes)
					{
					case 1:		//	Notes...
						//	If the pressed time is less than certain constant
						//	means that the arrow is normal, otherwise meaning
						//	a long arrow.
						{
							if (_Time_ < this->$_LongTime)
							{
								this->File_ << (m_InnerTime - (_Time_ * GAME_LOOP_VALUE)) << "," << _Direction_ << "," << 0 << ",\n";
							}
							else
							{
								this->File_ << (m_InnerTime - (_Time_ * GAME_LOOP_VALUE)) << "," << _Direction_ << "," << _Time_ << ",\n";
							}
						}

						break;

					case 2:		//	Camera...
						//	Camera recorder.
						switch (2)
						{
						case def::enm_CameraSet::SmoothZoom:		//	SmoothZooooooom.
							this->File_ << def::enm_CameraSet::SmoothZoom << "," << (m_InnerTime - (_Time_ * GAME_LOOP_VALUE)) << "," << 1.2 << "," << 1.0 << "," << 2.5 << ",\n";
							break;

						case def::enm_CameraSet::xSmoothMove:	//	'x' axis movement.
							this->File_ << def::enm_CameraSet::xSmoothMove << "," << (m_InnerTime - (_Time_ * GAME_LOOP_VALUE)) << "," << _xMoveAmount_ << "," << 2.0 << ",\n";
							break;
						}
						break;
					}
				}
			}
		}



		++this->m_InnerTime;
	}
	inline void			SetRecorder(		bool& _IsRecording		)
	{
		const std::string		_R_FNF_NSc_			= "_Resources_\\FridayNightFunking\\NotesAndScripts\\";
		const std::string		_Unwind_			= "Unwind\\";
		const std::string		_What_				= "Camera.beat";	

		if (	!this->m_FileIsOpen	)
		{
			//	----------------------------------------::..
			File_.open(_R_FNF_NSc_ + _Unwind_ + _What_, std::fstream::out | std::fstream::trunc);
			//	-----------------------------------------------------------------------------------------------------

			if (!File_.is_open())
			{
				tls::SetColor(tls::Colors::_Red);
				std::cout << "Couldn't open data file. Recording went out.\n";
				tls::ResetColor();

				_IsRecording		= false;
				this->m_FileIsOpen	= false;
			}
			else
			{
				m_FileIsOpen	= true;
				std::cout << "Recording!";
			}
		}
		else
		{
			this->m_FileIsOpen = false;
			std::cout << "Stop Recording!";

			//	-------------------::..
			File_.close();
			//	-----------------------------------------------------



			//	Some method to erase the last character.
			//	Not the best, but I'll take it.
			{
				//	---------------------------::..
				File_.open(_R_FNF_NSc_ + _Unwind_ + _What_);
				//	------------------------------------------------------------::..

				this->_Buffer_.clear();
				
				std::stringstream	_Stream_;
				_Stream_ << this->File_.rdbuf();
				this->_Buffer_		= _Stream_.str();

				//	-------------------::..
				File_.close();
				//	-----------------------------------------------------

			



				//	----------------------------------------::..
				File_.open(_R_FNF_NSc_ + _Unwind_ + _What_, std::fstream::out | std::fstream::trunc);
				//	-----------------------------------------------------------------------------------------------------
					
				if (!this->_Buffer_.empty())
				{
					this->_Buffer_.pop_back();
				}
				this->File_ << this->_Buffer_;

				//	-------------------::..
				File_.close();
				//	-----------------------------------------------------
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline void		UpdateKeysBindings(const std::string _KeyBindings_)
	{
		//	--------------------------------------------------------------
		//		! Update this function when all keys has been added !
		//	--------------------------------------------------------------

		this->m_KeyBindings[0] = kyb::D;
		this->m_KeyBindings[1] = kyb::F;
		this->m_KeyBindings[2] = kyb::J;
		this->m_KeyBindings[3] = kyb::K;
	}
};

class	Funking
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Containers
//	-------------------------------------------
private:

//	-------------------------------------------
//					Controllers
//	-------------------------------------------
private:
	std::vector<_Controller_FnkArrows*>			m_Ctrl_Arrows;
	_Controller_FnkCharacters*					m_Ctrl_Characters;
	std::vector<CameraTrigger*>					m_CameraTriggers;

	NotesRecorder*				m_Recorder = nullptr;

//	-------------------------------------------
//			Positional and rel variables
//	-------------------------------------------
private:
	double				_Window_W		= 0.0,		_Window_H	= 0.0;

	double				_HitBlock_W		= 500.0,	_HitBlock_H = 75.0;
	double				_OffSet_HitBlock_yP = 150.0;


	double				m_ArrowSpeedFct	= 12.5;

//	-------------------------------------------
//				Controlling Variables
//	-------------------------------------------
private:
	bool				m_IsDownScrolling	= true;
	bool				m_IsRecording		= false;
	bool				m_HideCharacters	= false;

	bool				_FreezeBrain_		= false;

	int					Trigger			= 0;
	int					m_InnerTime		= 0;

//	-------------------------------------------
//				External variables
//	-------------------------------------------
private:
	SoundFactory*			_Sound_		= nullptr;
	_Basic_KeyBoard*		_KeyBoard_	= nullptr;
	Camera*					_Camera_	= nullptr;





//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructor
//	-------------------------------------------
public:
	Funking(	_Basic_KeyBoard* _KeyBoard_Ptr, SoundFactory* _Sound_Ptr	, 
				Camera* _Camera_Ptr, tls::Vec2<double> _Window_Boundaries		)	
	{
		this->_KeyBoard_	= _KeyBoard_Ptr;
		this->_Sound_		= _Sound_Ptr;
		this->_Camera_		= _Camera_Ptr;

		//	About window boundaries.
		this->_Window_W		= _Window_Boundaries.First;
		this->_Window_H		= _Window_Boundaries.Second;

		//	About recordings.
		this->m_Recorder	= new NotesRecorder("DFJK");
	}

	~Funking()
	{
		//	Deleting Recorder.
		{
			if (this->m_Recorder != nullptr)
			{
				delete this->m_Recorder;
			}
		}

		//	Deleting Arrows Controllers !
		{
			while (!this->m_Ctrl_Arrows.empty())
			{
				delete this->m_Ctrl_Arrows[0];
				this->m_Ctrl_Arrows.erase(this->m_Ctrl_Arrows.begin() + 0);
			}
		}

		//	Deleting Character Controller !
		{
			if (this->m_Ctrl_Characters != nullptr)
			{
				delete this->m_Ctrl_Characters;
			}
		}

		//	Deleting Camera Triggers.
		{
			while (!this->m_CameraTriggers.empty())
			{
				delete		this->m_CameraTriggers[0];
				this->m_CameraTriggers.erase(this->m_CameraTriggers.begin() + 0);
			}
		}
	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	inline void			DoArrows()
	{
		//	Arrows controllers.
		for (	int i = 0; 
				i < this->m_Ctrl_Arrows.size(); 
				++i	)
		{
			this->m_Ctrl_Arrows[i]->MoveArrows(this->m_Ctrl_Characters);

			this->m_Ctrl_Arrows[i]->Animate();
		}

		++m_InnerTime;
	}
	inline void			SingCharacters()
	{
		this->m_Ctrl_Characters->AnimateChatacters();
	}
	inline void			CameraSetAction()
	{
		for (	int i = 0; 
				i < this->m_CameraTriggers.size(); 
				++i	)
		{
			if (this->m_CameraTriggers[i]->_When_ == this->m_InnerTime)
			{
				//	Selecting which time of camera event it is.
				switch (this->m_CameraTriggers[i]->EventType)
				{
				case def::enm_CameraSet::SmoothZoom:
					this->_Camera_->SmoothZoom(	this->m_CameraTriggers[i]->Value1	, 
												this->m_CameraTriggers[i]->Value2	, 
												this->m_CameraTriggers[i]->Value3	);
					break;

				case def::enm_CameraSet::xSmoothMove:
					this->_Camera_->SmoothMove(	def::enm_CameraSet::xSmoothMove		, 
												this->m_CameraTriggers[i]->Value1	, 
												this->m_CameraTriggers[i]->Value2	);
					break;
				}
			}
		}
	}

//	-------------------------------------------
//				Loading Functions
//	-------------------------------------------
public:
	inline void			Ld_Funking()
	{
		//	Creating the arrow controllers.
		{
			double		_yPos_	= ((this->m_IsDownScrolling) ? (this->_HitBlock_H + this->_OffSet_HitBlock_yP) : (this->_Window_H - this->_OffSet_HitBlock_yP + this->_HitBlock_H));



			//	Creating the left side arrow controller.
			{
				this->m_Ctrl_Arrows.push_back( new _Controller_FnkArrows(	(-this->_Window_W - this->_HitBlock_W) / 2.0		,
																			_yPos_,	this->_Sound_, this->m_IsDownScrolling		)	);

				this->m_Ctrl_Arrows[0]->Ld_HitBlocks(	this->_HitBlock_W / 4.0							);
			}

			//	Creating the right side arrow controller.
			{
				this->m_Ctrl_Arrows.push_back( new _Controller_FnkArrows(	(this->_Window_W - this->_HitBlock_W) / 2.0			,
																			_yPos_, this->_Sound_, this->m_IsDownScrolling		)	);

				this->m_Ctrl_Arrows[1]->Ld_HitBlocks(	this->_HitBlock_W / 4.0							);
			}
		}

		//	Reading and creating the arrows.
		{
			//	For the left side.
			{			
				this->m_Ctrl_Arrows[0]->Ld_Arrows(	this->m_ArrowSpeedFct, 1	);
			}

			//	For the right side.
			{
				this->m_Ctrl_Arrows[1]->Ld_Arrows(	this->m_ArrowSpeedFct, 2	);
			}
		}

		//	Creating the character controller.
		{		
			this->m_Ctrl_Characters = new _Controller_FnkCharacters();



			//	Creating Cassette Girl Clone !
			{
				std::vector<int> _TimeStates_;

				_TimeStates_.emplace_back(14);	//	Iddle.
				_TimeStates_.emplace_back(14);	//	Left.
				_TimeStates_.emplace_back(10);	//	Down.
				_TimeStates_.emplace_back(14);	//	Up.
				_TimeStates_.emplace_back(14);	//	Right.

				this->m_Ctrl_Characters->AddCharacter(	-650, 750, false, 1.0								,
														FNF_::enm_Characters::CassetteGirlClone, _TimeStates_	,
														this->m_HideCharacters								);
			}

			//	Creating BoyFriend !
			{
				std::vector<int> _TimeStates_;

				_TimeStates_.emplace_back(14);	//	Iddle.
				_TimeStates_.emplace_back(14);	//	Left.
				_TimeStates_.emplace_back(14);	//	Down.
				_TimeStates_.emplace_back(14);	//	Up.
				_TimeStates_.emplace_back(14);	//	Right.

				this->m_Ctrl_Characters->AddCharacter(	300, 555, false, 0.8						,
														FNF_::enm_Characters::BoyFriend, _TimeStates_	, 
														this->m_HideCharacters						);
			}
		}

		//	Reading camera events...
		{
			//	----------------------------------------------------------------
			//		1 means is a zoom event, and 2 means a 'x' move event
			//				3 means a movement but along the 'y' axis
			//	----------------------------------------------------------------	

			//	Here is the actual reading.
			{
				//	Variables to be used.
				const std::string		_R_FNF_NSc_			= "_Resources_\\FridayNightFunking\\NotesAndScripts\\";
				const std::string		_Unwind_			= "Unwind\\";

				std::fstream		File_;
				std::string			_Buffer_;

				char*				_Reader_Character	= new char;





				//	-------------------::..
				File_.open(_R_FNF_NSc_ + _Unwind_ + "Camera.beat");
				//	-----------------------------------------------------

				if (	!File_.is_open()	)
				{
					tls::SetColor(	tls::Colors::_Red	);
					std::cout << "Couldn't open data file. Camera?\n";
					tls::ResetColor();
				}
				else
				{
					//	Reading each line.
					while (		!File_.eof()	)
					{
						//	Reinterpret _Buffer_ (Proccess of reading).
						{
							//	----------------------------------------------------------------
							//							..::Meanings::..
							//	----------------------------------------------------------------
							//		Example: 1,100,...
							//		1	The first number shows the event type (Zoom or Move).
							//		2	Then 100 (or any other number) means when to trigger it.
							//		3	... are other values depending on the event type.
							//	----------------------------------------------------------------

							const int		_Maximum_Tries_		= 11;
							int				_Counter_			= 0;

							int				_EventType_		= 0;
							int				_When_			= 0;

							double			_ZoomFrom_		= 0.0;
							double			_ZoomTo_		= 0.0;
							double			_ZoomTime_		= 0.0;

							double			_MoveAmount_	= 0.0;
							double			_MoveTime_		= 0.0;



							//	Read for 'EventType'.
							{		
								//	Getting the string from file.
								{
									File_.read(		_Reader_Character, 1	);

									while (	(_Counter_ < _Maximum_Tries_)	&&
											(*_Reader_Character != ','	)	)
									{					
										_Buffer_.push_back(*_Reader_Character);
										File_.read(_Reader_Character, 1);

										++_Counter_;
									}

									_Counter_ = 0;
								}

								//	Transform that string into a number.
								{
									_EventType_ = tls::StrToInt(_Buffer_, false);
								}

								//	Some touches.
								{
									_Buffer_.clear();
								}
							}

							//	Read for 'When'.
							{		
								//	Getting the string from file.
								{
									File_.read(		_Reader_Character, 1	);

									while (	(_Counter_ < _Maximum_Tries_)	&&
											(*_Reader_Character != ','	)	)
									{					
										_Buffer_.push_back(*_Reader_Character);
										File_.read(_Reader_Character, 1);

										++_Counter_;
									}

									_Counter_ = 0;
								}

								//	Transform that string into a number.
								{
									_When_ = tls::StrToInt(_Buffer_, false);
								}

								//	Some touches.
								{
									_Buffer_.clear();
								}
							}

							//	Depending on the camera event, reading will be different.
							{
								switch (_EventType_)
								{
								case 1:		//	Zoom event.
									//	Read for 'ZoomFrom'.
									{		
										//	Getting the string from file.
										{
											File_.read(		_Reader_Character, 1	);

											while (	(_Counter_ < _Maximum_Tries_)	&&
													(*_Reader_Character != ','	)	)
											{					
												_Buffer_.push_back(*_Reader_Character);
												File_.read(_Reader_Character, 1);

												++_Counter_;
											}

											_Counter_ = 0;
										}

										//	Transform that string into a number.
										{
											_ZoomFrom_	= tls::StrToDouble(_Buffer_);
										}

										//	Some touches.
										{
											_Buffer_.clear();
											_Counter_ = 0;
										}
									}

									//	Read for 'ZoomTo'.
									{		
										//	Getting the string from file.
										{
											File_.read(		_Reader_Character, 1	);

											while (	(_Counter_ < _Maximum_Tries_)	&&
													(*_Reader_Character != ','	)	)
											{					
												_Buffer_.push_back(*_Reader_Character);
												File_.read(_Reader_Character, 1);

												++_Counter_;
											}

											_Counter_ = 0;
										}

										//	Transform that string into a number.
										{
											_ZoomTo_ = tls::StrToDouble(_Buffer_);
										}

										//	Some touches.
										{
											_Buffer_.clear();
											_Counter_ = 0;
										}
									}

									//	Read for '_ZoomTime_'.
									{		
										//	Getting the string from file.
										{
											File_.read(		_Reader_Character, 1	);

											while (	(_Counter_ < _Maximum_Tries_)	&&
													(*_Reader_Character != ','	)	)
											{					
												_Buffer_.push_back(*_Reader_Character);
												File_.read(_Reader_Character, 1);

												++_Counter_;
											}

											_Counter_ = 0;
										}

										//	Transform that string into a number.
										{
											_ZoomTime_ = tls::StrToDouble(_Buffer_);
										}

										//	Some touches.
										{
											_Buffer_.clear();
											_Counter_ = 0;
										}
									}



									//	Once read, create trigger.
									{
										this->m_CameraTriggers.push_back(	new CameraTrigger(	_EventType_, _When_					, 
																								_ZoomFrom_, _ZoomTo_, _ZoomTime_	)	);
									


										File_.read(_Reader_Character, 1);
									}

									break;

								case 2:		//	'x' movement event.
									//	Read for 'MoveAmount'.
									{		
										//	Getting the string from file.
										{
											File_.read(		_Reader_Character, 1	);

											while (	(_Counter_ < _Maximum_Tries_)	&&
													(*_Reader_Character != ','	)	)
											{					
												_Buffer_.push_back(*_Reader_Character);
												File_.read(_Reader_Character, 1);

												++_Counter_;
											}

											_Counter_ = 0;
										}

										//	Transform that string into a number.
										{
											_MoveAmount_ = tls::StrToDouble(_Buffer_);
										}

										//	Some touches.
										{
											_Buffer_.clear();
											_Counter_ = 0;
										}
									}

									//	Read for 'MoveTime'.
									{		
										//	Getting the string from file.
										{
											File_.read(		_Reader_Character, 1	);

											while (	(_Counter_ < _Maximum_Tries_)	&&
													(*_Reader_Character != ','	)	)
											{					
												_Buffer_.push_back(*_Reader_Character);
												File_.read(_Reader_Character, 1);

												++_Counter_;
											}

											_Counter_ = 0;
										}

										//	Transform that string into a number.
										{
											_MoveTime_ = tls::StrToDouble(_Buffer_);
										}

										//	Some touches.
										{
											_Buffer_.clear();
											_Counter_ = 0;
										}
									}



									//	Once read, create trigger.
									{
										this->m_CameraTriggers.push_back(	new CameraTrigger(	_EventType_, _When_			, 
																								_MoveAmount_, _MoveTime_	)	);
									


										File_.read(_Reader_Character, 1);
									}

									break;
								}
							}

							
						}
					}
					






					//	-------------------::..
					File_.close();
					//	-----------------------------------------------------
				}

				//	-------------------::..
				//	Here you close the file...
				//	-----------------------------------------------------

				//	Deleting everything that has been used.
				{
					delete		_Reader_Character;
				}
			}
		}
	}

//	-------------------------------------------
//				External and events
//	-------------------------------------------
public:
	inline void			KeyBoardStuff()
	{
		//	Recording part.
		{
			//	KeyBoard event.
			if (	this->_KeyBoard_->g_Key(kyb::Key::R)->g_Is(2)	)
			{
				this->m_IsRecording = !this->m_IsRecording;

				this->m_Recorder->SetRecorder(this->m_IsRecording);
			}

			//	Is recording?
			if (this->m_IsRecording)
			{
				this->m_Recorder->StartRecording(this->_KeyBoard_);
			}
		}

		//	Freeze part.
		{
			if (this->_KeyBoard_->g_Key(kyb::Key::_Space_)->g_Is(2))
			{
				this->_FreezeBrain_ = !this->_FreezeBrain_;
			}
		}

		//	Zoom cap.
		{
			if (this->_KeyBoard_->g_Key(kyb::Key::D)->g_Is(2))
			{
				this->_Camera_->ZoomFocus(0.75, 3.0);
			}
			if (this->_KeyBoard_->g_Key(kyb::Key::K)->g_Is(2))
			{
				this->_Camera_->ZoomFocus(1.0, 3.0);
			}
		}
	}
	inline void			InstaRecord()
	{
		//	Only use when insta recording...
		//	A button already exists for recording.
		if (0)
		{
			++Trigger;

			if (this->Trigger == 1)
			{
				this->m_IsRecording = !this->m_IsRecording;
				this->m_Recorder->SetRecorder(this->m_IsRecording);



				//	Is recording?
				if (this->m_IsRecording)
				{
					this->m_Recorder->StartRecording(this->_KeyBoard_);
				}
			}
		}
	}

//	-------------------------------------------
//				Setters and Getters
//	-------------------------------------------
public:
	inline _Controller_FnkArrows*			g_Cntrl_FnkArrows(int _Which)
	{
		return this->m_Ctrl_Arrows[_Which];
	}
	inline _Controller_FnkCharacters*		g_Cntrl_FnkCharacter()
	{
		return this->m_Ctrl_Characters;
	}

	inline int				g_Cntrl_FnkArrows_Size()
	{
		return this->m_Ctrl_Arrows.size();
	}

	inline bool				g_FreezeBrain()
	{
		return		this->_FreezeBrain_;
	}
};
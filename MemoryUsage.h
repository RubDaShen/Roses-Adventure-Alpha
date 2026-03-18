#pragma once
#include	<iostream>
#include	"thyObject.h"

#ifdef	_WIN32
	#include	<windows.h>
	#include	<psapi.h>
#else
	#include	<unistd.h>
#endif




class		MemoryUsage__ : public thyObject
{
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Private side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//					Variables
//	-------------------------------------------
private:




//	-------------------------------------------
//				Private Functions
//	-------------------------------------------
private:
	inline size_t			fn_g_MemoryUsage()
	{
	#ifdef _WIN32
		PROCESS_MEMORY_COUNTERS_EX		pmc{};

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

		return pmc.PagefileUsage;
	#else
		long	rss = 0;
		FILE* fp = nullptr;



		if ((fp = fopen("/proc/self/statm", "r")) != nullptr)
		{
			unsigned long		size = 0.0, resident = 0.0, share = 0.0;
			unsigned long		text = 0.0, lib = 0.0, data = 0.0, dt = 0.0;

			if (fscanf(fp, "%*s%ld%ld%ld%ld%ld%ld%ld", &size, &resident, &share, &text, &lib, &data, &dt) == 7)
			{
				rss = resident * sysconf(_SC_PAGESIZE);
			}

			fclose(fp);
		}

		return static_cast<size_t>(rss);
	#endif
	}
	inline size_t			fn_g_TotalMemory()
	{
		MEMORYSTATUSEX		status{};

		status.dwLength		= sizeof(status);
		GlobalMemoryStatusEx(&status);

		return status.ullTotalPhys;
	}

//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
//						 Public side !
//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

//	-------------------------------------------
//			Constructors and Destructors
//	-------------------------------------------
public:
	MemoryUsage__(double _xP, double _yP) : thyObject(_xP, _yP, def::enm_ObjectType::Generic)
	{

	}

	~MemoryUsage__()
	{

	}

//	-------------------------------------------
//					Functions
//	-------------------------------------------
public:
	//	What is _Format_Byte: This is like which format size.
	//	Bytes, Kilobytes, Megabytes, Gigabytes, and so on.
	//	0 Represents bytes, 1 Kilobytes, 2 Megabytes, ...
	inline double		g_MemoryUsage(int _Format_Byte)
	{
		size_t		_MemUsage = this->fn_g_MemoryUsage();

		return (_MemUsage / (std::pow(1024, _Format_Byte)));
	}
	inline double		g_TotalMemory(int _Format_Byte)
	{
		size_t		_MemUsage = this->fn_g_TotalMemory();

		return (_MemUsage / (std::pow(1024, _Format_Byte)));
	}
};
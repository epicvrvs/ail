#include <ail/time.hpp>

#include <ctime>
#include <sstream>

#include <ail/environment.hpp>

#ifdef AIL_WINDOWS
#include <ail/windows.hpp>
#else
#include <sys/time.h>
#include <sys/times.h>
#endif


#include <iostream>

namespace ail
{
	stop_watch::stop_watch()
	{
		start();
	}

	void stop_watch::start()
	{
		beginning = milliseconds();
	}

	ullong stop_watch::stop()
	{
		ullong now = milliseconds();
		ullong output = now - beginning;
		beginning = now;
		return output;
	}

	ullong stop_watch::time()
	{
		ullong now = milliseconds();
		ullong output = now - beginning;
		return output;
	}

	ulong time()
	{
		return static_cast<ulong>(std::time(0));
	}

	ullong milliseconds()
	{
#ifdef AIL_WINDOWS
		::SYSTEMTIME system_time;
		::GetLocalTime(&system_time);
		ullong output = time() * 1000ull + system_time.wMilliseconds;
#else
		ullong output = time() * 1000ull;
		::timeval time_value;
		::gettimeofday(&time_value, 0);
		::tm * time_data = ::localtime(&time_value.tv_sec);
		output += static_cast<ullong>(time_value.tv_usec / 1000);
#endif
		return output;
	}

	std::string timestamp()
	{
		std::time_t current_time;
		std::time(&current_time);
		std::tm * pointer = std::localtime(&current_time);
		std::stringstream output;
		output.fill('0');
		output << (pointer->tm_year + 1900) << "-";
		output.width(2);
		output << (pointer->tm_mon + 1) << "-";
		output.width(2);
		output << pointer->tm_mday << " ";
		output.width(2);
		output << pointer->tm_hour << ":";
		output.width(2);
		output << pointer->tm_min << ":";
		output.width(2);
		output << pointer->tm_sec;
		return output.str();
	}

	
	ullong boot_time()
	{
#ifdef AIL_WINDOWS
#if (_WIN32_WINNT >= 0x0600)
		return static_cast<ullong>(::GetTickCount64());
#else
		return static_cast<ullong>(::GetTickCount());
#endif
#else
		tms tm;
		return static_cast<ullong>(::times(&tm));
#endif
	}
}

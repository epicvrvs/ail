#pragma once

#include <string>
#include <ail/environment.hpp>
#include <ail/windows.hpp>

#ifndef AIL_WINDOWS
#include <boost/thread/mutex.hpp>
#endif

namespace ail
{
	class dynamic_module
	{
	public:
		dynamic_module();
		~dynamic_module();
		bool load(std::string const & new_path);
		void unload();
		bool get_function(std::string const & name, void * & output);

	private:
		bool is_loaded;
		std::string path;

#ifdef AIL_WINDOWS
		::HMODULE module_handle;
#else
		void * module_handle;
		boost::mutex mutex;
#endif
	};
}

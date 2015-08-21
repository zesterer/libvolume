#ifndef LIBVOLUME_COMMON_IO_H
#define LIBVOLUME_COMMON_IO_H

//----LIBRARY----
#include "string"

namespace LibVolume
{
	namespace IO
	{
		enum OutputType
		{
			INFO,
			DEBUG,
			ERROR
		};

		void output(std::string message, OutputType type = OutputType::DEBUG);

		bool test(bool test, std::string label = "NULL Test", bool critical = false, bool silent = false);
	}
}

#endif

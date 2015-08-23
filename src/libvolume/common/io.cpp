//----STANDARD----
#include "iostream"

//----LOCAL----
#include "io.h"
#include "settings.h"

namespace LibVolume
{
	namespace IO
	{
		void output(std::string message, OutputType type)
		{
			std::string output_strings[] = {"OUTPUT", "DEBUG", "ERROR"};

			if ((LIBVOLUME_DEBUG_ENABLED && type == OutputType::DEBUG) || type != OutputType::DEBUG)
			{
				std::string output_tag = output_strings[type];

				std::cout << "[" << output_tag << "]: " << message << std::endl;
			}
		}

		bool test(bool test, std::string label, bool critical, bool silent)
		{
			if (test)
			{
				if (!silent)
					output(label + ": success", OutputType::DEBUG);
			}
			else
			{
				output(label + ": failure", OutputType::ERROR);

				if (critical)
				{
					output("Critical error, program closing.", OutputType::ERROR);
					exit(EXIT_FAILURE);
				}
			}

			return test;
		}
	}
}

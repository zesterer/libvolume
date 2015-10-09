#ifndef LIBVOLUME_WINDOW_WINDOW_H
#define LIBVOLUME_WINDOW_WINDOW_H

//----STANDARD----
#include "string"

//----LIBRARY----
#include "SFML/Graphics.hpp"

//----LOCAL----
#include "eventmanager.h"

namespace LibVolume
{
	namespace Window
	{
		class Window
		{
			public:
				sf::Window* sfml_window;

				EventManager event_manager;

				Window();
				void outputContextDebug();
				void activate(bool enable);
				void setTitle(std::string title);
				bool tick();
				void checkKeys();
		};
	}
}

#endif

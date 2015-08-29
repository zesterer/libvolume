#ifndef LIBVOLUME_WINDOW_WINDOW_H
#define LIBVOLUME_WINDOW_WINDOW_H

//----LIBRARY----
#include "SFML/Window.hpp"

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
				bool tick();
				void checkKeys();
		};
	}
}

#endif

#ifndef LIBVOLUME_WINDOW_WINDOW_H
#define LIBVOLUME_WINDOW_WINDOW_H

//----LIBRARY----
#include "SFML/Window.hpp"

namespace LibVolume
{
	namespace Window
	{
		class Window
		{
			public:
				sf::Window* sfml_window;
				
				Window();
				void outputContextDebug();
				void activate(bool enable);
				bool tick();
		};
	}
}

#endif

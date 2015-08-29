#ifndef LIBVOLUME_WINDOW_EVENTMANAGER_H
#define LIBVOLUME_WINDOW_EVENTMANAGER_H

//----STANDARD----
#include "vector"

namespace LibVolume
{
	namespace Window
	{
		struct WindowSizeState
		{
			public:
				int width;
				int height;
		};
		
		class EventManager
		{
			public:
				unsigned long long time;
				
				WindowSizeState window_size_state;
				
				void tick();
				WindowSizeState* getWindowSizeState();
		};
	}
}

#endif

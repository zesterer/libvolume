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

		struct KeyboardState
		{
			public:
				bool key_w;
				bool key_a;
				bool key_s;
				bool key_d;
				bool key_q;
				bool key_e;

				bool key_up;
				bool key_left;
				bool key_down;
				bool key_right;

				bool key_space;
				bool key_shift;
				bool key_enter;
		};

		class EventManager
		{
			public:
				unsigned long long time;

				WindowSizeState window_size_state;
				KeyboardState keyboard_state;

				void tick();
				WindowSizeState* getWindowSizeState();
				KeyboardState* getKeyboardState();
		};
	}
}

#endif

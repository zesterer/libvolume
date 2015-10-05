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
				bool key_w; bool key_w_pressed;
				bool key_a; bool key_a_pressed;
				bool key_s; bool key_s_pressed;
				bool key_d; bool key_d_pressed;
				bool key_q; bool key_q_pressed;
				bool key_e; bool key_e_pressed;

				bool key_f; bool key_f_pressed;

				bool key_up; bool key_up_pressed;
				bool key_left; bool key_left_pressed;
				bool key_down; bool key_down_pressed;
				bool key_right; bool key_right_pressed;

				bool key_space; bool key_space_pressed;
				bool key_shift; bool key_shift_pressed;
				bool key_enter; bool key_enter_pressed;
		};

		class EventManager
		{
			public:
				unsigned long long time;

				int window_width = 640;
				int window_height = 480;

				WindowSizeState window_size_state;
				KeyboardState keyboard_state;

				void tick();
				WindowSizeState* getWindowSizeState();
				KeyboardState* getKeyboardState();
		};
	}
}

#endif

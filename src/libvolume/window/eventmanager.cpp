//----LOCAL----
#include "eventmanager.h"

namespace LibVolume
{
	namespace Window
	{
		void EventManager::tick()
		{
			this->time ++;
		}

		WindowSizeState* EventManager::getWindowSizeState()
		{
			return &this->window_size_state;
		}

		KeyboardState* EventManager::getKeyboardState()
		{
				return &this->keyboard_state;
		}
	}
}

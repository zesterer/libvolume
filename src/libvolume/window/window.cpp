//----LOCAL----
#include "window.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Window
	{
		Window::Window()
		{
			sf::ContextSettings settings;
			settings.depthBits = 24;
			settings.stencilBits = 8;
			settings.antialiasingLevel = 4;
			settings.majorVersion = 3;
			settings.minorVersion = 3;
			settings.attributeFlags = sf::ContextSettings::Attribute::Core;

			//Set the correct event handler window size
			this->event_manager.window_size_state.width = 640;
			this->event_manager.window_size_state.height = 480;

			this->sfml_window = new sf::Window(sf::VideoMode(640, 480), "LibVolume OpenGL Test", sf::Style::Default, settings);
			this->sfml_window->setFramerateLimit(60);
			this->sfml_window->setMouseCursorVisible(false);
			this->sfml_window->setVerticalSyncEnabled(true);
		}

		void Window::setTitle(std::string title)
		{
			this->sfml_window->setTitle(title);
		}

		void Window::outputContextDebug()
		{
			sf::ContextSettings settings = this->sfml_window->getSettings();

			IO::output("Depth bits:" + std::to_string(settings.depthBits));
			IO::output("Stencil bits:" + std::to_string(settings.stencilBits));
			IO::output("Antialiasing level:" + std::to_string(settings.antialiasingLevel));
			IO::output("Version:" + std::to_string(settings.majorVersion) + "." + std::to_string(settings.minorVersion));
		}

		void Window::activate(bool enable)
		{
			this->sfml_window->setActive(enable);

			//Update the window size
			this->event_manager.window_size_state.width = this->sfml_window->getSize().x;
			this->event_manager.window_size_state.height = this->sfml_window->getSize().y;
		}

		bool Window::tick()
		{
			bool closed = false;

			sf::Event event;
			while (this->sfml_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					closed = true;
					IO::output("Closed the window");
				}
				else if (event.type == sf::Event::Resized)
				{
					this->event_manager.window_size_state.width = this->sfml_window->getSize().x;
					this->event_manager.window_size_state.height = this->sfml_window->getSize().y;
					IO::output("Resized or moved the window");
				}
			}

			this->checkKeys();

			this->sfml_window->display();

			return closed;
		}

		void Window::checkKeys()
		{
			this->event_manager.keyboard_state.key_w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			this->event_manager.keyboard_state.key_a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			this->event_manager.keyboard_state.key_s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			this->event_manager.keyboard_state.key_d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			this->event_manager.keyboard_state.key_q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
			this->event_manager.keyboard_state.key_e = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

			this->event_manager.keyboard_state.key_f = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
			this->event_manager.keyboard_state.key_l = sf::Keyboard::isKeyPressed(sf::Keyboard::L);

			this->event_manager.keyboard_state.key_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			this->event_manager.keyboard_state.key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			this->event_manager.keyboard_state.key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			this->event_manager.keyboard_state.key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

			this->event_manager.keyboard_state.key_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			this->event_manager.keyboard_state.key_shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
			this->event_manager.keyboard_state.key_enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
		}
	}
}

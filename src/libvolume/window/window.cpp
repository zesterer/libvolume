//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

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
			
			this->sfml_window = new sf::Window(sf::VideoMode(800, 600), "LibVolume OpenGL Test", sf::Style::Default, settings);
			this->sfml_window->setVerticalSyncEnabled(true);
			
			//Enable GLBinding
			IO::output("Initialising GLBinding");
			glbinding::Binding::initialize();
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
					IO::output("Resized or moved the window");
				}
			}
			
			this->sfml_window->display();
			
			return closed;
		}
	}
}

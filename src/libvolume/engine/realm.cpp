//----LOCAL----
#include "realm.h"
#include "common/io.h"
#include "render/rendertarget.h"

namespace LibVolume
{
	namespace Engine
	{
		Realm::Realm()
		{
			IO::output("Created realm");
			
			this->renderer.camera = &this->camera;
		}
		
		void Realm::tick()
		{
			//Tick the camera
			this->camera.tick((float)this->event_manager->window_size_state.width / (float)this->event_manager->window_size_state.height);
			
			//Loop through the realm objects
			for (unsigned int count = 0; count < this->objects.size(); count ++)
			{
				Object* object = this->objects[count];
				
				//Tick the object
				object->tick();
				
				//IO::output("Ticked an object");
			}
			
			this->postTick();
		}
		
		void Realm::postTick()
		{
			//Time in seconds
			this->time += 1.0;
		}
		
		void Realm::render()
		{
			this->renderer.preRender();
			
			//Loop through the realm objects
			for (unsigned int count = 0; count < this->objects.size(); count ++)
			{
				Object* object = this->objects[count];
				
				//If the object is renderable, render it using the renderer
				if (object->renderable)
				{
					this->renderer.renderTarget(dynamic_cast<Render::RenderTarget*>(object));
				}
			}
		}
		
		void Realm::setEventManager(Window::EventManager* event_manager)
		{
			this->event_manager = event_manager;
			this->renderer.setEventManager(event_manager);
		}
	}
}

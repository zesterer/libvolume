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
			this->renderer.light_list = &this->light_list;
		}

		void Realm::tick()
		{
			//Tick the camera
			int w, h;
			w = this->event_manager->window_size_state.width;
			h = this->event_manager->window_size_state.height;
			if (w <= 0 || h <= 0)
				this->camera.tick(1.0f);
			else
				this->camera.tick((float)w / (float)h);

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
			this->renderer.preRender(Render::RenderMode::PreDeferred);

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

			this->renderer.postRender(Render::RenderMode::PostDeferred);
		}

		void Realm::setEventManager(Window::EventManager* event_manager)
		{
			this->event_manager = event_manager;
			this->renderer.setEventManager(event_manager);
		}
	}
}

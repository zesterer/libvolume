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
				object->parent = this;

				//Tick the object both as 'whatever it is', and as a base object.
				object->tick();

				//Delete the object if it needs deleting
				if (object->timeout == 0)
				{
					this->removeObject(*object);
					delete object;
				}

				//IO::output("Ticked an object");
			}

			this->postTick();
		}

		void Realm::postTick()
		{
			//Tick the renderer
			this->renderer.tick();

			//Time in seconds
			this->time += 1;
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

			this->renderer.postRender(Render::RenderMode::PostDeferred, this->background_colour);
		}

		void Realm::linkTo(Window::Window& window)
		{
			this->event_manager = &window.event_manager;
			this->renderer.linkTo(window);
		}

		void Realm::addObject(Object& object)
		{
			this->objects.push_back(&object);
		}

		void Realm::removeObject(Object& object)
		{
			auto it = std::find(this->objects.begin(), this->objects.end(), &object);

			if (it != this->objects.end())
			{
				using std::swap;

				std::swap(*it, this->objects.back());
				this->objects.pop_back();
			}
			//Else, the object doesn't exist in the realm
		}

		void Realm::addLight(Render::Structures::Light& light)
		{
			this->light_list.push_back(&light);
		}
	}
}

#ifndef LIBVOLUME_RENDER_SCENE_H
#define LIBVOLUME_RENDER_SCENE_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "render/renderer.h"
#include "object.h"
#include "camera.h"
#include "window/eventmanager.h"
#include "render/structures/light.h"
#include "window/window.h"

namespace LibVolume
{
	namespace Engine
	{
		class Realm
		{
			public:
				long time;

				Camera camera;

				Render::Renderer renderer;
				Window::EventManager* event_manager;

				glm::vec3 background_colour = glm::vec3(1.0, 1.0, 1.0);

				//Light list
				std::vector<Render::Structures::Light*> light_list;

				std::vector<Object*> objects;

				Realm();
				void tick();
				void postTick();
				void render();
				void linkTo(Window::Window& window);
				void addObject(Object& object);
				void removeObject(Object& object);
				void addLight(Render::Structures::Light& light);
		};
	}
}

#endif

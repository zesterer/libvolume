#ifndef LIBVOLUME_RENDER_SCENE_H
#define LIBVOLUME_RENDER_SCENE_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "render/renderer.h"
#include "object.h"
#include "camera.h"

namespace LibVolume
{
	namespace Engine
	{
		class Realm
		{
			public:
				double time;
				
				Camera camera;
				
				Render::Renderer renderer;
				
				std::vector<Object*> objects;
			
				Realm();
				void tick();
				void postTick();
				void render();
		};
	}
}

#endif

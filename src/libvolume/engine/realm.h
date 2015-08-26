#ifndef LIBVOLUME_RENDER_SCENE_H
#define LIBVOLUME_RENDER_SCENE_H

//----LOCAL----
#include "render/renderer.h"

namespace LibVolume
{
	namespace Engine
	{
		class Realm
		{
			public:
				double time;
				
				Render::Renderer renderer;
			
				Realm();
				void tick();
				void render();
		};
	}
}

#endif

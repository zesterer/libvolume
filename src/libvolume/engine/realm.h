#ifndef LIBVOLUME_RENDER_SCENE_H
#define LIBVOLUME_RENDER_SCENE_H

namespace LibVolume
{
	namespace Engine
	{
		class Realm
		{
			public:
				double time;
			
				Realm();
				void tick();
				void preRender();
				void render();
		};
	}
}

#endif

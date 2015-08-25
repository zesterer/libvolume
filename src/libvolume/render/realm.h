#ifndef LIBVOLUME_RENDER_SCENE_H
#define LIBVOLUME_RENDER_SCENE_H

namespace LibVolume
{
	namespace Render
	{
		class Realm
		{
			double time;
			
			Realm();
			void tick();
		};
	}
}

#endif

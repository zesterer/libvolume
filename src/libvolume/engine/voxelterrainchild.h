#ifndef LIBVOLUME_ENGINE_VOXELTERRAINCHILD_H
#define LIBVOLUME_ENGINE_VOXELTERRAINCHILD_H

//----LOCAL----
#include "voxelactor.h"

namespace LibVolume
{
	namespace Engine
	{
		class VoxelTerrainChild : public VoxelActor
		{
			public:
				glm::ivec3 pos = glm::ivec3(0, 0, 0);

				VoxelTerrainChild(glm::ivec3 size);
		};
	}
}

#endif

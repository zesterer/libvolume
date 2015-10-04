#ifndef LIBVOLUME_ENGINE_VOXELTERRAINCHILD_H
#define LIBVOLUME_ENGINE_VOXELTERRAINCHILD_H

//----LOCAL----
#include "voxelactor.h"

namespace LibVolume
{
	namespace Engine
	{
		//Forward decleration of VoxelTerrain
		class VoxelTerrain;

		class VoxelTerrainChild : public VoxelActor
		{
			public:
				glm::ivec3 location = glm::ivec3(0, 0, 0);
				VoxelTerrain* parent = nullptr;

				VoxelTerrainChild(glm::ivec3 size);
				Data::Voxel* getAt(glm::ivec3 pos) override;
		};
	}
}

#endif

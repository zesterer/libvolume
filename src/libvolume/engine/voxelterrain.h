#ifndef LIBVOLUME_ENGINE_VOXELTERRAIN_H
#define LIBVOLUME_ENGINE_VOXELTERRAIN_H

//----LOCAL----
#include "voxelactor.h"
#include "data/voxelcluster.h"
#include "engine/entity.h"

namespace LibVolume
{
	namespace Engine
	{
		class VoxelTerrain : public Data::VoxelCluster, public Engine::Entity
		{
			public:
				bool loadAt(glm::ivec3 pos) override;
		};
	}
}

#endif

#ifndef LIBVOLUME_ENGINE_VOXELTERRAIN_H
#define LIBVOLUME_ENGINE_VOXELTERRAIN_H

//----LOCAL----
#include "voxelactor.h"
#include "data/voxelcluster.h"
#include "engine/entity.h"
#include "render/rendertarget.h"
#include "voxelterrainchild.h"

namespace LibVolume
{
	namespace Engine
	{
		class VoxelTerrain : public Data::VoxelCluster, public Engine::Entity, public Render::RenderTarget
		{
			public:
				//An empty voxel, used for meshing
				Data::Voxel empty;

				VoxelTerrain(glm::ivec3 child_size);
				bool loadAt(glm::ivec3 pos) override;
				VoxelTerrainChild* getAt(glm::ivec3 pos) override;
				Data::Voxel* getVoxelAt(glm::ivec3 pos);
				virtual void tick() const;
		};
	}
}

#endif

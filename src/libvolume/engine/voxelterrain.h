#ifndef LIBVOLUME_ENGINE_VOXELTERRAIN_H
#define LIBVOLUME_ENGINE_VOXELTERRAIN_H

//----LOCAL----
#include "voxelactor.h"
#include "data/voxelcluster.h"
#include "engine/entity.h"
#include "render/rendertarget.h"

namespace LibVolume
{
	namespace Engine
	{
		class VoxelTerrain : public Data::VoxelCluster, public Engine::Entity, public Render::RenderTarget
		{
			public:
				VoxelTerrain(glm::ivec3 child_size);
				bool loadAt(glm::ivec3 pos) override;
				VoxelActor* getAt(glm::ivec3 pos) override;
				void tick() override;
		};
	}
}

#endif

//----LOCAL----
#include "voxelterrainchild.h"
#include "voxelterrain.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		VoxelTerrainChild::VoxelTerrainChild(glm::ivec3 size) : VoxelActor(size)
		{

		}

		Data::Voxel* VoxelTerrainChild::getAt(glm::ivec3 pos)
		{
			if (pos.x < 0 || pos.x >= this->size.x || pos.y < 0 || pos.y >= this->size.y || pos.z < 0 || pos.z >= this->size.z)
			{
				if (this->parent == nullptr)
					return &this->empty;
				else
					return this->parent->getVoxelAt(this->location + pos);
			}

			return &this->voxels[this->size.y * this->size.z * pos.x + this->size.z * pos.y + pos.z];
		}
	}
}

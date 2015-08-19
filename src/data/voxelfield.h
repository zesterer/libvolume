#ifndef LIBVOLUME_DATA_VOXELFIELD_H
#define LIBVOLUME_DATA_VOXELFIELD_H

//----STANDARD----
#include "vector"

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

//----LOCAL----
#include "voxel.h"

namespace LibVolume
{
	namespace Data
	{
		template <typename MetaType>
		class VoxelField
		{
			public:
				//The field dimensions
				glm::ivec3 size;
			
				//The voxel data
				std::vector<Voxel<MetaType>> voxels;
				
				//An empty voxel, used for meshing
				Voxel<MetaType> empty;
				
				//Find the voxel at the specified position within the field
				Voxel<MetaType>* getAt(glm::ivec3 pos);
		};
	}
}

#endif

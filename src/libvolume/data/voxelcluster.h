#ifndef LIBVOLUME_DATA_VOXELCLUSTER_H
#define LIBVOLUME_DATA_VOXELCLUSTER_H

//----STANDARD----
#include "unordered_map"

//----LOCAL----
#include "voxelfield.h"

namespace LibVolume
{
	namespace Data
	{
		struct MapKey
		{
			public:
				int  x, y, z;

				bool operator==(const MapKey &other) const;
		};

		struct KeyHasher
		{
			public:
				std::size_t operator()(const MapKey& k) const;
		};

		class VoxelCluster
		{
			public:
				glm::ivec3 child_size;
				std::unordered_map<MapKey, VoxelField*, KeyHasher> children;

				VoxelCluster(glm::ivec3 child_size);
				VoxelField* getAt(glm::ivec3 pos);
				virtual bool loadAt(glm::ivec3 pos);

				MapKey vecToKey(glm::ivec3 vec);
		};
	}
}

#endif

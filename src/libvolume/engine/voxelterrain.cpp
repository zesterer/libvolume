//----LOCAL----
#include "voxelterrain.h"
#include "io.h"

namespace LibVolume
{
	namespace Engine
	{
		bool VoxelTerrain::loadAt(glm::ivec3 pos)
		{
			if (this->children.count(this->vecToKey(pos)) > 0)
				return false;

			Data::VoxelField* tmp = dynamic_cast<Data::VoxelField*>(new VoxelActor(this->child_size));
			this->children.insert({this->vecToKey(pos), tmp});

			IO::output("Loaded region!");

			return true;
		}
	}
}

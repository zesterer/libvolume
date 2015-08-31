//----LOCAL----
#include "data/voxelfield.h"
#include "actor.h"

namespace LibVolume
{
	namespace Engine
	{
		class VoxelActor : public Data::VoxelField, public Actor
		{
			public:
				VoxelActor(glm::ivec3 size);
		};
	}
}

#ifndef LIBVOLUME_ENGINE_ENTITY_H
#define LIBVOLUME_ENGINE_ENTITY_H

namespace LibVolume
{
	namespace Engine
	{
		enum EntityType
		{
			VoxelBody,
			MeshBody,
			MetaObject,
			Particle
		};
		
		class Entity
		{
			public:
				EntityType type;
		};
	}
}

#endif

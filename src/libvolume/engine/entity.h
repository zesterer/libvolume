#ifndef LIBVOLUME_ENGINE_ENTITY_H
#define LIBVOLUME_ENGINE_ENTITY_H

//----LOCAL----
#include "physics/state.h"
#include "object.h"

namespace LibVolume
{
	namespace Engine
	{
		enum EntityType
		{
			Point,
			MeshBody,
			VoxelBody
		};

		//The general entity class
		class Entity : public Object
		{
			public:
				Physics::DynamicState state;
				EntityType type;

				void* metadata;

				Entity();
				void tick() override;
				virtual void collide(Entity& entity);
		};
	}
}

#endif

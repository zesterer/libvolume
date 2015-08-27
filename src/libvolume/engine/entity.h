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
				EntityType type;
				
				void* metadata;
				
				Entity();
		};
		
		//Used for static entities (e.g: waypoint markers, static particles, etc.)
		class StaticEntity : public Entity
		{
			public:
				Physics::PointState state;
				
				StaticEntity();
		};
		
		//Used for static body entities (e.g: terrain, metaobjects, etc.)
		class StaticBodyEntity : public Entity
		{
			public:
				Physics::BodyState state;
				
				StaticBodyEntity();
		};
		
		//Used for dynamic body entities (e.g: moving voxel bodies, moving characters, etc.)
		class DynamicBodyEntity : public Entity
		{
			public:
				Physics::DynamicState state;
				
				DynamicBodyEntity();
		};
	}
}

#endif

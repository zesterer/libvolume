#ifndef LIBVOLUME_ENGINE_OBJECT_H
#define LIBVOLUME_ENGINE_OBJECT_H

namespace LibVolume
{
	namespace Engine
	{
		//Forward declaration of Realm
		class Realm;

		//Type
		enum ObjectType
		{
			ObjectObject,
			EntityObject,
			ActorObject,
			VoxelActorObject,
			VoxelTerrainObject,
		};

		//Anything that inherits this class can be stored in a realm's object std::vector
		//And also has the ability to tick
		class Object
		{
			public:
				//This property should only be true if the object inherits
				//from the 'Render::RenderTarget' class.
				bool renderable = false;
				//This property should only be true if the object inherits
				//from the 'Entity' class.
				bool can_collide = false;

				ObjectType objecttype = ObjectType::ObjectObject;

				long timeout = -1;

				Realm* parent = nullptr;

				Object();
				virtual ~Object();
				virtual void tick();
		};
	}
}

#endif

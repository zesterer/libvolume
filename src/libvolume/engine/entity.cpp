//----LOCAL----
#include "entity.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		Entity::Entity()
		{
			this->can_collide = true;
		}

		void Entity::tick()
		{
			((Entity*)this)->state.tick();
			Object::tick();
		}

		void Entity::collide(Entity& other)
		{
			//Do nothing yet
		}
	}
}

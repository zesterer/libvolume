//----LOCAL----
#include "entity.h"

namespace LibVolume
{
	namespace Engine
	{
		Entity::Entity()
		{
			
		}
		
		void Entity::tick()
		{
			this->state.tick();
		}
	}
}

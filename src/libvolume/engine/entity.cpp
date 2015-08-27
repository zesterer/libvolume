//----LOCAL----
#include "entity.h"
#include "common/io.h"

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

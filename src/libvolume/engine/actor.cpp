//----LOCAL----
#include "actor.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		Actor::Actor()
		{
			this->renderable = true;
			this->rendertype = Render::RenderType::Actor;
			
			IO::output("Created Actor");
		}
		
		void Actor::tick()
		{
			Entity::tick();
		}
	}
}

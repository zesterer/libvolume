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
			this->state.orientation = glm::quat(glm::vec3(0.0, 0.03, 0.0)) * this->state.orientation;
			
			Entity::tick();
		}
	}
}

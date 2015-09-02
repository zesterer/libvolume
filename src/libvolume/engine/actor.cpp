//----LOCAL----
#include "actor.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		Actor::Actor(Render::Structures::Mesh* mesh) : Render::MeshedObject(mesh)
		{
			this->renderable = true;
			this->rendertype = Render::RenderType::Actor;

			IO::output("Created Actor");
		}

		void Actor::tick()
		{
			this->mesh_state.tick();
			Entity::tick();
		}
	}
}

//----LOCAL----
#include "actor.h"

namespace LibVolume
{
	namespace Engine
	{
		Actor::Actor(Render::Structures::Mesh* mesh) : Render::MeshedObject(mesh)
		{
			this->renderable = true;
			this->rendertype = Render::RenderType::Actor;
		}

		void Actor::tick() const
		{
			((Actor*)this)->mesh_state.tick();
			Entity::tick();
		}
	}
}

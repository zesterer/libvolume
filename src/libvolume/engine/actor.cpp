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
			this->objecttype = ObjectType::ActorObject;
		}

		void Actor::tick()
		{
			((Actor*)this)->mesh_state.tick();
			Entity::tick();
		}
	}
}

#ifndef LIBVOLUME_RENDER_MESHEDOBJECT_H
#define LIBVOLUME_RENDER_MESHEDOBJECT_H

//----LOCAL----
#include "structures/mesh.h"
#include "engine/physics/state.h"

namespace LibVolume
{
	namespace Render
	{
		class MeshedObject
		{
			public:
				Structures::Mesh* mesh;
				Engine::Physics::DynamicState mesh_state;

				MeshedObject();
		};
	}
}

#endif

#ifndef LIBVOLUME_ENGINE_ACTOR_H
#define LIBVOLUME_ENGINE_ACTOR_H

//----LOCAL----
#include "render/structures/mesh.h"
#include "render/rendertarget.h"
#include "entity.h"

namespace LibVolume
{
	namespace Engine
	{
		class Actor : public Render::RenderTarget, public Entity
		{
			public:
				Render::Structures::Mesh mesh;
				
				Actor();
				virtual void tick() override;
		};
	}
}

#endif

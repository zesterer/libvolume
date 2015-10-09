#ifndef LIBVOLUME_ENGINE_ACTOR_H
#define LIBVOLUME_ENGINE_ACTOR_H

//----LOCAL----
#include "render/meshedobject.h"
#include "render/rendertarget.h"
#include "entity.h"

namespace LibVolume
{
	namespace Engine
	{
		class Actor : public Render::RenderTarget, public Entity, public Render::MeshedObject
		{
			public:
				Actor(Render::Structures::Mesh* mesh = nullptr);
				void tick() override;
		};
	}
}

#endif

#ifndef LIBVOLUME_RENDER_RENDERER_H
#define LIBVOLUME_RENDER_RENDERER_H

//----LOCAL----
#include "rendertarget.h"
#include "structures/shader.h"
#include "engine/actor.h"
#include "engine/camera.h"

namespace LibVolume
{
	namespace Render
	{	
		class Renderer
		{
			public:
				Structures::Shader* std_shader;
				Structures::Shader* post_shader;
				
				Engine::Camera* camera;
				
				Renderer();
				void preRender();
				void renderTarget(RenderTarget* target);
				void renderActor(Engine::Actor* actor);
		};
	}
}

#endif

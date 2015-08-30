#ifndef LIBVOLUME_RENDER_RENDERER_H
#define LIBVOLUME_RENDER_RENDERER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "rendertarget.h"
#include "structures/shader.h"
#include "engine/actor.h"
#include "engine/camera.h"
#include "window/eventmanager.h"
#include "structures/gbuffer.h"
#include "structures/light.h"

namespace LibVolume
{
	namespace Render
	{
		enum RenderMode
		{
			PreDeferred,
			PostDeferred,
			SinglePass,
			PostProcess
		};

		class Renderer
		{
			public:
				Window::EventManager* event_manager;

				Structures::Shader* std_shader;
				Structures::Shader* predeferred_shader;
				Structures::Shader* postdeferred_shader;
				Structures::Shader* post_shader;

				//Deferred shading
				Structures::GBuffer gbuffer;

				//Screen quad
				gl::GLuint gl_quad_id;

				//Light list
				std::vector<Structures::Light*>* light_list;

				Engine::Camera* camera;

				Renderer();
				void preRender(RenderMode render_mode);
				void postRender(RenderMode render_mode);
				void renderTarget(RenderTarget* target);
				void renderActor(Engine::Actor* actor);
				void setEventManager(Window::EventManager* event_manager);
				void bufferScreenQuad();
				void assignLights();
		};
	}
}

#endif

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "renderer.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Render
	{
		Renderer::Renderer()
		{
			IO::output("Created renderer");
		}
		
		void Renderer::preRender()
		{
			//Enable backface culling
			gl::glEnable(gl::GL_CULL_FACE);

			//Enable the depth buffer
			gl::glEnable(gl::GL_DEPTH_TEST);
			gl::glDepthFunc(gl::GL_LESS);

			// Render to our framebuffer
			//gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->render_buffer->gl_id);
			//gl::glViewport(0, 0, 640 * 1.4, 480 * 1.4);

			//Blank the screen
			gl::glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
		}
		
		void Renderer::renderTarget(RenderTarget* target)
		{
			//Render a render target
			IO::output("Rendered a target");
		}
	}
}

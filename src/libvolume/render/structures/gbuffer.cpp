//----LOCAL----
#include "gbuffer.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			void GBuffer::init(int width, int height)
			{
				this->width = width;
				this->height = height;

				//Delete just incase we're re-initiating
				if (this->initiated)
				{
					gl::glDeleteFramebuffers(1, &this->gbuffer_id);
				}

				//Create the GBuffer
				gl::glGenFramebuffers(1, &this->gbuffer_id);
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gbuffer_id);

				//Create the relevant textures for storing data ready for deferred shading

				//Position texture
				gl::glGenTextures(1, &this->position_id);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->position_id);
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGBA32F, this->width, this->height, 0, gl::GL_RGB, gl::GL_FLOAT, NULL);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT0, gl::GL_TEXTURE_2D, this->position_id, 0);

				//Normal texture
				gl::glGenTextures(1, &this->normal_id);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->normal_id);
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGB16F, this->width, this->height, 0, gl::GL_RGB, gl::GL_FLOAT, NULL);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT1, gl::GL_TEXTURE_2D, this->normal_id, 0);

				//Colour texture
				gl::glGenTextures(1, &this->colour_id);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->colour_id);
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGBA16F, this->width, this->height, 0, gl::GL_RGBA, gl::GL_FLOAT, NULL);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT2, gl::GL_TEXTURE_2D, this->colour_id, 0);

				//Material texture
				//TODO: Doesn't actually exist yet since no material data input
				gl::glGenTextures(1, &this->material_id);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->colour_id);
				gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLuint)gl::GL_RGB, this->width, this->height, 0, gl::GL_RGB, gl::GL_FLOAT, NULL);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_NEAREST);
				gl::glFramebufferTexture2D(gl::GL_FRAMEBUFFER, gl::GL_COLOR_ATTACHMENT3, gl::GL_TEXTURE_2D, this->material_id, 0);

				//Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
				gl::GLenum attachments[4] = {gl::GL_COLOR_ATTACHMENT0, gl::GL_COLOR_ATTACHMENT1, gl::GL_COLOR_ATTACHMENT2, gl::GL_COLOR_ATTACHMENT3};
				gl::glDrawBuffers(4, attachments);

				//Create the depth buffer and attach it
				gl::glGenRenderbuffers(1, &this->render_depth_id);
				gl::glBindRenderbuffer(gl::GL_RENDERBUFFER, this->render_depth_id);
				gl::glRenderbufferStorage(gl::GL_RENDERBUFFER, gl::GL_DEPTH_COMPONENT32F, this->width, this->height);
				gl::glFramebufferRenderbuffer(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, gl::GL_RENDERBUFFER, this->render_depth_id);

				this->initiated = true;
			}

			void GBuffer::tick(int width, int height)
			{
				if (width != this->width || height != this->height || this->initiated == false)
					this->init(width, height);
			}
		}
	}
}


















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

			//Enable GLBinding
			IO::output("Initialising GLBinding");
			glbinding::Binding::initialize();

			this->std_shader = new Structures::Shader();
			this->std_shader->loadFromFiles("../libvolume/shaders/std-vertex-shader.glsl", "../libvolume/shaders/std-fragment-shader.glsl");

			this->predeferred_shader = new Structures::Shader();
			this->predeferred_shader->loadFromFiles("../libvolume/shaders/predeferred-vertex-shader.glsl", "../libvolume/shaders/predeferred-fragment-shader.glsl");

			this->postdeferred_shader = new Structures::Shader();
			this->postdeferred_shader->loadFromFiles("../libvolume/shaders/postdeferred-vertex-shader.glsl", "../libvolume/shaders/postdeferred-fragment-shader.glsl");

			this->bufferScreenQuad();
			this->gbuffer.init();
		}

		void Renderer::preRender(RenderMode render_mode)
		{
			//Enable backface culling
			gl::glEnable(gl::GL_CULL_FACE);

			//Enable the depth buffer
			gl::glEnable(gl::GL_DEPTH_TEST);
			gl::glDepthFunc(gl::GL_LESS);

			// Render to our framebuffer
			if (render_mode == RenderMode::PreDeferred)
			{
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gbuffer.gbuffer_id);
				gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
			}
			else if (render_mode == RenderMode::PostDeferred)
			{
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
				gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
			}
			else
			{
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
				gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
			}

			//Enable the shader
			if (render_mode == RenderMode::PreDeferred)
			{
				this->predeferred_shader->enable();
			}
			else if (render_mode == RenderMode::PostDeferred)
			{
				this->postdeferred_shader->enable();
			}
			else
			{
				this->std_shader->enable();
			}

			//Blank the screen
			gl::glClearColor(0.7f, 0.7f, 0.9f, 0.0f);

			if (render_mode == RenderMode::PostDeferred)
			{
				gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
			}
			else
			{
				gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
			}
		}

		void Renderer::renderTarget(RenderTarget* target)
		{
			//Render a render target
			//IO::output("Rendering target...");

			//TODO
			if (target->rendertype == RenderType::Actor || true)
			{
				//IO::output("Target is an instance of Engine::Actor");
				this->renderActor(dynamic_cast<Engine::Actor*>(target));
			}
			else if(target->rendertype == RenderType::None)
			{
				//IO::output("Target isn't an actor");
			}
		}

		void Renderer::renderActor(Engine::Actor* actor)
		{
			//IO::output("Rendering Actor...");

			//Buffer the mesh if it's not already been done
			if (!actor->mesh.buffered)
				actor->mesh.buffer();

			//Bind the vertex buffer
			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, actor->mesh.gl_id);

			//Tell the shaders what different parts of the buffer mean using the above array
			//What is the buffer array composed of?
			int length[] = {sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec2), sizeof(glm::vec3)};
			gl::GLuint offset = 0;
			for (gl::GLuint array_id = 0; array_id < 4; array_id ++)
			{
				gl::glEnableVertexAttribArray(array_id);
				gl::glVertexAttribPointer(array_id, length[array_id] / sizeof(gl::GLfloat), gl::GL_FLOAT, gl::GL_FALSE, sizeof(Structures::Vertex), (void*)(unsigned long)offset);
				offset += length[array_id];
			}

			//Find the uniform camera perspective matrix, then assign it
			gl::GLuint perspective_matrix_id = gl::glGetUniformLocation(this->predeferred_shader->gl_id, "PERSPECTIVE_MATRIX");
			gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &this->camera->perspective_matrix[0][0]);

			//Find the uniform camera matrix, then assign it
			gl::GLuint camera_matrix_id = gl::glGetUniformLocation(this->predeferred_shader->gl_id, "CAMERA_MATRIX");
			gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &this->camera->matrix[0][0]);

			//Find the uniform model vector, then assign it
			gl::GLuint model_matrix_id = gl::glGetUniformLocation(this->predeferred_shader->gl_id, "MODEL_MATRIX");
			//Create the correct matrix
			glm::mat4x4 sum = glm::mat4(1.0f);
			sum = actor->state.matrix * actor->mesh_state.matrix * sum;
			gl::glUniformMatrix4fv(model_matrix_id, 1, gl::GL_FALSE, &sum[0][0]);

			//Find the uniform colour vector, then assign it
			gl::glUniform3fv(gl::glGetUniformLocation(this->predeferred_shader->gl_id, "MESH_COLOUR"), 1, &actor->mesh.colour.x);

			//Find the material, then assign it
			//glm::vec4 material_data = glm::vec4(material->shininess, material->specular_amount, material->specular_cap, 0.0);
			//GLuint material_id = glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_DATA");
			//glUniform4fv(material_id, 1, &material_data.x);

			//glUniform1i(glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_EFFECTS"), material->effects);

			//Draw the model
			gl::glDrawArrays(actor->mesh.mode, 0, actor->mesh.polygons.size() * 3);

			//Disable all the vertex attribute arrays again
			for (int count = 0; count < 4; count ++)
				gl::glDisableVertexAttribArray(count);

			//IO::output("Rendered Actor");
		}

		void Renderer::postRender(RenderMode render_mode)
		{
            this->preRender(render_mode);

			//Disable backface culling
			gl::glDisable(gl::GL_CULL_FACE);

			//Disable the depth buffer
			gl::glDisable(gl::GL_DEPTH_TEST);
			gl::glDepthFunc(gl::GL_NONE);

			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_quad_id);

			//Tell the shaders what different parts of the buffer mean using the above array
			gl::glEnableVertexAttribArray(0);
			gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

			gl::GLuint position_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "POSITION_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE0);
			gl::glUniform1i(position_tex_id, 0);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.position_id);

			gl::GLuint normal_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "NORMAL_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE1);
			gl::glUniform1i(normal_tex_id, 1);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.normal_id);

			gl::GLuint colour_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "COLOUR_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE2);
			gl::glUniform1i(colour_tex_id, 2);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.colour_id);

			gl::GLuint material_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "MATERIAL_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE3);
			gl::glUniform1i(material_tex_id, 3);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.material_id);

			//Find the uniform camera perspective matrix, then assign it
			gl::GLuint perspective_matrix_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "PERSPECTIVE_MATRIX");
			gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &this->camera->perspective_matrix[0][0]);

			//Find the uniform camera matrix, then assign it
			gl::GLuint camera_matrix_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "CAMERA_MATRIX");
			gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &this->camera->matrix[0][0]);

			//GLuint depth_id = glGetUniformLocation(framebuffer->shader->gl_id, "RENDER_DEPTH");
			//glUniform1i(depth_id, 0);
			//glBindTexture(GL_TEXTURE_2D, framebuffer->gl_depth_id);

			this->assignLights();

			gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

			gl::glDisableVertexAttribArray(0);
		}

		void Renderer::assignLights()
		{
			//Find the uniform lighting vector, then assign it
			glm::vec4 light_vector_array[16];
			glm::vec4 light_colour_array[16];

			for (unsigned int light = 0; light < this->light_list->size(); light ++)
			{
				Structures::Light* clight = (*this->light_list)[light];

				if (clight->type == Structures::LightType::Directional)
					light_vector_array[light] = glm::vec4(clight->position, 0.0);
				else
					light_vector_array[light] = glm::vec4(clight->position, 1.0);

				light_colour_array[light] = glm::vec4(clight->colour, clight->ambiance);
			}

			gl::glUniform4fv(gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "LIGHT_VECTOR"), 16 * 4, &light_vector_array[0].x);
			gl::glUniform4fv(gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "LIGHT_COLOUR"), 16 * 4, &light_colour_array[0].x);
		}

		void Renderer::setEventManager(Window::EventManager* event_manager)
		{
			this->event_manager = event_manager;
		}

		void Renderer::bufferScreenQuad()
		{
			//Create the screen quad
			gl::glGenVertexArrays(1, &this->gl_quad_id);
			gl::glBindVertexArray(this->gl_quad_id);

			const gl::GLfloat gl_quad_data[] =
			{
				-1.0, -1.0,  0.0,
				 1.0, -1.0,  0.0,
				-1.0,  1.0,  0.0,
				-1.0,  1.0,  0.0,
				 1.0, -1.0,  0.0,
				 1.0,  1.0,  0.0,
			};

			gl::glGenBuffers(1, &this->gl_quad_id);
			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_quad_id);
			gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(gl_quad_data), gl_quad_data, gl::GL_STATIC_DRAW);
		}
	}
}

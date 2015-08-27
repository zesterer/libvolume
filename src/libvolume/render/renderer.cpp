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
			
			this->std_shader = new Structures::Shader();
			this->std_shader->loadFromFiles("../libvolume/shaders/std-vertex-shader.glsl", "../libvolume/shaders/std-fragment-shader.glsl");
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
			gl::glViewport(0, 0, 640 * 1.4, 480 * 1.4);

			//Blank the screen
			gl::glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
		}
		
		void Renderer::renderTarget(RenderTarget* target)
		{
			//Render a render target
			IO::output("Rendering target...");
			
			//TODO
			if (target->rendertype == RenderType::Actor || true)
			{
				IO::output("Target is an instance of Engine::Actor");
				this->renderActor((Engine::Actor*)target);
			}
			else if(target->rendertype == RenderType::None)
			{
				IO::output("Target isn't an actor");
			}
		}
		
		void Renderer::renderActor(Engine::Actor* actor)
		{
			IO::output("Rendering Actor...");
			
			//What is the buffer array composed of?
			int length[] = {sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec2), sizeof(glm::vec3)};
			
			//Buffer the mesh if it's not already been done
			if (!actor->mesh.buffered)
				actor->mesh.buffer();
			
			//Bind the vertex buffer
			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, actor->mesh.gl_id);
			
			//Enable the shader
			this->std_shader->enable();
			
			//Tell the shaders what different parts of the buffer mean using the above array
			gl::GLuint offset = 0;
			for (gl::GLuint array_id = 0; array_id < 4; array_id ++)
			{
				gl::glEnableVertexAttribArray(array_id);
				gl::glVertexAttribPointer(array_id, length[array_id] / sizeof(gl::GLfloat), gl::GL_FLOAT, gl::GL_FALSE, sizeof(Structures::Vertex), (void*)(unsigned long)offset);
				offset += length[array_id];
			}
			
			//Find the uniform camera perspective matrix, then assign it
			gl::GLuint perspective_matrix_id = gl::glGetUniformLocation(this->std_shader->gl_id, "PERSPECTIVE_MATRIX");
			gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &this->camera->perspective_matrix[0][0]);

			//Find the uniform camera matrix, then assign it
			gl::GLuint camera_matrix_id = gl::glGetUniformLocation(this->std_shader->gl_id, "CAMERA_MATRIX");
			gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &this->camera->matrix[0][0]);

			//Find the uniform model vector, then assign it
			gl::GLuint model_matrix_id = gl::glGetUniformLocation(this->std_shader->gl_id, "MODEL_MATRIX");
			gl::glUniformMatrix4fv(model_matrix_id, 1, gl::GL_FALSE, &actor->state.matrix[0][0]);

			//Find the material, then assign it
			//glm::vec4 material_data = glm::vec4(material->shininess, material->specular_amount, material->specular_cap, 0.0);
			//GLuint material_id = glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_DATA");
			//glUniform4fv(material_id, 1, &material_data.x);

			//glUniform1i(glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_EFFECTS"), material->effects);

			//this->assignLights();

			//Draw the model
			gl::glDrawArrays(actor->mesh.mode, 0, actor->mesh.polygons.size() * 3);

			//Disable all the vertex attribute arrays again
			for (int count = 0; count < 4; count ++)
				gl::glDisableVertexAttribArray(count);
			
			IO::output("Rendered Actor");
		}
	}
}

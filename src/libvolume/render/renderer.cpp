//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "renderer.h"
#include "common/io.h"
#include "engine/voxelterrain.h"
#include "common/misc.h"

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

			//this->std_shader = new Structures::Shader();
			//this->std_shader->loadFromFiles("../libvolume/shaders/std-vertex-shader.glsl", "../libvolume/shaders/std-fragment-shader.glsl");

			this->predeferred_shader = new Structures::Shader();
			this->predeferred_shader->loadFromFiles("../libvolume/shaders/predeferred-vertex-shader.glsl", "../libvolume/shaders/predeferred-fragment-shader.glsl");

			this->postdeferred_shader = new Structures::Shader();
			this->postdeferred_shader->loadFromFiles("../libvolume/shaders/postdeferred-vertex-shader.glsl", "../libvolume/shaders/postdeferred-fragment-shader.glsl");

			this->bufferScreenQuad();
			//this->gbuffer.init(640, 480);
		}

		void Renderer::preRender(RenderMode render_mode)
		{
			//Enable backface culling
			gl::glEnable(gl::GL_CULL_FACE);

			//Enable the depth buffer
			gl::glEnable(gl::GL_DEPTH_TEST);
			gl::glDepthFunc(gl::GL_LESS);

			//Switch framebuffer targets & enable shader
			switch (render_mode)
			{
				case (RenderMode::PreDeferred):
				{
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->gbuffer.gbuffer_id);
					gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
					this->predeferred_shader->enable();
				}
				break;

				case (RenderMode::PostDeferred):
				{
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
					gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
					this->postdeferred_shader->enable();
				}
				break;

				default:
				{
					gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
					gl::glViewport(0, 0, this->event_manager->window_size_state.width, this->event_manager->window_size_state.height);
					this->std_shader->enable();
				}
				break;
			}

			//Blank the screen
			gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			switch(render_mode)
			{
				case (RenderMode::PostDeferred):
				{
					gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
				}
				break;

				default:
				{
					gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
				}
				break;
			}
		}

		void Renderer::renderTarget(RenderTarget* target)
		{
			switch(target->rendertype)
			{
				case (RenderType::Actor):
				{
					//IO::output("Target is an instance of Engine::Actor");
					this->renderActor(dynamic_cast<Engine::Actor*>(target));
				}
				break;

				case (RenderType::VoxelTerrain):
				{
					//IO::output("Target is an instance of Engine::VoxelTerrain");
					for (auto region_pair : dynamic_cast<Engine::VoxelTerrain*>(target)->children)
					{
						Engine::VoxelActor* region = dynamic_cast<Engine::VoxelActor*>(region_pair.second);
						this->renderActor(region);
					}
				}
				break;

				default:
				{
					IO::output("Target isn't an actor");
				}
				break;
			}
		}

		void Renderer::renderActor(Engine::Actor* actor)
		{
			//IO::output("Rendering Actor...");

			//Buffer the mesh if it's not already been done
			if (!actor->mesh->buffered)
				actor->mesh->buffer();

			//Bind the vertex buffer
			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, actor->mesh->gl_id);

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
			glm::f32mat4 perspective_matrix = (glm::f32mat4)this->camera->perspective_matrix;
			gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &perspective_matrix[0][0]);

			//Find the uniform camera matrix, then assign it
			gl::GLuint camera_matrix_id = gl::glGetUniformLocation(this->predeferred_shader->gl_id, "CAMERA_MATRIX");
			glm::f32mat4 camera_matrix = (glm::f32mat4)this->camera->matrix;
			gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &camera_matrix[0][0]);

			//Find the uniform model vector, then assign it
			gl::GLuint model_matrix_id = gl::glGetUniformLocation(this->predeferred_shader->gl_id, "MODEL_MATRIX");
			//Create the correct cumulative matrix from the entity state and the mesh state
			//NP: Why is this done in realtime? Not a slowdown atm because all entities are ticked every frame. Maybe add sleeping system 4 lower cpu?
			//Modified is created for new coordinate system!
			Engine::Physics::DynamicState modified = actor->state;
			modified.position -= this->camera->state.position;
			modified.update();
			glm::mat4 sum = glm::mat4(1.0f);
			sum = (glm::f32mat4)modified.matrix * (glm::f32mat4)actor->mesh_state.matrix * sum;
			gl::glUniformMatrix4fv(model_matrix_id, 1, gl::GL_FALSE, &sum[0][0]);

			//Find the uniform colour vector, then assign it
			gl::glUniform3fv(gl::glGetUniformLocation(this->predeferred_shader->gl_id, "MESH_COLOUR"), 1, &actor->mesh->colour.x);

			//TODO: Build materials system that is passed via deferred shader. Could allow for normal texturing or different phong model?
			//Find the material, then assign it
			//glm::vec4 material_data = glm::vec4(material->shininess, material->specular_amount, material->specular_cap, 0.0);
			//GLuint material_id = glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_DATA");
			//glUniform4fv(material_id, 1, &material_data.x);

			//glUniform1i(glGetUniformLocation(this->std_shader->gl_id, "MATERIAL_EFFECTS"), material->effects);

			//Draw the model
			gl::glDrawArrays(actor->mesh->mode, 0, actor->mesh->polygons.size() * 3);

			//Disable all the vertex attribute arrays again
			for (int count = 0; count < 4; count ++)
				gl::glDisableVertexAttribArray(count);
		}

		void Renderer::postRender(RenderMode render_mode, glm::vec3 background_colour)
		{
            this->preRender(render_mode);

			//Disable backface culling
			gl::glDisable(gl::GL_CULL_FACE);

			//Disable the depth buffer
			//Not absolutely necessary, but may become useful in the future
			gl::glDisable(gl::GL_DEPTH_TEST);
			gl::glDepthFunc(gl::GL_NONE);

			//Obvious. Bind the bi-polygon array buffer ready for vertex shader passing
			gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_quad_id);

			//Tell the shaders what different parts of the buffer mean using the above array
			gl::glEnableVertexAttribArray(0);
			gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

			//Get the position buffer texture ready for rendering
			gl::GLuint position_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "POSITION_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE0);
			gl::glUniform1i(position_tex_id, 0);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.position_id);

			//Get the mesh position buffer texture ready for rendering
			gl::GLuint mesh_position_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "MESH_POSITION_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE1);
			gl::glUniform1i(mesh_position_tex_id, 1);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.mesh_position_id);

			//Get the normal buffer texture ready for rendering
			gl::GLuint normal_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "NORMAL_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE2);
			gl::glUniform1i(normal_tex_id, 2);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.normal_id);

			//Get the colour buffer texture ready for rendering
			gl::GLuint colour_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "COLOUR_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE3);
			gl::glUniform1i(colour_tex_id, 3);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.colour_id);

			//Get the material buffer texture ready for rendering
			//TODO: This doesn't actually exist yet, since there's not material input
			gl::GLuint material_tex_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "MATERIAL_BUFFER");
			gl::glActiveTexture(gl::GL_TEXTURE4);
			gl::glUniform1i(material_tex_id, 4);
			gl::glBindTexture(gl::GL_TEXTURE_2D, this->gbuffer.material_id);

			//Find the uniform camera perspective matrix, then assign it
			gl::GLuint perspective_matrix_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "PERSPECTIVE_MATRIX");
			glm::f32mat4 perspective_matrix = (glm::f32mat4)this->camera->perspective_matrix;
			gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &perspective_matrix[0][0]);

			//Find the uniform camera matrix, then assign it
			gl::GLuint camera_matrix_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "CAMERA_MATRIX");
			glm::f32mat4 camera_matrix = (glm::f32mat4)this->camera->matrix;
			gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &camera_matrix[0][0]);

			//Find the uniform aspect ratio, then assign it
			float aspect = (float)this->event_manager->getWindowSizeState()->width / (float)this->event_manager->getWindowSizeState()->height;
			gl::GLuint aspect_ratio_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "ASPECT_RATIO");
			gl::glUniform1f(aspect_ratio_id, aspect);

			//Find the uniform Field of View, then assign it
			gl::GLuint fov_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "FOV");
			gl::glUniform1f(fov_id, this->camera->fov);

			//Find the background colour, then assign it
			gl::GLuint background_colour_id = gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "BACKGROUND_COLOUR");
			gl::glUniform3f(background_colour_id, background_colour.r, background_colour.g, background_colour.b);

			//Not currently done, since calculated from position. Potentially wasteful, since distance in fragment
			// shader, but not too much of a problem since only calculated per-pixel, not per-fragment due to deferring
			//GLuint depth_id = glGetUniformLocation(framebuffer->shader->gl_id, "RENDER_DEPTH");
			//glUniform1i(depth_id, 0);
			//glBindTexture(GL_TEXTURE_2D, framebuffer->gl_depth_id);

			//Assign the lighting data for use in the fragment shader
			//Doesn't actually take full advantage of deferred shading yet
			// since lights are still passed in array without selective sphere rendering
			this->assignLights();

			gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

			gl::glDisableVertexAttribArray(0);
		}

		void Renderer::assignLights()
		{
			//Find the uniform lighting vector, then assign it
			glm::vec4 light_vector_array[32];
			glm::vec4 light_colour_array[32];
			glm::vec4 light_direct_array[32];

			for (unsigned int light = 0; light < this->light_list->size(); light ++)
			{
				Structures::Light* clight = (*this->light_list)[light];

				if (clight->type == Structures::LightType::Directional)
					light_vector_array[light] = glm::vec4(clight->position, 0.0);
				else
					light_vector_array[light] = glm::vec4(clight->position - this->camera->state.position, 1.0);

				light_colour_array[light] = glm::vec4(clight->colour, clight->ambiance);

				light_direct_array[light] = glm::vec4(clight->direct, clight->spot_angle);
			}

			//Assign the lighting array. Maximum of 16 lights at the moment
			gl::glUniform4fv(gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "LIGHT_VECTOR"), 32 * 4, &light_vector_array[0].x);
			gl::glUniform4fv(gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "LIGHT_COLOUR"), 32 * 4, &light_colour_array[0].x);
			gl::glUniform4fv(gl::glGetUniformLocation(this->postdeferred_shader->gl_id, "LIGHT_DIRECT"), 32 * 4, &light_direct_array[0].x);
		}

		void Renderer::linkTo(Window::Window& window)
		{
			//Link the event managers so this renderer can grab input from the window
			this->event_manager = &window.event_manager;
		}

		void Renderer::bufferScreenQuad()
		{
			//Create the screen quad
			gl::glGenVertexArrays(1, &this->gl_quad_id);
			gl::glBindVertexArray(this->gl_quad_id);

			//The bi-polygon array for deferred rendering
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

		void Renderer::tick()
		{
			this->gbuffer.tick(this->event_manager->getWindowSizeState()->width, this->event_manager->getWindowSizeState()->height);
		}
	}
}

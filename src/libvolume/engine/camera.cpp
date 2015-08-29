//----LOCAL----
#include "camera.h"

namespace LibVolume
{
	namespace Engine
	{
		Camera::Camera()
		{
			this->state.position = glm::vec3(0.0, 3.0, 20.0);
		}
		
		void Camera::update()
		{
			//Clear the matrix
			this->matrix = glm::mat4(1.0);

			//Normalize the camera quaternion
			glm::normalize(this->state.orientation);
			this->matrix = glm::toMat4(this->state.orientation) * this->matrix;
			
			//Position
			this->matrix = translate(this->matrix, glm::vec3(-this->state.position.x, -this->state.position.y, -this->state.position.z));
			
			//Perspective / projection
			this->perspective_matrix = glm::perspective(this->fov, this->screen_ratio, this->min_render, this->max_render);
		}
		
		void Camera::tick(float screen_ratio)
		{
			this->screen_ratio = screen_ratio;
			this->update();
		}
	}
}

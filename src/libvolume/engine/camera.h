#ifndef LIBVOLUME_ENGINE_CAMERA_H
#define LIBVOLUME_ENGINE_CAMERA_H

//----LIBRARY----
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

//----LOCAL----
#include "physics/state.h"

namespace LibVolume
{
	namespace Engine
	{
		class Camera
		{
			public:
				Physics::DynamicState state;
				
				glm::mat4 matrix;
				glm::mat4 perspective_matrix;
				
				float fov = 0.95;
				float min_render = 0.01;
				float max_render = 1000;
				float screen_ratio = 1.0;
				
				Camera();
				void update();
				void tick(float screen_ratio);
		};
	}
}

#endif
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

				glm::f64mat4 matrix;
				glm::f64mat4 perspective_matrix;

				float fov = 1.0;
				float min_render = 0.001;
				float max_render = 1000.0;
				float screen_ratio = 1.0;
				float fog_distance = 64.0f; //Make equal to 0.0 to remove fog

				Camera();
				void update();
				void tick(float screen_ratio);
		};
	}
}

#endif

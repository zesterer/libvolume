#ifndef LIBVOLUME_COMMON_STATE_H
#define LIBVOLUME_COMMON_STATE_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

//----LOCAL----
#include "position.h"

namespace LibVolume
{
	namespace Engine
	{
		namespace Physics
		{
			struct PointState
			{
				public:
					//glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
					glm::f64vec3 position = glm::f64vec3(0.0, 0.0, 0.0);
					glm::f64mat4 matrix = glm::f64mat4(1.0f);

					virtual void update();
			};

			struct BodyState : public PointState
			{
				public:
					glm::f64quat orientation = glm::f64quat(glm::f64vec3(0.0, 0.0, 0.0));
					glm::f64vec3 scale = glm::f64vec3(1.0, 1.0, 1.0);

					virtual void update() override;
			};

			struct DynamicState : public BodyState
			{
				public:
					glm::f64vec3 velocity = glm::f64vec3(0.0, 0.0, 0.0);
					glm::f64quat spin = glm::f64quat(glm::f64vec3(0.0, 0.0, 0.0));
					float mass = 1.0;

					void tick();
					virtual void update() override;
			};
		}
	}
}

#endif

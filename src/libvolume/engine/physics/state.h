#ifndef LIBVOLUME_COMMON_STATE_H
#define LIBVOLUME_COMMON_STATE_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace LibVolume
{
	namespace Engine
	{
		namespace Physics
		{
			struct PointState
			{
				public:
					glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
					glm::mat4x4 matrix = glm::mat4(1.0f);
					
					virtual void update();
			};
			
			struct BodyState : public PointState
			{
				public:
					glm::quat orientation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
					glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
					
					virtual void update() override;
			};
			
			struct DynamicState : public BodyState
			{
				public:
					glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0);
					glm::quat spin = glm::quat(glm::vec3(0.0, 0.03, 0.0));
				
					void tick();
					virtual void update() override;
			};
		}
	}
}

#endif

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
					glm::vec3 position;
					glm::mat4x4 matrix;
					
					virtual void update();
			};
			
			struct BodyState : public PointState
			{
				public:
					glm::quat orientation;
					glm::vec3 scale;
					
					virtual void update() override;
			};
			
			struct DynamicState : public BodyState
			{
				public:
					glm::vec3 velocity;
					glm::quat spin;
				
					void tick();
					virtual void update() override;
			};
		}
	}
}

#endif

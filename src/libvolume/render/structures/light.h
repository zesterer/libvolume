#ifndef LIBVOLUME_RENDER_STRUCTURES_H
#define LIBVOLUME_RENDER_STRUCTURES_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			enum LightType
			{
				Directional,
				Point
			};

			struct Light
			{
				public:
					LightType type = Directional;
					glm::f64vec3 position = glm::vec3(1.0, 1.0, 1.0);
					glm::vec3 colour = glm::vec3(1.0, 1.0, 1.0);
					glm::vec3 direct = glm::vec3(1.0, 0.0, 0.0);
					float spot_angle = 0.0;
					float ambiance = 0.1;

					Light(LightType type, glm::vec3 position, glm::vec3 colour, float ambiance, glm::vec3 direct = glm::vec3(1.0, 0.0, 0.0), float spot_angle = 0.0);
			};
		}
	}
}

#endif

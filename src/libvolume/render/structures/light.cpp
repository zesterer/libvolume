//----LOCAL----
#include "light.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			Light::Light(LightType type, glm::vec3 position, glm::vec3 colour, float ambiance, glm::vec3 direct, float spot_angle)
			{
				this->type = type;
				this->position = position;
				this->colour = colour;
				this->ambiance = ambiance;
				this->direct = direct;
				this->spot_angle = spot_angle;
			}
		}
	}
}

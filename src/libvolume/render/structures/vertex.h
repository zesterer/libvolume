#ifndef LIBVOLUME_RENDER_STRUCTURES_VERTEX_H
#define LIBVOLUME_RENDER_STRUCTURES_VERTEX_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			struct Vertex
			{
				public:
					glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
					glm::vec3 colour = glm::vec3(1.0, 1.0, 1.0);
					glm::vec2 uv_coords = glm::vec2(0.0, 0.0);
					glm::vec3 normal = glm::vec3(0.0, 0.0, 0.0);
			};
		}
	}
}

#endif

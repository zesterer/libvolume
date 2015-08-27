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
					glm::vec3 position;
					glm::vec3 colour;
					glm::vec2 uv_coords;
					glm::vec3 normal;
			};
		}
	}
}

#endif

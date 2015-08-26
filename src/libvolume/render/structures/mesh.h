#ifndef LIBVOLUME_RENDER_STRUCTURES_MESH_H
#define LIBVOLUME_RENDER_STRUCTURES_MESH_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "polygon.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			class Mesh
			{
				public:
					std::vector<Polygon> polygons;
					
					Mesh();
			};
		}
	}
}

#endif

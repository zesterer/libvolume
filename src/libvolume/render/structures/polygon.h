#ifndef LIBVOLUME_RENDER_STRUCTURES_POLYGON_H
#define LIBVOLUME_RENDER_STRUCTURES_POLYGON_H

//----LOCAL----
#include "vertex.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			struct Polygon
			{
				public:
					Vertex a, b, c;
			};
		}
	}
}

#endif

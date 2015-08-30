#ifndef LIBVOLUME_RENDER_STRUCTURES_GBUFFER_H
#define LIBVOLUME_RENDER_STRUCTURES_GBUFFER_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			struct GBuffer
			{
				public:
					gl::GLuint gbuffer_id;

					gl::GLuint position_id, normal_id, colour_id, material_id;

					gl::GLuint render_depth_id;

					void init();
			};
		}
	}
}

#endif

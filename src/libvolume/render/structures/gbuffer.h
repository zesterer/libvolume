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

					gl::GLuint position_id, mesh_position_id, normal_id, colour_id, material_id;

					gl::GLuint render_depth_id;

					int width = 640;
					int height = 480;

					//Has the gbuffer been created?
					bool initiated = false;

					void init(int width, int height);
					void tick(int width, int height);
			};
		}
	}
}

#endif

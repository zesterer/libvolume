#ifndef LIBVOLUME_RENDER_RENDERER_H
#define LIBVOLUME_RENDER_RENDERER_H

//----LOCAL----
#include "rendertarget.h"

namespace LibVolume
{
	namespace Render
	{	
		class Renderer
		{
			public:
				Renderer();
				void preRender();
				void renderTarget(RenderTarget* target);
		};
	}
}

#endif

#ifndef LIBVOLUME_RENDER_RENDERTARGET_H
#define LIBVOLUME_RENDER_RENDERTARGET_H

namespace LibVolume
{
	namespace Render
	{
		enum RenderType
		{
			None,
			MeshedStatic,
			MeshedBody,
			MeshedTerrain
		};
		
		//Anything that inherits this class can be rendered by the renderer class
		class RenderTarget
		{
			RenderType rendertype = RenderType::None;
		};
	}
}

#endif

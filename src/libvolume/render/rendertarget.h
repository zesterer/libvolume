#ifndef LIBVOLUME_RENDER_RENDERTARGET_H
#define LIBVOLUME_RENDER_RENDERTARGET_H

namespace LibVolume
{
	namespace Render
	{
		enum RenderType
		{
			None,
			Actor
		};
		
		//Anything that inherits this class can be rendered by the renderer class
		class RenderTarget
		{
			public:
				RenderType rendertype = RenderType::None;
				
				RenderTarget();
				
				virtual void dummy();
		};
	}
}

#endif

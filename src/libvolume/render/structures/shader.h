#ifndef LIBVOLUME_RENDER_STRUCTURES_SHADER_H
#define LIBVOLUME_RENDER_STRUCTURES_SHADER_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			class Shader
			{
				public:
					gl::GLuint gl_id;

					void enable();
					void loadFromFiles(std::string vertex_file_path, std::string fragment_file_path);
					void loadFromStrings(std::string VertexShaderCode, std::string FragmentShaderCode);
			};
		}
	}
}

#endif

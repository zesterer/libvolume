#ifndef LIBVOLUME_RENDER_STRUCTURES_MESH_H
#define LIBVOLUME_RENDER_STRUCTURES_MESH_H

//----STANDARD----
#include "vector"
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

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

					bool buffered = false;
					gl::GLuint gl_id;
					gl::GLenum mode = gl::GL_TRIANGLES;

					glm::vec3 colour = glm::vec3(1.0, 1.0, 1.0);

					Mesh();
					~Mesh();
					bool loadFromOBJ(std::string filename, bool recalc_normals = false);
					void buffer();
					void clear();
			};
		}
	}
}

#endif

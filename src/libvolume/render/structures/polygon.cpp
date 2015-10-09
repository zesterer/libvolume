//----LOCAL----
#include "polygon.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			void Polygon::correctNormals(float curvature_bias)
			{
				//Find the normal to the surface
				glm::vec3 n0 = glm::cross(this->b.position - this->a.position, this->c.position - this->a.position);
				n0 /= glm::length(n0);

				glm::vec3 average = (this->a.position + this->b.position + this->c.position) / glm::vec3(3.0, 3.0, 3.0);

				//Curvature bias is used only to make things look a little 3D...
				this->a.normal = n0 + (a.normal - average) * curvature_bias;
				this->b.normal = n0 + (b.normal - average) * curvature_bias;
				this->c.normal = n0 + (c.normal - average) * curvature_bias;
			}

			void Polygon::invert()
			{
				//Swap the vertices around
				Vertex temp = this->a;
				this->a = this->c;
				this->c = temp;

				//Recalculate the normals
				this->correctNormals();
			}
		}
	}
}

//----LOCAL----
#include "meshedobject.h"

namespace LibVolume
{
	namespace Render
	{
		MeshedObject::MeshedObject(Structures::Mesh* mesh)
		{
			if (mesh == nullptr)
				this->mesh = new Structures::Mesh();
			else
				this->mesh = mesh;
		}
	}
}

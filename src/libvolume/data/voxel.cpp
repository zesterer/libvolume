//----LIBRARY----
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "voxel.h"

namespace LibVolume
{
	namespace Data
	{
		template <typename MetaType>
		MetaType* Voxel<MetaType>::getMeta()
		{
			return &this->metadata;
		}
	}
}

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
		unsigned int Voxel::getID()
		{
			return this->id;
		}
		
		float Voxel::getDensity()
		{
			return this->density;
		}
	}
}

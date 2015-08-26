//----LOCAL----
#include "voxel.h"

namespace LibVolume
{
	namespace Data
	{
		int Voxel::getType()
		{
			return this->type;
		}
		
		float Voxel::getDensity()
		{
			return this->density;
		}
		
		void* Voxel::getMeta()
		{
			return this->metadata;
		}
	}
}

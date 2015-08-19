#ifndef LIBVOLUME_DATA_VOXEL_H
#define LIBVOLUME_DATA_VOXEL_H

namespace LibVolume
{
	namespace Data
	{
		struct Voxel
		{
			unsigned int id;
			float density;
			
			unsigned int getID();
			float getDensity();
		};
	}
}

#endif

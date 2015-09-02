#ifndef LIBVOLUME_DATA_VOXEL_H
#define LIBVOLUME_DATA_VOXEL_H

namespace LibVolume
{
	namespace Data
	{
		struct Voxel
		{
			public:
				int type = 0;
				float density = 0.0f;

				void* metadata;

				int getType();
				float getDensity();
				void* getMeta();
		};
	}
}

#endif

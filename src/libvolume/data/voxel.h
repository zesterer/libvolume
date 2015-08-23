#ifndef LIBVOLUME_DATA_VOXEL_H
#define LIBVOLUME_DATA_VOXEL_H

namespace LibVolume
{
	namespace Data
	{
		template <typename MetaType>
		struct Voxel
		{
			public:
				MetaType metadata;
			
				MetaType* getMeta();
		};
	}
}

#endif

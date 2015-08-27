#ifndef LIBVOLUME_RENDER_STRUCTURES_FACE_H
#define LIBVOLUME_RENDER_STRUCTURES_FACE_H

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			//This struct is largely used for OBJ conversion
			struct Face
			{
			    	public:
					unsigned int a_pos, a_col, a_tex, a_norm;
					unsigned int b_pos, b_col, b_tex, b_norm;
					unsigned int c_pos, c_col, c_tex, c_norm;
					
					unsigned char has_parts;
			};
		}
	}
}

#endif

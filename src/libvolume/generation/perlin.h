#ifndef LIBVOLUME_GENERATION_PERLIN_H
#define LIBVOLUME_GENERATION_PERLIN_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

namespace LibVolume
{
	namespace Generation
	{
		struct PerlinNoise
		{
			static float getRandom(glm::vec4 pos);

			static float getNoise(glm::vec4 pos, float octave);

			static float getPerlin(glm::vec4 pos, float initial, float octaves, float skip);

			static glm::vec2 getPerlinVec2(glm::vec4 pos, float initial, float octaves, float skip);
			static glm::vec3 getPerlinVec3(glm::vec4 pos, float initial, float octaves, float skip);
		};
	}
}

#endif

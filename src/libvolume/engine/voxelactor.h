#ifndef LIBVOLUME_ENGINE_VOXELACTOR_H
#define LIBVOLUME_ENGINE_VOXELACTOR_H

//----LOCAL----
#include "data/voxelfield.h"
#include "actor.h"
#include "marchingcubes.h"

//Cube vectors. For face placement and stuff
#define CubeVec000 glm::vec3(0.0, 0.0, 0.0)
#define CubeVec001 glm::vec3(0.0, 0.0, 1.0)
#define CubeVec010 glm::vec3(0.0, 1.0, 0.0)
#define CubeVec011 glm::vec3(0.0, 1.0, 1.0)

#define CubeVec100 glm::vec3(1.0, 0.0, 0.0)
#define CubeVec101 glm::vec3(1.0, 0.0, 1.0)
#define CubeVec110 glm::vec3(1.0, 1.0, 0.0)
#define CubeVec111 glm::vec3(1.0, 1.0, 1.0)

namespace LibVolume
{
	namespace Engine
	{
		enum MeshingAlgorithm
		{
			Cubic,
			MarchingCubes,
			SurfaceNets
		};

		class VoxelActor : public Data::VoxelField, public Actor
		{
			public:
				float threshold = 0.5f;

				std::vector<glm::vec3> colour_table;

				//Whether the meshing algorithm meshes the first plane
				bool mesh_first_plane = true;

				VoxelActor(glm::ivec3 size);
				void extract(MeshingAlgorithm algorithm, bool smooth_normals = true, bool smooth_colour = true);
				void extractCubic();
				void addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, int type);
				void extractMarchingCubes(bool use_density = true, bool smooth_normals = true, bool smooth_colours = true);
				std::vector<Render::Structures::Polygon> getMarchingCubesPolygonConfiguration(glm::ivec3 pos, unsigned char index, float density[8], bool use_density, bool smooth_colour, int type);
				glm::vec3 getVoxelColour(int type);
		};
	}
}

#endif

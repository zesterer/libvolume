//----LOCAL----
#include "voxelactor.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		VoxelActor::VoxelActor(glm::ivec3 size) : Data::VoxelField(size), Actor()
		{
			//By default, voxel actors collide with one-another
			this->can_collide = true;
			this->objecttype = ObjectType::VoxelActorObject;
		}

		void VoxelActor::extract(MeshingAlgorithm algorithm, bool smooth_normals, bool smooth_colour) //Extract a mesh from the voxel field
		{
			IO::output("Extracting mesh from voxel field of size " + std::to_string(this->size.x * this->size.y * this->size.z));

			//Clear before meshing takes place
			this->mesh->clear();

			switch (algorithm)
			{
				case (MeshingAlgorithm::Cubic):
				{
					this->extractCubic();
					break;
				}

				case (MeshingAlgorithm::MarchingCubes):
				{
					this->extractMarchingCubes(true, smooth_normals, smooth_colour);
					break;
				}

				case (MeshingAlgorithm::SurfaceNets):
				{
					this->extractMarchingCubes(false, smooth_normals, smooth_colour);
					break;
				}
			}
		}

		void VoxelActor::extractCubic()
		{
			//Loop through each voxel
			glm::ivec3 count = {0, 0, 0};
			for (count.x = 0; count.x < this->size.x; count.x ++)
			{
				for (count.y = 0; count.y < this->size.y; count.y ++)
				{
					for (count.z = 0; count.z < this->size.z; count.z ++)
					{
						Data::Voxel* voxel = this->getAt(count);

						glm::vec3 pos = glm::vec3((float)count.x, (float)count.y, (float)count.z);

						if (voxel->density > this->threshold)
						{
							//Bottom
							if (this->getAt({count.x, count.y, count.z - 1})->density <= this->threshold)
								this->addQuad(pos + CubeVec100, pos + CubeVec110, pos + CubeVec010, pos + CubeVec000, voxel->type);
							//Top
							if (this->getAt({count.x, count.y, count.z + 1})->density <= this->threshold)
								this->addQuad(pos + CubeVec001, pos + CubeVec011, pos + CubeVec111, pos + CubeVec101, voxel->type);
							//Left
							if (this->getAt({count.x - 1, count.y, count.z})->density <= this->threshold)
								this->addQuad(pos + CubeVec000, pos + CubeVec010, pos + CubeVec011, pos + CubeVec001, voxel->type);
							//Right
							if (this->getAt({count.x + 1, count.y, count.z})->density <= this->threshold)
								this->addQuad(pos + CubeVec101, pos + CubeVec111, pos + CubeVec110, pos + CubeVec100, voxel->type);
							//Back
							if (this->getAt({count.x, count.y - 1, count.z})->density <= this->threshold)
								this->addQuad(pos + CubeVec000, pos + CubeVec001, pos + CubeVec101, pos + CubeVec100, voxel->type);
							//Front
							if (this->getAt({count.x, count.y + 1, count.z})->density <= this->threshold)
								this->addQuad(pos + CubeVec110, pos + CubeVec111, pos + CubeVec011, pos + CubeVec010, voxel->type);
						}
					}
				}
			}
		}

		void VoxelActor::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, int type)
		{
			Render::Structures::Polygon p1, p2;

			glm::vec3 voxel_colour = this->getVoxelColour(type);

			p1.a.position = a;
			p1.b.position = c;
			p1.c.position = b;

			p2.a.position = d;
			p2.b.position = c;
			p2.c.position = a;

			p1.correctNormals();
			p2.correctNormals();

			p1.a.colour = voxel_colour;
			p1.b.colour = voxel_colour;
			p1.c.colour = voxel_colour;

			p2.a.colour = voxel_colour;
			p2.b.colour = voxel_colour;
			p2.c.colour = voxel_colour;

			this->mesh->polygons.push_back(p1);
			this->mesh->polygons.push_back(p2);
		}

		void VoxelActor::extractMarchingCubes(bool use_density, bool smooth_normals, bool smooth_colour)
		{
			glm::ivec3 count;
			glm::ivec3 initial;

            //Loop through each voxel
            if (this->mesh_first_plane)
				initial = {-1, -1, -1};
			else
				initial = {0, 0, 0};

			for (count.x = initial.x; count.x < this->size.x; count.x ++)
			{
				for (count.y = initial.y; count.y < this->size.y; count.y ++)
				{
					for (count.z = initial.z; count.z < this->size.z; count.z ++)
					{
						glm::vec3 pos = glm::vec3((float)count.x, (float)count.y, (float)count.z);

						//Find the configuration index based on surrounding voxels
						unsigned char index = 0;
						if (this->getAt(count + glm::ivec3(0, 0, 0))->density >= this->threshold) index |= 0b00000001;
						if (this->getAt(count + glm::ivec3(1, 0, 0))->density >= this->threshold) index |= 0b00000010;
						if (this->getAt(count + glm::ivec3(1, 1, 0))->density >= this->threshold) index |= 0b00000100;
						if (this->getAt(count + glm::ivec3(0, 1, 0))->density >= this->threshold) index |= 0b00001000;
						if (this->getAt(count + glm::ivec3(0, 0, 1))->density >= this->threshold) index |= 0b00010000;
						if (this->getAt(count + glm::ivec3(1, 0, 1))->density >= this->threshold) index |= 0b00100000;
						if (this->getAt(count + glm::ivec3(1, 1, 1))->density >= this->threshold) index |= 0b01000000;
						if (this->getAt(count + glm::ivec3(0, 1, 1))->density >= this->threshold) index |= 0b10000000;

						float density_cube[8];
						density_cube[0b000] = this->getAt(count + glm::ivec3(0, 0, 0))->density;
						density_cube[0b001] = this->getAt(count + glm::ivec3(0, 0, 1))->density;
						density_cube[0b010] = this->getAt(count + glm::ivec3(0, 1, 0))->density;
						density_cube[0b011] = this->getAt(count + glm::ivec3(0, 1, 1))->density;
						density_cube[0b100] = this->getAt(count + glm::ivec3(1, 0, 0))->density;
						density_cube[0b101] = this->getAt(count + glm::ivec3(1, 0, 1))->density;
						density_cube[0b110] = this->getAt(count + glm::ivec3(1, 1, 0))->density;
						density_cube[0b111] = this->getAt(count + glm::ivec3(1, 1, 1))->density;

						if (index != 0 && index != 255) //Make sure it's not fully empty or fully filled
						{
							//Get the configuration
							std::vector<Render::Structures::Polygon> polygons = this->getMarchingCubesPolygonConfiguration(count, index, density_cube, use_density, smooth_colour, this->getAt(count)->type);

							//World::Generation::PerlinNoise noise;
							//Move all those polygons to their correct position in the mesh
							for (unsigned char poly = 0; poly < polygons.size(); poly ++)
							{
								polygons[poly].a.position += pos;
								polygons[poly].b.position += pos;
								polygons[poly].c.position += pos;

								if (smooth_normals)
								{
									polygons[poly].a.normal = this->getNormalAt(polygons[poly].a.position);
									polygons[poly].b.normal = this->getNormalAt(polygons[poly].b.position);
									polygons[poly].c.normal = this->getNormalAt(polygons[poly].c.position);
								}
								else
									polygons[poly].correctNormals();
							}

							//Append them all to the current mesh
							this->mesh->polygons.insert(this->mesh->polygons.end(), polygons.begin(), polygons.end());
						}
					}
				}
			}
		}

		//Seriously, I'm not even going to try to explain this monster.
		//Just go with it. It works, ok?
		std::vector<Render::Structures::Polygon> VoxelActor::getMarchingCubesPolygonConfiguration(glm::ivec3 pos, unsigned char index, float density[8], bool use_density, bool smooth_colour, int type)
		{
			std::vector<Render::Structures::Polygon> polygons;
			int triangles[16];

			//Place the triangle array into the triangles
			for (unsigned char c = 0; c < 16; c ++)
			{
				triangles[c] = MC_TRITABLE[index][c];
			}

			glm::vec3 voxel_colour = this->getVoxelColour(type);

			//Add the polygons
			for (unsigned char c = 0; c < 15; c += 3)
			{
				if (triangles[c] != -1)
				{
					Render::Structures::Polygon poly;

					if (!use_density)
					{
						poly.c.position = glm::mix(MC_EDGES[triangles[c + 0]][0], MC_EDGES[triangles[c + 0]][1], 0.5);
						poly.b.position = glm::mix(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], 0.5);
						poly.a.position = glm::mix(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], 0.5);

						poly.c.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 0]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 0]][1])->type), 0.5f);
						poly.b.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 1]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 1]][1])->type), 0.5f);
						poly.a.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 2]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 2]][1])->type), 0.5f);

						//poly.c.position = this->getInterp(triangles[c + 0], density);
						//poly.b.position = this->getInterp(triangles[c + 1], density);
						//poly.a.position = this->getInterp(triangles[c + 2], density);

						//poly.b.pos = this->getInterp(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], density[MC_EDGE2VERTEX[triangles[c + 1]][0]], density[MC_EDGE2VERTEX[triangles[c + 1]][1]]);
						//	poly.a.pos = this->getInterp(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], density[MC_EDGE2VERTEX[triangles[c + 2]][0]], density[MC_EDGE2VERTEX[triangles[c + 2]][1]]);

						//poly.c.pos = glm::mix(MC_EDGES[triangles[c + 0]][0], MC_EDGES[triangles[c + 0]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 0]][0]], density[MC_EDGE2VERTEX[triangles[c + 0]][1]]));
						//poly.b.pos = glm::mix(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 1]][0]], density[MC_EDGE2VERTEX[triangles[c + 1]][1]]));
						//poly.a.pos = glm::mix(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 2]][0]], density[MC_EDGE2VERTEX[triangles[c + 2]][1]]));
					}
					else
					{
						float x;
						x = (this->threshold - density[MC_EDGES_TO_INT[triangles[c + 0]][0]]) / (density[MC_EDGES_TO_INT[triangles[c + 0]][1]] - density[MC_EDGES_TO_INT[triangles[c + 0]][0]]);
						poly.c.position = glm::mix(MC_EDGES[triangles[c + 0]][0], MC_EDGES[triangles[c + 0]][1], x);

						if (smooth_colour)
							poly.c.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 0]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 0]][1])->type), x);

						x = (this->threshold - density[MC_EDGES_TO_INT[triangles[c + 1]][0]]) / (density[MC_EDGES_TO_INT[triangles[c + 1]][1]] - density[MC_EDGES_TO_INT[triangles[c + 1]][0]]);
						poly.b.position = glm::mix(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], x);

						if (smooth_colour)
							poly.b.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 1]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 1]][1])->type), x);

						x = (this->threshold - density[MC_EDGES_TO_INT[triangles[c + 2]][0]]) / (density[MC_EDGES_TO_INT[triangles[c + 2]][1]] - density[MC_EDGES_TO_INT[triangles[c + 2]][0]]);
						poly.a.position = glm::mix(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], x);

						if (smooth_colour)
							poly.a.colour = glm::mix(this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 2]][0])->type), this->getVoxelColour(this->getAt(pos + MC_INTEDGES[triangles[c + 2]][1])->type), x);
					}

					if (!smooth_colour)
					{
						poly.a.colour = voxel_colour;
						poly.b.colour = voxel_colour;
						poly.c.colour = voxel_colour;
					}

					polygons.push_back(poly);
				}
			}

			return polygons;
		}

		glm::vec3 VoxelActor::getVoxelColour(int type)
		{
			if (this->colour_table.size() <= (unsigned int)type)
				return glm::vec3(1.0f, 1.0f, 1.0f);

			return this->colour_table[type];
		}
	}
}

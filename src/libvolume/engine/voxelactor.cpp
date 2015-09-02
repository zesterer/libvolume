//----LOCAL----
#include "voxelactor.h"

namespace LibVolume
{
	namespace Engine
	{
		VoxelActor::VoxelActor(glm::ivec3 size) : Data::VoxelField(size), Actor()
		{

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
							if (this->getAt({count.x, count.y, count.z - 1})->density < this->threshold)
								this->addQuad(pos + CubeVec100, pos + CubeVec110, pos + CubeVec010, pos + CubeVec000);
							//Top
							if (this->getAt({count.x, count.y, count.z + 1})->density < this->threshold)
								this->addQuad(pos + CubeVec001, pos + CubeVec011, pos + CubeVec111, pos + CubeVec101);
							//Left
							if (this->getAt({count.x - 1, count.y, count.z})->density < this->threshold)
								this->addQuad(pos + CubeVec000, pos + CubeVec010, pos + CubeVec011, pos + CubeVec001);
							//Right
							if (this->getAt({count.x + 1, count.y, count.z})->density < this->threshold)
								this->addQuad(pos + CubeVec101, pos + CubeVec111, pos + CubeVec110, pos + CubeVec100);
							//Back
							if (this->getAt({count.x, count.y - 1, count.z})->density < this->threshold)
								this->addQuad(pos + CubeVec000, pos + CubeVec001, pos + CubeVec101, pos + CubeVec100);
							//Front
							if (this->getAt({count.x, count.y + 1, count.z})->density < this->threshold)
								this->addQuad(pos + CubeVec110, pos + CubeVec111, pos + CubeVec011, pos + CubeVec010);
						}
					}
				}
			}
		}

		void VoxelActor::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
		{
			Render::Structures::Polygon p1, p2;

			p1.a.position = a;
			p1.b.position = c;
			p1.c.position = b;

			p2.a.position = d;
			p2.b.position = c;
			p2.c.position = a;

			p1.correctNormals();
			p2.correctNormals();

			this->mesh->polygons.push_back(p1);
			this->mesh->polygons.push_back(p2);
		}

		void VoxelActor::extractMarchingCubes(bool use_density)
		{
            //Loop through each voxel
			glm::ivec3 count = {0, 0, 0};
			for (count.x = -1; count.x < this->size.x; count.x ++)
			{
				for (count.y = -1; count.y < this->size.y; count.y ++)
				{
					for (count.z = -1; count.z < this->size.z; count.z ++)
					{
						glm::vec3 pos = glm::vec3((float)count.x, (float)count.y, (float)count.z);

						//Find the configuration index based on surrounding voxels
						unsigned char index = 0;
						if (this->getAt(count + glm::ivec3(0, 0, 0))->density > 0.0) index |= 0b00000001;
						if (this->getAt(count + glm::ivec3(1, 0, 0))->density > 0.0) index |= 0b00000010;
						if (this->getAt(count + glm::ivec3(1, 1, 0))->density > 0.0) index |= 0b00000100;
						if (this->getAt(count + glm::ivec3(0, 1, 0))->density > 0.0) index |= 0b00001000;
						if (this->getAt(count + glm::ivec3(0, 0, 1))->density > 0.0) index |= 0b00010000;
						if (this->getAt(count + glm::ivec3(1, 0, 1))->density > 0.0) index |= 0b00100000;
						if (this->getAt(count + glm::ivec3(1, 1, 1))->density > 0.0) index |= 0b01000000;
						if (this->getAt(count + glm::ivec3(0, 1, 1))->density > 0.0) index |= 0b10000000;

						float density_cube[2][2][2];
						density_cube[0][0][0] = this->getAt(count + glm::ivec3(0, 0, 0))->density;
						density_cube[1][0][0] = this->getAt(count + glm::ivec3(0, 0, 1))->density;
						density_cube[1][1][0] = this->getAt(count + glm::ivec3(0, 1, 0))->density;
						density_cube[0][1][0] = this->getAt(count + glm::ivec3(0, 1, 1))->density;
						density_cube[0][0][1] = this->getAt(count + glm::ivec3(1, 0, 0))->density;
						density_cube[1][0][1] = this->getAt(count + glm::ivec3(1, 0, 1))->density;
						density_cube[1][1][1] = this->getAt(count + glm::ivec3(1, 1, 0))->density;
						density_cube[0][1][1] = this->getAt(count + glm::ivec3(1, 1, 1))->density;

						if (index != 0 && index != 255) //Make sure it's not fully empty or fully filled
						{
							//Get the configuration
							std::vector<Render::Structures::Polygon> polygons = this->getMarchingCubesPolygonConfiguration(index, density_cube, use_density);

							//World::Generation::PerlinNoise noise;
							//Move all those polygons to their correct position in the mesh
							for (unsigned char poly = 0; poly < polygons.size(); poly ++)
							{
								polygons[poly].a.position += pos;
								polygons[poly].b.position += pos;
								polygons[poly].c.position += pos;

								if (use_density && false)
								{
									/*auto v1 = noise.getPerlinVec3(glm::vec4(polygons[poly].a.pos, 17.0f), -3.0f, 1.0f, 1.0f);
									auto v2 = noise.getPerlinVec3(glm::vec4(polygons[poly].b.pos, 17.0f), -3.0f, 1.0f, 1.0f);
									auto v3 = noise.getPerlinVec3(glm::vec4(polygons[poly].c.pos, 17.0f), -3.0f, 1.0f, 1.0f);

									polygons[poly].a.pos += glm::mix(v1, glm::vec3(0.0, 0.0, 0.0), 0.1);
									polygons[poly].b.pos += glm::mix(v2, glm::vec3(0.0, 0.0, 0.0), 0.1);
									polygons[poly].c.pos += glm::mix(v3, glm::vec3(0.0, 0.0, 0.0), 0.1);*/
								}
							}

							//Append them all to the current mesh
							this->mesh->polygons.insert(this->mesh->polygons.end(), polygons.begin(), polygons.end());
						}
					}
				}
			}
		}

		glm::vec3 VoxelActor::getInterp(int edge, float density[2][2][2])
		{
			glm::vec3 p1 = MC_EDGES[edge][0];
			glm::vec3 p2 = MC_EDGES[edge][1];

			float d1 = density[MC_INTEDGES[edge][0].x][MC_INTEDGES[edge][0].y][MC_INTEDGES[edge][0].z];
			float d2 = density[MC_INTEDGES[edge][1].x][MC_INTEDGES[edge][1].y][MC_INTEDGES[edge][1].z];

			float isolevel = 0.5;
			float mu;
			glm::vec3 p;

			/*if (abs(isolevel - d1) < 0.00001)
				return p1;
			if (abs(isolevel - d2) < 0.00001)
				return p2;
			if (glm::abs(d1 - d2) < 0.00001)
				return p1;*/

			if (std::abs(d2 - d1) < 0.0001)
				p = glm::mix(p1, p2, 0.5);
			else
			{
				mu = (isolevel - d1) / (d2 + d1);
				//mu = 0.5;
				p.x = p1.x + mu * (p2.x - p1.x);
				p.y = p1.y + mu * (p2.y - p1.y);
				p.z = p1.z + mu * (p2.z - p1.z);
			}

			//IO::output("x=" + to_string(p1.x) + " y=" + to_string(p2.x) + " z=" + to_string(p.x) + " mu=" + to_string(mu));

			return p;
		}

		std::vector<Render::Structures::Polygon> VoxelActor::getMarchingCubesPolygonConfiguration(unsigned char index, float density[2][2][2], bool use_density)
		{
			std::vector<Render::Structures::Polygon> polygons;
			int triangles[16];

			//Place the triangle array into the triangles
			for (unsigned char c = 0; c < 16; c ++)
			{
				triangles[c] = MC_TRITABLE[index][c];
			}

			//Add the polygons
			for (unsigned char c = 0; c < 15; c += 3)
			{
				if (triangles[c] != -1)
				{
					Render::Structures::Polygon poly;

					if (use_density)
					{
						poly.c.position = this->getInterp(triangles[c + 0], density);
						poly.b.position = this->getInterp(triangles[c + 1], density);
						poly.a.position = this->getInterp(triangles[c + 2], density);
						//poly.b.pos = this->getInterp(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], density[MC_EDGE2VERTEX[triangles[c + 1]][0]], density[MC_EDGE2VERTEX[triangles[c + 1]][1]]);
						//	poly.a.pos = this->getInterp(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], density[MC_EDGE2VERTEX[triangles[c + 2]][0]], density[MC_EDGE2VERTEX[triangles[c + 2]][1]]);

						//poly.c.pos = glm::mix(MC_EDGES[triangles[c + 0]][0], MC_EDGES[triangles[c + 0]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 0]][0]], density[MC_EDGE2VERTEX[triangles[c + 0]][1]]));
						//poly.b.pos = glm::mix(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 1]][0]], density[MC_EDGE2VERTEX[triangles[c + 1]][1]]));
						//poly.a.pos = glm::mix(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], this->getOffset(density[MC_EDGE2VERTEX[triangles[c + 2]][0]], density[MC_EDGE2VERTEX[triangles[c + 2]][1]]));
					}
					else
					{
						poly.c.position = glm::mix(MC_EDGES[triangles[c + 0]][0], MC_EDGES[triangles[c + 0]][1], 0.5);
						poly.b.position = glm::mix(MC_EDGES[triangles[c + 1]][0], MC_EDGES[triangles[c + 1]][1], 0.5);
						poly.a.position = glm::mix(MC_EDGES[triangles[c + 2]][0], MC_EDGES[triangles[c + 2]][1], 0.5);
					}

					poly.a.colour = glm::vec3(1.0, 1.0, 1.0);
					poly.b.colour = glm::vec3(1.0, 1.0, 1.0);
					poly.c.colour = glm::vec3(1.0, 1.0, 1.0);

					poly.correctNormals();

					polygons.push_back(poly);
				}
			}

			return polygons;
		}
	}
}

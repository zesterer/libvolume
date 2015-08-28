//----STANDARD----
#include "stdlib.h"
#include "stdio.h"
#include "fstream"

//----LOCAL----
#include "mesh.h"
#include "common/io.h"
#include "face.h"

namespace LibVolume
{
	namespace Render
	{
		namespace Structures
		{
			Mesh::Mesh()
			{
				
			}
			
			bool Mesh::loadFromOBJ(std::string filename)
			{
				//Clear the polygon vector ready for new data
				this->polygons.clear();

				std::vector<glm::vec3> tmp_pos;
				std::vector<glm::vec3> tmp_col;
				std::vector<glm::vec2> tmp_tex;
				std::vector<glm::vec3> tmp_norm;
				std::vector<Face>      tmp_face;

				//Open the file
				std::ifstream file (filename);

				//Return false if the read operation failed
				if (!IO::test(file.is_open(), "Opening '" + filename + "'"))
					return false;

				//We'll be using this later...
				std::string line;

				//Keep reading file lines from the stream
				while (getline(file, line))
				{
					//Some functions here only take c-style strings, so convert it for them
					const char* c_line = line.c_str();

					//Parse the line
					if (c_line[0] == 'v' && c_line[1] == ' ') //Deal with the vertex positions
					{
						glm::vec3 pos;
						glm::vec3 col;

						bool matches = (sscanf(c_line, "v %f %f %f %f %f %f", &pos.x, &pos.y, &pos.z, &col.r, &col.g, &col.b) == 6);

						if (!matches) //It has no colour
						{
							col = glm::vec3(1.0, 1.0, 1.0); //Let's assume it's white
							matches = (sscanf(c_line, "v %f %f %f", &pos.x, &pos.y, &pos.z) == 3);
						}

						tmp_pos.push_back(pos);
						tmp_col.push_back(col);
					}
					else if (c_line[0] == 'v' && c_line[1] == 't') //Deal with the vertex UV coordinates
					{
						glm::vec2 tex = {-1.0, -1.0};
						sscanf(c_line, "vt %f %f", &tex.x, &tex.y);
						tmp_tex.push_back(tex);
					}
					else if (c_line[0] == 'v' && c_line[1] == 'n') //Deal with the vertex UV coordinates
					{
						glm::vec3 norm; //Default to a non-existent normal
						sscanf(c_line, "vn %f %f %f", &norm.x, &norm.y, &norm.z);
						tmp_norm.push_back(norm);
					}
					else if (c_line[0] == 'f' && c_line[1] == ' ') //Deal with the vertex UV coordinates
					{
						//The actual string
						char vertex[3][20];
						//The ids of all the data
						int pos_index[3], tex_index[3], norm_index[3];

						unsigned char has_parts = 0b00000000; //Got everything

						//Scan the vertex strings
						bool matches = (sscanf(c_line, "f %s %s %s", vertex[0], vertex[1], vertex[2]) == 3);

						if (!IO::test(matches, "Parsing file", false, true))
							return false;

						//Scan each vertex for data
						for (int n = 0; n < 3; n ++)
						{
							//Default to 3-format (with normals)
							matches = (sscanf(vertex[n], "%d/%d/%d", &pos_index[n], &tex_index[n], &norm_index[n]) == 3);
							if (matches)
								has_parts = 0b11100000;


							if (!matches)
							{
								matches = (sscanf(vertex[n], "%d//%d", &pos_index[n], &norm_index[n]) == 2);
								if (matches)
									has_parts = 0b10100000;
							}

							//...and just in case there aren't normals!
							if (!matches)
							{
								matches = (sscanf(vertex[n], "%d/%d", &pos_index[n], &tex_index[n]) == 2);
								if (matches)
									has_parts = 0b11000000;
							}


							if (!IO::test(matches, "Parsing file", false, true))
								return false;
						}

						for (int x = 0; x < 3; x ++)
							if (pos_index[x] < 0) pos_index[x] *= -1;

						for (int x = 0; x < 3; x ++)
							if (tex_index[x] < 0) tex_index[x] *= -1;

						for (int x = 0; x < 3; x ++)
							if (norm_index[x] < 0) norm_index[x] *= -1;

						Face face;

						face.a_pos = pos_index[0];
						face.a_col = pos_index[0];
						face.a_tex = tex_index[0];
						face.a_norm = norm_index[0];

						face.b_pos = pos_index[1];
						face.b_col = pos_index[1];
						face.b_tex = tex_index[1];
						face.b_norm = norm_index[1];

						face.c_pos = pos_index[2];
						face.c_col = pos_index[2];
						face.c_tex = tex_index[2];
						face.c_norm = norm_index[2];

						face.has_parts = has_parts;

						tmp_face.push_back(face);
					}
				}
				
				IO::output("Collected faces from file " + filename);

				for (unsigned long face_id = 0; face_id < tmp_face.size(); face_id ++)
				{
					Face face = tmp_face[face_id];

					Polygon poly;

					//Find the parts of the polygon
					if ((face.has_parts & 0b10000000) == 0b10000000) //If we have position data
					{
						poly.a.position = tmp_pos[face.a_pos - 1];
						poly.b.position = tmp_pos[face.b_pos - 1];
						poly.c.position = tmp_pos[face.c_pos - 1];
					}

					poly.a.colour = tmp_col[face.a_col - 1];
					poly.b.colour = tmp_col[face.b_col - 1];
					poly.c.colour = tmp_col[face.c_col - 1];

					if ((face.has_parts & 0b01000000) == 0b01000000) //If we have texture data
					{
						poly.a.uv_coords = tmp_tex[face.a_tex - 1];
						poly.b.uv_coords = tmp_tex[face.b_tex - 1];
						poly.c.uv_coords = tmp_tex[face.c_tex - 1];
					}

					//We got normals!
					if ((face.has_parts & 0b00100000) == 0b00100000 && false) //If we have normal data
					{
						//Set to default normals
						poly.a.normal = tmp_norm[face.a_norm - 1];
						poly.b.normal = tmp_norm[face.b_norm - 1];
						poly.c.normal = tmp_norm[face.c_norm - 1];
					}
					else //Otherwise, calculate our own normals (not smoothed)
					{
						poly.correctNormals();
						/*
						glm::vec3 a = glm::vec3(tmp_pos[face.a_pos - 1].x, tmp_pos[face.a_pos - 1].y, tmp_pos[face.a_pos - 1].z);
						glm::vec3 b = glm::vec3(tmp_pos[face.b_pos - 1].x, tmp_pos[face.b_pos - 1].y, tmp_pos[face.b_pos - 1].z);
						glm::vec3 c = glm::vec3(tmp_pos[face.c_pos - 1].x, tmp_pos[face.c_pos - 1].y, tmp_pos[face.c_pos - 1].z);
						glm::vec3 n0 = glm::cross(b - a, c - a);
						n0 /= glm::length(n0);
						poly.a.norm = {n0.x, n0.y, n0.z};
						poly.b.norm = {n0.x, n0.y, n0.z};
						poly.c.norm = {n0.x, n0.y, n0.z};
						*/
					}

					this->polygons.push_back(poly);
				}
				
				return true;
			}
			
			void Mesh::buffer()
			{
				//Clear any existing memory before rebuffering
				if (this->buffered)
					gl::glDeleteVertexArrays(1, &this->gl_id);
				
				//Create the vertex array id and bind it
				gl::glGenVertexArrays(1, &this->gl_id);
				gl::glBindVertexArray(this->gl_id);

				//Create the vertex buffer id and bind it
				gl::glGenBuffers(1, &this->gl_id);
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_id);

				//Pass the vertex position data to GL (the graphics card)
				gl::glBufferData(gl::GL_ARRAY_BUFFER, this->polygons.size() * sizeof(Polygon), &this->polygons[0], gl::GL_STATIC_DRAW);

				this->buffered = true;
				IO::output("Buffered model with " + std::to_string(this->polygons.size()) + " polygons.");

				//We've buffered the data, so let's clear it
				//if (this->clear_on_buffer)
					//this->polygons.clear();
			}
		}
	}
}

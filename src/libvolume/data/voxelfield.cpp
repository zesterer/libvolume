//----LOCAL----
#include "voxelfield.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Data
	{
		VoxelField::VoxelField(glm::ivec3 size)
		{
			this->size = size;
			this->voxels.reserve(this->size.x * this->size.y * this->size.z);
		}

		VoxelField::~VoxelField()
		{

		}

		Voxel* VoxelField::getAt(glm::ivec3 pos)
		{
			if (pos.x < 0 || pos.x >= this->size.x)
				return &this->empty;
			if (pos.y < 0 || pos.y >= this->size.y)
				return &this->empty;
			if (pos.z < 0 || pos.z >= this->size.z)
				return &this->empty;

			return &this->voxels[this->size.y * this->size.z * pos.x + this->size.z * pos.y + pos.z];
		}

		float VoxelField::getDensityAt(glm::vec3 pos)
		{
			glm::vec3 mpos = glm::fract(pos);
			glm::ivec3 ppos = glm::ivec3(pos.x, pos.y, pos.z);

			float density_o[8];
			density_o[0b000] = this->getAt(ppos + glm::ivec3(0, 0, 0))->density;
			density_o[0b001] = this->getAt(ppos + glm::ivec3(0, 0, 1))->density;
			density_o[0b010] = this->getAt(ppos + glm::ivec3(0, 1, 0))->density;
			density_o[0b011] = this->getAt(ppos + glm::ivec3(0, 1, 1))->density;
			density_o[0b100] = this->getAt(ppos + glm::ivec3(1, 0, 0))->density;
			density_o[0b101] = this->getAt(ppos + glm::ivec3(1, 0, 1))->density;
			density_o[0b110] = this->getAt(ppos + glm::ivec3(1, 1, 0))->density;
			density_o[0b111] = this->getAt(ppos + glm::ivec3(1, 1, 1))->density;

			float eX00 = glm::mix(density_o[0b000], density_o[0b100], mpos.x);
			float eX10 = glm::mix(density_o[0b010], density_o[0b110], mpos.x);
			float eX01 = glm::mix(density_o[0b001], density_o[0b101], mpos.x);
			float eX11 = glm::mix(density_o[0b011], density_o[0b111], mpos.x);

			float fXX0 = glm::mix(eX00, eX10, mpos.y);
			float fXX1 = glm::mix(eX01, eX11, mpos.y);

			return glm::mix(fXX0, fXX1, mpos.z);
		}

		glm::vec3 VoxelField::getNormalAt(glm::vec3 pos)
		{
			float d = this->getDensityAt(pos);
			float nx = this->getDensityAt(pos + glm::vec3(1.0, 0.0, 0.0) * 0.01f) - d;
			float ny = this->getDensityAt(pos + glm::vec3(0.0, 1.0, 0.0) * 0.01f) - d;
			float nz = this->getDensityAt(pos + glm::vec3(0.0, 0.0, 1.0) * 0.01f) - d;
			return glm::normalize(glm::vec3(-nx, -ny, -nz));
		}
	}
}

//----LOCAL----
#include "voxelterrain.h"
#include "io.h"

namespace LibVolume
{
	namespace Engine
	{
		VoxelTerrain::VoxelTerrain(glm::ivec3 child_size) : Data::VoxelCluster(child_size)
		{
			this->renderable = true;
			this->rendertype = Render::RenderType::VoxelTerrain;
			this->objecttype = ObjectType::VoxelTerrainObject;
		}

		bool VoxelTerrain::loadAt(glm::ivec3 pos)
		{
			if (this->children.count(this->vecToKey(pos)) > 0)
				return false;

			//Add the new region
			Data::VoxelField* tmp = dynamic_cast<Data::VoxelField*>(new VoxelTerrainChild(this->child_size));
			this->children.insert({this->vecToKey(pos), tmp});

			//Set it's parent
			dynamic_cast<VoxelTerrainChild*>(tmp)->parent = this;

			//Set it's state
			dynamic_cast<VoxelTerrainChild*>(tmp)->mesh_state.position = pos * this->child_size;

			//Set it's position
			dynamic_cast<VoxelTerrainChild*>(tmp)->location = pos * this->child_size;

			//TODO
			//Make sure it meshes correctly
			dynamic_cast<VoxelTerrainChild*>(tmp)->mesh_first_plane = false;

			IO::output("Loaded region!");

			return true;
		}

		VoxelTerrainChild* VoxelTerrain::getAt(glm::ivec3 pos)
		{
			if (!this->existsAt(pos / this->child_size))
				this->loadAt(pos);

			return dynamic_cast<VoxelTerrainChild*>(this->children.at(this->vecToKey(pos)));
		}

		Data::Voxel* VoxelTerrain::getVoxelAt(glm::ivec3 pos)
		{
			//IO::output(std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + std::to_string(pos.z));
			//IO::output(std::to_string(pos.x / this->child_size.x) + "," + std::to_string(pos.y / this->child_size.y) + "," + std::to_string(pos.z / this->child_size.z));

			glm::ivec3 p = pos;
			p += 10 * this->child_size;
			p /= this->child_size;
			p -= 10;

			if (this->existsAt(p))
				return this->getAt(p)->getAt((pos + 10 * this->child_size) % this->child_size);
			else
				return &this->empty;
		}

		void VoxelTerrain::tick()
		{
			for (auto region_pair : this->children)
			{
				Engine::VoxelTerrainChild* region = dynamic_cast<VoxelTerrainChild*>(region_pair.second);
				region->state = this->state;
				region->mesh_state.tick();
				region->tick();
			}
		}
	}
}

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
		}

		bool VoxelTerrain::loadAt(glm::ivec3 pos)
		{
			if (this->children.count(this->vecToKey(pos)) > 0)
				return false;

			//Add the new region
			Data::VoxelField* tmp = dynamic_cast<Data::VoxelField*>(new VoxelActor(this->child_size));
			this->children.insert({this->vecToKey(pos), tmp});

			//Set it's state
			dynamic_cast<VoxelActor*>(tmp)->mesh_state.position = glm::vec3((float)(pos.x * this->child_size.x), (float)(pos.y * this->child_size.y), (float)(pos.z * this->child_size.z));

			IO::output("Loaded region!");

			return true;
		}

		VoxelActor* VoxelTerrain::getAt(glm::ivec3 pos)
		{
			if (this->children.count(this->vecToKey(pos)) == 0)
				this->loadAt(pos);

			return dynamic_cast<VoxelActor*>(this->children.at(this->vecToKey(pos)));
		}

		void VoxelTerrain::tick()
		{
			for (auto region_pair : this->children)
			{
				Engine::VoxelActor* region = dynamic_cast<VoxelActor*>(region_pair.second);
				region->state = this->state;
				region->tick();
			}
		}
	}
}

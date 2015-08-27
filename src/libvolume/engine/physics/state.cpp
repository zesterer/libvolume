//----LOCAL----
#include "state.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		namespace Physics
		{
			void PointState::update()
			{
				//Clear the matrix ready to change it
				this->matrix = glm::mat4(1.0f);
				
				//Apply positional transformations
				this->matrix = glm::translate(this->matrix, this->position);
			}
			
			void BodyState::update()
			{
				//Clear the matrix ready to change it
				this->matrix = glm::mat4(1.0f);
				
				//Apply quaternion orientational transformations
				this->matrix = glm::toMat4(this->orientation) * this->matrix;
				
				//Apply positional transformations
				this->matrix = glm::translate(this->matrix, this->position);
				
				//Scale
				this->matrix = glm::scale(this->matrix, this->scale);
			}
			
			void DynamicState::update()
			{
				//For the moment, this method is the same as it's parent
				//This will probably change later
				BodyState::update();
			}
			
			void DynamicState::tick()
			{
				this->position += this->velocity;
				
				//Normalise the quaternions (or they will gradually decay)
				normalize(this->orientation);
				normalize(this->spin);
				
				this->orientation *= this->spin;
				
				this->update();
			}
		}
	}
}

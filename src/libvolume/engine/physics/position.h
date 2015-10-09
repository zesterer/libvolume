#ifndef LIBVOLUME_ENGINE_PHYSICS_POSITION_H
#define LIBVOLUME_ENGINE_PHYSICS_POSITION_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef LIBVOLUME_COORDINATE_LIMITS
#define LIBVOLUME_COORDINATE_LIMITS 1048576.0f
#endif

namespace LibVolume
{
	namespace Engine
	{
		namespace Physics
		{
			struct Position
			{
				glm::vec3 layer[4];

				Position(float x, float y, float z);
				Position(double x, double y, double z);
				void update();
				Position& operator+(const Position& pos);
				Position& operator+=(const Position& pos);
				Position& operator-(const Position& pos);
				Position& operator-=(const Position& pos);
				Position& operator*(const Position& pos);
				Position& operator=(const Position& pos);

				Position& operator+(const glm::vec3& vec);
				Position& operator+=(const glm::vec3& vec);
				Position& operator-(const glm::vec3& vec);
				Position& operator-=(const glm::vec3& vec);
				Position& operator=(const glm::vec3& vec);
			};
		}
	}
}

#endif

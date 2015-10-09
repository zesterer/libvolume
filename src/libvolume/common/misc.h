//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace LibVolume
{
	glm::f32mat4 matrix64To32(glm::f64mat4 matrix);
}

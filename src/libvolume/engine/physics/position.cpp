//----LOCAL----
#include "position.h"

namespace LibVolume
{
	namespace Engine
	{
		namespace Physics
		{
			Position::Position(float x, float y, float z)
			{
				this->layer[0] = glm::vec3(x, y, z);
				this->update();
			}

			Position::Position(double x, double y, double z)
			{
				this->layer[0] = glm::vec3(x, y, z);
				this->update();
			}

			void Position::update()
			{
				for (int c = 1; c < 4; c ++)
				{
					this->layer[c] += glm::floor(this->layer[c - 1] + LIBVOLUME_COORDINATE_LIMITS) / LIBVOLUME_COORDINATE_LIMITS - 1.0f;
					this->layer[c - 1] = glm::mod(this->layer[c - 1], LIBVOLUME_COORDINATE_LIMITS);
				}
			}

			Position& Position::operator+(const Position& pos)
			{
				Position result;
				for (int c = 0; c < 4; c ++)
					result.layer[c] = this->layer[c] + pos.layer[c];
				result.update();
				return result;
			}

			Position& Position::operator+=(const Position& pos)
			{
				*this = *this + pos;
				this->update();
				return *this;
			}

			Position& Position::operator-(const Position& pos)
			{
				Position result;
				for (int c = 0; c < 4; c ++)
					result.layer[c] = this->layer[c] - pos.layer[c];
				result.update();
				return result;
			}

			Position& Position::operator-=(const Position& pos)
			{
				*this = *this - pos;
				this->update();
				return *this;
			}

			Position& Position::operator*(const Position& pos)
			{
				Position result;
				for (int c0 = 0; c0 < 4; c0 ++)
				{
					for (int c1 = 0; c1 < 4; c1 ++)
						result.layer[c0] = this->layer[c0] * pos.layer[c1];
				}
				result.update();
				return result;
			}

			Position& Position::operator=(const Position& pos)
			{
				for (int c = 0; c < 4; c ++)
					this->layer[c] = pos.layer[c];
				this->update();
				return *this;
			}

			Position& Position::operator+(const glm::vec3& vec)
			{
				Position result;
				result.layer[0] = this->layer[0] + vec;
				result.update();
				return result;
			}

			Position& Position::operator+=(const glm::vec3& vec)
			{
				this
				return *this;
			}

			Position& Position::operator-(const glm::vec3& vec)
			{
				Position result;
				result.layer[0] = this->layer[0] - vec;
				result.update();
				return result;
			}

			Position& Position::operator=(const glm::vec3& vec)
			{
				for (int c = 0; c < 4; c ++)
					this->layer[c] = glm::vec3(0.0, 0.0, 0.0);
				this->layer[0] = vec;
				this->update();
				return *this;
			}
		}
	}
}

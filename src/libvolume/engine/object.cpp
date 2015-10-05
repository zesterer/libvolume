//----LOCAL----
#include "object.h"
#include "realm.h"
#include "io.h"

namespace LibVolume
{
	namespace Engine
	{
		Object::Object()
		{

		}

		void Object::tick() const
		{
			if (((Object*)this)->timeout > 0)
				((Object*)this)->timeout --;
		}

		Object::~Object()
		{
			if (this->parent != nullptr)
				this->parent->removeObject(*this);
		}
	}
}

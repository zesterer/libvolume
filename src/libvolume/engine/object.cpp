//----LOCAL----
#include "object.h"
#include "realm.h"

namespace LibVolume
{
	namespace Engine
	{
		Object::Object()
		{

		}

		void Object::tick()
		{

		}

		Object::~Object()
		{
			if (this->parent != nullptr)
				this->parent->removeObject(*this);
		}
	}
}

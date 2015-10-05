#ifndef LIBVOLUME_ENGINE_OBJECT_H
#define LIBVOLUME_ENGINE_OBJECT_H

namespace LibVolume
{
	namespace Engine
	{
		//Forward declaration of Realm
		class Realm;

		//Anything that inherits this class can be stored in a realm's object std::vector
		//And also has the ability to tick
		class Object
		{
			public:
				//This property should only be true if the object inherits
				//from the 'Render::RenderTarget' class.
				bool renderable = false;

				long timeout = -1;

				Realm* parent = nullptr;

				Object();
				virtual ~Object();
				virtual void tick() const;
		};
	}
}

#endif

//----LOCAL----
#include "realm.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Engine
	{
		Realm::Realm()
		{
			IO::output("Created realm");
		}
		
		void Realm::tick()
		{
			//Time in seconds
			this->time += 1.0;
		}
		
		void Realm::render()
		{
			this->renderer.preRender();
			
			//Add rendering here
		}
	}
}

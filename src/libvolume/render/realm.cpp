//----LOCAL----
#include "realm.h"
#include "common/io.h"

namespace LibVolume
{
	namespace Render
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
	}
}

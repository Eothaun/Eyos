#include "eyos/ClientEcsType.h"

namespace eyos
{
	void RegisterClientEcsTypes(Ecs& ecs)
	{
		// NO ecs_builtins::EcsTrackable here. Because the default Ecs automatically adds that flag
		ecs.RegisterTypes<
			rendering_components::Transform, 
			rendering_components::Model3D, 
			rendering_components::InstancedModel>();
	}

}
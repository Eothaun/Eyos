#pragma once
#include "engine/ecs/Ecs.h"
#include "rendering/Components.h"

namespace eyos {
	using EyosEcs = Ecs<
		rendering_components::Transform, 
		rendering_components::Model3D, 
		rendering_components::InstancedModel, 
		ecs_builtins::EcsTrackable>;
}

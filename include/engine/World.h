#pragma once
#include <engine/ecs/Ecs.h>
#include <engine/ResourceManager.h>
#include <engine/EngineEvents.h>
#include <engine/Time.h>
namespace eyos {
	struct World {
		Ecs ecs;
		ResourceManager resourceManager;
		EngineEvents engineEvents;
		Time time;
	};
}
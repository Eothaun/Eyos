#include <engine/ecs/Ecs.h>
#include <engine/ResourceManager.h>
#include <engine/EngineEvents.h>
#include <engine/Time.h>
namespace eyos {
	// TODO: Add missing system Manager
	template<typename ESCT>
	struct World {
		ESCT esc;
		ResourceManager resourceManager;
		EngineEvents engineEvents;
		Time time;
	};
}
#include <engine/ecs/Ecs.h>
#include <engine/ResourceManager.hpp>
#include <engine/EngineEvents.hpp>
#include <engine/Time.hpp>
namespace eyos {
	// TODO: Add missing system Manager
	template<typename ESCT,typename GameEvents>
	struct World {
		ESCT esc;
		ResourceManager resourceManager;
		EngineEvents engineEvents;
		GameEvents gameEvents;
		Time time;
	};
}


namespace eyos::nav
{

	class TerrainNav {
	public:
		TerrainNav();

		bool Init();
		
		bool Shutdown();

	private:
		//void MoveModels(EyosEcs& ecs);
		//void MoveInstancedModels(EyosEcs& ecs);

	};
}
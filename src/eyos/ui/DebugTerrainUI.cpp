#include "eyos/ui/DebugTerrainUI.h"
#include "engine/gen/MapGeneration.h"
#include <imgui/imgui.h>
#include <iostream>

namespace eyos::gen
{
	float frequency = 2.0f;
	int imageSize = 512;
	int octaves = 2;
	int seed = 2;

	void DrawTerrainToolImgui(std::string& path)
	{
		ImGui::SetNextWindowSize(
			ImVec2(300.0f, 210.0f)
			, ImGuiCond_FirstUseEver
		);
		ImGui::SetNextWindowPos(
			ImVec2(50.0f, 300.0f)
			, ImGuiCond_FirstUseEver
		);

		ImGui::Begin("DebugTerrainTool ImGUI");
		
		
		static char str[128] = "../data/maps/";
		ImGui::InputFloat("frequency", &frequency, 0.0f, 10.0f);
		ImGui::InputInt("imageSize", &imageSize, 1, 2000);
		ImGui::InputInt("octaves", &octaves, 1, 10);
		ImGui::InputInt("seed", &seed, 0, 10000);
		//ImGui::InputText("path", str, IM_ARRAYSIZE(str));
		path = str;
		if (ImGui::Button("Generate"))
		{
			path = MapGeneration::GenHeightMap(path,imageSize,frequency,octaves,seed);
		}
		else
		{
			path = "";
		}
		
		ImGui::End();
	}
}
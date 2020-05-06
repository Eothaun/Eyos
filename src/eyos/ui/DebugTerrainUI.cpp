#pragma once
#include "eyos/Config.h"
#include "eyos/ui/DebugTerrainUI.h"
#include "engine/gen/MapGeneration.h"
#include <imgui/imgui.h>
#include <iostream>

namespace eyos::gen
{
	float frequency{ setting::terrain::frequency };
	int imageSize{setting::terrain::imageSize};
	int octaves{setting::terrain::octaves};
	int seed{setting::terrain::seed};
	char path_str[128]{};
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
		
		
		
		memcpy(path_str,path.data(),path.size());
		ImGui::InputFloat("frequency", &frequency, 0.0f, 10.0f);
		ImGui::InputInt("imageSize", &imageSize, 1, 2000);
		ImGui::InputInt("octaves", &octaves, 1, 10);
		ImGui::InputInt("seed", &seed, 0, 10000);
		ImGui::InputText("path", path_str, IM_ARRAYSIZE(path_str));
		path = path_str;
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
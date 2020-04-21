#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "engine/Defines.h"

struct node
{
	glm::vec2 pos;
	int distance;
	int weight;
};

class EYOS_API FlowField
{
public:
	FlowField();
	~FlowField();

	void GenerateFlowField();
private:

	
	void GenerateDijkstraGrid(std::vector<glm::vec2> obstacles);
	std::vector<node> NeighboursOf(node& node);
	std::vector<node> AllNeighboursOf(node& neighbour);

	int gridWidth = 10;
	int gridHeight = 10;
	std::vector<std::vector<node>> dijkstraGrid;
};


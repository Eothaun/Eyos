#include "engine/gen/FlowField.h"

FlowField::FlowField()
{
	dijkstraGrid = std::vector<std::vector<node>>(gridWidth);
}

FlowField::~FlowField()
{
}

void FlowField::GenerateFlowField()
{
	GenerateDijkstraGrid(std::vector<glm::vec2>{ {2, 4}, { 5,6 }});

	int x, y;

	std::vector<std::vector<glm::vec2>> flowField(gridWidth); 
	for (x = 0; x < gridWidth; x++)
	{
		std::vector<glm::vec2> arr(gridHeight);
		for (y = 0; y < gridHeight; y++)
		{
			arr[y] = glm::vec2(0,0);
		}
		flowField[x] = arr;
	}

	for (x = 0; x < gridWidth; x++)
	{
		for (y = 0; y < gridHeight; y++)
		{
			if (dijkstraGrid[x][y].weight == INT_MAX)
			{
				continue;
			}

			std::vector neighbours = AllNeighboursOf(dijkstraGrid[x][y]);

			node min = node();
			float minDist = 0;

			for (int i = 0; i < neighbours.size(); i++)
			{
				
				node n = neighbours[i];
				float dist = dijkstraGrid[n.pos.x][n.pos.y].weight - dijkstraGrid[x][y].weight;
				
				//if (i == 0) minDist = dist;
				//if (dist < minDist)
				//	minDist = dist;

				if (dist < minDist)
				{
					n.distance = dist;

					min = n;
					minDist = dist;
					
				}
			}

			//if valid neightbour point in its direction
			if (min.distance != 0)
			{
				flowField[x][y] = glm::normalize(min.pos - dijkstraGrid[x][y].pos);
			}
		}
	}
}



void FlowField::GenerateDijkstraGrid(std::vector<glm::vec2> obstacles)
{
	int gridWidth = 10;
	int gridHeight = 10;


	for (int x = 0; x < gridWidth; x++)
	{
		std::vector<node> arr(gridHeight);
		for (int y = 0; y < gridHeight; y++)
		{
			arr[y].weight = 0;
			arr[y].pos = glm::vec2(x, y);
			arr[y].distance = 0;
		}
		dijkstraGrid[x] = arr;
	}

	//set all places with obstacles with weight of MAXINT
	for (int i = 0; i<obstacles.size(); i++)
	{
		glm::vec2 t = obstacles[i];

		dijkstraGrid[t.x][t.y].weight = INT_MAX;
	}

	node pathEnd;
	pathEnd.distance = 0;
	pathEnd.pos = { 2,4 };
	pathEnd.weight = 0;

	dijkstraGrid[pathEnd.pos.x][pathEnd.pos.y].weight = 0;

	std::vector<node> toVisit{ pathEnd };

	for (int i = 0; i < toVisit.size(); i++)
	{
		std::vector<node> neighbours = NeighboursOf(toVisit[i]);

		//for each neighbour of this node (only straight line neighbours)
		for (int j = 0; j < neighbours.size(); j++)
		{
			node n = neighbours[j];

			if (dijkstraGrid[n.pos.x][n.pos.y].weight == 0)
			{
				n.distance = toVisit[i].distance + 1;
				dijkstraGrid[n.pos.x][n.pos.y].weight = n.distance;
				toVisit.push_back(n);
			}
		}
	}

}

//no diagonal neighbours
std::vector<node> FlowField::NeighboursOf(node& neighbour)
{
	std::vector<node> neighbours;
	if (neighbour.pos.x != gridWidth-1) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x + 1][neighbour.pos.y]);
	if (neighbour.pos.x != 0) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x - 1][neighbour.pos.y]);
	if (neighbour.pos.y != gridHeight-1) neighbours.push_back(dijkstraGrid[neighbour.pos.x][(int)neighbour.pos.y + 1]);
	if (neighbour.pos.y != 0)neighbours.push_back(dijkstraGrid[neighbour.pos.x][(int)neighbour.pos.y - 1]);
	return neighbours;
}

//all neighbours including diagonal
std::vector<node> FlowField::AllNeighboursOf(node& neighbour)
{
	std::vector<node> neighbours;
	if (neighbour.pos.x != gridWidth -1) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x + 1][neighbour.pos.y]);
	if(neighbour.pos.x != 0) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x - 1][neighbour.pos.y]);
	if (neighbour.pos.y != gridHeight -1) neighbours.push_back(dijkstraGrid[neighbour.pos.x][(int)neighbour.pos.y + 1]);
	if(neighbour.pos.y != 0 )neighbours.push_back(dijkstraGrid[neighbour.pos.x][(int)neighbour.pos.y - 1]);

	if (neighbour.pos.x != gridWidth - 1 && neighbour.pos.y != gridHeight -1) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x + 1][(int)neighbour.pos.y + 1]);
	if (neighbour.pos.x != 0 && neighbour.pos.y != 0) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x - 1][(int)neighbour.pos.y - 1]);
	if (neighbour.pos.y != gridHeight - 1 && neighbour.pos.x != 0) neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x - 1][(int)neighbour.pos.y + 1]);
	if (neighbour.pos.y != 0 && neighbour.pos.x != gridWidth - 1)neighbours.push_back(dijkstraGrid[(int)neighbour.pos.x + 1][(int)neighbour.pos.y - 1]);
	return neighbours;
}
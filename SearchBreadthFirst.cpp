//	SearchBreadthFirst.cpp - Niall Starkey

//
//	Implementation of Search class for Breadth-first algorithm
//

#include "SearchBreadthFirst.h"

//  FUNCTIONS:  //
bool CSearchBreadthFirst::FindPath(MapManager& mapManager, NodeList& openList,
	NodeList& closedList, NodeList& pathList,
	std::unique_ptr<SNode>& currentNode,
	std::unique_ptr<SNode>& end)
{
	currentNode = move(openList.front());
	openList.pop_front();

	if (currentNode->x == end->x)
	{
		if (currentNode->y == end->y)
		{
			pathList.push_front(move(currentNode));
			return true;
		}
	}
	GetNeighbourNodes(mapManager, currentNode, openList, closedList);
	closedList.push_front(move(currentNode));
	return false;
}

void CSearchBreadthFirst::GetNeighbourNodes(MapManager& mapManager,
	std::unique_ptr<SNode>& currentNode,
	NodeList& openList, NodeList& closedList)
{
	int count = 0;

	std::unique_ptr<SNode> North(new SNode);
	North->x = currentNode->x;
	North->y = currentNode->y + 1;

	std::unique_ptr<SNode> East(new SNode);
	East->x = currentNode->x + 1;
	East->y = currentNode->y;

	std::unique_ptr<SNode> South(new SNode);
	South->x = currentNode->x;
	South->y = currentNode->y - 1;

	std::unique_ptr<SNode> West(new SNode);
	West->x = currentNode->x - 1;
	West->y = currentNode->y;

	auto p = mapManager.unopenedList.begin();
	while (p != mapManager.unopenedList.end() && count != 4)
	{
		if (North->x == (*p)->x && North->y == (*p)->y)
		{
			if (!FindInList(North, openList) && !FindInList(North, closedList))
			{
				if (GetCost(mapManager, North->x, North->y) != 0)
				{
					(*p)->parent = currentNode.get();
					openList.push_back(move((*p)));
					p = mapManager.unopenedList.erase(p);
				}
				else
				{
					p++;
				}
			}
			else
			{
				p++;
			}
			count++;
		}
		else if (East->x == (*p)->x && East->y == (*p)->y)
		{
			if (!FindInList(East, openList) && !FindInList(East, closedList))
			{
				if (GetCost(mapManager, East->x, East->y) != 0)
				{
					(*p)->parent = currentNode.get();
					openList.push_back(move((*p)));
					p = mapManager.unopenedList.erase(p);
				}
				else
				{
					p++;
				}
			}
			else
			{
				p++;
			}
			count++;
		}
		else if (South->x == (*p)->x && South->y == (*p)->y)
		{
			if (!FindInList(South, openList) && !FindInList(South, closedList))
			{
				if (GetCost(mapManager, South->x, South->y) != 0)
				{
					(*p)->parent = currentNode.get();
					openList.push_back(move((*p)));
					p = mapManager.unopenedList.erase(p);
				}
				else
				{
					p++;
				}
			}
			else
			{
				p++;
			}
			count++;
		}
		else if (West->x == (*p)->x && West->y == (*p)->y)
		{
			if (!FindInList(West, openList) && !FindInList(West, closedList))
			{
				if (GetCost(mapManager, West->x, West->y) != 0)
				{
					(*p)->parent = currentNode.get();
					openList.push_back(move((*p)));
					p = mapManager.unopenedList.erase(p);
				}
				else
				{
					p++;
				}
			}
			else
			{
				p++;
			}
			count++;
		}
		else
		{
			p++;
		}
	}
}

ETerrainCost CSearchBreadthFirst::GetCost(MapManager& mapManager, int x, int y)
{
	std::vector<ETerrainCost> row = mapManager.terrain[y];
	return row[x];
}

bool CSearchBreadthFirst::FindInList(std::unique_ptr<SNode>& node, NodeList& list)
{
	std::deque<std::unique_ptr<SNode>>::iterator p;

	for (auto p = list.begin(); p != list.end(); p++)
	{
		if (node->x == (*p)->x)
		{
			if (node->y == (*p)->y)
			{
				return true;
			}
		}
	}

	return false;
}

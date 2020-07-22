//	MapManager.cpp - Niall Starkey

//
//	Manager for creating, deleting and storing maps.
//

#include "MapManager.h"

//  GETTERS:  //

//  FUNCTIONS:  //
void MapManager::GetMapText(string mapLocation)
{
	std::deque<std::string> fileText;
	std::string	line;
	std::ifstream infile;

	infile.open(mapLocation);

	while (!infile.eof())
	{
		getline(infile, line);
		fileText.push_front(line);
	}

	fileText.pop_front();
	fileText.pop_back();
	infile.close();
	map.swap(fileText);
}

void MapManager::MoveCamera(EMap map)
{
	if (map == dMap || map == mMap || map == tMap)
	{
		camera->SetPosition(45, 110, 45);	// 0, 1, 3
	}
	else if (map == sMap)
	{
		camera->SetPosition(60, 110, 35);	// 2
	}
	else if (map == xMap)
	{
		camera->SetPosition(25, 70, 25);	// 4
	}
}

void MapManager::GetCoords(std::unique_ptr<SNode>& start,
	std::unique_ptr<SNode>& end,
	string coordsLocation)
{
	std::deque<std::string> fileText;
	std::string	line;
	std::ifstream infile;

	infile.open(coordsLocation);

	while (!infile.eof())
	{
		getline(infile, line);
		fileText.push_back(line);
	}

	/*fileText.pop_back();*/

	for (int i = 0; i < fileText.size(); i++)
	{
		if (i == 0)
		{
			std::vector<std::string> coords = SplitString(fileText[i]);
			start->x = stoi(coords[0]);
			start->y = stoi(coords[1]);
		}
		else if (i == 1)
		{
			std::vector<std::string> coords = SplitString(fileText[i]);
			end->x = stoi(coords[0]);
			end->y = stoi(coords[1]);
		}
	}

	infile.close();
}


std::vector<std::string> MapManager::SplitString(std::string text)
{
	std::vector<std::string>	container;
	std::stringstream			stream(text);
	std::string					token = "";

	while (std::getline(stream, token, ' '))
	{
		container.push_back(token);
	}

	return container;
}

void MapManager::CreateMap(std::unique_ptr<SNode>& startNode,
	std::unique_ptr<SNode>& endNode,
	std::vector<std::string>& skins)
{
	for (int i = 0; i < map.size(); i++)
	{
		vector<ETerrainCost> row;
		string line = map[i];

		for (int j = 0; j < line.length(); j++)
		{
			string cost;
			cost += line[j];
			ETerrainCost terrainCost = (ETerrainCost)stoi(cost);
			row.push_back(terrainCost);

			tle::IModel* model = nodeMesh->CreateModel(j * 10, 0, i * 10);

			std::unique_ptr<SNode> node(new SNode);
			node->x = j;
			node->y = i;
			node->model = model;

			if (i == startNode->y && j == startNode->x)
			{
				model->SetSkin(skins[4]);
				node->parent = 0;
				unopenedList.push_back(move(node));

				std::unique_ptr<SNode> start(new SNode);
				start->x = j;
				start->y = i;
				start->parent = 0;
				startNode = move(start);
			}
			else if (i == endNode->y && j == endNode->x)
			{
				model->SetSkin(skins[4]);
				node->parent = 0;
				unopenedList.push_back(move(node));

				model->SetSkin(skins[6]);
				std::unique_ptr<SNode> end(new SNode);
				end->x = j;
				end->y = i;
				end->parent = 0;
				endNode = move(end);
			}
			else
			{
				model->SetSkin(skins[stoi(cost)]);
				unopenedList.push_back(move(node));
			}
		}

		terrain.push_back(row);
	}
}

void MapManager::DeleteModels(NodeList& list)
{
	std::deque<std::unique_ptr<SNode>>::iterator;
	for (auto p = list.begin(); p != list.end(); p++)
	{
		(*p)->model->~IModel();
	}
}

bool MapManager::GetPath(NodeList& path, NodeList& openList, NodeList& closedList)
{
	bool pathFound = false;

	while (!pathFound)
	{
		if ((*path.begin())->parent == 0)
		{
			return true;
		}

		bool parentFound = false;

		NodeList::iterator p;
		if (!parentFound)
		{
			for (auto p = closedList.begin(); p != closedList.end(); p++)
			{
				if ((*p)->x == (*path.begin())->parent->x &&
					(*p)->y == (*path.begin())->parent->y)
				{
					path.push_front(move((*p)));
					closedList.erase(p);
					parentFound = true;
					break;
				}
			}
		}

		if (!parentFound)
		{
			for (auto p = openList.begin(); p != openList.end(); p++)
			{
				if ((*p)->x == (*path.begin())->parent->x &&
					(*p)->y == (*path.begin())->parent->y)
				{
					path.push_front(move((*p)));
					openList.erase(p);
					parentFound = true;
					break;
				}
			}
		}
	}

	return false;
}

void MapManager::HighlightPath(NodeList& list, string skin)
{
	std::deque<std::unique_ptr<SNode>>::iterator;
	for (auto p = list.begin(); p != list.end(); p++)
	{
		(*p)->model->SetSkin(skin);
	}
}

void MapManager::LoadNewMap(std::unique_ptr<SNode>& startNode,
	std::unique_ptr<SNode>& endNode, string mapLocation, string coordsLocation,
	std::vector<std::string> skins,
	EMap currentMap)
{
	map.clear();
	terrain.clear();
	DeleteModels(unopenedList);
	unopenedList.clear();
	startNode.reset(new SNode);
	startNode->parent = 0;
	endNode.reset(new SNode);

	GetMapText(mapLocation);
	GetCoords(startNode, endNode, coordsLocation);
	CreateMap(startNode, endNode, skins);
	MoveCamera(currentMap);
}

//  CONSTRUCTORS:  //
MapManager::MapManager(tle::I3DEngine* engine)
{
	camera = engine->CreateCamera(tle::kManual);
	camera->RotateX(90);

	nodeMesh = engine->LoadMesh("cube.x");
}

//  DESTRUCTORS:  //
MapManager::~MapManager()
{
}
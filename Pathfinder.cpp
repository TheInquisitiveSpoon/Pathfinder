//	Pathfinder.cpp - Niall Starkey

//
// Main source for Pathfinding porfect
//

//	TODO:
//			Implement Depth first
//			Implement Breadth first
//			Implement A*

//  HEADERS:  //
#include <TL-Engine.h>
#include <iostream>
#include "Search.h"
#include "SearchFactory.h"
#include "Definitions.h"
#include "MapManager.h"

//  FILES:  //
const std::vector<std::string> mapFiles =
{
	"./Maps/dMap.txt",
	"./Maps/mMap.txt",
	"./Maps/sMap.txt",
	"./Maps/tMap.txt",
	"./Maps/xMap.txt"
};

const std::vector<std::string> coordsFiles =
{
	"./Maps/dCoords.txt",
	"./Maps/mCoords.txt",
	"./Maps/sCoords.txt",
	"./Maps/tCoords.txt",
	"./Maps/xCoords.txt"
};

const std::vector<std::string> skins =
{
	"wall.jpg",
	"clear.jpg",
	"wood.jpg",
	"water.jpg",
	"start.jpg",
	"searched.jpg",
	"target.jpg"
};

string GetMapName(EMap map);

//  MAIN:  //
void main()
{
	//  SETUP:  //
	tle::I3DEngine* engine = tle::New3DEngine(tle::kTLX);
	engine->StartWindowed();
	tle::IFont* font = engine->LoadFont("Comis Sans MS", 20);
	engine->AddMediaFolder("./Media");

	//  LOADING:  //
	EMap currentMap = dMap;
	ESearchType currentSearch = BreadthFirst;

	NodeList openList;
	NodeList closedList;
	NodeList pathList;
	std::unique_ptr<SNode> startNode(new SNode);
	std::unique_ptr<SNode> endNode(new SNode);
	std::unique_ptr<SNode> currentNode;

	MapManager mapManager = MapManager(engine);
	mapManager.LoadNewMap(startNode, endNode, mapFiles[currentMap],
		coordsFiles[currentMap], skins, currentMap);

	ISearch* pathfinder = NewSearch(currentSearch);
	bool currentlySearching = false;

	//  MAIN LOOP:  //
	while (engine->IsRunning())
	{
		//  DRAW SCENE:  //
		engine->DrawScene();

		if (currentlySearching && !openList.empty())
		{
			bool endFound = false;
			endFound = pathfinder->FindPath(mapManager, openList, closedList,
				pathList, currentNode, endNode);

			cout << "openlist:" << endl;
			deque<unique_ptr<SNode>>::iterator p;
			for (auto p = openList.begin(); p != openList.end(); p++)
			{
				cout << (*p)->x << " " << (*p)->y << endl;
			}

			// output the current closedlist to console.
			cout << endl << "closed list:" << endl;
			for (auto p = closedList.begin(); p != closedList.end(); p++)
			{
				cout << (*p)->x << " " << (*p)->y << endl;
			}

			if (endFound)
			{
 				currentlySearching = false;
				if (mapManager.GetPath(pathList, openList, closedList))
				{
					startNode = move(pathList.front());
					pathList.pop_front();
					endNode = move(pathList.back());
					pathList.pop_back();
					mapManager.HighlightPath(pathList, skins[5]);
				}
			}
		}

		std::string mapText = "Current map: " + GetMapName(currentMap);
		font->Draw(mapText, 10, 10);
		
		font->Draw("Search:", 10, 100);
		if (currentSearch == BreadthFirst)
		{
			font->Draw("Breadth First", 20, 120, tle::kRed);
		}
		else
		{
			font->Draw("Breadth First", 20, 120);
		}

		if (currentSearch == DepthFirst)
		{
			font->Draw("Depth First", 20, 140, tle::kRed);
		}
		else
		{
			font->Draw("Depth First", 20, 140);
		}

		if (currentSearch == AStar)
		{
			font->Draw("A*", 20, 160, tle::kRed);
		}
		else
		{
			font->Draw("A*", 20, 160);
		}

        if (engine->KeyHit(tle::Key_Space))
		{
			currentlySearching = true;
			openList.push_back(move(startNode));
		}

		if (engine->KeyHit(tle::Key_Down))
		{
			if (currentSearch == BreadthFirst)
			{
				currentSearch = DepthFirst;
			}
			else if (currentSearch == DepthFirst)
			{
				currentSearch = AStar;
			}
			else if (currentSearch == AStar)
			{
				currentSearch = BreadthFirst;
			}

			pathfinder = NewSearch(currentSearch);
		}

		if (engine->KeyHit(tle::Key_Up))
		{
			if (currentSearch == BreadthFirst)
			{
				currentSearch = AStar;
			}
			else if (currentSearch == DepthFirst)
			{
				currentSearch = BreadthFirst;
			}
			else if (currentSearch == AStar)
			{
				currentSearch = DepthFirst;
			}

			pathfinder = NewSearch(currentSearch);
		}

		if (engine->KeyHit(tle::Key_Left))
		{
			if (currentMap == dMap)
			{
				currentMap = xMap;
			}
			else if (currentMap == mMap)
			{
				currentMap = dMap;
			}
			else if (currentMap == sMap)
			{
				currentMap = mMap;
			}
			else if (currentMap == tMap)
			{
				currentMap = sMap;
			}
			else if (currentMap == xMap)
			{
				currentMap = tMap;
			}

			if (endNode->model != NULL)
			{
				endNode->model->~IModel();
			}
			mapManager.DeleteModels(pathList);
			pathList.clear();

			currentNode.reset(new SNode);
			mapManager.DeleteModels(openList);
			mapManager.DeleteModels(closedList);
			mapManager.LoadNewMap(startNode, endNode, mapFiles[currentMap],
				coordsFiles[currentMap], skins, currentMap);
		}

		if (engine->KeyHit(tle::Key_Right))
		{
			if (currentMap == dMap)
			{
				currentMap = mMap;
			}
			else if (currentMap == mMap)
			{
				currentMap = sMap;
			}
			else if (currentMap == sMap)
			{
				currentMap = tMap;
			}
			else if (currentMap == tMap)
			{
				currentMap = xMap;
			}
			else if (currentMap == xMap)
			{
				currentMap = dMap;
			}

			if (endNode->model != NULL)
			{
				endNode->model->~IModel();
			}

			mapManager.DeleteModels(pathList);
			pathList.clear();

			currentNode.reset(new SNode);
			mapManager.DeleteModels(pathList);
			mapManager.DeleteModels(openList);
			mapManager.DeleteModels(closedList);
			mapManager.LoadNewMap(startNode, endNode, mapFiles[currentMap],
				coordsFiles[currentMap], skins, currentMap);
		}

		if (engine->KeyHit(tle::Key_Escape))
		{
			engine->Stop();
		}
	}

	//  END:  //
	engine->Delete();
	mapManager.~MapManager();
}

string GetMapName(EMap map)
{
	if (map == dMap)
	{
		return "dMap";
	}
	else if (map == mMap)
	{
		return "mMap";
	}
	else if (map == sMap)
	{
		return "sMap";
	}
	else if (map == tMap)
	{
		return "tMap";
	}
	else if (map == xMap)
	{
		return "xMap";
	}
}
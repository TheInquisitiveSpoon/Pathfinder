//	MapManager.h - Niall Starkey

//
//	Manager for creating, deleting and storing maps.
//

#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

//  HEADERS:  //
#include <TL-Engine.h>
#include <sstream>
#include <fstream>
#include "Definitions.h"

//  MAP:  //
class MapManager
{
//  PRIVATE:  //
private:
	//  VARIABLES:  //
	tle::I3DEngine* engine;
	tle::ICamera* camera;
	tle::IMesh* nodeMesh;

//  PUBLIC:  //
public:
	//  VARIABLES:  //
	std::deque<std::string> map;
	std::vector<std::vector<ETerrainCost>> terrain;
	NodeList unopenedList;

	//  GETTERS:  //


	//  FUNCTIONS:  //
	void GetMapText(string mapLocation);
	void MoveCamera(EMap map);
	void DeleteModels(NodeList& list);
	bool GetPath(NodeList& path, NodeList& openList, NodeList& closedList);
	void HighlightPath(NodeList& list, string skin);
	std::vector<std::string> SplitString(std::string text);

	void GetCoords
	(
		std::unique_ptr<SNode>& start,
		std::unique_ptr<SNode>& end,
		string coordsLocation
	);

	void CreateMap
	(
		std::unique_ptr<SNode>& startNode,
		std::unique_ptr<SNode>& endNode,
		std::vector<std::string>& skins
	);

	void MapManager::LoadNewMap
	(
		std::unique_ptr<SNode>& startNode,
		std::unique_ptr<SNode>& endNode, string mapLocation,
		string coordsLocation,
		std::vector<std::string> skins,
		EMap currentMap
	);

	//  CONSTRUCTORS:  //
	MapManager(tle::I3DEngine* engine);

	//  DESTRUCTORS:  //
	~MapManager();
};

#endif	// MAP_MANAGER_H
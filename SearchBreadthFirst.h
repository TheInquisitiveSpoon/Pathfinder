//	SearchBreadthFirst.h - Niall Starkey

//
//	Declaration of Search class for Breadth-first algorithm
//

#ifndef SEARCH_BREADTH_FIRST_H
#define SEARCH_BREADTH_FIRST_H

//  HEADERS:  //
#include "Definitions.h"  // Type definitions
#include "Search.h"       // Base (=interface) class definition

class CSearchBreadthFirst : public ISearch
{
	bool FindPath(MapManager& mapManager, NodeList& openList,
		NodeList& closedList, NodeList& pathList,
		std::unique_ptr<SNode>& currentNode,
		std::unique_ptr<SNode>& end);

	void GetNeighbourNodes(MapManager& mapManager,
		std::unique_ptr<SNode>& currentNode,
		NodeList& openList, NodeList& closedList);
	ETerrainCost GetCost(MapManager& mapManager, int x, int y);
	bool FindInList(std::unique_ptr<SNode>& node, NodeList& list);
};

#endif	// SEARCH_BREADTH_FIRST_H
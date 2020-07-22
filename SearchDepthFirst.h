//	SearchNoStar.h - Niall Starkey

//
// Declaration of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#ifndef SEARCH_DEPTH_FIRST_H
#define SEARCH_DEPTH_FIRST_H

#include "Definitions.h"  // Type definitions
#include "Search.h"       // Base (=interface) class definition

// NoStar search class definition

/* TODO - Replace this class with classes to implement real search algorithms*/

// Inherit from interface and provide implementation for 0* algorithm
class CSearchDepthFirst : public ISearch
{
  // I have not implemented any constructors or destructors.
  // Whether you need some is up to how you choose to do your implementation.

  // Constructs the path from start to goal for the given terrain
  bool FindPath(MapManager& mapManager, NodeList& openList,
	  NodeList& closedList, NodeList& pathList,
	  std::unique_ptr<SNode>& currentNode,
	  std::unique_ptr<SNode>& end);

  bool FindInList(std::unique_ptr<SNode>& node, NodeList& list);
};

#endif	// SEARCH_DEPTH_FIRST_H
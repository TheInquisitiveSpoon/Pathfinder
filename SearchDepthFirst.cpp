//	SearchNoStar.cpp - Niall Starkey

//
// Implementation of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#include "SearchDepthFirst.h" // Declaration of this class

/* TODO - Replace this class with classes to implement real search algorithms*/


// This function takes ownership of the start and goal pointers that are passed in
// from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CSearchDepthFirst::FindPath(MapManager& mapManager, NodeList& openList,
	NodeList& closedList, NodeList& pathList,
	std::unique_ptr<SNode>& currentNode,
	std::unique_ptr<SNode>& end)
{
  return true;
}

bool CSearchDepthFirst::FindInList(std::unique_ptr<SNode>& node, NodeList& list)
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
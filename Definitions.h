//	Definitions.h - Niall Starkey

//
// Type definitions to support path finding 
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <vector>
#include <deque>
#include <memory>
#include <TL-Engine.h>

// Represents a node in the search tree.
struct SNode
{
  int x;            // x coordinate
  int y;            // y coordinate
  int score;        // used in more complex algorithms
  SNode* parent		= 0; // note use of raw pointer here
  tle::IModel* model = 0;
};

// Lists of nodes (e.g Open, Closed and Paths) are implemented as double-ended queues
using NodeList = std::deque<std::unique_ptr<SNode>>;

// Terrain costs for map squares
enum ETerrainCost
{
  Clear		= 1,
  Wood		= 2,
  Water		= 3,
  Wall		= 0
};

enum EMap
{
	mMap = 1,
	sMap = 2,
	tMap = 3,
	xMap = 4,
	dMap = 0
};

// Maps of any size are implemented as 2D vectors
using TerrainMap	= std::vector<std::vector<ETerrainCost>>;

#endif	// DEFINITIONS_H
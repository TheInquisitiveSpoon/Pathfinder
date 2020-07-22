//	SearchFactory.h - Niall Starkey

//
// Factory function declaration to create CSearchXXX objects 
//

#ifndef SEARCH_FACTORY_H
#define SEARCH_FACTORY_H

#include "Search.h" // Search interface class

// List of implemented seach algorithms
enum ESearchType
{
  BreadthFirst,
  DepthFirst,
  AStar
};

// Factory function to create CSearchXXX object where XXX is the given search type
ISearch* NewSearch(ESearchType search);

#endif	// SEARCH_FACTORY_H
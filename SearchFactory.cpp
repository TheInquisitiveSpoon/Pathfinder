//	SearchFactory.cpp - Niall Starkey

//
// Factory function implementation to create CSearchXXX objects 
//

#include "SearchDepthFirst.h" // NoStar search class
#include "SearchBreadthFirst.h"

/* TODO - include each implemented search class here */


#include "SearchFactory.h" // Factory declarations

// Create new search object of the given type and return a pointer to it.
// Note the returned pointer type is the base class. This is how we implement
// polymorphism.
ISearch* NewSearch(ESearchType search)
{
  switch (search)
  {
	case BreadthFirst:
	{
		return new CSearchBreadthFirst();
	}

	case DepthFirst:
	{
		return new CSearchDepthFirst();
	}
  }
}

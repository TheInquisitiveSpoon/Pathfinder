//	Pathfinding.cpp - Niall Starkey

//
// Main source for Pathfinding porfect
//

//  HEADERS:  //
#include <TL-Engine.h>
#include "Definitions.h"
#include "SearchFactory.h"

//  MAIN:  //
void main()
{
	//  SETUP:  //
	tle::I3DEngine* engine = tle::New3DEngine( tle::kTLX );
	engine->StartWindowed();
	engine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	//  CAMERA:  //
	tle::ICamera* camera = engine->CreateCamera(tle::kManual);

	//  MAIN LOOP:  //
	while (engine->IsRunning())
	{
		//  DRAW SCENE:  //
		engine->DrawScene();
	}

	//  END:  //
	engine->Delete();
}

//  FUNCTIONS:  //

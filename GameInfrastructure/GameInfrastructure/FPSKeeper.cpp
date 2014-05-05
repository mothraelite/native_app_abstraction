//
//  FPSKeeper.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 4/7/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "FPSKeeper.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

FPSKeeper::FPSKeeper() : Actor()
{
    name = "FPS KEEPER";
    frame = 0;
    time = 0;
    timebase = 0;
}

int count = 0;
void FPSKeeper::update()
{
    
    frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
    
	if (time - timebase > 1000) {
		float fps = frame*1000.0f/(time-timebase);
	 	timebase = time;
		frame = 0;
        
        std::cout<<"Fps: "<<fps<<std::endl;
	}
        
}
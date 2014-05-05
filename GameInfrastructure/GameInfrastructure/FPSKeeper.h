//
//  FPSKeeper.h
//  GameInfrastructure
//
//  Created by Navid Milani on 4/7/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__FPSKeeper__
#define __GameInfrastructure__FPSKeeper__

#include <iostream>
#include "Actor.h"

class FPSKeeper : public Actor // changed to image actor later (when we can do text)
{
public:
    FPSKeeper();
    virtual void update();
private:
    int frame,time,timebase;
    
};

#endif /* defined(__GameInfrastructure__FPSKeeper__) */

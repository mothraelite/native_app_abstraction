//
//  Semaphore.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/23/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__Semaphore__
#define __GameInfrastructure__Semaphore__

#include <iostream>

class Semaphore
{
public:
    Semaphore(int resources);
    void up();
    void down();
private:
    int count;
};

#endif /* defined(__GameInfrastructure__Semaphore__) */

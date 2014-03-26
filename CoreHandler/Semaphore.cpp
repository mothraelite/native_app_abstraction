//
//  Semaphore.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 3/23/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "Semaphore.h"
#include <thread>

Semaphore::Semaphore(int resources)
{
    count = resources;
}

void Semaphore::up()
{
    if(count == 0)
    {
    //wait
    }
    count--;
}
void Semaphore::down()
{
    //notify
    count++;
}
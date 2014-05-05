//
//  CollisionDetection.h
//  GameInfrastructure
//
//  Created by Navid Milani on 4/3/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__CollisionDetection__
#define __GameInfrastructure__CollisionDetection__

#include <iostream>


//
//  CollisionDetection.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 4/3/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "CollisionDetection.h"


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author navid
 */
class CollisionDetection{
public:
    CollisionDetection(float w,float h);
    void setPos(float x,float y);
    void reinit(float w,float h);
    
    bool hasCollided(CollisionDetection* ie);
    bool intersectsUsingCollisionCircle(CollisionDetection* cc);
    bool intersects(CollisionDetection* cd);
    
    bool containsPoint(float x, float y);
    
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getArea();
    
private:
    float x,y,height,width;
};


#endif /* defined(__GameInfrastructure__CollisionDetection__) */

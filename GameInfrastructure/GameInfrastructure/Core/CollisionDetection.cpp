//
//  CollisionDetection.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 4/3/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "CollisionDetection.h"
#include "Definitions.h"

CollisionDetection::CollisionDetection(float _w,float _h)
{
    x = 0;
    y = 0;
    width = _w;
    height = _h;
}

void CollisionDetection::setPos(float _x,float _y){
    x = _x;
    y = _y;
}

void CollisionDetection::reinit(float _w,float _h){
    width = _w;
    height = _h;
}

bool CollisionDetection::containsPoint(float _x, float _y)
{
    float left,right,down,up,px,py;
    left = this->x;
    right = left + width;
    up = this->y;
    down = up + height;
    px = _x;
    py = _y;
    
    return
    (
     px >= left &&
     px <= right &&
     py >= up &&
     py <= down
     );
}

bool CollisionDetection::containsPointRelativeToCamera(float _x, float _y)
{
    float left,right,down,up,px,py;
    left = this->x+camera->getX();
    right = left + width;
    up = this->y+camera->getY();
    down = up + height;
    px = _x;
    py = _y;
    
    return
    (
     px >= left &&
     px <= right &&
     py >= up &&
     py <= down
     );
}

bool CollisionDetection::hasCollided(CollisionDetection *ie)
{
    float left1,left2,right1,right2,down1,down2,up1,up2;
    
    left1 = x;
    left2 = ie->getX();
    
    right1 = left1 + width;
    right2 = left2 + ie->getWidth();
    
    up1 = y;
    up2 = ie->getY();
    
    down1 = up1 + height;
    down2 = up2 + ie->getHeight();
    
    if(down1 < up2) return false;
    if(up1 > down2)return false;
    if(right1 < left2)return false;
    if(left1 > right2)return false;
    
    
    return true;
}

float CollisionDetection::getX()
{
    return x;
}

float CollisionDetection::getY()
{
    return y;
}

float CollisionDetection::getWidth()
{
    return width;
}

float CollisionDetection::getHeight()
{
    return height;
}

float CollisionDetection::getArea()
{
    return width*height; // not really but temp
}
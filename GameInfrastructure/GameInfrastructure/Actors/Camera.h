//
//  Camera.h
//  GameInfrastructure
//
//  Created by Navid Milani on 5/7/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__Camera__
#define __GameInfrastructure__Camera__

#include <iostream>

class Camera{
public:
    Camera();
    ~Camera();
    
    void setPosition(float _x, float _y);
    void setXScale(float _scale);
    void setYScale(float _scale);
    void setRotation(float _rot);
    
    float getX();
    float getY();
    float getXScale();
    float getYScale();
    float getRotation();
private:
    float x, y, xscale, yscale, rotation;
};

#endif /* defined(__GameInfrastructure__Camera__) */

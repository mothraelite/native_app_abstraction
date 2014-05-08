//
//  Camera.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 5/7/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "Camera.h"
#include "Definitions.h"

Camera::Camera()
{
    x = 0;
    y = 0;
    rotation = 0;
    xscale = 0;
    yscale = 0;
}

void Camera::setPosition(float _x, float _y)
{
    x = _x;
    y = _y;
}
void Camera::setXScale(float _scale)
{
    xscale = _scale;
}
void Camera::setYScale(float _scale)
{
    yscale = _scale;
}
void Camera::setRotation(float _rot)
{
    rotation = _rot;
}

float Camera::getX()
{
    return x;
}
float Camera::getY(){
    return y;
}
float Camera::getXScale()
{
    return xscale;
}
float Camera::getYScale()
{
    return yscale;
}
float Camera::getRotation(){
    return rotation;
}
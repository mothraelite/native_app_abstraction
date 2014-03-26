//
//  Texture.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/16/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__Texture__
#define __GameInfrastructure__Texture__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <png.h>
#include <iostream>

struct Texture
{
    GLubyte* data;
    int width;
    int height;
    
};

#endif /* defined(__GameInfrastructure__Texture__) */

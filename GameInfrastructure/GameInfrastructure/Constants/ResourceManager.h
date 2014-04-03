//
//  ResourceManager.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/17/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__ResourceManager__
#define __GameInfrastructure__ResourceManager__

#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>
#include <map>

class ResourceManager
{
public:
    static ResourceManager* shared_instance;
    
    ResourceManager();
    void init();
    GLubyte* getImageWithName(std::string name);
protected:
private:
    std::map<std::string, GLubyte*> images;
};

#endif /* defined(__GameInfrastructure__ResourceManager__) */

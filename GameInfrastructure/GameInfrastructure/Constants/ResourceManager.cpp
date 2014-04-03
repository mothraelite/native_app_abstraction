//
//  ResourceManager.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 3/17/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
    init();
}

void ResourceManager::init()
{
    //iterate through all assets in asset folder
        //append all of them to list
    
}

ResourceManager* ResourceManager::shared_instance = new ResourceManager();
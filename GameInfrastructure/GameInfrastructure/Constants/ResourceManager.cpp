//
//  ResourceManager.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 3/17/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "ResourceManager.h"
#include "Definitions.h"
#include "Utility.h"


ResourceManager::ResourceManager()
{
    images = new std::map<std::string, Texture*>();
    current_textures = new std::vector<Texture*>();
    
    init();
}

void ResourceManager::init()
{
    if(TESTING)
    {
        //putTexture("null",loadPngImage("/Users/navidmilani/Desktop/png_file.png"));
        putTexture("flowers",loadPngImage("/Users/navidmilani/Desktop/png_file.png"));
        putTexture("notes",loadPngImage("/Users/navidmilani/Desktop/test_notes.png"));
    }
    //iterate through all assets in asset folder
        //append all of them to list
    
}

void ResourceManager::putTexture(std::string name, Texture* texture)
{
    if(!texture)
    {
        std::cout<<"Passed a null texture"<<std::endl;
        return;
    }
    
    auto it = images->find(name);
    if(it != images->end())
    {
        std::cout<<"Could not store texture with name: "<<name<<" because one with this name already exists"<<std::endl;
        return;
    }
    images->insert(st_pair(name,texture));
}

Texture* ResourceManager::getImageWithName(std::string name)
{
    auto it = images->find(name);
    if(it != images->end())
    {
        Texture* texture = it->second;
        if(texture->id == -1) //not buffered yet
        {
            glGenTextures(1, &texture->id);
            current_textures->push_back(texture);
        }
        
        return texture;
    }
    
    std::cout<<"Could not find texture with name: "<<name<<std::endl;
    return 0;
}
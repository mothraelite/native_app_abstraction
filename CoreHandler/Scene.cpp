/* 
 * File:   Scene.cpp
 * Author: navidmilani
 * 
 * Created on January 29, 2014, 11:38 AM
 */


#include "Scene.h"

Scene::Scene() {
    actors_present = new ia_map();
}

Scene::~Scene() {
    delete(actors_present);
}

void Scene::custom_init()
{
    //do nothing, meant to be overriden
}

void Scene::init()
{
    
    
    
    custom_init();
}

void Scene::custom_update()
{
    //do nothing, meant to be overriden
}

void Scene::update()
{
    custom_update();
    
    
}

void Scene::render()
{
    
}
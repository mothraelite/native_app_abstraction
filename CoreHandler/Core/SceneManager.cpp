/* 
 * File:   SceneManager.cpp
 * Author: navidmilani
 * 
 * Created on January 29, 2014, 11:38 AM
 */

#include "SceneManager.h"
#include "Definitions.h"

SceneManager::SceneManager() { 
    scenes = new std::vector<Scene*>();
    
    initThreads();
}

SceneManager::~SceneManager() {
    //delete scenes
    for(int i = 0; i < scenes->size(); i++)
        delete(scenes->at(i));
    
    //delete vector
    delete(scenes);
}

//Scene Manager functions-----------------------------------
void SceneManager::addScene(Scene *scene)
{
    if(!current_scene)
        current_scene = scene;
    
    scenes->push_back(scene);
}

void SceneManager::removeScene(Scene *scene)
{
    bool found = false;
    for(int i = 0; i < scenes->size(); ++i)
    {
        if(scenes->at(i) == scene)
        {
            scenes->erase(scenes->begin()+i);
            found = true;
            break;
        }
    }
    
    if(!found)
        std::cout<<"Could not remove scene: "<<scene->name<<" because that scene does not exist here."<<std::endl;
}

void SceneManager::removeSceneWithName(std::string name)
{
    
}

void SceneManager::getSceneWithName(std::string name)
{
    
}



//Threaded functions----------------------------------------

    //Input Handler... Needs to accomadate linux,mac,windows
void getInput()
{
    while(true)
    {
#ifdef __APPLE__
#elif defined __WINDOWS__
#elif defined __LINUX__
#else
#endif
    }
}

Scene* SceneManager::current_scene = NULL;
void update()
{
    while(true)
    {
        if(SceneManager::current_scene)
            SceneManager::current_scene->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}

void SceneManager::render()//will be on main loop
{
    if(current_scene)
        current_scene->render();
    
}

void SceneManager::initThreads()
{
    if(!input_thread)
    {
        input_thread = new std::thread(getInput);
        update_thread = new std::thread(update);
    }
}


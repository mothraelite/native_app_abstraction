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

void Scene::addActor(Actor* actor)
{
    //call actor event
    std::vector<std::function<void(void)> >* on_add_handlers = actor->getFunctionListForEvent("onAddedToScene");
    if(on_add_handlers)
        for(int i = 0; i < on_add_handlers->size(); i++)
        {
            on_add_handlers->at(i)();
        }
    
    ia_map::iterator it = actors_present->find(actor->depth);
    
    //there is no vector @ this depth.. first one
    if(it == actors_present->end())
    {
        std::vector<Actor*>* temp = new std::vector<Actor*>();
        temp->push_back(actor);
        actors_present->insert(ia_pair(actor->depth,temp));
    }else{
        //append the actor to the back of the vector @ this depth
        it->second->push_back(actor);
    }
}

void Scene::removeActor(Actor* actor, int location)
{
    //lock object

    if(actor)
    {
        std::vector<Actor*>* list = actors_present->at(actor->depth);
        
        //remove from list
        list->erase(list->begin()+location);
        delete(actor);
    }else
        std::cout<<"Error: no depth present in scene @ "<<actor->depth<<std::endl;
    
    //unlock object
}

void Scene::init()
{

}

void Scene::update()
{
    for(ia_map::reverse_iterator it = actors_present->rbegin(); it != actors_present->rend(); it++)
    {
        for(int i = 0; i < it->second->size(); i++)
        {
            Actor* actor = it->second->at(i);
            actor->update();
            
            if(!actor->alive)
            {
                removeActor(actor,i--);
                
                //the actor vector @ this depth is now empty, remove...
                if(it->second->empty())
                {
                    actors_present->erase(it++->first);
                    break;
                }
            }
        }
    }
}

void Scene::render()
{
    /*
    for(auto it = actors_present->end(); it > actors_present->begin(); it--)
    {
        for(int i = 0; i < it->second->size(); i++)
        {
            Actor actor = it->second->at(i);
            actor->update();
            
            if(!actor->alive)
            {
                it->second->erase(it->second->begin() + i--);
            }
        }
    }*/
}
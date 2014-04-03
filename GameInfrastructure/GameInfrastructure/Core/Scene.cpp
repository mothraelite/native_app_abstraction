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
    //delete all actors in the scene...
    for(int i = 0; i < actors_present->size(); ++i)
    {
        //std::vector<Actor*> list = actors_present->at(i);
        //for(int j = 0; j < )
        //delete();
    }
    
    delete(actors_present);
}

void Scene::addActor(Actor* actor)
{
    if(!actor)
        return;
    
    //call actor event
    std::vector<std::function<void(void)> >* on_add_handlers = actor->getFunctionListForEvent("onAddedToScene");
    if(on_add_handlers)
        for(int i = 0; i < on_add_handlers->size(); ++i)
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

void Scene::removeActor(Actor* actor)
{
    if(actor)
    {
        std::vector<Actor*>* list = actors_present->at(actor->depth);
        
        //remove from list
        for(int i = 0; i < list->size(); ++i)
            if(list->at(i) == actor)
            {
                list->erase(list->begin()+i);
                break;
            }
    }
}

void Scene::init()
{

}

void Scene::update()
{
    //UPDATE ALL ACTORS!
    std::vector<Actor*>* tobe_readded = new std::vector<Actor*>();
    for(ia_map::iterator it = actors_present->begin(); it != actors_present->end(); ++it)
    {
        for(register int i = 0; i < it->second->size(); ++i)
        {
            Actor* actor = it->second->at(i);
            actor->update();
            
            if(actor->alive)
            {
                //uh-oh! what if the object changed depths? too bad... next render cycle...
                if(actor->depth != it->first)
                {
                    it->second->erase(it->second->begin()+i--);
                    tobe_readded->push_back(actor);
                    break;
                }
            }else{
                it->second->erase(it->second->begin()+i--);
                delete(actor);
                
            }
        }
    }
    
    for(int i = 0; i < tobe_readded->size(); ++i)
        addActor(tobe_readded->at(i));
    
    delete(tobe_readded);
    
    //should we remove depths with no objects? if so make a list at the top, fill it up during update step, then delet them here
}

void Scene::render()
{
    for(ia_map::iterator it = actors_present->begin(); it != actors_present->end(); ++it)
    {
        for(register int i = 0; i < it->second->size(); ++i)
        {
            Actor* actor = it->second->at(i);
            if(actor->getType() == image_actor)
                actor->render();
        }
    }
}
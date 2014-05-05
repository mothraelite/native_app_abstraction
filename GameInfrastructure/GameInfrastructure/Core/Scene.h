/* 
 * File:   Scene.h
 * Author: navidmilani
 *
 * Created on January 29, 2014, 11:38 AM
 */


#ifndef SCENE_H
#define	SCENE_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "Actor.h"
#include "ImageActor.h"


typedef std::map<int, std::vector<Actor*>* > ia_map;
typedef std::pair<int, std::vector<Actor*>* > ia_pair;

class Scene {
public:
    std::string name;
    
    Scene();
    virtual ~Scene();
    
    void addActor(Actor* actor);
    void removeActorAtIndex(int index);
    void removeActor(Actor* actor);
    ia_map* getActors();

    void init();
    void update();
    void render();
    
protected:
    ia_map* actors_present;

};

#endif	/* SCENE_H */


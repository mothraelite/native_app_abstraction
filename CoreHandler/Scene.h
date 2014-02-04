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
#include "Actor.h"

typedef std::map<int, std::vector<Actor> > ia_map;

class Scene {
public:
    Scene();
    virtual ~Scene();
    
    void addActor(Actor actor);
    void removeActorAtIndex(int index);
    void removeActor(Actor actor);
    virtual void custom_init();
    virtual void custom_update();

private:
    ia_map* actors_present;
    
    void init();
    void update();
    void render();
};

#endif	/* SCENE_H */


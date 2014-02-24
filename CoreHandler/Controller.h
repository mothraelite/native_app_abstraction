/* 
 * File:   Controller.h
 * Author: navidmilani
 *
 * Created on January 30, 2014, 11:51 AM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <iostream>
#include "Actor.h"

class Controller {
public:
    int id;
    std::string identifier;
    std::function<void(Actor* actor)>  behavior;
    
    Controller();
    virtual ~Controller();
    virtual void init();
    
private:
    std::function<void(Actor* actor)> original_behavior;
};

#endif	/* CONTROLLER_H */


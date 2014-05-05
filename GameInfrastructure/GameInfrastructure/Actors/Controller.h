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

class Controller : public Actor{
public:
    int id;
    Controller();
    virtual ~Controller();
    virtual void init();
    virtual void behave(Actor* actor);
private:
};

#endif	/* CONTROLLER_H */


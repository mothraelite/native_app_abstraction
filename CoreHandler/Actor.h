/* 
 * File:   Actor.h
 * Author: navidmilani
 *
 * Base object that the entire application
 * 
 * Created on January 29, 2014, 11:38 AM
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include "Controller.h"
#include "Definitions.h"

#ifndef ACTOR_H
#define	ACTOR_H

typedef std::map<std::string,void (*)(void)> sf_map; //string, function ~ alarm completion
typedef std::map<std::string,int> si_map; //string, int ~ alarm countdown

typedef std::pair<std::string, void(*)(void)> sf_pair;
typedef std::pair<std::string, int> si_pair;

class Actor {
public:
    //VARIABLES---------------------
    std::string name;
    int depth;
    
    //FUNCTIONS---------------------
    Actor();
    virtual ~Actor();
    
    void addDefinition(ApplyableSystem definition);
    void removeDefinition(ApplyableSystem definition);
    
    void attachController(Controller* controller);
    void removeController(int id);
    
    void setEventWithCompletionBlock(std::string, int how_long, void (*func)(void));
    void removeEventWithCompletionBlock(std::string);
    
    virtual void update();
    
protected:
    
private:
    std::vector<Controller*>* controllers; //all objects that are attached can manipulate the obj
    std::vector<int>* responds_to; //all specific definitions that we can modularly apply to base actor
    si_map* alarm_counters;
    sf_map* alarm_handlers;
    
};

#endif	/* ACTOR_H */


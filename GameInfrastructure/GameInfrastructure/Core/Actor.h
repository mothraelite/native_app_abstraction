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
#include <mutex>
#include "Definitions.h"

#ifndef ACTOR_H
#define	ACTOR_H

class Controller;

//for custom time driven events and responses
typedef std::map<std::string,std::function<void(void)> > sf_map; //string, function ~ alarm complete
typedef std::map<std::string,int> si_map; //string, int ~ alarm countdown

typedef std::pair<std::string, std::function<void(void)> > sf_pair;
typedef std::pair<std::string, int> si_pair;

//for internal events and appendable responses
typedef std::map<std::string, std::vector<std::function<void(void)> >* > event_map;
typedef std::pair<std::string, std::vector<std::function<void(void)> >* > event_pair;

class Actor {
public:
    //VARIABLES---------------------
    std::string name;
    int depth;
    bool alive;
    
    //FUNCTIONS---------------------
    Actor();
    virtual ~Actor();
    
    void attachController(Controller* controller);
    void dettachController(Controller* controller);
    void dettachController(int identifier);
    std::vector<Controller*>* getControllerList();
    void clearControllers();
    
    void addDefinition(ApplyableSystem definition);
    void removeDefinition(ApplyableSystem definition);
    
    void setTimedEventWithCompletionBlock(std::string, int how_long, std::function<void(void)>);
    void removeTimedEventWithCompletionBlock(std::string);
    
    void appendFunctionToEvent(std::string event, std::function<void(void)>); //returns index of which was appended
    std::vector<std::function<void (void)> >* getFunctionListForEvent(std::string);
    void resetFunctionsFromEvent(std::string event);
    
    ObjectType getType();
    
    virtual void update();
    virtual void render();
    
protected:
    event_map* event_handlers; //base level events that you can hook to with your own logic from anywhere
    ObjectType type;
    
private:
    void initEvents();
            
    std::vector<Controller*>* controllers; //all objects that are attached can manipulate the obj
    std::vector<int>* responds_to; //all specific definitions that we can modularly apply to base actor
    si_map* alarm_counters;
    sf_map* alarm_handlers;
    
};

#endif	/* ACTOR_H */


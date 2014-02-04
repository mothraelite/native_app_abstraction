/* 
 * File:   Actor.cpp
 * Author: navidmilani
 * 
 * Created on January 29, 2014, 11:38 AM
 */

#include "Actor.h"

Actor::Actor() {
    alarm_counters = new si_map();
    alarm_handlers = new sf_map();
    controllers = new std::vector<Controller*>();
    responds_to = new std::vector<int>();
    depth = 0;
    name = "default";
}

Actor::~Actor() {
    delete(alarm_counters);
    delete(alarm_handlers);
    delete(controllers);
    delete(responds_to);
}

void Actor::setEventWithCompletionBlock(std::string name, int how_long, void(*func)())
{
    std::map<std::string,int>::iterator it = alarm_counters->find(name);
    if(it == alarm_counters->end())
    {
        alarm_counters->insert(si_pair(name,how_long));
        alarm_handlers->insert(sf_pair(name,func));
    }else
        std::cout<<"Error: can not set event with trigger "<<name<<" because it is already set\n";
}

void Actor::attachController(Controller* controller)
{
    
}

void Actor::removeController(int id)
{
    bool found = false;
    int i = 0;
    for(Controller* controller : *controllers)
        if(controller->id == id)
        {
            controllers->erase(controllers->begin()+i++);
            found = true;
            break;
        }
    std::cout<<"warning: could not find controller attached to "<<this<< " with id " <<id<<std::endl;
}

void Actor::update()
{
    //handle alarm system
        //iterate through all alarms
    int i = 0;
    for(auto it = alarm_counters->begin(); it != alarm_counters->end(); it++) {
        i++;
        //check if the alarm is active...
        if(it->second == 1)
        {
            //delayed event trigger
                    //call completion block
            alarm_handlers->find(it->first)->second();

                    //set to inactive
            it->second = 0;
            
        }else if(it->second > 1)
            it->second--;

    }
    
    //cleanup all events that are finished
    
}



/* 
 * File:   Actor.cpp
 * Author: navidmilani
 * 
 * Created on January 29, 2014, 11:38 AM
 */

#include "Actor.h"
#include "Controller.h"

Actor::Actor() {
    alarm_counters = new si_map();
    alarm_handlers = new sf_map();
    event_handlers = new event_map();
    controllers = new std::vector<Controller*>();
    responds_to = new std::vector<int>();
    depth = 0;
    name = "default";
    alive = true;
    type = actor;

    initEvents();
}

Actor::~Actor() {
    //erase all created vectors
    for(event_map::iterator it = event_handlers->begin(); it != event_handlers->end(); it++)
    {
        if(it->second)
        {       
            if(it->first == "onDestroyed")
                for(int i = 0 ; i < it->second->size(); i++)
                {
                    it->second->at(i)();
                }
            
            delete(it->second);
        }
    }
    
    //TESTING!!
        //memory leaks everywhere, delete controllers,
    delete(event_handlers);
    delete(alarm_counters);
    delete(alarm_handlers);
    delete(controllers);
    delete(responds_to);
}

void Actor::initEvents()
{
    event_handlers->insert(event_pair("onAddedToScene", 0));
    event_handlers->insert(event_pair("beforeUpdate",0));
    event_handlers->insert(event_pair("onUpdate",0));
    event_handlers->insert(event_pair("onDestroyed",0));
    event_handlers->insert(event_pair("onRender",0));
    event_handlers->insert(event_pair("beforeRender",0));
   
    if(TESTING)
    {
        //setTimedEventWithCompletionBlock("death", random()%300,  [&]{this->alive = false;});
        appendFunctionToEvent("onAddedToScene", []{std::cout<<"I was added to a scene\n";});
        appendFunctionToEvent("onDestroyed",[]{std::cout<<"I am now destroyed\n";});
    }
}

void Actor::setTimedEventWithCompletionBlock(std::string name, int how_long, std::function<void(void)> func)
{
    //fire immediately
    if(how_long == 0)
    {
        func();
        return;
    }
    
    std::map<std::string,int>::iterator it = alarm_counters->find(name);
    if(it == alarm_counters->end())
    {
        alarm_counters->insert(si_pair(name,how_long));
        alarm_handlers->insert(sf_pair(name,func));
    }else
        std::cout<<"Error: can not set event with trigger "<<name<<" because it is already set\n";
}

void Actor::appendFunctionToEvent(std::string event, std::function<void(void)> handler)
{
    event_map::iterator it = event_handlers->find(event);
    
    if(it == event_handlers->end())
    {
        std::cout<<"Event: "<<event<<" was not found"<<std::endl;
        return;
    }
    
    if(!it->second)
        it->second = new std::vector<std::function<void(void)> >();
    
     it->second->push_back(handler);
}

std::vector<std::function<void(void)> >* Actor::getFunctionListForEvent(std::string event)
{
    event_map::iterator it = event_handlers->find(event);
    
    return it->second;
}

void Actor::removeTimedEventWithCompletionBlock(std::string event)
{
    sf_map::iterator it = alarm_handlers->find(event);
    if(it != alarm_handlers->end())
        alarm_handlers->erase(it);
    else
        std::cout<<"No timed event named: "<<event<<" exists.  Are you sure it's not done?"<<std::endl;
    
    si_map::iterator other_it = alarm_counters->find(event);
    if(other_it != alarm_counters->end())
        alarm_counters->erase(other_it);
}

void Actor::resetFunctionsFromEvent(std::string event){
    event_map::iterator it = event_handlers->find(event);
    
    if(it != event_handlers->end()){
        it->second->clear();
    }else
        std::cout<<"Can not remove handlers for event: "<<event<<", it does not exist"<<std::endl;
}

#pragma mark --Controller manipulation
void Actor::attachController(Controller *controller)
{
    controllers->push_back(controller);
}

void Actor::dettachController(Controller *controller)
{
    bool found = false;
    int i = 0;
    for(Controller* current_controller : *controllers)
    {
        if(current_controller == controller)
        {
            controllers->erase(controllers->begin()+i);
            found = true;
            break;
        }
        i++;
    }
    
    if(!found)
        std::cout<<"warning: could not find controller attached to "<<this->name<< " with id " <<controller->name<<std::endl;
}

void Actor::dettachController(int id)
{
    bool found = false;
    int i = 0;
    for(Controller* controller : *controllers)
    {
        if(controller->id == id)
        {
            controllers->erase(controllers->begin()+i);
            found = true;
            break;
        }
        i++;
    }
    
    if(!found)
        std::cout<<"warning: could not find controller attached to "<<this->name<< " with id " <<id<<std::endl;
}

void Actor::clearControllers()
{
    for(Controller* controller: *controllers)
        delete(controller);
    
    controllers->clear();
}

ObjectType Actor::getType(){
    return type;
}

void Actor::update()
{
    event_map::iterator event_iterator = event_handlers->find("beforeUpdate");
    if(event_iterator != event_handlers->end())
        if(event_iterator->second)
        {
            //iterate through list of functions to call on this event
            for(int i = 0; i < event_iterator->second->size(); i++)
            {
                event_iterator->second->at(i)();
            }
        }
    
    //handle alarm system
        //iterate through all alarms
    std::vector<std::string>* to_remove = new std::vector<std::string>();
    for(auto it = alarm_counters->begin(); it != alarm_counters->end(); it++) {
        //check if alarm is archaic or user misused delayed event
        if(it->second == 0)
        {
            to_remove->push_back(it->first);
            continue;
        }
        
        //check if the alarm is active...
        if(it->second == 1)
        {
            //delayed event trigger
                    //call completion block
            alarm_handlers->find(it->first)->second();

                    //set to inactive
            it->second = 0;
            to_remove->push_back(it->first);
        }else if(it->second > 1)
            it->second--;

    }
    
    //cleanup all events that are finished
    for(std::string name : *to_remove)
    {
        alarm_handlers->erase(name);
        alarm_counters->erase(name);
    }
    
    delete(to_remove);
    
    
    //HANDLE CONTROLLERS
    for(Controller* controller : *controllers)
    {
        controller->behave(this);
    }
    
    
    //ITERATE THROUGH EVENT HANDLER FOR EVEN UPDATE
    event_iterator = event_handlers->find("onUpdate");
    if(event_iterator != event_handlers->end())
        if(event_iterator->second)
        {
            //iterate through list of functions to call on this event
            for(int i = 0; i < event_iterator->second->size(); i++)
            {
                event_iterator->second->at(i)();
            }
        }
}

void Actor::render()
{
}


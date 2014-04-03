/* 
 * File:   Controller.cpp
 * Author: navidmilani
 * 
 * Created on January 30, 2014, 11:51 AM
 */

#include "Controller.h"

Controller::Controller() : Actor(){
    type = controller;
}

Controller::~Controller() {
    
}

void Controller::init(){
    
}

void Controller::behave(Actor* actor)
{
    std::cout<<"Spanking actor: "<<actor->name<<std::endl;
}

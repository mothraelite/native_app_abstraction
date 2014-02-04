/* 
 * File:   Controller.h
 * Author: navidmilani
 *
 * Created on January 30, 2014, 11:51 AM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <iostream>

class Controller {
public:
    int id;
    std::string identifier;
    Controller();
    virtual ~Controller();
private:

};

#endif	/* CONTROLLER_H */


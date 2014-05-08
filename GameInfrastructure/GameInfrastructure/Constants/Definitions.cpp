//
//  Definitions.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 5/8/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "Definitions.h"

lua_State* lua_state = luaL_newstate();
ResourceManager* rmanager = new ResourceManager();
std::vector<int>* buttons_down = new std::vector<int>;
std::vector<mouse_action>* mouse_actions = new std::vector<mouse_action>;
Camera* camera = new Camera();

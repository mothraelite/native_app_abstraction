//
//  LuaCameraInterface.h
//  GameInfrastructure
//
//  Created by Navid Milani on 5/8/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef GameInfrastructure_LuaCameraInterface_h
#define GameInfrastructure_LuaCameraInterface_h

#include "Definitions.h"

int setCamPosition(lua_State* l)
{
    camera->setPosition(  (luaL_checknumber(l, 1)), luaL_checknumber(lua_state, 2) );
    return 0;
}
int setCamRotation(lua_State* l)
{
    camera->setRotation(  (luaL_checknumber(l, 1)) );
    return 0;
}
int setCamXScale(lua_State* l)
{
    camera->setXScale(  (luaL_checknumber(l, 1)) );
    return 0;
}
int setCamYScale(lua_State* l)
{
    camera->setYScale(  (luaL_checknumber(l, 1)) );
    return 0;
}
int getCamPosition(lua_State* l)
{
    lua_pushnumber(l, camera->getX());
    lua_pushnumber(l, camera->getY());
    return 2;
}

int getCamRotation(lua_State* l)
{
    lua_pushnumber(l, camera->getRotation());
    return 1;
}

int getCamXScale(lua_State* l)
{
    lua_pushnumber(l, camera->getXScale());
    return 1;
}

int getCamYScale(lua_State* l)
{
    lua_pushnumber(l, camera->getYScale());
    return 1;
}

static const luaL_Reg exposed_cam_funcs[] = {
    // Creation
    {"setRotation", setCamRotation},
    {"setPosition", setCamPosition},
    {"setXScale", setCamXScale},
    {"setYScale", setCamYScale},
    
    {"getRotation", getCamRotation},
    {"getPosition", getCamPosition},
    {"getXScale", getCamXScale},
    {"getYScale", getCamYScale},
    
    {NULL, NULL}
};

static void registerLuaCamera(lua_State* l)
{
    //lua_createtable(l, 0, 0);
    // Register metatable for user data in registry
    luaL_newmetatable(l, "LuaCameraInterface");
    luaL_setfuncs(l,exposed_cam_funcs,0);
    lua_pushvalue(l,-1);
    lua_setfield(l,-2, "__index");
    lua_setglobal(l, "LuaCameraInterface");
}


#endif

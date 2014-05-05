//
//  LuaImageActor.h
//  GameInfrastructure
//
//  Created by Navid Milani on 4/28/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//
#include <iostream>
#include "ImageActor.h"
#include "Definitions.h"

//EXPOSE THE OBJECT!!
static int createActor(lua_State *l)
{
    //args they are going to pass in
    int arg_count = lua_gettop(l);
    
    std::string img_name = "null";
    
    if(arg_count == 1)
    {
        img_name = luaL_checkstring(l,1);
    }
    
    //create pointer space for lua for our c++ object
    ImageActor** actor = (ImageActor**)lua_newuserdata(l, sizeof(ImageActor*));
    
    //create the c++ object
    ImageActor* iactor = new ImageActor(rmanager->getImageWithName(img_name));
    *actor = iactor;
    
    SceneManager::current_scene->addActor(*actor);
    
    luaL_getmetatable(l, "LuaImageActor");
    lua_setmetatable(l, -2);
    
    return 1;
}

static ImageActor* checkLuaImageActor(lua_State* l, int index)
{
    void* ud = 0;
    ud = luaL_checkudata(l, index, "LuaImageActor");
    return *((ImageActor**)ud);
}


static int setPosition(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->setPosition(  (luaL_checknumber(l, 2)), luaL_checknumber(lua_state, 3) );
    return 0;
}

static int setAlive(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->alive = luaL_checkinteger(l, 2);
    return 0;
}

static int setColors(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->red = ( (luaL_checknumber(l, 2)) );
    actor->green = ( (luaL_checknumber(l, 3)) );
    actor->blue = ( (luaL_checknumber(l, 4)) );
    actor->setAlpha ( (luaL_checknumber(l, 5)) );
    return 0;
}

static int setRotation(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->setRotation ( (luaL_checknumber(l, 2)) );
    return 0;
}

static int setSize(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    std::cout<<actor->getWidth()<<" , "<<actor->getHeight()<<std::endl;
    actor->setWidth ( (luaL_checknumber(l, 2)) );
    actor->setHeight ( (luaL_checknumber(l, 3)) );
    std::cout<<actor->getWidth()<<" , "<<actor->getHeight()<<std::endl;
    return 0;
}

static int getPosition(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->getX());
    lua_pushnumber(l, actor->getY());
    return 2;
}


static int getRotationCoordinates(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->getRotX());
    lua_pushnumber(l, actor->getRotY());
    return 2;
}

static int getSize(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->getWidth());
    lua_pushnumber(l, actor->getHeight());
    return 2;
}

static int getColors(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->red);
    lua_pushnumber(l, actor->blue);
    lua_pushnumber(l, actor->green);
    lua_pushnumber(l, actor->getAlpha());
    return 4;
}

static int getRotation(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->getRotation());
    return 1;
}


static int setTimedEventWithCompletionBlock(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    float wait_time = luaL_checknumber(l, 2);
    
    int func_ref = luaL_ref(l, LUA_REGISTRYINDEX);
    actor->setTimedEventWithCompletionBlock("fromLua", wait_time, [func_ref]()
    {
        //get natural lua func from index
        lua_rawgeti(lua_state, LUA_REGISTRYINDEX, func_ref);
        
        //call the func
        if ( 0 != lua_pcall(lua_state, 0, 0, 0 ) ) {
            printf("Failed to call the callback!\n %s\n", lua_tostring(lua_state, -1) );
        }
        
        luaL_unref(lua_state, LUA_REGISTRYINDEX, func_ref);
    });
    
    return 0;
}

static int appendFunctionToEvent(lua_State* l)
{
 
    ImageActor* actor = checkLuaImageActor(l, 1);
    std::string event = luaL_checkstring(l, 2);
    
    int func_ref = luaL_ref(l, LUA_REGISTRYINDEX);
    actor->appendFunctionToEvent(event,
    [func_ref]()
    {
        luaL_loadfile(lua_state, "/Users/navidmilani/Desktop/native_app_abstraction/GameInfrastructure/main.lua");
        
        lua_pcall(lua_state, 0, LUA_MULTRET, 0);
        
        //get natural lua func from index
        lua_rawgeti(lua_state, LUA_REGISTRYINDEX, func_ref);
        
        //duplicate the func for reuse
        //lua_pushvalue(lua_state, 1);
        
        //call the func: pcall pops everything off stack
        if ( 0 != lua_pcall(lua_state, 0, 0, 0 ) ) {
            printf("Failed to call the callback!\n %s\n", lua_tostring(lua_state, -1) );
        }
    });
    
    return 0;
}

static int resetFunctionsListFromEvent(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    std::string event = luaL_checkstring(l, 2);
    
    actor->resetFunctionsFromEvent(event);
    return 0;
}

static int getName(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushstring(l,actor->name.c_str());
    return 1;
}

static int setCanAutoMove(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->canAutoMove = luaL_checkinteger(l, 2);
    return 0;
}

static int setAsButton(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->isButton = (bool)luaL_checkinteger(l, 2);
    return 0;
}

static int setDestination(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->dx = luaL_checknumber(l, 2);
    actor->dy = luaL_checknumber(l, 3);
    return 0;
}

static int setDepth(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    actor->depth = luaL_checknumber(l, 2);
    return 0;
}

static int getDestination(lua_State* l)
{
    ImageActor* actor = checkLuaImageActor(l, 1);
    lua_pushnumber(l, actor->dx);
    lua_pushnumber(l, actor->dy);
    return 2;
}

static const luaL_Reg exposed_funcs[] = {
    // Creation
    {"new", createActor},
    
    {"getName", getName},
    
    {"setAlive", setAlive},
    
    {"getPosition", getPosition},
    {"setPosition", setPosition},
    
    {"setAutoMove", setCanAutoMove},
    {"setAsButton", setAsButton},
    
    {"setDestinationCoordinates",setDestination},
    {"getDestinationCoordinates",getDestination},
    
    {"getRotation", getRotation},
    {"setRotation", setRotation},
    {"getRotationCoordinates", getRotationCoordinates},
    
    {"setSize", setSize},
    {"getSize", getSize},
    
    {"setDepth", setDepth},
    
    {"setColors", setColors},
    {"getColors", getColors},
    
    {"setTimedEvent",setTimedEventWithCompletionBlock},
    {"appendFunctionToEvent",appendFunctionToEvent},
    {"resetFunctionListForEvent", resetFunctionsListFromEvent},
    {NULL, NULL}
};

static void registerLuaImageActor(lua_State* l)
{
    lua_createtable(l, 0, 0);
    // Register metatable for user data in registry
    luaL_newmetatable(l, "LuaImageActor");
    luaL_setfuncs(l,exposed_funcs,0);
    lua_pushvalue(l,-1);
    lua_setfield(l,-2, "__index");
    lua_setglobal(l, "LuaImageActor");
    
    // Register the base class for instances of Sprite
    luaL_register(l, "LuaImageActor", exposed_funcs);
}


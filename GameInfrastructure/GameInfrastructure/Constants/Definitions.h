/* 
 * File:   Definitions.h
 * Author: navidmilani
 *
 * Created on January 30, 2014, 11:52 AM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#import <thread>
#import "ResourceManager.h"

#define LUA_COMPAT_ALL
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
enum ObjectType
{
    actor,
    controller,
    image_actor
};
struct mouse_action
{
    int button;
    int x;
    int y;
};

static lua_State* lua_state;

static ResourceManager* rmanager;
static std::vector<int>* buttons_down = new std::vector<int>();
static std::vector<mouse_action>* mouse_actions = new std::vector<mouse_action>();


static int screen_width = 800;
static int screen_height = 600;

static int desired_fps = 61; // does not matter for render engine only

static int TESTING = 1;
static int DEBUG_ON = 1;

#endif	/* DEFINITIONS_H */


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
#import "Camera.h"

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

extern lua_State* lua_state;

extern ResourceManager* rmanager;
extern std::vector<int>* buttons_down;
extern std::vector<mouse_action>* mouse_actions;
extern Camera* camera;

static int screen_width = 800;
static int screen_height = 600;

static int desired_fps = 61; // does not matter for render engine only

static int TESTING = 1;
static int DEBUG_ON = 1;

#endif	/* DEFINITIONS_H */


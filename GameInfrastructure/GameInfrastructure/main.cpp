/* 
 * File:   main.cpp
 * Author: navidmilani
 *
 * Created on January 29, 2014, 11:26 AM
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <chrono>
#include <thread>

#include "Actor.h"
#include "ImageActor.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Definitions.h"
#include "LuaImageActor.h"
#include "LuaCameraInterface.h"

using namespace std;

SceneManager* manager;


void mouse_pressed(int button, int state, int x, int y)
{
    if(state == GLUT_UP)
    {
        for(int i = 0; i < mouse_actions->size(); ++i)
        {
            //already contains an instance of char
            if(mouse_actions->at(i).button == button)
            {
                //check if there was a button pressed...
                if(manager)
                    if(manager->current_scene)
                    {
                        ia_map* actors = manager->current_scene->getActors();
                        for(ia_map::iterator it = actors->begin(); it != actors->end(); ++it)
                        {
                            for(register int j = 0; j < it->second->size(); ++j)
                            {
                                Actor* actor = it->second->at(j);
                                if(actor->getType() == image_actor)
                                {
                                    ImageActor* iactor = (ImageActor*)actor;
                                    
                                    //was this button pressed?
                                    if(iactor->hitbox->containsPointRelativeToCamera(x, y))
                                    {
                                        if(iactor->isButton)
                                        {
                                            auto event_iterator = iactor->get_event_handlers()->find("onPressed");
                                            if(event_iterator != iactor->get_event_handlers()->end())
                                                if(event_iterator->second)
                                                {
                                                    //iterate through list of functions to call on this event
                                                    for(int k = 0; k < event_iterator->second->size(); k++)
                                                    {
                                                        event_iterator->second->at(k)();
                                                    }
                                                }

                                        }
                                    }
                                }

                            }
                        }
                    }
                
                mouse_actions->erase(mouse_actions->begin()+i);
                break;
            }
        }
    }else{
        mouse_action action = { button, static_cast<int>(x+camera->getX()), static_cast<int>(y+camera->getY())};
        mouse_actions->push_back(action);
    }
}

void key_pressed(unsigned char character, int x, int y)
{
    for(int i = 0; i < buttons_down->size(); ++i)
    {
        //already contains an instance of char
        if(buttons_down->at(i) == character)
        {
            return;
        }
    }
    buttons_down->push_back(character);
}

void key_up(unsigned char character, int x, int y)
{
    for(int i = 0; i < buttons_down->size(); ++i)
    {
        if(buttons_down->at(i) == character)
        {
            buttons_down->erase(buttons_down->begin()+i--);
            break;
        }
    }
}

void renderScene()
{
    if(manager)
    {
        luaL_loadfile(lua_state, "/Users/navidmilani/Desktop/native_app_abstraction/GameInfrastructure/main.lua");
        lua_pcall(lua_state, 0, LUA_MULTRET, 0);
        manager->update();
        manager->render();
    }else{
        if(TESTING)
        {
            manager = new SceneManager();
            Scene* s = new Scene();
            
            //setup manager!
            manager->addScene(s);
            
            //setup scene!
            luaL_loadfile(lua_state, "/Users/navidmilani/Desktop/native_app_abstraction/GameInfrastructure/main.lua");
            
            lua_pcall(lua_state, 0, LUA_MULTRET, 0);
            
            //load up the global func
            lua_getglobal(lua_state, "init");
            
            //arguements
            //lua_pushstring(lua_state, "Hello from c to lua and back!\n");
            
            //call func: state, argument count, return count
            lua_call(lua_state, 0, 0);
            
            //const char* str_from_lua = lua_tostring(lua_state, -1);
            
            //pop off stack
            lua_pop(lua_state,1);
        }
    }
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv) {    
    //init LUA
    luaL_openlibs(lua_state);
    
    //register our lua bindings
    registerLuaImageActor(lua_state);
    registerLuaCamera(lua_state);
    
    //init RAND
    srand(time(0));
    
    // init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow("DNP Game Engine");
    
    //setup general
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    
	// register callbacks
    glutMouseFunc(mouse_pressed);
    glutKeyboardFunc(key_pressed);
    glutKeyboardUpFunc(key_up);
	glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    
	// enter GLUT event processing cycle
	glutMainLoop();
    
    lua_close(lua_state);
    
    return 0;
}


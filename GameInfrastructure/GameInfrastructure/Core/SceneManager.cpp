/* 
 * File:   SceneManager.cpp
 * Author: navidmilani
 * 
 * Created on January 29, 2014, 11:38 AM
 */

#include "SceneManager.h"
#include "Definitions.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

SceneManager::SceneManager() { 
    scenes = new std::vector<Scene*>();
}

SceneManager::~SceneManager() {
    //delete scenes
    for(int i = 0; i < scenes->size(); i++)
        delete(scenes->at(i));
    
    //delete vector
    delete(scenes);
}

//Scene Manager functions-----------------------------------
void SceneManager::addScene(Scene *scene)
{
    if(!current_scene)
        current_scene = scene;

    scenes->push_back(scene);
}

void SceneManager::removeScene(Scene *scene)
{
    bool found = false;
    for(int i = 0; i < scenes->size(); ++i)
    {
        if(scenes->at(i) == scene)
        {
            scenes->erase(scenes->begin()+i);
            found = true;
            break;
        }
    }
    
    if(!found)
        std::cout<<"Could not remove scene: "<<scene->name<<" because that scene does not exist here."<<std::endl;
}

void SceneManager::removeSceneWithName(std::string name)
{
    
}

void SceneManager::getSceneWithName(std::string name)
{
    
}



//Threaded functions----------------------------------------

    //Input Handler... Needs to accomadate linux,mac,windows
void getInput()
{
    while(true)
    {
#ifdef __APPLE__
#elif defined __WINDOWS__
#elif defined __LINUX__
#else
#endif
    }
}

Scene* SceneManager::current_scene = NULL;

void SceneManager::update()
{
    if(SceneManager::current_scene)
        SceneManager::current_scene->update();
}

void SceneManager::render()//will be on main loop
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen_width, screen_height, 0, 0, 1.0f);
    
    if(camera)
    {
        glTranslatef(camera->getX()+screen_width/2, camera->getY()+screen_height/2, 0.0);
        glRotatef(camera->getRotation(), 0.0, 0.0, 1.0);
        glTranslatef(-screen_width/2, -screen_height/2, 0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    
    if(current_scene)
        current_scene->render();
    
    //get around v-sync issue
    std::this_thread::sleep_for(std::chrono::milliseconds(0));

    glPopMatrix();
    
    glutSwapBuffers();
}


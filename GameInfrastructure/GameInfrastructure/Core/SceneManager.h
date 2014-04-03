/* 
 * File:   SceneManager.h
 * Author: navidmilani
 *
 * Created on January 29, 2014, 11:38 AM
 */

#ifndef SCENEMANAGER_H
#define	SCENEMANAGER_H

#include <thread>
#include "Scene.h"

class SceneManager {
public:
    //variables
    static Scene* current_scene;
    
    //functions
    SceneManager();
    virtual ~SceneManager();
    
    void addScene(Scene* scene);
    void removeScene(Scene* scene);
    void removeSceneWithName(std::string name);
    void getSceneWithName(std::string name);
    void update();
    void render();
private:
    std::vector<Scene*>* scenes;
};

#endif	/* SCENEMANAGER_H */


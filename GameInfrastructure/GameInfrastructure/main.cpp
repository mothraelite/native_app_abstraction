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

#include "Utility.h"
#include "Actor.h"
#include "ImageActor.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Controller.h"
#include "GameMath.h"
#include "Definitions.h"

using namespace std;

SceneManager* manager;
ImageActor* controlledActor;

int current_choice = 0;
float mx=0, my=0;
void mouse_handler(int button, int state,int x, int y)
{
    if(current_choice == 4)
    {
        mx = x;
        my = y;
    }
}


void keyboard_handler(unsigned char character, int x, int y)
{
    if(!manager)
        return;
    
    //reset driver
    if(character == 'r')
    {
        //reset position
        mx = 0;
        my = 0;
        
        controlledActor->setAlpha(1);
        controlledActor->setRotation(0);
        controlledActor->resetSize();
        
        //reset choice
        current_choice = 0;
    }
    
    //set test depth
    else if(character == '1')
    {
        current_choice = 1;
        
        controlledActor->setAlpha(1);
        controlledActor->setRotation(0);
        controlledActor->resetSize();
        
        mx = 200;
        my = 0;
    }
    
    //set test keyboard
    else if(character == '2')
    {
        current_choice = 2;
        
        controlledActor->setAlpha(1);
        controlledActor->setRotation(0);
        controlledActor->resetSize();
        
        mx = 400;
        my = 0;
    }
    
    //set test color/rotation
    else if(character == '3')
    {
        current_choice = 3;
        
        controlledActor->setAlpha(1);
        controlledActor->setRotation(0);
        
        mx = 200;
        my = 200;
    }
    
    //set test flags(mouse input)
    else if(character == '4')
    {
        current_choice = 4; //not working
        
        controlledActor->setAlpha(1);
        controlledActor->setRotation(0);
        
        mx = 0;
        my = 0;
    }
    
    //behavior on click
    if(current_choice == 1)
    {
        if(character == 'w')
        {
            
            if(controlledActor)
            {
                controlledActor->depth = 2;
            }
        }else if(character == 's')
        {
            if(controlledActor)
            {
                controlledActor->depth = 0;
            }
        }
    }
    
    if(current_choice == 2)
    {
        if(character == 'd')
        {
            mx += 100;
        }else if(character == 'a'){
            mx -= 100;
        }else if(character == 'w'){
            my -= 100;
        }else if(character == 's'){
            my += 100;
        }
    }
}

void renderScene()
{
    if(manager)
    {
        manager->update();
        manager->render();
    }
    
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(0));
    
    // init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
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
    glutMouseFunc(mouse_handler);
    glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    
    
    // register singleton scene manager
        //setup scene manager
    manager = new SceneManager();
    Scene* s = new Scene();
    
    ImageActor* actor = new ImageActor(loadPngImage("/Users/navidmilani/Desktop/png_file.png"));
    actor->appendFunctionToEvent("onUpdate", [&](){
        if(actor->getX() != mx || actor->getY() != my)
        {
            float distance = dist(actor->getX(), actor->getY(), mx, my);
            if(distance < .001)
            {
                actor->setPosition(mx,my);
                mx = actor->getX();
                my = actor->getY();
            }else{
                float speed = distance;
                if(speed > 5.5f)
                    speed = 5.5f;
                
                float angle = getAngleOnCircle(mx, my,actor->getX(), actor->getY());
                
                Vector2D vect = getPointOnCircle(actor->getX(), actor->getY(), angle, speed);
                actor->setPosition(vect.x, vect.y);
            }
        }
    });
    
    bool toggleAlphaDown = true;
    int mwidth = actor->getWidth();
    bool toggleSizeUp = true;
    actor->appendFunctionToEvent("onUpdate", [&](){
            if(current_choice == 3)
            {
                actor->setRotation(actor->getRotation()+5);
                
                if(toggleAlphaDown)
                {
                    if(actor->getAlpha() > 0.05)
                        actor->setAlpha(actor->getAlpha()-0.005);
                    else
                        toggleAlphaDown = false;
                }else{
                    if(actor->getAlpha() < 0.95)
                        actor->setAlpha(actor->getAlpha()+0.005);
                    else
                        toggleAlphaDown = true;
                }
                
                if(actor->getWidth() >= mwidth*2)
                {
                    toggleSizeUp = false;
                }else if(actor->getWidth() <= mwidth)
                {
                    toggleSizeUp = true;
                }
                
                if(toggleSizeUp)
                {
                    actor->setWidth(1+actor->getWidth());
                    actor->setHeight(1+actor->getHeight());
                }else{
                    actor->setWidth(actor->getWidth()-1);
                    actor->setHeight(actor->getHeight()-1);
                }
                
            }
    });
    
    controlledActor = actor;
    actor->depth = 2;

    Texture* img = loadPngImage("/Users/navidmilani/Desktop/png_file.png");//loadPngImage("/Users/navidmilani/Desktop/other_png.png");
    for(int i = 0; i < 80; ++i)
    {
        ImageActor* temp = new ImageActor(img);
        temp->setWidth(50);
        temp->setHeight(20);
        temp->setPosition(random()%400, random()%400);
        
        temp->depth = 1;
        
        //add objects to scene
        s->addActor(temp);
    }
    
    s->addActor(actor);
    
    ImageActor* bg = new ImageActor(loadPngImage("/Users/navidmilani/Desktop/test_notes.png"));
    bg->setWidth(800);
    bg->setHeight(600);
    bg->depth = 100;
    //s->addActor(bg);
    
    //setup manager!
    manager->addScene(s);
    
	// enter GLUT event processing cycle
	glutMainLoop();
    
    return 0;
}


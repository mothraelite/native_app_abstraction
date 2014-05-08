/* 
 * File:   ImageActor.h
 * Author: navidmilani
 *
 * Created on February 3, 2014, 4:18 PM
 */

#ifndef IMAGEACTOR_H
#define	IMAGEACTOR_H

#include "Actor.h"
#include "Texture.h"
#include "CollisionDetection.h"

class ImageActor: public Actor {
public:
    float red,green,blue;
    bool isButton;
    bool canAutoMove;
    float dx,dy;
    
    CollisionDetection* hitbox;
    
    ImageActor(Texture* texture);
    virtual ~ImageActor();
    
    void setPosition(float _x, float _y);
    void setAlpha(float _alpha);
    void setRotation(float _theta);
    void setWidth(float _width);
    void setHeight(float _height);
    
    float getX();
    float getY();
    float getRotX();
    float getRotY();
    float getWidth();
    float getHeight();
    float getAlpha();
    float getRotation();
    Texture* getTexture();
    
    virtual void render();
    virtual void update();
    
    void resetSize();
    
    void setAsButton(bool isButton);
private:
    float x,y;
    float autoMoveSpeed;
    float rotX, rotY;
    float alpha;
    float rotation;
    float width, height;
    Texture* texture;

};

#endif	/* IMAGEACTOR_H */


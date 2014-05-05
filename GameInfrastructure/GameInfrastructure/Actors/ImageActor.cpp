/* 
 * File:   ImageActor.cpp
 * Author: navidmilani
 * 
 * Created on February 3, 2014, 4:18 PM
 */

#include "ImageActor.h"
#include "GameMath.h"

ImageActor::ImageActor(Texture* texture) : Actor() {
    this->texture = texture;
    
    x = 0;
    y = 0;
    
    dx = 0;
    dy = 0;
    
    autoMoveSpeed = 3;
    
    rotation = 0;
    
    alpha = 1;
    red = 255;
    green = 255;
    blue = 255;
    
    if(texture)
    {
        width = texture->width;
        height = texture->height;
    }else{
        width = 200;
        height = 200;
    }
    
    hitbox = new CollisionDetection(width,height);
    
    rotX = width/2;
    rotY = height/2;
    
    type = image_actor;
    isButton = false;
    canAutoMove = false;
    
    event_handlers->insert(event_pair("onPressed",0));
}

ImageActor::~ImageActor() {
    delete(hitbox);
}

void ImageActor::setAsButton(bool isButton)
{
    isButton = true;
}

float ImageActor::getX()
{
    return x;
}

float ImageActor::getY()
{
    return y;
}

float ImageActor::getAlpha()
{
    return alpha;
}

float ImageActor::getRotation()
{
    return rotation;
}

float ImageActor::getRotX()
{
    return rotX;
}

float ImageActor::getRotY()
{
    return rotY;
}

float ImageActor::getWidth()
{
    return width;
}

float ImageActor::getHeight()
{
    return height;
}

Texture* ImageActor::getTexture()
{
    return texture;
}

void ImageActor::setPosition(float _x, float _y)
{
    x = _x;
    y = _y;
}

void ImageActor::setAlpha(float _alpha)
{
    if(_alpha > 1)
        _alpha = 1;
    
    if(_alpha < 0)
        _alpha = 0;
    
    alpha = _alpha;
}

void ImageActor::setRotation(float _theta)
{
    if(_theta > 360)
        _theta = ((int)_theta)%360;
    
    rotation = _theta;
}

void ImageActor::setWidth(float _width)
{
    width = _width;
    rotX = _width/2;
    
    hitbox->reinit(width, height);
}

void ImageActor::setHeight(float _height)
{
    height = _height;
    rotY = _height/2;
    
    hitbox->reinit(width, height);
}

void ImageActor::resetSize()
{
    setWidth(texture->width);
    setHeight(texture->height);
}

void ImageActor::update()
{
    Actor::update();
    
    hitbox->setPos(x, y);
    
    if(canAutoMove)
    {
        float distance = dist(getX(), getY(), dx, dy);
        if(distance < .01)
        {
            dx = getX();
            dy = getY();
        }else{
            float speed = distance;
            if(speed > 5.5f)
                speed = 5.5f;
            
            float angle = getAngleOnCircle(dx, dy, getX(), getY());
            
            Vector2D vect = getPointOnCircle(getX(), getY(), angle, autoMoveSpeed);
            setPosition(vect.x, vect.y);
        }
    }
    
    if(isButton)
    {
        //check all mouse presses in queue
        
    }
}

void ImageActor::render()
{
    glLoadIdentity();
    
    //setup texture
    if(texture)
    {
        glActiveTexture(GL_TEXTURE0+texture->id);
        glBindTexture(GL_TEXTURE, texture->id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
        
        glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->width,
                     texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,texture->data
                     );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    
    //color
    glColor4f(red, green, blue, alpha);
    
    //reset world position
    glPushMatrix();
    
    //translate
    glTranslatef(x, y, 0);
    
    //rotate - from center
    glTranslatef(rotX, rotY, 0);
    
    glRotatef(rotation, 0, 0, 1);
    
    glTranslatef(-rotX, -rotY, 0);
    //end of rotation
    
    //render
    
    //VBO pass
    /*glBindBuffer(GL_ARRAY_BUFFER, vbo->vertexVBOID);
    glEnableVertexAttribArray(0);    //We like submitting vertices on stream 0 for no special reason
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));   //The starting point of the VBO, for the vertices
    glEnableVertexAttribArray(1);    //We like submitting normals on stream 1 for no special reason
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));     //The starting point of normals, 12 bytes away
    glEnableVertexAttribArray(2);    //We like submitting texcoords on stream 2 for no special reason
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));   //The starting point of texcoords, 24 bytes away
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->indexVBOID);
    
    glDrawRangeElements(GL_QUADS, 0, 3, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));*/
    
    //manual draw
    glBegin(GL_QUADS);
    
    glTexCoord2d(1.0, 1.0);
    glVertex2i(width, height);
    
    glTexCoord2d(1.0,0.0);
    glVertex2i(width, 0);
    
    glTexCoord2f(0.0,0.0);
    glVertex2i(0, 0);
    
    glTexCoord2f(0.0, 1.0);
    glVertex2i(0, height);
    
    glEnd();
    
    //end of render
    
    glPopMatrix();
}


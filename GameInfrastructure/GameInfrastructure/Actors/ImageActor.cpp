/* 
 * File:   ImageActor.cpp
 * Author: navidmilani
 * 
 * Created on February 3, 2014, 4:18 PM
 */

#include "ImageActor.h"

ImageActor::ImageActor(Texture* texture) : Actor() {
    this->texture = texture;
    x = 0;
    y = 0;
    rotation = 0;
    
    alpha = 1;
    red = 255;
    green = 255;
    blue = 255;
    
    width = texture->width;
    height = texture->height;
    rotX = width/2;
    rotY = height/2;
    
    type = image_actor;
}

ImageActor::~ImageActor() {
    
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
}

void ImageActor::setHeight(float _height)
{
    height = _height;
    rotY = _height/2;
}

void ImageActor::resetSize()
{
    setWidth(texture->width);
    setHeight(texture->height);
}

void ImageActor::render()
{
    glLoadIdentity();
    
    //setup
    glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->width,
                 texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,texture->data
                 );
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    
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


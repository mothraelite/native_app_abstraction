//
//  Texture.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/16/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef __GameInfrastructure__Texture__
#define __GameInfrastructure__Texture__
#define BUFFER_OFFSET(i) ((void*)(i))

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <png.h>
#include <iostream>

struct Texture
{
    GLuint id;
    GLubyte* data;
    int width;
    int height;
    
};

struct Vertex
{
    float x, y;        //Vertex
    //float nx, ny, nz;     //Normal
    float s0, t0;         //Texcoord0
};

class VBO
{
public:
    int mode;
    GLuint indexVBOID;
    GLuint vertexVBOID;
    std::vector<Vertex>* vertices;
    
    VBO()
    {
        indexVBOID = -1;
        vertexVBOID = -1;
        vertices = new std::vector<Vertex>();
    }
    ~VBO()
    {
        delete(vertices);
        
        if(vertexVBOID != -1)
            glDeleteBuffers(1,  &vertexVBOID);
        
        if(indexVBOID != -1)
            glDeleteBuffers(1,  &indexVBOID);
    }
    void generateVBO()
    {
        if(vertices->size() <= 0)
            return;
        
        if(vertexVBOID == -1)
        {
            glGenBuffers(1, &vertexVBOID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices->size(), &vertices->at(0).x, GL_DYNAMIC_DRAW);
            
            ushort pindices[3];
            pindices[0] = 0;
            pindices[1] = 1;
            pindices[2] = 2;
            
            glGenBuffers(1, &indexVBOID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort)*3, pindices, GL_STATIC_DRAW);
        }
    }
    
};

#endif /* defined(__GameInfrastructure__Texture__) */

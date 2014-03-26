//
//  GameMath.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/19/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#ifndef GameInfrastructure_GameMath_h
#define GameInfrastructure_GameMath_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float pi = 3.145;
float RADIANS_PER_DEGREE = (float)(pi/180.0);
float DEGREES_PER_RADIAN = (float)(180.0/pi);

struct Vector2D
{
    float x, y;
};

float clamp(float val, float min, float max){
    if (val < min){
        return min;
    } else if (val > max){
        return max;
    } else {
        return val;
    }
}

int clamp(int val, int min, int max){
    if (val < min){
        return min;
    } else if (val > max){
        return max;
    } else {
        return val;
    }
}

float len(float x, float y){
    return (float)sqrtf(x*x + y*y);
}

float dist(float x1, float y1, float x2, float y2){
    return len(x2 - x1, y2 - y1);
}

float normaliseAngle(float a){
    if ( a >= 0 && a <= pi*2 ){
        return a;
    }
    
    while (a < 0){
        a += 2*pi;
    }
    while (a > 2*pi){
        a -= 2*pi;
    }
    return a;
}

float getMinAngle(float cur, float target){
    cur = normaliseAngle(cur);
    target = normaliseAngle(target);
    float diff = target - cur;
    if (diff > pi){
        diff -= pi*2;
    } else if (diff < -pi){
        diff += pi*2;
    }
    return diff;
}

float getSlope(float x1,float y1,float x2,float y2){
    float slope;
    slope = (y2-y1)/(x2-x1);
    
    return slope;
}
float getAngleOnTriangle(float slope){
    float ans;
    ans = (float)atan(slope);
    ans = DEGREES_PER_RADIAN*ans;
    return ans;
}
float getAngleOnCircle(float x,float y,float cx,float cy){
    float ans,rad;
    //calculate radius
    rad = dist(cx,cy,x,y);
    ans = 2*(float)atan2((double)y-(cy-rad),(double)x-cx);
    ans = ans*DEGREES_PER_RADIAN;
    return ans;
}
Vector2D getPointOnCircle(float x,float y,float dir,float rad){
    Vector2D point;
    point.x = x+rad*(float)sin(dir*RADIANS_PER_DEGREE);
    point.y = y-rad*(float)cos(dir*RADIANS_PER_DEGREE);
    return point;
}

float lineCircleIntersect(float x1, float y1, float x2, float y2, float r){
    
    if ((x1*x1 + y1*y1) < r*r){
        // Already inside
        return NULL;
    }
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    float a, b, c;
    a = dx*dx + dy*dy;
    b = 2.0f * (dx*x1 + dy*y1);
    c = (x1*x1 + y1*y1) - r*r;
    
    float d = b*b - 4*a*c;
    if(d < 0){
        return NULL;
    }
    
    d = (float)sqrtf(d);
    float u;
    float u1 = (-b + d)/(2.0f*a);
    float u2 = (-b - d)/(2.0f*a);
    
    if (u1 > 0 && u1 < 1.0f && u2 > 0 && u2 < 1.0f){
        u = fmin(u1,u2);
    } else if (u1 > 0 && u1 < 1.0f){
        u = u1;
    } else if (u2 > 0 && u2 < 1.0f){
        u = u2;
    } else {
        u = NULL;
    }
    return u;
}

float lerp(float v1, float v2, float dx){
    return v2*dx + (1 - dx)*v1;
}

#endif

//
//  CollisionDetection.cpp
//  GameInfrastructure
//
//  Created by Navid Milani on 4/3/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//

#include "CollisionDetection.h"

CollisionDetection::CollisionDetection(float w,float h)
{
    
}

void CollisionDetection::setPos(float x,float y){
    
}

void CollisionDetection::reinit(float w,float h){
    
}

/*bool hasCollided(CollisionDetection* ie);
bool intersectsUsingCollisionCircle(CollisionDetection* cc);
bool intersects(CollisionDetection* cd);

bool containsPoint(float x, float y);

float getX();
float getY();
float getArea();

class CollisionDetection{
    public Vector2D loc;
    public float height,width,hOffset,wOffset;
    
    public CollisionDetection(float w,float h){
        loc = new Vector2D(0,0);
        //height = h*.8f;
        //width = w*.8f;
        height = h;
        width = w;
        //take 80% for offset of actualy width and height of box relative to obj rep
        //hOffset = (height*.1f);
        //wOffset = (width*.1f);
    }
    public void setPos(float x,float y){
        loc.x = x+(width*.1f);
        loc.y = y+(height*.1f);
        //loc.x = x;
        //loc.y = y;
    }
    public void reinit(float w,float h){
        height = h;
        width = w;
        //take 80% for offset of actualy width and height of box relative to obj rep
        hOffset = 0;
        wOffset = 0;
        
    }
    
    public boolean hasCollided(CollisionBox ie, float xOff, float yOff){
        CollisionBox offBox = new CollisionBox(width,height);
        offBox.loc.x = loc.x + xOff;
        offBox.loc.y = loc.y + yOff;
        
        return offBox.intersects(ie);
    }
    
    public boolean intersects(CollisionBox cb){
        
        float left1,left2,right1,right2,down1,down2,up1,up2;
        float width = this.width;
        float height = this.height;
        
        
        left1 = loc.x + wOffset;
        left2 = cb.loc.x + cb.wOffset;
        
        right1 = left1 + width;
        right2 = left2 + cb.width;
        
        up1 = loc.y + hOffset;
        up2 = cb.loc.y+ cb.hOffset;
        
        down1 = up1 + height;
        down2 = up2 + cb.height;
        
        if(down1 < up2) return false;
        if(up1 > down2)return false;
        if(right1 < left2)return false;
        if(left1 > right2)return false;
        
        
        return true;
    }
    public boolean intersects(CollisionCircle cc){
        //create bounding box around the circle
        CollisionBox cb = new CollisionBox(cc.radius,cc.radius);
        cb.setPos(cc.loc.x, cc.loc.y);
        return intersects(cb);
        //        if(GameMath.dist(cb.loc.x, cb.loc.y, loc.x, loc.y) < (cb.getArea()+getArea()))
        //            return true;
        //        else
        //            return false;
        
    }
    public boolean intersects(CollisionDetection cd){
        if(cd instanceof CollisionBox){
            return intersects((CollisionBox)cd);
        }else{
            return intersects((CollisionCircle)cd);
        }
    }
    public boolean containsPoint(Vector2D point)
    {
        float left,right,down,up,px,py;
        left = loc.x + wOffset;
        right = left + width;
        up = loc.y + hOffset;
        down = up + height;
        px = point.x;
        py = point.y;
        
        return
        (
         px >= left &&
         px <= right &&
         py >= up &&
         py <= down
         );
    }
    
    public boolean containsPoint(Point point)
    {
        float left,right,down,up,px,py;
        left = loc.x + wOffset;
        right = left + width;
        up = loc.y + hOffset;
        down = up + height;
        px = point.x;
        py = point.y;
        
        return
        (
         px >= left &&
         px <= right &&
         py >= up &&
         py <= down
         );
    }
    
    public float getX(){
        return loc.x;
    }
    public float getY(){
        return loc.y;
    }
    public float getArea(){
        return width*height;
    }
    
}*/

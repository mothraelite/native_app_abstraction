/* 
 * File:   main.cpp
 * Author: navidmilani
 *
 * Created on January 29, 2014, 11:26 AM
 */

#include "Actor.h"
#include "Scene.h"


using namespace std;

void completionBlockTest()
{
    cout<<"CALLED IT\n";
}
void completionBlockTestDelayed()
{
    cout<<"Delayed\n";
}
void completionBlockTestPriority()
{
    cout<<"1st\n";
}
int main(int argc, char** argv) {
    //DRIVER FOR SCENE AND LAMBDA FUNCTION INCLUSION
    Actor* actor = new Actor();
    
    actor->setTimedEventWithCompletionBlock("Die of old age", 100, [&actor](){actor->alive = false;cout<<"now I am dead\n";});
    actor->setTimedEventWithCompletionBlock("My first birthday", 1, [&actor](){
        
        cout<<"I was born\n";
        //actor->resetFunctionsFromEvent("onDestroyed"); //uncomment to tryout
    
    });

    Scene* s = new Scene();
    s->addActor(actor); 
    
    while(true)
        s->update();
    
    return 0;
}


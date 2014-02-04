/* 
 * File:   main.cpp
 * Author: navidmilani
 *
 * Created on January 29, 2014, 11:26 AM
 */

#include "Actor.h"



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
    //DRIVER FOR 
    
    //DRIVER FOR FUNCTION DELAY ~ alarm system built in
    
    Actor* actor = new Actor();
    
    actor->setEventWithCompletionBlock("test_event2",1000,&completionBlockTestDelayed);
    actor->setEventWithCompletionBlock("test_event",60,&completionBlockTest);
    actor->setEventWithCompletionBlock("test_event",60,&completionBlockTest);
    actor->setEventWithCompletionBlock("test_event0",1,&completionBlockTestPriority);
   
    while(true)
        actor->update();
    
    
    return 0;
}


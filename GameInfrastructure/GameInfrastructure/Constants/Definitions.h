/* 
 * File:   Definitions.h
 * Author: navidmilani
 *
 * Created on January 30, 2014, 11:52 AM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#import <thread>

enum ApplyableSystem
{
    physics,
    lighting
    
};

enum ObjectType
{
    actor,
    controller,
    image_actor
};

static std::thread* update_thread;
static std::thread* input_thread;

static int screen_width = 800;
static int screen_height = 600;

static int desired_fps = 61; // does not matter for render engine only

static int TESTING = 1;
static int DEBUG_ON = 1;
static bool renderEachFrame = false; //turn off for games, ON for a render engine

#endif	/* DEFINITIONS_H */


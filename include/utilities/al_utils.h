//TITLE: AL UTILS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: Generic functions for drawing and handdling allegro bitmaps
#ifndef AL_UTILS_H
#define AL_UTILS_H

#include "debug_log.h"
#include <vector>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//returns width (in pixels) as an unsigned int from a const bitmap (with const cast)
unsigned int get_bitmap_width(const ALLEGRO_BITMAP *bmp);
//returns height (in pixels) as an unsigned int from a const bitmap (with const cast)
unsigned int get_bitmap_height(const ALLEGRO_BITMAP *bmp);
//al_get_bitmap overloaded to get a bitmap from a string
ALLEGRO_BITMAP *al_load_bitmap(const string &path);
//draw bitmap (with const cast)
void draw_bitmap(const ALLEGRO_BITMAP *bmp,int x,int y);
void draw_bitmap(const ALLEGRO_BITMAP *bmp,double x,double y);
void draw_scaled(const ALLEGRO_BITMAP *bmp,int x,int y,unsigned int width,unsigned int height);
//draw bitmap centered and rotated
void draw_rotated(const ALLEGRO_BITMAP *bmp,double x,double y,double rotation);
//resize bmp to given width and height (x and y), destroying the original bitmap
void resize_bitmap(ALLEGRO_BITMAP *&bitmap,unsigned int x,unsigned int y);
//copy bitmap
ALLEGRO_BITMAP *copy_bitmap(const ALLEGRO_BITMAP *bitmap);
//copy and resize bitmap
ALLEGRO_BITMAP *copy_bitmap(const ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height);
//slice given bitmap in a vector of bitmaps, each bitmap with given height and width (if ntiles>0, represents the max tiles to slice)
vector<ALLEGRO_BITMAP *> slice_bitmap(const ALLEGRO_BITMAP *bitmap,int width,int height,int ntiles=-1);
//start allegro with the necessary configuration
//void al_start(ALLEGRO_DISPLAY *&display,ALLEGRO_EVENT_QUEUE *&event_queue,ALLEGRO_TIMER *&timer);
//updates movement 1 frame (being speed pixels/frame) from position to destiny
pair<double,double> movement_update(pair<double,double> position,pair<double,double> destiny,double speed);
//return speed per frame from speed per second from given timer
double convert_speed(double speed,const ALLEGRO_TIMER *timer);
//get frames in given seconds
unsigned int get_frames(double seconds, const ALLEGRO_TIMER *timer);
//draw given bitmap centered in position
void draw_centered(const ALLEGRO_BITMAP *bitmap,double x,double y);
#endif

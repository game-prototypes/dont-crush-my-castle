//TITLE: AL UTILS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.3
//DESCRIPTION: Generic functions for drawing and handdling allegro bitmaps
#ifndef AL_UTILS_H
#define AL_UTILS_H

#include "debug_log.h"
#include <vector>
#include <cmath>
#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//using namespace std;


//resize bmp to given width and height (x and y), destroying the original bitmap
void resize_bitmap(ALLEGRO_BITMAP *&bitmap,unsigned int x,unsigned int y) {
    if(bitmap!=NULL && x>0 && y>0) {
        ALLEGRO_BITMAP *temp;
        ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //current display
        int origx=al_get_bitmap_width(bitmap);
        int origy=al_get_bitmap_height(bitmap);
        temp=al_create_bitmap(x,y); //the new bitmap with the given size
        al_set_target_bitmap(temp);
        al_draw_scaled_bitmap(bitmap,0,0, origx, origy,0,0, x,y,0);//draw the original bitmap to the new one (resized)
        al_set_target_bitmap(disp); //returns the target to the display
        al_destroy_bitmap(bitmap); //destroys the old bitmap
        bitmap=temp; //bmp now points to the resized bitmap
    }
}
ALLEGRO_BITMAP *copy_bitmap(const ALLEGRO_BITMAP *bitmap) {
    ALLEGRO_BITMAP *res=NULL;
    if(bitmap!=NULL) {
        ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //current display
        int origx=al_get_bitmap_width(const_cast<ALLEGRO_BITMAP *>(bitmap));
        int origy=al_get_bitmap_height(const_cast<ALLEGRO_BITMAP *>(bitmap));
        res=al_create_bitmap(origx,origy); //the new bitmap with the given size
        al_set_target_bitmap(res);
        al_draw_bitmap(const_cast<ALLEGRO_BITMAP *>(bitmap),0,0,0); //draw the original bitmap to the new one
        al_set_target_bitmap(disp); //returns the target to the display
    }
    return res;
}
ALLEGRO_BITMAP *copy_bitmap(const ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height) {
    ALLEGRO_BITMAP *res=NULL;
    if(bitmap!=NULL && width>0 && height>0) {
        ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //current display
        int origx=al_get_bitmap_width(const_cast<ALLEGRO_BITMAP *>(bitmap));
        int origy=al_get_bitmap_height(const_cast<ALLEGRO_BITMAP *>(bitmap));
        res=al_create_bitmap(width,height); //the new bitmap with the given size
        al_set_target_bitmap(res);
        al_draw_scaled_bitmap(const_cast<ALLEGRO_BITMAP *>(bitmap),0,0, origx, origy,0,0, width,height,0); //draw the original bitmap to the new one (resized)
        al_set_target_bitmap(disp); //returns the target to the display
    }
    return res;
}


//slice given bitmap in a vector of bitmaps, each bitmap with given height and width (if ntiles>0, represents the max tiles to slice)
vector<ALLEGRO_BITMAP *> slice_bitmap(const ALLEGRO_BITMAP *bitmap,int width,int height,int ntiles) {
    vector<ALLEGRO_BITMAP *> v;
    if(!bitmap) debug_log::report("null pointer to slice",err,true,true);
    else {
        ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //actual display (stores for re-target)
        int x=al_get_bitmap_width(const_cast<ALLEGRO_BITMAP *>(bitmap));
        int y=al_get_bitmap_height(const_cast<ALLEGRO_BITMAP *>(bitmap));
        if(height>y || width>x) debug_log::report("impossible to slice bitmap",err,true,true);
        else {
            if(x%width!=0 || y%height) debug_log::report("slice section not exact",warning,true,false);
            int xtiles=x/width; //x tiles in bitmap
            int ytiles=y/height;//y tiles in bitmap
            x=y=0;
            for(int i=0; i<ytiles; i++) {
                for(int j=0; j<xtiles; j++) {
                    if((ntiles>=0 && v.size()<(unsigned int)ntiles) || ntiles<0) {
                        ALLEGRO_BITMAP *temp;
                        temp=al_create_bitmap(width,height);
                        al_set_target_bitmap(temp); //sets new bitmap as target
                        al_draw_bitmap_region(const_cast<ALLEGRO_BITMAP *>(bitmap),x,y,width,height,0,0,0); //draw the region into the bitmap
                        v.push_back(temp); //adds bitmap to vector
                        x+=width;
                    }
                    else break;
                }
                x=0;
                y+=height;
            }
        }
        al_set_target_bitmap(disp); //returns target to original target
    }
    return v;
}

/*//start allegro with the necessary configuration
void al_start(ALLEGRO_DISPLAY *&display,ALLEGRO_EVENT_QUEUE *&event_queue,ALLEGRO_TIMER *&timer) {
    al_init(); //init allegro
    al_init_image_addon();  //init allegro image addons
    display = al_create_display(640, 480); //create display (640x480)
    event_queue = al_create_event_queue();//create event queue
    timer = al_create_timer(1.0 / 60); //create timer for fps (1.0/60 seconds, 60 fps)
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //add timer and display to event queue
    al_start_timer(timer); //start the timer
}
*/
//updates movement 1 frame (being speed pixels/frame) from position to destiny
pair<double,double> movement_update(pair<double,double> position,pair<double,double> destiny,double speed) {
    if(position!=destiny) {
        double x=destiny.first-position.first;
        double y=destiny.second-position.second;
        double m=sqrt(x*x+y*y);
        m=speed/m;
        x*=m;
        y*=m;
        if(abs(position.first-destiny.first)<=speed) position.first=destiny.first;
        else position.first+=x;
        if(abs(position.second-destiny.second)<=speed) position.second=destiny.second;
        else position.second+=y;
    }
    return position;
}
//return speed per frame from speed per second from given timer
double convert_speed(double speed,const ALLEGRO_TIMER *timer) {
    if(timer==NULL) {
        debug_log::report("timer not set",err,true,true,false);
        return speed;
    }
    if(speed<0) {
        debug_log::report("enemy speed negative (set to positive)",warning,true,false,false);
        speed=-speed;
    }
    if(speed==0) debug_log::report("enemy speed set to 0",warning,true,false,false);
    return speed*al_get_timer_speed(timer);
}
//draw given bitmap centered in position
void draw_centered(ALLEGRO_BITMAP *bitmap,double x,double y) {
    x-=al_get_bitmap_width(bitmap)/2;
    y-=al_get_bitmap_height(bitmap)/2;
    al_draw_bitmap(bitmap,x,y,0);
}

#endif

//TITLE: AL_ANIM_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines a general animation with allegro as a set of bitmaps

#include "al_anim.h"

al_anim::al_anim() {
    animation_delay=0;
    current_delay=0;
    count=0;
    loop=true;
    active=false;
}
al_anim::al_anim(const vector<ALLEGRO_BITMAP *> bitmap_sheet,double duration,const ALLEGRO_TIMER *timer) {
    if(bitmap_sheet.empty()) debug_log::report("animation with no bitmaps",err,true,true,false);
    else {
        count=0;
        active=false;
        loop=true;
        set_duration(duration,timer);
    }
}
al_anim::al_anim(ALLEGRO_BITMAP *bitmap_sheet,unsigned int width,unsigned int height,double duration,const ALLEGRO_TIMER *timer) {
    load_from_bitmap(bitmap_sheet,width,height);
    if(bitmap_set.empty()==false) {
        count=0;
        active=false;
        loop=true;
        set_duration(duration,timer);
    }
}
void al_anim::activate() {
    active=true;
    check();
}
void al_anim::start() {
    count=0;
    current_delay=animation_delay;
    active=true;
    check();
}
void al_anim::pause() {
    active=false;
}
void al_anim::stop() {
    active=false;
    count=0;
    current_delay=animation_delay;
}
void al_anim::set_frame(unsigned int frame) {
    if(frame<size()) {
        count=frame;
        current_delay=animation_delay;
    }
}
void al_anim::set_duration(double seconds,const ALLEGRO_TIMER *timer) {
    if(size()>0) {
        double tspeed=al_get_timer_speed(timer);
        seconds/=size();
        animation_delay=seconds/tspeed;
        if(animation_delay==0) {
            debug_log::report("animation speed too fast for timer, speed=refresh rate",warning,true,false,false);
            animation_delay=1;
        }
        current_delay=animation_delay;
    }
}
void al_anim::animation_loop(bool loop) {
    this->loop=loop;
}
unsigned int al_anim::size() const {
    return bitmap_set.size();
}
double al_anim::duration(const ALLEGRO_TIMER *timer)const {
    double tspeed=al_get_timer_speed(timer);
    return tspeed*animation_delay*size();
}
unsigned int al_anim::fps(const ALLEGRO_TIMER *timer) const {
    double speed=al_get_timer_speed(timer);
    speed*=animation_delay;
    return 1/speed;
}

bool al_anim::is_active() const {
    return active;
}
unsigned int al_anim::get_frame() const {
    return count;
}
void al_anim::update() {
    if(active) {
        current_delay--;
        if(current_delay==0) { //change bitmap
            count++;
            if(count==bitmap_set.size()-1 && loop==false) pause();
            count%=bitmap_set.size();
            current_delay=animation_delay;  //resets delay
        }
    }
}
void al_anim::draw(double x,double y) const {
    if(!bitmap_set.empty()) { //comprobation erased to improve performance ??
        al_draw_bitmap(bitmap_set[count],x,y,0);
    }
}
void al_anim::draw_resized(double x,double y,unsigned int width,unsigned int height) const {
    if(width==0 || height==0) debug_log::report("tile size=0",err,true,false,false);
    else
        al_draw_scaled_bitmap(bitmap_set[count],0.0,0.0,al_get_bitmap_width(bitmap_set[count]),al_get_bitmap_height(bitmap_set[count]),x,y,width,height,0);
}
void al_anim::destroy() {
    for(unsigned int i=0; i<bitmap_set.size(); i++) al_destroy_bitmap(bitmap_set[i]);
    animation_delay=0;
    count=0;
    active=false;
    current_delay=0;
    bitmap_set.clear();
}
void al_anim::load_from_bitmap(ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height) {
    bitmap_set=slice_bitmap(bitmap,width,height); //slice the bitmap in small bitmaps
    check();
}
void al_anim::check() const {
    if(active==true) {
        if(bitmap_set.empty()) debug_log::report("animation with no bitmaps",err,true,true,false);
        if(animation_delay==0) debug_log::report("animation with speed=0",err,true,true,false);
    }
}

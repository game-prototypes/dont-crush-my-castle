//TITLE: tower_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines an user tower

#include "tower.h"
tower_attributes::tower_attributes() {
}
tower_attributes::tower_attributes(ALLEGRO_BITMAP *bitmap,atk_attributes atk) {
    this->bitmap=bitmap;
    this->atk=atk;
}
unsigned int tower_attributes::get_width() const {
    return al_get_bitmap_width(bitmap);
}
unsigned int tower_attributes::get_height() const {
    return al_get_bitmap_height(bitmap);
}

//resize bitmap (overriding old) to given size
void tower_attributes::resize(unsigned int width,unsigned int height) {
    resize_bitmap(bitmap,width,height);
}
//destroy tower attributes (including bitmaps and attack attribute)
void tower_attributes::destroy() {
    //animation.destroy();
    al_destroy_bitmap(bitmap);
    atk.clear();
}


//tower

tower::tower() {
    atk_counter=0;
    position=make_pair(-1,-1);
    atk_delay=0;
    active=false;
}
tower::tower(tower_attributes attribute,double posx,double posy,const ALLEGRO_TIMER *timer) {
    this->attributes=attributes;
    this->position=make_pair(posx,posy);
    this->atk_delay=convert_speed(attributes.atk.delay,timer);
    reset_counter();
    active=true;
}

void tower::deactivate() {
    active=false;
}
bool tower::is_active() const {
    return active;
}
pair<double,double> tower::get_position()const {
    return position;
}
unsigned int tower::get_range()const {
    return attributes.atk.range;
}
unsigned int tower::get_damage() const {
    return attributes.atk.damage;
}
atk_type tower::get_attack_type() const {
    return attributes.atk.type;
}
bool tower::in_range(pair<double,double> objective) const {
    double rad=attributes.atk.range;
    double x=objective.first-position.first;
    double y=objective.second-position.second;
    return (x*x+y*y)<=(rad*rad);
}
bool tower::can_attack() const {
    return atk_counter==0;
}
void tower::update() {
    if(active) {
        if(atk_counter>0) atk_counter--;
    }
}
void tower::draw() const {
    if(active)
        draw_centered(attributes.bitmap,position.first,position.second);
}
tower_atk tower::attack(const pair<double,double> target) {
    if(atk_counter>0) debug_log::report("tower attack before counter reach 0",warning,true,false,false);
    reset_counter();
    return tower_atk(attributes.atk,position,target);
}

void tower::reset_counter() {
    atk_counter=atk_delay;
}

bool tower::check() const {
    return true;
}

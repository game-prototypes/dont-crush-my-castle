//TITLE: BUILDING_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines an user building

#include "building.h"
building_attributes::building_attributes() {
}
building_attributes::building_attributes(ALLEGRO_BITMAP *bitmap,atk_attributes atk) {
    this->bitmap=bitmap;
    this->atk=atk;
}
unsigned int building_attributes::get_width() const {
    return al_get_bitmap_width(bitmap);
}
unsigned int building_attributes::get_height() const {
    return al_get_bitmap_height(bitmap);
}

//resize bitmap (overriding old) to given size
void building_attributes::resize(unsigned int width,unsigned int height) {
    resize_bitmap(bitmap,width,height);
}
//destroy building attributes (including bitmaps and attack attribute)
void building_attributes::destroy() {
    //animation.destroy();
    al_destroy_bitmap(bitmap);
    atk.clear();
}


//BUILDING

building::building() {
    atk_counter=0;
    position=make_pair(-1,-1);
    atk_delay=0;
    active=false;
}
building::building(building_attributes attribute,double posx,double posy,const ALLEGRO_TIMER *timer) {
    this->attributes=attributes;
    this->position=make_pair(posx,posy);
    this->atk_delay=convert_speed(attributes.atk.delay,timer);
    reset_counter();
    active=true;
}

void building::deactivate() {
    active=false;
}
bool building::is_active() const {
    return active;
}
pair<double,double> building::get_position()const {
    return position;
}
unsigned int building::get_range()const {
    return attributes.atk.range;
}
unsigned int building::get_damage() const {
    return attributes.atk.damage;
}
atk_type building::get_attack_type() const {
    return attributes.atk.type;
}
bool building::in_range(pair<double,double> objective) const {
    double rad=attributes.atk.range;
    double x=objective.first-position.first;
    double y=objective.second-position.second;
    return (x*x+y*y)<=(rad*rad);
}
bool building::can_attack() const {
    return atk_counter==0;
}
void building::update() {
    if(active) {
        if(atk_counter>0) atk_counter--;
    }
}
void building::draw() const {
    if(active)
        draw_centered(attributes.bitmap,position.first,position.second);
}
tower_atk building::attack(const pair<double,double> target) {
    if(atk_counter>0) debug_log::report("tower attack before counter reach 0",warning,true,false,false);
    reset_counter();
    return tower_atk(attributes.atk,position,target);
}

void building::reset_counter() {
    atk_counter=atk_delay;
}

bool building::check() const {
    return true;
}

//TITLE: tower_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7-4
//DESCRIPTION: defines an user tower

#include "tower.h"
//TOWER

tower::tower() {
    atk_counter=0;
    position=make_pair(-1,-1);
    atk_delay=0;
    active=false;
}
tower::tower(const tower_attributes &attributes,double posx,double posy,const ALLEGRO_TIMER *timer) {
    this->attributes=&attributes;
    this->position=make_pair(posx,posy);
    this->timer=timer;
    set_delay();
    reset_counter();
    active=true;
}
tower::~tower() {
}
string tower::get_name() const {
    return attributes->name;
}
unsigned int tower::get_range()const {
    return attributes->atk.range;
}
unsigned int tower::get_damage() const {
    return attributes->atk.damage;
}
unsigned int tower::get_cost() const {
    return attributes->cost;
}
atk_type tower::get_attack_type() const {
    return attributes->atk.type;
}
bool tower::in_range(pair<double,double> target) const {
    double rad=attributes->atk.range;
    double x=target.first-position.first;
    double y=target.second-position.second;
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
    unsigned int hoffset=get_bitmap_height(attributes->bitmap)/2;
    draw_centered(attributes->bitmap,position.first,position.second-hoffset);
}

tower_atk tower::attack(const pair<double,double> target) {
    if(atk_counter>0) debug_log::report("tower attack before counter reach 0",warning,true,false,false);
    if(in_range(target)==false) debug_log::report("tower attack out of range",warning,true,false,false);
    reset_counter();
    unsigned int hoffset=get_bitmap_height(attributes->bitmap)/3;
    pair<double,double> pos=position;
    pos.second-=hoffset*2;
    return tower_atk(attributes->atk,pos,target,timer);
}
bool tower::check() const {
    bool b=true;
    if(attributes->check()==false) b=false;
    if(atk_delay==0) b=false;
    return b;
}
//PRIVATE
void tower::set_delay() {
    atk_delay=get_frames(attributes->atk.delay,timer);
}
void tower::reset_counter() {
    atk_counter=atk_delay;
}


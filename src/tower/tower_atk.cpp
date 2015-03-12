//TITLE: TOWER_ATK_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines the attack of buildings

#include "tower_atk.h"

tower_atk::tower_atk() {
    position=make_pair(-1,-1);
    destiny=make_pair(-1,-1);
    rotation=0;
    collide=false;
    active=false;
    valid=false;
    speed=0;
}

tower_atk::tower_atk(const atk_attributes &attributes,pair<double,double> position,pair<double,double> destiny,const ALLEGRO_TIMER *timer) {
    this->attributes=&attributes;
    this->collision_anim=this->attributes->collision_anim;
    this->position=position;
    this->destiny=destiny;
    set_speed(timer);
    set_rotation();
    collide=false;
    active=true;
    valid=true;
}
tower_atk::~tower_atk() {
}
void tower_atk::invalidate() {
    valid=false;
}
unsigned int tower_atk::get_damage()const {
    return attributes->damage;
}
double tower_atk::get_speed() const {
    return attributes->speed;
}
unsigned int tower_atk::get_range() const {
    return attributes->range;
}
atk_type tower_atk::get_type() const {
    return attributes->type;
}
bool tower_atk::is_valid() const {
    return valid;
}
bool tower_atk::hit() const {
    return collide;
}
void tower_atk::update() {
    if(active) {
        if(collide==false) {
            position=movement_update(position,destiny,attributes->speed);
            if(position==destiny) collision();
        }
        else {
            collision_anim.update(); //animation update
            if(collision_anim.is_active()==false) active=false;
        }
    }
}
//redraw tower atk
void tower_atk::draw() const {
    if(active) {
        if(collide==false) draw_rotated(attributes->bitmap,position.first,position.second,rotation);
        //draw_centered(attributes.bitmap,position.first,position.second);
        else collision_anim.draw(destiny.first,destiny.second);
    }
}
bool tower_atk::check() const {
    bool b=true;
    if(attributes->check()==false) b=false;
    return b;
}
//when attack hit, starts collision, and damage enemy (if still available)
void tower_atk::collision() {
    if(collide==false) {
        collide=true;
        collision_anim.animation_loop(false);
        collision_anim.start();
    }
}
void tower_atk::set_speed(const ALLEGRO_TIMER *timer) {
    speed=convert_speed(attributes->speed,timer);
}

void tower_atk::set_rotation() {
    double dx=destiny.first-position.first;
    dx+=0.00000001;
    double dy=destiny.second-position.second;
    rotation=atan(dy/dx);
    if(position.first>destiny.first) rotation+=3.141592;
}

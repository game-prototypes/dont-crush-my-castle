//TITLE: TOWER_ATK_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: defines the attack of buildings

#include "tower_atk.h"

atk_attributes::atk_attributes() {
    damage=range=delay=speed=0;
    type=shoot_atk;
}
atk_attributes::atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,double speed,atk_type type) {
    this->bitmap=bitmap;
    this->collision_anim=collision_anim;
    this->damage=damage;
    this->range=range;
    this->delay=delay;
    this->type=type;
    this->speed=speed;
}
atk_attributes::~atk_attributes() {
}
void atk_attributes::clear() {
    damage=range=delay=0;
    type=shoot_atk;
    collision_anim.clear();
    bitmap=NULL;
}
void atk_attributes::destroy() {
    al_destroy_bitmap(bitmap);
    bitmap=NULL;
    collision_anim.destroy();
    clear();
}
bool atk_attributes::check() const {
    bool b=true;
    if(delay==0 && type!=continuous_atk) {
        debug_log::report("attack delay equals 0",warning,true,false,false);
        b=false;
    }
    if(range==0) {
        debug_log::report("attack range equals 0",warning,true,false,false);
        b=false;
    }
    if(damage==0) {
        debug_log::report("attack damage equals 0",warning,true,false,false);
        b=false;
    }
    if(bitmap==NULL) b=false;
    if(speed<=0 || delay<=0) b=false;
    if(collision_anim.check()==false) b=false;
    return b;
}

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
    this->attributes=attributes;
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
    return attributes.damage;
}
double tower_atk::get_speed() const {
    return attributes.speed;
}
unsigned int tower_atk::get_range() const {
    return attributes.range;
}
atk_type tower_atk::get_type() const {
    return attributes.type;
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
            position=movement_update(position,destiny,attributes.speed);
            if(position==destiny) collision();
        }
        else {
            attributes.collision_anim.update(); //animation update
            if(attributes.collision_anim.is_active()==false) active=false;
        }
    }
}
//redraw tower atk
void tower_atk::draw() const {
    if(active) {
        if(collide==false) draw_rotated(attributes.bitmap,position.first,position.second,rotation);
        //draw_centered(attributes.bitmap,position.first,position.second);
        else attributes.collision_anim.draw(destiny.first,destiny.second);
    }
}
bool tower_atk::check() const {
    bool b=true;
    if(attributes.check()==false) b=false;
    return b;
}
//when attack hit, starts collision, and damage enemy (if still available)
void tower_atk::collision() {
    if(collide==false) {
        collide=true;
        attributes.collision_anim.animation_loop(false);
        attributes.collision_anim.start();
    }
}
void tower_atk::set_speed(const ALLEGRO_TIMER *timer) {
    speed=convert_speed(attributes.speed,timer);
}

void tower_atk::set_rotation() {
    double dx=destiny.first-position.first;
    dx+=0.00000001;
    double dy=destiny.second-position.second;
    rotation=atan(dy/dx);
    if(position.first>destiny.first) rotation+=3.141592;
}

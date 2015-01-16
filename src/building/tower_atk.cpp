//TITLE: TOWER_ATK_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines the attack of buildings

#include "tower_atk.h"

atk_attributes::atk_attributes() {
    damage=range=delay=0;
    type=shoot_atk;
}
atk_attributes::atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,atk_type type) {
    this->bitmap=bitmap;
    this->collision_anim=collision_anim;
    this->damage=damage;
    this->range=range;
    this->delay=delay;
    this->type=type;
}
void atk_attributes::clear() {
    damage=range=delay=0;
    type=shoot_atk;
    collision_anim.clear();
    bitmap=NULL;
}
void atk_attributes::destroy() {
    al_destroy_bitmap(bitmap);
    collision_anim.destroy();
    clear();
}
bool atk_attributes::check() const {
    bool b=true;
    if(delay==0) {
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
    return b;
}

tower_atk::tower_atk() {
    position=make_pair(-1,-1);
    destiny=make_pair(-1,-1);
    collide=false;
    active=false;
}

tower_atk::tower_atk(const atk_attributes &attributes,pair<double,double> position,pair<double,double> destiny) {
    this->attributes=attributes;
    this->position=position;
    this->destiny=destiny;
    collide=false;
    check();
    active=true;
}


unsigned int tower_atk::get_damage()const {
    return attributes.damage;
}
bool tower_atk::is_active() const {
    return active;
}
bool tower_atk::hit() const {
    return collide;
}
void tower_atk::update() {
    if(active) {
        if(collide==false) {
            position=movement_update(position,destiny,atk_speed);
            if(position==destiny) collision();
        }
        else {
            attributes.collision_anim.update(); //animation update
            // if(attributes.collision_anim.is_active()==false) /*attributes.collision_anim.*/clear();
        }
    }
}
//redraw tower atk
void tower_atk::draw() {
    if(active) {
        if(collide==false)  al_draw_bitmap(attributes.bitmap,position.first,position.second,0);
        else attributes.collision_anim.draw(destiny.first,destiny.second);
    }
}

//when attack hit, starts collision, and damage enemy (if still available)
void tower_atk::collision() {
    if(collide==false) {
        collide=true;
        attributes.collision_anim.animation_loop(false);
        attributes.collision_anim.start();
    }
}
//check class is working properly
void tower_atk::check() const {
}

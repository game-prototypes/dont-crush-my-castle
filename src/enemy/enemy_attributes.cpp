//TITLE: ENEMY_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines each kind of enemy

#include "enemy_attributes.h"

enemy_attributes::enemy_attributes() {
    speed=max_life=armor=reward=0;
}
enemy_attributes::enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,unsigned int reward) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    this->speed=enemy_speed;
    this->reward=reward;
}
enemy_attributes::enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const map<enemy_animation,al_anim> &animation,unsigned int rewatd) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    this->animation=animation;
    this->speed=enemy_speed;
    this->reward=reward;
}
enemy_attributes::~enemy_attributes() {
}
void enemy_attributes::insert_animation(enemy_animation type,const al_anim &anim) {
    if(anim.size()==0) debug_log::report("setting empty animation",err,true,true,false);
    else {
        animation.erase(type);
        animation.insert(make_pair(type,anim));
        animation[type].stop(); //set the animation to inactive and restart counters
    }
}
void enemy_attributes::clear() {
    animation.clear();
    name.clear();
    speed=0;
    max_life=0;
    armor=0;
}
void enemy_attributes::destroy() {
    map<enemy_animation,al_anim>::iterator it;
    for(it=animation.begin(); it!=animation.end(); it++)(it->second).destroy();
    clear();
}
bool enemy_attributes::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("enemy info without name",err,true,true,false);
        b=false;
    }
    if(animation.size()!=6) {
        debug_log::report("enemy without all necesssary animations",err,true,true,false);
        b=false;
    }
    if(speed<=0) {
        debug_log::report("enemy speed<=0",err,true,true,false);
        b=false;
    }
    if(max_life==0) {
        debug_log::report("enemy info with life=0",err,true,true,false);
        b=false;
    }
    return b;
}
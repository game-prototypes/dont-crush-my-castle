//TITLE: ENEMY_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines each single enemy

#include "enemy.h"

//STRUCT ENEMY_INFO
enemy_info::enemy_info() {
    speed=max_life=armor=0;
}
enemy_info::enemy_info(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const ALLEGRO_TIMER *timer) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    set_speed(enemy_speed,timer);
}
enemy_info::enemy_info(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const map<enemy_animation,al_anim> &animation,const ALLEGRO_TIMER *timer) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    this->animation=animation;
    set_speed(enemy_speed,timer);
}
void enemy_info::insert_animation(enemy_animation type,const al_anim &anim) {
    if(anim.size()==0) debug_log::report("setting empty animation",err,true,true,false);
    else {
        animation.erase(type);
        animation.insert(make_pair(type,anim));
        animation[type].stop(); //set the animation to inactive and restart counters
    }
}
void enemy_info::set_speed(double enemy_speed,const ALLEGRO_TIMER *timer) {
    if(enemy_speed<0) {
        debug_log::report("enemy speed negative (set to positive)",warning,true,false,false);
        enemy_speed=-enemy_speed;
    }
    if(enemy_speed==0) debug_log::report("enemy speed set to 0",warning,true,false,false);
    speed=enemy_speed*al_get_timer_speed(timer);
}
void enemy_info::clear() {
    name.clear();
    speed=max_life=armor=0;
    animation.clear();
}
void enemy_info::destroy() {
    map<enemy_animation,al_anim>::iterator it;
    for(it=animation.begin(); it!=animation.end(); it++)(it->second).destroy();
    clear();
}
bool enemy_info::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("enemy info without name",err,true,true,false);
        b=false;
    }
    if(animation.size()<6) {
        debug_log::report("enemy without all necesssary animations",err,true,true,false);
        b=false;
    }
    if(speed<0) {
        debug_log::report("enemy with speed<0",err,true,true,false);
        b=false;
    }
    if(max_life==0) {
        debug_log::report("enemy info with life=0",err,true,true,false);
        b=false;
    }
    return b;
}




//############################CLASS ENEMY#############################

//CONSTRUCTORS
enemy::enemy() {
    life=level=0;
    position=destiny=make_pair(-1,-1);
    active=false;
}
enemy::enemy(enemy_info basic_info,unsigned int level,double posx,double posy) {
    life=basic_info.max_life;
    set_level(level);
    spawn(posx,posy);
    check();
    update();
}

//MODIFICATION
void enemy::set_level(unsigned int level) {
    this->level=level;
}
void enemy::spawn(double posx,double posy) {
    if(posx<0 ||posy<0) debug_log::report("enemy position negative",err,true,true,false);
    else {
        destiny=position=make_pair(posx,posy);
        active=true;
    }
    check();
}
//CONSULT
string enemy::get_name() const {
    return basic_info.name;
}
unsigned int enemy::get_life() const {
    return life;
}
unsigned int enemy::get_max_life() const {
    return basic_info.max_life;
}
pair<double,double> enemy::get_position() const {
    return position;
}
pair<double,double> enemy::get_destiny() const {
    return destiny;
}
bool enemy::alive() const {
    return life>0;
}
bool enemy::spawned() const {
    return active;
}
bool enemy::idle() const {
    return position==destiny;
}

//ENEMY CONTROL
void enemy::stop() {
    destiny=position;
    set_to_idle();
}
void enemy::move_to(double x,double y) {
    if(x<0 || y<0) debug_log::report("destiny negative",err,true,true,false);
    else {
        destiny.first=x;
        destiny.second=y;
        basic_info.animation[idle_anim].stop();
    }
}
void enemy::decrease_life(unsigned int dam) {
    if(dam>life) kill();
    else  life-=dam;
}
void enemy::damage(unsigned int dam) {
    if(basic_info.armor>dam) dam=0;
    else dam-=basic_info.armor;
    decrease_life(dam);
}
void enemy::kill() {
    life=0;
    basic_info.animation[current_animation].stop();
    current_animation=dead_anim;
    basic_info.animation[current_animation].animation_loop(false);
    basic_info.animation[current_animation].start();
}

void enemy::deactivate() {
    active=false;
}
void enemy::clear() {
    if(active==true) debug_log::report("enemy still active",err,true,true,false);
    else {
        basic_info.clear();
        life=level=0;
        position=destiny=make_pair(-1,-1);
    }
}

void enemy::update() {
    if(spawned()) {
        if(alive()) {
            if(!idle()) { //not idle option
                double x=destiny.first-position.first;
                double y=destiny.second-position.second;
                if(abs(x)>=abs(y)) { //vertical animation
                    if(x>0) change_movement_animation(up_anim);
                    else change_movement_animation(down_anim);
                }
                else { //horizontal animation
                    if(y>0) change_movement_animation(right_anim);
                    else change_movement_animation(left_anim);
                }
                position=movement_update(position,destiny,basic_info.speed);
                if(idle()) set_to_idle(); //if reach destiny
            }
        }
        else if(current_animation!=dead_anim) kill(); //killed
        basic_info.animation[current_animation].update(); //animation update
    }
}


void enemy::draw() {
    if(spawned()) {
        basic_info.animation[current_animation].draw(position.first,position.second);
    }
}

//PRIVATE
void enemy::change_movement_animation(enemy_animation anim) {
    if(current_animation!=anim) {
        unsigned int frame=basic_info.animation[current_animation].get_frame();
        basic_info.animation[current_animation].stop();
        current_animation=anim;
        basic_info.animation[current_animation].stop();
        basic_info.animation[current_animation].set_frame(frame);
        basic_info.animation[current_animation].activate();
    }
}
void enemy::set_to_idle() {
    stop_movement_anim();
    basic_info.animation[current_animation].stop(); //stop current anim (if it is not movememnt anim)
    current_animation=idle_anim;
    basic_info.animation[current_animation].animation_loop(true);
    basic_info.animation[current_animation].start();
}
void enemy::stop_movement_anim() {
    basic_info.animation[left_anim].stop();
    basic_info.animation[right_anim].stop();
    basic_info.animation[up_anim].stop();
    basic_info.animation[down_anim].stop();
}
void enemy::check() const {
}

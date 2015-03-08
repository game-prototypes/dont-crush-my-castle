//TITLE: ENEMY_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.3
//DESCRIPTION: defines each single enemy

#include "enemy.h"
//CONSTRUCTORS
enemy::enemy() {
    life=level=0;
    speed=0.0;
    position=destiny=make_pair(-1,-1);
    deactivate();
    current_animation=idle_anim;
    reward_given=false;
}
enemy::enemy(const enemy_attributes &attributes,unsigned int level,double posx,double posy,const ALLEGRO_TIMER *timer) {
    this->attributes=&attributes;
    current_animation=idle_anim;
    this->animation=this->attributes->animation;
    set_level(level);
    this->life=get_level_increment(this->attributes->max_life);
    set_speed(this->attributes->speed,timer);
    spawn(posx,posy);
    update();
}
enemy::~enemy() {
}
//MODIFICATION
void enemy::spawn(double posx,double posy) {
    if(posx<0 || posy<0) debug_log::report("enemy position negative",err,true,true,false);
    else {
        destiny=make_pair(posx,posy);
        set_position(posx,posy);
        activate();
    }
    reward_given=false;
}
//CONSULT
string enemy::get_name() const {
    return attributes->name;
}
double enemy::get_speed() const {
    return attributes->speed;
}
unsigned int enemy::get_life() const {
    return life;
}
unsigned int enemy::get_level() const {
    return level;
}
unsigned int enemy::get_max_life() const {
    return get_level_increment(attributes->max_life);
}
unsigned int enemy::get_reward() {
    reward_given=true;
    return get_level_increment(attributes->reward);
}
bool enemy::is_reward_given() const {
    return reward_given;
}
pair<double,double> enemy::get_destiny() const {
    return destiny;
}
bool enemy::alive() const {
    return life>0;
}
bool enemy::spawned() const {
    return is_active();
}
bool enemy::idle() const {
    return position==destiny;
}
enemy_animation enemy::get_current_animation() const {
    return current_animation;
}

//ENEMY CONTROL
void enemy::stop() {
    destiny=position;
    set_to_idle();
}
void enemy::move_to(double x,double y) {
    if(x<0 || y<0) debug_log::report("destiny negative",err,true,true,false);
    else {
        if(x==position.first && y==position.second) set_to_idle();
        else {
            destiny.first=x;
            destiny.second=y;
            set_movement_animation();
            animation[idle_anim].stop();
        }
    }
}
void enemy::decrease_life(unsigned int dam) {
    if(dam>life) kill();
    else  life-=dam;
}
void enemy::damage(unsigned int dam) {
    unsigned int arm=get_level_increment(attributes->armor);
    if(arm>dam) dam=0;
    else dam-=arm;
    decrease_life(dam);
}
void enemy::kill() {
    life=0;
    animation[current_animation].stop();
    current_animation=dead_anim;
    animation[current_animation].animation_loop(false);
    animation[current_animation].start();
}
unsigned int enemy::destiny_reached() {
    deactivate();
    return 1;
}
void enemy::update() {
    if(spawned()) {
        if(alive()) {
            if(!idle()) { //not idle option
                position=movement_update(position,destiny,speed);
            }
            else set_to_idle(); //if reach destiny
        }
        else if(current_animation!=dead_anim) kill(); //killed
        animation[current_animation].update(); //animation update
        if(current_animation==dead_anim && animation[current_animation].is_active()==false)   deactivate();
    }
}
void enemy::draw() const {
    if(spawned()) {
        map<enemy_animation,al_anim>::const_iterator it;
        it=animation.find(current_animation);
        unsigned int hoffset=it->second.get_height()/2;
        it->second.draw(position.first,position.second-hoffset);
    }
}
bool enemy::check() const {
    bool b=attributes->check();
    if(life>get_max_life()) {
        b=false;
        debug_log::report("enemy life>max life",warning,true,true,false);
    }
    if(animation.size()!=6) b=false;
    if(speed<=0) {
        b=false;
        debug_log::report("speed<=0",err,true,true,false);
    }
    if(position.first<0.0 || position.second<0.0 || destiny.first<0.0 || destiny.second<0.0) b=false;
    return b;
}

//PRIVATE
void enemy::change_movement_animation(enemy_animation anim) {
    if(current_animation!=anim) {
        unsigned int frame=animation[current_animation].get_frame();
        animation[current_animation].stop();
        current_animation=anim;
        animation[current_animation].stop();
        animation[current_animation].set_frame(frame);
        animation[current_animation].activate();
    }
}
void enemy::set_to_idle() {
    stop_movement_anim();
    destiny=position;
    animation[current_animation].stop(); //stop current anim (if it is not movememnt anim)
    current_animation=idle_anim;
    animation[current_animation].animation_loop(true);
    animation[current_animation].start();
}
void enemy::stop_movement_anim() {
    animation[left_anim].stop();
    animation[right_anim].stop();
    animation[up_anim].stop();
    animation[down_anim].stop();
}

void enemy::set_speed(double spd,const ALLEGRO_TIMER *timer) {
    this->speed=convert_speed(spd,timer);
}
void enemy::set_level(unsigned int level) {
    this->level=level;
}
void enemy::set_movement_animation() {
    double x=destiny.first-position.first;
    double y=destiny.second-position.second;
    if(abs(x)>=abs(y)) { //horizontal animation
        if(x>0) change_movement_animation(right_anim);
        else change_movement_animation(left_anim); //position 0,0 is top-left
    }
    else { //vertical animation
        if(y>0) change_movement_animation(down_anim);
        else change_movement_animation(up_anim);
    }
}
unsigned int enemy::get_level_increment(unsigned int value) const {
    return (unsigned int)(value+(value*(level*level_ratio)));
}

//TITLE: ENEMY_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: defines each single enemy

#include "enemy.h"

//CONSTRUCTORS
enemy::enemy() {
    life=level=armor=speed=0;
    position=destiny=make_pair(-1,-1);
    active=false;
}
enemy::enemy(const string &name,unsigned int life,unsigned int armor,double speed,const map<enemy_animation,al_anim> &animation,const ALLEGRO_TIMER *timer) {
    this->name=name;
    set_life(life);
    set_armor(armor);
    set_speed(speed,timer);
    this->animation=animation;
    position=destiny=make_pair(-1,-1);
    level=0;
    active=false;
}
enemy::enemy(const string &name,unsigned int life,unsigned int armor,double speed,const ALLEGRO_TIMER *timer) {
    this->name=name;
    set_life(life);
    set_armor(armor);
    set_speed(speed,timer);
    position=destiny=make_pair(-1,-1);
    level=0;
    active=false;
}
//MODIFICATION
void enemy::set_life(unsigned int life) {
    this->life=life;
}
void enemy::set_armor(unsigned int armor) {
    this->armor=armor;
}
void enemy::set_speed(double enemy_speed,const ALLEGRO_TIMER *timer) {
    if(enemy_speed<0) {
        debug_log::report("enemy speed negative (set to positive)",warning,true,false,false);
        enemy_speed=-enemy_speed;
    }
    if(enemy_speed==0) debug_log::report("enemy speed set to 0",warning,true,false,false);
    speed=enemy_speed*al_get_timer_speed(timer);
}
void enemy::set_idle_animation(const al_anim &idle) {
    insert_animation(idle_anim,idle);
}
void enemy::set_dead_animation(const al_anim &dead) {
    insert_animation(dead_anim,dead);
}
void enemy::set_movement_animation(const al_anim &up,const al_anim &down,const al_anim &left,const al_anim &right) {
    unsigned int siz=up.size();
    if(siz==0 || down.size()==0 || left.size()==0 || right.size()==0) debug_log::report("setting empty animation",err,true,true,false);
    else {
        insert_animation(up_anim,up);
        if(down.size()!=siz) debug_log::report("movement animations size dont match",warning,true,false,false);
        insert_animation(down_anim,down);
        if(left.size()!=siz) debug_log::report("movement animations size dont match",warning,true,false,false);
        insert_animation(left_anim,left);
        if(right.size()!=siz) debug_log::report("movement animations size dont match",warning,true,false,false);
        insert_animation(left_anim,left);
    }
}

//CONSULT
string enemy::get_name() const {
    return name;
}
unsigned int enemy::get_life() const {
    return life;
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

void enemy::spawn(double posx,double posy) {
    destiny=position=make_pair(posx,posy);
    active=true;
    update();
}
void enemy::stop() {
    destiny=position;
    set_to_idle();
}
void enemy::decrease_life(unsigned int dam) {
    if(dam>life) kill();
    else  life-=dam;
}
void enemy::move_to(double x,double y) {
    destiny.first=x;
    destiny.second=y;
    animation[idle_anim].stop();
}
void enemy::damage(unsigned int dam) {
    if(armor>dam) dam=0;
    else dam-=armor;
    decrease_life(dam);
}

void enemy::kill() {
    life=0;
    animation[current_animation].stop();
    current_animation=dead_anim;
    animation[current_animation].animation_loop(false);
    animation[current_animation].start();
}

void enemy::deactivate() {
    active=false;
}

void enemy::update() {
    if(spawned()) {
        if(alive()) {
            if(!idle()) {
        double x=destiny.first-position.first;
        double y=destiny.second-position.second;
        if(abs(x)>=abs(y)){ //vertical animation
        	if(x>0) change_movement_animation(up_anim);
        	else change_movement_animation(down_anim);
        }
        else{//horizontal animation
        	if(y>0) change_movement_animation(right_anim);
        	else change_movement_animation(left_anim);
        }
                position=movement_update(position,destiny,speed);
                if(idle()) set_to_idle(); //if reach destiny
            }
        }
        else if(current_animation!=dead_anim) kill();
        animation[current_animation].update();
    }
}


void enemy::draw() {
    if(spawned()) {
        animation[current_animation].draw(position.first,position.second);
    }
}

//PRIVATE

void enemy::insert_animation(enemy_animation anim_type,const al_anim &anim) {
    if(anim.size()==0) debug_log::report("setting empty animation",err,true,true,false);
    else {
        animation.erase(anim_type);
        animation.insert(make_pair(anim_type,anim));
        animation[anim_type].stop(); //set the animation to inactive and restart counters
    }
}
void enemy::change_movement_animation(enemy_animation anim){
	if(current_animation!=anim){
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
void enemy::check() {
    if(position.first<0 || position.second<0 || destiny.first<0 || destiny.second<0) debug_log::report("enemy position or destiny <0",err,true,true,false);
    if(name.empty()) debug_log::report("enemy instance without name",warning,true,false,false);
    if(animation.size()<6)   debug_log::report("enemy without all necesssary animations",err,true,true,false);
    if(speed<0) debug_log::report("enemy with speed<0",err,true,true,false);
}

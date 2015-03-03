//TITLE: ENEMY_SET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#include "enemy_set.h"

//CONSTRUCTORS
enemy_set::enemy_set() {
}
enemy_set::enemy_set(const string &name,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
}
enemy_set::enemy_set(const string &name,const vector<enemy_attributes> &enemy_list,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    for(unsigned int i=0; i<enemy_list.size(); i++)
        add_enemy(enemy_list[i]);
}
enemy_set::enemy_set(const string &name,const enemy_attributes &enemy_att,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    add_enemy(enemy_att);
}
enemy_set::~enemy_set() {
    name.clear();
    map<string,enemy_attributes>::iterator it;
    for(it=enemies.begin(); it!=enemies.end(); it++)
        (it->second).destroy();
    clear();
}
//MODIFICATION
void enemy_set::set_name(const string &name) {
    this->name=name;
}
void enemy_set::add_enemy(const enemy_attributes &info) {
    if(enemies.insert(make_pair(info.name,info)).second==false) debug_log::report("already exists enemy with given name "+info.name,err,true,true,false);
}
void enemy_set::set_timer(const ALLEGRO_TIMER *timer) {
    this->timer=timer;
}
void enemy_set::remove_enemy(const string &name) {
    enemies.erase(name);
}
void enemy_set::clear() {
    enemies.clear();
    name.clear();
    timer=NULL;
}
//CONSULT
string enemy_set::get_name() const {
    return name;
}
unsigned int enemy_set::size() const {
    return enemies.size();
}
bool enemy_set::empty() const {
    return enemies.empty();
}
bool enemy_set::is_enemy(const string &name) const {
    if(enemies.find(name)!=enemies.end()) return true;
    else return false;
}
enemy enemy_set::spawn_enemy(const string &name,unsigned int level,double posx,double posy) {
    if(enemies.find(name)==enemies.end()) {
        debug_log::report("spawning non existing enemy",err,true,true,false);
        return enemy();
    }
    else
        return enemy(enemies[name],level,posx,posy,timer);
    return enemy();
}
bool enemy_set::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("enemy_set with no name",warning,true,false,false);
        b=false;
    }
    if(timer==NULL) {
        debug_log::report("timer not set",err,true,true,false);
        b=false;
    }
    return b;
}

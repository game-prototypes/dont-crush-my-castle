//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.4
//DESCRIPTION: stores a set of towers

#include "tower_set.h"


tower_set::tower_set() {
}
tower_set::tower_set(const string &name,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
}
tower_set::tower_set(const string &name,const vector<tower_attributes> &tower_list,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    for(unsigned int i=0; i<tower_list.size(); i++)
        add_tower(tower_list[i]);
}
tower_set::tower_set(const string &name,const tower_attributes &tower_attr,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    add_tower(tower_attr);
}
tower_set::~tower_set() {
    name.clear();
    map<string,tower_attributes>::iterator it;
    for(it=towers.begin(); it!=towers.end(); it++)
        (it->second).destroy();
    clear();
}

//MODIFICATION
void tower_set::set_name(const string &name) {
    this->name=name;
}
void tower_set::add_tower(const tower_attributes &info) {
    if(towers.insert(make_pair(info.name,info)).second==false) debug_log::report("already exists enemy with given name "+info.name,err,true,true,false);
}
void tower_set::set_timer(const ALLEGRO_TIMER *timer) {
    this->timer=timer;
}
void tower_set::remove_tower(const string &name) {
    towers.erase(name);
}
void tower_set::clear() {
    name.clear();
    towers.clear();
    timer=NULL;
}
//CONSULT
string tower_set::get_name() const {
    return name;
}
unsigned int tower_set::get_size() const {
    return towers.size();
}
bool tower_set::empty() const {
    return towers.empty();
}
bool tower_set::is_tower(const string &name) const{
 if(towers.find(name)!=towers.end()) return true;
    else return false;
}
tower tower_set::spawn_tower(const string &name,double posx,double posy) {
    if(towers.find(name)==towers.end()) {
        debug_log::report("spawning non existing tower",err,true,true,false);
        return tower();
    }
    else
        return tower(towers[name],posx,posy,timer);
}
bool tower_set::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("tower_set with no name",warning,true,false,false);
        b=false;
    }
    if(timer==NULL) {
        debug_log::report("timer not set",err,true,true,false);
        b=false;
    }
    return b;
}
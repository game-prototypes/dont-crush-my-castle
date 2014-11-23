//TITLE: ENEMY_SET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#include "enemyset.h"

//CONSTRUCTORS
enemy_set::enemy_set() {
}
enemy_set::enemy_set(const string &name) {
    set_name(name);
}
enemy_set::enemy_set(const string &name,const vector<enemy_info> &enemy_list) {
    set_name(name);
    for(unsigned int i=0; i<enemy_list.size(); i++)
        add_enemy(enemy_list[i]);
}
enemy_set::~enemy_set() {
    name.clear();
    map<string,enemy_info>::iterator it;
    for(it=enemies.begin(); it!=enemies.end(); it++)
        (it->second).destroy();
    enemies.clear();
}
//MODIFICATION
void enemy_set::set_name(const string &name) {
    this->name=name;
    if(this->name.empty()) debug_log::report("enemy_set with no name",warning,true,false,false);
}
void enemy_set::add_enemy(const enemy_info &info) {
    if(enemies.insert(make_pair(info.name,info)).second==false) debug_log::report("already exists enemy with given name "+info.name,err,true,true,false);
}
//CONSULT
string enemy_set::get_name() const {
    return name;
}

enemy enemy_set::spawn_enemy(const string &name,unsigned int level,double posx,double posy) {
    if(enemies.find(name)==enemies.end()) {
        debug_log::report("spawning non existing enemy",err,true,true,false);
        return enemy();
    }
    else
        return enemy(enemies[name],level,posx,posy);
}


//PRIVATE
void check() {
}

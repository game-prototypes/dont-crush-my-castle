//TITLE:GAME_OBJECTS_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: stores all instantiated ofjects in the scene
#include "game_objects.h"

game_objects::game_objects() {
    tower_id=0;
}
game_objects::game_objects(const list<enemy> &spawned_enemies,const map<tower_id,tower> &spawned_towers) {
    this->spawned_enemies=spawned_enemies;
    this->spawned_towers=spawned_towers;
    if(spawned_towers.empty()) current_id=0;
    else current_id=(spawned_towers.rbegin()->first)+1;
}
game_objects::~game_objects() {
    spawned_towers.clear();
    spawned_enemies.clear();
}
void game_objects::add_enemy(const enemy &new_enemy) {
    spawned_enemies.push_back(enemy);
}
tower_id game_objects::add_tower(const tower &new_tower) {
    spawned_towers.insert(make_pair(current_id,new_tower));
    current_id++;
    return current_id-1;
}
void game_objects::remove_tower(tower_id id) {
    spawned_towers.remove(id);
}
unsigned int game_objects::enemy_size() const {
    return spawned_enemies.size();
}
unsigned int game_objects::tower_size() const {
    return spawned_towers.size();
}
bool game_objects::is_last(list<enemy>::iterator it) const {
    if(it==spawned_enemies.end) return true;
    else return false;
}
list<enemy>::iterator game_objects::get_first() const {
    return spawned_enemies.begin();
}
tower &get_tower(tower_id id)const {
    return spawned_towers[id];
}

vector<tower_id> game_objects::update_towers() {
    vector<tower_id> res;
    for(map<tower_id,tower>::iterator it=spawned_towers.begin; it!=spawned_towers.end; it++) {
        it->second.update();
        if(it->second.can_attack()) res.push_back(it->first);
    }
    return res;
}
void game_objects::update_enemies() {
    for(list<enemy>::iterator it=spawned_enemies.begin; it!=spawned_enemies.end; it++) {
        it->update();
        if(it->is_active()==false) spawned_enemies.erase(it); //maybe problem here!!!
    }
}
bool game_objects::check() {
    bool b=true;
    return b;
}
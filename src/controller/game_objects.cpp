//TITLE:GAME_OBJECTS_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: stores all instantiated objects in the scene
#include "game_objects.h"

game_objects::game_objects() {
    current_id=1;
    killed=0;
}
/*game_objects::game_objects(const list<enemy> &spawned_enemies,const map<tower_id,tower> &spawned_towers,const multimap<list<enemy>::iterator,tower_atk> &spawned_attacks) {
    this->spawned_enemies=spawned_enemies;
    this->spawned_towers=spawned_towers;
    this->spawned_attacks=spawned_attacks;
    if(spawned_towers.empty()) current_id=1;
    else current_id=(spawned_towers.rbegin()->first)+1;
    killed=0;
}*/
game_objects::~game_objects() {
    clear();
}
void game_objects::add_enemy(const enemy &new_enemy) {
    spawned_enemies.push_back(new_enemy);
}
tower_id game_objects::add_tower(const tower &new_tower) {
    spawned_towers.insert(make_pair(current_id,new_tower));
    current_id++;
    return current_id-1;
}
void game_objects::add_attack(const tower_atk &atk,list<enemy>::iterator target) {
    spawned_attacks.push_back(make_pair(target,atk));
}
void game_objects::remove_tower(tower_id id) {
    spawned_towers.erase(id);
}
void game_objects::clear() {
    spawned_enemies.clear();
    spawned_towers.clear();
    spawned_attacks.clear();
    current_id=1;
    killed=0;
}
unsigned int game_objects::enemy_size() const {
    return spawned_enemies.size();
}
unsigned int game_objects::tower_size() const {
    return spawned_towers.size();
}
unsigned int game_objects::killed_enemies() const {
    return killed;
}
list<enemy>::iterator game_objects::get_first_enemy() {
    return spawned_enemies.begin();
}
list<enemy>::const_iterator game_objects::get_first_enemy() const {
    return spawned_enemies.begin();
}
list<enemy>::iterator game_objects::get_last_enemy() {
    return spawned_enemies.end();
}
list<enemy>::const_iterator game_objects::get_last_enemy() const {
    return spawned_enemies.end();
}
tower *game_objects::get_tower(tower_id id) {
    return &spawned_towers[id];
}
const tower *game_objects::get_tower(tower_id id) const {
    map<tower_id,tower>::const_iterator it;
    it=spawned_towers.find(id);
    return &(it->second);
}
vector<tower_id> game_objects::update_towers() {
    vector<tower_id> res;
    for(map<tower_id,tower>::iterator it=spawned_towers.begin(); it!=spawned_towers.end(); it++) {
        it->second.update();
        if(it->second.can_attack()) res.push_back(it->first);
    }
    return res;
}
vector<list<enemy>::iterator> game_objects::update_enemies() {
    vector<list<enemy>::iterator> res;
    vector<list<enemy>::iterator> to_invalidate;
    for(list<enemy>::iterator it=spawned_enemies.begin(); it!=spawned_enemies.end(); it++) {
        bool can_die=false;
        if(it->alive()) can_die=true;
        it->update();
        if(it->is_active()==false) {
            list<enemy>::iterator it2=it;
            it--;
            spawned_enemies.erase(it2);
        }
        else if(it->alive()==false) {
            if(can_die==true) {
                killed++;
                to_invalidate.push_back(it);
            }
        }
        else if(it->idle()) res.push_back(it);
    }
    invalidate_attacks(to_invalidate);
    return res;
}
void game_objects::update_attacks() {
    list<pair<list<enemy>::iterator,tower_atk> >::iterator it,it2;
    for(it=spawned_attacks.begin(); it!=spawned_attacks.end(); it++) {
        bool can_collide=false;
        if(it->second.hit()==false) can_collide=true;
        it->second.update();
        if(it->second.is_active()==false) {
            it2=it;
            it--;
            spawned_attacks.erase(it2);
        }
        else if(it->second.hit() && can_collide && it->second.is_valid()) it->first->damage(it->second.get_damage());
    }
}
void game_objects::draw_towers() const {
    for(map<tower_id,tower>::const_iterator it=spawned_towers.begin(); it!=spawned_towers.end(); it++)
        it->second.draw();
}
void game_objects::draw_enemies() const {
    for(list<enemy>::const_iterator it=spawned_enemies.begin(); it!=spawned_enemies.end(); it++)
        it->draw();
}
void game_objects::invalidate_attacks(vector<list<enemy>::iterator> to_invalidate) {
    list<pair<list<enemy>::iterator,tower_atk> >::iterator it;
    for(it=spawned_attacks.begin(); it!=spawned_attacks.end(); it++) {
        for(unsigned int i=0; i<to_invalidate.size(); i++) {
            if(it->first==to_invalidate[i]) it->second.invalidate();
        }
    }
}
bool game_objects::check() {
    bool b=true;
    return b;
}
//TITLE:GAME_OBJECTS_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: stores all instantiated objects in the scene
#include "game_objects.h"

game_objects::game_objects() {
    current_id=1;
    killed=0;
    reward=0;
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
    destroy_texts();
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
void game_objects::add_text(const text_handler &new_text) {
    string t=new_text.get_tag();
    texts.erase(t);
    texts.insert(make_pair(t,new_text));
}
void game_objects::remove_tower(tower_id id) {
    spawned_towers.erase(id);
}
void game_objects::remove_text(const string &tag) {
    texts.erase(tag);
}
void game_objects::clear() {
    spawned_enemies.clear();
    spawned_towers.clear();
    spawned_attacks.clear();
    texts.clear();
    current_id=1;
    killed=0;
    reward=0;
}
unsigned int game_objects::enemy_size() const {
    return spawned_enemies.size();
}
unsigned int game_objects::tower_size() const {
    return spawned_towers.size();
}
unsigned int game_objects::attack_size() const {
    return spawned_attacks.size();
}
unsigned int game_objects::texts_size() const {
    return texts.size();
}
bool game_objects::empty() const {
    return (spawned_enemies.empty() && spawned_attacks.empty() && spawned_towers.empty() && texts.empty());
}
unsigned int game_objects::killed_enemies() const {
    return killed;
}
unsigned int game_objects::get_reward() {
    unsigned int r=reward;
    reward=0;
    return r;
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
text_handler *game_objects::get_text(const string &tag) {
    return &texts[tag];
}
const text_handler *game_objects::get_text(string &tag) const {
    map<string,text_handler>::const_iterator it;
    it=texts.find(tag);
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
        it->update();
        if(it->is_active()==false) {
            list<enemy>::iterator it2=it;
            it--;
            killed++;
            to_invalidate.push_back(it2);
            spawned_enemies.erase(it2);
        }
        else if(it->idle()) res.push_back(it);
        else if(it->alive()==false && !it->is_reward_given()) {
            reward+=it->get_reward();
        }
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
void game_objects::draw() const {
    multimap<double,const game_object *> object_list;
    for(map<tower_id,tower>::const_iterator it=spawned_towers.begin(); it!=spawned_towers.end(); it++)
        object_list.insert(make_pair(it->second.get_position().second,&(it->second)));
    for(list<enemy>::const_iterator it=spawned_enemies.begin(); it!=spawned_enemies.end(); it++)
        object_list.insert(make_pair(it->get_position().second,&(*it)));
    for(list<pair<list<enemy>::iterator,tower_atk> >::const_iterator it=spawned_attacks.begin(); it!=spawned_attacks.end(); it++)
        object_list.insert(make_pair(it->second.get_position().second,&(it->second)));
    for(multimap<double,const game_object *>::const_iterator it=object_list.begin(); it!=object_list.end(); it++) {
        it->second->draw();
    }
    map<string,text_handler>::const_iterator text_list;
    for(text_list=texts.begin(); text_list!=texts.end(); text_list++) text_list->second.draw();
    // for(list<pair<list<enemy>::iterator,tower_atk> >::const_iterator it=spawned_attacks.begin(); it!=spawned_attacks.end(); it++)
    //  it->second.draw();
}
bool game_objects::check() {
    bool b=true;
    return b;
}
//PRIVATE
void game_objects::invalidate_attacks(vector<list<enemy>::iterator> to_invalidate) {
    list<pair<list<enemy>::iterator,tower_atk> >::iterator it;
    for(it=spawned_attacks.begin(); it!=spawned_attacks.end(); it++) {
        for(unsigned int i=0; i<to_invalidate.size(); i++) {
            if(it->first==to_invalidate[i]) it->second.invalidate();
        }
    }
}
void game_objects::destroy_texts() {
    map<string,text_handler>::iterator text_list;
    for(text_list=texts.begin(); text_list!=texts.end(); text_list++) text_list->second.destroy();
    texts.clear();
}
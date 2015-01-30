//TITLE:GAME_MASTER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: control the IA and in-game stuff (spawning,movement etc..)
#include "game_master.h"


//GAME SPAWNER

game_spawner::game_spawner() {
    delay=0;
}
game_spawner::game_spawner(const vector<spawn_wave> &waves,unsigned int delay) {
    this->waves=waves;
    this->delay=delay;
}
game_spawner::game_spawner(const spawn_wave &wave,unsigned int delay) {
    this->waves.push_back(wave);
    this->delay=delay;
}
game_spawner::~game_spawner() {
    clear();
}

void game_spawner::add_wave(const spawn_wave &wave) {
    waves.push_back(wave);
}
void game_spawner::clear() {
    waves.clear();
    delay=0;
}
unsigned int game_spawner::get_delay() const {
    return delay;
}
unsigned int game_spawner::get_total_waves() const {
    return waves.size();
}
const spawn_wave &game_spawner::get_wave(unsigned int wave_number) const {
    if(wave_number>=waves.size()) wave_number=0;
    return waves[wave_number];
}
bool game_spawner::check() const {
    bool b=true;
    for(unsigned int i=0; i<waves.size(); i++) {
        if(waves[i].empty()==true) b=false;
    }
    return b;
}

//GAME MASTER

game_spawner spawner;
enemy_set *enemies;
game_objects *objects;
const tilemap *game_map;
unsigned int current_wave;
bool active;


game_master::game_master() {
    this->current_wave=0;
    set_active(false);
}
game_master::game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map) {
    this->enemies=&enemies;
    this->objects=&objects;
    this->game_map=&game_map;
    current_wave=0;
    set_active(true);
}
game_master::~game_master() {
    current_wave=0;
    set_active(false);
}

unsigned int game_master::get_current_wave() const {
    return current_wave;
}
unsigned int game_master::get_total_waves() const {
    return spawner.get_total_waves();
}
bool game_master::is_active() const {
    return active;
}
void game_master::set_active(bool active) {
    this->active=active;
}
//updates all info
void game_master::update() {
    if(active) {
    }
}
bool game_master::check()const {
}
//Private
void game_master::update_attacks(vector<tower_id> &towers) {
}
void game_master::update_position(vector<list<enemy>::iterator> &enemy_list) {
}
void game_master::spawn(const spawn_wave &wave) {
}
void game_master::spawn(const string &enemy) {
}
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
    srand(time(NULL));
}
game_master::game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map) {
    this->enemies=&enemies;
    this->objects=&objects;
    this->game_map=&game_map;
    current_wave=0;
    set_active(true);
    srand(time(NULL));
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
        //  	vector<tower_id> update_towers();
        //update_tower_attacks;
        //  vector<list<enemy>::iterator> update_enemies();
        //update_enemy_position();
        //  	objects->update_attacks();
    }
}
bool game_master::check()const {
    bool b=true;
    return b;
}
//Private
void game_master::update_tower_attacks(vector<tower_id> &towers) {
}
void game_master::update_enemy_position(const vector<list<enemy>::iterator> &enemy_list) {
}
void game_master::update_attacks() {
}

void game_master::spawn(const spawn_wave &wave) {
}
void game_master::spawn(const string &enemy_name) {
    if(enemies->is_enemy(enemy_name)) {
        vector< pair<unsigned int,unsigned int> > spawner_vector=game_map->spawners_position();
        unsigned int rand_spaw = rand() % spawner_vector.size();
        objects->add_enemy(enemies->spawn_enemy(enemy_name,current_wave,spawner_vector[rand_spaw].first,spawner_vector[rand_spaw].second));
    }
    else debug_log::report("enemy name not in set",err,true,true,false);
}
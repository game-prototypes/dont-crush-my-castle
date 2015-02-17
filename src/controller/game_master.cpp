//TITLE:GAME_MASTER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
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
    add_wave(wave);
    this->delay=delay;
}
game_spawner::~game_spawner() {
    clear();
}
void game_spawner::add_wave(const spawn_wave &wave) {
    if(!wave.empty()) waves.push_back(wave);
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


game_master::game_master() {
    this->current_wave=0;
    set_active(false);
    srand(time(NULL));
    tower_atk_counter=0;
    wave_delay_counter=0;
    spawn_delay_counter=0;
}
game_master::game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map,const game_spawner &spawner,const ALLEGRO_TIMER *timer) {
    this->enemies=&enemies;
    this->objects=&objects;
    this->game_map=&game_map;
    this->spawner=spawner;
    current_wave=0;
    set_active(true);
    srand(time(NULL));
    set_delays(timer);
    tower_atk_counter=0;
    wave_delay_counter=0;
    spawn_delay_counter=0;
}
game_master::~game_master() {
    set_active(false);
    current_wave=0;
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
    tower_atk_counter=0;
}
//updates all info
void game_master::update() {
    if(active) {
        if(wave_delay_counter==0) {
            if(current_wave<spawner.get_total_waves()) {
                spawn(spawner.get_wave(current_wave));
                current_wave++;
            }
        }
        if(spawn_delay_counter==0) spawn();
        vector<tower_id> tids=objects->update_towers();
        //if(tower_atk_counter==0) update_tower_attacks(tids);
        objects->update_attacks();
        vector<list<enemy>::iterator> enemy_list=objects->update_enemies();
        update_enemy_position(enemy_list);
        if(current_wave==spawner.get_total_waves() && left.empty() && objects->enemy_size()==0) game_over();
        tower_atk_counter--;
        wave_delay_counter--;
        spawn_delay_counter--;
    }
}
bool game_master::check()const {
    bool b=true;
    if(current_wave==spawner.get_total_waves() && left.empty() && objects->enemy_size()==0 && active==true) b=false;
    return b;
}
//Private
void game_master::update_tower_attacks(vector<tower_id> &towers) {
    list<enemy>::iterator first=objects->get_first_enemy();
    list<enemy>::iterator last=objects->get_last_enemy();
    list<enemy>::iterator current_enemy;
    for(unsigned int i=0; i<towers.size(); i++) {
        tower *current_tower=objects->get_tower(towers[i]);
        list<enemy>::iterator target;
        bool target_found=false;
        int path_value=-1;
        for(current_enemy=first; current_enemy!=last; current_enemy++) {
            if(current_tower->in_range(current_enemy->get_position())) { //if enemy in range
                int new_path_value=game_map->get_path_value_of_position(target->get_position().first,target->get_position().second);
                if(!target_found || (target_found && new_path_value<path_value && new_path_value!=-1)) {
                    target_found=true;
                    target=current_enemy;
                    path_value=new_path_value;
                }
            }
            if(path_value==0) break;
        }
        if(target_found)
            objects->add_attack(current_tower->attack(target->get_position()),target);
    }
    tower_atk_counter=check_towers_atk_delay;
}
void game_master::update_enemy_position(const vector<list<enemy>::iterator> &enemy_list) {
    list<enemy>::iterator it;
    pair<double,double> dest;
    for(unsigned int i=0; i<enemy_list.size(); i++) {
        it=enemy_list[i];
        dest=game_map->get_next_position(it->get_position().first,it->get_position().second);
        it->move_to(dest.first,dest.second);
    }
}

void game_master::spawn(const spawn_wave &wave) {
    if(left.empty()) left=wave;
    else {
        spawn_wave aux;
        while(left.empty()==false) {
            aux.push(left.top());
            left.pop();
        }
        left=wave;
        while(aux.empty()==false) {
            left.push(aux.top());
            aux.top();
        }
    }
    wave_delay_counter=wave_delay;
}
void game_master::spawn() {
    if(left.empty()==false) {
        string enemy_name=left.top().second;
        if(left.top().first<=1) left.pop();
        else left.top().first--;
        if(enemies->is_enemy(enemy_name)) {
            vector< pair<unsigned int,unsigned int> > spawner_vector=game_map->spawners_position();
            unsigned int rand_spawn = rand() % spawner_vector.size();
            pair<double,double> spawn_position=game_map->translate_position(spawner_vector[rand_spawn].first,spawner_vector[rand_spawn].second);
            objects->add_enemy(enemies->spawn_enemy(enemy_name,current_wave,spawn_position.first,spawn_position.second));
        }
        else debug_log::report("enemy name not in set",err,true,true,false);
        spawn_delay_counter=spawn_delay; //resets counter
    }
}
void game_master::set_delays(const ALLEGRO_TIMER *timer) {
    spawn_delay=get_frames(enemies_spawn_delay,timer);
    wave_delay=get_frames(spawner.get_delay(),timer);
}
void game_master::game_over() {
    active=false;
    cout<<"Game Over\n";
    //stuff if game over
}
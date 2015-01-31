//TITLE: GAME_MASTER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: control the IA and in-game stuff (spawning,movement etc..)

#ifndef GAME_MASTER
#define GAME_MASTER

#include "game_objects.h"
#include "tilemap.h"
#include "enemy_set.h"
#include <stack>
//#include <stdlib.h>
//#include <time.h>

typedef std::stack<std::pair<unsigned int,string> > spawn_wave;
const double enemies_spawn_speed=0.1; //speed between spawning
//information about spawning enemies
class game_spawner {
private:
    vector<spawn_wave> waves;
    unsigned int delay; //delay between waves, in seconds
public:
    game_spawner();
    game_spawner(const vector<spawn_wave> &waves,unsigned int delay);
    game_spawner(const spawn_wave &wave,unsigned int delay);
    ~game_spawner();

    void add_wave(const spawn_wave &wave);
    void clear();
    unsigned int get_delay() const;
    unsigned int get_total_waves() const;
    const spawn_wave &get_wave(unsigned int wave_number)const;
    bool check() const;
};


class game_master {
private:
    game_spawner spawner;
    //list<pair<tower_atk,list<enemy>::iterator> spawned_attacks;
    spawn_wave left;
    enemy_set *enemies;
    game_objects *objects;
    const tilemap *game_map;
    unsigned int current_wave;
    bool active;
public:
    game_master();
    game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map);
    ~game_master();

    unsigned int get_current_wave() const;
    unsigned int get_total_waves() const;
    bool is_active() const;
    void set_active(bool active);
    //updates all info
    void update();
    bool check() const;
private:
    void update_tower_attacks(vector<tower_id> &towers);
    void update_enemy_position(const vector<list<enemy>::iterator> &enemy_list);
    void update_attacks();
    void spawn(const spawn_wave &wave);
    //spawn one enemy in a random place in map
    void spawn(const string &enemy_name);
};
#endif
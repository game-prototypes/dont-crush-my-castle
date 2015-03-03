//TITLE: GAME_MASTER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: control the IA and in-game stuff (spawning,movement etc..)

#ifndef GAME_MASTER
#define GAME_MASTER

#include "game_objects.h"
#include "player.h"
#include "tilemap.h"
#include "enemy_set.h"
#include <stack>
#include <functional>
//#include <stdlib.h>
//#include <time.h>

typedef std::stack<std::pair<unsigned int,string> > spawn_wave;
const double enemies_spawn_delay=1; //speed between spawning (seconds)
const unsigned int check_towers_atk_delay=1; //delay (in frames) between checks of tower attacks (costly operation to do each frame)

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
    const spawn_wave &get_wave(unsigned int wave_number) const;
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
    player *game_player;
    unsigned int current_wave;

    unsigned int spawn_delay; //in frames
    unsigned int wave_delay; //in frames

    unsigned int tower_atk_counter; //count for next update_tower_attacks
    unsigned int wave_delay_counter;
    unsigned int spawn_delay_counter;

    function<void()> win_function; //function when win, with enemies killed and parameter

    bool active;
public:
    game_master();
    game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map,player &game_player,const game_spawner &spawner,const ALLEGRO_TIMER *timer,function<void()> win_function);
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
    //spawn a wave (set it to left)
    void spawn(const spawn_wave &wave);
    //spawn one enemy in a random place in map
    void spawn();
    void set_delays(const ALLEGRO_TIMER *timer);
    void game_over();
};
#endif
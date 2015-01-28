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

//TODO: game_master.cpp!!!
typedef vector<pair<unsigned int quantity,string enemy> > spawn_wave;
class game_spawner {
private:
    vector<spawn_wave> waves;
    unsigned int delay;
    unsigned int current;
public:
    game_spawner();
    game_spawner(const vector<spawn_wave> &waves,unsigned int delay);
    game_spawner(const spawn_wave &wave,unsigned int delay);
    ~game_spawner();

    void restart() const;
    void add_wave(const spawn_wave &wave) const;
    bool active() const;
    unsigned int get_delay() const;
    spawn_wave get_wave();
    bool check() const;

};


class game_master {
private:
	game_spawner spawner;
    enemy_set *enemies;
    game_objects *objects;
    const tilemap *game_map;
public:
    game_master();
    game_master(enemy_set &enemies,game_objects &objects,const tilemap &tilemap);
    ~game_master();

//TODO




};



#endif
//TITLE: GAME_OBJECTS_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: stores all instantiated ofjects in the scene

#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#include "enemy.h"
#include "tower.h"
#include <list>

typedef unsigned int tower_id; //defines a id for a tile in the tileset
class game_objects {
private:
    list<enemy> spawned_enemies;
    map<tower_id,tower> spawned_towers;
    tower_id current_id;
public:
    game_objects();
    game_objects(const list<enemy> &spawned_enemies,const map<tower_id,tower> &spawned_towers);
    ~game_objects();
    //MODIFIERS
    void add_enemy(const enemy &new_enemy);
    tower_id add_tower(const tower &new_tower);
    void remove_tower(tower_id id);
    void clear(); //removes all data (without destroying)

    //CONSULT
    unsigned int enemy_size() const;
    unsigned int tower_size() const;

    bool is_last_enemy(list<enemy>::iterator it) const;
    list<enemy>::iterator get_first_enemy();
    list<enemy>::const_iterator get_first_enemy() const;
    tower *get_tower(tower_id id);
    const tower *get_tower(tower_id id) const;

    //updates all enemies and towers, removes unactive enemies, returns vector of towers ready to fire
    vector<tower_id> update_towers();
    void update_enemies();
    bool check();

};


#endif
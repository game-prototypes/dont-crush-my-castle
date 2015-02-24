//TITLE: GAME_OBJECTS_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: stores all instantiated ofjects in the scene

#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#include "enemy.h"
#include "tower.h"
#include <list>

typedef unsigned int tower_id; //defines a id for a tile in the tileset
//will be always >=1, 0 reserved for null id

class game_objects {
private:
    list<enemy> spawned_enemies;
    map<tower_id,tower> spawned_towers;
    list<pair<list<enemy>::iterator,tower_atk> > spawned_attacks;

    tower_id current_id;
    unsigned int killed;
public:
    game_objects();
    //game_objects(const list<enemy> &spawned_enemies,const map<tower_id,tower> &spawned_towers,const multimap<list<enemy>::iterator,tower_atk> &spawned_attacks);
    ~game_objects();
    //MODIFIERS
    void add_enemy(const enemy &new_enemy);
    tower_id add_tower(const tower &new_tower);
    void add_attack(const tower_atk &atk,list<enemy>::iterator target);
    void remove_tower(tower_id id);
    void clear(); //removes all data (without destroying)

    //CONSULT
    unsigned int enemy_size() const;
    unsigned int tower_size() const;
    unsigned int attack_size() const;
    //return true if every list is empty
    bool empty() const;
    unsigned int killed_enemies() const;
    list<enemy>::iterator get_first_enemy();
    list<enemy>::const_iterator get_first_enemy() const;
    list<enemy>::iterator get_last_enemy();
    list<enemy>::const_iterator get_last_enemy() const;
    tower *get_tower(tower_id id);
    const tower *get_tower(tower_id id) const;

    //updates all enemies and towers, removes unactive enemies, returns vector of towers ready to fire
    vector<tower_id> update_towers();
    //updates all enemies, returns all enemies in idle, set to invalid all attacks of killed enemy
    vector<list<enemy>::iterator> update_enemies();
    //updates all attacks, damaging all enemies when collided
    void update_attacks();
    // pair<vector<tower_id>,vector<list<gameobject::iterator>> update_gameobjets() const;
    void draw() const;
    bool check();

private:
    void invalidate_attacks(vector<list<enemy>::iterator> to_invalidate);

};


#endif

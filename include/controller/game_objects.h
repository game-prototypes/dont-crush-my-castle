//TITLE: GAME_OBJECTS_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: stores all instantiated ofjects in the scene

#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#include "enemy.h"
#include "tower.h"
#include "text_handler.h"
#include <list>

typedef unsigned int tower_id; //defines a id for a tile in the tileset
//will be always >=1, 0 reserved for null id

class game_objects {
private:
    list<enemy> spawned_enemies; //list of spawned enemies
    map<tower_id,tower> spawned_towers; //list of spawned towers
    map<string,text_handler> texts; //list of texts
    list<pair<list<enemy>::iterator,tower_atk> > spawned_attacks; //map of spawned attacks and targets
    unsigned int reward; //current reward value
    tower_id current_id; //current tower id to assign
    unsigned int killed; //number of enemies killed
public:
    //CONSTRUCTORS
    //default constructor
    game_objects();
    //DESTRUCTOR
    ~game_objects();
    //METHODS
    //adds given enemy to gameobjects
    void add_enemy(const enemy &new_enemy);
    //adds given tower to gameobjects, returns assigned tower id
    tower_id add_tower(const tower &new_tower);
    //adds given tower attack to gameobjects
    void add_attack(const tower_atk &atk,list<enemy>::iterator target);
    //adds a new text_handler, overriding any text with same tag
    void add_text(const text_handler &new_text);
    //removes tower with given id
    void remove_tower(tower_id id);
    //removed text with given tag
    void remove_text(const string &tag);
    //removes all data (without destroying)
    void clear();

    //return number of enemies
    unsigned int enemy_size() const;
    //return number of towers
    unsigned int tower_size() const;
    //return namber of attacks
    unsigned int attack_size() const;
    //return number of texts
    unsigned int texts_size() const;
    //return true if every list is empty
    bool empty() const;
    //return the number if killed enemies
    unsigned int killed_enemies() const;
    //rewards from dead enemies will accumulate until get_reward called
    unsigned int get_reward();
    //return an iterator to first enemy
    list<enemy>::iterator get_first_enemy();
    //return a const iterator to first enemy
    list<enemy>::const_iterator get_first_enemy() const;
    //return an iterator to last position of enemy (like enemy.end())
    list<enemy>::iterator get_last_enemy();
    //return a const iterator to last position of enemy (like enemy.end())
    list<enemy>::const_iterator get_last_enemy() const;
    //returns a pointer to tower instance with given id
    tower *get_tower(tower_id id);
    //returns a const pointer to tower instance with given id
    const tower *get_tower(tower_id id) const;
    //returns a pointer to text instance with given tag
    text_handler *get_text(const string &tag);
    //returns a const pointer to text instance with given tag
    const text_handler *get_text(string &tag) const;
    //updates all enemies and towers, removes unactive enemies, returns vector of towers ready to fire
    vector<tower_id> update_towers();
    //updates all enemies, returns all enemies in idle, set to invalid all attacks of killed enemy
    vector<list<enemy>::iterator> update_enemies();
    //updates all attacks, damaging all enemies when collided
    void update_attacks();
    //draw all gameobjects ordered by vertical position except texts
    void draw() const;
    //checks class
    bool check();

private:
    //nvalidates given attacks (animation will continue normally, but won't harm)
    void invalidate_attacks(vector<list<enemy>::iterator> to_invalidate);
    //destroy texts
    void destroy_texts();
};


#endif

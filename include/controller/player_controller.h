//TITLE: PLAYER_CONTROLLER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: controls the actions of the player

#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include "game_objects.h"
#include "tower_set.h"
#include "tilemap.h"


class player_controller {
private:
    map<pair<unsigned int,unsigned int>,tower_id> built_towers; //tile in map and tower_id

    tower_set *towers; //tower set of game
    game_objects *objects; //gameobjects of game
    tilemap *game_map; //map of game

public:
    //CONSTRUCTORS
    //default constructor
    player_controller();
    //full constructor
    player_controller(tower_set &towers,game_objects &objects,tilemap &game_map);
    //DESTRUCTOR
    ~player_controller();
    //number of towers in towerset
    unsigned int get_towers_size() const;
    //return all tower names in tower_set
    set<string> get_tower_names() const;
    //return the cost of tower with given name
    unsigned int get_tower_cost(const string &name) const;
    //return all the spawned towers
    unsigned int spawned_towers() const;
    //return true if can build in given position(in pixels)
    bool can_build(double x,double y) const;
    //build tower of given name in given position, will return true if succsefully built
    bool build_tower(const string &name,double x,double y);
    //remove tower of given position, return true if removed
    bool remove_tower(double x,double y);
    //return true if there is a tower in given position
    bool is_tower(double x,double y) const;
    //returns pointer to tower in given position
    const tower *get_tower(double x,double y) const;
    //checks class
    bool check() const;
private:
    //return id of tower in given position, 0 if no tower
    tower_id get_tower_id(double x,double y) const;
    //removes tower with given id
    void remove_tower(tower_id id);
    //translates position from pixels to tiles
    pair<unsigned int,unsigned int> translate_position(double x,double y) const;
    //translates position from tiles to pixels (centered)
    pair<double,double> translate_position(unsigned int x,unsigned int y) const;
};

#endif

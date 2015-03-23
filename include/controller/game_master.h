//TITLE: GAME_MASTER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: control the IA and in-game stuff (spawning,movement etc..)

#ifndef GAME_MASTER
#define GAME_MASTER

#include "game_objects.h"
#include "player.h"
#include "tilemap.h"
#include "enemy_set.h"
#include <stack>
#include <functional>

typedef std::stack<std::pair<unsigned int,string> > spawn_wave; //defines a enemy wave
const double enemies_spawn_delay=1; //speed between spawning (seconds)
const unsigned int check_towers_atk_delay=1; //delay (in frames) between checks of tower attacks (costly operation to do each frame)
const string spawner_xml_value="Spawn";
//information about spawning enemies
class game_spawner {
private:
    vector<spawn_wave> waves;//waves of the game_spawner
    unsigned int delay; //delay between waves, in seconds
public:
    //CONSTRUCTORS
    //default constructor
    game_spawner();
    //full constructor
    game_spawner(const vector<spawn_wave> &waves,unsigned int delay);
    //constructor from one wave
    game_spawner(const spawn_wave &wave,unsigned int delay);
    //constructor from xml element
    game_spawner(const XMLElement *spawner_root);
    //DESTRUCTOR
    ~game_spawner();
    //METHODS
    //reads xml from element
    bool read_xml(const XMLElement *spawner_root);
    //reads xml from file
    bool read_xml(const string &filename);
    //adds a new wave
    void add_wave(spawn_wave wave);
    //clear all spawning info
    void clear();
    //returns wave delay
    unsigned int get_delay() const;
    //return number of waves
    unsigned int get_total_waves() const;
    //return wave with given number
    const spawn_wave &get_wave(unsigned int wave_number) const;
    //checks struct
    bool check() const;
};


class game_master {
private:
    game_spawner spawner; //game spawner
    spawn_wave left; //left enemies of the current wave
    enemy_set *enemies; //game enemy set
    game_objects *objects; //game enemy objects
    const tilemap *game_map; //game map
    player *game_player; //game player
    unsigned int current_wave; //number of current wave

    unsigned int spawn_delay; //in frames
    unsigned int wave_delay; //in frames

    unsigned int tower_atk_counter; //count for next update_tower_attacks
    unsigned int wave_delay_counter; //count for next wave
    unsigned int spawn_delay_counter; //count for next enemy spawn

    function<void()> win_function; //function when win, with enemies killed and parameter

    bool active;
public:
    //CONTRUCTORS
    //default constructor
    game_master();
    //full constructor
    game_master(enemy_set &enemies,game_objects &objects,const tilemap &game_map,player &game_player,const game_spawner &spawner,const ALLEGRO_TIMER *timer,function<void()> win_function);
    //DESTRUCTOR
    ~game_master();
    //METHODS
    //return number of current wave
    unsigned int get_current_wave() const;
    //return number of total waves
    unsigned int get_total_waves() const;
    //return true if active
    bool is_active() const;
    //set active or not
    void set_active(bool active);
    //updates enemies/attacks (if active)
    void update();
    //check class
    bool check() const;
private:
    //update all tower attacks of towers with given ids
    void update_tower_attacks(vector<tower_id> &towers);
    //updates all enemy positions (of the neemy list)
    void update_enemy_position(const vector<list<enemy>::iterator> &enemy_list);
    //spawn a wave (set it to left)
    void spawn(const spawn_wave &wave);
    //spawn one enemy in a random spawn-place in map
    void spawn();
    //set delays according to given timer
    void set_delays(const ALLEGRO_TIMER *timer);
    //will be called when all enemies are dead, and will call the callback win_function
    void game_over();
};
#endif

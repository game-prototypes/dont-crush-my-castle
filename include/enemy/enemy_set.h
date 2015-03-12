//TITLE: ENEMY_SET_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#ifndef ENEMY_SET
#define ENEMY_SET

#include "enemy.h"

class enemy_set {
private:
    string name; //name of the set
    map<string,enemy_attributes> enemies; //the first string is the name of the enemy_attributes
    const ALLEGRO_TIMER *timer; //timer to be used
public:
    //CONSTRUCTORS
    enemy_set();
    enemy_set(const string &name,const ALLEGRO_TIMER *timer);
    enemy_set(const string &name,const vector<enemy_attributes> &enemy_list,const ALLEGRO_TIMER *timer);
    enemy_set(const string &name,const enemy_attributes &enemy_list,const ALLEGRO_TIMER *timer);
    ~enemy_set();

    //MODIFICATION
    void set_name(const string &name);
    void add_enemy(const enemy_attributes &info);
    void set_timer(const ALLEGRO_TIMER *timer);
    void remove_enemy(const string &name);
    //clear all the enemies and info without destroyin anything
    void clear();
    //CONSULT
    string get_name() const;
    unsigned int size() const;
    bool empty() const;
    bool is_enemy(const string &name) const;

    enemy spawn_enemy(const string &name,unsigned int level,double posx,double posy);//return new enemy spawned
    bool check() const;
};

#endif

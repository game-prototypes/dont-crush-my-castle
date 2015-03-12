//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: stores a set of towers

#ifndef TOWER_SET_H
#define TOWER_SET_H

#include "tower.h"
#include <map>
#include <set>

class tower_set {
private:
    string name; //name of the set
    map<string,tower_attributes> towers; //the first string is the name of the tower_attributes
    const ALLEGRO_TIMER *timer; //timer to be used when spawning
public:
    //CONSTRUCTORS
    tower_set();
    tower_set(const string &name,const ALLEGRO_TIMER *timer);
    tower_set(const string &name,const vector<tower_attributes> &tower_list,const ALLEGRO_TIMER *timer);
    tower_set(const string &name,const tower_attributes &tower_attr,const ALLEGRO_TIMER *timer);
    ~tower_set();

    //MODIFICATION
    void set_name(const string &name);
    void add_tower(const tower_attributes &info);
    void set_timer(const ALLEGRO_TIMER *timer);
    void remove_tower(const string &name);
    void clear();
    //CONSULT
    string get_name() const;
    unsigned int size() const;
    bool empty() const;
    bool is_tower(const string &name) const;
    set<string> get_towers_names() const;
    unsigned int get_tower_cost(const string &name) const;

    tower spawn_tower(const string &name,double posx,double posy) const;//return new tower spawned
    bool check() const;
};


#endif
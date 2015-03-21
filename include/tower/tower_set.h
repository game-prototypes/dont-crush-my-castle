//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: stores a set of towers

#ifndef TOWER_SET_H
#define TOWER_SET_H

#include "tower.h"
#include <map>
#include <set>

const string tower_set_xml_value="Tower_Set";
class tower_set {
private:
    string name; //name of the set
    map<string,tower_attributes> towers; //the first string is the name of the tower_attributes
    const ALLEGRO_TIMER *timer; //timer to be used when spawning
public:
    //CONSTRUCTORS
    //default constructor
    tower_set();
    //constructor from xml element
    tower_set(const XMLElement *tower_set_root,const ALLEGRO_TIMER *timer);
    //constructor from name
    tower_set(const string &name,const ALLEGRO_TIMER *timer);
    //full constructor
    tower_set(const string &name,const vector<tower_attributes> &tower_list,const ALLEGRO_TIMER *timer);
    //constructor with one tower
    tower_set(const string &name,const tower_attributes &tower_attr,const ALLEGRO_TIMER *timer);
    //DESTRUCTOR
    ~tower_set();
    //reads xml from element
    bool read_xml(const XMLElement *tower_set_root,const ALLEGRO_TIMER *timer);
    //reads from xml file
    bool read_xml(const string &filename,const ALLEGRO_TIMER *timer);
    //METHODS
    //sets the name
    void set_name(const string &name);
    //adds new tower
    void add_tower(const tower_attributes &info);
    //sets timer
    void set_timer(const ALLEGRO_TIMER *timer);
    //removes tower with given name
    void remove_tower(const string &name);
    //clear all info and towers
    void clear();
    //returns set name
    string get_name() const;
    //returns set size (number of towers)
    unsigned int size() const;
    //return true if set is empty
    bool empty() const;
    //return tower if there is a tower with given name
    bool is_tower(const string &name) const;
    //returns all the towers names in am ordered set
    set<string> get_towers_names() const;
    //returns the cost of the tower with given name
    unsigned int get_tower_cost(const string &name) const;
    //returns an instance of a tower, spawned in given postition
    tower spawn_tower(const string &name,double posx,double posy) const;//return new tower spawned
    //checks class
    bool check() const;
};
#endif

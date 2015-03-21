//TITLE: ENEMY_SET_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#ifndef ENEMY_SET
#define ENEMY_SET

#include "enemy.h"
const string enemy_set_xml_value="Enemy_Set";
class enemy_set {
private:
    string name; //name of the set
    map<string,enemy_attributes> enemies; //the first string is the name of the enemy_attributes
    const ALLEGRO_TIMER *timer; //timer to be used
public:
    //CONSTRUCTORS
    enemy_set();
    enemy_set(const XMLElement *enemy_set_root,const ALLEGRO_TIMER *timer);
    enemy_set(const string &name,const ALLEGRO_TIMER *timer);
    enemy_set(const string &name,const vector<enemy_attributes> &enemy_list,const ALLEGRO_TIMER *timer);
    enemy_set(const string &name,const enemy_attributes &enemy_list,const ALLEGRO_TIMER *timer);
    //DESTRUCTOR
    ~enemy_set();
    //METHODS
    //reads from xml element
    bool read_xml(const XMLElement *enemy_set_root,const ALLEGRO_TIMER *timer);
    //reads from xml file
    bool read_xml(const string &filename,const ALLEGRO_TIMER *timer);
    //MODIFICATION
    //sets enemy_set name
    void set_name(const string &name);
    //adds a new enemy to the set
    void add_enemy(const enemy_attributes &info);
    //sets timer
    void set_timer(const ALLEGRO_TIMER *timer);
    //remove enemy with given name from set
    void remove_enemy(const string &name);
    //clear all the enemies and info without destroyin anything
    void clear();
    //CONSULT
    //returns set name
    string get_name() const;
    //returns set size (number of enemies)
    unsigned int size() const;
    //return true if set is empty
    bool empty() const;
    //return true if there is an enemy with give nname in the set
    bool is_enemy(const string &name) const;
    //returns a new enemy instance (spawned) from the attributes with given name
    //enemy will be spawned at given level and positon
    enemy spawn_enemy(const string &name,unsigned int level,double posx,double posy);//return new enemy spawned
    //checks the class
    bool check() const;
};

#endif

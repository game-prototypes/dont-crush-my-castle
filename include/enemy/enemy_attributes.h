//TITLE: ENEMY_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: defines each kind of enemy
#ifndef ENEMY_ATTRIBUTES
#define ENEMY_ATTRIBUTES

#include "al_anim.h"
#include <map>

const string enemy_xml_value="Enemy";
enum enemy_animation {idle_anim,up_anim,down_anim,left_anim,right_anim,dead_anim}; //defines each animation for an enemy
//defines the basic characteristics of an enemy kind
struct enemy_attributes {
    map<enemy_animation,al_anim> animation; //stores all animations of an enemy
    string name; //name of the enemy
    double speed; //basic speed (pixels per seconds)
    unsigned int max_life; //max (and initial) life of enemy
    unsigned int armor; //armor of the enemy
    unsigned int reward; //reward when killed
    //CONSTRUCTORS
    //default constructor
    enemy_attributes();
    //constructor from xml element
    enemy_attributes(XMLElement *enemy_root,const ALLEGRO_TIMER *timer);
    //full constructor without animations
    enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,unsigned int reward=0);
    //full constructor with animations
    enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const map<enemy_animation,al_anim> &animation,unsigned int reward=0);
    //DESTRUCTOR
    ~enemy_attributes();
    //METHODS
    //reads xml element
    bool read_xml(const XMLElement *enemy_root,const ALLEGRO_TIMER *timer);
    //reads from xml file (with enemy xml element as root)
    bool read_xml(const string &filename,const ALLEGRO_TIMER *timer);

    //insert animation (erasing previous animations and reseting all counters)
    void insert_animation(enemy_animation type,const al_anim &anim);
    //clear all attributes (dont destroy bitmaps)
    void clear();
    //destroy all animations and clear data
    void destroy();
    //returns true if the enemy has all the necessary info
    bool check() const;
};
#endif

//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: defines the attack of buildings
#ifndef TOWER_ATK_H
#define TOWER_ATK_H

#include "al_anim.h"

enum atk_type {shoot_atk,explosion_atk,continuous_atk};

//defines the atributes of an attack
struct atk_attributes {
    ALLEGRO_BITMAP *bitmap; //attack bitmap
    al_anim collision_anim; //collision animation (explosion) or continuous
    unsigned int damage; //damage of the attack
    unsigned int range; //range of damage in pixels
    double delay; //delay (in seconds) between attacks (except continuous)
    atk_type type;
    double speed; //speed of attack (in pixels/second)
    //string name ¿?
    //METHODS
    atk_attributes();
    atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,double speed,atk_type type=shoot_atk);
    ~atk_attributes();
    //clear data (dont destroy animations)
    void clear();
    //destroy all bitmaps and clear data
    void destroy();
    bool check() const;
};

//defines an instance of attack
class tower_atk {
private:
    atk_attributes attributes;
    pair<double,double> position; //actual position
    pair<double,double> destiny; //position to move
    double speed; //speed (pixels per frame)
    bool collide; //true if the attack reached destiny
    bool valid; //true if attack is valid (enemy alive)
    bool active;
public:
    //default constructor
    tower_atk();
    //full constructor
    tower_atk(const atk_attributes &attributes,pair<double,double> position,pair<double,double> destiny,const ALLEGRO_TIMER *timer);
    //destroyed (dont destroy animation or bitmap!!)
    ~tower_atk();
    //invalidates attack
    void invalidate();
    //return atk damage
    unsigned int get_damage() const;
    //returns speed in pixels per second
    double get_speed() const;
    //return range of attack
    unsigned int get_range() const;
    //returns attack position
    pair<double,double> get_position() const;
    //returns attack type
    atk_type get_type() const;
    //return true if active
    bool is_active() const;
    //return true if valid
    bool is_valid() const;
    //return true after collision
    bool hit() const;
    //updates the attack,updating its position and colliding if necessary
    void update();
    //draws the attack
    void draw() const;
    //check class, return false if problem
    bool check() const;
private:
    //when attack hit, starts collision, and damage enemy (if still available)
    void collision();
    //set speed (pixels per second), need timer wich will be used
    void set_speed(const ALLEGRO_TIMER *timer);
};
#endif

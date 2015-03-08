//TITLE: TOWER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines each player tower

#ifndef TOWER_H
#define TOWER_H

#include "tower_attributes.h"

class tower : public game_object {
private:
    const tower_attributes *attributes;
    unsigned int atk_counter; //time to next attack (depending on delay) in frames
    unsigned int atk_delay; //atk delay (in frames)
    //change atk_delay to unsigned int (count as frames)
    const ALLEGRO_TIMER *timer; //timer of the tower and attacks

public:
    tower();
    //full constructor
    tower(const tower_attributes &attributes,double posx,double posy,const ALLEGRO_TIMER *timer);
    ~tower();
    //returns tower name
    string get_name() const;
    //return tower range in pixels
    unsigned int get_range()const;
    //return tower damage
    unsigned int get_damage()const;
    //return cost of the tower
    unsigned int get_cost() const;
    //return attack type
    atk_type get_attack_type()const;
    //return true if given position is in range of attack
    bool in_range(pair<double,double> target) const;
    //return true if tower can attack (counter=0)
    bool can_attack()const;
    //update tower
    void virtual update();
    //draw tower
    void virtual draw() const;
    //attacks an enemy (atk destiny will be that enemy), return the attack
    tower_atk attack(const pair<double,double> target);
    bool check() const;
private:
    void set_delay();
    void reset_counter();
};


#endif

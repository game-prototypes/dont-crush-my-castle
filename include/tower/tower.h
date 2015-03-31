//TITLE: TOWER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: defines each player tower

#ifndef TOWER_H
#define TOWER_H

#include "tower_attributes.h"

class tower : public game_object {
private:
    const tower_attributes *attributes;//tower attributes
    unsigned int atk_counter; //time to next attack (depending on delay) in frames
    unsigned int atk_delay; //atk delay (in frames)
    const ALLEGRO_TIMER *timer; //timer of the tower and attacks
public:
    //CONSTRUCTORS
    //default contructor
    tower();
    //full constructor
    tower(const tower_attributes &attributes,double posx,double posy,const ALLEGRO_TIMER *timer);
    //DESTRUCTOR
    ~tower();
    //METHODS
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
    void update();
    //draw tower
    void draw() const;
    //attacks an enemy (atk destiny will be that enemy), return the attack
    tower_atk attack(const pair<double,double> target);
    //checks class
    bool check() const;
private:
    //sets delay (changing from seconds to frames according to timer)
    void set_delay();
    //resets atk counter back to the delay value
    void reset_counter();
};


#endif

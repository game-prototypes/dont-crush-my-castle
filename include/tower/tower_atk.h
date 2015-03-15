//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines the attack of buildings
#ifndef TOWER_ATK
#define TOWER_ATK

#include "tower_atk_attributes.h"
#include "game_object.h"

//defines an instance of attack
class tower_atk : public game_object {
private:
    al_anim collision_anim;
    const atk_attributes *attributes;
    pair<double,double> destiny; //position to move
    double speed; //speed (pixels per frame)
    double rotation;
    bool collide; //true if the attack reached destiny
    bool valid; //true if attack is valid (enemy alive)
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
    //returns attack type
    atk_type get_type() const;
    //return true if valid
    bool is_valid() const;
    //return true after collision
    bool hit() const;
    //updates the attack,updating its position and colliding if necessary
    void virtual update();
    //draws the attack
    void virtual draw() const;
    //check class, return false if problem
    bool check() const;
private:
    //when attack hit, starts collision, and damage enemy (if still available)
    void collision();
    //set speed (pixels per second), need timer wich will be used
    void set_speed(const ALLEGRO_TIMER *timer);
    void set_rotation();
};
#endif

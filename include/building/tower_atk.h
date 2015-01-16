//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines the attack of buildings
#ifndef TOWER_ATK_H
#define TOWER_ATK_H

#include "al_anim.h"

enum atk_type {shoot_atk,explosion_atk,continuous_atk};
double atk_speed=1; //base attack speed (pixels by frame) (may vary depending on attack type)
//defines the atributes of an attack
struct atk_attributes {
    ALLEGRO_BITMAP *bitmap; //attack bitmap
    al_anim collision_anim; //collision animation (explosion) or continuous
    unsigned int damage; //damage of the attack
    unsigned int range; //range of damage in pixels (0= one enemy dage)
    double delay; //delay (in seconds) between attacks (except continuous)
    atk_type type;

    //METHODS
    atk_attributes();
    atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,atk_type type);
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
    bool collide; //true if the attack reached destiny
    bool active;
public:
    //default constructor
    tower_atk();
    //full constructor
    tower_atk(const atk_attributes &attributes,pair<double,double> position,pair<double,double> destiny);

    //return atk damage
    unsigned int get_damage() const;
    //return true if active
    bool is_active() const;
    //return true after collision
    bool hit() const;
    //updates the attack,updating its position and colliding if necessary
    void update();
    //draws the attack
    void draw();

private:
    //when attack hit, starts collision, and damage enemy (if still available)
    void collision();
    //check class is working properly
    void check() const;

};
#endif

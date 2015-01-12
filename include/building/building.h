//TITLE: BUILDING_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines each player building

#ifndef BUILDING_H
#define BUILDING_H

#include "tower_atk.h"


//defines the attributes of the building
struct building_attributes {
    ALLEGRO_BITMAP *bitmap; //main bitmap of the buildings (static)
    //	ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    atk_attributes atk; //attack attributes

    //METHODS
    building_attributes(ALLEGRO_BITMAP *bitmap,atk_attributes atk);
    //return bitmap width (in pixels)
    unsigned int get_width() const;
    //returns bitmap height (in pixels)
    unsigned int get_height() const;
    //resize bitmap (overriding old) to given size
    void resize(unsigned int width,unsigned int height);
    //destroy building attributes (including bitmaps and attack attribute)
    void destroy();

};

class building {
private:
    building_attributes attributes;
    pair<double,double> position; //building position (centered)
    double atk_counter; //time to next attack (depending on delay) in frames
    double atk_delay; //atk delay (in frames)
    bool active;

public:
    building();
    //full constructor
    building(building_attributes attribute,double posx,double posy,const ALLEGRO_TIMER *timer);

    //deactivates the tower drawing/updating
    void deactivate();

    //return true if active
    bool is_active() const;
    //return tower position (in pixels)
    pair<double,double> get_position()const;
    //return tower range in pixels
    unsigned int get_range()const;
    //return tower damage
    unsigned int get_damage()const;
    //return attack type
    attack_type get_attack_type()const;
    //return true if given position is in range of attack
    bool in_range(pair<double,double> objective) const;
    bool can_attack()const;
    //update building
    void update();
    //draw building
    void draw() const;
    //attacks an enemy (atk destiny will be that enemy), return the attack
    tower_atk attack(const enemy &enem) const;

private:
    void reset_counter();
    void check() const;

};


#endif

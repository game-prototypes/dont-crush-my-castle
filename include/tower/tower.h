//TITLE: TOWER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines each player tower

#ifndef TOWER_H
#define TOWER_H

#include "tower_atk.h"


//defines the attributes of the tower
struct tower_attributes {
    ALLEGRO_BITMAP *bitmap; //main bitmap of the towers (static)
    //	ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    atk_attributes atk; //attack attributes

    //METHODS
    tower_attributes();
    tower_attributes(ALLEGRO_BITMAP *bitmap,atk_attributes atk);
    //return bitmap width (in pixels)
    unsigned int get_width() const;
    //returns bitmap height (in pixels)
    unsigned int get_height() const;
    //resize bitmap (overriding old) to given size
    void resize(unsigned int width,unsigned int height);
    //destroy tower attributes (including bitmaps and attack attribute)
    void destroy();

};

class tower {
private:
    tower_attributes attributes;
    pair<double,double> position; //tower position (centered)
    double atk_counter; //time to next attack (depending on delay) in frames
    double atk_delay; //atk delay (in frames)
    bool active;

public:
    tower();
    //full constructor
    tower(tower_attributes attribute,double posx,double posy,const ALLEGRO_TIMER *timer);

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
    atk_type get_attack_type()const;
    //return true if given position is in range of attack
    bool in_range(pair<double,double> objective) const;
    bool can_attack()const;
    //update tower
    void update();
    //draw tower
    void draw() const;
    //attacks an enemy (atk destiny will be that enemy), return the attack
    tower_atk attack(const pair<double,double> target);

private:
    void reset_counter();
    bool check() const;

};


#endif

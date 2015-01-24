//TITLE: TOWER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.4
//DESCRIPTION: defines each player tower

#ifndef TOWER_H
#define TOWER_H

#include "tower_atk.h"


//defines the attributes of the tower
struct tower_attributes {
    atk_attributes atk; //attack attributes
    ALLEGRO_BITMAP *bitmap; //main bitmap of the towers (static)
    //	ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    unsigned int cost;
    string name;
    //METHODS
    tower_attributes();
    tower_attributes(const string &name,ALLEGRO_BITMAP *bitmap,const atk_attributes &atk,unsigned int cost);
    ~tower_attributes();
    //return bitmap width (in pixels)
    unsigned int get_width() const;
    //returns bitmap height (in pixels)
    unsigned int get_height() const;
    //resize bitmap (overriding old) to given size
    void resize(unsigned int width,unsigned int height);
    bool check() const;
    //destroy tower attributes (including bitmaps and attack attribute)
    void destroy();

};

class tower {
private:
    tower_attributes attributes;
    pair<double,double> position; //tower position (centered)  //¿Maybe use foot as in enemy?
    unsigned int atk_counter; //time to next attack (depending on delay) in frames
    unsigned int atk_delay; //atk delay (in frames)
    //change atk_delay to unsigned int (count as frames)
    bool active;
    const ALLEGRO_TIMER *timer; //timer of the tower and attacks

public:
    tower();
    //full constructor
    tower(const tower_attributes &attributes,double posx,double posy,const ALLEGRO_TIMER *timer);
    //deactivates the tower updating
    void deactivate();
    //return true if active
    bool is_active() const;
    //returns tower name
    string get_name() const;
    //return tower position (in pixels)
    pair<double,double> get_position()const;
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
    bool check() const;
private:
    void set_delay();
    void reset_counter();
};


#endif

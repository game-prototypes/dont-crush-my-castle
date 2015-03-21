//TITLE: TOWER_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: defines each kind of tower

#ifndef TOWER_ATTRIBUTES_H
#define TOWER_ATTRIBUTES_H

#include "tower_atk.h"
const string tower_xml_value="Tower";
//defines the attributes of the tower
struct tower_attributes {
    string name;
    atk_attributes atk; //attack attributes
    ALLEGRO_BITMAP *bitmap; //main bitmap of the towers (static)
    unsigned int cost; //cost of the tower
    //ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    //CONSTRUCTORS
    //default constructor
    tower_attributes();
    //constructor from xml element
    tower_attributes(const XMLElement *tower_root,const ALLEGRO_TIMER *timer);
    //full constructor
    tower_attributes(const string &name,ALLEGRO_BITMAP *bitmap,const atk_attributes &atk,unsigned int cost);
    //DESTUCTOR
    ~tower_attributes();
    //METHODS
    //reads from xml element
    bool read_xml(const XMLElement *tower_root,const ALLEGRO_TIMER *timer);
    //reads from xml file
    bool read_xml(const string &filename,const ALLEGRO_TIMER *timer);
    //return bitmap width (in pixels)
    unsigned int get_width() const;
    //returns bitmap height (in pixels)
    unsigned int get_height() const;
    //resize bitmap (overriding old) to given size
    void resize(unsigned int width,unsigned int height);
    //destroy tower attributes (including bitmaps and attack attribute)
    void destroy();
    //check class
    bool check() const;
};


#endif

//TITLE: TOWER_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
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
    unsigned int cost;
    //ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    //METHODS
    tower_attributes();
    tower_attributes(const XMLElement *tower_root,const ALLEGRO_TIMER *timer);
    tower_attributes(const string &name,ALLEGRO_BITMAP *bitmap,const atk_attributes &atk,unsigned int cost);
    ~tower_attributes();

    bool read_xml(const XMLElement *tower_root,const ALLEGRO_TIMER *timer);
    bool read_xml(const string &filename,const ALLEGRO_TIMER *timer);
    //    bool write_xml(XMLElement *attributes_root) const;

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


#endif

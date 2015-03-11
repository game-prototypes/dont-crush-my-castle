//TITLE: TOWER_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines each kind of tower

#ifndef TOWER_ATTRIBUTES_H
#define TOWER_ATTRIBUTES_H

#include "tower_atk.h"

//defines the attributes of the tower
struct tower_attributes : game_object_attributes {
    atk_attributes atk; //attack attributes
    ALLEGRO_BITMAP *bitmap; //main bitmap of the towers (static)
    //	ALLEGRO_BITMAP *secondary_bitmap; //secondary bitmap (rotate)
    unsigned int cost;
    string name;
    //METHODS
    tower_attributes();
    tower_attributes(const XMLElement *attributes_root);
    tower_attributes(const string &name,ALLEGRO_BITMAP *bitmap,const atk_attributes &atk,unsigned int cost);
    ~tower_attributes();

    bool read_xml(const XMLElement *attributes_root);
    bool write_xml(XMLElement *attributes_root) const;

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

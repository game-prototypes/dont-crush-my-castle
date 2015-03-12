//TITLE: GAME_OBJECT_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines a generic object attributes as a base class

#ifndef GAME_OBJECT_ATTRIBUTES
#define GAME_OBJECT_ATTRIBUTES

#include "tinyxml2.h"
#include <string>
using namespace tinyxml2;
using namespace std;

struct game_object_attributes {
    bool virtual read_xml(const XMLElement *attributes_root)=0;
    //    bool virtual write_xml(XMLElement *attributes_root) const=0;
    void virtual destroy()=0;
    bool virtual check() const;
};
#endif

//TITLE: TOWER_ATK_ATTRIBUTES_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines the kind of attack of buildings

#include "tower_atk_attributes.h"

atk_attributes::atk_attributes() {
    damage=range=delay=speed=0;
    type=shoot_atk;
}
atk_attributes::atk_attributes(const XMLElement *attributes_root) {
    if(!read_xml(attributes_root)) destroy();
}
atk_attributes::atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,double speed,atk_type type) {
    this->bitmap=bitmap;
    this->collision_anim=collision_anim;
    this->damage=damage;
    this->range=range;
    this->delay=delay;
    this->type=type;
    this->speed=speed;
}
atk_attributes::~atk_attributes() {
}
bool atk_attributes::read_xml(const XMLElement *attributes_root) {
    bool b=false;
    //TODO
    return b;
}
bool atk_attributes::write_xml(XMLElement *attributes_root) const {
    bool b=false;
    //TODO
    return b;
}
void atk_attributes::clear() {
    damage=range=delay=0;
    type=shoot_atk;
    collision_anim.clear();
    bitmap=NULL;
}
void atk_attributes::destroy() {
    al_destroy_bitmap(bitmap);
    bitmap=NULL;
    collision_anim.destroy();
    clear();
}
bool atk_attributes::check() const {
    bool b=true;
    if(delay==0 && type!=continuous_atk) {
        debug_log::report("attack delay equals 0",warning,true,false,false);
        b=false;
    }
    if(range==0) {
        debug_log::report("attack range equals 0",warning,true,false,false);
        b=false;
    }
    if(damage==0) {
        debug_log::report("attack damage equals 0",warning,true,false,false);
        b=false;
    }
    if(bitmap==NULL) b=false;
    if(speed<=0 || delay<=0) b=false;
    if(collision_anim.check()==false) b=false;
    return b;
}

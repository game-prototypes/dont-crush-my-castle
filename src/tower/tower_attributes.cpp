//TITLE: TOWER_ATTRIBUTES_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines each kind of tower


#include "tower_attributes.h"
tower_attributes::tower_attributes() {
}
tower_attributes::tower_attributes(const string &name,ALLEGRO_BITMAP *bitmap,const atk_attributes &atk,unsigned int cost) {
    this->bitmap=bitmap;
    this->atk=atk;
    this->name=name;
    this->cost=cost;
}
tower_attributes::~tower_attributes() {
}
unsigned int tower_attributes::get_width() const {
    return al_get_bitmap_width(bitmap);
}
unsigned int tower_attributes::get_height() const {
    return al_get_bitmap_height(bitmap);
}
//resize bitmap (overriding old) to given size
void tower_attributes::resize(unsigned int width,unsigned int height) {
    resize_bitmap(bitmap,width,height);
}
bool tower_attributes::check() const {
    bool b=true;
    if(bitmap==NULL) b=false;
    if(atk.check()==false) b=false;
    if(name.empty()==true) b=false;
    return b;
}
//destroy tower attributes (including bitmaps and attack attribute)
void tower_attributes::destroy() {
    //animation.destroy();
    al_destroy_bitmap(bitmap);
    bitmap=NULL;
    atk.destroy();
}
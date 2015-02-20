//TITLE: tower_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: defines an user tower

#include "tower.h"
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
    atk.destroy();
}
//TOWER

tower::tower() {
    atk_counter=0;
    position=make_pair(-1,-1);
    atk_delay=0;
    active=false;
}
tower::tower(const tower_attributes &attributes,double posx,double posy,const ALLEGRO_TIMER *timer) {
    this->attributes=attributes;
    this->position=make_pair(posx,posy);
    this->timer=timer;
    set_delay();
    reset_counter();
    active=true;
}
tower::~tower() {
}
void tower::deactivate() {
    active=false;
}
bool tower::is_active() const {
    return active;
}
string tower::get_name() const {
    return attributes.name;
}
pair<double,double> tower::get_position()const {
    return position;
}
unsigned int tower::get_range()const {
    return attributes.atk.range;
}
unsigned int tower::get_damage() const {
    return attributes.atk.damage;
}
unsigned int tower::get_cost() const {
    return attributes.cost;
}
atk_type tower::get_attack_type() const {
    return attributes.atk.type;
}
bool tower::in_range(pair<double,double> target) const {
    double rad=attributes.atk.range;
    double x=target.first-position.first;
    double y=target.second-position.second;
    return (x*x+y*y)<=(rad*rad);
}
bool tower::can_attack() const {
    return atk_counter==0;
}
void tower::update() {
    if(active) {
        if(atk_counter>0) atk_counter--;
    }
}
void tower::draw() const {
    unsigned int hoffset=get_bitmap_height(attributes.bitmap)/2;
    draw_centered(attributes.bitmap,position.first,position.second-hoffset);
}

tower_atk tower::attack(const pair<double,double> target) {
    if(atk_counter>0) debug_log::report("tower attack before counter reach 0",warning,true,false,false);
    if(in_range(target)==false) debug_log::report("tower attack out of range",warning,true,false,false);
    reset_counter();
    unsigned int hoffset=get_bitmap_height(attributes.bitmap)/3;
    pair<double,double> pos=position;
    pos.second-=hoffset*2;
    return tower_atk(attributes.atk,pos,target,timer);
}
bool tower::check() const {
    bool b=true;
    if(attributes.check()==false) b=false;
    if(atk_delay==0) b=false;
    return b;
}
//PRIVATE
void tower::set_delay() {
    atk_delay=get_frames(attributes.atk.delay,timer);
}
void tower::reset_counter() {
    atk_counter=atk_delay;
}


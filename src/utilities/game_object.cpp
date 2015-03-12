//TITLE: GAME_OBJECT_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: defines a generic gameobject
#include "game_object.h"

game_object::game_object() {
    set_position(-1,-1);
    active=false;
}
game_object::game_object(pair<double,double> position) {
    set_position(position);
    active=false;
}
game_object::~game_object() {
    active=false;
}
void game_object::activate() {
    active=true;
}
void game_object::deactivate() {
    active=false;
}
void game_object::set_active(bool active) {
    this->active=active;
}
bool game_object::is_active() const {
    return active;
}
void game_object::set_position(double x,double y) {
    position.first=x;
    position.second=y;
}
void game_object::set_position(pair<double,double> position) {
    this->position=position;
}
pair<double,double> game_object::get_position() const {
    return position;
}
bool game_object::check() const {
    bool b=true;
    return b;
}
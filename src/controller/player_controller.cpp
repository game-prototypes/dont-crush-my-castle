//TITLE: PLAYER_CONTROLLER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: controls the actions of the player

#include "player_controller.h"

//CONSTRUCTORS
player_controller::player_controller() {
}
player_controller::player_controller(tower_set &towers,game_objects &objects,tilemap &game_map) {
    this->towers=&towers;
    this->objects=&objects;
    this->game_map=&game_map;
}
player_controller::~player_controller() {
    built_towers.clear();
}
unsigned int player_controller::get_towers_size() const {
    return towers->size();
}
set<string> player_controller::get_tower_names() const {
    return towers->get_towers_names();
}
unsigned int player_controller::get_tower_cost(const string &name) const {
    return towers->get_tower_cost(name);
}
unsigned int player_controller::spawned_towers() const {
    return objects->tower_size();
}
bool player_controller::can_build(double x,double y) const {
    pair<unsigned int,unsigned int> p=translate_position(x,y);
    return game_map->can_build(p.first,p.second);
    // game_map->check_path_if_build(p.first,p.second);
    //if may build on open_ground
}
bool player_controller::build_tower(const string &name,double x,double y) {
    bool b;
    if(can_build(x,y)==false || towers->is_tower(name)==false) b=false;
    else {
        pair<unsigned int,unsigned int> p=translate_position(x,y);
        pair<double,double> p2=translate_position(p.first,p.second);
        unsigned int siz=game_map->get_tile_size();
        p2.second+=siz/2; //posiiton of tower is the foot of the tile
        game_map->occupy_tile(p.first,p.second);
        tower_id tid=objects->add_tower(towers->spawn_tower(name,p2.first,p2.second));
        built_towers.insert(make_pair(p,tid));
        b=true;
    }
    return b;
}
bool player_controller::remove_tower(double x,double y) {
    pair<unsigned int,unsigned int> p=translate_position(x,y);
    map<pair<unsigned int,unsigned int>,tower_id>::iterator it;
    it=built_towers.find(p);
    if(it!=built_towers.end()) {
        tower_id id=it->second;
        objects->remove_tower(id);
        built_towers.erase(it);
        game_map->free_tile(p.first,p.second);
        return true;
    }
    else return false;
}
bool player_controller::is_tower(double x,double y) const {
    pair<unsigned int,unsigned int> p=translate_position(x,y);
    if(built_towers.find(p)==built_towers.end()) return false;
    else return true;
}
/*tower *player_controller::get_tower(double x,double y) {
    return objects->get_tower(get_tower_id(x,y));
}*/
const tower *player_controller::get_tower(double x,double y) const {
    return objects->get_tower(get_tower_id(x,y));
}
bool player_controller::check() const {
    bool b=true;
    if(built_towers.size()!=objects->tower_size()) b=false;
    if(objects==NULL || game_map==NULL) b=false;
    return b;
}
tower_id player_controller::get_tower_id(double x,double y) const {
    tower_id id=0;
    pair<unsigned int,unsigned int> p=translate_position(x,y);
    map<pair<unsigned int,unsigned int>,tower_id>::const_iterator it;
    it=built_towers.find(p);
    if(it!=built_towers.end()) id=it->second;
    return id;
}
pair<unsigned int,unsigned int> player_controller::translate_position(double x,double y) const {
    return game_map->translate_position(x,y);
}
pair<double,double> player_controller::translate_position(unsigned int x,unsigned int y) const {
    return game_map->translate_position(x,y);
}

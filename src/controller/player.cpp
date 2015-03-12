//TITLE: PLAYER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: Player information

#include "player.h"

//CONSTRUCTORS
player::player() {
    active=false;
    coins=lives=0;
}
player::player(const string &name,tower_set &towers,game_objects &objects,tilemap &game_map,unsigned int lives,unsigned int coins,function<void()> lose_function) {
    this->name=name;
    this->controller=player_controller(towers,objects,game_map);
    this->lives=lives;
    this->coins=coins;
    this->lose_function=lose_function;
    this->active=true;
    set_current_tower(*(get_tower_names().begin()));
}
player::player(tower_set &towers,game_objects &objects,tilemap &game_map,unsigned int lives,unsigned int coins,function<void()> lose_function) {
    this->controller=player_controller(towers,objects,game_map);
    this->lives=lives;
    this->coins=coins;
    this->lose_function=lose_function;
    this->active=true;
    set_current_tower(*(get_tower_names().begin()));
}

player::~player() {
    this->active=false;
}
//METHODS
//removes given lives
void player::remove_life(unsigned int lives_removes) {
    if(lives_removes>=lives) lives=0;
    else lives-=lives_removes;
    if(lives==0) game_over();
}
void player::recover_life(unsigned int lives_recovered) {
    lives+=lives_recovered;
}
void player::add_coins(unsigned int coins) {
    this->coins+=coins;
}
void player::remove_coins(unsigned int coins) {
    if(coins>=this->coins) this->coins=0;
    else this->coins-=coins;
}
bool player::is_active() const {
    return active;
}
string player::get_name() const {
    return name;
}
unsigned int player::get_coins() const {
    return coins;
}
unsigned int player::get_lives() const {
    return lives;
}
void player::set_current_tower(const string &tower) {
    current_tower=tower;
}
set<string> player::get_tower_names() const {
    return controller.get_tower_names();
}
bool player::check() const {
    bool b=true;
    if(!lose_function) b=false;
    if(controller.check()==false) b=false;
    return b;
}
void player::click_action(int button,unsigned int x,unsigned int y) {
    if(button==1) build_tower(x,y);
    else if(button==2) remove_tower(x,y);
}
void player::key_action(int keycode) {
}
//PRIVATE
void player::build_tower(double x,double y) {
    if(controller.can_build(x,y)) {
        unsigned int tower_cost=controller.get_tower_cost(current_tower);
        if(tower_cost<=coins) {
            coins-=tower_cost;
            controller.build_tower(current_tower,x,y);
        }
    }
}
void player::remove_tower(double x,double y) {
    if(controller.is_tower(x,y)) {
        double gain=0.8*(controller.get_tower(x,y)->get_cost());
        if(gain<1) gain=1;
        coins+=gain;
        controller.remove_tower(x,y);
    }
}

void player::game_over() {
    active=false;
    lose_function();
}
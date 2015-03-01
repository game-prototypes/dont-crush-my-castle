//TITLE: PLAYER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: Player information

#ifndef PLAYER_H
#define PLAYER_H
#include "player_controller.h"
#include "input_handler.h"
class player {
private:
    player_controller controller;
    string name;
    string current_tower;
    unsigned int lives;
    unsigned int coins;
    bool active;
    function<void()> lose_function;
public:
    player();
    player(const string &name,tower_set &towers,game_objects &objects,tilemap &game_map,unsigned int lives,unsigned int coins,function<void()> lose_function);
    player(tower_set &towers,game_objects &objects,tilemap &game_map,unsigned int lives,unsigned int coins,function<void()> lose_function);

    ~player();
    //METHODS
    //removes given lives
    void remove_life(unsigned int lives_removes=1);
    void recover_life(unsigned int lives_recovered=1);
    void add_coins(unsigned int coins);
    void remove_coins(unsigned int coins);

    bool is_active() const;
    string get_name() const;
    unsigned int get_coins() const;
    unsigned int get_lives() const;
    void set_current_tower(const string &tower);
    set<string> get_tower_names() const;

    //player actions
    void click_action(int button,unsigned int x,unsigned int y);
    void key_action(int keycode);

    bool check() const;
private:
    void build_tower(double x,double y);
    void remove_tower(double x,double y);
    void game_over();

};

#endif
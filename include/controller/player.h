//TITLE: PLAYER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: Player information and interface

#ifndef PLAYER_H
#define PLAYER_H
#include "player_controller.h"
#include "input_handler.h"
class player {
private:
    player_controller controller; //this player controller
    string name; //name of the player
    string current_tower; //current tower to build
    unsigned int lives; //lives of player
    unsigned int coins; //coins of player
    bool active; //if player actions are active
    function<void()> lose_function; //callback function for lose
public:
    //CONSTRUCTORS
    //default constructor
    player();
    //full constructor
    player(const string &name,tower_set &towers,game_objects &objects,tilemap &game_map,unsigned int lives,unsigned int coins,function<void()> lose_function);
    //DESTRUCTOR
    ~player();
    //METHODS
    //removes given lives (1 if not specified)
    void remove_life(unsigned int lives_removes=1);
    //recover given lives (1 if not specified)
    void recover_life(unsigned int lives_recovered=1);
    //add given number of coins
    void add_coins(unsigned int coins);
    //removed given number of coins
    void remove_coins(unsigned int coins);
    //return true if player is active
    bool is_active() const;
    //reutrns player name
    string get_name() const;
    //return number of coins
    unsigned int get_coins() const;
    //return number of player lives
    unsigned int get_lives() const;
    //sets the tower to build
    void set_current_tower(const string &tower);
    //returns all the towers names
    set<string> get_tower_names() const;

    //actions of player when clicking in given position
    void click_action(int button,unsigned int x,unsigned int y);
    //actions of player when pressing a key
    void key_action(int keycode);
    //checks class
    bool check() const;
private:
    //builds a tower in given position
    void build_tower(double x,double y);
    //removes tower of given position
    void remove_tower(double x,double y);
    //called when player dies (wil call the callback function )
    void game_over();

};

#endif

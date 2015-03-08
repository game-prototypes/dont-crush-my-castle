//TITLE: ENEMY_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.3
//DESCRIPTION: defines each single enemy

#ifndef ENEMY
#define ENEMY

#include "game_object.h"
#include "enemy_attributes.h"

const double level_ratio=0.3; //ratio used to increase base values per level

class enemy : public game_object {
private:
    const enemy_attributes *attributes; //basic info of enemy type
    map<enemy_animation,al_anim> animation; //stores all animations of an enemy

    unsigned int life; //current life of enemy
    unsigned int level; //level may change enemy parameters
    double speed; //pixels per frame

    pair<double,double> destiny; //position to move

    bool reward_given;

    enemy_animation current_animation;
public:
    //CONSTRUCTORS
    //default constructor (active=false by default)
    enemy();
    //constructor with basic info, enemy life will start with the max_life value
    //constructor with spawning in position given
    enemy(const enemy_attributes &attributes,unsigned int level,double posx,double posy,const ALLEGRO_TIMER *timer);
    ~enemy();
    //set enemy to active in given position
    void spawn(double posx,double posy);

    //CONSULT
    //return enemy name
    string get_name() const;
    //returns enemy_speed (in pixels per second)
    double get_speed() const;
    //return enemy life
    unsigned int get_life() const;
    //returns level
    unsigned int get_level() const;
    //return max life
    unsigned int get_max_life() const;
    //returns reward when killed, also set reward given to true
    unsigned int get_reward();
    //return true if the reward has benn already given
    bool is_reward_given() const;
    //return the enemy destiny (where is moving)
    pair<double,double> get_destiny() const;
    //return true if enemy is alive(life>0)
    bool alive() const;
    //return true if enemy is active
    bool spawned() const;
    //return true if enemy is idle (destiny==position)
    bool idle() const;
    //return current aimation
    enemy_animation get_current_animation() const;
    //ENEMY CONTROL (make sure to call update in each iteration)
    //stop the movement(idle) (final destination will be the current position)
    void stop();
    //set final destination, when reached, set_idle will be called
    void move_to(double x,double y);
    //decrease live and kill if life=0 (this method dont account the armor)
    void decrease_life(unsigned int dam);
    //enemy takes the given damage, decreasing life according to armor
    void damage(unsigned int dam);
    //set life automatically to 0 and live=false, this kills the enemy, starting the animation, but will not destroy the class
    void kill();
    //deactivates enemy and returns lives taken
    unsigned int destiny_reached();
    //update the movement,animation and all booleans
    void virtual update();
    //draw the current_animation in the enemy position
    //note that draw the enemy with the position at its feet
    void virtual draw() const;
    //check enemy class is working well, debug_log output if error or warning, return true if everything is ok
    bool check() const;
    //  pair<double,double> get_position() const;
private:
    //changes to given movement animation
    void change_movement_animation(enemy_animation anim);
    //set animation to idle (stoppping all movement animation and current animation)
    void set_to_idle();
    //stops all movement anim
    void stop_movement_anim();
    //set speed (pixels per second), need timer wich will be used
    void set_speed(double spd,const ALLEGRO_TIMER *timer);
    //set enemy level
    void set_level(unsigned int level);
    //sets movement animation
    void set_movement_animation();
    //return the incremenet of attributes at given level
    unsigned int get_level_increment(unsigned int value) const;
};


#endif

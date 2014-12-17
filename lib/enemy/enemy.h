//TITLE: ENEMY_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines each single enemy

#ifndef ENEMY_H
#define ENEMY_H

enum enemy_animation {idle_anim,up_anim,down_anim,left_anim,right_anim,dead_anim}; //defines each animation for an enemy

//defines the basic characteristics of an enemy kind
struct enemy_attributes {
    map<enemy_animation,al_anim> animation; //stores all animations of an enemy
    string name; //name of the enemy
    double speed; //basic speed (pixels per seconds)
    unsigned int max_life; //max (and initial) life of enemy
    unsigned int armor; //armor of the enemy
    unsigned int reward; //rreward when killed
    //Methods
    enemy_attributes();
    enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed);
    enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const map<enemy_animation,al_anim> &animation);
    //insert animation (erasing previous animations and reseting all counters)
    void insert_animation(enemy_animation type,const al_anim &anim);
    //clear all attributes (dont destroy bitmaps)
    void clear();
    //destroy all animations and clear data
    void destroy();
    //returns true if the enemy has all the necessary info
    bool check() const;
};


class enemy {
private:
    enemy_attributes attributes; //basic info of enemy type
    unsigned int life; //current life of enemy
    unsigned int level; //level may change enemy parameters (unused)
    double speed; //pixels per frame
    unsigned int reward;

    pair<double,double> position; //actual position, it refers to foot centered position
    pair<double,double> destiny; //position to move
    bool active; //if false, update will not take effect, false by default in constructors

    enemy_animation current_animation;
public:
    //CONSTRUCTORS
    //default constructor (actie=false by default)
    enemy();
    //constructor with basic info, enemy life will start with the max_life value
    //constructor with spawning in position given
    enemy(const enemy_attributes &attributes,unsigned int level,double posx,double posy,const ALLEGRO_TIMER *timer);

    //MODIFICATION
    //set enemy level (currently unused)
    void set_level(unsigned int level);
    //set enemy to active in given position
    void spawn(double posx,double posy);
    
    //CONSULT
    //return enemy name
    string get_name() const;
    //return enemy life
    unsigned int get_life() const;
    //return max life
    unsigned int get_max_life() const;
    //returns reward when killed
    unsigned int get_reward() const;
    //return enemy position in a pair<x,y>
    pair<double,double> get_position() const;
    //return the enemy destiny (where is moving)
    pair<double,double> get_destiny() const;
    //return true if enemy is alive(life>0)
    bool alive() const;
    //return true if enemy is active
    bool spawned() const;
    //return true if enemy is idle (destiny==position)
    bool idle() const;

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
    //deactive the enemy,so no longer will be updated or drawn (do after kill the enemy)
    void deactivate();
    //update the movement,animation and all booleans
    void update();
    //draw the current_animation in the enemy position
    //note that draw the enemy with the position at its feet
    void draw();

private:
    //changes to given movement animation
    void change_movement_animation(enemy_animation anim);
    //set animation to idle (stoppping all movement animation and current animation)
    void set_to_idle();
    //stops all movement anim
    void stop_movement_anim();
    //set speed (pixels per second), need timer wich will be used
    void set_speed(double spd,const ALLEGRO_TIMER *timer);
    //check enemy class is working well, debug_log output if error or warning
    void check() const;
};


#endif

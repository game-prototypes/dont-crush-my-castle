//TITLE: ENEMY_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: defines each single enemy

#ifndef ENEMY_H
#define ENEMY_H

enum enemy_animation {idle_anim,up_anim,down_anim,left_anim,right_anim,dead_anim}; //defines each animation for an enemy

class enemy {
private:
    string name; //name is the same for all enemies of the same kind
    unsigned int life;
    unsigned int level; //level may change enemy parameters (unused)
    unsigned int armor; //armor of the enemy
    double speed; //speed

    pair<double,double> position; //actual position
    pair<double,double> destiny; //position to move
    bool active; //if false, update will not take effect, false by default in constructors

    map<enemy_animation,al_anim> animation;
    enemy_animation current_animation;
public:
    //CONSTRUCTORS
    //default constructor
    enemy();
    //full constructor with animations
    enemy(const string &name,unsigned int life,unsigned int armor,double speed,const map<enemy_animation,al_anim> &animation);
    //full constructor without animations
    enemy(const string &name,unsigned int life,unsigned int armor,double speed);

    //MODIFICATION
    //set enemy life
    void set_life(unsigned int life);
    //set armor
    void set_armor(unsigned int armor);
    //set speed
    void set_speed(double speed);
    //set animation to use in iddle stage (remove any previous animation)
    void set_idle_animation(const al_anim &idle);
    //set dead animation (remove any previous animation)
    void set_dead_animation(const al_anim &dead);
    //set move animation (recommended all animations to have the same size) (remove any previous animation)
    void set_movement_animation(const al_anim &up,const al_anim &down,const al_anim &left,const al_anim &right);

    //CONSULT
    //return enemy name
    string get_name() const;
    //return enemy life
    unsigned int get_life() const;
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
    //set the enemy to active in the given position and checks
    void spawn(double posx,double posy);
    //stop the movement(idle) (final destination will be the current position)
    void stop();
    //decrease live and kill if life=0 (this method dont account the armor)
    void decrease_life(unsigned int dam);
    //set final destination, when reached, set_idle will be called
    void move_to(double x,double y);
    //enemy takes the given damage, decreasing life according to armor
    void damage(unsigned int dam);
    //set life automatically to 0 and live=false, this kills the enemy, starting the animation, but will not destroy the class
    void kill();
    //deactive the enemy,so no longer will be updated or drawn (do after kill the enemy)
    void deactivate ();
    //update the movement,animation and all booleans
    void update();
    //draw the current_animation in the enemy position
    void draw();
private:

    //insert animation (erasing previous animations and reseting all counters)
    void insert_animation(enemy_animation anim,const al_anim &animation);
    //set animation to idle (stoppping all movement animation and current
    void set_to_idle();
    //stops all movement anim
    void stop_movement_anim();
    void check();
};
















#endif

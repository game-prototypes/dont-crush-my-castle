//TITLE: ENEMY_SET_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#ifndef ENEMY_SET_H
#define ENEMY_SET_H

class enemy_set {
private:
    string name; //name of the set
    map<string,enemy_attributes> enemies; //the first string is the name of the enemy_attributes
    const ALLEGRO_TIMER *timer; //timer to be used
public:
    //CONSTRUCTORS
    enemy_set();
    enemy_set(const string &name,const ALLEGRO_TIMER* timer);
    enemy_set(const string &name,const vector<enemy_attributes> &enemy_list,const ALLEGRO_TIMER* timer);
    enemy_set(const string &name,const enemy_attributes &enemy_list,const ALLEGRO_TIMER* timer);
    ~enemy_set();

    //MODIFICATION
    void set_name(const string &name);
    void add_enemy(const enemy_attributes &info);
    void set_timer(const ALLEGRO_TIMER *timer);
    //CONSULT
    string get_name() const;
    unsigned int get_size() const;

    enemy spawn_enemy(const string &name,unsigned int level,double posx,double posy);//return new enemy spawned

private:

    void check();
};

#endif

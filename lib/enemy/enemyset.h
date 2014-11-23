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
public:
    //CONSTRUCTORS
    enemy_set();
    enemy_set(const string &name);
    enemy_set(const string &name,const vector<enemy_attributes> &enemy_list);
    enemy_set(const string &name,const enemy_attributes &enemy_list);
    ~enemy_set();

    //MODIFICATION
    void set_name(const string &name);
    void add_enemy(const enemy_attributes &info);
    //CONSULT
    string get_name() const;

    enemy spawn_enemy(const string &name,unsigned int level,double posx,double posy);//return new enemy spawned

private:

    void check();
};

#endif

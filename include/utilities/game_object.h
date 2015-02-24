//TITLE: GAME_OBJECTS_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: defines a generic gameobject

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <utility>
using namespace std;

class game_object {
protected:
    pair<double,double> position;
    bool active;
public:
    game_object();
    game_object(pair<double,double> position);
    ~game_object();
    void activate();
    void deactivate();
    void set_active(bool active);
    bool is_active() const;
    void set_position(double x,double y);
    void set_position(pair<double,double> position);
    pair<double,double> get_position() const;
    void draw() const;
    void update();
    bool check() const;
};
#endif
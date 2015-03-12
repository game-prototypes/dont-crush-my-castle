//TITLE: GAME_OBJECTS_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: defines a generic gameobject

#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <iostream>
#include <utility>
#include "game_object_attributes.h"
using namespace std;

class game_object {
protected:
    pair<double,double> position;
    bool active;
public:
    //CONSTRUCTORS
    game_object();
    game_object(pair<double,double> position);
    //DESTRUCTOR
    ~game_object();
    //METHODS
    //set active as true
    void activate();
    //set active to false
    void deactivate();
    //change active value
    void set_active(bool active);
    //return true if active is true
    bool is_active() const;
    //set position
    void set_position(double x,double y);
    //set position
    void set_position(pair<double,double> position);
    //returns game object position
    pair<double,double> get_position() const;
    //draw gameobject (will print an error and won't do anything)
    void virtual draw() const=0;
    //update gameobject (will print an error and won't do anything)
    void virtual update()=0;
    //check game object, return true if everyting is fine
    bool check() const;
};
#endif
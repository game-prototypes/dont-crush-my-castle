//TITLE: INPUT_HANDLER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: user input class for allegro5 (keys and mouse)

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <functional>
#include <allegro5/allegro.h>
using namespace std;

class input_handler {
public:
    enum mouse_button {primary,secondary,wheel};
private:
    function<void(int,unsigned int,unsigned int)> click_mouse; //function to handle mouse events (button,posx,posy)
    function<void(int)> key_pressed; //function to handle key events
    //function<void(int)> mouse_wheel; //function to handle mouse wheel events (being the argument the change of wheel)
    bool active; //if false, update function wont do anything
public:
    //CONSTRUCTORS
    //default constructor, not active
    input_handler();
    //contructors , sets functions, install keyboard and mouse, sets callback functions and sets handler to active
    input_handler(ALLEGRO_EVENT_QUEUE *event_queue,function<void(int,unsigned int,unsigned int)> click_mouse,function<void(int)> key_pressed);
    //DESTRUCTOR, unninstall keyboard and mouse
    ~input_handler();
    //activates/deactivates handler
    void set_active(bool active);
    //true if is active
    bool is_active() const;
    //return mouse position (in the current moment)
    pair<unsigned int,unsigned int> get_mouse_position() const;
    //return true if key with given keycode is pressed (in current moment)
    bool is_pressed(int keycode) const;
    //updates and call the necessary callback functions if a key is pressed or mouse is clicked
    void update(const ALLEGRO_EVENT &event) const; //updates input_handler, calling needed functions
    //sets callback functions
    void set_functions(function<void(int,unsigned int,unsigned int)> click_mouse,function<void(int)> key_pressed);
    //checks class
    bool check() const;
};
#endif

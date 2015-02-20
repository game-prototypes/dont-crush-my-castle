//TITLE: INPUT_HANDLER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
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
    function<void(int)> mouse_wheel; //function to handle mouse wheel events (being the argument the change of wheel)
public:
    input_handler(ALLEGRO_EVENT_QUEUE *event_queue,function<void(int,unsigned int,unsigned int)> click_mouse,function<void(int)> key_pressed,function<void(int)> mouse_wheel);
    ~input_handler();
    pair<unsigned int,unsigned int> get_mouse_position() const;
    bool is_pressed(int keycode) const;
    void update(const ALLEGRO_EVENT &event) const; //updates input_handler, calling needed functions
    bool check() const;
};
#endif
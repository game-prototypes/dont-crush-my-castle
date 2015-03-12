//TITLE: INPUT_HANDLER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: user input class for allegro5

#include "input_handler.h"

input_handler::input_handler() {
    active=false;
}
input_handler::input_handler(ALLEGRO_EVENT_QUEUE *event_queue,function<void(int,unsigned int,unsigned int)> click_mouse,function<void(int)> key_pressed) {
    al_install_mouse();
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    this->click_mouse=click_mouse;
    this->key_pressed=key_pressed;
    active=true;
}
input_handler::~input_handler() {
    al_uninstall_mouse();
    al_uninstall_keyboard();
    active=false;
}
void input_handler::set_active(bool active) {
    this->active=active;
}
bool input_handler::is_active() const {
    return active;
}
pair<unsigned int,unsigned int> input_handler::get_mouse_position() const {
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    return make_pair((unsigned int)state.x,(unsigned int)state.y);
}
bool input_handler::is_pressed(int keycode) const {
    ALLEGRO_KEYBOARD_STATE state;
    return al_key_down(&state,keycode);
}
void input_handler::update(const ALLEGRO_EVENT &event) const {
    if(active) {
        if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) click_mouse(event.mouse.button,(unsigned int) event.mouse.x,(unsigned int) event.mouse.y);
        if(event.type==ALLEGRO_EVENT_KEY_DOWN) key_pressed(event.keyboard.keycode);
    }
}
void input_handler::set_functions(function<void(int,unsigned int,unsigned int)> click_mouse,function<void(int)> key_pressed) {
    if(click_mouse) this->click_mouse=click_mouse;
    if(key_pressed) this->key_pressed=key_pressed;
}
bool input_handler::check() const {
    bool b=true;
    if(al_is_mouse_installed()==false) b=false;
    if(al_is_keyboard_installed()==false) b=false;
    if(al_get_mouse_num_axes()<2) b=false;
    if(al_get_mouse_num_buttons()<2) b=false;
    if(!click_mouse || !key_pressed) b=false;
    return b;
}
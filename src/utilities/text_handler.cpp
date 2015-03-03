//TITLE: TEXT_HANDLER_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: defines a text in the game screen
#include "text_handler.h"


text_handler::text_handler() {
    active=false;
    position=make_pair(0,0);
    set_color(0,0,0);
    font=NULL;
}
text_handler::text_handler(ALLEGRO_FONT *font,unsigned int x,unsigned int y) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_font(font);
    set_color(0.0,0.0,0.0);
}
text_handler::text_handler(const string &text,ALLEGRO_FONT *font,unsigned int x,unsigned int y) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_font(font);
    set_text(text);
    set_color(0.0,0.0,0.0);
}
text_handler::text_handler(const string &text,const string &filename,unsigned int size,unsigned int x,unsigned int y) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_font(filename,size);
    set_text(text);
    set_color(0.0,0.0,0.0);
}
text_handler::~text_handler() {
    destroy_font();
}

void text_handler::draw() const {
    if(active) al_draw_text(font,text_color, position.first,position.second, text_align,text.c_str());
}
void text_handler::set_text(const string &text) {
    this->text=text;
}
void text_handler::set_font(ALLEGRO_FONT *font) {
    destroy_font();
    this->font=font;
}
void text_handler::set_font(const string &filename,int size) {
    destroy_font();
    font=al_load_font(filename.c_str(),size,0);
}
void text_handler::set_color(double r,double g,double b) {
    this->text_color=al_map_rgb_f(r,g,b);
}
void text_handler::set_color(double r,double g,double b,double a) {
    this->text_color=al_map_rgba_f(r,g,b,a);
}
void text_handler::set_alignment(alignment text_align) {
    this->text_align=text_align;
}
//return the string
string text_handler::get_string() const {
    return text;
}
//clear the string, not changing font
void text_handler::clear() {
    text.clear();
}
bool text_handler::check() const {
    bool b=true;
    return b;
}
//PRIVATE
void text_handler::destroy_font() {
    if(font!=NULL) {
        al_destroy_font(font);
        font=NULL;
    }
}

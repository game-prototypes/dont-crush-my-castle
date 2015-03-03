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
    set_alignment(align_left);
    font=NULL;
}
text_handler::text_handler(const string &tag,ALLEGRO_FONT *font,unsigned int x,unsigned int y) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_font(font);
    set_tag(tag);
    set_alignment(align_left);
    set_color(0.0,0.0,0.0);
}


text_handler::text_handler(const string &tag,ALLEGRO_FONT *font,unsigned int x,unsigned int y,const string &text) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_font(font);
    set_string(text);
    set_alignment(align_left);
    set_tag(tag);
    set_color(0.0,0.0,0.0);
}
text_handler::text_handler(const string &tag,const string &filename,unsigned int size,unsigned int x,unsigned int y,const string &text) {
    font=NULL;
    active=true;
    position=make_pair(x,y);
    set_alignment(align_left);
    set_font(filename,size);
    set_string(text);
    set_tag(tag);
    set_color(0.0,0.0,0.0);
}
text_handler::~text_handler() {
    text.clear();
    tag.clear();
    // destroy_font();
}

void text_handler::draw() const {
    if(active) al_draw_text(font,text_color, position.first,position.second, text_align,text.c_str());
}
void text_handler::set_string(const string &text) {
    this->text=text;
}
void text_handler::set_tag(const string &tag) {
    this->tag=tag;
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
string text_handler::get_tag() const {
    return tag;
}
unsigned int text_handler::get_width() const {
    return al_get_text_width(font, text.c_str());
}
//clear the string, not changing font
void text_handler::clear() {
    text.clear();
}
void text_handler::update() {
}
void text_handler::destroy() {
    destroy_font();
    tag.clear();
    clear();
    set_color(0.0,0.0,0.0);
    active=false;
}
bool text_handler::check() const {
    bool b=true;
    if(!font && active) b=false;
    return b;
}
//PRIVATE
void text_handler::destroy_font() {
    if(font!=NULL) {
        al_destroy_font(font);
        font=NULL;
    }
}

//TITLE: TEXT_HANDLER_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: defines a text in the game screen
#ifndef TEXT_HANDLER
#define TEXT_HANDLER

//#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "game_object.h"


class text_handler : public game_object {
public:
    enum alignment {align_left,align_center,align_right};
private:
    string text;
    string tag; //name (tag) of the handler
    ALLEGRO_COLOR text_color;
    ALLEGRO_FONT *font;
    alignment text_align;

public:
    text_handler();
    text_handler(const string &tag,ALLEGRO_FONT *font,unsigned int x,unsigned int y);
    text_handler(const string &tag,ALLEGRO_FONT *font,unsigned int x,unsigned int y,const string &text);
    text_handler(const string &tag,const string &filename,unsigned int size,unsigned int x,unsigned int y,const string &text);
    ~text_handler();

    void draw() const;
    //sets the string
    void set_string(const string &text);
    void set_tag(const string &tag);
    //sets new font
    void set_font(ALLEGRO_FONT *font);
    //set new font,if size is negative it will measure as pixel heigh
    void set_font(const string &filename,int size);
    //sets new color
    void set_color(double r,double g,double b);
    void set_color(double r,double g,double b,double a);
    void set_alignment(alignment text_align);
    //return the string
    string get_string() const;
    string get_tag() const;
    //returns text width in pixels
    unsigned int get_width() const;

    //clear the string, not changing font
    void clear();
    //does nothing
    void update();
    void destroy();
    bool check() const;
private:
    //destroy font
    void destroy_font();
};

#endif
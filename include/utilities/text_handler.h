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

// al_init_font_addon(); // initialize the font addon
//  al_init_ttf_addon();// initialize the ttf (True Type Font) addon

// ALLEGRO_FONT *font = al_load_ttf_font("pirulen.ttf",72,0 );


class text_handler : public game_object {
public:
    enum alignment {align_left,align_center,align_right};
private:
    string text;
    ALLEGRO_COLOR text_color;
    ALLEGRO_FONT *font;
    alignment text_align;

public:
    text_handler();
    text_handler(ALLEGRO_FONT *font,unsigned int x,unsigned int y);
    text_handler(const string &text,ALLEGRO_FONT *font,unsigned int x,unsigned int y);
    text_handler(const string &text,const string &filename,unsigned int size,unsigned int x,unsigned int y);
    ~text_handler();

    void draw() const;
    //sets the string
    void set_text(const string &text);
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
    //clear the string, not changing font
    void clear();
    //void update();
    bool check() const;

private:
    //destroy font
    void destroy_font();
};

#endif
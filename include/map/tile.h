//TITLE: TILE_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: Defines one tile of a tileset

#ifndef TILE
#define TILE

#include "al_utils.h"


class tile {
public:
    enum tile_type {blocked,road,ground,open_ground,special,null_tile};
    /*tile_type:
    block: blocked, not construction or enemies can pass
    road: blocked for construction, enemies can pass
    ground: free for construction
    open_ground: free for constuction and enemy movement
    */

    tile_type type;
private:
    ALLEGRO_BITMAP *bitmap;
public:
    //default constructor
    tile();
    //full constructor
    tile(tile_type type,const ALLEGRO_BITMAP *bitmap);
    //full constructor with resizing
    tile(tile_type type,const ALLEGRO_BITMAP *bitmap,unsigned int width);
    //copy constructor
    tile(const tile &other);
    //destructor
    ~tile();
    //resize the tile bitmap to a squared one with given width
    void resize(unsigned int width);
    //draw the tile bitmap on x,y position (of the target bitmap)
    void draw(float x,float y) const;
    //draw the tile bitmap on x,y  position, resizing it to width given
    void draw_resized(float x,float y,unsigned int width) const;
    //returns tile width
    unsigned int size() const;
    //check the class
    bool check() const;
    //OPERATORS
    tile &operator=(const tile &other);
};

#endif

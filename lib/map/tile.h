//TITLE: TILE_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Defines one tile of a tileset

#ifndef TILE_H
#define TILE_H
#include "al_utils.h"
enum tile_type {blocked,road,ground,special,null_tile};
/*tile_type:
block: blocked, not construction or enemies can pass
road: blocked for construction, enemies can pass
ground: free for construction
*/

class tile {
public:
    tile_type type;
private:
    ALLEGRO_BITMAP *bitmap;
public:
    tile();
    tile(tile_type type,ALLEGRO_BITMAP *bitmap);
    ~tile();

    //resize the tile bitmap
    void resize(unsigned int width,unsigned int height){
    //draw the tile bitmap on x,y position (of the target bitmap)
    void draw(float x,float y);
    //draw the tile bitmap on x,y  position, resizing it to width,height size
    void draw_resized(float x,float y,unsigned int width,unsigned int height);
};

#endif

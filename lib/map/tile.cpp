//TITLE: TILE_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Defines one tile of a tileset

#include "tile.h"

tile::tile() {
    type=null_tile;
}
tile::tile(tile_type type,ALLEGRO_BITMAP *bitmap) {
    this->type=type;
    this->bitmap=bitmap;
}

//MODIFICATION
void tile::resize(unsigned int width,unsigned int height) {
    if(width<=0 || height<=0) debug_log::report("resize bitmap error",err,true,false,false);
    else {
        resize_bitmap(bitmap,width,height);
    }
}

//Drawing methods
void tile::draw(float x,float y) const {
    al_draw_bitmap(bitmap,x,y,0);
}
void tile::draw_resized(float x,float y,unsigned int width,unsigned int height) const {
    if(width==0 || height==0) debug_log::report("tile size=0",err,true,false,false);
    else
        al_draw_scaled_bitmap(bitmap,0.0,0.0,al_get_bitmap_width(bitmap),al_get_bitmap_height(bitmap),x,y,width,height,0);
}

void tile::destroy_bitmap() {
    al_destroy_bitmap(bitmap);
}

//TITLE: TILE_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.2
//DESCRIPTION: Defines one tile of a tileset

#include "tile.h"

tile::tile() {
    type=null_tile;
}
tile::tile(tile_type type,const ALLEGRO_BITMAP *bitmap) {
    this->type=type;
    unsigned int w=get_bitmap_width(bitmap);
    unsigned int h=get_bitmap_height(bitmap);
    if(w==0 || h==0) debug_log::report("error,bitmap with size=0",err,true,true,false);
    else {
        if(w==h) this->bitmap=copy_bitmap(bitmap);
        else {
            debug_log::report("bitmap not squared, resizing to lowest size",warning,true,false,false);
            if(w>h) this->bitmap=copy_bitmap(bitmap,h,h);
            else this->bitmap=copy_bitmap(bitmap,w,w);
        }
    }
}
tile::tile(tile_type type,const ALLEGRO_BITMAP *bitmap,unsigned int side_size) {
    this->type=type;
    unsigned int w=get_bitmap_width(bitmap);
    unsigned int h=get_bitmap_height(bitmap);
    if(w==0 || h==0 || side_size==0) debug_log::report("error,bitmap with size=0",err,true,true,false);
    else {
        if(w!=h) debug_log::report("bitmap not squared",warning,true,false,false);
        this->bitmap=copy_bitmap(bitmap,side_size,side_size);
    }
}
tile::tile(const tile &other) {
    this->type=other.type;
    this->bitmap=copy_bitmap(other.bitmap);
}
tile::~tile() {
    al_destroy_bitmap(this->bitmap);
    this->bitmap=NULL;
}
//MODIFICATION
void tile::resize(unsigned int width) {
    if(width==0) debug_log::report("resize bitmap error (size equals 0)",err,true,true,false);
    else {
        resize_bitmap(bitmap,width,width);
    }
}
//Drawing methods
void tile::draw(float x,float y) const {
    if(bitmap!=NULL)
        draw_bitmap(bitmap,x,y);
}
void tile::draw_resized(float x,float y,unsigned int width) const {
    if(width==0) debug_log::report("tile size=0",err,true,true,false);
    else if(bitmap!=NULL)  draw_scaled(bitmap,x,y,width,width);
}
unsigned int tile::size() const {
    return get_bitmap_width(bitmap);
}
bool tile::check() const {
    bool b=true;
    if(bitmap==NULL && type!=null_tile) {
        debug_log::report("tile with no bitmap",err,true,true,false);
        b=false;
    }
    else if(size() != (unsigned int) al_get_bitmap_height(bitmap)) {
        debug_log::report("tile not squared",err,true,true,false);
        b=false;
    }
    return b;
}
tile &tile::operator=(const tile &other) {
    if(this!=&other) {
        this->type=other.type;
        al_destroy_bitmap(this->bitmap);
        this->bitmap=copy_bitmap(other.bitmap);
    }
    return *this;
}

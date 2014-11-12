//TITLE: TILEMAP_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Generate,write,read and draw maps

#include "tilemap.h"

tilemap::tilemap() {
}

tilemap::clear(){
                 name.clear();
                 background.clear();
                 foreground.clear();
                 
                 }

int tilemap::get_height() {
    return background.size();
}
int tilemap::get_width() {
    if(background.size()>0) return background[0].size();
    else return 0;
}
string tilemap::get_name(){
       return name;
       }
bool tilemap::occupied_tile(unsigned int x,unsigned int y) {
    return foreground[x][y];
}
tile_id tilemap::get_tile_id(unsigned int x,unsigned int y) {
    return background[x][y];
}
tile_type tilemap::get_tile_type(unsigned int x,unsigned int y) {
    tile_id id=background[x][y];
    return (tiles->get_tile(id)).type;
}

void tilemap::draw_tilemap() {
    int height=get_height();
    int width=get_width();
    float x=0,y=0;
    int tilew=tiles->get_tile_width();
    int tileh=tiles->get_tile_height();
    for(int i=0; i<height; i++) {
        x=0;
        for(int j=0; j<width; j++) {
            draw_tile(background[i][j],x,y);
            x+=tilew;
        }
        y+=tileh;
    }
}

//Private methods
void tilemap::init_matrix(int width,int height) {
    foreground.clear();
    background.clear();
    foreground.resize(height);
    background.resize(height);
    vector<bool> v(width,empty_tile);
    for(int i=0; i<height; i++) {
        foreground.push_back(v);
        background.resize(width);
    }
}
void tilemap::check() {
    if(background.size()!=foreground.size()) debug_log::report("map matrix don't match(height)",err,true,true,false);
    if(background.size()>0 && foreground.size()>0 && background[0].size()!=foreground[0].size()) debug_log::report("map matrix don't match(width)",err,true,true,false);
}

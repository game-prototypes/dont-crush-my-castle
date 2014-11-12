//TITLE: TILESET_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Information about a set of tiles to be used on maps
#ifndef TILESET_H
#define TILESET_H
#include "tile.h"


const string tmx_tiletype_property="tiletype"; //defines the name of the property used on tmx for tiletype
typedef int tile_id; //defines a id for a tile in the tileset
class tileset {
private:
    map<tile_id,tile> tile_list;
    string name;
    unsigned int height;
    unsigned int width; //each tile height and width

public:
  //default constructor
    tileset();
    //contructor from tmx file
      //tileset(const Tmx::Tileset *ts);
    tileset(string name,ALLEGRO_BITMAP* bitmap,unsigned int height,unsigned int width);
    tileset(ALLEGRO_BITMAP* bitmap,unsigned int height,unsigned int width);
    //MODIFICATION
    void clear();
    //ACCESS
    //returns tile with given id(null tile if id doesnt match)
    tile get_tile(tile_id id);
    //get width of each tile
    int get_tile_width();
    //gets height of each tile
    int get_tile_height();
    //returns name of tileset
    string get_name();

    //DRAWING
    //draw the tile with given id in position x,y
    void draw_tile(tile_id id,float x,float y);
    //draw the tile with given id in position x,y resizing it into width,height size
    void draw_scaled_tile(tile_id id,float x,float y,unsigned int width,unsigned int height);
    //resize the tileset, resizing the bitmaps of all tiles in tileset
    void resize_tileset(int width,int height);
    //adds a tileset from tmx file to the actual tileset (resizing bitmaps), name and sizes will remain unchanged
    //tiles with same id will not be inserted
      //void add_tmx_tileset(const Tmx::Tileset *ts);
    

private:
    //adds a tile,return true if inserted, false if already exists
    bool add_tile(tile_id id,tile_type type,ALLEGRO_BITMAP *bitmap);

    void check();
};
#endif

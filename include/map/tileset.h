//TITLE: TILESET_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.3
//DESCRIPTION: Information about a set of tiles to be used on maps
#ifndef TILESET_H
#define TILESET_H

#include "tile.h"
#include <map>

typedef int tile_id; //defines a id for a tile in the tileset
static const tile_id null_tile_id=-1;
class tileset {
private:
    string name;
    map<tile_id,tile> tile_list;
    tile_id lowest_free; //lowest "free" id
    unsigned int tile_size; //each tile width/height
    //  const static string tmx_tiletype_property; //defines the name of the property used on tmx for tiletype
public:
    //default constructor
    tileset();
    //contructor from tmx file
    //      tileset(const Tmx::Tileset *ts);
    //full constructor
    tileset(const string &name,const ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int tile_size,int ntiles=-1);
    //full constructor (without name)
    tileset(const ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int tile_size,int ntiles=-1);
    //contructors with one tile
    tileset(const string &name,const tile &t,unsigned int tile_size);
    tileset(const tile &t,unsigned int tile_size);
    //size of tileset tiles will be tile size
    tileset(const tile &t);
    ~tileset();
    //MODIFICATION
    //adds a tile,returning tile_id used
    tile_id add_tile(tile_type type,const ALLEGRO_BITMAP *bitmap);
    tile_id add_tile(const tile &t);
    //slices given bitmap and adds tiles to the tileset, return vector of ids used
    vector<tile_id> load_from_bitmap(const ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int tile_size,int ntiles);
    //removes tile with given id
    void remove_tile(tile_id id);
    //change name
    void set_name(const string &name);
    //ACCESStypes.push_back(road);
    //return true if tile with given tile_id exists
    bool is_tile(tile_id id) const;
    //returns the size of the tileset
    unsigned int size() const;
    //get width of each tile
    unsigned int get_tile_width() const;
    //gets height of each tile (same as get_tile_height)
    unsigned int get_tile_height() const;
    //gets tile size (same as get_tile_width)
    unsigned int get_tile_size() const;
    //returns name of tileset
    string get_name() const;
    //returns tile type (null if not found)
    tile_type get_tile_type(tile_id id) const;

    //DRAWING
    //draw the tile with given id in position x,y
    void draw_tile(tile_id id,float x,float y) const;
    //draw the tile with given id in position x,y resizing it into width,height size
    void draw_resized_tile(tile_id id,float x,float y,unsigned int tile_size) const;
    //resize the tileset, resizing the bitmaps of all tiles in tileset
    void resize_tileset(unsigned int tile_size);
    //adds a tileset from tmx file to the actual tileset (resizing bitmaps), name and sizes will remain unchanged
    //tiles with same id will not be inserted
    //void add_tmx_tileset(const Tmx::Tileset *ts);

    //return true if everything correct
    bool check() const;
private:
    //return next free id after or equal to actual lower_id
    tile_id get_next_free_id() const;
};
#endif

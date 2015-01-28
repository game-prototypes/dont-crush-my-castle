//TITLE: TILEMAP_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: Generate,write,read and draw maps
#ifndef TILEMAP_H
#define TILEMAP_H

#include "tileset.h"
#include <stack>
#include <set>

class tilemap {
private:
    vector< vector<tile_id> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
    vector< vector<int> > path_map; //defines the distance to destiny of each tile
    set< pair<unsigned int,unsigned int> > destination; //possible targets of enemies
    set< pair<unsigned int,unsigned int> > spawners; //possible targets of enemies
    string name;
    const tileset *tiles; //pointer to tileset
public:
    //default coonstructor
    tilemap();
    //full constructor with name
    tilemap(const string &name,const vector< vector<tile_id> > &background,const tileset *tiles,const set< pair<unsigned int,unsigned int> > &destination);
    //full constructor without name
    tilemap(const vector< vector<tile_id> > &background,const tileset *tiles,const set< pair<unsigned int,unsigned int> > &destination);
    //Loads from tmx file
    // void loadtmx(string filename);
    ~tilemap();
    //MODIFICATION
    //clear all the map info (except tileset)
    void clear();
    //set a tile to occupied
    void occupy_tile(unsigned int x,unsigned int y);
    //set a section to occupied, only the part inside the matrix, (check the section is free with empty_section)
    void occupy_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height);
    //set tile to empty
    void free_tile(unsigned int x,unsigned int y);
    //set all tiles to empty in the given section
    void free_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height);
    //add destiny to map
    void add_destiny(unsigned int x,unsigned int y);
    //adds new spawner
    void add_spawner(unsigned int x,unsigned int y);
    //sets tile in position[x,y] with given tile id
    void set_tile(unsigned int x,unsigned int y,tile_id tid);
    //ACCESS
    //return true if given positon is in matrix
    bool in_matrix(unsigned int x,unsigned int y) const;
    //returns map width in tiles
    unsigned int get_width() const;
    //returns map height in tiles
    unsigned int get_height() const;
    //return positon in tiles
    pair<unsigned int,unsigned int> translate_position(double x,double y) const;
    //return position in pixels (the center of the tile)
    pair<double,double> translate_position(unsigned int x,unsigned int y) const;
    //return size (height or width) of tile (in pixels)
    unsigned int get_tile_size() const;
    //returns the map name
    string get_name() const;
    //return empty tile (true) or occupied tile(false)
    bool empty_tile(unsigned int x,unsigned int y) const;
    //check if the section given by the top-left point,width and height is occupied (if at least one tile inside is occupied) position x,y include
    //return true if all tiles inside the section free, return false if out of bounds returns false
    bool empty_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) const;
    //return tile_id
    tile_id get_tile_id(unsigned int x,unsigned int y) const;
    //return tile_type
    tile_type get_tile_type(unsigned int x,unsigned int y) const;
    //returns path value
    int get_path_value(unsigned int x,unsigned int y) const;
    //returns next tile (following path map)
    pair<unsigned int,unsigned int> get_next_position(unsigned int x,unsigned int y) const;
    //return true if given position is in the path of the enemies
    bool in_path(unsigned int x,unsigned int y) const;
    //return true if is posible to build in given position (correct empty tile and enemy path not blocked
    bool can_build(unsigned int x,unsigned int y) const;
    //will check if build in [x,y] isolates any spawner (use only when necessary)
    bool check_path_if_build(unsigned int x,unsigned int y);

    //DRAWING
    //draw all the tilemap in the target bitmap
    void draw_tilemap() const;
    //check if everything is ok
    bool check() const;
private:
    //generate path_map from background given destination tiles
    bool spawners_in_path() const;
    void update_path_map();
    //updates foreground according to background
    void generate_foreground();
    //set background so its rectgular
    void set_background(const vector< vector<tile_id> > &back);
    vector< vector<int> > generate_path_map() const;
    //      void load_background(const Tmx::Layer *lay,int width,int height);

};
#endif

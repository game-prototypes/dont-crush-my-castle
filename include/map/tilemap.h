//TITLE: TILEMAP_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.3
//DESCRIPTION: Generate,write,read and draw maps
#ifndef TILEMAP_H
#define TILEMAP_H

#include "tileset.h"
#include <stack>

class tilemap {
private:
    vector< vector<tile_id> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
    vector< vector<int> > path_map; //defines the distance to destiny of each tile
    string name;
    tileset *tiles; //pointer to tileset
public:
    tilemap();
    tilemap(const string &name,const vector< vector<tile_id> > &background,tileset *tiles);
    tilemap(const vector< vector<tile_id> > &background,tileset *tiles);

    //Loads from tmx file
    // void loadtmx(string filename);

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
    //ACCESS
    //returns map width in tiles
    unsigned int get_width() const;
    //returns map height in tiles
    unsigned int get_height() const;
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
    //DRAWING
    //draw all the tilemap in the target bitmap
    void draw_tilemap() const;


private:
    //init foreground matrix to 0 and path_map to -1 and generate foreground
    void init_submatrix(unsigned int width,unsigned int height);
    //generate path_map from background given destination tiles
    void update_path_map(vector< pair<unsigned int,unsigned int> > destination);
    //updates foreground according to background
    void generate_foreground();
    //      void load_background(const Tmx::Layer *lay,int width,int height);
    //cehcks if given position is in the matrix
    bool in_matrix(unsigned int x,unsigned int y) const;
    bool check() const;

};
#endif

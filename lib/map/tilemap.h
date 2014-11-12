//TITLE: TILEMAP_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Generate,write,read and draw maps
#ifndef TILEMAP_H
#define TILEMAP_H
#include "tileset.h"
#define empty_tile 0
#define occupied_tile 1

class tilemap {
private:
    vector< vector<tile_id> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
    string name;
    tileset *tiles; //pointer to tileset
    //   unsigned int width; //map size (in tiles)
    //   unsigned int height;
public:
    tilemap();

    //Loads from tmx file
    /*   void loadtmx(string filename) {
           Tmx::Map map;
           map.ParseFile(filename);
           if(map.HasError()==false) {
               //   int layers=map.GetNumLayers(); //we will use only first layer
               int width=map.GetWidth();
               int height=map.GetHeight();
               init_matrix(width,height);
               const Tmx::Layer *back=map.GetLayer(0); //get the background layer
               load_background(back,width,height);
               tiles.clear();
               const vector< Tmx::Tileset * > vts=map.GetTilesets();
               if(vts.size()==0) debug_log::report("Not tileset",err,true,true,false);
               else if(vts.size()>1) debug_log::report("more than one tilesey",warning,true,false,false);
               for(int i=0; i<vts.size(); i++) {
                   tiles.add_tileset(vts[i]);
               }
               check();
           }
       }*/
    //MODIFICATION
    //clear all the map info (except tileset)
    void clear();
    //ACCESS
    //returns map width in tiles
    unsigned int get_width();
    //returns map height in tiles
    unsigned int get_height();
    //returns the map name
    string get_name();
    //return occupied tile (true) or empty tile(false)
    bool occupied_tile(unsigned int x,unsigned int y);
    //return tile_id
    tile_id get_tile_id(unsigned int x,unsigned int y);
    //return tile_type
    tile_type get_tile_type(unsigned int x,unsigned int y);
    //DRAWING
    //draw all the tilemap in the target bitmap
    void draw_tilemap();


private:
    void init_matrix(int width,int height);
    /*   void load_background(const Tmx::Layer *lay,int width,int height) {
           for(int i=0; i<height; i++) {
               for(int j=0; j<width; j++) {
                   background[i][j]=lay->GetTileTilesetIndex(i,j);
               }
           }
       }*/
    void check();

};
#endif

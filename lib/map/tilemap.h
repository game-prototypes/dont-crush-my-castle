//TITLE: TILEMAP_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Generate,write,read and draw maps
#ifndef TILEMAP_H
#define TILEMAP_H
class tilemap {
private:
    vector< vector<tile_id> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
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
    //ACCESS
    //returns map width in tiles
    unsigned int get_width() const;
    //returns map height in tiles
    unsigned int get_height() const;
    //returns the map name
    string get_name() const;
    //return occupied tile (true) or empty tile(false)
    bool occupied_tile(unsigned int x,unsigned int y) const;
    //return tile_id
    tile_id get_tile_id(unsigned int x,unsigned int y) const;
    //return tile_type
    tile_type get_tile_type(unsigned int x,unsigned int y) const;
    //DRAWING
    //draw all the tilemap in the target bitmap
    void draw_tilemap() const;


private:
    void init_foreground_matrix(unsigned int width,unsigned int height);
    //   void load_background(const Tmx::Layer *lay,int width,int height);

    void check();

};
#endif

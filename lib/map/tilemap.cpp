//TITLE: TILEMAP_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Generate,write,read and draw maps

#include "tilemap.h"

tilemap::tilemap() {
}
tilemap::tilemap(const string &name,const vector< vector<tile_id> > &background,tileset *tiles) {
    this->tiles=tiles;
    this->name=name;
    this->background=background;
    if(background.size()>0) init_foreground_matrix(background[0].size(),background.size());
}
tilemap::tilemap(const vector< vector<tile_id> > &background,tileset *tiles) {
    this->tiles=tiles;
    this->background=background;
    if(background.size()>0) init_foreground_matrix(background[0].size(),background.size());
}
/*   void tilemap::loadtmx(string filename) {
           Tmx::Map map;
           map.ParseFile(filename);
           if(map.HasError()==false) {
               //   int layers=map.GetNumLayers(); //we will use only first layer
               int width=map.GetWidth();
               int height=map.GetHeight();
              // init_matrix(width,height); //CHANGE
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

void tilemap::clear() {
    name.clear();
    background.clear();
    foreground.clear();
}
void tilemap::occupy_tile(unsigned int x,unsigned int y) {
    foreground[x][y]=1;
}
void tilemap::occupy_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
    if(x+width>get_width()) width=get_width()-x;
    if(y+height>get_height()) height=get_height()-y;
    for(unsigned int i=0; i<width; i++) {
        for(unsigned int j=0; j<height; j++)
            foreground[x+i][y+j]=1;
    }
}
void tilemap::free_tile(unsigned int x,unsigned int y) {
    foreground[x][y]=0;
}
void tilemap::free_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
    if(x+width>get_width()) width=get_width()-x;
    if(y+height>get_height()) height=get_height()-y;
    for(unsigned int i=0; i<width; i++) {
        for(unsigned int j=0; j<height; j++)
            foreground[x+i][y+j]=0;
    }
}
unsigned int tilemap::get_width() const {
    if(background.size()>0) return background[0].size();
    else return 0;
}
unsigned int tilemap::get_height() const {
    return background.size();
}

string tilemap::get_name() const {
    return name;
}
bool tilemap::empty_tile(unsigned int x,unsigned int y) const {
    return !foreground[x][y];
}
bool tilemap::empty_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
    if(x+width>get_width() || y+height>get_height()) return false;
    else {
        for(unsigned int i=0; i<width; i++) {
            for(unsigned int j=0; j<height; j++)
                if(foreground[x+i][y+j]==1) return false;
        }
        return true;
    }
}

tile_id tilemap::get_tile_id(unsigned int x,unsigned int y) const {
    return background[x][y];
}
tile_type tilemap::get_tile_type(unsigned int x,unsigned int y) const {
    tile_id id=background[x][y];
    return (tiles->get_tile(id)).type;
}

void tilemap::draw_tilemap() const {
    int height=get_height();
    int width=get_width();
    float x=0,y=0;
    int tilew=tiles->get_tile_width();
    int tileh=tiles->get_tile_height();
    for(int i=0; i<height; i++) {
        x=0;
        for(int j=0; j<width; j++) {
            tiles->draw_tile(background[i][j],x,y);
            x+=tilew;
        }
        y+=tileh;
    }
}

//Private methods
void tilemap::init_foreground_matrix(unsigned int width,unsigned int height) {
    foreground.clear();
    foreground.resize(height);
    vector<bool> v(width,false);
    for(unsigned int i=0; i<height; i++) {
        foreground.push_back(v);
    }
}
/*   void tilemap::load_background(const Tmx::Layer *lay,int width,int height) {
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                background[i][j]=lay->GetTileTilesetIndex(i,j);
            }
        }
    }*/
void tilemap::check() {
    if(background.size()!=foreground.size()) debug_log::report("map matrix don't match(height)",err,true,true,false);
    if(background.size()>0 && foreground.size()>0 && background[0].size()!=foreground[0].size()) debug_log::report("map matrix don't match(width)",err,true,true,false);
}

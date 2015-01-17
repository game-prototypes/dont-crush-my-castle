//TITLE: TILEMAP_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.3
//DESCRIPTION: Generate,write,read and draw maps

#include "tilemap.h"

tilemap::tilemap() {
}
tilemap::tilemap(const string &name,const vector< vector<tile_id> > &background,tileset *tiles) {
    this->tiles=tiles;
    this->name=name;
    this->background=background;
    if(background.size()>0) init_submatrix(background[0].size(),background.size());
    check();
}
tilemap::tilemap(const vector< vector<tile_id> > &background,tileset *tiles) {
    this->tiles=tiles;
    this->background=background;
    if(background.size()>0) init_submatrix(background[0].size(),background.size());
    generate_foreground();
    check();
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
    path_map.clear();
}
void tilemap::occupy_tile(unsigned int x,unsigned int y) {
    if(in_matrix(x,y)==false) debug_log::report("trying to access out of map",warning,true,false,false);
    else
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
    if(in_matrix(x,y)==false) debug_log::report("trying to access out of map",warning,true,false,false);
    else
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
    if(in_matrix(x,y))
        return !foreground[x][y];
    else return false;
}
bool tilemap::empty_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) const {
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
    if(in_matrix(x,y))
        return background[x][y];
    else return -1;
}
tile_type tilemap::get_tile_type(unsigned int x,unsigned int y) const {
    if(in_matrix(x,y)) {
        tile_id id=background[x][y];
        return (tiles->get_tile_type(id));
    }
    else {
        debug_log::report("get_tyle_type out of bounds",err,true,true,false);
        return null_tile;
    }
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
void tilemap::init_submatrix(unsigned int width,unsigned int height) {
    foreground.clear();
    path_map.clear();
    foreground.resize(height);
    path_map.resize(height);
    vector<bool> v(width,false);
    vector<int> v2(width,-1);
    for(unsigned int i=0; i<height; i++) {
        foreground.push_back(v);
        path_map.push_back(v2);
    }
    generate_foreground();
}
void tilemap::update_path_map(vector< pair<unsigned int,unsigned int> > destination) {
    if(destination.empty()) debug_log::report("no final destination in map",err,true,true,false);
    for(unsigned int i=0; i<path_map.size(); i++)
        for(unsigned int j=0; j<path_map[0].size(); j++)
            path_map[i][j]=-1; //all path map set to -1
    stack< pair<unsigned int,unsigned int> > left_tiles; //tiles left to check surroundings
    pair<unsigned int,unsigned int> til;
    for(unsigned int i=0; i<destination.size(); i++) {
        til=destination[i];
        path_map[til.first][til.second]=0; //set tile of destination to 0
        left_tiles.push(til);
    }
    while(!left_tiles.empty()) {
        til=left_tiles.top();
        left_tiles.pop();
        for(int i=-1; i<=1; i++) {
            for(int j=-1; j<=1; j++) {
                int x=til.first+i;
                int y=til.second+j;
                if(x>0 && y>0) {
                    if(in_matrix(x,y)) {
                        if(get_tile_type(x,y)==road || (get_tile_type(x,y)==open_ground && foreground[x][y]==0)) {
                            if(path_map[x][y]==-1) left_tiles.push(make_pair(x,y)); //push tile if havent been updated yet
                            int val=path_map[til.first][til.second]+1;
                            if(path_map[x][y]<val) path_map[x][y]=val;
                        }
                    }
                }
            }
        }
    }
}
void tilemap::generate_foreground() {
    for(unsigned int i=0; i<background.size(); i++) {
        for(unsigned int j=0; j<background.size(); j++) {
            bool b=false;
            switch(get_tile_type(i,j)) {
            case blocked:
                b=true;
                break;
            case road:
                b=true;
                break;
            case ground:
                b=false;
                break;
            case special:
                b=true; //special are occupied
            case null_tile:
                b=true;
            case open_ground:
                b=false;
                break;
            }
            foreground[i][j]=b;
        }
    }
}
bool tilemap::in_matrix(unsigned int x,unsigned int y)const {
    if(x<get_width() || y<get_height()) return true;
    else return false;
}
/*   void tilemap::load_background(const Tmx::Layer *lay,int width,int height) {
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                background[i][j]=lay->GetTileTilesetIndex(i,j);
            }
        }
    }*/
bool tilemap::check() const {
    bool b=true;
    if(background.size()!=foreground.size() || background.size()!=path_map.size()) {
        debug_log::report("map matrix don't match(height)",err,true,true,false);
        b=false;
    }
    if(background.empty()) {
        debug_log::report("empty map",err,true,true,false);
        b=false;
    }
    else if(background[0].size()!=foreground[0].size() || background[0].empty()) {
        debug_log::report("map matrix incorrect width",err,true,true,false);
        b=false;
    }
    if(tiles==NULL) {
        debug_log::report("map with no tileset",err,true,true,false);
        b=false;
    }
    return b;
}

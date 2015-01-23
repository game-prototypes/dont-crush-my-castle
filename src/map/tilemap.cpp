//TITLE: TILEMAP_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.4
//DESCRIPTION: Generate,write,read and draw maps

#include "tilemap.h"

tilemap::tilemap() {
}
tilemap::tilemap(const string &name,const vector< vector<tile_id> > &background,const tileset *tiles) {
    this->tiles=tiles;
    this->name=name;
    set_background(background);
    if(background.size()>0) init_submatrix();
}
tilemap::tilemap(const vector< vector<tile_id> > &background,const tileset *tiles) {
    this->tiles=tiles;
    set_background(background);
    if(background.size()>0) init_submatrix();
    generate_foreground();
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
void tilemap::set_destiny(const vector< pair<unsigned int,unsigned int> > &destination) {
    if(!destination.empty()) update_path_map(destination);
}
bool tilemap::in_matrix(unsigned int x,unsigned int y)const {
    if(x<get_width() && y<get_height()) return true;
    else return false;
}
unsigned int tilemap::get_width() const {
    return background.size();
}
unsigned int tilemap::get_height() const {
    if(background.size()>0) return background[0].size();
    else return 0;
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
    else return null_tile_id;
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

int tilemap::get_path_value(unsigned int x,unsigned int y)const {
    if(in_matrix(x,y))
        return path_map[x][y];
    else return -1;
}

pair<unsigned int,unsigned int> tilemap::get_next_position(unsigned int x,unsigned int y) const {
    pair<unsigned int,unsigned int> res=make_pair(x,y);
    int min=get_path_value(x,y);
    if(get_path_value(x-1,y)<min && get_path_value(x-1,y)>-1) {
        min=get_path_value(x-1,y);
        res=make_pair(x-1,y);
    }
    if(get_path_value(x,y-1)<min && get_path_value(x,y-1)>-1) {
        min=get_path_value(x,y-1);
        res=make_pair(x,y-1);
    }
    if(get_path_value(x,y+1)<min && get_path_value(x,y+1)>-1) {
        min=get_path_value(x,y+1);
        res=make_pair(x,y+1);
    }
    if(get_path_value(x+1,y)<min && get_path_value(x+1,y)>-1) {
        min=get_path_value(x+1,y);
        res=make_pair(x+1,y);
    }
    return res;
}

void tilemap::draw_tilemap() const {
    int height=get_height();
    int width=get_width();
    float x=0,y=0;
    int tilew=tiles->get_tile_width();
    int tileh=tiles->get_tile_height();
    for(int i=0; i<width; i++) {
        x=0;
        for(int j=0; j<height; j++) {
            tiles->draw_tile(background[i][j],x,y);
            x+=tilew;
        }
        y+=tileh;
    }
}
bool tilemap::check() const {
    bool b=true;
    if(background.size()!=foreground.size() || background.size()!=path_map.size()) {
        debug_log::report("map matrix don't match(width)",err,true,true,false);
        b=false;
    }
    if(background.empty()==false)
        if(background[0].size()!=foreground[0].size() || background[0].empty() || path_map[0].empty() || background[0].size()!=path_map[0].size()) {
            debug_log::report("map matrix incorrect height",err,true,true,false);
            b=false;
        }
    if(tiles==NULL) {
        debug_log::report("map with no tileset",err,true,true,false);
        b=false;
    }
    for(unsigned int i=0; i<background.size(); i++) {
        if(background[i].size()!=get_height()) b=false;
        if(foreground[i].size()!=get_height()) b=false;
        if(path_map[i].size()!=get_height()) b=false;
    }
    return b;
}
//Private methods
void tilemap::init_submatrix() {
    unsigned int width=get_width();
    unsigned int height=get_height();
    foreground.clear();
    path_map.clear();
    foreground.reserve(height);
    path_map.reserve(height);
    vector<bool> v(height,false);
    vector<int> v2(height,-1);
    for(unsigned int i=0; i<width; i++) {
        foreground.push_back(v);
        path_map.push_back(v2);
    }
    generate_foreground();
}
void tilemap::update_path_map(const vector< pair<unsigned int,unsigned int> > &destination) {
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
                if(i!=j && i!=-j) {
                    int x=til.first+i;
                    int y=til.second+j;
                    if(x>=0 && y>=0) {
                        if(in_matrix(x,y)) {
                            if(get_tile_type(x,y)==road || (get_tile_type(x,y)==open_ground && empty_tile(x,y)==0)) {
                                int val=path_map[til.first][til.second]+1;
                                if(path_map[x][y]==-1 || path_map[x][y]>val) {
                                    left_tiles.push(make_pair(x,y)); //push tile if havent been updated yet
                                    path_map[x][y]=val;
                                }
                                //    else if(path_map[x][y]<val && path_map[x][y]!=-1){
                                //    path_map[x][y]=val;
                                // }
                            }
                        }
                    }
                }
            }
        }
    }
}
void tilemap::generate_foreground() {
    for(unsigned int i=0; i<background.size(); i++) {
        for(unsigned int j=0; j<background[0].size(); j++) {
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

void tilemap::set_background(const vector< vector<tile_id> > &back) {
    this->background=back;
    unsigned int max_siz=0;
    for(unsigned int i=0; i<background.size(); i++) {
        if(background[i].size()>max_siz) max_siz=background[i].size();
    }
    for(unsigned int i=0; i<background.size(); i++) {
        while(background[i].size()<max_siz)
            background[i].push_back(null_tile_id);
    }
}

/*   void tilemap::load_background(const Tmx::Layer *lay,int width,int height) {
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                background[i][j]=lay->GetTileTilesetIndex(i,j);
            }
        }
    }*/

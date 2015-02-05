//TITLE: TILEMAP_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: Generate,write,read and draw maps

#include "tilemap.h"

tilemap::tilemap() {
}
tilemap::tilemap(const string &name,const vector< vector<tile_id> > &background,const tileset *tiles,const set< pair<unsigned int,unsigned int> > &destination,const set< pair<unsigned int,unsigned int> > &spawners) {
    this->tiles=tiles;
    this->name=name;
    this->destination=destination;
    this->spawners=spawners;
    set_background(background);
    if(background.size()>0) {
        generate_foreground();
        update_path_map();
    }
}
tilemap::tilemap(const vector< vector<tile_id> > &background,const tileset *tiles,const set< pair<unsigned int,unsigned int> > &destination,const set< pair<unsigned int,unsigned int> > &spawners) {
    this->tiles=tiles;
    this->destination=destination;
    this->spawners=spawners;
    set_background(background);
    if(background.size()>0) {
        generate_foreground();
        update_path_map();
    }
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
tilemap::~tilemap() {
    clear();
}
void tilemap::clear() {
    name.clear();
    background.clear();
    foreground.clear();
    path_map.clear();
    spawners.clear();
    destination.clear();
}
void tilemap::occupy_tile(unsigned int x,unsigned int y) {
    if(in_matrix(x,y)==true) {
        foreground[x][y]=1;
        if(get_tile_type(x,y)==open_ground) update_path_map();
    }
}
void tilemap::occupy_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
    if(x+width>get_width()) width=get_width()-x;
    if(y+height>get_height()) height=get_height()-y;
    for(unsigned int i=0; i<width; i++) {
        for(unsigned int j=0; j<height; j++)
            foreground[x+i][y+j]=1;
    }
    if(get_tile_type(x,y)==open_ground)   update_path_map();
}
void tilemap::free_tile(unsigned int x,unsigned int y) {
    if(in_matrix(x,y)==true) {
        foreground[x][y]=0;
        if(get_tile_type(x,y)==open_ground)   update_path_map();
    }
}
void tilemap::free_section(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
    if(x+width>get_width()) width=get_width()-x;
    if(y+height>get_height()) height=get_height()-y;
    for(unsigned int i=0; i<width; i++) {
        for(unsigned int j=0; j<height; j++)
            foreground[x+i][y+j]=0;
    }
    if(get_tile_type(x,y)==open_ground)    update_path_map();
}
void tilemap::add_destiny(unsigned int x,unsigned int y) {
    if(in_matrix(x,y)) {
        destination.insert(make_pair(x,y));
        update_path_map();
    }
}
void tilemap::add_spawner(unsigned int x,unsigned int y) {
    if(in_matrix(x,y))
        spawners.insert(make_pair(x,y));
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
pair<unsigned int,unsigned int> tilemap::translate_position(double x,double y) const {
    unsigned int siz=get_tile_size();
    pair<unsigned int,unsigned int> res;
    if(x<0) x=0.0;
    if(y<0) y=0.0;
    x/=siz;
    y/=siz;
    res=make_pair((unsigned int) x,(unsigned int) y);
    if(res.first>get_width()) res.first=get_width();
    if(res.second>get_height()) res.second=get_height();
    return res;
}
pair<double,double> tilemap::translate_position(unsigned int x,unsigned int y) const {
    unsigned int siz=get_tile_size();
    double rx=(x*siz)+(siz/2);
    double ry=(y*siz)+(siz/2);
    return make_pair(rx,ry);
}
unsigned int tilemap::get_tile_size() const {
    return tiles->get_tile_size();
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
int tilemap::get_path_value_of_position(double x,double y) const {
    pair<unsigned int,unsigned int> p=translate_position(x,y);
    return get_path_value(p.first,p.second);
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
pair<double,double> tilemap::get_next_position(double x,double y) const {
    pair<unsigned int,unsigned int> p2=translate_position(x,y);
    p2=get_next_position(p2.first,p2.second);
    pair<double,double> p=translate_position(p2.first,p2.second);
    return p;
}
vector< pair<unsigned int,unsigned int> > tilemap::spawners_position() const {
    return vector< pair<unsigned int,unsigned int> > (spawners.begin(),spawners.end());
}
bool tilemap::in_path(unsigned int x,unsigned int y) const {
    if(in_matrix(x,y))
        if(path_map[x][y]>-1) return true;
    return false;
}
bool tilemap::can_build(unsigned int x,unsigned int y) const {
    bool b=true;
    if(!in_matrix(x,y)) b=false;
    else if(!empty_tile(x,y)) b=false;
    return b;
}
bool tilemap::check_path_if_build(unsigned int x,unsigned int y) {
    bool b=true;
    if(can_build(x,y)==true || get_tile_type(x,y)!=open_ground) b=true;
    else {
        occupy_tile(x,y);
        update_path_map();
        if(spawners_in_path()==false) b=false;
        free_tile(x,y);
        update_path_map();
    }
    return b;
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
    //if(spawners_in_path()==false) b=false;
    return b;
}
//Private methods


/*void tilemap::update_path_map(const vector< pair<unsigned int,unsigned int> > &destination) {
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
}*/

void tilemap::generate_foreground() {
    unsigned int width=get_width();
    unsigned int height=get_height();
    foreground.clear();
    foreground.reserve(width);
    vector<bool> v(height,false);
    for(unsigned int i=0; i<width; i++) {
        foreground.push_back(v);
        for(unsigned int j=0; j<height; j++) {
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
bool tilemap::spawners_in_path() const {
    bool b=true;
    pair<unsigned int,unsigned int> p;
    for(set< pair<unsigned int,unsigned int> >::const_iterator it=spawners.begin(); it!=spawners.end(); it++) {
        p=*it;
        if(path_map[p.first][p.second]==-1) {
            b=false;
            break;
        }
    }
    return b;
}

void tilemap::update_path_map() {
    path_map=vector< vector<int> >(get_width(),vector<int>(get_height(),-1));
    stack< pair<unsigned int,unsigned int> > left_tiles; //tiles left to check surroundings
    pair<unsigned int,unsigned int> til;
    for(set< pair<unsigned int,unsigned int> >::const_iterator it=destination.begin(); it!=destination.end(); it++) {
        til=*it;
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
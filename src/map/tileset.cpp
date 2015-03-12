//TITLE: TILESET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: Information about a set of tiles to be used on maps

#include "tileset.h"

//const tileset::tmx_tiletype_property="tiletype";

tileset::tileset() {
    tile_size=0;
    name="";
    lowest_free=0;
}
/*   tileset::tileset(const Tmx::Tileset *ts) {
           height=ts->GetTileHeight();
           width=ts->GetTileWidth();
           name=ts->GetName();
           add_tileset(ts);
       }*/

tileset::tileset(const string &name,const ALLEGRO_BITMAP *bitmap,const vector<tile::tile_type> &types,unsigned int tile_size,int ntiles) {
    set_name(name);
    lowest_free=0;
    this->tile_size=tile_size;
    load_from_bitmap(bitmap,types,tile_size,ntiles);
}
tileset::tileset(const ALLEGRO_BITMAP *bitmap,const vector<tile::tile_type> &types,unsigned int tile_size,int ntiles) {
    set_name("");
    lowest_free=0;
    this->tile_size=tile_size;
    load_from_bitmap(bitmap,types,tile_size,ntiles);
}
tileset::tileset(const string &name,const tile &t,unsigned int tile_size) {
    set_name(name);
    lowest_free=0;
    this->tile_size=tile_size;
    add_tile(t);
}
tileset::tileset(const tile &t,unsigned int tile_size) {
    set_name("");
    lowest_free=0;
    this->tile_size=tile_size;
    add_tile(t);
}
tileset::tileset(const tile &t) {
    set_name("");
    lowest_free=0;
    this->tile_size=t.size();
    add_tile(t);
}
tileset::~tileset() {
    name.clear();
    tile_list.clear();
}
tile_id tileset::add_tile(tile::tile_type type,const ALLEGRO_BITMAP *bitmap) {
    tile_list.insert(make_pair(lowest_free,tile(type,bitmap)));
    tile_id r=lowest_free;
    if(tile_size==0) tile_size=tile_list[r].size();
    else tile_list[r].resize(tile_size);
    lowest_free=get_next_free_id();
    return  r;
}
tile_id tileset::add_tile(const tile &t) {
    tile_list.insert(make_pair(lowest_free,t));
    tile_id r=lowest_free;
    if(tile_size==0) tile_size=tile_list[r].size();
    else tile_list[r].resize(tile_size);
    lowest_free=get_next_free_id();
    return  r;
}
vector<tile_id> tileset::load_from_bitmap(const ALLEGRO_BITMAP *bitmap,const vector<tile::tile_type> &types,unsigned int tile_size,int ntiles) {
    vector<ALLEGRO_BITMAP *> v=slice_bitmap(bitmap,tile_size,tile_size,ntiles); //slice the bitmap in small bitmaps
    vector<tile_id> vid;
    tile::tile_type type;
    if(v.size()==0) debug_log::report("loading bitmap with size=0",err,true,true,false);
    for(unsigned int i=0; i<v.size(); i++) {
        if(i<types.size()) type=types[i];
        else type=tile::null_tile; //defines each tile from vector, if there is not a tile_type, is null by default
        vid.push_back(add_tile(type,v[i])); //adds the tile to the tileset with id=i
    }
    return vid;
}
void tileset::remove_tile(tile_id id) {
    tile_list.erase(id);
    if(id<lowest_free) lowest_free=id;
}
void tileset::set_name(const string &name) {
    this->name=name;
}
bool tileset::is_tile(tile_id id) const {
    if(tile_list.find(id)!=tile_list.end()) return true;
    else return false;
}
unsigned int tileset::size() const {
    return tile_list.size();
}
unsigned int tileset::get_tile_width() const {
    return tile_size;
}
unsigned int tileset::get_tile_height() const {
    return tile_size;
}
unsigned int tileset::get_tile_size() const {
    return tile_size;
}
string tileset::get_name() const {
    return name;
}
tile::tile_type tileset::get_tile_type(tile_id id) const {
    tile::tile_type type=tile::null_tile;
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) type=it->second.type;
    return type;
}
void tileset::draw_tile(tile_id id,float x,float y) const {
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) it->second.draw(x,y);
}
void tileset::draw_resized_tile(tile_id id,float x,float y,unsigned int tile_size) const {
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) it->second.draw_resized(x,y,tile_size); //CHANGE!!!
}
void tileset::resize_tileset(unsigned int tile_size) {
    if(tile_size<=0) debug_log::report("resize tileset: new size not allowed (not resized)",err,true,true,false);
    else {
        this->tile_size=tile_size;
        map<tile_id,tile>::iterator it;
        for(it=tile_list.begin(); it!=tile_list.end(); it++) it->second.resize(tile_size);
    }
}

/*  void tileset::add_tmx_tileset(const Tmx::Tileset *ts) {
          if(name.empty()==true) name=ts->GetName();
          if(height==0 || width==0) {
              width=ts->GetTileWidth();
              height=ts->GetTileHeight();
          }
          else if(ts->GetTileWidth()!=width || ts->GetTileHeight()!=height) debug_log::report("not matching sizes on tileset,will resize bitmaps",warning,false,true,false);
          vector<Tmx::Tile *> tiles=ts->GetTiles();
          int siz=tiles.size();
          string imgpath=(ts->GetImage())->GetSource(); //image source path
          ALLEGRO_BITMAP *bitmap;
          bitmap=al_load_bitmap(imgpath.c_str()); //loads bitmap
          vector<ALLEGRO_BITMAP *> tileset_images=slice_bitmap(bitmap,width,height,siz); //slice bitmap
          al_destroy_bitmap(bitmap);
          //loads the tiles
          for(int i=0; i<siz; i++) {
              ALLEGRO_BITMAP *bmp=tileset_images[i]; //tile image
              int id=tiles[i]->GetId(); //tile id
              Tmx::PropertySet ps=tiles[i]->GetProperties();//tile properties
              string tt=ps.GetStringProperty(tmx_tiletype_property);
              tile_type t;
              if(tt=="blocked") t=blocked;
              else if(tt=="road") t=road;
              else if(tt=="ground") t=ground;
              else if(tt=="special") t=special;
              else t=null_tile;
              if(t==null_tile) debug_log::report("null tile parsed",err,true,false);
              if(add_tile(id,t,bmp)==false) {
                  al_destroy_bitmap(bmp);
              }
          }
          check();
      }*/
bool tileset::check() const {
    bool b=true;
    map<tile_id,tile>::const_iterator it;
    for(it=tile_list.begin(); it!=tile_list.end(); it++) {
        if(it->second.check()==false) b=false;
        if(it->second.size()!=tile_size) {
            debug_log::report("tile in tileset with different size",warning,true,false,false);
            b=false;
        }
    }
    if(lowest_free<=-1) b=false;
    return b;
}
//PRIVATE METHODS
tile_id tileset::get_next_free_id() const {
    map<tile_id,tile>::const_iterator it=tile_list.lower_bound(lowest_free);
    tile_id cid=it->first;
    it++;
    for(; it!=tile_list.end(); it++) {
        cid++;
        if(it->first!=cid) {
            return cid;
        }
    }
    cid++;
    return cid;
}


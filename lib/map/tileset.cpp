//TITLE: TILESET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Information about a set of tiles to be used on maps

#include "tileset.h"

//const tileset::tmx_tiletype_property="tiletype";

tileset::tileset() {
    tile_height=tile_width=0;
}
/*   tileset::tileset(const Tmx::Tileset *ts) {
           height=ts->GetTileHeight();
           width=ts->GetTileWidth();
           name=ts->GetName();
           add_tileset(ts);
       }*/

tileset::tileset(const string &name,ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int tile_width,unsigned int tile_height,int ntiles) {
    this->name=name;
    this->tile_height=tile_height;
    this->tile_width=tile_width;
    load_from_bitmap(bitmap,types,tile_width,tile_height,ntiles);
}
tileset::tileset(ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int tile_width,unsigned int tile_height,int ntiles) {
    name="";
    this->tile_height=tile_height;
    this->tile_width=tile_width;
    load_from_bitmap(bitmap,types,tile_width,tile_height,ntiles);
}
tileset::~tileset() {
    destroy_tileset();
}
unsigned int tileset::size() const {
    return tile_list.size();
}
tile tileset::get_tile(tile_id id) const {
    tile ret;
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) ret=it->second;
    return ret;
}
unsigned int tileset::get_tile_width() const {
    return tile_width;
}
unsigned int tileset::get_tile_height() const {
    return tile_height;
}
string tileset::get_name() const {
    return name;
}

void tileset::draw_tile(tile_id id,float x,float y) const {
    get_tile(id).draw(x,y);
}
void tileset::draw_resized_tile(tile_id id,float x,float y,unsigned int width,unsigned int height) const {
    get_tile(id).draw_resized(x,y,width,height);
}
void tileset::resize_tileset(unsigned int tile_width,unsigned int tile_height) {
    if(tile_width<=0 || tile_height<=0) debug_log::report("resize tileset: new size not allowed (not resized)",err,true,true,false);
    else {
        this->tile_width=tile_width;
        this->tile_height=tile_height;
        map<tile_id,tile>::iterator it;
        for(it=tile_list.begin(); it!=tile_list.end(); it++) it->second.resize(tile_width,tile_height);
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
void tileset::destroy_tileset() {
    name.clear();
    tile_height=tile_width=0;
    for(unsigned int i=0; i<tile_list.size(); i++) tile_list[i].destroy_bitmap();
    tile_list.clear();
}
//PRIVATE METHODS

bool tileset::add_tile(tile_id id,tile_type type,ALLEGRO_BITMAP *bitmap) {
    if((unsigned int)al_get_bitmap_height(bitmap)!=tile_height || (unsigned int)al_get_bitmap_width(bitmap)!=tile_width)
        resize_bitmap(bitmap,tile_width,tile_height);
    return  tile_list.insert(make_pair(id,tile(type,bitmap))).second;
}
void tileset::load_from_bitmap(ALLEGRO_BITMAP *bitmap,const vector<tile_type> &types,unsigned int twidth,unsigned int theight,int ntiles) {
    vector<ALLEGRO_BITMAP *> v=slice_bitmap(bitmap,twidth,theight,ntiles); //slice the bitmap in small bitmaps
    tile_type type;
    if(v.size()==0) debug_log::report("loading bitmap with size=0",err,true,true,false);
    for(unsigned int i=0; i<v.size(); i++) {
        if(i<types.size()) type=types[i];
        else type=null_tile; //defines each tile from vector, if there is not a tile_type, is null by default
        add_tile(i,type,v[i]); //adds the tile to the tileset with id=i
    }
    check();
}

void tileset::check() const {
}

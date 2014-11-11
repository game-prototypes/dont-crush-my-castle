//TITLE: TILESETS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Information about a set of tiles to be used on maps

enum tile_type {blocked,road,ground,special,null_tile};
const string tmx_tiletype_property="tiletype"; //defines the name of the property used on tmx for tiletype
/*tile_type:
block: blocked, not construction or enemies can pass
road: blocked for construction, enemies can pass
ground: free for construction
*/
class tile {
public:
    tile_type type;
private:
    ALLEGRO_BITMAP *bitmap;
public:
    tile() {
        type=null_tile;
    }
    tile(tile_type type,ALLEGRO_BITMAP *bitmap) {
        this->type=type;
        this->bitmap=bitmap;
    }

    ~tile() {
        al_destroy_bitmap(bitmap);
    }

    void draw(float x,float y) {
        al_draw_bitmap(bitmap,x,y,0);
    }
    void draw_resized(float x,float y,unsigned int width,unsigned int height) {
        if(width==0 || height==0) debug_log::report("tile size=0",err,true,false,false);
        else
            al_draw_scaled_bitmap(bitmap,0.0,0.0,al_get_bitmap_width(bitmap),al_get_bitmap_height(bitmap),x,y,width,height);

    }
};



#define tile_id int
class tileset {
private:
    map<tile_id,tile> tile_list;
    string name;
    int height;
    int width; //each tile height and width

public:
    tileset() {
        height=width=0;
    }
    /*   tileset(const Tmx::Tileset *ts) {
           height=ts->GetTileHeight();
           width=ts->GetTileWidth();
           name=ts->GetName();
           add_tileset(ts);
       }*/
    //gets a tile with given id
    tile get_tile(tile_id id) {
        tile ret;
        map<tile_id,tile>::const_iterator it;
        it=tile_list.find(id);
        if(it!=tile_list.end()) ret=it->second;
        return ret;
    }
    int get_tile_width() {
        return width;
    }
    int get_tile_height() {
        return height;
    }
    void clear() {
        name.clear();
        height=width=0;
        tile_list.clear();
    }
    void draw_tile(tile_id id,float x,float y) {
        get_tile(id).draw(x,y);
    }
    void draw_scaled_tile(tile_id id,float x,float y,unsigned int width,unsigned int height) {
        get_tile(id).draw_scaled(x,y,width,height);
    }

    //adds a tileset to the actual tileset (resizing bitmaps), name and sizes will remain unchanged
    //tiles with same id will not be inserted
    /*  void add_tmx_tileset(const Tmx::Tileset *ts) {
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


private:
    //return true if inserted, false if already exists
    bool add_tile(tile_id id,tile_type type,ALLEGRO_BITMAP *bitmap) {
        if(al_get_bitmap_height(bitmap)!=height || al_get_bitmap_width(bitmap)!=width)
            resize_bitmap(bitmap,width,height);
        return  tile_list.insert(make_pair(id,tile(type,bitmap))).second;
    }

    void check() {
    }
};

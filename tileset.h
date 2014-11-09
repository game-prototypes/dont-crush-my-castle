//TITLE: TILESETS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Information about a set of tiles to be used on maps

#include "lib/al_draw.h"

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
    int id;
private:
    ALLEGRO_BITMAP *bitmap;
public:
    tile(int id,tile_type type,ALLEGRO_BITMAP *bitmap) {
        this->type=type;
        this->bitmap=bitmap;
        this->id=id;
    }

    ~tile() {
        al_destroy_bitmap(bitmap);
    }

    void draw_tile(float x,float y) {
        al_draw_bitmap(bitmap,x,y,0);
    }
};




class tileset {
private:
    vector<tile> tile_list;
    string name;
    int height;
    int widht; //each tile height and width

public:
    tileset() {
        height=width=0;
    }
    //gets a tile with given id
    tile get_tile(unsigned int id) {
        return tile_list[id];
    }
    pair<int,int> get_tile_size() {
        return make_pair(width,height);
    }

    void loadtmx(const string &name) {
        Tmx::Tileset ts;
        ts.ParseFile(filename);
        if(ts.HasError()==false) {
            height=ts.GetTileHeight();
            width=ts.GetTileWidth();
            name=ts.GetName();

            vector<Tmx::Tile*> tiles=ts.GetTiles();
            int siz=tiles.size();

            string imgpath=ts.GetImage()->GetSource(); //image source path
            ALLEGRO_BITMAP *bitmap;
            bitmap=al_load_bitmap(imgpath.c_str()); //loads bitmap
            vector<ALLEGRO_BITMAP*> tileset_images=slice_bitmap(bitmap,width,height,siz);//slice bitmap
            al_destroy_bitmap(bitmap);

            //loads all the tiles
            tile_list.reserve(siz));
            for(int i=0; i<siz; i++) {
            ALLEGRO_BITMAP* bmp=tileset_images[i]; //tile image
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
                tile_list.push_back(tile(id,t,bmp));
            }
        }
        check();
    }


private:
    unsigned int add_tile(int id,tile_type type,ALLEGRO_BITMAP *bitmap) {
        if(al_get_bitmap_height(bitmap)!=height || al_get_bitmap_width(bitmap)!=width)
            resize_bitmap(bitmap,widht,height);
        tile_list.push_back(tile(id,type,bitmap));
        return tile_list.size()-1;
    }

    void check() {

    }
};

//TITLE: MAPS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Information about a set of tiles to be used on maps

#include "lib/al_draw.h"

enum tile_type {blocked,road,ground,special};
/*tile_type:
block: blocked, not construction or enemies can pass
road: blocked for construction, enemies can pass
ground: free for construction
            */
class tile {
public:
    tile_type type;
private:
    bool drawable;
    ALLEGRO_BITMAP *bitmap; //if any
public:
    tile(tile_type type,ALLEGRO_BITMAP *bitmap) {
        this->type=type;
        this->bitmap=bitmap;
        drawable=true;
    }
    tile(tile_type type) {
        drawable=false;
        this->type=type;
    }

    ~tile() {
        if(drawable)
            al_destroy_bitmap(bitmap);
    }


    void draw_tile(float x,float y) {
        if(drawable)
            al_draw_bitmap(bitmap,x,y,0);
    }
    bool is_drawable() {
        return drawable;
    }
};




class tileset {
private:
    vector<tile> tile_list;
    int height;
    int widht; //each tile height and width

public:

private:
    unsigned int add_tile(tile_type type,ALLEGRO_BITMAP *bitmap) {
        resize_bitmap(bitmap,widht,height);
        tile_list.push_back(tile(type,bitmap));
        return tile_list.size()-1;
    }
    unsigned int add_tile(tile_type type) {
        tile_list.push_back(tile(type));
        return tile_list.size()-1;
    }
    tile get_tile(unsigned int tileid) {
        return tile_list[tile];
    }
    pair<int,int> get_tile_size() {
        return make_pair(width,height);
    }
    bool check() {
        return true;
    }
};

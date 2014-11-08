//TITLE: TileMAPS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Generate,write,read and draw maps
#include "lib/TmxParser/Tmx.h"

struct position {
    int x;
    int y;
    position() {
        x=y=-1;
    }
    position(int x,int y) {
        this->x=x;
        this->y=y;
    }
};

class tilemap {
private:
    int width;
    int height;
    vector< vector<int> > background; //background (grass,roads...)
    vector< vector<int> > foreground; //buildings, objects...
    tileset *tiles;
public:
    tilemap() {
        width=0;
        height=0;
    }



    //Loads from tmx file
    void loadtmx(string filename) {
        Tmx::Map map;
        map.ParseFile(filename);
        if(map.HasError()==false) {
            int layers=map.GetNumLayers();
            //TODO
        }
    }

private:
    bool check() {
        bool b=true;
        return b;
    }


};

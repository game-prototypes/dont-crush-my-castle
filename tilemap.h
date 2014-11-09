//TITLE: TILEMAPS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Generate,write,read and draw maps
#include "lib/TmxParser/Tmx.h"
#define empty_tile 0
#define occupied_tile 1

class tilemap {
private:
    int width;
    int height;
    vector< vector<int> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
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
    void check() {

    }


};

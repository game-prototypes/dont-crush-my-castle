//TITLE: TILEMAPS
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Generate,write,read and draw maps

#define empty_tile 0
#define occupied_tile 1

class tilemap {
private:
    //   unsigned int width; //map size (in tiles)
    //   unsigned int height;

    vector< vector<tile_id> > background; //background (grass,roads...)
    vector< vector<bool> > foreground; //foreground (occupied tiles)
    tileset* tiles; //pointer to tileset
public:
    tilemap() {
    }


    //Loads from tmx file
    /*   void loadtmx(string filename) {
           Tmx::Map map;
           map.ParseFile(filename);
           if(map.HasError()==false) {
               //   int layers=map.GetNumLayers(); //we will use only first layer
               int width=map.GetWidth();
               int height=map.GetHeight();
               init_matrix(width,height);
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
    int get_height() {
        return background.size();
    }
    int get_width() {
        if(background.size()>0) return background[0].size();
        else return 0;
    }
    void draw_tilemap() {
        int height=get_height();
        int width=get_width();
        float x=0,y=0;
        int tilew=tiles->get_tile_width();
        int tileh=tiles->get_tile_height();
        for(int i=0; i<height; i++) {
            x=0;
            for(int j=0; j<width; j++) {
                draw_tile(background[i][j],x,y);
                x+=tilew;
            }
            y+=tileh;
        }


private:
        void check() {
            if(background.size()!=foreground.size()) debug_log::report("map matrix don't match(height)",err,true,true,false);
            if(background.size()>0 && foreground.size()>0 && background[0].size()!=foreground[0].size()) debug_log::report("map matrix don't match(width)",err,true,true,false);
        }

        void init_matrix(int width,int height) {
            foreground.clear();
            background.clear();
            foreground.resize(height);
            background.resize(height);
            vector<bool> v(width,empty_tile);
            for(int i=0; i<height; i++) {
                foreground.push_back(v);
                background.resize(width);
            }
        }
        /*   void load_background(const Tmx::Layer *lay,int width,int height) {
               for(int i=0; i<height; i++) {
                   for(int j=0; j<width; j++) {
                       background[i][j]=lay->GetTileTilesetIndex(i,j);
                   }
               }
           }*/


    };

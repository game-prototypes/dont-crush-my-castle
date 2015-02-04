//TITLE: DCmC Main
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: Main program of DCmC


#include "player_controller.h"
#include "game_master.h"
using namespace std;

//conf variables
unsigned int fps_conf=60; //frames per second
unsigned int screen_width=600;
unsigned int screen_height=600;
bool fullscreen=false;
//end conf

int main() {
    cout<<"DCmC V0.6 alpha\n";
    cout<<"===============\n";
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    al_init();
    al_init_image_addon();
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(screen_width,screen_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / fps_conf);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer); //start timer
    cout<<"Screen Size:"<<screen_width<<"x"<<screen_height<<endl;
    //GENEATE TILESET
    ALLEGRO_BITMAP *tilesetbmp=al_load_bitmap("resources/spr/ground_tileset_reduced.png");
    if(!tilesetbmp) {
        cout<<"error loading bitmap\n";
        exit(1);
    }
    vector<tile_type> tile_type_v;
    tile_type_v.push_back(road);
    tile_type_v.push_back(ground);
    tile_type_v.push_back(blocked);
    tileset tset("Ground tileset",tilesetbmp,tile_type_v,32);
    cout<<"Tileset Name:"<<tset.get_name()<<endl;
    cout<<"Tile Size:"<<tset.get_tile_size()<<endl;
    cout<<"Number of Tiles:"<<tset.size()<<endl;
    al_destroy_bitmap(tilesetbmp);
    tile_type_v.clear();
    //GENERATE MAP
    vector<vector<tile_id> > map_matrix(10,vector<tile_id>(10,1));
    for(unsigned int i=0; i<map_matrix[0].size(); i++) {
        map_matrix[5][i]=0;
    }
    set< pair<unsigned int,unsigned int> >  destinations;
    destinations.insert(make_pair(5,0));
    tilemap game_map("DCmC_map_1",map_matrix,&tset,destinations);
    cout<<"Map name:"<<game_map.get_name()<<endl;
    cout<<"Map Size:"<<game_map.get_width()<<"x"<<game_map.get_height()<<endl;
    tset.resize_tileset(screen_height/game_map.get_height());
    cout<<"Tileset resize to:"<<tset.get_tile_size()<<endl;
    destinations.clear();
    map_matrix.clear();
    bool redraw=true;
    while(true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)   //evento si se cierra pantalla
            break;
        if(event.type == ALLEGRO_EVENT_TIMER) { //evento de timer
            redraw = true;
        }
        if(redraw) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            game_map.draw_tilemap();
            al_flip_display();
        }
    }
    //destroy display,queue and timer
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}
//TITLE: DCmC Main
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: Main program of DCmC

#include "input_handler.h"
#include "player_controller.h"
#include "game_master.h"
using namespace std;

//conf variables
unsigned int fps_conf=60; //frames per second
unsigned int screen_width=600;
unsigned int screen_height=600;
bool fullscreen=false;
//end conf
string enemy_path="resources/spr/enemy_0/";
enemy_attributes create_enemy_0(const ALLEGRO_TIMER *timer);
tower_attributes create_tower_0(const ALLEGRO_TIMER *timer);
game_spawner create_game_spawner();

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
    cout<<"Screen Size:"<<screen_width<<"x"<<screen_height<<endl<<endl;
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
    if(tset.check()==false) cout<<"error in check\n";
    cout<<"\n";
    al_destroy_bitmap(tilesetbmp);
    tile_type_v.clear();
    //GENERATE MAP
    vector<vector<tile_id> > map_matrix(10,vector<tile_id>(10,1));
    for(unsigned int i=0; i<map_matrix[0].size(); i++) {
        map_matrix[5][i]=0;
    }
    map_matrix[5][5]=1;
    map_matrix[4][4]=0;
    map_matrix[4][5]=0;
    map_matrix[4][6]=0;
    set< pair<unsigned int,unsigned int> >  destinations,spawners;
    destinations.insert(make_pair(5,9));
    spawners.insert(make_pair(5,0));
    tilemap game_map("DCmC_map_1",map_matrix,&tset,destinations,spawners);
    cout<<"Map name:"<<game_map.get_name()<<endl;
    cout<<"Map Size:"<<game_map.get_width()<<"x"<<game_map.get_height()<<endl;
    cout<<"Spawners:";
    vector< pair<unsigned int,unsigned int> > spawners_in_map=game_map.spawners_position();
    for(unsigned int i=0; i<spawners_in_map.size(); i++) cout<<"["<<spawners_in_map[i].first<<","<<spawners_in_map[i].second<<"] ";
    cout<<endl;
    tset.resize_tileset(screen_height/game_map.get_height());
    cout<<"Tileset resize to:"<<tset.get_tile_size()<<endl;
    if(game_map.check()==false) cout<<"error in check\n";
    cout<<"\n";
    destinations.clear();
    map_matrix.clear();
    bool redraw=true;
    unsigned int seconds=0;
    unsigned int tt=0;
    enemy_set eset("Enemy_set_0",create_enemy_0(timer),timer);
    cout<<"Enemy Set Name:"<<eset.get_name()<<endl;
    cout<<"Enemy Set Size:"<<eset.get_size()<<endl;
    if(eset.check()==false) cout<<"error in check\n";
    cout<<endl;
    tower_set towerset("Tower_set_0",create_tower_0(timer),timer);
    cout<<"Tower Set Name:"<<towerset.get_name()<<endl;
    cout<<"Tower Set Size:"<<towerset.get_size()<<endl;
    if(towerset.check()==false) cout<<"error in check\n";
    cout<<endl;
    game_objects game_objects_0;
    game_spawner spawner_0=create_game_spawner();
    game_master master_0(eset,game_objects_0,game_map,spawner_0,timer);
    cout<<"Number of waves:"<<master_0.get_total_waves()<<endl;
    player_controller pc(towerset,game_objects_0,game_map);
    cout<<"player_controller can_build [330,330]:"<<pc.can_build(300.0,300.0)<<endl;
    pc.build_tower("tower_0",300,300);
    cout<<"player_controller can_build [330,330] (after build):"<<pc.can_build(300.0,300.0)<<endl;
    cout<<endl<<"Start Game\n";
    while(true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)   //evento si se cierra pantalla
            break;
        if(event.type==ALLEGRO_EVENT_TIMER) { //evento de timer
            redraw=true;
            tt++;
            if(tt==fps_conf) {
                tt=0;
                seconds++;
            }
        }
        if(redraw) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            game_map.draw_tilemap();
            master_0.update();
            game_objects_0.draw_enemies();
            game_objects_0.draw_towers();
            game_objects_0.draw_attacks();
            al_flip_display();
        }
        if(master_0.is_active()==false) break;
    }
    //destroy display,queue and timer
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}

enemy_attributes create_enemy_0(const ALLEGRO_TIMER *timer) {
    ALLEGRO_BITMAP *enemy_bitmap;
    enemy_attributes res("enemy_0",100,1,50,20);
    enemy_bitmap=al_load_bitmap(enemy_path+"idle.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(idle_anim,al_anim(enemy_bitmap,64,64,1,timer));
    al_destroy_bitmap(enemy_bitmap);
    enemy_bitmap=al_load_bitmap(enemy_path+"dead.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(dead_anim,al_anim(enemy_bitmap,64,64,2,timer));
    al_destroy_bitmap(enemy_bitmap);
    enemy_bitmap=al_load_bitmap(enemy_path+"up.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(up_anim,al_anim(enemy_bitmap,64,64,3,timer));
    al_destroy_bitmap(enemy_bitmap);
    enemy_bitmap=al_load_bitmap(enemy_path+"down.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(down_anim,al_anim(enemy_bitmap,64,64,3,timer));
    al_destroy_bitmap(enemy_bitmap);
    enemy_bitmap=al_load_bitmap(enemy_path+"left.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(left_anim,al_anim(enemy_bitmap,64,64,3,timer));
    al_destroy_bitmap(enemy_bitmap);
    enemy_bitmap=al_load_bitmap(enemy_path+"right.png");
    if(!enemy_bitmap) cout<<"error loading enemy bitmap\n";
    res.insert_animation(right_anim,al_anim(enemy_bitmap,64,64,3,timer));
    al_destroy_bitmap(enemy_bitmap);
    return res;
}
tower_attributes create_tower_0(const ALLEGRO_TIMER *timer) {
    ALLEGRO_BITMAP *atk_bitmap;
    ALLEGRO_BITMAP *exp_bitmap;
    ALLEGRO_BITMAP *tower_bitmap;
    atk_bitmap=al_load_bitmap("resources/spr/cannonball.png");
    if(!atk_bitmap) cout<<"error loading tower_atk bitmap\n";
    resize_bitmap(atk_bitmap,30,30);
    exp_bitmap=al_load_bitmap("resources/spr/explosion.png");
    if(!atk_bitmap) cout<<"error loading explosion bitmap\n";
    tower_bitmap=al_load_bitmap("resources/spr/tower_cartoon.png");
    if(!tower_bitmap) cout<<"error loading tower bitmap\n";
    al_anim explosion_anim(exp_bitmap,64,64,0.5,timer);
    al_destroy_bitmap(exp_bitmap);
    atk_attributes atk_0(atk_bitmap,explosion_anim,60,90,2,5,shoot_atk);
    return tower_attributes("tower_0",tower_bitmap,atk_0,100);
}
game_spawner create_game_spawner() {
    spawn_wave wav;
    wav.push(make_pair(1,"enemy_0"));
    vector<spawn_wave> v;
    v.push_back(wav);
    return  game_spawner(v,10);
}
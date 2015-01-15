//TITLE: Map Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: This cpp is for testing purposes only (test for debug_log,al_utils,tile,tileset and tilemap)
//compile with allegrog++  testenemy.cpp -I lib/utilities -I lib/map/ -I lib/enemy -Wall

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <cmath>
#include <stack>
using namespace std;
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "debug_log.h"
#include "al_utils.h"
#include "tile.h"
#include "tileset.h"
#include "tilemap.h"
#include "al_anim.h"
#include "enemy.h"
#include "enemyset.h"



int main() {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    // al_start(display,event_queue,timer);
    al_init(); //inicia allegro
    al_init_image_addon();  //inicia imagenes en allegro
    //  al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(640, 480);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); //creamos timer que limita los fps (1.0/60 segundos, es decir, 60 fps)
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_start_timer(timer);
    enemy_attributes enematt("paco",100,6,70);
    ALLEGRO_BITMAP *bmp=al_load_bitmap("sprites/down.png");
    enematt.insert_animation(down_anim,al_anim(bmp,64,76,0.3,timer));
    al_destroy_bitmap(bmp);
    bmp=al_load_bitmap("sprites/up.png");
    enematt.insert_animation(up_anim,al_anim(bmp,72,93,0.3,timer));
    al_destroy_bitmap(bmp);
    bmp=al_load_bitmap("sprites/left.png");
    enematt.insert_animation(left_anim,al_anim(bmp,67,91,0.3,timer));
    al_destroy_bitmap(bmp);
    bmp=al_load_bitmap("sprites/right.png");
    enematt.insert_animation(right_anim,al_anim(bmp,65,77,0.3,timer));
    al_destroy_bitmap(bmp);
    bmp=al_load_bitmap("sprites/idle.png");
    enematt.insert_animation(idle_anim,al_anim(bmp,68,93,0.3,timer));
    al_destroy_bitmap(bmp);
    bmp=al_load_bitmap("sprites/dead.png");
    enematt.insert_animation(dead_anim,al_anim(bmp,84,65,0.3,timer));
    al_destroy_bitmap(bmp);
    enemy_set testset("prueba",enematt,timer);
    // double x=0,y=0;
    cout<<testset.get_size()<<endl;
    enemy enem=testset.spawn_enemy("paco",1,100,300);
    enem.move_to(0,0);
    cout<<enem.get_life()<<"/"<<enem.get_max_life()<<"  "<<enem.get_destiny().first<<" "<<enem.get_destiny().second<<endl;
    while(true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if(event.type==ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0,0,0));
            enem.update();
            enem.draw();
            al_flip_display();
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}

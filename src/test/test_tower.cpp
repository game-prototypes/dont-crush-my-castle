//TITLE: Tower Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.4
/*DESCRIPTION: test of towers and buildings
This test will check:
tower_atk
tower
tower_set
*/

#include "tower.h"

int main() {
    cout<<"TOWER TEST";
    bool test_result=true;
    //ALLEGRO display,timer and queue pointers
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    //allegro startup with image addon
    al_init();
    al_init_image_addon();
    //Declaration and assign of display,event_queue and timer
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); //60 fps timer
    //register timer and events
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_start_timer(timer); //begin timer
    //btimap and animation
    ALLEGRO_BITMAP *bmp=al_load_bitmap("spr/example_clock.png");
    resize_bitmap(bmp,100,100);
    al_anim anim(bmp,50,50,2,timer);
    //TOWER ATK
    //atk_attributes attr(bmp,anim,10,8,2,0,shoot_atk);
    //if(attr.check()==false) test_result=false;
    //tower_atk atk(attr,make_pair(0,0),make_pair(5,5));
    //TOWER
    al_destroy_bitmap(bmp);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
   // if(test_result==true) cout<<" - OK\n";
   // else cout<<" - FAIL\n";
    cout<<" - NOT TESTED\n";
    return !test_result;
}
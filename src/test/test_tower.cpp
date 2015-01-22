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
    atk_attributes attr(bmp,anim,10,8,3,2,shoot_atk);
    if(attr.check()==false) test_result=false;
    tower_atk atk(attr,make_pair(0,0),make_pair(5,5),timer);
    if(atk.check()==false) test_result=false;
    if(atk.get_damage()!=10) test_result=false;
    if(atk.get_speed()!=2) test_result=false;
    if(atk.get_range()!=8) test_result=false;
    if(atk.get_type()!=shoot_atk) test_result=false;
    if(atk.is_active()==false) test_result=false;
    if(atk.hit()==true) test_result=false;
    if(atk.get_position()!=make_pair(0.0,0.0)) test_result=false;
    while(atk.hit()==false) {
        atk.update();
        if(atk.get_position()==make_pair(0.0,0.0) || atk.get_position().first>5.0 || atk.get_position().second>5.0) {
            test_result=false;
            break;
        }
    }
    if(atk.get_position()!=make_pair(5.0,5.0)) test_result=false;
    if(atk.is_active()==false) test_result=false;
    for(int i=0; i<5; i++) atk.update();
    if(atk.is_active()==true) test_result=true;
    if(atk.hit()==false) test_result=false;
    //TOWER
    

    
    al_destroy_bitmap(bmp);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return !test_result;
}
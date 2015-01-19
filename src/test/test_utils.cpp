//TITLE: Al_utils Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.3
/*DESCRIPTION: basic test of allegro utilities (src/utilities) for DCmC
This test will check:
al_utils
*/
#include "al_utils.h"
using namespace std;

int main() {
    cout<<"AL_UTILS TEST";
    //Final result of test, true if everything OK
    bool test_result=true;
    //ALLEGRO display,timer and queue pointers
    //ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    //allegro startup with image addon
    al_init();
    al_init_image_addon();
    //Declaration and assign of display,event_queue and timer
    //display = al_create_display(640, 480);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); //60 fps timer
    //register timer and display events
    //al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_start_timer(timer); //begin timer
    //load example bitmap
    ALLEGRO_BITMAP *bmp=al_load_bitmap("spr/example_clock.png");
    if(bmp==NULL) {
        cout<<" || ERROR - bitmap not loaded\n";
        test_result=false;
    }
    vector<ALLEGRO_BITMAP *> v;
    int x=al_get_bitmap_width(bmp);
    int y=al_get_bitmap_height(bmp);
    int x2=x*2;
    int y2=y*2;
    //Testing Resize
    resize_bitmap(bmp,x2,y2);
    if(al_get_bitmap_width(bmp)!=x2 || al_get_bitmap_height(bmp)!=y2) test_result=false;
    //Testing copy
    ALLEGRO_BITMAP *bmp2=copy_bitmap(bmp);
    if(bmp2==NULL || bmp==NULL) test_result=false;
    if(al_get_bitmap_width(bmp2)!=al_get_bitmap_width(bmp) || al_get_bitmap_height(bmp2)!=al_get_bitmap_height(bmp)) test_result=false;
    al_destroy_bitmap(bmp2);
    bmp2=copy_bitmap(bmp,x,y);
    if(bmp2==NULL || bmp==NULL) test_result=false;
    if(al_get_bitmap_width(bmp2)!=x || al_get_bitmap_height(bmp2)!=y) test_result=false;
    if(al_get_bitmap_width(bmp)!=x2 || al_get_bitmap_height(bmp)!=y2) test_result=false;
    al_destroy_bitmap(bmp2);
    //Testing Slice 1
    v=slice_bitmap(bmp,x,y2);
    if(v.size()!=2) test_result=false;
    for(unsigned int i=0; i<v.size(); i++) {
        if(v[i]==NULL) test_result=false;
        else {
            if(al_get_bitmap_width(v[i])!=x) test_result=false;
            if(al_get_bitmap_height(v[i])!=y2) test_result=false;
        }
        al_destroy_bitmap(v[i]);
    }
    v.clear();
    if(!v.empty()) test_result=false;
    //Testing Slice 2
    v=slice_bitmap(bmp,x,y,3);
    if(v.size()!=3) test_result=false;
    for(unsigned int i=0; i<v.size(); i++) {
        if(v[i]==NULL) test_result=false;
        else {
            if(al_get_bitmap_width(v[i])!=x) test_result=false;
            if(al_get_bitmap_height(v[i])!=y) test_result=false;
        }
        al_destroy_bitmap(v[i]);
    }
    v.clear();
    if(!v.empty()) test_result=false;
    //Testing convert speed
    double spd=42;
    double spd2=convert_speed(spd,timer);
    if(spd2/al_get_timer_speed(timer)!=spd) test_result=false;
    //Testing update_movement
    pair<double,double> p1,p2;
    p1=make_pair(0,0);
    p2=make_pair(29.5,29.5);//at given speed, it should get here in 1 second (tspeed frames)
    double tspeed=1/al_get_timer_speed(timer);
    for(int i=0; i<tspeed-1; i++) {
        p1=movement_update(p1,p2,spd2);
    }
    if(p2==p1) test_result=false;  //one frame left to get there
    p1=movement_update(p1,p2,spd2);
    if(p1!=p2) test_result=false; //now whe are here
    //draw centered not tested
    /*
    al_anim animtest(bmp,64,64,0.5,timer);
    animtest.start();
    double x=0,y=0;

    while(true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if(event.type==ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(1,1,1));
            animtest.update();
            animtest.draw(x,y);
            al_flip_display();
        }
    }
    animtest.destroy();*/
    al_destroy_bitmap(bmp);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    //al_destroy_display(display);
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return !test_result;
}
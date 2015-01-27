//TITLE: TEST_CONTROLLER
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: will test different game controllers
/*This test will check:
game_objects
*/

#include "game_objects.h"

int main() {
       cout<<"GAME CONTROLLERS TEST";
    bool test_result=true;
    //ALLEGRO display,timer and queue pointers
    ALLEGRO_TIMER *timer;
    //allegro startup with image addon
    al_init();
    al_init_image_addon();
    timer = al_create_timer(1.0 / 60); //60 fps timer
    al_start_timer(timer); //begin timer
    ALLEGRO_BITMAP *bmp=al_load_bitmap("spr/example_clock.png");
    resize_bitmap(bmp,100,100);



    al_destroy_bitmap(bmp);
    al_destroy_timer(timer);
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return !test_result;
}
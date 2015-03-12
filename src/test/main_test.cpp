//TITLE: Main Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: full test of DCmC,calling other tests

#include "input_handler.h"
#include "player_controller.h"
#include "game_master.h"
#include "text_handler.h"
using namespace std;
//ALLEGRO,timer and queue pointers
ALLEGRO_TIMER *timer;
const char *bitmap_path="resources/spr/example_clock.png";
const string font_path="resources/fonts/big_bottom_cartoon.ttf";

#include "test_utils.h"
#include "test_anim.h"
#include "test_map.h"
#include "test_enemy.h"
#include "test_tower.h"
#include "test_controller.h"


int main() {
    cout<<"DCmC Test\n";
    cout<<"0.7.4\n";
    cout<<"=========\n";
    bool test_result=true;
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    timer = al_create_timer(1.0 / 60); //60 fps timer
    al_start_timer(timer); //begin timer
    test_result=test_result && test_utilities();
    test_result=test_result && test_animation();
    test_result=test_result && test_map();
    test_result=test_result && test_enemy();
    test_result=test_result && test_tower();
    test_result=test_result && test_controller();
    al_destroy_timer(timer);
    cout<<"Final Result - ";
    if(test_result==true) cout<<"OK\n";
    else cout<<"FAIL\n";
    return !test_result;
}

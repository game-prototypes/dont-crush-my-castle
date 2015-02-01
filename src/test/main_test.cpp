//TITLE: Main Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: full test of DCmC,calling other tests


#include "player_controller.h"
#include "game_master.h"
using namespace std;

#include "test_utils.h"
#include "test_anim.h"
#include "test_map.h"
#include "test_enemy.h"
#include "test_tower.h"
#include "test_controller.h"

int main() {
    cout<<"DCmC Test\n";
    bool test_result=true;
    al_init();
    al_init_image_addon();
    test_result=test_result && test_utilities();
    test_result=test_result && test_animation();
    test_result=test_result && test_map();
    test_result=test_result && test_enemy();
    test_result=test_result && test_tower();
    test_result=test_result && test_controller();
    cout<<"Final Result - ";
    if(test_result==true) cout<<"OK\n";
    else cout<<"FAIL\n";
    return !test_result;
}
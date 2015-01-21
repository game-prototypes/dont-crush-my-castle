//TITLE: Enemy Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.4
//DESCRIPTION: test of enemies
/*This test will check:
enemy
enemyset
*/

#include "enemyset.h"

int main() {
    cout<<"ENEMY TEST";
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
    //ENEMY ATTRIBUTES
    enemy_attributes testenemy_attr("minion test",100,10,2,5);
    map<enemy_animation,al_anim> vanim;
    ALLEGRO_BITMAP *bmp=al_load_bitmap("spr/example_clock.png");
    resize_bitmap(bmp,100,100);
    al_anim anim(bmp,50,50,2,timer);
    al_destroy_bitmap(bmp);
    if(anim.size()!=4) test_result=false;
    vanim.insert(make_pair(idle_anim,anim));
    vanim.insert(make_pair(up_anim,anim));
    vanim.insert(make_pair(down_anim,anim));
    vanim.insert(make_pair(left_anim,anim));
    vanim.insert(make_pair(right_anim,anim));
    vanim.insert(make_pair(dead_anim,anim));
    testenemy_attr.animation=vanim;
    if(testenemy_attr.check()==false) test_result=false;
    //ENEMY
    enemy testenemy(testenemy_attr,1,0,0,timer);
    if(testenemy.get_name()!="minion test") test_result=false;
    if(testenemy.get_speed()!=2) test_result=false;
    if(testenemy.get_life()!=100) test_result=false;
    if(testenemy.get_max_life()!=100) test_result=false;
    if(testenemy.get_reward()!=5) test_result=false;
    if(testenemy.get_position()!=make_pair(0.0,0.0)) test_result=false;
    if(testenemy.get_destiny()!=make_pair(0.0,0.0)) test_result=false;
    if(testenemy.check()==false) test_result=false;
    if(testenemy.alive()==false || testenemy.spawned()==false) test_result=false;
    if(testenemy.idle()==false) test_result=false;
   if(testenemy.get_current_animation()!=idle_anim) test_result=false;
    testenemy.move_to(2,2);
    if(testenemy.get_position()!=make_pair(0.0,0.0)) test_result=false;
    if(testenemy.idle()==true) test_result=false;
    testenemy.update();
if(testenemy.get_current_animation()!=down_anim || testenemy.get_current_animation()!=right_anim) test_result=false;
   //cout<<endl<<testenemy.get_current_animation()<<endl;
   //FIXME
    if(testenemy.idle()==true) test_result=false;
    if(testenemy.get_position()==make_pair(0.0,0.0)) test_result=false;
    while(testenemy.idle()==false) testenemy.update();
    if(testenemy.get_position()!=make_pair(2.0,2.0)) test_result=false;

   /* testenemy.damage(109);
    if(testenemy.get_life()!=1) test_result=false;
    if(testenemy.alive()==false) test_result=false;
    testenemy.kill();
    if(testenemy.alive()==true); test_result=false;*/
    //test animations in enemy
    //test enemyset
    anim.destroy();
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return !test_result;
}
//TITLE: Enemy Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: test of enemies
/*This test will check:
enemy
enemyset
*/

#ifndef ENEMY_TEST
#define ENEMY_TEST

bool test_enemy() {
    cout<<"ENEMY TEST";
    bool test_result=true;
    //ENEMY ATTRIBUTES
    enemy_attributes testenemy_attr("minion test",100,10,2,5);
    map<enemy_animation,al_anim> vanim;
    ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_path);
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
    //testenemy_attr.write_xml("testenemy.xml");
    //ENEMY
    enemy testenemy(testenemy_attr,0,0,0,timer);
    if(testenemy.get_name()!="minion test") test_result=false;
    if(testenemy.get_speed()!=2) test_result=false;
    if(testenemy.get_life()!=100) test_result=false;
    if(testenemy.get_level()!=0) test_result=false;
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
    if(testenemy.get_current_animation()!=down_anim && testenemy.get_current_animation()!=right_anim) test_result=false;
    if(testenemy.idle()==true) test_result=false;
    if(testenemy.get_position()==make_pair(0.0,0.0)) test_result=false;
    while(testenemy.idle()==false) testenemy.update();
    if(testenemy.get_position()!=make_pair(2.0,2.0)) test_result=false;
    testenemy.damage(109);
    if(testenemy.get_life()!=1) test_result=false;
    if(testenemy.alive()==false) test_result=false;
    testenemy.kill();
    if(testenemy.alive()==true) test_result=false;
    if(testenemy.is_active()==false) test_result=false;
    if(testenemy.destiny_reached()!=1) test_result=false;
    if(testenemy.is_active()==true) test_result=false;
    //ENEMYSET
    enemy_set testset("Minions of darkness",testenemy_attr,timer);
    if(testset.get_name()!="Minions of darkness") test_result=false;
    if(testset.is_enemy("minion test")==false) test_result=false;
    if(testset.size()!=1) test_result=false;
    if(testset.check()==false) test_result=false;
    enemy testenemy2=testset.spawn_enemy("minion test",2,5.0,5.0);
    double inc=1+(2*level_ratio);
    if(testenemy2.get_name()!="minion test") test_result=false;
    if(testenemy2.get_speed()!=2) test_result=false;
    if(testenemy2.get_level()!=2) test_result=false;
    if(testenemy2.get_life()!=100*inc) test_result=false; //some of these may change in the future
    if(testenemy2.get_max_life()!=100*inc) test_result=false;
    if(testenemy2.get_reward()!=5*inc) test_result=false;
    if(testenemy2.get_position()!=make_pair(5.0,5.0)) test_result=false;
    if(testenemy2.get_destiny()!=make_pair(5.0,5.0)) test_result=false;
    if(testenemy2.check()==false) test_result=false;
    if(testenemy2.alive()==false || testenemy2.spawned()==false) test_result=false;
    if(testenemy2.is_active()==false) test_result=false;
    if(testenemy2.idle()==false) test_result=false;
    if(testenemy2.get_current_animation()!=idle_anim) test_result=false;
    testset.remove_enemy("minion test");
    if(testset.is_enemy("minion test")==true) test_result=false;
    if(testset.size()!=0 || testset.empty()==false) test_result=false;
    anim.destroy();
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}
#endif

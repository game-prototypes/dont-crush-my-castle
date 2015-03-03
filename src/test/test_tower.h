//TITLE: Tower Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
/*DESCRIPTION: test of towers and buildings
This test will check:
tower_atk
tower
tower_set
*/
#ifndef TOWER_TEST
#define TOWER_TEST

bool test_tower() {
    cout<<"TOWER TEST";
    bool test_result=true;
    //btimap and animation
    ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_path);
    resize_bitmap(bmp,100,100);
    al_anim anim(bmp,50,50,2,timer);
    //TOWER ATK
    atk_attributes attr(bmp,anim,10,8,3,2,shoot_atk);
    if(attr.check()==false) test_result=false;
    tower_atk atk(attr,make_pair(0,0),make_pair(5,5),timer);
    if(atk.check()==false) test_result=false;
    if(atk.is_valid()==false) test_result=false;
    atk.invalidate();
    if(atk.is_valid()==true) test_result=false;
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
    tower_attributes attr2("towerTest",bmp,attr,110);
    if(attr2.check()==false) test_result=false;
    if(attr2.get_width()!=(unsigned int)al_get_bitmap_width(bmp) || attr2.get_height()!=(unsigned int)al_get_bitmap_height(bmp)) test_result=false;
    tower towertest(attr2,0,0,timer);
    if(towertest.get_name()!="towerTest") test_result=false;
    if(towertest.get_cost()!=110) test_result=false;
    if(towertest.is_active()==false) test_result=false;
    if(towertest.check()==false) test_result=false;
    if(towertest.get_position()!=make_pair(0.0,0.0)) test_result=false;
    if(towertest.get_range()!=8) test_result=false;
    if(towertest.get_damage()!=10) test_result=false;
    if(towertest.get_attack_type()!=shoot_atk) test_result=false;
    if(towertest.can_attack()==true) test_result=false;
    for(unsigned int i=0; i<179; i++) towertest.update();
    if(towertest.can_attack()==true) test_result=false;
    towertest.update();
    if(towertest.can_attack()==false) test_result=false;
    if(towertest.in_range(make_pair(8.2,0.0))==true) test_result=false;
    if(towertest.in_range(make_pair(0.0,8.2))==true) test_result=false;
    if(towertest.in_range(make_pair(8.0,0.0))==false) test_result=false;
    if(towertest.in_range(make_pair(6.0,5.0))==false) test_result=false;
    if(towertest.in_range(make_pair(6.0,6.0))==true) test_result=false;
    atk=towertest.attack(make_pair(2.2,2.2));
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
        if(atk.get_position()==make_pair(0.0,0.0) || atk.get_position().first>2.2 || atk.get_position().second>2.2) {
            test_result=false;
            break;
        }
    }
    if(atk.get_position()!=make_pair(2.2,2.2)) test_result=false;
    if(atk.is_active()==false) test_result=false;
    for(int i=0; i<5; i++) atk.update();
    if(atk.is_active()==true) test_result=true;
    if(atk.hit()==false) test_result=false;
    //TOWER SET
    tower_set testset("test_tower_set",attr2,timer);
    if(testset.get_name()!="test_tower_set") test_result=false;
    if(testset.size()!=1) test_result=false;
    if((testset.get_towers_names()).size()!=1) test_result=false;
    if(testset.is_tower("towerTest")==false) test_result=false;
    if(testset.get_tower_cost("towerTest")!=110) test_result=false;
    if(testset.empty()==true) test_result=false;
    if(testset.check()==false) test_result=false;
    towertest=testset.spawn_tower("towerTest",1,1);
    if(towertest.get_name()!="towerTest") test_result=false;
    if(towertest.is_active()==false) test_result=false;
    if(towertest.check()==false) test_result=false;
    if(towertest.get_position()!=make_pair(1.0,1.0)) test_result=false;
    if(towertest.get_range()!=8) test_result=false;
    if(towertest.get_damage()!=10) test_result=false;
    if(towertest.get_attack_type()!=shoot_atk) test_result=false;
    if(towertest.can_attack()==true) test_result=false;
    for(unsigned int i=0; i<179; i++) towertest.update();
    if(towertest.can_attack()==true) test_result=false;
    towertest.update();
    if(towertest.can_attack()==false) test_result=false;
    testset.remove_tower("towerTest");
    if(testset.is_tower("towerTest")==true) test_result=false;
    if(testset.empty()==false) test_result=false;
    al_destroy_bitmap(bmp);
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}
#endif
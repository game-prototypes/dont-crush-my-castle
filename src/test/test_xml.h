//TITLE: XML Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.5
/*DESCRIPTION: basic test of allegro utilities (src/utilities) for DCmC
This test will check:
al_anim
*/
#ifndef XML_TEST
#define XML_TEST
bool test_xml() {
    bool test_result=true;
    //testing animation
    cout<<"XML TEST";
    XMLDocument document;
    if(document.LoadFile("resources/xml/animation_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *anim_element = document.RootElement();
        string element_name=anim_element->Name();
        if(element_name!="Al_Animation") test_result=false;
        else if(anim_element == nullptr) test_result=false;
        else {
            al_anim test_animation;
            if(test_animation.read_xml(anim_element,timer)==false) test_result=false;
            if(test_animation.duration()!=2) test_result=false;
            if(test_animation.is_active()==true) test_result=false;
            if(test_animation.get_frame()!=0) test_result=false;
            if(test_animation.size()!=6) test_result=false;
            if(test_animation.get_width()!=64 || test_animation.get_height()!=64) test_result=false;
            if(test_animation.check()==false) test_result=false;
            test_animation.destroy();
        }
    }
    document.Clear();
    if(document.LoadFile("resources/xml/enemy_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *enemy_element = document.RootElement();
        string element_name=enemy_element->Name();
        if(enemy_element == nullptr) test_result=false;
        else if(element_name!="Enemy") test_result=false;
        else {
            enemy_attributes test_enemy;
            if(test_enemy.read_xml(enemy_element,timer)==false) test_result=false;
            if(test_enemy.check()==false) test_result=false;
            if(test_enemy.name!="Enemy_0") test_result=false;
            if(test_enemy.speed!=50) test_result=false;
            if(test_enemy.max_life!=100) test_result=false;
            if(test_enemy.armor!=1) test_result=false;
            if(test_enemy.reward!=20) test_result=false;
            if(test_enemy.animation.size()!=6) test_result=false;
            test_enemy.destroy();
        }
    }
    document.Clear();
    if(document.LoadFile("resources/xml/atk_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *atk_element=document.RootElement();
        string element_name=atk_element->Name();
        if(atk_element==nullptr) test_result=false;
        else if(element_name!="Tower_Atk") test_result=false;
        else {
            atk_attributes test_tower_atk;
            if(test_tower_atk.read_xml(atk_element,timer)==false) test_result=false;
            if(test_tower_atk.check()==false) test_result=false;
            if(test_tower_atk.damage!=60) test_result=false;
            if(test_tower_atk.delay!=2) test_result=false;
            if(test_tower_atk.speed!=5) test_result=false;
            if(test_tower_atk.bitmap==false) test_result=false;
            if(test_tower_atk.type!=shoot_atk) test_result=false;
            test_tower_atk.destroy();
        }
    }
    document.Clear();
    if(document.LoadFile("resources/xml/tower_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *tower_element=document.RootElement();
        string element_name=tower_element->Name();
        if(tower_element==nullptr) test_result=false;
        else if(element_name!="Tower") test_result=false;
        else {
            tower_attributes test_tower;
            if(test_tower.read_xml(tower_element,timer)==false) test_result=false;
            if(test_tower.check()==false) test_result=false;
            if(test_tower.name!="Tower 0") test_result=false;
            if(test_tower.bitmap==nullptr) test_result=false;
            if(test_tower.cost!=50) test_result=false;
            test_tower.destroy();
        }
    }
    document.Clear();
    if(document.LoadFile("resources/xml/tower_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *tower_element=document.RootElement();
        string element_name=tower_element->Name();
        if(tower_element==nullptr) test_result=false;
        else if(element_name!="Tower") test_result=false;
        else {
            tower_attributes test_tower;
            if(test_tower.read_xml(tower_element,timer)==false) test_result=false;
            if(test_tower.check()==false) test_result=false;
            if(test_tower.name!="Tower 0") test_result=false;
            if(test_tower.bitmap==nullptr) test_result=false;
            if(test_tower.cost!=50) test_result=false;
            test_tower.destroy();
        }
    }
    document.Clear();
    if(document.LoadFile("resources/xml/tile_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *tileset_element=document.RootElement();
        string element_name=tileset_element->Name();
        if(tileset_element==nullptr) test_result=false;
        else if(element_name!="Tileset") test_result=false;
        else {
            tileset test_tileset;
            if(test_tileset.read_xml(tileset_element)==false) test_result=false;
            if(test_tileset.check()==false) test_result=false;
            if(test_tileset.size()!=3) test_result=false;
            if(test_tileset.get_name()!="Tileset 0") test_result=false;
            if(test_tileset.get_tile_size()!=32) test_result=false;
        }
    }
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}
#endif

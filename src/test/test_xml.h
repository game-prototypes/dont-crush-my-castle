//TITLE: XML Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: basic test for DCmC XML files

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
        document.Clear();
    }
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
        document.Clear();
    }
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
        document.Clear();
    }
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
        document.Clear();
    }
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
        document.Clear();
    }
    tileset test_tileset;
    if(document.LoadFile("resources/xml/tile_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *tileset_element=document.RootElement();
        string element_name=tileset_element->Name();
        if(tileset_element==nullptr) test_result=false;
        else if(element_name!="Tileset") test_result=false;
        else {
            if(test_tileset.read_xml(tileset_element)==false) test_result=false;
            if(test_tileset.check()==false) test_result=false;
            if(test_tileset.size()!=3) test_result=false;
            if(test_tileset.get_name()!="Tileset 0") test_result=false;
            if(test_tileset.get_tile_size()!=32) test_result=false;
        }
        document.Clear();
    }
    if(document.LoadFile("resources/xml/enemy_set_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *enemyset_element=document.RootElement();
        string element_name=enemyset_element->Name();
        if(enemyset_element==nullptr) test_result=false;
        else if(element_name!="Enemy_Set") test_result=false;
        else {
            enemy_set tset;
            if(tset.read_xml(enemyset_element,timer)==false) test_result=false;
            if(tset.check()==false) test_result=false;
            if(tset.get_name()!="Default Enemies") test_result=false;
            if(tset.size()!=2) test_result=false;
        }
        document.Clear();
    }
    if(document.LoadFile("resources/xml/tower_set_test.xml")!=XML_SUCCESS) test_result=false;
    else {
        XMLElement *towerset_element=document.RootElement();
        string element_name=towerset_element->Name();
        if(towerset_element==nullptr) test_result=false;
        else if(element_name!="Tower_Set") test_result=false;
        else {
            tower_set tset;
            if(tset.read_xml(towerset_element,timer)==false) test_result=false;
            if(tset.check()==false) test_result=false;
            if(tset.get_name()!="Default Towers") test_result=false;
            if(tset.size()!=2) test_result=false;
        }
        document.Clear();
    }
    if(test_result==true) {
        if(document.LoadFile("resources/xml/tilemap_test.xml")!=XML_SUCCESS) test_result=false;
        else {
            XMLElement *towermap_element=document.RootElement();
            string element_name=towermap_element->Name();
            if(towermap_element==nullptr) test_result=false;
            else if(element_name!="Map") test_result=false;
            else {
                tilemap test_map;
                if(test_map.read_xml(towermap_element,&test_tileset)==false) test_result=false;
                if(test_map.check()==false) test_result=false;
                if(test_map.get_name()!="Map 0") test_result=false;
                if(test_map.get_width()!=10 || test_map.get_height()!=10) test_result=false;
                if(test_map.spawners_position().size()!=1) test_result=false;
                if(test_map.get_path_value(5,9)!=0) test_result=false;
                if(test_map.get_tile_id(1,1)!=1 || test_map.get_tile_id(8,0)!=1) test_result=false;
                if(test_map.get_tile_id(5,5)!=1 || test_map.get_tile_id(5,0)!=0) test_result=false;
                if(test_map.get_tile_id(4,0)!=2 || test_map.get_tile_id(6,9)!=2) test_result=false;
            }
            document.Clear();
        }
        if(document.LoadFile("resources/xml/spawn_test.xml")!=XML_SUCCESS) test_result=false;
        else {
            XMLElement *spawn_element=document.RootElement();
            string element_name=spawn_element->Name();
            if(spawn_element==nullptr) test_result=false;
            else if(element_name!="Spawn") test_result=false;
            else {
                game_spawner test_spawner;
                if(test_spawner.read_xml(spawn_element)==false) test_result=false;
                else {
                    if(test_spawner.check()==false) test_result=false;
                    if(test_spawner.get_delay()!=10) test_result=false;
                    if(test_spawner.get_total_waves()!=2) test_result=false;
                    if(test_spawner.get_wave(0).size()!=2) test_result=false;
                    if(test_spawner.get_wave(1).size()!=1) test_result=false;
                }
            }
            document.Clear();
        }
    }
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}
#endif

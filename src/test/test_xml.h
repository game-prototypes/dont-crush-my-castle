//TITLE: XML Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
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
            al_anim test_animation(anim_element,timer);
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
        if(element_name!="Enemy") test_result=false;
        else if(enemy_element == nullptr) test_result=false;
        else {
        //    enemy_attributes test_enemy(enemy_element,timer);
        }
    }
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}



#endif

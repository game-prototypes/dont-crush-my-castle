//TITLE: Al_utils Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
/*DESCRIPTION: basic test of allegro utilities (src/utilities) for DCmC
This test will check:
al_utils
input_handler
game_object
*/
#ifndef UTILITIES_TEST
#define UTILITIES_TEST
void click_event_test(int button,unsigned int x,unsigned int y) {
    cout<<"button pressed:"<<button<<" position:"<<x<<"x"<<y<<endl;
}
void key_pressed_test(int keycode) {
    cout<<"key_pressed:"<<keycode<<endl;
}
bool test_utilities() {
    cout<<"AL_UTILS TEST";
    //Final result of test, true if everything OK
    bool test_result=true;
    //load example bitmap
    ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_path);
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
    //Testing get_frames
    if(get_frames(2,timer)!=120) test_result=false; //frames in 2 seconds should be 120 at 60 fps
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
    al_destroy_bitmap(bmp);
    //Testing handler
    ALLEGRO_EVENT_QUEUE *event_queue;
    event_queue = al_create_event_queue();
    input_handler handler_test(event_queue,click_event_test,key_pressed_test);
    if(handler_test.check()==false) test_result=false;
    if(handler_test.is_active()==false) test_result=false;
    //testing gameobject
    game_object gameobj;
    if(gameobj.check()==false) test_result=false;
    if(gameobj.get_position()!=make_pair(-1.0,-1.0)) test_result=false;
    gameobj.set_position(2,2);
    if(gameobj.get_position()!=make_pair(2.0,2.0)) test_result=false;
    if(gameobj.is_active()==true) test_result=false;
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}


#endif

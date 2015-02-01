//TITLE: Anim Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
/*DESCRIPTION: basic test of allegro utilities (src/utilities) for DCmC
This test will check:
al_anim
*/
#ifndef AL_ANIM_TEST
#define AL_ANIM_TEST


bool test_animation() {
    cout<<"AL_ANIM TEST";
    //Final result of test, true if everything OK
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
    //load example bitmap
    ALLEGRO_BITMAP *bmp=al_load_bitmap("spr/example_clock.png");
    if(bmp==NULL) {
        cout<<" || ERROR - bitmap not loaded";
        test_result=false;
    }
    //TESTING ANIMATION
    int x=al_get_bitmap_width(bmp);
    int y=al_get_bitmap_height(bmp);
    unsigned int x2=x/4;
    unsigned int y2=y/2;
    //animation test with 8 sprites, 0.4 seconds (10 fps)
    al_anim animtest(bmp,x2,y2,0.4,timer);
    al_destroy_bitmap(bmp);
    //TESTING ANIMATION DATA
    if(animtest.is_active()==true) test_result=false;
    if(animtest.get_frame()!=0) test_result=false;
    if(animtest.size()!=8) test_result=false;
    if(animtest.duration()!=0.4) test_result=false;
    if(animtest.fps()!=20) test_result=false;
    if(animtest.get_width()!=x2 || animtest.get_height()!=y2) test_result=false;
    //TESTING ANIMATION
    animtest.animation_loop(false);
    animtest.start();
    if(animtest.is_active()==false) test_result=false;
    if(animtest.get_frame()!=0) test_result=false;
    for(unsigned int i=0; i<24-1; i++) animtest.update();
    if(animtest.is_active()==false) test_result=false;
    if(animtest.get_frame()!=animtest.size()-1) test_result=false;
    animtest.update();
    if(animtest.is_active()==true) test_result=false;
    if(animtest.get_frame()!=animtest.size()-1) test_result=false;
    animtest.animation_loop(true);
    animtest.activate();
    if(animtest.is_active()==false || animtest.get_frame()!=animtest.size()-1) test_result=false;
    animtest.update();
    if(animtest.is_active()==false || animtest.get_frame()!=0) test_result=false;
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    animtest.destroy();
    if(animtest.size()>0) test_result=false;
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}
#endif
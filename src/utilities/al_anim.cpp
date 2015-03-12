//TITLE: AL_ANIM_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: defines a general animation with allegro as a set of bitmaps

#include "al_anim.h"

al_anim::al_anim() {
    animation_delay=0;
    current_delay=0;
    count=0;
    loop=true;
    active=false;
}
al_anim::al_anim(const XMLElement *animation_root,const ALLEGRO_TIMER *timer) {
    this->timer=timer;
    this->count=0;
    this->active=false;
    this->loop=true;
    if(!read_xml(animation_root)) {
        destroy();
    }
}
al_anim::al_anim(const vector<ALLEGRO_BITMAP *> bitmap_sheet,double duration,const ALLEGRO_TIMER *timer) {
    if(bitmap_sheet.empty()) debug_log::report("animation with no bitmaps",err,true,true,false);
    else {
        this->bitmap_set=bitmap_sheet;
        count=0;
        active=false;
        loop=true;
        set_duration(duration,timer);
    }
}
al_anim::al_anim(const ALLEGRO_BITMAP *bitmap_sheet,unsigned int width,unsigned int height,double duration,const ALLEGRO_TIMER *timer) {
    load_from_bitmap(bitmap_sheet,width,height);
    if(bitmap_set.empty()==false) {
        count=0;
        active=false;
        loop=true;
        set_duration(duration,timer);
    }
}
al_anim::~al_anim() {
}
bool al_anim::read_xml(const XMLElement *animation_root) {
    bool b=false;
    this->count=false;
    if(animation_root == nullptr) b=false;
    else if(animation_root->Value()!=anim_xml_value) b=false;
    else {
        b=true;
        const char *version=animation_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        const char *loop=animation_root->Attribute("Loop");
        if(loop!=nullptr) {
            string sloop=(string(loop));
            if(sloop=="true" || sloop=="1") this->loop=true;
            else if(sloop=="false" || sloop=="0") this->loop=false;
        }
        const XMLElement *width_element,*height_element,*duration_element;
        width_element=animation_root->FirstChildElement("Width");
        height_element=animation_root->FirstChildElement("Height");
        duration_element=animation_root->FirstChildElement("Duration");
        if(height_element==nullptr || width_element==nullptr || duration_element==nullptr) return false;
        int width,height,duration;
        if(width_element->QueryIntText(&width)!=XML_SUCCESS ||
                height_element->QueryIntText(&height)!=XML_SUCCESS ||
                duration_element->QueryIntText(&duration)!=XML_SUCCESS) return false;
        const XMLElement *sheet_path=animation_root->FirstChildElement("Bitmap Sheet");
        if(sheet_path==nullptr) return false;
        const char *bitmap_sheet=sheet_path->GetText();
        if(bitmap_sheet==nullptr) return false;
        ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_sheet);
        load_from_bitmap(bmp,width,height);
        if(bitmap_set.empty()==true) b=false;
        set_duration(duration,timer);
    }
    return b;
}
void al_anim::activate() {
    if(check()==true)
        active=true;
}
void al_anim::start() {
    count=0;
    current_delay=animation_delay;
    active=true;
}
void al_anim::pause() {
    active=false;
}
void al_anim::stop() {
    active=false;
    count=0;
    current_delay=animation_delay;
}
void al_anim::set_frame(unsigned int frame) {
    if(frame<size()) {
        count=frame;
        current_delay=animation_delay;
    }
}
void al_anim::set_duration(double seconds) {
    unsigned int frames=get_frames(seconds,timer);
    frames/=size();
    animation_delay=frames;
    if(animation_delay==0) {
        debug_log::report("animation speed too fast for timer, speed=refresh rate",warning,true,false,false);
        animation_delay=1;
    }
    current_delay=animation_delay;
}
void al_anim::set_duration(double seconds,const ALLEGRO_TIMER *timer) {
    this->timer=timer;
    set_duration(seconds);
}
void al_anim::animation_loop(bool loop) {
    this->loop=loop;
}
void al_anim::resize(unsigned int w,unsigned int h) {
    for(unsigned int i=0; i<bitmap_set.size(); i++) resize_bitmap(bitmap_set[i],w,h);
}
bool al_anim::is_active() const {
    return active;
}
unsigned int al_anim::get_frame() const {
    return count;
}
unsigned int al_anim::size() const {
    return bitmap_set.size();
}
double al_anim::duration()const {
    double tspeed=al_get_timer_speed(timer);
    return tspeed*animation_delay*size();
}
unsigned int al_anim::fps() const {
    double speed=al_get_timer_speed(timer);
    speed*=animation_delay;
    return 1/speed;
}
unsigned int al_anim::get_width() const {
    return al_get_bitmap_width(bitmap_set[count]);
}
unsigned int al_anim::get_height() const {
    return al_get_bitmap_height(bitmap_set[count]);
}
void al_anim::update() {
    if(active) {
        current_delay--;
        if(current_delay==0) { //change bitmap
            current_delay=animation_delay;  //resets delay
            count++;
            if(count==bitmap_set.size() && loop==false) {
                count--;
                current_delay=1;
                pause();
            }
            count%=bitmap_set.size();
        }
    }
}
void al_anim::draw(double x,double y) const {
    if(!bitmap_set.empty()) { //comprobation erased to improve performance ??
        draw_centered(bitmap_set[count],x,y);
    }
}

/*
void al_anim::draw_resized(double x,double y,unsigned int width,unsigned int height) const {
    if(width==0 || height==0) debug_log::report("tile size=0",err,true,false,false);
    else
        al_draw_scaled_bitmap(bitmap_set[count],0.0,0.0,al_get_bitmap_width(bitmap_set[count]),al_get_bitmap_height(bitmap_set[count]),x,y,width,height,0);
}*/
void al_anim::clear() {
    animation_delay=0;
    count=0;
    active=false;
    current_delay=0;
    bitmap_set.clear();
}
void al_anim::destroy() {
    for(unsigned int i=0; i<bitmap_set.size(); i++) {
        al_destroy_bitmap(bitmap_set[i]);
        bitmap_set[i]=nullptr;
    }
    clear();
}
bool al_anim::check() const {
    bool b=true;
    if(bitmap_set.empty()) debug_log::report("animation with no bitmaps",err,true,true,false);
    if(animation_delay==0) debug_log::report("animation with speed=0",err,true,true,false);
    return b;
}
void al_anim::load_from_bitmap(const ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height) {
    bitmap_set=slice_bitmap(bitmap,width,height); //slice the bitmap in small bitmaps
}

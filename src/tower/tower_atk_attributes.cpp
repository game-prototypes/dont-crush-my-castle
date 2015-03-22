//TITLE: TOWER_ATK_ATTRIBUTES_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: defines the kind of attack of buildings

#include "tower_atk_attributes.h"

atk_attributes::atk_attributes() {
    damage=range=delay=speed=0;
    type=shoot_atk;
    bitmap=nullptr;
}
atk_attributes::atk_attributes(const XMLElement *attributes_root,const ALLEGRO_TIMER *timer) {
    bitmap=nullptr;
    read_xml(attributes_root,timer);
}
atk_attributes::atk_attributes(ALLEGRO_BITMAP *bitmap,al_anim collision_anim,unsigned int damage,unsigned int range,unsigned int delay,double speed,atk_type type) {
    this->bitmap=bitmap;
    this->collision_anim=collision_anim;
    this->damage=damage;
    this->range=range;
    this->delay=delay;
    this->type=type;
    this->speed=speed;
}
atk_attributes::~atk_attributes() {
}
bool atk_attributes::read_xml(const XMLElement *atk_root,const ALLEGRO_TIMER *timer) {
    bool b=true;
    destroy();
    if(atk_root == nullptr) b=false;
    else if(atk_root->Value()!=tower_atk_xml_value) b=false;
    else {
        b=true;
        const char *version=atk_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        const XMLElement *damage_element,*range_element,*delay_element,*type_element,*speed_element;
        damage_element=atk_root->FirstChildElement("Damage");
        range_element=atk_root->FirstChildElement("Range");
        delay_element=atk_root->FirstChildElement("Delay");
        type_element=atk_root->FirstChildElement("Type");
        speed_element=atk_root->FirstChildElement("Speed");
        if(damage_element==nullptr || range_element==nullptr || delay_element==nullptr || type_element==nullptr || speed_element==nullptr) return false;
        if(damage_element->QueryUnsignedText(&damage)!=XML_SUCCESS ||
                range_element->QueryUnsignedText(&range)!=XML_SUCCESS ||
                delay_element->QueryDoubleText(&delay)!=XML_SUCCESS ||
                speed_element->QueryDoubleText(&speed)!=XML_SUCCESS) {
            return false;
        }
        const char *nam=type_element->GetText();
        string typ=string(nam);
        if(typ.empty()) return false;
        else if(typ=="Shoot") this->type=shoot_atk;
        else if(typ=="Explosion") this->type=explosion_atk;
        else if(typ=="Continuous") this->type=continuous_atk;
        else return false;
        const XMLElement *bmp_path=atk_root->FirstChildElement("Sprite");
        ALLEGRO_BITMAP *bmp=al_load_bitmap(bmp_path);
        if(!bmp) return false;
        this->bitmap=bmp;
        const XMLElement *collision_element=atk_root->FirstChildElement("Al_Animation");
        if(collision_element!=nullptr) { //it is possible to attack without animaton
            al_anim anim;
            if(anim.read_xml(collision_element,timer)==true) {
                this->collision_anim=anim;
            }
        }
    }
    return b;
}
bool atk_attributes::read_xml(const string &filename,const ALLEGRO_TIMER *timer) {
    XMLDocument document;
    XMLElement *element=get_root_element(filename,document);
    if(element==nullptr) return false;
    else return read_xml(element,timer);
}
void atk_attributes::clear() {
    damage=range=delay=0;
    type=shoot_atk;
    collision_anim.clear();
    bitmap=nullptr;
}
void atk_attributes::destroy() {
    al_destroy_bitmap(bitmap);
    bitmap=nullptr;
    collision_anim.destroy();
    clear();
}
bool atk_attributes::check() const {
    bool b=true;
    if(delay==0 && type!=continuous_atk) {
        debug_log::report("attack delay equals 0",warning,true,false,false);
        b=false;
    }
    if(range==0) {
        debug_log::report("attack range equals 0",warning,true,false,false);
        b=false;
    }
    if(damage==0) {
        debug_log::report("attack damage equals 0",warning,true,false,false);
        b=false;
    }
    if(bitmap==nullptr) b=false;
    if(speed<=0 || delay<=0) b=false;
    if(collision_anim.check()==false) b=false;
    return b;
}

//TITLE: ENEMY_ATTRIBUTES_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines each kind of enemy

#include "enemy_attributes.h"

enemy_attributes::enemy_attributes() {
    speed=max_life=armor=reward=0;
}
enemy_attributes::enemy_attributes(XMLElement *enemy_root,const ALLEGRO_TIMER *timer) {
    if(!read_xml(enemy_root,timer)) {
        destroy();
    }
}
enemy_attributes::enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,unsigned int reward) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    this->speed=enemy_speed;
    this->reward=reward;
}
enemy_attributes::enemy_attributes(const string &name,unsigned int life,unsigned int armor,double enemy_speed,const map<enemy_animation,al_anim> &animation,unsigned int rewatd) {
    this->name=name;
    this->max_life=life;
    this->armor=armor;
    this->animation=animation;
    this->speed=enemy_speed;
    this->reward=reward;
}
enemy_attributes::~enemy_attributes() {
}
bool enemy_attributes::read_xml(const XMLElement *enemy_root,const ALLEGRO_TIMER *timer) {
    bool b=false;
    if(enemy_root == nullptr) b=false;
    else if(enemy_root->Value()!=enemy_xml_value) b=false;
    else {
        b=true;
        const char *version=enemy_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        const XMLElement *name_element,*life_element,*armor_element,*speed_element,*reward_element;
        name_element=enemy_root->FirstChildElement("Name");
        life_element=enemy_root->FirstChildElement("Life");
        armor_element=enemy_root->FirstChildElement("Armor");
        speed_element=enemy_root->FirstChildElement("Speed");
        reward_element=enemy_root->FirstChildElement("Reward");
        if(name_element==nullptr || life_element==nullptr || armor_element==nullptr || speed_element==nullptr || reward_element==nullptr) return false;
        if(life_element->QueryUnsignedText(&max_life)!=XML_SUCCESS ||
                armor_element->QueryUnsignedText(&armor)!=XML_SUCCESS ||
                reward_element->QueryUnsignedText(&reward)!=XML_SUCCESS ||
                speed_element->QueryDoubleText(&speed)!=XML_SUCCESS) {
            return false;
        }
        const char *nam=name_element->GetText();
        this->name=string(nam);
        if(name.empty()) return false;
        const XMLElement *anim_element=enemy_root->FirstChildElement("Al_Animation");
        while(anim_element!=nullptr) {
            al_anim anim;
            if(anim.read_xml(anim_element)==false) return false;
            const char *type=anim_element->Attribute("type");
            if(type==nullptr) {
                anim.destroy();
                return false;
            }
            string typ=(type);
            enemy_animation anim_type;
            if(typ=="dead") anim_type=dead_anim;
            else if(typ=="left") anim_type=left_anim;
            else if(typ=="right") anim_type=right_anim;
            else if(typ=="up") anim_type=up_anim;
            else if(typ=="down") anim_type=down_anim;
            else if(typ=="idle") anim_type=idle_anim;
            else {
                anim.destroy();
                return false;
            }
            insert_animation(anim_type,anim);
            anim_element=anim_element->NextSiblingElement("Al_Animation");
        }
        if(animation.size()<6) return false;
    }
    return b;
}
/*bool enemy_attributes::write_xml(XMLElement *enemy_root) const {
    //THIS is only a small test, not to use!!!
    bool b=true;
       XMLDocument document;
        XMLElement *pRoot=document.NewElement("Enemy");
        pRoot->SetAttribute("Version","0.7.4");
        document.InsertFirstChild(pRoot);
        XMLElement *pElement = document.NewElement("Name");
        pElement->SetText(name.c_str());
        pRoot->InsertEndChild(pElement);
        pElement = document.NewElement("Life");
        pElement->SetText(max_life);
        pRoot->InsertEndChild(pElement);
        pElement = document.NewElement("Armor");
        pElement->SetText(armor);
        pRoot->InsertEndChild(pElement);
        pElement = document.NewElement("Speed");
        pElement->SetText(speed);
        pRoot->InsertEndChild(pElement);
        pElement = document.NewElement("Reward");
        pElement->SetText(reward);
        pRoot->InsertEndChild(pElement);
        XMLError eResult = document.SaveFile(filename.c_str());
    return b;
}*/
void enemy_attributes::insert_animation(enemy_animation type,const al_anim &anim) {
    if(anim.size()==0) debug_log::report("setting empty animation",err,true,true,false);
    else {
        animation.erase(type);
        animation.insert(make_pair(type,anim));
        animation[type].stop(); //set the animation to inactive and restart counters
    }
}
void enemy_attributes::clear() {
    animation.clear();
    name.clear();
    speed=0;
    max_life=0;
    armor=0;
}
void enemy_attributes::destroy() {
    map<enemy_animation,al_anim>::iterator it;
    for(it=animation.begin(); it!=animation.end(); it++)(it->second).destroy();
    clear();
}
bool enemy_attributes::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("enemy info without name",err,true,true,false);
        b=false;
    }
    if(animation.size()!=6) {
        debug_log::report("enemy without all necesssary animations",err,true,true,false);
        b=false;
    }
    if(speed<=0) {
        debug_log::report("enemy speed<=0",err,true,true,false);
        b=false;
    }
    if(max_life==0) {
        debug_log::report("enemy info with life=0",err,true,true,false);
        b=false;
    }
    return b;
}

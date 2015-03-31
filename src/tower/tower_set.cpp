//TITLE: TOWER_ATK_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: stores a set of towers

#include "tower_set.h"


tower_set::tower_set() {
}
tower_set::tower_set(const XMLElement *tower_set_root,const ALLEGRO_TIMER *timer) {
    read_xml(tower_set_root,timer);
}
tower_set::tower_set(const string &name,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
}
tower_set::tower_set(const string &name,const vector<tower_attributes> &tower_list,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    for(unsigned int i=0; i<tower_list.size(); i++)
        add_tower(tower_list[i]);
}
tower_set::tower_set(const string &name,const tower_attributes &tower_attr,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    add_tower(tower_attr);
}
tower_set::~tower_set() {
    name.clear();
    map<string,tower_attributes>::iterator it;
    for(it=towers.begin(); it!=towers.end(); it++)
        (it->second).destroy();
    clear();
}
bool tower_set::read_xml(const XMLElement *tower_set_root,const ALLEGRO_TIMER *timer) {
    bool b=false;
    set_timer(timer);
    if(tower_set_root == nullptr) b=false;
    else if(tower_set_root->Value()!=tower_set_xml_value) b=false;
    else {
        b=true;
        const char *version=tower_set_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        const XMLElement *name_element=tower_set_root->FirstChildElement("Name");
        if(name_element==nullptr) return false;
        const char *nam=name_element->GetText();
        this->name=string(nam);
        if(name.empty()) return false;
        const XMLElement *current_tower=tower_set_root->FirstChildElement("Tower");
        while(current_tower!=nullptr) {
            tower_attributes ctower;
            string txt;
            const char *ctext=current_tower->GetText();
            if(ctext!=nullptr) txt=string(ctext);
            if(txt.empty()) {
                if(ctower.read_xml(current_tower,timer)==true) {
                    add_tower(ctower);
                }
            }
            else {
                if(ctower.read_xml(txt,timer)==true) {
                    add_tower(ctower);
                }
            }
            current_tower=current_tower->NextSiblingElement("Tower");
        }
    }
    return b;
}
bool tower_set::read_xml(const string &filename,const ALLEGRO_TIMER *timer) {
    XMLDocument document;
    XMLElement *element=get_root_element(filename,document);
    if(element==nullptr) return false;
    else return read_xml(element,timer);
}
//MODIFICATION
void tower_set::set_name(const string &name) {
    this->name=name;
}
void tower_set::add_tower(const tower_attributes &info) {
    if(towers.insert(make_pair(info.name,info)).second==false) debug_log::report("already exists enemy with given name "+info.name,err,true,true,false);
}
void tower_set::set_timer(const ALLEGRO_TIMER *timer) {
    this->timer=timer;
}
void tower_set::remove_tower(const string &name) {
    towers.erase(name);
}
void tower_set::clear() {
    name.clear();
    towers.clear();
    timer=NULL;
}
string tower_set::get_name() const {
    return name;
}
unsigned int tower_set::size() const {
    return towers.size();
}
bool tower_set::empty() const {
    return towers.empty();
}
bool tower_set::is_tower(const string &name) const {
    if(towers.find(name)!=towers.end()) return true;
    else return false;
}
set<string> tower_set::get_towers_names() const {
    map<string,tower_attributes>::const_iterator it;
    set<string> names;
    for(it=towers.begin(); it!=towers.end(); it++) names.insert(names.end(),it->second.name);
    return names;
}
unsigned int tower_set::get_tower_cost(const string &name) const {
    map<string,tower_attributes>::const_iterator it;
    it=towers.find(name);
    if(it==towers.end()) {
        return 0;
    }
    else
        return it->second.cost;
}
tower tower_set::spawn_tower(const string &name,double posx,double posy) const {
    map<string,tower_attributes>::const_iterator it;
    it=towers.find(name);
    if(it==towers.end()) {
        debug_log::report("spawning non existing tower",err,true,true,false);
        return tower();
    }
    else
        return tower(it->second,posx,posy,timer);
}
bool tower_set::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("tower_set with no name",warning,true,false,false);
        b=false;
    }
    if(timer==NULL) {
        debug_log::report("timer not set",err,true,true,false);
        b=false;
    }
    return b;
}

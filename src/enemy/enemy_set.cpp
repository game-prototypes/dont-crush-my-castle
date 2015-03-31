//TITLE: ENEMY_SET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: stores all kinds of enemies and spawn instances of each enemy

#include "enemy_set.h"

//CONSTRUCTORS
enemy_set::enemy_set() {
}
enemy_set::enemy_set(const XMLElement *enemy_set_root,const ALLEGRO_TIMER *timer) {
    read_xml(enemy_set_root,timer);
}
enemy_set::enemy_set(const string &name,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
}
enemy_set::enemy_set(const string &name,const vector<enemy_attributes> &enemy_list,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    for(unsigned int i=0; i<enemy_list.size(); i++)
        add_enemy(enemy_list[i]);
}
enemy_set::enemy_set(const string &name,const enemy_attributes &enemy_att,const ALLEGRO_TIMER *timer) {
    set_name(name);
    set_timer(timer);
    add_enemy(enemy_att);
}
enemy_set::~enemy_set() {
    name.clear();
    map<string,enemy_attributes>::iterator it;
    for(it=enemies.begin(); it!=enemies.end(); it++)
        (it->second).destroy();
    clear();
}

bool enemy_set::read_xml(const XMLElement *enemy_set_root,const ALLEGRO_TIMER *timer) {
    bool b=false;
    set_timer(timer);
    if(enemy_set_root == nullptr) b=false;
    else if(enemy_set_root->Value()!=enemy_set_xml_value) b=false;
    else {
        b=true;
        const char *version=enemy_set_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        const XMLElement *name_element=enemy_set_root->FirstChildElement("Name");
        if(name_element==nullptr) return false;
        const char *nam=name_element->GetText();
        this->name=string(nam);
        if(name.empty()) return false;
        const XMLElement *current_enemy=enemy_set_root->FirstChildElement("Enemy");
        while(current_enemy!=nullptr) {
            enemy_attributes cenemy;
            string txt;
            const char *ctext=current_enemy->GetText();
            if(ctext!=nullptr) txt=string(ctext);
            if(txt.empty()) {
                if(cenemy.read_xml(current_enemy,timer)==true) {
                    add_enemy(cenemy);
                }
            }
            else {
                if(cenemy.read_xml(txt,timer)==true) {
                    add_enemy(cenemy);
                }
            }
            current_enemy=current_enemy->NextSiblingElement("Enemy");
        }
    }
    return b;
}
bool enemy_set::read_xml(const string &filename,const ALLEGRO_TIMER *timer) {
    XMLDocument document;
    XMLElement *element=get_root_element(filename,document);
    if(element==nullptr) return false;
    else return read_xml(element,timer);
}
//MODIFICATION
void enemy_set::set_name(const string &name) {
    this->name=name;
}
void enemy_set::add_enemy(const enemy_attributes &info) {
    if(enemies.insert(make_pair(info.name,info)).second==false) debug_log::report("already exists enemy with given name "+info.name,err,true,true,false);
}
void enemy_set::set_timer(const ALLEGRO_TIMER *timer) {
    this->timer=timer;
}
void enemy_set::remove_enemy(const string &name) {
    enemies.erase(name);
}
void enemy_set::clear() {
    enemies.clear();
    name.clear();
    timer=NULL;
}
//CONSULT
string enemy_set::get_name() const {
    return name;
}
unsigned int enemy_set::size() const {
    return enemies.size();
}
bool enemy_set::empty() const {
    return enemies.empty();
}
bool enemy_set::is_enemy(const string &name) const {
    if(enemies.find(name)!=enemies.end()) return true;
    else return false;
}
enemy enemy_set::spawn_enemy(const string &name,unsigned int level,double posx,double posy) {
    if(enemies.find(name)==enemies.end()) {
        debug_log::report("spawning non existing enemy",err,true,true,false);
        return enemy();
    }
    else
        return enemy(enemies[name],level,posx,posy,timer);
    return enemy();
}
bool enemy_set::check() const {
    bool b=true;
    if(name.empty()) {
        debug_log::report("enemy_set with no name",warning,true,false,false);
        b=false;
    }
    if(timer==NULL) {
        debug_log::report("timer not set",err,true,true,false);
        b=false;
    }
    return b;
}

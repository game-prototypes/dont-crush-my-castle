//TITLE: TILESET_CPP
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.6
//DESCRIPTION: Information about a set of tiles to be used on maps

#include "tileset.h"

tileset::tileset() {
    tile_size=0;
    name="";
    lowest_free=0;
}
tileset::tileset(const string &name,const ALLEGRO_BITMAP *bitmap,const vector<tile::tile_type> &types,unsigned int tile_size,int ntiles) {
    set_name(name);
    lowest_free=0;
    this->tile_size=tile_size;
    load_from_bitmap(bitmap,types,tile_size,ntiles);
}
tileset::tileset(const string &name,const tile &t,unsigned int tile_size) {
    set_name(name);
    lowest_free=0;
    this->tile_size=tile_size;
    add_tile(t);
}
tileset::tileset(const string &name,const tile &t) {
    set_name(name);
    lowest_free=0;
    this->tile_size=t.size();
    add_tile(t);
}
tileset::tileset(const XMLElement *tileset_root) {
    tile_size=0;
    name="";
    lowest_free=0;
    read_xml(tileset_root);
}
tileset::~tileset() {
    name.clear();
    tile_list.clear();
}
bool tileset::read_xml(const XMLElement *tileset_root) {
    bool b=true;
    if(tileset_root == nullptr) b=false;
    else if(tileset_root->Value()!=tileset_xml_value) b=false;
    else {
        b=true;
        const char *version=tileset_root->Attribute("Version");
        //Compare version!!!!
        if(version==nullptr) return false;
        bool resize=false;
        const char *res=tileset_root->Attribute("Resize");
        if(res!=nullptr) {
            string s(res);
            if(s=="True" || s=="true"||s=="1") resize=true;
        }
        int ntiles=-1;
        tileset_root->QueryIntAttribute("Number",&ntiles); //ntiles will be -1 if nothing found
        const XMLElement *name_element,*size_element,*bitmap_element,*types_element;
        name_element=tileset_root->FirstChildElement("Name");
        size_element=tileset_root->FirstChildElement("Size");
        bitmap_element=tileset_root->FirstChildElement("Bitmap");
        types_element=tileset_root->FirstChildElement("Tile_Types");
        if(name_element==nullptr || size_element==nullptr ||bitmap_element==nullptr || types_element==nullptr) return false;
        if(size_element->QueryUnsignedText(&tile_size)!=XML_SUCCESS) return false;
        const char *nam=name_element->GetText();
        this->name=string(nam);
        if(name.empty()) return false;
        const char *bitmap_p=bitmap_element->GetText();
        if(bitmap_p==nullptr) return false;
        ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_p);
        if(!bmp) return false;
        vector<tile::tile_type> types=get_xml_types(types_element);
        load_from_bitmap(bmp,types,tile_size,ntiles);
        al_destroy_bitmap(bmp);
        if(resize==true) resize_tileset(this->tile_size);
    }
    return b;
}
bool tileset::read_xml(const string &filename) {
    XMLDocument document;
    XMLElement *element=get_root_element(filename,document);
    if(element==nullptr) return false;
    else return read_xml(element);
}
tile_id tileset::add_tile(tile::tile_type type,const ALLEGRO_BITMAP *bitmap) {
    tile_list.insert(make_pair(lowest_free,tile(type,bitmap)));
    tile_id r=lowest_free;
    if(tile_size==0) tile_size=tile_list[r].size();
    else tile_list[r].resize(tile_size);
    lowest_free=get_next_free_id();
    return  r;
}
tile_id tileset::add_tile(const tile &t) {
    tile_list.insert(make_pair(lowest_free,t));
    tile_id r=lowest_free;
    if(tile_size==0) tile_size=tile_list[r].size();
    else tile_list[r].resize(tile_size);
    lowest_free=get_next_free_id();
    return  r;
}
vector<tile_id> tileset::load_from_bitmap(const ALLEGRO_BITMAP *bitmap,const vector<tile::tile_type> &types,unsigned int tile_size,int ntiles) {
    vector<ALLEGRO_BITMAP *> v=slice_bitmap(bitmap,tile_size,tile_size,ntiles); //slice the bitmap in small bitmaps
    vector<tile_id> vid;
    tile::tile_type type;
    if(v.size()==0) debug_log::report("loading bitmap with size=0",err,true,true,false);
    for(unsigned int i=0; i<v.size(); i++) {
        if(i<types.size()) type=types[i];
        else type=tile::null_tile; //defines each tile from vector, if there is not a tile_type, is null by default
        vid.push_back(add_tile(type,v[i])); //adds the tile to the tileset with id=i
    }
    return vid;
}
void tileset::remove_tile(tile_id id) {
    tile_list.erase(id);
    if(id<lowest_free) lowest_free=id;
}
void tileset::set_name(const string &name) {
    this->name=name;
}
bool tileset::is_tile(tile_id id) const {
    if(tile_list.find(id)!=tile_list.end()) return true;
    else return false;
}
unsigned int tileset::size() const {
    return tile_list.size();
}
unsigned int tileset::get_tile_width() const {
    return tile_size;
}
unsigned int tileset::get_tile_height() const {
    return tile_size;
}
unsigned int tileset::get_tile_size() const {
    return tile_size;
}
string tileset::get_name() const {
    return name;
}
tile::tile_type tileset::get_tile_type(tile_id id) const {
    tile::tile_type type=tile::null_tile;
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) type=it->second.type;
    return type;
}
void tileset::draw_tile(tile_id id,float x,float y) const {
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) it->second.draw(x,y);
}
void tileset::draw_resized_tile(tile_id id,float x,float y,unsigned int tile_size) const {
    map<tile_id,tile>::const_iterator it;
    it=tile_list.find(id);
    if(it!=tile_list.end()) it->second.draw_resized(x,y,tile_size); //CHANGE!!!
}
void tileset::resize_tileset(unsigned int tile_size) {
    if(tile_size<=0) debug_log::report("resize tileset: new size not allowed (not resized)",err,true,true,false);
    else if(tile_size) {
        this->tile_size=tile_size;
        map<tile_id,tile>::iterator it;
        for(it=tile_list.begin(); it!=tile_list.end(); it++) it->second.resize(tile_size);
    }
}
bool tileset::check() const {
    bool b=true;
    map<tile_id,tile>::const_iterator it;
    for(it=tile_list.begin(); it!=tile_list.end(); it++) {
        if(it->second.check()==false) b=false;
        if(it->second.size()!=tile_size) {
            debug_log::report("tile in tileset with different size",warning,true,false,false);
            b=false;
        }
    }
    if(lowest_free<=-1) b=false;
    return b;
}
//PRIVATE METHODS
tile_id tileset::get_next_free_id() const {
    map<tile_id,tile>::const_iterator it=tile_list.lower_bound(lowest_free);
    tile_id cid=it->first;
    it++;
    for(; it!=tile_list.end(); it++) {
        cid++;
        if(it->first!=cid) {
            return cid;
        }
    }
    cid++;
    return cid;
}
vector<tile::tile_type> tileset::get_xml_types(const XMLElement *types_element) {
    vector<tile::tile_type> types;
    if(types_element != nullptr)
        if((string)types_element->Value()=="Tile_Types") {
            const XMLElement *type_element=types_element->FirstChildElement("Type");
            while(type_element!=nullptr) {
                const char *nam=type_element->GetText();
                string typ=string(nam);
                if(typ.empty()==false) {
                    tile::tile_type new_type;
                    if(typ=="road") new_type=tile::road;
                    else if(typ=="ground") new_type=tile::ground;
                    else if(typ=="blocked") new_type=tile::blocked;
                    else if(typ=="open") new_type=tile::open_ground;
                    else if(typ=="special") new_type=tile::special;
                    else if(typ=="null") new_type=tile::null_tile;
                    else {
                        new_type=tile::null_tile;
                    }
                    types.push_back(new_type);
                }
                type_element=type_element->NextSiblingElement("Type");
            }
        }
    return types;
}

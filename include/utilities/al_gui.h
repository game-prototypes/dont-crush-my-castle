//TITLE: AL_GUI_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.8
//DESCRIPTION: defines a simple gui interface based on allegro 5

#ifndef AL_GUI
#define AL_GUI
class panel : public game_object{
private:
    pair<double,double> size;
    ALLEGRO_BITMAP *bitmap;
public:
    //CONSTRUCTORS
    panel(){
        set_position(-1,-1);
        set_size(-1,-1);
        bitmap=nullptr;
        set_active(false);
    }
    panel(ALLEGRO_BITMAP *bitmap,pair<double,double> position,pair<double,double> size){
        this->bitmap=bitmap;
        set_position(position);
        set_size(size);
        set_active=true;
    }
    //DESTRUCTOR
    ~panel(){
        destroy_bitmap(bitmap);
        deactivate();
    }
    //METHODS
    //changes size
    void set_size(pair<double,double> size){
        this->size=size;
    }
    //changes size
    void set_size(double width,double height){
        this->size=make_pair(width,height);
    }
    pair<double,double> get_size() const{
        return size;
    }
    //draw (scaled)
    void draw() const{
        draw_scaled(bitmap,position.first,position.second,size.first,size.second);
    }
    //does nothing
    void update(){

    }
};
//handles a button
class button : public game_object{
    string id;
    pair<double,double> size;
    ALLEGRO_BITMAP *bitmap;
    function<void(string)> button_clicked;
    //add text handler
public:
    //CONSTRUCTORS
    button(){
        id=nullptr;
        set_position(-1,-1);
        set_size(-1,-1);
        bitmap=nullptr;
        set_active(false);
    }
    button(ALLEGRO_BITMAP *bitmap,pair<double,double> position,pair<double,double> size){
        this->bitmap=bitmap;
        set_position(position);
        set_size(size);
        set_active=true;
    }
    //DESTRUCTOR
    ~panel(){
        destroy_bitmap(bitmap);
        deactivate();
    }
    //METHODS
    //changes size
    void set_size(pair<double,double> size){
        this->size=size;
    }
    //changes size
    void set_size(double width,double height){
        this->size=make_pair(width,height);
    }
    pair<double,double> get_size() const{
        return size;
    }
    //draw (scaled)
    void draw() const{
        draw_scaled(bitmap,position.first,position.second,size.first,size.second);
    }
    //does nothing
    void update(){

    }
};



#endif

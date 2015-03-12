//TITLE: AL_ANIM_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7.4
//DESCRIPTION: defines a general animation with allegro as a set of bitmaps

#ifndef AL_ANIM_H
#define AL_ANIM_H

#include "al_utils.h"
#include "tinyxml2.h"
using namespace tinyxml2;
const string anim_xml_value="Al Animation";
class al_anim {
private:
    vector<ALLEGRO_BITMAP *> bitmap_set;
    const ALLEGRO_TIMER *timer;
    unsigned int animation_delay; //delay in fotograms beetween bitmap change
    unsigned int count;
    unsigned int current_delay;
    bool active; //true to activate animation (false will pause it)
    bool loop; //if true, the animation will repeat, if not, it will stop in the last frame
public:
    //CONSTRUCTORS
    //default constructor
    al_anim();
    //contructor from XML element
    al_anim(const XMLElement *animation_root,const ALLEGRO_TIMER *timer);
    //full constructor for an al_anim, will set it to unactive by default,duration is the total duration of animation in seconds
    al_anim(const vector<ALLEGRO_BITMAP *> bitmap_sheet,double duration,const ALLEGRO_TIMER *timer);
    //loads animationa from one bitmap slicing it
    al_anim(const ALLEGRO_BITMAP *bitmap_sheet,unsigned int width,unsigned int height,double duration,const ALLEGRO_TIMER *timer);
    //destructor
    ~al_anim();
    //MODIFICATION
    bool read_xml(const XMLElement *animation_root);
    //checks animation and activates it
    void activate();
    //checks and activates animation from the beginning (like stop+activate)
    void start();
    //deactivate animation (paused)
    void pause();
    //deactivates the animation and resets counter
    void stop();
    //sets following frame to use (restarting current delay) if its inside bounds
    void set_frame(unsigned int frame);
    //set animation speed, given the duration in seconds (according to currently set timer), duration will change according to fps
    void set_duration(double seconds);
    //set duration and timer of animation
    void set_duration(double seconds,const ALLEGRO_TIMER *timer);
    //set loop value to true or false
    void animation_loop(bool loop);
    //resize all bitmaps
    void resize(unsigned int w,unsigned int h);

    //ACCESS
    //return true if animation is active
    bool is_active() const;
    //return current frame(count)
    unsigned int get_frame() const;
    //returns size of animation (number of frames)
    unsigned int size() const;
    //returns total duration of animation
    double duration() const;
    //return animation fps
    unsigned int fps() const;
    //return width of current bitmap
    unsigned int get_width() const;
    //return height of current bitmap
    unsigned int get_height() const;

    //updates current_delay if bitmap is active, if necessary, updates count
    //this method should be called once in each timer event (of the same timer given in set_animation_speed)
    void update();
    //DRAWING METHODS
    //draws the current bitmap (with flips if set to true)
    //note that draws centered animation
    void draw(double x,double y) const;
    //draw resized to given width and height
    //void draw_resized(double x,double y,unsigned int width,unsigned int height) const;
    //clear the animation(dont destroy bitmaps)
    void clear();
    //destroy all the bitmaps and clear the animation
    void destroy();
    bool check() const;
private:
    //slice the given bitmap into pieces of equal size for animation
    void load_from_bitmap(const ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height);
};

#endif

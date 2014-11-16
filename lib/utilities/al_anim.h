//TITLE: AL_ANIM_H
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: defines a general animation with allegro as a set of bitmaps

#ifndef AL_ANIM_H
#define AL_ANIM_H


class al_anim {
private:
    vector<ALLEGRO_BITMAP *> bitmap_set;
    unsigned int animation_delay; //delay in fotograms beetween bitmap change

    unsigned int count;
    unsigned int current_delay;
    bool active; //true to activate animation (false will pause it)
public:
    //CONSTRUCTORS
    //default constructor
    al_anim();
    //full constructor for an al_anim, will set it to unactive by default,duration is the total duration of animation in seconds
    al_anim(const vector<ALLEGRO_BITMAP *> bitmap_sheet,double duration,const ALLEGRO_TIMER *timer);
    //loads animationa from one bitmap slicing it
    al_anim(ALLEGRO_BITMAP *bitmap_sheet,unsigned int width,unsigned int height,double duration,const ALLEGRO_TIMER *timer);
    //MODIFICATION
    //checks animation and activates it
    void activate();
    //deactivate animation (paused)
    void pause();
    //deactivates the animation and resets counter
    void stop();
    //set animation speed, given the duration,returns animation_delay
    void set_duration(double seconds,const ALLEGRO_TIMER *timer);
    //returns size of animation (number of frames)
    unsigned int size()const;
    //returns total duration of animation
    double duration(const ALLEGRO_TIMER *timer)const;
    //return animation fps
    unsigned int fps(const ALLEGRO_TIMER *timer)const;
    //ACCESS
    //return true if animation is active
    bool is_active()const;
    //updates current_delay if bitmap is active, if necessary, updates count
    //this method should be called once in each timer event (of the same timer given in set_animation_speed)
    void update();
    //DRAWING METHODS
    //draws the current bitmap (with flips if set to true)
    void draw(double x,double y) const;
    //draw resized to given width and height
    void draw_resized(float x,float y,unsigned int width,unsigned int height) const;
    //destroy all the bitmaps and clear the animation
    void destroy();
private:
    //slice the given bitmap into pieces of equal size for animation
    void load_from_bitmap(ALLEGRO_BITMAP *bitmap,unsigned int width,unsigned int height);
    void check() const;
};
#endif

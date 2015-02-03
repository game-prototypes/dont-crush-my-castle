//TITLE: DCmC Main
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: Main program of DCmC


#include "player_controller.h"
#include "game_master.h"
using namespace std;

//conf variables
unsigned int fps_conf=60; //frames per second
unsigned int screen_width=800;
unsigned int screen_height=600;
bool fullscreen=false;
//end conf

int main() {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    al_init();
    al_init_image_addon();
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(screen_width,screen_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / fps_conf); //creamos timer que limita los fps (1.0/60 segundos, es decir, 60 fps)
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //para recibir eventos del timer
    al_start_timer(timer); //inicia el timer
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}
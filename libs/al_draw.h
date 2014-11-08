//TITLE: al_draw
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Generic methods for drawing and handdling allegro bitmaps


//resize bmp to given width and height (x and y), destroying the original bitmap
void resize_bitmap(ALLEGRO_BITMAP *&bmp,int x,int y) {
    ALLEGRO_BITMAP *temp;
    ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //actual display
    int origx=al_get_bitmap_width(bmp);
    int origy=al_get_bitmap_height(bmp);
    temp=al_create_bitmap(x,y); //the new bitmap with the given size
    al_set_target_bitmap(temp);
    al_draw_scaled_bitmap(bmp,0,0, origx, origy,0,0, x,y,0);//draw the original bitmap to the new one (resized)
    al_set_target_bitmap(disp); //returns the target to the display
    al_destroy_bitmap(bmp); //destroys the old bitmap
    bmp=temp; //bmp now points to the resized bitmap
}

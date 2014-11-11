//TITLE: al_utils
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Generic functions for drawing and handdling allegro bitmaps

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

//slice given bitmap in a vector of bitmaps, each birmap with given height and width (if ntiles>0, represents the max tiles to slice)
vector<ALLEGRO_BITMAP*> slice_bitmap(ALLEGRO_BITMAP *bitmap,int width,int height,int ntiles=-1) {
    ALLEGRO_BITMAP *disp=al_get_target_bitmap(); //actual display (stores for re-target)
    int x=al_get_bitmap_width(bitmap);
    int y=al_get_bitmap_height(bitmap);
    vector<ALLEGRO_BITMAP*> v;
    if(height>y || width>x) debug_log::report("impossible to slice bitmap",err,true,true);
    else {
        if(x%width!=0 || y%height) debug_log::report("slice section not exact",warning,true,false);
        int xtiles=x/width; //x tiles in bitmap
        int ytiles=y/height;//y tiles in bitmap
        x=y=0;
        for(int i=0; i<ytiles; i++) {
            for(int j=0; j<xtiles; j++) {
                if(ntiles>=0 && v.size()<ntiles) {
                    ALLEGRO_BITMAP *temp;
                    temp=al_create_bitmap(width,height);
                    al_set_target_bitmap(temp); //sets new bitmap as target
                    al_draw_bitmap_region(bitmap,x,y,width,height,0,0,0); //draw the region into the bitmap
                    v.push_back(temp); //adds bitmap to vector
                    x+=width;
                }
                else break;
            }
            x=0;
            y+=height;
        }

    }
    al_set_target_bitmap(disp); //returns target to original target
    return v;
}

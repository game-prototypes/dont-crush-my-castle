//TITLE: Map Test
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.7
//DESCRIPTION: test of DCmC for maps
/*This test will check:
tile
tileset
tilemap
*/
#ifndef MAP_TEST
#define MAP_TEST


void test_func(tile &t) {
    ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_path);
    tile tt(tile::road,bmp,80);
    t=tt;
}

bool test_map() {
    cout<<"TILEMAP TEST";
    //Final result of test, true if everything OK
    bool test_result=true;
    //load example bitmap
    ALLEGRO_BITMAP *bmp=al_load_bitmap(bitmap_path);
    if(bmp==NULL) {
        cout<<" || ERROR - bitmap not loaded";
        test_result=false;
    }
    //TESTING TILE
    //road tile with given bmp,512x512
    tile testtile(tile::road,bmp,512);
    if(testtile.check()==false) test_result=false;
    if(testtile.size()!=512) test_result=false;
    if(testtile.type!=tile::road) test_result=false;
    tile *testtile2=new tile(tile::ground,bmp,256);
    testtile=*testtile2;
    delete testtile2;
    if(testtile.size()!=256 || testtile.type!=tile::ground) test_result=false;
    test_func(testtile);
    if(testtile.size()!=80) test_result=false;
    //TESTING TILESET
    vector<tile::tile_type> types;
    types.push_back(tile::ground);
    types.push_back(tile::road);
    types.push_back(tile::road);
    types.push_back(tile::road);
    //tile set test with 4 tiles of 20x20
    tileset tset("test",bmp,types,20,4);
    if(tset.size()!=4) test_result=false;
    if(tset.get_name()!="test") test_result=false;
    if(tset.get_tile_width()!=20) test_result=false;
    if(tset.add_tile(testtile)!=4) test_result=false;
    if(tset.is_tile(4)==false || tset.is_tile(5)==true) test_result=false;
    if(tset.size()!=5) test_result=false;
    tset.remove_tile(2);
    if(tset.size()!=4) test_result=false;
    if(tset.add_tile(tile::ground,bmp)!=2) test_result=false;
    if(tset.size()!=5) test_result=false;
    vector<tile_id> v2=tset.load_from_bitmap(bmp,types,25,4);
    if(tset.size()!=9) test_result=false;
    if(v2.size()!=4) test_result=false;
    for(unsigned int i=0; i<v2.size(); i++)
        if(v2[i]!=(int) i+5) test_result=false;
    if(tset.check()==false) test_result=false;
    tileset tset2(testtile,12);
    if(tset2.get_tile_width()!=12) test_result=false;
    if(tset2.size()!=1) test_result=false;
    tileset tset3(testtile);
    if(tset3.size()!=1) test_result=false;
    if(tset3.get_tile_width()!=80) test_result=false;
    //TESTING MAP
    vector<tile_id> row;
    row.push_back(2);//ground
    row.push_back(1);//road
    row.push_back(3);//road
    vector<vector<tile_id> > mapids;
    mapids.push_back(row);
    mapids.push_back(row);
    mapids.push_back(row);
    mapids.push_back(row);
    /*Map (with the tset "test)
    2 2 2 2
    1 1 1 1
    3 3 3 3
    */
    //i=vertical
    //j=horizontal
    set<pair<unsigned int,unsigned int> > dest,spaw;
    dest.insert(make_pair(0,2));
    spaw.insert(make_pair(1,0));
    tilemap testmap("testing map",mapids,&tset,dest,spaw);
    if(testmap.get_name()!="testing map") test_result=false;
    if(testmap.get_width()!=4 || testmap.get_height()!=3) test_result=false;
    if(testmap.get_tile_size()!=20) test_result=false;
    if(testmap.spawners_position().size()!=1) test_result=false;
    if(testmap.translate_position(0.0,0.0)!=make_pair((unsigned int)0,(unsigned int)0)) test_result=false;
    if(testmap.translate_position(-10.0,-5.0)!=make_pair((unsigned int)0,(unsigned int)0)) test_result=false;
    if(testmap.translate_position(1000.0,1000.0)!=make_pair((unsigned int)4,(unsigned int)3)) test_result=false;
    if(testmap.translate_position(25.0,15.0)!=make_pair((unsigned int)1,(unsigned int)0)) test_result=false;
    if(testmap.check()==false) test_result=false;
    testmap.occupy_tile(1,1);
    if(testmap.empty_section(0,0,4,1)==false) test_result=false;
    if(testmap.empty_section(1,0,1,2)==true) test_result=false;
    //TESTING BACKGROUND && foreground
    for(unsigned int i=0; i<testmap.get_width(); i++) {
        for(unsigned int j=0; j<testmap.get_height(); j++) {
            if(testmap.get_tile_id(i,j)!=mapids[i][j]) test_result=false;
            if(testmap.get_tile_type(i,j)==tile::road && j==0) test_result=false;
            if(testmap.get_tile_type(i,j)==tile::ground && j!=0) test_result=false;
            if(testmap.empty_tile(i,j)==true && j!=0 && (i!=1 && j!=1)) test_result=false;
            if(testmap.empty_tile(i,j)==false && j==0) test_result=false;
        }
    }
    vector<tile_id> row2;
    row2.push_back(3);//road
    vector<vector<tile_id> > mapids2;
    mapids2.push_back(row);
    mapids2.push_back(row2);
    /*
    2 3
    1 -
    3 -
    */
    tilemap testmap2("testing map2",mapids2,&tset,dest,spaw);
    if(testmap2.get_name()!="testing map2") test_result=false;
    if(testmap2.get_width()!=2 || testmap2.get_height()!=3) test_result=false;
    if(testmap2.check()==false) test_result=false;
    for(unsigned int i=0; i<testmap2.get_width(); i++) {
        for(unsigned int j=0; j<testmap2.get_height(); j++) {
            if(testmap2.get_tile_id(i,j)!=null_tile_id && i==1 && j>=1) test_result=false;
        }
    }
    //CHECK PATH
    if(testmap2.in_path(0,1)==false) test_result=false;
    if(testmap.check()==false) test_result=false;
    if(testmap.get_path_value(0,2)!=0) test_result=false;
    if(testmap.get_path_value_of_position(5,46)!=0) test_result=false;
    for(unsigned int i=0; i<testmap.get_width(); i++) {
        if(testmap.get_path_value(i,0)!=-1) test_result=false;
    }
    for(unsigned int i=0; i<testmap.get_width(); i++) {
        if(testmap.get_path_value(i,1)!=(int) i+1) test_result=false;
    }
    for(unsigned int i=0; i<testmap.get_width(); i++) {
        if(testmap.get_path_value(i,2)!=(int) i) test_result=false;
    }
    pair<unsigned int,unsigned int> pos=make_pair(3,1);
    for(int i=3; i>=0; i--) {
        pos=testmap.get_next_position(pos.first,pos.second);
        if(testmap.get_path_value(pos.first,pos.second)!=i) test_result=false;
    }
    pos=testmap.get_next_position(pos.first,pos.second);
    if(testmap.get_path_value(pos.first,pos.second)!=0) test_result=false;
    if(pos!=make_pair((unsigned int)0,(unsigned int)2)) test_result=false;
    //TODO: test map with different row (different size)
    //test background,foreground and path map
    if(test_result==true) cout<<" - OK\n";
    else cout<<" - FAIL\n";
    return test_result;
}

#endif

#Don't Crush my Castle Makefile v0.4
#by demiurgosoft
#Just type make to compile project (currently compiling tests)
#make test: compile tests
#make clean: clean directories (removing binaries and objects)
#make astyle: astyle format to all .cpp and .h files (needs astyled installed)
#make print-%: shows % variable (if makefile crashes, for testing)


#FLAGS
CXX = g++
CPPFLAGS= -Wall -O1 #-g
ALLEGROFLAGS=-lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image -lallegro_main -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_memfile -lallegro_physfs -lallegro_primitives
#DIR
IDIR=include
ODIR=obj
SDIR=src
BDIR=bin

UTILSDIR=utilities
MAPDIR=map
ENEMYDIR=enemy
TOWERDIR=tower

_INC=$(UTILSDIR) $(MAPDIR) $(ENEMYDIR) $(TOWERDIR)
INC=$(patsubst %,$(IDIR)/%,$(_INC))
I_INC=$(patsubst %,-I %,$(INC))

_AL_UTILS=al_anim.cpp al_utils.cpp debug_log.cpp
AL_UTILS_O=$(patsubst %,$(ODIR)/%,$(_AL_UTILS:.cpp=.o))
_MAP=tile.cpp tileset.cpp tilemap.cpp
MAP_O=$(patsubst %,$(ODIR)/%,$(_MAP:.cpp=.o))
_ENEMY=enemy.cpp enemy_set.cpp
ENEMY_O=$(patsubst %,$(ODIR)/%,$(_ENEMY:.cpp=.o))
_TOWER=tower_atk.cpp tower.cpp tower_set.cpp
TOWER_O=$(patsubst %,$(ODIR)/%,$(_TOWER:.cpp=.o))

_TEST_UTILS=al_utils.o debug_log.o test_utils.o
TEST_UTILS_O=$(patsubst %,$(ODIR)/%,$(_TEST_UTILS))
TEST_ANIM_O=$(AL_UTILS_O) $(ODIR)/test_anim.o 
TEST_MAP_O=$(AL_UTILS_O) $(MAP_O) $(ODIR)/test_map.o
TEST_ENEMY_O=$(AL_UTILS_O) $(ENEMY_O) $(ODIR)/test_enemy.o
TEST_TOWER_O=$(AL_UTILS_O) $(TOWER_O) $(ODIR)/test_tower.o

.PHONY: all
all: test

#Compile tests
bin/test_utils: $(TEST_UTILS_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC)  $(ALLEGROFLAGS)
bin/test_anim: $(TEST_ANIM_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC)  $(ALLEGROFLAGS)
bin/test_map: $(TEST_MAP_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC)  $(ALLEGROFLAGS)
bin/test_enemy: $(TEST_ENEMY_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC)  $(ALLEGROFLAGS)
bin/test_tower: $(TEST_TOWER_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC)  $(ALLEGROFLAGS)
#compile a generic .o
obj/%.o: $(SDIR)/*/%.cpp $(INC)
	$(CXX) -c -o $@ $< $(I_INC) $(CPPFLAGS)

#Creates directories if dont exists
$(BDIR)/:
	mkdir $(BDIR)
$(ODIR)/:
	mkdir $(ODIR)
	
	
	
#compile tests binaries
.PHONY: test
test: $(BDIR) $(ODIR)  bin/test_utils bin/test_anim bin/test_map bin/test_enemy bin/test_tower
#astyle for all code (.cpp and .h)
.PHONY: astyle
astyle:
	astyle --style=attach --break-closing-brackets --align-pointer=name --delete-empty-lines --indent-col1-comments --unpad-paren -n -Q $(IDIR)/*/*.h $(SDIR)/*/*.cpp
#print variable
.PHONY: print-%
print-%  : ; @echo $* = $($*)
#clean obj and bin directories as well as *~ files
.PHONY: clean
clean:
	rm -r -f $(BDIR) $(ODIR) *~ $(SDIR)/*/*~ $(IDIR)/*/*~

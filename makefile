#Don't Crush my Castle Makefile v0.7.2
#by demiurgosoft
#Just type make to compile project (currently compiling tests)
#make test: compile tests
#make clean: clean directories (removing binaries and objects)
#make astyle: astyle format to all .cpp and .h files (needs astyled installed)
#make print-%: shows % variable (if makefile crashes, for testing)


#FLAGS
CXX = g++
CPPFLAGS= -Wall -O1 -std=c++11 #-g
ALLEGROFLAGS=-lallegro -lallegro_image -lallegro_main -lallegro_font -lallegro_ttf
#ALLEGROFLAGS2=-lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image -lallegro_main -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_memfile -lallegro_physfs

IDIR=include
ODIR=obj
SDIR=src
BDIR=bin

UTILSDIR=$(IDIR)/utilities
MAPDIR=$(IDIR)/map
ENEMYDIR=$(IDIR)/enemy
TOWERDIR=$(IDIR)/tower
CONTROLLERDIR=$(IDIR)/controller
TESTDIR=$(SDIR)/test
MAINDIR=$(SDIR)/main

_INC=$(UTILSDIR) $(MAPDIR) $(ENEMYDIR) $(TOWERDIR) $(CONTROLLERDIR)
I_INC=$(patsubst %,-I %,$(_INC))

_AL_UTILS=al_anim.cpp al_utils.cpp debug_log.cpp input_handler.cpp game_object_attributes.cpp game_object.cpp text_handler.cpp tinyxml2.cpp
AL_UTILS_O=$(patsubst %,$(ODIR)/%,$(_AL_UTILS:.cpp=.o))
_MAP=tile.cpp tileset.cpp tilemap.cpp
MAP_O=$(patsubst %,$(ODIR)/%,$(_MAP:.cpp=.o))
_ENEMY=enemy_attributes.cpp enemy.cpp enemy_set.cpp
ENEMY_O=$(patsubst %,$(ODIR)/%,$(_ENEMY:.cpp=.o))
_TOWER=tower_atk_attributes.cpp tower_atk.cpp tower_attributes.cpp tower.cpp tower_set.cpp
TOWER_O=$(patsubst %,$(ODIR)/%,$(_TOWER:.cpp=.o))
_CONTROLLER=game_objects.cpp player_controller.cpp game_master.cpp player.cpp
CONTROLLER_O=$(patsubst %,$(ODIR)/%,$(_CONTROLLER:.cpp=.o))

TEST_O=$(AL_UTILS_O) $(MAP_O) $(ENEMY_O) $(TOWER_O) $(CONTROLLER_O)
_TEST_H=test_utils.h test_anim.h test_map.h test_tower.h test_enemy.h test_controller.h
TEST_H=$(patsubst %,$(TESTDIR)/%,$(_TEST_H))

MAIN_O=$(AL_UTILS_O) $(MAP_O) $(ENEMY_O) $(TOWER_O) $(CONTROLLER_O) $(ODIR)/DCmC.o

.PHONY: all
all: main

bin/DCmC: $(MAIN_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC) -I $(TESTDIR) $(ALLEGROFLAGS)
#Compile tests
bin/main_test: $(TEST_O) $(LIBS) $(TESTDIR)/main_test.cpp
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC) -I $(TESTDIR) $(ALLEGROFLAGS)
#compile a generic .o
obj/%.o: $(SDIR)/*/%.cpp $(IDIR)/*/%.h
	$(CXX) -c -o $@ $< $(I_INC) $(CPPFLAGS)
obj/%.o: $(SDIR)/*/%.cpp
	$(CXX) -c -o $@ $< $(I_INC) $(CPPFLAGS)
#Creates directories if dont exists
$(BDIR)/:
	mkdir $(BDIR)
$(ODIR)/:
	mkdir $(ODIR)


.PHONY: main
main: $(BDIR)/ $(ODIR)/ bin/DCmC
#compile tests binaries
.PHONY: test
test: $(BDIR)/ $(ODIR)/ $(TEST_H) bin/main_test
#astyle for all code (.cpp and .h)
.PHONY: astyle
astyle:
	astyle --style=java --break-closing-brackets --align-pointer=name --delete-empty-lines --indent-col1-comments --unpad-paren -n -Q $(IDIR)/*/*.h $(SDIR)/*/*.cpp $(SDIR)/*/*.h
#print variable
.PHONY: print-%
print-%  : ; @echo $* = $($*)
#clean obj and bin directories as well as *~ files
.PHONY: clean
clean:
	rm -r -f $(BDIR) $(ODIR) *~ $(SDIR)/*/*~ $(IDIR)/*/*~

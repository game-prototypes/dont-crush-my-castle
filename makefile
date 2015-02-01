#Don't Crush my Castle Makefile v0.5
#by demiurgosoft
#Just type make to compile project (currently compiling tests)
#make test: compile tests
#make clean: clean directories (removing binaries and objects)
#make astyle: astyle format to all .cpp and .h files (needs astyled installed)
#make print-%: shows % variable (if makefile crashes, for testing)


#FLAGS
CXX = g++
CPPFLAGS= -Wall -O1 #-g
ALLEGROFLAGS=-lallegro -lallegro_image -lallegro_main
#ALLEGROFLAGS2=-lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image -lallegro_main -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_memfile -lallegro_physfs
#DIR
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

_INC=$(UTILSDIR) $(MAPDIR) $(ENEMYDIR) $(TOWERDIR) $(CONTROLLERDIR)
#INC=$(patsubst %,$(IDIR)/%,$(_INC))
I_INC=$(patsubst %,-I %,$(_INC))

_AL_UTILS=al_anim.cpp al_utils.cpp debug_log.cpp
AL_UTILS_O=$(patsubst %,$(ODIR)/%,$(_AL_UTILS:.cpp=.o))
_MAP=tile.cpp tileset.cpp tilemap.cpp
MAP_O=$(patsubst %,$(ODIR)/%,$(_MAP:.cpp=.o))
_ENEMY=enemy.cpp enemy_set.cpp
ENEMY_O=$(patsubst %,$(ODIR)/%,$(_ENEMY:.cpp=.o))
_TOWER=tower_atk.cpp tower.cpp tower_set.cpp
TOWER_O=$(patsubst %,$(ODIR)/%,$(_TOWER:.cpp=.o))
_CONTROLLER=game_objects.cpp player_controller.cpp game_master.cpp
CONTROLLER_O=$(patsubst %,$(ODIR)/%,$(_CONTROLLER:.cpp=.o))

TEST_O=$(AL_UTILS_O) $(MAP_O) $(ENEMY_O) $(TOWER_O) $(CONTROLLER_O) $(TESTDIR)/main_test.cpp

.PHONY: all
all: test

#Compile tests
bin/main_test: $(TEST_O)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(I_INC) -I $(TESTDIR) $(ALLEGROFLAGS)
#compile a generic .o
obj/%.o: $(SDIR)/*/%.cpp
	$(CXX) -c -o $@ $< $(I_INC) $(CPPFLAGS)

#Creates directories if dont exists
$(BDIR)/:
	mkdir $(BDIR)
$(ODIR)/:
	mkdir $(ODIR)
	
	
	
#compile tests binaries
.PHONY: test
test: $(BDIR) $(ODIR) bin/main_test
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

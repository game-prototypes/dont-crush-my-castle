#Don't Crush my Castle Makefile v0.3
#by demiurgosoft
#Just type make to compile project (currently compiling tests)
#make test: compile tests
#make clean: clean directories (removing binaries and objects)
#make astyle: astyle format to all .cpp and .h files (needs astyled installed)
#make print-%: shows % variable (if makefile crashes, for testing)


#FLAGS
CXX = g++
CPPFLAGS= -Wall -O1 #-g
ALLEGROFLAGS=`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

#DIR
IDIR=include
ODIR=obj
SDIR=src
IBIN=bin

UTILSDIR=utilities/
MAPDIR=map/
ENEMYDIR=enemy/
BUILDINGDIR=building/

_INC=$(UTILSDIR)
INC=$(patsubst %,$(IDIR)/%,$(_INC))

_AL_UTILS=al_anim.cpp al_utils.cpp debug_log.cpp
AL_UTILS_H=$(patsubst %,$(IDIR)/$(UTILSDIR)/%,$(_AL_UTILS:.cpp=.h))
AL_UTILS_O=$(patsubst %,$(ODIR)/%,$(_AL_UTILS:.cpp=.o))

TEST_OBJ=obj/test_utils.o $(AL_UTILS_O)
TEST_DEP=$(AL_UTILS_H)

bin/test_utils: $(TEST_OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS) -I $(INC)  $(ALLEGROFLAGS)

obj/%.o: $(SDIR)/*/%.cpp $(TEST_DEP)
	$(CXX) -c -o $@ $< -I $(INC) $(CPPFLAGS)


.PHONY: test
test: bin/test_utils
.PHONY: astyle
astyle:
	astyle --style=attach --break-closing-brackets --align-pointer=name --delete-empty-lines --indent-col1-comments --unpad-paren -n -Q $(IDIR)/*/*.h $(SDIR)/*/*.cpp
.PHONY: print-%
print-%  : ; @echo $* = $($*)
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*/*~ $(IBIN)/*

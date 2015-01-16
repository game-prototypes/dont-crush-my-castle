#Don't Crush my Castle Testing script v0.3
#by demiurgosoft

#This script will compile,test and clean Don't Crush My Castle

echo 'Compiling and testing (may take a while)';
#COMPILE TEST
make test >/dev/null;



#TEST 1
./bin/test_utils;
RES1=$?
#TEST 2
./bin/test_anim;
RES2=$?
echo 'Cleaning binaries and .o files'
#CLEAN DIRECTORIES
make clean >/dev/null;

RES=$(($RES1 || $RES2))
exit $RES

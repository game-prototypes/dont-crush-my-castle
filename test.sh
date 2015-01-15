#Don't Crush my Castle Testing script v0.3
#by demiurgosoft

#This script will compile,test and clean Don't Crush My Castle

echo 'Compiling and testing (may take a while)';
#COMPILE TEST
make test >/dev/null;
#TEST 1
./bin/test_utils;
#CLEAN DIRECTORIES
make clean >/dev/null;

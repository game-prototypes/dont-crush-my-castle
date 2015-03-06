#Don't Crush my Castle Testing script v0.7.2
#by demiurgosoft
#This script will compile,test and clean Don't Crush My Castle
echo '+Compiling and testing (may take a while)';
make clean >/dev/null;
#COMPILE TEST
make test >/dev/null;
#EXXECUTE
./bin/main_test;
echo '+Cleaning binaries and .o files'
#CLEAN DIRECTORIES
make clean >/dev/null;

exit $RES

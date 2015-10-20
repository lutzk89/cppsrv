### This Makefile is part of the tutorial of the EO library
# Unlike other Makefiles in EO, it is not using the automake/autoconf
# so that it stays easy to understand (you are in the tutorial, remember!)
# MS, Oct. 2002

# if you use this Makefile as a starting point for another application
# you might need to modify the following
DIR_EO = eo/release/lib
DIR_SRC = eo/src
DIR_SO = eo/src/do
DIR_FOR = eo/forex
DIR_BOOST = /usr/include/boost/

.SUFFIXES: .cpp

# Warning: $(CXX) in Linux (RedHat and Mandrake at least) is g++
# However, if you are using this Makefile within xemacs,
# and have problems with the interpretation of the output (and its colors)
# then you should use c++ instead (make CXX=c++ will do)

.cpp: ; $(CXX) -I. -I$(DIR_FOR) -I$(DIR_EO) -I$(DIR_SRC) -I$(DIR_SO) -I$(DIR_BOOST) -Wall -g -o $@  -std=gnu++11  $*.cpp $(DIR_EO)/libeoutils.a $(DIR_EO)/libeo.a  -lboost_system

.cpp.o: ; $(CXX) -I. -I$(DIR_FOR) -I$(DIR_EO) -I$(DIR_SRC) -I$(DIR_SO) -I$(DIR_BOOST) -std=gnu++11 -Wall -g -c $*.cpp -lboost_system 

ALL = forexEA 

all : $(ALL)

forexEA: forexEA.o ; $(CXX) -Wall -std=gnu++11  -o $@  $< $(DIR_EO)/libes.a $(DIR_EO)/libeoutils.a $(DIR_EO)/libeo.a -lboost_system 

clean :
	@/bin/rm $(ALL) *.o *.sav *.xg *.status *~

# Author:
# Emails


PP := g++

FlAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

INC := inc
SRC := src
OBJ := obj
EXE := exe

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

$(OBJ)/deck.o : $(SRC)/deck.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/deck.cpp -o $@

$(OBJ)/player.o : $(SRC)/player.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/player.cpp -o $@

$(OBJ)/maintest.o : $(SRC)/maintest.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/maintest.cpp -o $@

sim_obj := $(OBJ)/deck.o $(OBJ)/player.o $(OBJ)/maintest.o

simulation : $(sim_obj)
	$(PP) $(CXXFLAGS) $(sim_obj) -o $(EXE)/simulation


clean:
	rm -rf *.o $(OBJ)/* $(EXE)/*

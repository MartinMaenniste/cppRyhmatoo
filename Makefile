
LINKER-FLAGS= -lsfml-graphics -lsfml-window -lsfml-system
COMPILER= g++

rungame: main.o Minesweeper.o
	$(COMPILER) main.o Minesweeper.o -o rungame $(LINKER-FLAGS)
main.o: main.cpp
	$(COMPILER) -c main.cpp

Minesweeper.o: Minesweeper.cpp
	$(COMPILER) -c Minesweeper.cpp

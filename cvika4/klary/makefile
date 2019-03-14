# Run program 
run: compile
	./main

# Remove generated files
clean:
	rm main.o deck.o card.o main

# Compilation of program 'main'
compile: main.o card.o deck.o
	g++ main.o card.o deck.o -o main

# Modul 'main.cpp'
main.o: main.cpp card.hpp deck.hpp
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp -o main.o

# Classes
deck.o: deck.cpp deck.hpp card.hpp
	g++ -Wall -pedantic -g -std=c++11 -c deck.cpp -o deck.o

card.o: card.cpp card.hpp
	g++ -Wall -pedantic -g -std=c++11 -c card.cpp -o card.o

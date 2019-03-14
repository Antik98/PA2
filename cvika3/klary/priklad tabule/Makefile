all: compile run

compile:
	g++ -Wall -pedantic -g point.cpp rectangle.cpp main.cpp -o example

run: compile
	./example

memory: compile
	valgrind ./example

clean:
	rm -f example

hi:
	echo "Hi hooman^^";

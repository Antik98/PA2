CXX = g++
CXXFLAGS = -std=c++11
CPPFLAGS = -Wall -pedantic -g


# Run program
run: compile
	valgrind ./main

# Remove generated files
clean:
	rm main


# Compilation old-way
compile_old: main.cpp
	g++ -Wall -pedantic -g -std=c++11 main.cpp -o main

# Compilation of program 'main'
compile: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp -o main

# Compilation with more features
main: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

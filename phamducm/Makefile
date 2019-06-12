CXX =g++
CXXFLAGS = -pedantic -g -std=c++14
CXXLOCALFLAGS = -Wall
BIN = phamducm
SOURCE_DIR = ./src
DOC_DIR = doc
OUTPUT_BIN = .
SOURCE_FILES= $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECT_FILES= $(patsubst $(SOURCE_DIR)/%.cpp,$(SOURCE_DIR)/%.o,$(SOURCE_FILES))

all: compile

compile: $(OBJECT_FILES)
	@ $(CXX) -o $(OUTPUT_BIN)/$(BIN) $^
	mkdir -p saveFolder

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

run:
	$(OUTPUT_BIN)/$(BIN)

valgrind:
	valgrind $(OUTPUT_BIN)/$(BIN)

clean:
	rm $(SOURCE_DIR)/*.o $(BIN)

doc:
	mkdir -p doc
	doxygen Doxyfile
	mv $(DOC_DIR)/html/* $(DOC_DIR)
	rm -r $(DOC_DIR)/html



CAIPlayer.o: src/CAIPlayer.cpp src/CAIPlayer.h src/CPlayer.h \
 src/CCardStack.h src/CCard.h src/CardDatabase.h src/CBoard.h \
 src/CWindow.h
CBoard.o: src/CBoard.cpp src/CBoard.h src/CWindow.h src/CGame.h \
 src/CardDatabase.h src/CCard.h src/CMainMenu.h src/CPauseMenu.h \
 src/CHumanPlayer.h src/CPlayer.h src/CCardStack.h src/CAIPlayer.h
CCard.o: src/CCard.cpp src/CCard.h src/CPlayer.h src/CCardStack.h \
 src/CardDatabase.h src/CBoard.h src/CWindow.h
CCardStack.o: src/CCardStack.cpp src/CCardStack.h src/CCard.h \
 src/CardDatabase.h src/CBoard.h src/CWindow.h src/CMinion.h
CGame.o: src/CGame.cpp src/CGame.h src/CardDatabase.h src/CCard.h \
 src/CMainMenu.h src/CWindow.h src/CPauseMenu.h src/CBoard.h \
 src/CHumanPlayer.h src/CPlayer.h src/CCardStack.h src/CAIPlayer.h
CHumanPlayer.o: src/CHumanPlayer.cpp src/CHumanPlayer.h src/CPlayer.h \
 src/CCardStack.h src/CCard.h src/CardDatabase.h src/CBoard.h \
 src/CWindow.h
CMainMenu.o: src/CMainMenu.cpp src/CMainMenu.h src/CWindow.h
CMinion.o: src/CMinion.cpp src/CMinion.h src/CCard.h src/CPlayer.h \
 src/CCardStack.h src/CardDatabase.h src/CBoard.h src/CWindow.h
CPauseMenu.o: src/CPauseMenu.cpp src/CPauseMenu.h src/CWindow.h
CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CCardStack.h src/CCard.h \
 src/CardDatabase.h src/CBoard.h src/CWindow.h
CSpell.o: src/CSpell.cpp src/CSpell.h src/CCard.h src/CMinion.h
CWindow.o: src/CWindow.cpp src/CWindow.h
CardDatabase.o: src/CardDatabase.cpp src/CardDatabase.h src/CCard.h \
 src/CSpell.h src/CMinion.h
main.o: src/main.cpp src/CGame.h src/CardDatabase.h src/CCard.h \
 src/CMainMenu.h src/CWindow.h src/CPauseMenu.h src/CBoard.h \
 src/CHumanPlayer.h src/CPlayer.h src/CCardStack.h src/CAIPlayer.h

CXX =g++
CXXFLAGS = -pedantic -g
CXXLOCALFLAGS = -Wall
BIN = phamducm
SOURCE_DIR = .
DOC_DIR = doc
OUTPUT_BIN = .

all: game clean

game: main.o CAIPlayer.o CardDatabase.o CBoard.o CCard.o CCardStack.o CGame.o CHumanPlayer.o CMainMenu.o CMinion.o CPauseMenu.o CPlayer.o CSpell.o CWindow.o
	$(CXX) -o $(OUTPUT_BIN)/$(BIN) main.o CAIPlayer.o CardDatabase.o CBoard.o CCard.o CCardStack.o CGame.o CHumanPlayer.o CMainMenu.o CMinion.o CPauseMenu.o CPlayer.o CSpell.o CWindow.o -I.

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CGame.o: CGame.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CAIPlayer.o: CAIPlayer.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CardDatabase.o: CardDatabase.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CBoard.o: CBoard.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CCard.o: CCard.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CCardStack.o: CCardStack.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CHumanPlayer.o: CHumanPlayer.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CMainMenu.o: CMainMenu.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CMinion.o: CMinion.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CPauseMenu.o: CPauseMenu.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CPlayer.o: CPlayer.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CSpell.o: CSpell.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

CWindow.o: CWindow.cpp
	$(CXX) -c $(CXXFLAGS) $(SOURCE_DIR)/$^

run:
	$(OUTPUT_BIN)/$(BIN)
clean:
	rm *.o $(BIN)

doc:
	doxygen Doxyfile

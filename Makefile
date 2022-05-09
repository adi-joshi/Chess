CXX=g++
CXXFLAGS= -MMD
OBJECTS= main.o game.o exception.o color.o board.o result.o textdisplay.o square.o piece.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

debug: CXXFLAGS += -g
debug: ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

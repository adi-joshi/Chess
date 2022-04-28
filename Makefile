CXX=g++
CXXFLAGS= -MMD
OBJECTS= main.o game.o exception.o color.o result.o board.o observer.o subject.o result.o textdisplay.o square.o piece.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

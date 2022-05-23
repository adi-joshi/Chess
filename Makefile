CXX=g++
CXXFLAGS= -MMD -pthread
OBJECTS= code/main.o code/game.o code/exception.o code/color.o code/board.o code/result.o code/textdisplay.o code/square.o code/piece.o code/move.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} -pthread ${OBJECTS} -o ${EXEC}

debug: CXXFLAGS += -g
debug: ${EXEC}

test: code/test.o gtest-all.o gtest_main.o gtest.a gtest_main.a
test: OBJECTS += code/test.o gtest-all.o gtest_main.o gtest.a gtest_main.a
test: CXXFLAGS += -DDEBUG=1
test: ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC} gtest*

# Makefile copied from googletest: https://github.com/google/googletest/blob/release-1.8.1/googletest/make/Makefile

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = testing

# Where to find user code.
USER_DIR = ../code

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


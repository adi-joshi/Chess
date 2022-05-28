CXX=g++
CXXFLAGS= -MMD
OBJECTS= $(addprefix code/, main.o game.o exception.o color.o board.o result.o textdisplay.o square.o piece.o move.o)
GTEST_DIR = testing
TEST_DIR = testing/tests
USER_DIR = ../code
PROJECT_DIR = .
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GTEST_FILES = gtest-all.o gtest_main.o gtest.a gtest_main.a
TESTS = $(addprefix testing/tests/, test.o square_tests.o piece_tests.o)
DEPENDS = ${OBJECTS:.o=.d}
# TEST_SRCS = ${TEST_DIR}/*.cc
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} -pthread ${OBJECTS} -o ${EXEC}

debug: CXXFLAGS += -g
debug: ${EXEC}

test: OBJECTS += ${TESTS}
test: OBJECTS += ${GTEST_FILES}
test: DEPENDS += ${TESTS:.o=.d}
test: DEPENDS += ${GTEST_FILES:.o=.d}
test: ${TESTS}
test: ${GTEST_FILES}
test: CXXFLAGS += -DDEBUG=1
test: ${EXEC}

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

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${FILES} ${DEPENDS} ${EXEC} ${OBJECTS} ${TESTS} ${GTEST_FILES} ./*.d ${TEST_DIR}/*.d

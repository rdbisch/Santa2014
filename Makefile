CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++11
SOURCES = $(shell find -name "*.cpp")
OBJECTS = ${SOURCES:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a.out

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

clean:
	rm ${OBJECTS} ${DEPENDS}

-include ${DEPENDS}

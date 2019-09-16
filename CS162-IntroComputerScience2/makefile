CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

EXECUTABLE = HauntedHouse
OBJS = main.o menu.o spaces.o character.o dungeon.o house.o outside.o
SRCS = main.cpp menu.cpp spaces.cpp character.cpp dungeon.cpp house.cpp outside.cpp
HEADERS = menu.hpp spaces.hpp character.hpp dungeon.hpp house.hpp outside.hpp

${EXECUTABLE}: ${OBJS}
	${CXX} ${LDFLAGS} ${OBJS} -o ${EXECUTABLE}

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o ${EXECUTABLE}

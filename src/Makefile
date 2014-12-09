# Compiler
CC	= g++

# Include pahts
INCLUDE_SNET=-I network/headers
INCLUDE_HASHTAG=-I hashtag/headers 

# Network module sources and objects
NET_DIR=network
NET_SRC=graph.cpp
NET_MAIN=main.cpp
NET_OBJS=$(patsubst %.cpp,%.o, $(NET_SRC))
NET_MOBJ=$(patsubst %.cpp,%.o, $(NET_MAIN))

# Hashtag module sources
HASH_DIR=hashtag
HASH_MAIN=main.cpp
HASH_MOJB=$(patsubst %.cpp, %.o, $(HASH_MAIN))

# Results dir
BIN_DIR=../bin
LOCAL_DIR=~/Documents/Mestrado/Twitter 

# Flags
CFLAGS=-fopenmp

all: graph hashtag

graph:	${NET_OBJS} ${NET_MOBJ}
	${CC} ${NET_DIR}/obj/${NET_OBJS} ${NET_DIR}/obj/${NET_MOBJ} -o ${BIN_DIR}/network
	cp ${BIN_DIR}/* ${LOCAL_DIR}

${NET_MOBJ}: 
	${CC} -c ${NET_DIR}/src/${NET_MAIN} ${CFLAGS} ${INCLUDE_SNET}
	mv *.o network/obj

${NET_OBJS}:
	${CC} -c ${NET_DIR}/src/${NET_SRC} ${CFLAGS} ${INCLUDE_SNET}

clean:
	rm -rf *.o

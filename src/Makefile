# Compiler
CC=g++
AR=ar

# Lib dir
LIB_DIR=lib

# Include pahts
INCLUDE_SNET=-I snet/headers 
INCLUDE_HASHTAG=-I hashtag/headers ${INCLUDE_SNET} 

# Link libraries
LINK_FLAG=-L./lib 
LINK_SNET=-lsnet

# Results dir
BIN_DIR=../bin
LOCAL_DIR=~/Documents/Mestrado/Twitter

# SNET 
# Snet module sources and objects
SNET_LIB=${LIB_DIR}/libsnet.a
SNET_DIR=snet
SNET_SRC:=$(wildcard ${SNET_DIR}/src/*.cpp)
SNET_OBJ:=$(patsubst $(SNET_DIR)/src/%,%,$(SNET_SRC))
SNET_OBJ:=$(patsubst %.cpp,%.o,$(SNET_OBJ))
SNET_OBJ:=$(addprefix $(SNET_DIR)/obj/,$(SNET_OBJ))

# Flags
CFLAGS=-fopenmp -std=gnu++0x

# EXECUTABLE PROGRAMS
PROGRAM_DIR=programs
SNET_MSRC=${PROGRAM_DIR}/src/snet_main.cpp
SNET_MOBJ=${PROGRAM_DIR}/obj/snet_main.o
SNET_BIN=${BIN_DIR}/snet

all: ${SNET_LIB} ${SNET_BIN}

${SNET_LIB}: ${SNET_OBJ}
	${AR} crf ${SNET_LIB} ${SNET_OBJ}

${SNET_OBJ}:
	${CC} -c ${SNET_SRC} ${CFLAGS} ${INCLUDE_SNET}
	mv *.o ${SNET_DIR}/obj/

${SNET_BIN}: ${SNET_MOBJ} ${SNET_LIB}
	${CC} ${SNET_MOBJ} -o ${SNET_BIN} ${LINK_FLAG} ${LINK_SNET} ${CFLAGS}
	cp ${SNET_BIN} ${LOCAL_DIR}/snet

${SNET_MOBJ}: ${SNET_LIB}
	${CC} -c ${SNET_MSRC} ${CFLAGS} ${INCLUDE_SNET} ${LINK_FLAG} ${LINK_SNET}

clean:
	rm -rf *.o

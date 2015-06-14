# Compiler
CXX=g++
AR=ar

# Lib dir
LIB_DIR=lib

# Include pahts
INCLUDE_SNET=-I snet/headers 
INCLUDE_JSON=-I json/headers

# Link libraries
LINK_FLAG=-L./lib 
LINK_SNET=-lsnet
LINK_JSON=-ljson

# Results dir
BIN_DIR=../bin
LOCAL_DIR=~/Documents/Mestrado/Twitter

# JSON (Using jsoncpp)
JSON_LIB=${LIB_DIR}/libjson.a
JSON_DIR=json
JSON_SRC:=$(wildcard ${JSON_DIR}/src/*.cpp)
JSON_OBJ:=$(patsubst $(JSON_DIR)/src/%,%,$(JSON_SRC))
JSON_OBJ:=$(patsubst %.cpp,%.o,$(JSON_OBJ))
JSON_OBJ:=$(addprefix $(JSON_DIR)/obj/,$(JSON_OBJ))

# SNET 
# Snet module sources and objects
SNET_LIB=${LIB_DIR}/libsnet.a
SNET_DIR=snet
SNET_SRC:=$(wildcard ${SNET_DIR}/src/*.cpp)
SNET_OBJ:=$(patsubst $(SNET_DIR)/src/%,%,$(SNET_SRC))
SNET_OBJ:=$(patsubst %.cpp,%.o,$(SNET_OBJ))
SNET_OBJ:=$(addprefix $(SNET_DIR)/obj/,$(SNET_OBJ))

# Flags
CFLAGS=-g -std=gnu++0x -O2

# EXECUTABLE PROGRAMS
PROGRAM_DIR=programs
SNET_MSRC=${PROGRAM_DIR}/src/snet_main.cpp
SNET_MOBJ=${PROGRAM_DIR}/obj/snet_main.o
SNET_BIN=${BIN_DIR}/snet
HASHTAG_SRC=${PROGRAM_DIR}/src/hashtag_network.cpp
HASHTAG_OBJ=${PROGRAM_DIR}/obj/hashtag_network.o
HASHTAG_BIN=${BIN_DIR}/hashtag_network

all: ${SNET_LIB} ${JSON_LIB} ${SNET_BIN} ${HASHTAG_BIN}

${JSON_LIB}: ${JSON_OBJ}
	${AR} crf ${JSON_LIB} ${JSON_OBJ}

${JSON_OBJ}: ${JSON_SRC}
	${CXX} -c ${JSON_SRC} ${CFLAGS} ${INCLUDE_JSON} 
	mv *.o ${JSON_DIR}/obj/

${SNET_LIB}: ${SNET_OBJ}
	${AR} crf ${SNET_LIB} ${SNET_OBJ}
 
${SNET_OBJ}: ${SNET_SRC}
	${CXX} -c ${SNET_SRC} ${CFLAGS} ${INCLUDE_SNET} ${INCLUDE_JSON}
	mv *.o ${SNET_DIR}/obj/

${SNET_BIN}: ${SNET_MOBJ} ${SNET_LIB}
	${CXX} ${SNET_MOBJ} -o ${SNET_BIN} ${LINK_FLAG} ${LINK_SNET} ${LINK_JSON} ${CFLAGS}

${SNET_MOBJ}: ${SNET_LIB} ${SNET_MSRC}
	${CXX} -c ${SNET_MSRC} ${CFLAGS} ${INCLUDE_SNET} ${INCLUDE_JSON}
	mv *.o ${PROGRAM_DIR}/obj/

${HASHTAG_BIN}: ${HASHTAG_OBJ}
	${CXX} ${HASHTAG_OBJ} -o ${HASHTAG_BIN} ${LINK_JSON} ${LINK_FLAG} ${LINK_SNET} ${CFLAGS}

${HASHTAG_OBJ}: ${HASHTAG_SRC}
	${CXX} -c ${HASHTAG_SRC} ${CFLAGS} ${INCLUDE_JSON} ${INCLUDE_SNET}
	mv *.o ${PROGRAM_DIR}/obj/

clean:
	rm -rf *.o

copy:
	cp ${BIN_DIR}/*  ~/Documents/Mestrado/Twitter/

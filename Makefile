#Compiler:
CC=gcc

#Flags:
CFLAGS=-c -g -Wall
LDFLAGS=-g

#Sources
DEBUG_SOURCES=./debugUtils/printutils.c 
TEST_SOURCES=./testing/main.c ./testing/jsonvalidation_tests.c
LIB_SOURCES=./BSON_JSON/jsonutils.c
DEBUG_OBJECT=debugutils.o 
TEST_OBJECT=main.o
LIB_OBJECT=jsonutils.o

#Executable
TEST_EXECUTABLE=test

all: $(DEBUG_OBJECTS) $(LIB_OBJECTS) $(TEST_OBJECTS) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(DEBUG_OBJECT) $(TEST_OBJECT) $(LIB_OBJECT)
	$(CC) $(LDFLAGS) $(LIB_OBJECT) $(DEBUG_OBJECT) $(TEST_OBJECT) -o $(TEST_EXECUTABLE)

$(DEBUG_OBJECT): 
	$(CC) $(CFLAGS) $(DEBUG_SOURCES) -o $(DEBUG_OBJECT)

$(TEST_OBJECT):
	$(CC) $(CFLAGS) $(TEST_SOURCES)

$(LIB_OBJECT):
	$(CC) $(CFLAGS) $(LIB_SOURCES) -o $(LIB_OBJECT)

clean:
	rm -rf *o $(TEST_EXECUTABLE)

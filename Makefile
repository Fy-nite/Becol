VERSION := 1.0.0
LIB_VERSION := 1.0.0

CXX     := gcc
TARGET = bin/fob
LIB_TARGET = bin/libfob.so
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -DCOMMIT="\"$(shell git describe --always)\"" -DVERSION="\"$(VERSION)\"" -DSOURCE="\"$(shell git remote get-url $(shell git remote))\"" -Werror
LIB_CFLAGS = -fPIC -DVERSION="\"$(LIB_VERSION)\""

.PHONY: default all clean

default: release
release: $(TARGET)
debug: CFLAGS += -DDEBUG
debug: $(TARGET)
trace: CFLAGS += -DTRACE
trace: debug
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
LIB_OBJECTS = $(patsubst %.c, %.o, $(wildcard src/fob/*.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS) $(LIB_TARGET)
	mkdir bin -p
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ -L. -l:$(LIB_TARGET)

$(LIB_TARGET): CFLAGS += $(LIB_CFLAGS)
$(LIB_TARGET): $(LIB_OBJECTS)
	mkdir bin -p
	$(CC) $(LIB_OBJECTS) -Wall -Werror -shared $(LIBS) -o $@

clean:
	-find . -name *.o -delete
	-rm -rf bin/*

run: $(TARGET)
	$(TARGET)

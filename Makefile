## Makefile for utils lib

CC := gcc
INCLUDES := -I. -I/usr/local/include
CFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -L. -Wall -Werror -fdiagnostics-color=always $(INCLUDES)
LDLIBS := -lcrypto -lssl

ifneq ($(strip $(DEBUG)), no)
  CFLAGS += -g
endif

ifneq ($(strip $(OPTIM)), no)
  CFLAGS += -O2
endif

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: libpeer.a

libpeer.a: $(OBJECTS)
	ar rcs $@ $^
	@echo $(OBJECTS)

.PHONY: clean
clean:
	@rm -f *.o *.a

depend : $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep


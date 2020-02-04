## Makefile for utils lib

CC := clang
INCLUDES := -I. -I/usr/local/include
CFLAGS := -Wall -Werror -pedantic -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -L. -Wall -Werror -fdiagnostics-color=always $(INCLUDES)
LDLIBS := -lcrypto -lssl

ifneq ($(strip $(DEBUG)), no)
  CFLAGS += -g
endif

ifneq ($(strip $(OPTIM)), no)
  CFLAGS += -O0
else
  CFLAGS += -O3
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


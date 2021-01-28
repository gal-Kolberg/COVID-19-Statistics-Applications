CC = gcc
CC_SO_FLAGS = -shared -fPIC
SO_LIBRARY = corona_api_utils.c
CC_OUT_FLAGS =  -lcorona_api_utils -L`pwd`

SRCS := $(shell find . -maxdepth 1 -name "*.c" ! -iname "corona_api_utils.c")
OBJS := $(patsubst %.c,%.out,$(SRCS))

all: libcorona_api_utils.so $(SRCS) $(OBJS)

%.out: %.c
	$(CC) $^ $(CC_OUT_FLAGS) -o $@

libcorona_api_utils.so: corona_api_utils.c corona_api_utils.h
	$(CC) $(CC_SO_FLAGS) $< -o $@

clean:
	rm -rf *.out *.so countries # Countries_Dir
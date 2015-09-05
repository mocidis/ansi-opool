.PHONY: all clean
APP := test-opool

OPOOL_DIR := .
OPOOL_SRCS := object-pool.c

MAIN_DIR := .
MAIN_SRCS := main.c

LIBS := -std=c99 -Werror -lpthread
CFLAGS := -I$(C_DIR)/include -I$(OPOOL_DIR)/include

all: $(APP)

$(APP): $(OPOOL_SRCS:.c=.o) $(MAIN_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(MAIN_SRCS:.c=.o): %.o: $(MAIN_DIR)/test/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(OPOOL_SRCS:.c=.o): %.o: $(OPOOL_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr *.o $(APP)

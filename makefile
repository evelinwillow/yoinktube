# Append to existing options (if OBJS is already defined)
#    vv
OBJS += src/main.c
# Set if unset
#   vv
BIN ?= bin/out

CC ?= gcc
CCLD ?= $(CC)
CFLAGS = -Isrc/include -Isrc/extern/include -Wall -Wpedantic -Wshadow -Wextra -lcurl
LDFLAGS += -Isrc/include -Isrc/extern/include -Wall -Wpedantic -Wshadow -Wextra -lcurl
VFLAGS = --leak-check=full -s --track-origins=yes

#############
# First thing executed when running `make`
all: $(BIN)
#############

# Build all object files
.SUFFIXES: .c .o
.c.o:
	$(CC) -o $@ $< $(CFLAGS)

# Link final file
$(BIN): $(OBJS)
	$(CCLD) $(LDFLAGS) -o $(BIN) $(OBJS)

debug:	CFLAGS += -g
debug:	LDFLAGS += -g
debug:  $(BIN)

clean:
	./clean.sh

remake:
	make clean
	make debug

run:
	make remake
	$(BIN)

gdb:
	make remake
	gdb $(BIN)

valgrind:
	make remake
	valgrind $(VFLAGS) $(BIN)

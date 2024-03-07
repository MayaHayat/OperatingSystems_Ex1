CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g3

.PHONY: all clean debug_bug_c debug_bug_c_debug debug_bug_b debug_bug_b_debug

all: Bug_b Bug_b_debug Bug_c Bug_c_debug

# B Bug

Bug_b: Bug_b.c
	$(CC) $(CFLAGS) $^ -o $@

Bug_b_debug: Bug_b.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

debug_bug_b: Bug_b
	gdb ./Bug_b

debug_bug_b_debug: Bug_b_debug
	gdb ./Bug_b_debug



# C Bug

Bug_c: Bug_c.c
	$(CC) $(CFLAGS) $^ -o $@

Bug_c_debug: Bug_c.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

debug_bug_c: Bug_c
	gdb ./Bug_c

debug_bug_c_debug: Bug_c_debug
	gdb ./Bug_c_debug

clean:
	rm -f Bug_c Bug_c_debug Bug_b Bug_b_debug
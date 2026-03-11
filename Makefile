CC = gcc
CFLAGS = -Wall -Wextra

all: priority

priority: priority.c
	@$(CC) $(CFLAGS) -o priority priority.c

test: priority
	@./priority

clean:
	@rm -f priority

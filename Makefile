CC = gcc

priority: priority.c
	$(CC) priority.c -o priority

test: priority
	./priority

clean:
	rm -f priority

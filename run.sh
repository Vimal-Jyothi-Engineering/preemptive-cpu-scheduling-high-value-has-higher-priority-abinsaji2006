#!/bin/bash

# Generate Makefile so "make test" works
cat > Makefile << 'EOF'
CC = gcc

priority: priority.c
	@$(CC) priority.c -o priority

test: priority.c
	@$(CC) priority.c -o priority
	@./priority

clean:
	@rm -f priority
EOF

gcc priority.c -o priority
./priority

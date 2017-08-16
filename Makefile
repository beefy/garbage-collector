
CC=gcc -std=gnu99 -pthread -g

# by convention the first makefile target
# compile, run the problems, then clean up
all: run clean

# compile all of the files 
# and execute the tests
run: compile
	./bin/test.out
	
# compile all of the files
# and execute the tests with valgrind
# then clean up
test: compile
	valgrind --track-origins=yes ./bin/test.out
	@$(MAKE) clean

# compile all of the files
# and give them execute permissions
compile: test.out
	chmod u+x ./bin/test.out

# compile the tests
test.out:
	$(CC) -o ./bin/test.out ./tests/gc_malloc_test.c ./gc_malloc/gc_malloc.c

# remove all of the binary/executables
clean:
	rm ./bin/*.out


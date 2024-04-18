CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
FOLDER = ../testing/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

my_cat: my_cat.o my_cat_lib.o
	$(CC) $(CFLAGS) $^ -o $@
	rm -f *.o

my_cat.o: my_cat.c my_cat_lib.h

my_cat_lib.o: my_cat_lib.c my_cat_lib.h

rebuild: clean my_cat

clean:
	rm -f *.o my_cat

test: test_cppcheck rebuild test_diff test_gnu_flags test_ascii_plus test_return 

test_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

test_diff: my_cat
	$(FOLDER)test_diff.sh cat $(FOLDER)input_cat.txt

test_gnu_flags: my_cat
	$(FOLDER)test_cat_gnu_flags.sh $(FOLDER)file1.txt $(FOLDER)file2.txt

test_ascii_plus: my_cat
	$(FOLDER)test_cat_ascii_plus.sh

test_return: my_cat
	$(FOLDER)test_return_code.sh cat $(FOLDER)input_cat_extended.txt

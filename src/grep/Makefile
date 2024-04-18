CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRCMODULES = s21_grep.c s21_grep_args.c s21_grep_auxiliary.c s21_grep_free.c s21_grep_match.c s21_grep_output.c 
OBJMODULES = $(SRCMODULES:.c=.o)
FOLDER = ../testing/
TEST_FLAG_PAIRS_OPTIONS = -f $(FOLDER)patterns_B.txt $(FOLDER)file1.txt $(FOLDER)file2.txt

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_grep: $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@ 
	rm -f *.o

s21_grep.o: s21_grep.c s21_grep_args.h s21_grep_auxiliary.h s21_grep_free.h s21_grep_match.h s21_grep_output.h s21_grep_types.h 

s21_grep_args.o: s21_grep_args.c s21_grep_args.h s21_grep_auxiliary.h s21_grep_types.h

s21_grep_auxiliary.o: s21_grep_auxiliary.c s21_grep_auxiliary.h s21_grep_types.h

s21_grep_free.o: s21_grep_free.c s21_grep_free.h s21_grep_types.h

s21_grep_match.o: s21_grep_match.c s21_grep_match.h s21_grep_args.h s21_grep_auxiliary.h s21_grep_free.h s21_grep_output.h s21_grep_types.h

s21_grep_output.o: s21_grep_output.c s21_grep_output.h s21_grep_types.h

rebuild: clean s21_grep

clean:
	rm -f *.o s21_grep

test:  test_cppcheck rebuild test_flags test_diff test_long test_return

test_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

test_flags: s21_grep
	$(FOLDER)test_grep_flags.sh $(TEST_FLAG_PAIRS_OPTIONS)

test_diff: s21_grep
	$(FOLDER)test_diff.sh grep $(FOLDER)input_grep.txt

test_long: s21_grep
	$(FOLDER)test_grep_long_lines.sh

test_return: s21_grep
	$(FOLDER)test_return_code.sh grep $(FOLDER)input_grep_extended.txt


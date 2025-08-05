CC = gcc
FLAG = -std=c11 -Wall -Werror -Wextra

all: rebuild

s21_grep: clean
	${CC} ${FLAG} s21_grep.c -o s21_grep -lpcre

rebuild: clean s21_grep

clean:
	rm -rf s21_grep

style:
	cp ../../materials/linters/.clang-format ../../src/grep/.clang-format
	clang-format -style=Google -n *.c *.h

test: s21_grep
	sh test.sh


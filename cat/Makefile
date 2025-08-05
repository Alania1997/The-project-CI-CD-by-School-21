CC = gcc
FLAG = -Wall -Werror -Wextra -std=c11

all: rebuild

s21_cat: clean
	$(CC) $(FLAG) s21_cat.c -o s21_cat

rebuild: clean s21_cat

test:
	sh tests_cat.sh

clean:
	rm -rf s21_cat

style:
	cp ../../materials/linters/.clang-format ../../src/cat/.clang-format
	clang-format -style=Google -n *.c *.h
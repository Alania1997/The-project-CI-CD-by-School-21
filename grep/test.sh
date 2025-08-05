#!/bin/bash

TEST_FILE_FIRST="s21_grep.c"
TEMPLATE_CHAR="int"

grep -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -i -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -i -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -v -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -v -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -c -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -c -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -l -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -l -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -n -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -n -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -h -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -h -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -s -e "fvs" -e "b" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -s -e "fvs" -e "b" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt 
grep -f "pattern.txt" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -f "pattern.txt"  ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -o "a" ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -o "a" ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt


grep -ihs -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -is -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -io -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -io -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -io -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -io -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -ic -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -ic -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -vo -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -vo -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -sho -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -so -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt

grep -isl -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -isl -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -iov -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -iov -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -ioc -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -ioc -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -sic -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -sic -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -nvo -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -nvo -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt
grep -iso -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > ORIGINAL.txt && ./s21_grep -iso -e ${TEMPLATE_CHAR} ${TEST_FILE_FIRST} > MINE.txt && diff -s ORIGINAL.txt MINE.txt




rm -rf ORIGINAL.txt MINE.txt
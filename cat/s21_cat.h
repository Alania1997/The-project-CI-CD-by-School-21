#ifndef S21_SRC_CAT
#define S21_SRC_CAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cat {
  int b;
  int e;
  int s;
  int n;
  int t;
  int v;
  int other;
  char *other_str;
} s21_cat;

void print_file(char *name, s21_cat *flags);
void print_string(s21_cat *flags, char *buff, int *num, int i);
void parsing(s21_cat *flags, char **argv, int i);
void reading_file(int argc, char **argv);

#endif  // S21_SRC_CAT

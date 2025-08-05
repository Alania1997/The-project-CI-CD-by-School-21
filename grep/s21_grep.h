#ifndef S21_SRC_GREP_H
#define S21_SRC_GREP_H

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s21_grep {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} s21_grep;

int parsing(int *argc, char *argv[], s21_grep *flags, char *pattern);
int pattern_from_file(s21_grep *flags, char *pattern);
void fix_pattern(int *argc, char *argv[], s21_grep *flags, char *pattern);
void print_pattern(int *argc, char *argv[], s21_grep *flags, char *pattern,
                   int *count_files);
void print_flag_o(char *file_name, s21_grep *flags, pcre *temp,
                  pcre_extra *f_ext, char *buff, int *vector, int *vecsize,
                  int *j, int *count_files);
void print_flag_n(char *file_name, s21_grep *flags, char *buff,
                  int *count_files, int *j);
void check_flag_c(int *pairs, s21_grep *flags, int *check_file, int *count_str);
void print_pcre_compile(char *file_name, s21_grep *flags, FILE *f,
                        char *pattern, int *count_files);
void print_flag_c_l(char *file_name, s21_grep *flags, int *count_files,
                    int *count_str, int *check_file);
void check_enter(char *buff);

#endif  // S21_SRC_GREP_H

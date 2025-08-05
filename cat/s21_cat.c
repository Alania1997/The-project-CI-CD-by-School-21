#include "s21_cat.h"

int main(int argc, char **argv) {
  reading_file(argc, argv);
  return 0;
}

void reading_file(int argc, char **argv) {
  s21_cat flags = {0};
  flags.other_str = NULL;
  int check_f = 0;
  for (int i = 1; i < argc && check_f < 2; i++) {
    if (argv[i][0] == '-' && check_f == 0) {
      if (strlen(argv[i]) == 1 || (strlen(argv[i]) == 2 && argv[i][1] == '-')) {
        check_f = 2;
        printf("cat: illegal option -- %c", argv[i][0]);
        break;
      }
      parsing(&flags, argv, i);
      if (flags.other != 0) {
        printf("cat: illegal option -- %c", flags.other);
        break;
      } else if (flags.other_str != NULL) {
        printf("cat: illegal option -- %s", flags.other_str);
        break;
      }
    } else {
      check_f = 1;
      print_file(argv[i], &flags);
    }
  }
}

void parsing(s21_cat *flags, char **argv, int i) {
  if (argv[i][0] == '-' && argv[i][1] == '-') {
    if (strcmp(argv[i], "--number-nonblank") == 0) {
      flags->b = 1;
    } else if (strcmp(argv[i], "--number") == 0) {
      flags->n = 1;
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
      flags->s = 1;
    } else {
      flags->other_str = argv[i];
    }
  } else {
    for (int j = 1; argv[i][j] != '\0'; j++) {
      if (argv[i][j] == 'b') {
        flags->b = 1;
      } else if (argv[i][j] == 'e') {
        flags->e = 1;
        flags->v = 1;
      } else if (argv[i][j] == 'n') {
        flags->n = 1;
      } else if (argv[i][j] == 's') {
        flags->s = 1;
      } else if (argv[i][j] == 't') {
        flags->t = 1;
        flags->v = 1;
      } else if (argv[i][j] == 'E') {
        flags->e = 1;
      } else if (argv[i][j] == 'v') {
        flags->v = 1;
      } else if (argv[i][j] == 'T') {
        flags->t = 1;
      } else {
        flags->other = argv[i][j];
      }
    }
  }
}

void print_string(s21_cat *flags, char *buff, int *num, int i) {
  for (int j = 0; buff[j] != '\0'; j++) {
    if (flags->b == 1 && j == 0 && buff[0] != '\n') {
      printf("%6d\t", *num);
      (*num)++;
    }
    if (flags->n == 1 && j == 0 && flags->b == 0) {
      printf("%6d\t", i);
    }
    if (flags->t == 1 && buff[j] == '\t') {
      buff[j] = 'I';
      printf("^");
    }
    if (flags->v == 1 && buff[j] <= 31 && buff[j] != 10 && buff[j] != 9) {
      buff[j] += 64;
      printf("^");
    } else if (flags->v == 1 && buff[j] == 127) {
      buff[j] -= 64;
      printf("^");
    }
    if (flags->e == 1 && buff[j] == '\n' && buff[0] != '\n') {
      printf("$");
    }
    if (flags->e == 1 && buff[0] == '\n') {
      if (flags->n == 1 || flags->b == 1) {
        printf("%9c", '$');
      } else {
        printf("$");
      }
    }
    printf("%c", buff[j]);
  }
}

void print_file(char *name, s21_cat *flags) {
  FILE *f = fopen(name, "rb");
  if (f != NULL) {
    char buff[1024] = {0};
    int num = 1;
    int check_s = 0;
    for (int i = 1; fgets(buff, 1024, f) != NULL;) {
      if (flags->s == 1 && buff[0] == '\n') {
        check_s++;
        if (check_s > 1) {
          continue;
        }
      } else if (flags->s == 1 && buff[0] != '\n') {
        check_s = 0;
      }
      print_string(flags, buff, &num, i);
      i++;
    }
    fclose(f);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory\n", name);
  }
}

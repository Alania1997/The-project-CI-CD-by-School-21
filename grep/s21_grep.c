#include "s21_grep.h"

int main(int argc, char *argv[]) {
  // это структура в которой хрантся все флаги
  s21_grep flags = {0};
  // тут хранится массив с паттернами
  char pattern[1024] = {0};
  // это сделал код если во флаг f добавить файл кторого не существует то будет
  // ошибка
  int code = 1;
  if (argc < 3) {
    fprintf(stderr,
            "no valid argument\n");  // это функция в языке программирования C,
                                     // которая используется для вывода ошибок.
  } else {
    // тут вызывается функция которая будет искать флаги и активировать их в
    // структуре
    code = parsing(&argc, argv, &flags, pattern);
    if (code == 1) {
      // тут после парсинга мы закрыли все паттерны \0
      fix_pattern(&argc, argv, &flags, pattern);
      // тут посчитали количество файлов с которыми будем работать
      int count_files = argc - optind;
      // тут уже выводятся строки из фалйа с паттернами
      print_pattern(&argc, argv, &flags, pattern, &count_files);
    }
  }

  return 0;
}

// функция которая парсит флаги
int parsing(int *argc, char *argv[], s21_grep *flags, char *pattern) {
  char ch = 0;
  int code = 1;
  const char *short_options = "e:f:ivclnhso";
  while ((ch = getopt_long(*argc, argv, short_options, NULL, NULL)) != -1 &&
         code == 1) {
    switch (ch) {
      case 'e': {
        flags->e = 1;
        strcat(pattern, optarg);
        strcat(pattern, "|");
        break;
      }
      case 'i': {
        flags->i = 1;
        break;
      }
      case 'v': {
        flags->v = 1;
        break;
      }
      case 'c': {
        flags->c = 1;
        break;
      }
      case 'l': {
        flags->l = 1;
        break;
      }
      case 'n': {
        flags->n = 1;
        break;
      }
      case 'h': {
        flags->h = 1;
        break;
      }
      case 's': {
        flags->s = 1;
        break;
      }
      case 'f': {
        flags->f = 1;
        // это вызывается функция которая сохраняет паттерн из файла в массив
        // pattern
        code = pattern_from_file(flags, pattern);
        break;
      }
      case 'o': {
        flags->o = 1;
        break;
      }
      // если флага не существует то будет вывод ошибки о том что флаг
      // неправильный
      default: {
        fprintf(stderr, "grep: invalid option -- %c", ch);
        code = 0;
        break;
      }
    }
  }
  return code;
}

// функция которая собирает паттерн из файла и закидывает паттерн в массив
// pattern
int pattern_from_file(s21_grep *flags, char *pattern) {
  int code = 1;
  FILE *f_patter = fopen(optarg, "rb");
  char pattern_in_file[1024] = {0};
  if (f_patter == NULL) {
    if (flags->s == 0) {
      // stderr поток вывода ошибок, fprintf тоже как printf  только допом
      // указываем куда выводить
      fprintf(stderr, "No such file or directory-%s\n", optarg);
    }
    code = 0;
  } else {
    while (fgets(pattern_in_file, 1024, f_patter) != NULL) {
      // strcat берет из второго аргумента строку и присоединяет ее к первому
      // аргументу
      //  например у нас есть строка в pattern "123" и есть строка в
      //  pattern_in_file "567" то
      // после функции в pattern будет храниться строка "123567"
      strcat(pattern, pattern_in_file);
      // тут мы смотрим если строка не начинается на \n то в конце ставим |
      if (pattern[strlen(pattern) - 1] == '\n' && pattern_in_file[0] != '\n') {
        pattern[strlen(pattern) - 1] = '|';
        // а тут уже если строка начинается на \n
        // символ | нужен для того чтобы разделить паттерны
      } else {
        pattern[strlen(pattern)] = '|';
      }
    }
    // закрытие потока после открытия файла если он существует
    fclose(f_patter);
  }
  return code;
}

// функция которая ставит в строке pattern \0
// optind это переменная из библиотеки getopt long  и хранит номер с которого
// начинаются файлы
void fix_pattern(int *argc, char *argv[], s21_grep *flags, char *pattern) {
  if (flags->f == 0 && flags->e == 0 && *argc > 2) {
    strcat(pattern, argv[optind]);
    optind++;
  } else {
    pattern[strlen(pattern) - 1] = '\0';
  }
}

// тут начинаем выводить строки из файла
void print_pattern(int *argc, char *argv[], s21_grep *flags, char *pattern,
                   int *count_files) {
  for (int i = optind; i < *argc; i++) {
    FILE *f = fopen(argv[i], "rb");
    if (f == NULL) {
      if (flags->s == 0) {
        fprintf(stderr, "No such file or directory-%s\n", argv[i]);
      }
    } else {
      // тут вызывается функция в кторой происходит обработка и вывод строк
      // после обработки pcre
      print_pcre_compile(argv[i], flags, f, pattern, count_files);
      fclose(f);
    }
  }
}

// обработка строк в pcre и вывод строк после обработки
void print_pcre_compile(char *file_name, s21_grep *flags, FILE *f,
                        char *pattern, int *count_files) {
  char buff[1024] = {0};
  pcre *temp = NULL;
  pcre_extra *f_ext = NULL;
  const char *errstr = NULL;
  int errchar = 0, pairs = 0;
  int vector[5000] = {0};
  int vecsize = 5000;
  int count_str = 0;
  int check_file = 0;
  // получили строку из файла и каждую обрабатываем
  for (int j = 1; fgets(buff, 1024, f) != NULL; j++) {
    if (flags->i == 1) {
      // обработка паттерна без регистра
      temp = pcre_compile(pattern, PCRE_CASELESS | PCRE_MULTILINE, &errstr,
                          &errchar, NULL);
    } else {
      // обработка паттерна с регистром
      temp = pcre_compile(pattern, 0 | PCRE_MULTILINE, &errstr, &errchar, NULL);
    }
    if (temp == NULL) {
      printf("%s", errstr);
    } else {
      // ищет количество совпадений функция библиотеки pcre
      // библиотека pcre
      pairs = pcre_exec(temp, f_ext, buff, strlen(buff), 0, PCRE_NOTEMPTY,
                        vector, vecsize);
      if (flags->c == 0 && flags->l == 0) {
        // вывод флага о
        print_flag_o(file_name, flags, temp, f_ext, buff, vector, &vecsize, &j,
                     count_files);
        if (pairs > 0 && flags->v == 0 && flags->o == 0) {
          // вывод флага n если совпадения есть при выключенном флаге v
          print_flag_n(file_name, flags, buff, count_files, &j);
        } else if (pairs < 0 && flags->v == 1) {
          // вывод флага n если совпадений нет при включенном флаге v
          print_flag_n(file_name, flags, buff, count_files, &j);
        }
      } else {
        // обработка при флаге c
        check_flag_c(&pairs, flags, &check_file, &count_str);
      }
      pcre_free(temp);
    }
  }
  // выводит флаги c , l
  print_flag_c_l(file_name, flags, count_files, &count_str, &check_file);
}

// выводит флаги c , l
void print_flag_c_l(char *file_name, s21_grep *flags, int *count_files,
                    int *count_str, int *check_file) {
  // вывод флага c
  if ((flags->c == 1 && *count_files == 1) ||
      (flags->c == 1 && flags->h == 1)) {
    if (flags->l == 1) {
      printf("%d\n", *check_file);
    } else {
      printf("%d\n", *count_str);
    }
  } else if (flags->c == 1 && *count_files > 1) {
    if (flags->l == 1) {
      printf("%s:%d\n", file_name, *check_file);
    } else {
      printf("%s:%d\n", file_name, *count_str);
    }
  }

  // вывод флага l
  if (flags->l == 1 && *check_file == 1) {
    printf("%s\n", file_name);
  }
}

// обработка и вывод флага о
// тут так же происходит обработка, но уже в указателе ptr_substr содержится
// указатель на подстроку в самой строке так же вывод этой подстроки
void print_flag_o(char *file_name, s21_grep *flags, pcre *temp,
                  pcre_extra *f_ext, char *buff, int *vector, int *vecsize,
                  int *j, int *count_files) {
  int pairs_o = 0;
  if (flags->o == 1 && flags->v == 0) {
    int count_o = 0;
    const char *ptr_substr = NULL;
    while ((pairs_o = pcre_exec(temp, f_ext, buff, strlen(buff), count_o,
                                PCRE_NOTEMPTY, vector, *vecsize)) >= 0) {
      if ((pcre_get_substring(buff, vector, pairs_o, 0, &ptr_substr)) >= 0) {
        if (*count_files > 1 && flags->n == 0 && flags->h == 0) {
          printf("%s:%s\n", file_name, ptr_substr);
        } else if (flags->n == 0 && (*count_files == 1 || flags->h == 1)) {
          printf("%s\n", ptr_substr);
        }

        if (*count_files > 1 && flags->n == 1 && flags->h == 0) {
          printf("%s:%d:%s\n", file_name, *j, ptr_substr);
        } else if ((*count_files == 1 && flags->n == 1) ||
                   (*count_files > 1 && flags->n == 1 && flags->h == 1)) {
          printf("%d:%s\n", *j, ptr_substr);
        }
        count_o = vector[0] + 1;
        // очищаем память в которой хранится подстрока
        pcre_free_substring(ptr_substr);
      }
    }
  }
}

// флаг n выводит строку вместе с номером строки
void print_flag_n(char *file_name, s21_grep *flags, char *buff,
                  int *count_files, int *j) {
  if (*count_files > 1 && flags->n == 0 && flags->h == 0) {
    printf("%s:%s", file_name, buff);
  } else if (flags->n == 0 && (*count_files == 1 || flags->h == 1)) {
    printf("%s", buff);
  }

  if (*count_files > 1 && flags->n == 1 && flags->h == 0) {
    printf("%s:%d:%s", file_name, *j, buff);
  } else if ((*count_files == 1 && flags->n == 1) ||
             (*count_files > 1 && flags->n == 1 && flags->h == 1)) {
    printf("%d:%s", *j, buff);
  }
  check_enter(buff);
}

// флаг c выводит количество совпадающих строк или при включенном флаге l
// выводит совпадающие файлы 0 или 1
void check_flag_c(int *pairs, s21_grep *flags, int *check_file,
                  int *count_str) {
  if (*pairs > 0 && flags->v == 0) {
    if (flags->l == 1) {
      *check_file = 1;
    }
    (*count_str)++;
  } else if (*pairs < 0 && flags->v == 1) {
    if (flags->l == 1) {
      *check_file = 1;
    }
    (*count_str)++;
  }
}

// ставим \n в  конце если последний символ не \n
void check_enter(char *buff) {
  int a = 0;
  a = strlen(buff);
  if (buff[a] == '\0' && buff[a - 1] != '\n') {
    printf("\n");
  }
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"



#define EOF -1


int
getchar(void) {
  int c;
  return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

/* char* */
int
getline(char *line) {
  int c, i;
  for (i = 0; i < MAXPATH - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    /* printf("intput is %c\n", c); */
    line[i]= c;
  }
  line[i] = '\0';
  /* printf("length is %d\n", i); */
  return i;
}
int
readlines(char *lineptr[]) {


  char line[MAXPATH];
  memset(line, 0, sizeof(line));
  char *p;
  int len;
  int nlines = 0;
  while ((len = getline(line)) > 0) {
  /* while ((p = getline(line)) && strlen(p) > 0) { */
    p = malloc(strlen(line));
    strcpy(p, line);
    lineptr[nlines++] = p;
    /* printf("p is %s\n", lineptr[nlines - 1]); */
  }
  return nlines;

}

void getarg(char *argv[], char *exec_argv[],char *p) {
  int i = 1;
  int j = 0;
  while (argv[i]) {
    exec_argv[j++] = argv[i++];
  }
  exec_argv[j] = p;
  exec_argv[++j] = 0;

  /* int k = 0; */
  /* while (exec_argv[k]) { */
  /*   printf("k is %d\n", k); */
  /*   printf("exec arg is %s\n", exec_argv[k++]); */
  /* } */
  /* printf("get arg over\n"); */

  return;
}
int
main(int argc, char *argv[]) {
  /* int k = 0; */
  /* while (argv[k]) { */
  /*   printf("xarg is %s\n", argv[k++]); */
  /* } */


  char *lineptr[MAXARG];
  readlines(lineptr);
  int i = 0;
  char *exec_argv[MAXARG];
  while (lineptr[i]) {
    /* printf("intput %d is %s\n", i, lineptr[i]); */
    getarg(argv, exec_argv, lineptr[i]);
    /* printf("arg is %s\n", exec_argv[i++]); */
    if (fork() == 0) {
      exec(argv[1],exec_argv);
    } else {
      wait(0);
    }
    free(lineptr[i]);
    i++;
  }
  exit(0);
}

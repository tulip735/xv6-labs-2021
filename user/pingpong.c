#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int
main(int argc, char * argv[]) {
  int buffer[512];
  int pipe1[2];
  int pipe2[2];
  pipe(pipe1);
  pipe(pipe2);
  if (fork() == 0) {
    printf("enter child\n");
    int childPid = getpid();
    read(pipe1[0], buffer, sizeof(buffer));
    printf("%d: received %s\n", childPid, buffer);
    write(pipe2[1], "pong", 5);
    exit(0);
  } else {
    int parentPid = getpid();
    write(pipe1[1],"ping", 5);
    wait(0);
    printf("enter parent\n");
    read(pipe2[0], buffer, sizeof(buffer));
    printf("%d: received %s\n", parentPid, buffer);
  }
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  exit(0);
}

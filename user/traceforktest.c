#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/syscall.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("Starting fork trace test\n");

  // Enable tracing for getpid only to keep output clean.
  trace(1 << SYS_getpid);

  int pid = fork();

  if(pid < 0){
    printf("fork failed\n");
    trace(0);
    exit(1);
  }

  if(pid == 0){
    // Child process: should inherit tracemask from parent.
    printf("Child calling getpid\n");
    getpid();
    exit(0);
  } else {
    // Parent process: should still have tracing enabled.
    wait(0);
    printf("Parent calling getpid\n");
    getpid();

    trace(0);
    printf("Fork trace test complete\n");
    exit(0);
  }
}

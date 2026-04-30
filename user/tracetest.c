#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char *argv[])
{
  printf("Starting trace test\n");

  // Enable tracing for getpid only to keep output clean.
  trace(1 << SYS_getpid);

  int pid = getpid();
  printf("Current pid: %d\n", pid);

  // Disable tracing.
  trace(0);

  printf("Trace test complete\n");
  exit(0);
}

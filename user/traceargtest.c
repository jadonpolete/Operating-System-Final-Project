#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/syscall.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  trace(1 << SYS_write);

  write(1, "Argument trace test\n", 20);

  trace(0);
  exit(0);
}

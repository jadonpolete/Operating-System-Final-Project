# System Call Tracing (strace) for xv6

## Team Members

- Jadon Polete
- Connor McConnell
- Achyuth Kumar Kurakula

## Repository

GitHub Repository: https://github.com/jadonpolete/Operating-System-Final-Project

## Project Overview

This project modifies the xv6 operating system to add a basic system call tracing feature similar to Linux `strace`. The purpose of the project is to make system call activity visible while xv6 is running.

A new `trace(int mask)` system call was added. This system call allows a process to enable tracing for selected system calls using a bitmask. When tracing is enabled, xv6 prints information about matching system calls after they execute.

The trace output includes:

- Process ID
- System call name
- Return value

The project also supports trace mask inheritance across `fork`, meaning child processes inherit the tracing configuration from their parent process.

## Modified Files

The following files were modified:

- `kernel/proc.h`
  - Added a `tracemask` field to the process structure.

- `kernel/proc.c`
  - Updated `kfork()` so child processes inherit the parent process's trace mask.

- `kernel/sysproc.c`
  - Added the kernel-side implementation of `sys_trace()`.

- `kernel/syscall.h`
  - Added a new system call number for `trace`.

- `kernel/syscall.c`
  - Added `sys_trace` to the syscall table.
  - Added syscall name mapping.
  - Added tracing logic to the syscall dispatcher.

- `user/user.h`
  - Added the user-level declaration for `trace(int)`.

- `user/usys.pl`
  - Added a syscall stub entry for `trace`.

- `user/tracetest.c`
  - Added a user-space test program for basic tracing.

- `user/traceforktest.c`
  - Added a user-space test program for fork inheritance.

- `user/traceargtest.c`
  - Added a user-space test program for basic syscall argument tracing.

- `Makefile`
  - Added the test programs to the xv6 user program list.

## Prerequisites

This project was built and tested using Kali Linux with the xv6 RISC-V toolchain.

Required tools include:

- `make`
- `qemu-system-riscv64`
- RISC-V GCC toolchain
- Git

If these are not installed, they can usually be installed with:

```bash
sudo apt update
sudo apt install git make qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

Depending on the environment, additional xv6 dependencies may already be installed.

## Build Instructions

From the root of the repository, run:

```bash
make clean
make qemu
```

If the build succeeds, xv6 should boot and display a shell prompt similar to:

```text
init: starting sh
$
```

To exit QEMU, press:

```text
Ctrl + A, then X
```

## Testing Instructions

After xv6 boots, run the included test programs from the xv6 shell.

### Basic Trace Test

Run:

```text
tracetest
```

Expected behavior:

- Enables tracing for `getpid`
- Calls `getpid`
- Displays a trace line containing the process ID, syscall name, and return value
- Disables tracing before exiting

Example output:

```text
Starting trace test
3: syscall getpid -> 3
Current pid: 3
Trace test complete
```

The process ID may be different depending on the run.

### Argument Trace Test

Run:

```text
traceargtest
```

Expected behavior:

- Enables tracing for `write`
- Calls `write` with a file descriptor, buffer, and byte count
- Displays a trace line containing the syscall name, selected arguments, and return value

Example output:

```text
Argument trace test
6: syscall write(fd=1, buf=0x..., n=20) -> 20
```

The process ID and buffer address may be different depending on the run.

### Fork Inheritance Test

Run:

```text
traceforktest
```

Expected behavior:

- Enables tracing for `getpid`
- Calls `fork`
- Child process calls `getpid`
- Parent process calls `getpid`
- Both parent and child produce trace output

Example output:

```text
Starting fork trace test
Child calling getpid
5: syscall getpid -> 5
Parent calling getpid
4: syscall getpid -> 4
Fork trace test complete
```

The process IDs may be different depending on the run.

## Notes About This xv6 Version

This version of xv6 uses `kfork()` in `kernel/proc.c` for the internal process creation logic. Because of that, trace mask inheritance was added inside `kfork()`.

This xv6 version does not define `SYS_sleep`, so the project tests use available system calls such as `getpid`, `write`, `fork`, and `read`.

## Version Control

Development was completed on the `Feature` branch while keeping `main` as the baseline xv6 source. Commits were made in smaller steps to show the development process clearly.

Example commit categories include:

- `feat:` kernel implementation changes
- `test:` user-space test programs
- `docs:` documentation updates

## Project Status

The project currently supports:

- A new `trace(int mask)` system call
- Per-process trace mask storage
- System call name logging
- Return value logging
- Basic argument logging for selected syscalls such as `read` and `write`
- Fork inheritance of trace settings
- User-space tests for basic tracing, argument tracing, and fork inheritance

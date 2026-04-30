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

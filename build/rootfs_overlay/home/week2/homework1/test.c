#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_my_add1 467

int main() {
    int x = 41;
    int result = syscall(SYS_my_add1, x);
    printf("my_add1(%d) = %d\n", x, result);
    return 0;
}

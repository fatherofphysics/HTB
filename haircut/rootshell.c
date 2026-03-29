#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    setuid(0);
    setgid(0);

    char *args[] = {"/bin/bash", NULL};
    execvp("/bin/bash", args);

    return 0;
}

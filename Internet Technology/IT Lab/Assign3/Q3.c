#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        // Child process
        printf("Child process writes: Hello from the child!\n");
    } else {
        // Parent process
        printf("Parent process writes: Hello from the parent!\n");
    }

    return 0;
}

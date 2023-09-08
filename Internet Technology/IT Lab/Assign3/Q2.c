#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int file_descriptor = open("shared.txt", O_RDWR | O_CREAT, 0644);

    if (file_descriptor == -1) {
        perror("open");
        exit(1);
    }

    // Write data in the parent process
    if (fork() == 0) {
        // Child process
        sleep(1);  // Let the parent write first
        char child_data[] = "Child process data\n";
        write(file_descriptor, child_data, sizeof(child_data));
        printf("Child wrote: %s", child_data);
    } else {
        // Parent process
        char parent_data[] = "Parent process data\n";
        write(file_descriptor, parent_data, sizeof(parent_data));
        printf("Parent wrote: %s", parent_data);
        wait(NULL);  // Wait for the child to finish
    }

    close(file_descriptor);

    return 0;
}

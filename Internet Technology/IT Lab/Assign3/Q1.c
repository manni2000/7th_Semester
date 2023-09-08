#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file_descriptor;

    // Open a file or create it if it doesn't exist
    file_descriptor = open("letter.txt", O_RDWR | O_CREAT, 0644);

    if (file_descriptor == -1) {
        perror("open");
        exit(1);
    }

    // Write a message to the file
    char message[] = "Dear friend, this course is fantastic!\n";
    write(file_descriptor, message, sizeof(message));

    // Move the file pointer to the beginning of the file
    lseek(file_descriptor, 0, SEEK_SET);

    // Read and print the file content
    char buffer[100];
    int bytes_read = read(file_descriptor, buffer, sizeof(buffer));

    if (bytes_read == -1) {
        perror("read");
        close(file_descriptor);
        exit(1);
    }

    buffer[bytes_read] = '\0';
    printf("File Content:\n%s", buffer);

    // Close the file
    close(file_descriptor);

    return 0;
}

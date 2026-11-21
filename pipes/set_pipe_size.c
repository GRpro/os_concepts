#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Try to set pipe size to 1MB
    int new_size = fcntl(pipefd[1], F_SETPIPE_SZ, 1024 * 1024);
    if (new_size == -1) {
        perror("fcntl - F_SETPIPE_SZ");
    } else {
        printf("Pipe size set to %d bytes\n", new_size);
    }

    // Optional: Get and print the current pipe size
    int actual_size = fcntl(pipefd[1], F_GETPIPE_SZ);
    if (actual_size == -1) {
        perror("fcntl - F_GETPIPE_SZ");
    } else {
        printf("Current pipe size is %d bytes\n", actual_size);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

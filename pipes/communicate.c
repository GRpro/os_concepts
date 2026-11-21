#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_COUNT 5
#define MSG_SIZE 64

int main() {
    int pipefd[2]; // pipefd[0] - read end, pipefd[1] - write end

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // --- Child Process: Consumer ---
        close(pipefd[1]); // Close unused write end

        char buffer[MSG_SIZE];
        for (int i = 0; i < MSG_COUNT; i++) {
            read(pipefd[0], buffer, MSG_SIZE);
            printf("Consumer: Received message '%s'\n", buffer);
            fflush(stdout);
        }

        close(pipefd[0]); // Close read end
    } else {
        // --- Parent Process: Producer ---
        close(pipefd[0]); // Close unused read end

        for (int i = 0; i < MSG_COUNT; i++) {
            char msg[MSG_SIZE];
            snprintf(msg, sizeof(msg), "Message #%d from producer", i + 1);
            write(pipefd[1], msg, strlen(msg) + 1);
            printf("Producer: Sent message '%s'\n", msg);
            fflush(stdout);
            sleep(1); // simulate work
        }

        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}

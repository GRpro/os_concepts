#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid_t current_pid = getpid();

    printf("Before fork: PID = %d, parent = %d\n", current_pid, getppid());
    fflush(stdout); // flush before fork so the line is not copied into the child

    pid = fork(); // Create a new process

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: Current = %d, PID = %d, Parent PID = %d\n", current_pid, getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process: Current = %d, PID = %d, Child PID = %d\n", current_pid, getpid(), pid);
        wait(NULL); // Wait for child process to finish
    }

    printf("Process PID = %d is exiting.\n", getpid());
    return 0;
}

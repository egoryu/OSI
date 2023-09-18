#include "kernel/types.h"
#include "user/user.h"

void main() {
    int fd[2];
    int child_pid;
    char message[10];

    if (pipe(fd) == -1) {
        printf("Ошибка при создании пайпа");
        exit(1);
    }
    dump();

    child_pid = fork();

    if (child_pid == -1) {
        printf("Ошибка при создании дочернего процесса");
        exit(1);
    }

    if (child_pid == 0) {
        read(fd[0], message, sizeof(message));
        close(fd[0]);
        printf("child %d: got %s\n", getpid(), message);

        write(fd[1], "pong", 5);
        close(fd[1]);

        exit(0);
    } else {
        write(fd[1], "ping", 5);
        close(fd[1]);

        read(fd[0], message, sizeof(message));
        close(fd[0]);
        printf("parent %d: got %s\n", getpid(), message);

        exit(0);
    }
}
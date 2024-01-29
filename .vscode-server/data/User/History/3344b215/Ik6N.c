#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handler_sigchild(int signal) {
    int status;
    pid_t child_pid = wait(&status);
    if (child_pid == -1) {
        printf("wait");
        exit(1);
    }
    printf("Child process %u terminated\n", child_pid);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler_sigchild;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        printf("sigaction");
        exit(1);
    }

    printf("Parent process %u started\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}

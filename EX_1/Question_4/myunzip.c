#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // Create pipes for communication between processes
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }
    else if (child_pid == 0) {
        // Child 1: gpg decryption
        close(pipe1[0]);
        dup2(pipe1[1], 1);
        close(pipe1[1]);

        // Decrypt using gpg
        execlp("gpg", "gpg", "--decrypt", "--passphrase", argv[2], "-o", "-", argv[1], NULL);

        // If execlp fails
        perror("exec gpg");
        printf("An error has occurred");
        return 1;
    }

    // Parent process
    close(pipe1[1]);
    dup2(pipe1[0], 0);
    close(pipe1[0]);

    pid_t gunzip_pid = fork();
    if (gunzip_pid == -1) {
        perror("fork");
        exit(1);
    } else if (gunzip_pid == 0) {

        // Child 2: gunzip
        close(pipe2[0]);
        dup2(pipe2[1], 1);
        close(pipe2[1]);

        // Gunzip
        execlp("gunzip", "gunzip", "-", NULL);

        // If execlp fails
        perror("exec gunzip");
        printf("An error has occurred");
        return 1;
    }

    // Parent process
    close(pipe2[1]);
    dup2(pipe2[0], 0);
    close(pipe2[0]);

    // Execute tar command
    execlp("tar", "tar", "xvf", "-", NULL);

    // If execlp fails
    perror("exec tar");
    printf("An error has occurred");
    return 1;
}

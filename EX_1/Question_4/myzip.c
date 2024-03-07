#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char *argv[]) {

    int pipe1[2];
    int pipe2[2];

    // fdarry THIS ARRARY DOES NOT EXIST
    // fd[0] = STDIN
    // fd[1] = STDOUT
    // fd[2] = STDERR
    // fd[3] = pipefdone[0];
    // fd[4] = pipefdone[1];
    // fd[5] = pipefdtwo[0];
    // fd[6] = pipefdtwo[1];

    // In pipes 0 means it works, 1 means it doesn't
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1){
        printf("An error has occured while creating pipe.");
    }

    pid_t child_pid;  // We we can see if fork was completed
    // Phase 1 : first child - responsible for the tar
    child_pid = fork();
    if (child_pid == -1) {
        printf("An error has occured while forking.");
        return 1;
    } else if (child_pid == 0) {
        close(pipe1[0]); // Note that we will always close unused ends to ensure that the data flows the correct direction
        close(pipe2[0]);
        close(pipe2[1]);

        dup2(pipe1[1], 1);

        close(pipe1[1]);


        execlp("tar", "tar", "cf", "-", argv[1], NULL);
        printf("An error has occured while tar");
        return 1;
    }

    // Phase 2 :second child - responsible for the gzip
    child_pid = fork();
    if (child_pid == -1) {
        printf("An error has occured while forking.");
        return 1;
    } else if (child_pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        dup2(pipe1[0], 0);

        close(pipe1[0]);

        dup2(pipe2[1], 1);

        close(pipe2[1]);


        execlp("gzip", "gzip", "-c", NULL);
        printf("An error has occured while gzip");
        return 1;
    }

    // Phase 3: third child - responsible for the gpg
    child_pid = fork();
    if (child_pid == -1) {
        printf("An error has occured while forking.");
        return 1;
    } else if (child_pid == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);

        dup2(pipe2[0], 0);

        close(pipe2[0]);


        execlp("gpg", "gpg", "--symmetric", "--passphrase", argv[2], "-o", "Compressed.gpg", "-", NULL);
        //here we use symmetric so same passphrase is used for both encryption and decryption
        printf("An error has occured while gpg");
        return 1;
    }

    // Close all open pipe ends
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all processes to end
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Compression Completed.\n");
    return 0;
}
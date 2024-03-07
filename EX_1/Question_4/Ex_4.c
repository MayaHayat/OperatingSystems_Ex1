#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    // Phase 1 - create 2 pipes to communicate between them

    int pipe1[2];

    int pipe2[2];

    pipe(pipe1);

    pipe(pipe2);

    // fd[0] = STDIN

    // fd[1] = STDOUT

    // fd[2] = STDERR

    // fd[3] = pipefdone[0];

    // fd[4] = pipefdone[1];

    // fd[5] = pipefdtwo[0];

    // fd[6] = pipefdtwo[1];

    // Make sure

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {

        printf("An error has occurred\n");

        return 1;
    }

    // only way to create process is fork - premission reasons

    if (fork() == 0)
    {

        // child pipe - tar

        close(1);

        dup2(pipe1[0], 1); // redirect to stdout

        char *arglist[] = {"tar", "-cv", "fileName", "-", NULL};

        execv("/bin/tar", arglist); // take binary code -> ram

        perror("Error executing tar");

        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {

        // child pipe - gzip

        close(0);

        close(1);

        dup2(pipe1[0], 1); // pipe1_stdin ->

        dup2(pipe2[1], 0); // into pipe2_stdout

        char *arglist[] = {"gzip", "-", NULL};

        execv("/bin/gzip", arglist);

        perror("Error executing gzip");

        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {

        // child pipe - gpg

        close(0);

        dup2(pipe2[1], 0); // redirect to stdin

        char *arglist[] = {"gpg", "-e", "--recipient", "Maya_Hayat", NULL};

        execv("/bin/gpg", arglist);

        perror("Error executing gpg");

        exit(EXIT_FAILURE);
    }

    // wait for all 3 to finish

    wait(NULL);

    wait(NULL);

    wait(NULL);

    printf("Compression finished.\n");

    return 0;
}
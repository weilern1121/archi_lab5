#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {

    int fd[2],child1,child2;

    //fd[0]-> for using read end    fd[1]-> for using write end
    char* lsCommand[3]= {"ls","-l",0};
    char* tailCommand[4]={"tail","-n","2",0};
    //#1 - Create a pipe.
    if(pipe(fd)==-1){
        perror("pipe(fd)1 error");
        exit(EXIT_FAILURE);
    }
    //#2 - Fork to a child process (child1).
    child1 = fork();
    //#3 - On the child1 process:
    if (child1 == 0) {
        close(1);                               //a. Close the standard output.
        dup(fd[1]);                             //b. Duplicate the write-end of the pipe using dup (see man).
        close(fd[1]);                           //c. Close the file descriptor that was duplicated.
        if(execvp(lsCommand[0],lsCommand)==-1){ //d. Execute "ls -l".
            perror("execvp1 error");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    //#4 -  On the parent process: Close the write end of the pipe.
    close(fd[1]);
    //#5
    child2 = fork(); //Fork again to a child process (child2).
    //#6 - On the child2 process:
    if (child2 == 0) {
        close(0);                                   //a. Close the standard input.
        dup(fd[0]);                                 //b. Duplicate the read-end of the pipe using dup.
        close(fd[0]);                               //c. Close the file descriptor that was duplicated.
        if(execvp(tailCommand[0],tailCommand)==-1){ //d. Execute "tail -n 2".
            perror("execvp2 error");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    //#7 - On the parent process: Close the read end of the pipe.
    close(fd[0]);
    //#8 - Now wait for the child processes to terminate, in the same order of their execution. 
    waitpid(child1, 0, 0);
    waitpid(child2, 0, 0);

    return 0;
}

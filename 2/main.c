#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {

    int fd[2],child1,child2;

    //fd[0]-> for using read end    fd[1]-> for using write end
    char* lsCommand[3]= {"ls","-l",0};
    char* tailCommand[4]={"tail","-n","2",0};
    //#1
    if(pipe(fd)==-1){
        perror("pipe(fd)1 error");
        exit(EXIT_FAILURE);
    }
    //#2
    child1 = fork();
    //#3
    if (child1 == 0) {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        if(execvp(lsCommand[0],lsCommand)==-1){
            perror("execvp1 error");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    //#4
    close(fd[1]);
    //#5-6
    child2 = fork();
    if (child2 == 0) {
        close(0);
        dup(fd[0]);
        close(fd[0]);
        if(execvp(tailCommand[0],tailCommand)==-1){
            perror("execvp2 error");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    //#7
    close(fd[0]);
    //#8
    waitpid(child1, 0, 0);
    waitpid(child2, 0, 0);

    return 0;
}
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "line_parser.h"
//#include "line_parser.c"


int execute(cmd_line *line){
    int inputStream,outputStream;
    //check the input and output fields before execute
    if(line->input_redirect!=NULL) {
        inputStream = open(line->input_redirect, O_RDONLY, 0);
        if(inputStream<0) {
            perror("inputStream error");
            exit(EXIT_FAILURE);
        }
        dup2(inputStream,0);
    }
    if(line->output_redirect!=NULL) {
        outputStream = open(line->output_redirect, O_TRUNC | O_CREAT | O_WRONLY, 0644);
        if(outputStream<0) {
            perror("outputStream error");
            exit(EXIT_FAILURE);
        }
        dup2(outputStream,1);
    }
    int output=execvp(line->arguments[0],line->arguments);


    //close streaming ->for each son
    if(line->output_redirect!=NULL)
        close( outputStream);
    if(line->input_redirect!=NULL)
        close(inputStream);

    // -1 ->error
    return output;
}

int main(int argc, char *argv[]) {
    //buf=getcwd input (getting the address)
    char buf[PATH_MAX];
    //userStream = used in fgets input
    char userStream[2048];
    int done=0;
    char* s;
    int cpid;

    while(1){
        //get the current path
        getcwd(buf, PATH_MAX);
        printf("%s",buf);
        //get the current command line
        s=fgets(userStream,2048,stdin);
        if(strcmp(s,"\n")!=0|| strcmp(s," \n")!=0 || strcmp(s,"    \n")!=0) {
            //if the execution order is quit ->exit 0
            if (strcmp(s, "quit") == 0 || strcmp(s, "quit\n") == 0)
                exit(EXIT_SUCCESS);
            //else - go to parse the line and execute it
            cmd_line *line = parse_cmd_lines(s);
            cpid = fork();
            if (cpid == 0) {
                //sent to execute in execute func, if -1 ->error
                done = execute(line);
                if (done == -1) {
                    perror("illegal execute line");
                    exit(EXIT_FAILURE);
                }

                exit(0);

            }


            //check if there is a need to wait for son, if 0->don't wait
            if (line->blocking == 1)
                waitpid(cpid, 0, 0);
            //wait(cpid);
            //release the curr cmd_line from memory
            free_cmd_lines(line);
        }
    }



    return 0;
}

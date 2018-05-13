#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "line_parser.h"
//#include "line_parser.c"


int execute(cmd_line *line){
    int output=execvp(line->arguments[0],line->arguments);
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
        printf("%s\n",buf);
        //get the current command line
        s=fgets(userStream,2048,stdin);
        //if the execution order is quit ->exit 0
        if(strcmp(s,"quit")==0 || strcmp(s,"quit\n")==0)
            exit(EXIT_SUCCESS);
        //else - go to parse the line and execute it
        cmd_line* tmp=parse_cmd_lines(s);
        cpid=fork();
        if(cpid==0) {
            //sent to execute in execute func, if -1 ->error
            done = execute(tmp);
            if (done == -1) {
                perror("illegal execute line");
                exit(EXIT_FAILURE);
            }
            else exit(EXIT_SUCCESS);
        }
        //release the curr cmd_line from memory
        free_cmd_lines(tmp);
        //wait(cpid);
    }

    return 0;
}
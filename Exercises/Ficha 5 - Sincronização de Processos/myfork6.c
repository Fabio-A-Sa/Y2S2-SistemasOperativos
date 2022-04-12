#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX_HISTORY_SIZE 10

int main(int argc, char* argv[]) {

    char  buf[1024];
    char* command;
    pid_t pid;
    static char *history[MAX_HISTORY_SIZE];
    int index = 0;

    for( ; ; ) {

        fprintf(stdout, "$ ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL) break;
        command[strlen(buf) - 1] = '\0';

        if((pid = fork()) == -1) {
            fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
            continue;
            
        } else if (pid == 0) {

            char* result;
            char *stop = "exit";
            char *getHistory = "history";

            history[(index % MAX_HISTORY_SIZE)] = command;
            index++;

            if ((result = strstr(stop, command)) != NULL) {
                printf("Exit!\n");
                return 0;
            } else if ((result = strstr(getHistory, command)) != NULL) {
                for (int i = 0 ; i < MAX_HISTORY_SIZE ; i++) {
                    if (history[i] != NULL) printf("%s\n", history[i]);
                }
            } else {
                execlp(command, command, (char *)0); 
                fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf, strerror(errno));
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        } 

        if ((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n", argv[0], strerror(errno));
    }

    exit(EXIT_SUCCESS);
}
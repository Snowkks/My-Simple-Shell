#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char *input = NULL;
    size_t buffer = 0;

    while(1){
        printf("myshell>");

        int read_status = getline(&input, &buffer, stdin);

        if( read_status == -1 ){
            printf("Exiting...");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        const char *delimeter = " ";
        char *command[64];
        int i = 1;

        command[0] = strtok( input, delimeter );

        while ( command[i - 1] != NULL ){
            command[i] = strtok( NULL, delimeter );
            if ( command[i - 1] == NULL ) {
                break;
            }
            i++;
        }

        command[i] = NULL;

        if( strcmp(command[0], "cd") == 0 ){
            if( command[1] == NULL ){
                chdir(getenv("HOME"));
            }else {
                chdir(command[1]);
            }

            continue;
        }

        if( strcmp(command[0], "exit") == 0 ){
            printf("Exiting...");
            break;
        }

        int pid = fork();


        if(pid < 0){ continue; }

        if(pid == 0){
            execvp(command[0], command);
        }

        if( pid > 0 ){
            wait(NULL);
        }
    }

    free(input);
    return 0;
}

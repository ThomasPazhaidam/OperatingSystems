#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/*
 * 
 * Author: Thomas Pazhaidam
 */


char* rdprompt(){
    
    int i = 0;
    char *input=malloc(sizeof(char)*100);
    int c;
    
    while(true){
        c = getchar();
        
        if(c == EOF || c == '\n'){
            input[i]='\0';
            return input;
        }else{
            input[i] = c;
        }
        i++;
    }
}

char prompt(){
    printf("your command>");
}
char **params(char *line, char *s){
    
    int i = 0;
    char **tokens= malloc(sizeof(char)*100);
    char *token;
    token = strtok(line, s);
    
    while(token != NULL){
        tokens[i] = token;
        i++;
        token = strtok(NULL, s);
    }
    tokens[i] = NULL;
    return tokens;
}


int main(int argc, char** argv) {
    char **param1, **param2;
    char *in1= malloc(sizeof(char)*100);
    char *in2= malloc(sizeof(char)*100);
    int i = 0;
    int j = 0;
    int io[2];
    
    
    char *input;
    
    while(true){
        prompt();
        
        input = rdprompt();
        
        while (input[i] != '|') {
            in1[i] = input[i];
            i++;
        }

        in1[i] = '\0';
        i++;

        while (input[i] != '\0') {
            in2[j] = input[i];
            i++;
            j++;
        }

        in2[j] = '\0';

        param1 = params(in1, " ");
        param2 = params(in2, " ");

        pipe(io);

        if (fork() == 0) {
            dup2(io[1], STDOUT_FILENO);
            close(io[0]);
            execvp(param1[0], param1);
        } else {
            dup2(io[0], STDIN_FILENO);
            close(io[1]);
            execvp(param2[0], param2);
        }
    }

    return 0;
}
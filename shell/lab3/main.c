#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
void prmpt(){
    printf("your command> ");
}
void rdprmpt(char cmd[], char *param[]){
    char ln[1024]={NULL};
    int cnt=0;
    int i=0;
    int j=0;
    char *arr[100];
    char *token;
    
    while(true){
        int c=fgetc(stdin);
        ln[cnt++]=(char)c;
        if(c=='\n'){
            break;
        }
    }
    if(cnt==1){
        return;
    }
    
    token=strtok(ln," \n");
    
    while(token !=NULL){
        arr[i++]=strdup(token);
        token=strtok(NULL," \n");
    }
    
    strcpy(cmd,arr[0]);
    
    for(j=0;j<i;j++)
        param[j]=arr[j];
    param[i]=NULL;
    
}
int main(){
    char cmd[100];
    char cmds[100];
    char *parameters[100];
    char *env[]={(char*)"PATH=/bin",0};
    while(true){
        prmpt();
        rdprmpt(cmds,parameters);
        if(fork()!=0)
            wait(NULL);
        else{
            strcpy(cmd,"/bin/");
            strcat(cmd,cmds);
            execve(cmd,parameters,env);
        }
        if(strcmp(cmds,"exit")==0)
            break;
    }
    return 0;
}
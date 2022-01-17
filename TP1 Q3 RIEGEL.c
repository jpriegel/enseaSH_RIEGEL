#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CMD_SIZE 100

const char prompt[] = "enseash$";
const char msg[] = "Bienvenue dans le Shell ENSEA.\n"
                   "Pour quitter, tapez 'exit'.\n";
char exitmsg[] = "bye bye...\n";

int main() {
    char cmd[CMD_SIZE];
    write(STDOUT_FILENO, msg, sizeof(msg));
    size_t cmdlength;
    int status;
    pid_t ret;

    while (1) {
        write(STDOUT_FILENO, prompt, sizeof(prompt)); //affiche "enseash$"
        cmdlength = read(STDIN_FILENO, cmd, sizeof(cmd));
        cmd[cmdlength - 1] = '\0';

        if (strncmp("exit", cmd, strlen("exit")) == 0 || cmdlength == 0) {
            break; //exit
        } else {
            ret = fork();
            if (ret != 0) { //dans le pere
                wait(&status);
            } else { //dans le fils
                execlp(cmd, cmd, (char *) NULL);
                exit(EXIT_FAILURE);
            }
        }
    }
    write(STDOUT_FILENO, exitmsg, sizeof(exitmsg));
    exit(EXIT_SUCCESS);

}
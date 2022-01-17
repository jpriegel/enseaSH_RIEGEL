#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define CMD_SIZE 100

const char prompt[] = "enseash$";
const char msg[] = "Bienvenue dans le Shell ENSEA.\n"
                   "Pour quitter, tapez 'exit'.\n";
char exitmsg[] = "bye bye...\n";
char exitmsg2[CMD_SIZE];
struct timespec start;
struct timespec stop;
clockid_t clk_id;
int conv = 1000000;

//Dans cette question on apporte une information suplementaire a l'utilisateur: le temps d'execution de la commande.
int main() {
    char cmd[CMD_SIZE];
    write(STDOUT_FILENO, msg, sizeof(msg));
    size_t cmdlength;
    int status;
    pid_t ret;
    clk_id = CLOCK_REALTIME;

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
                clock_gettime(clk_id, &stop); //fin chrono
                if (WIFEXITED(status)) {
                    sprintf(exitmsg2, "enseash [exit: %d | %ld ms]", WEXITSTATUS(status),
                            (stop.tv_nsec - start.tv_nsec) / conv); //affiche temps en 10^-3s -->1ms
                    write(STDOUT_FILENO, exitmsg2, strlen(exitmsg2));
                } else if (WIFSIGNALED(status)) {
                    sprintf(exitmsg2, "enseash [exit: %d | %ld ms]", WTERMSIG(status),
                            (stop.tv_nsec - start.tv_nsec) / conv); /
                    write(STDOUT_FILENO, exitmsg2, strlen(exitmsg2));
                }
            } else { //dans le fils
                clock_gettime(clk_id, &start);//debut chrono
                execlp(cmd, cmd, (char *) NULL);
                exit(EXIT_FAILURE);
            }
        }
    }
    write(STDOUT_FILENO, exitmsg, sizeof(exitmsg));
    exit(EXIT_SUCCESS);
}
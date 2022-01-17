
#include <unistd.h>
#include <stdlib.h>

#define CMD_SIZE 100

const char prompt[] = "enseash$";
const char msg[] = "Bienvenue dans le Shell ENSEA.\n"
                   "Pour quitter, tapez 'exit'.\n";

//le programme est clair: on veut afficher le msg dans le shell
int main() {
    char cmd[CMD_SIZE];
    write(STDOUT_FILENO, msg, sizeof(msg));
    write(STDOUT_FILENO, prompt, sizeof(prompt));

    exit(EXIT_SUCCESS);
}

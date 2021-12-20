#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 256


int main(int argc, char *argv[]) {
    char input[INPUT_MAX];
    while (1)
    {
        printf("[<-] ");
        fgets(input, INPUT_MAX, stdin);
        if (strncmp(input, "exit\n", 5) == 0) {
            printf("[->] bye!!\n");
            break;
        }
    }
}
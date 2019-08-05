#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

int myexec(const char *cmd) {
    FILE *pp = popen(cmd, "r");
    if (!pp) {
        return -1;
    }
    char tmp[1024];

    char propchar[10];
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (strncmp(tmp,"propagation",11) == 0){
            strncpy(propchar,tmp+24,5);
        }
    }

    int propagation = atoi(propchar);

    pclose(pp);
    return propagation;
}

int main() {
    int var;

    float allresult[10][10];
    for (var = 50; var <= 500 ; var = var + 50){
        for (int ratio = 1 ; ratio <= 10 ; ratio++){
            int clause = var * ratio;
            char dirname[100];
            sprintf(dirname, "%d-%d",var, clause);
            chdir(dirname);
            int result[10];
            int total = 0;
            printf("%d var & %d clauses : \n",var, clause);
            for (int i = 0; i < 10; i++) {
                char exec[20];
                sprintf(exec,"minisat %d-%d-%d.txt",var,clause,i+1);
                result[i] = myexec(exec);

                total = total + result[i];
                printf("%d ", result[i]);
                if (i == 9){
                    printf("\nAverage = %f\n\n", (float)total / 10);
                }
                int j = var / 50 - 1;
                allresult[j][clause / 50 - 1] = (float)total / 10;
            }
            chdir("/home/parallels/CLionProjects/terminaltry/cmake-build-debug");
        }
    }

    for (int i = 0; i < 10; i++){
        printf("%d var : ", (i + 1) * 50);
        for (int j = 0; j < 10; j++){
            printf("%f ",allresult[i][j]);
        }
        printf("\n");
    }
    return 0;
}
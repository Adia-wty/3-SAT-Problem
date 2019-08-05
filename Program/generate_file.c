// created by Tianyi Wang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


#define MODE (S_IRWXU | S_IRWXG | S_IRWXO)


void generate(int var, int ratio){
    int clause = var * ratio;
    srand((unsigned)time(NULL));
    int instance = 10; // need to change to 20 afterwards

    char fileformat[5] = ".txt";
    char filename1[10];
    char dirname[10];

    sprintf(filename1, "%d-%d-",var,clause);
    sprintf(dirname, "%d-%d",var,clause);


    FILE *fp;
    mkdir(dirname, MODE);
    chdir(dirname);

    for (int i = 0; i < instance; i++)
    {
        char presentfile[20] = "";
        char number[2];
        sprintf(number,"%d",i + 1);
        strcat(presentfile,filename1);
        strcat(presentfile,number);
        strcat(presentfile,fileformat);
        fp = fopen(presentfile,"w");

        fprintf(fp, "p cnf %d %d\n", var, clause);

        int all[var];
        for (int j = 0; j < var; j ++){
            all[j] = 1;
        }

        int a = rand() % var + 1;
        int sign = rand() % 2;
        if (sign == 1){ a = -a;}

        int b = rand() % var + 1;
        sign = rand() % 2;
        if (sign == 1){ b = -b;}

        fprintf(fp, "%d %d %d 0\n", var, a, b);

        for (int j = 1; j < clause; j++)
        {
            for (int m = 0; m < 3; m++)
            {
                int count = 0;
                for (int k = 0; k < var; k++){
                    count = count + all[k];
                }
                if (count > 0){
                    int flag = 1;
                    while (flag == 1){
                        int v = rand() % var;
                        if (all[v] == 1){
                            all[v] = 0;
                            v = v + 1;
                            int sign = rand() % 2;
                            if (sign == 1){ v = - v;}
                            fprintf(fp, "%d ", v);
                            flag = 0;
                        }
                    }
                }
                else {
                    int v = rand() % var + 1;
                    int sign = rand() % 2;
                    if (sign == 1){ v = -v;}
                    fprintf(fp, "%d ", v);
                }
            }
            fprintf(fp,"0\n");
        }
        fclose(fp);
    }
    chdir("..");
}

int main() {
    int var;
    char resource[80] = "/home/parallels/CLionProjects/terminaltry/cmake-build-debug";
    chdir(resource);
    for (var = 50; var <= 500 ; var = var + 50){
        char dirname[100];
        sprintf(dirname, "%s/%d",resource,var);
        chdir(dirname);
        for (int ratio = 1; ratio <= 10; ratio++){
            generate(var, ratio);
        }
        chdir(resource);
    }

    return 0;
}
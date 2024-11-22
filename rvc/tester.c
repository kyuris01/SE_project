#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define ITERATION_NUM 10

void tester();
bool positionSequence[ITERATION_NUM][4]; //일련의 obstacle위치와 dust의 존재유무를 저장하는 이차원배열


void tester() {
    

    srand(time(NULL));
    
    for (int i = 0; i< ITERATION_NUM ; i++) {
        if ((positionSequence[i-1][1] == 1) || (positionSequence[i-1][2] == 1)) {
            positionSequence[i][0] = 0;
            for (int k = 1;k < 4; k++) {
                positionSequence[i][k] = rand() % 2;
            }
            continue;
        }
        for(int j = 0; j < 4 ; j++) {
            // int randomExistence;
            // randomExistence = rand() % 2;
            positionSequence[i][j] = rand() % 2;
        }

    }


    for (int i = 0; i< ITERATION_NUM ; i++) {
        for(int j = 0; j < 4 ; j++) {
            printf("%d", positionSequence[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
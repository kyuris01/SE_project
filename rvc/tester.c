#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define ITERATION_NUM 10

void tester();
// char*inputData[ITERATION_NUM];
bool positionSequence[ITERATION_NUM][4];


void tester() {
    
    bool positionAtTheMoment;

    srand(time(NULL));
    
    for (int i = 0; i< ITERATION_NUM ; i++) {
        for(int j = 0; j < 4 ; j++) {
            int randomExistence;
            randomExistence = rand() % 2;
            positionSequence[i][j] = randomExistence;
        }

    }

    // for (int i = 0; i < ITERATION_NUM; i++) {
    //     inputData[i] = (char*)malloc(5 * sizeof(char)); // 문자열 저장 공간 할당 (4자리 + '\0')
    //     for (int j = 0; j < 4; j++) {
    //         inputData[i][j] = positionSequence[i][j] ? '1' : '0'; // bool 값을 문자로 변환
    //     }
    //     inputData[i][4] = '\0'; // null 문자 추가
    // }

    // for (int i = 0; i < ITERATION_NUM; i++) {
    //     printf("%s\n", inputData[i]);
    //     free(inputData[i]); // 동적 메모리 해제
    // }

    for (int i = 0; i< ITERATION_NUM ; i++) {
        for(int j = 0; j < 4 ; j++) {
            printf("%d", positionSequence[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
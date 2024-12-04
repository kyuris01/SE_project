#include "rvc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// RVC 유닛 테스트 함수들
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();
void Test10();
void Test11();
void Test12();
void Test13();
void Test14();
void Test15();
void Test16();
void Test17();
void Test18();
void Test19();
void Test20();
void Test21();

//TEST 2
// 장애물 인풋을 주고 잘 감지하는지 테스트
void Test1() {
    frontSensorInput = true;
    leftSensorInput = false;
    rightSensorInput = false;

    Obstacle obstacle = ObstacleLocation();
    assert(obstacle.frontobstacle == true);
    assert(obstacle.leftobstacle == false);
    assert(obstacle.rightobstacle == false);

    printf("Test 1 Passed: ObstacleLocation correctly identifies obstacles.\n");
}

//TEST 3
// DustExistence() 테스트
void Test2() {
    dustSensorInput = true;
    assert(DustExistence() == true);
    printf("Test 2 Passed: DustExistence correctly identifies dust.\n");
}

void Test3() {
    dustSensorInput = false;
    assert(DustExistence() == false);
    printf("Test 3 Passed: DustExistence correctly identifies dust.\n");
}

//TEST 4
// moveForward(), turnLeft(), turnRight(), moveBackward()시의 동작과 각각의 power 상태를 테스트
void Test4() {
    moveForward();
    assert((strcmp(motorCommand, "Moving forward...\n") == 0));
    printf("Test 4 Passed: Movement functions set motorCommand(moveForward) correctly.\n");
}

void Test5() {
    turnLeft();
    assert((strcmp(motorCommand, "Turn Left for 5 Tick...\n") == 0));
    printf("Test 5 Passed: Movement functions set motorCommand(turnLeft) correctly.\n");
}

void Test6() {
    turnRight();
    assert((strcmp(motorCommand, "Turn Right for 5 Tick...\n") == 0));
    printf("Test 6 Passed: Movement functions set motorCommand(turnRight) correctly.\n");
}

void Test7() {
    moveBackward();
    assert((strcmp(motorCommand, "Moving Backward...\n") == 0));
    printf("Test 7 Passed: Movement functions set motorCommand(moveBackward) correctly.\n");
}

void Test8() {
    // 출력 리다이렉트 설정
    freopen("output.log", "w", stdout);

    // `stop()` 호출
    stop();

    // 출력 플러시 및 파일 닫기
    fflush(stdout);
    fclose(stdout);

    // 출력 파일 읽기
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    // 출력 버퍼에 읽기
    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), sizeof(outputBuffer) - 1, file);
    outputBuffer[1023] = '\0'; // Null-terminate
    fclose(file);

    // 예상 출력과 비교
    const char *expectedOutput = "Stop...\nMoving Backward...\n";
    assert(strcmp(outputBuffer, expectedOutput) == 0);

    // 테스트 성공 메시지
    printf("Test 8 Passed: stop() calls moveBackward.\n");

    // 파일 정리
    remove("output.log");
}

void Test9() {
    // 시작 시간 기록
    time_t startTime = time(NULL);

    // `turnRight()` 호출
    turnRight();

    // 종료 시간 기록
    time_t endTime = time(NULL);

    // 실행 시간 계산
    double duration = difftime(endTime, startTime);

    // 실행 시간이 5초에 근접한지 확인 (허용 오차 ±1초)
    assert(duration >= 4.0 && duration <= 6.0);

    // 테스트 성공 메시지 출력
    printf("Test 9  Passed: turnRight() sleeps for approximately 5 seconds (%.2f seconds).\n", duration);
}

void Test10() {
    // 시작 시간 기록
    time_t startTime = time(NULL);

    // `turnRight()` 호출
    turnLeft();

    // 종료 시간 기록
    time_t endTime = time(NULL);

    // 실행 시간 계산
    double duration = difftime(endTime, startTime);

    // 실행 시간이 5초에 근접한지 확인 (허용 오차 ±1초)
    assert(duration >= 4.0 && duration <= 6.0);

    // 테스트 성공 메시지 출력
    printf("Test 10  Passed: turnLeft() sleeps for approximately 5 seconds (%.2f seconds).\n", duration);
}


//시스템 테스트
//TEST 8 move FW-앞에 장애물이 없고, 좌우에 모두 장애물이 있는 경우 
void Test11() {
    // 아무 장애물도 없는 경우 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0},
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0},
            {0, 1, 1, 0}, {0, 1, 1, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 11 Passed: Controller output matches expected values.\n");
}
//Test9 좌우에 장애물이 없는 경우에도 앞으로 가는지 테스트 
void Test12() {
    // 아무 장애물도 없는 경우 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={
            {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0},
            {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0},
            {0, 1, 1, 0}, {0, 0, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 12 Passed: Controller output matches expected values.\n");
}

// Test10 앞으로 가다가 먼지 발견 시 먼지 제거 후 다시 전진 (3,4,5,6,7,8)
void Test13() {

    bool testcase[ITERATION_NUM][4]={ 
            {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 1},
            {0, 1, 0, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 1, 1, 1},
            {0, 0, 1, 0}, {0, 1, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    freopen("output.log", "w", stdout);

    // bool testcase[ITERATION_NUM][4]={ 
    //         {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 1},
    //         {0, 1, 0, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 1, 1, 1},
    //         {0, 0, 1, 0}, {0, 1, 0, 0}
    // };

    // memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Cleaning Power ON\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Cleaning Power ON\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Cleaning Power ON\n"
                                "Moving forward...\n"
                                "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "-----------------\n"
                                "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "Moving forward...\n"
                                "-----------------\n"
                               "Dust Detected\n"
                                "Cleaning Power UP\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Dust Cleared\n"
                                "Cleaning Power ON\n"
                                "Cleaning Power ON\n"
                                "Moving forward...\n"
                                "-----------------\n"
                                "Cleaning Power ON\n"
                                "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 13 Passed: Controller output matches expected values.\n");
}


void Test14() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 좌측에만 장애물 없는 상황

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3
        {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, 
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));

    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Left for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 14 Passed: Controller output matches expected values.\n");
}

void Test15() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 좌우측 모두 장애물 없는 상황 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3 , 좌회전했으면 우측엔 반드시 장애물 존재 
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, 
            {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
            {0, 0, 0, 0}, {0, 0, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Left for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 15 Passed: Controller output matches expected values.\n");
}

void Test16() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 좌우측 모두 장애물 없는 상황 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3 , 좌회전했으면 우측엔 반드시 장애물 존재 
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, 
            {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
            {0, 0, 0, 0}, {0, 0, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Left for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 16 Passed: Controller output matches expected values.\n");
}

void Test17() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 우측에만 장애물이 없는 상황

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3 , 우회전했으면 좌측엔 반드시 장애물 존재 
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, 
            {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
            {0, 0, 0, 0}, {0, 0, 0, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Right for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 17 Passed: Controller output matches expected values.\n");
}

void Test18() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 좌우측 모두 장애물 존재하여 후진 시 좌우 모두 장애물이 있는 경우 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3 
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 0}, 
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0},
            {0, 1, 1, 0}, {0, 1, 1, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Stop...\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 18 Passed: Controller output matches expected values.\n");
}

void Test19() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 후진하다가 좌우측 중 좌측에만 장애물이 없는 상황

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3, 8 후진하다가 우회전 -> 좌측에 반드시 장애물 없음
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 0}, 
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0},
            {0, 0, 0, 0}, {0, 1, 1, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Stop...\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Right for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 19 Passed: Controller output matches expected values.\n");
}

void Test20() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 후진하다가 좌우측 둘 다 장애물이 없는 상황 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3, 8 후진하다가 우회전 -> 좌측에 반드시 장애물 없음
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 0}, 
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
            {0, 0, 0, 0}, {0, 1, 1, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Stop...\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Left for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 20 Passed: Controller output matches expected values.\n");
}

void Test21() {
    //먼지가 없는 경우, 직진하다가 정면 장애물, 후진하다가 좌우측 둘 다 장애물이 없는 상황 

    freopen("output.log", "w", stdout);

    bool testcase[ITERATION_NUM][4]={ //3, 8 후진하다가 우회전 -> 좌측에 반드시 장애물 없음
            {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 0}, 
            {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0},
            {0, 0, 0, 0}, {0, 1, 1, 0}
    };

    memcpy(positionSequence, testcase, sizeof(positionSequence));
    Controller();

    fflush(stdout);
    fclose(stdout);
    
    FILE *file = fopen("output.log", "r");
    assert(file != NULL);

    char outputBuffer[1024];
    fread(outputBuffer, sizeof(char), 1024, file);
    fclose(file);

    // Step 6: 예상 출력과 비교
    const char *expectedOutput = "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Stop...\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Moving Backward...\n"
                                 "-----------------\n"
                                 "Cleaning Power OFF\n"
                                 "Turn Left for 5 Tick...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n"
                                 "-----------------\n"
                                 "Cleaning Power ON\n"
                                 "Moving forward...\n";
                                 
    assert(strstr(outputBuffer, expectedOutput) != NULL);

    // Clean up
    remove("output.log");

    printf("Test 21 Passed: Controller output matches expected values.\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: Test name argument is required.\n");
        return 1;
    }

    // 명령줄 인수로 실행할 테스트 결정
    if (strcmp(argv[1], "--test1") == 0) {
       Test1();
    } else if (strcmp(argv[1], "--test2") == 0) {
        Test2();
;    } else if (strcmp(argv[1], "--test3") == 0) {
        Test3();
    } else if (strcmp(argv[1], "--test4") == 0) {
        Test4();
    } else if (strcmp(argv[1],  "--test5") == 0) {
        Test5();
    } else if (strcmp(argv[1],  "--test6") == 0) {
        Test6();
    } else if (strcmp(argv[1],  "--test7") == 0) {
        Test7();
    } else if (strcmp(argv[1],  "--test8") == 0) {
        Test8();
    } else if (strcmp(argv[1],  "--test9") == 0) {
        Test9();
    } else if (strcmp(argv[1],  "--test10") == 0) {
        Test10();
    } else if (strcmp(argv[1],  "--test11") == 0) {
        Test11();
    } else if (strcmp(argv[1],  "--test12") == 0) {
        Test12();
    } else if (strcmp(argv[1],  "--test13") == 0) {
        Test13();
    } else if (strcmp(argv[1],  "--test14") == 0) {
        Test14();
    } else if (strcmp(argv[1],  "--test15") == 0) {
        Test15();
    } else if (strcmp(argv[1],  "--test16") == 0) {
        Test16();
    } else if (strcmp(argv[1],  "--test17") == 0) {
        Test17();
    } else if (strcmp(argv[1],  "--test18") == 0) {
        Test18();
    } else if (strcmp(argv[1],  "--test19") == 0) {
        Test19();
    } else if (strcmp(argv[1],  "--test20") == 0) {
        Test20();
    } else if (strcmp(argv[1],  "--test21") == 0) {
        Test21();
    } else {
        printf("Error: Unknown test name '%s'.\n", argv[1]);
        return 1;
    }

    printf("Test '%s' passed successfully.\n", argv[1]);
    return 0;
}





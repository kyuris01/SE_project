#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> 
#include <string.h>
#define ITERATION_NUM 10

bool frontSensorInput = false;
bool leftSensorInput = false;
bool rightSensorInput = false;
bool dustSensorInput = false; 

typedef struct {
    bool frontobstacle;
    bool leftobstacle;
    bool rightobstacle;
} Obstacle;

char* Power = "ON"; //초기값 지정 
char* motorCommand = "Moving forward...\n";

extern void tester();
extern bool positionSequence[ITERATION_NUM][4];

bool frontSensor();
bool leftSensor();
bool rightSensor();
bool dustSensor();

Obstacle ObstacleLocation();
bool DustExistence();

//Direction
void moveForward();
void turnLeft();
void turnRight();
void moveBackward();
void stop();

//Cleaning Power 
void cleaningPower(char* power);
// 메인 컨트롤러
void Controller();
//Output Interface
void motorInterface(char* motorCommand);
void cleanerInterface(char* power);

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // 버퍼에 남아 있는 데이터 제거
}

int main() {
    tester();
    Controller(); // Controller 호출 
    return 0;
}

void Controller() {

    Power = "ON"; // 초기 상태는 "ON"
    cleaningPower(Power);
    moveForward(); // 초기 상태는 전진
    int i = 0;
    while (1) { // 무한 루프
        if(i == ITERATION_NUM) {
            break;
        }
        printf("-----------------\n");
        frontSensorInput = positionSequence[i][0];
        leftSensorInput = positionSequence[i][1];
        rightSensorInput = positionSequence[i][2];
        dustSensorInput = positionSequence[i][3];

        // 장애물 감지
        Obstacle obstacleDetected = ObstacleLocation();
        bool F = obstacleDetected.frontobstacle;
        bool L = obstacleDetected.leftobstacle;
        bool R = obstacleDetected.rightobstacle;
        bool Dust = DustExistence();

        if (strcmp(motorCommand, "Moving Backward...\n") == 0) { //Controller의 방향결정 로직 
            if (!L) {
                Power = "OFF";
                cleaningPower(Power);
                turnLeft();
            } else if (L && !R) {
                Power = "OFF";
                cleaningPower(Power);
                turnRight();
            } else {
                Power = "OFF";
                cleaningPower(Power);
                moveBackward();
            }
        } else {
            if (!F) {
                if(!Dust && (strcmp(Power, "UP") == 0)) {
                    printf("Dust Cleared\n");
                    Power = "ON";
                    cleaningPower(Power); 
                }

                Power = "ON";
                cleaningPower(Power);
                moveForward();

                if(Dust && (strcmp(Power, "ON") == 0)) {
                    printf("Dust Detected\n");
                    Power = "UP";
                    cleaningPower(Power);
                }
            } else {
                if (F && !L) {
                    Power = "OFF";
                    cleaningPower(Power);
                    turnLeft();
                } else if (F && L && !R) {
                    Power = "OFF";
                    cleaningPower(Power);
                    turnRight();
                } else if (F && L && R) {
                    Power = "OFF";
                    cleaningPower(Power);
                    stop();
                }
            }
        }
        sleep(1); // 1초 동안 수행 
        i++;
    }
}

Obstacle ObstacleLocation() {
    Obstacle obstacle;
    obstacle.frontobstacle = frontSensor();
    obstacle.leftobstacle = leftSensor();
    obstacle.rightobstacle = rightSensor();
    return obstacle;
}

bool DustExistence() {
    return dustSensorInput; // 먼지 센서 값
}

bool frontSensor() {
    return frontSensorInput; // 입력받은 값을 반환
}

bool leftSensor() {
    return leftSensorInput; // 입력받은 값을 반환
}

bool rightSensor() {
    return rightSensorInput; // 입력받은 값을 반환
}

bool dustSensor() {
    return dustSensorInput; // 먼지 센서 값
}

void moveForward() {
    motorCommand = "Moving forward...\n";
    motorInterface(motorCommand);
}

void turnLeft() {
    motorCommand = "Turn Left for 5 Tick...\n";
    motorInterface(motorCommand);
    sleep(5); //5초 동안 수행
    
}

void turnRight() {
    motorCommand = "Turn Right for 5 Tick...\n";
    motorInterface(motorCommand);
    sleep(5); //5초 동안 수행 
}

void stop() {
    printf("Stop...\n");
    moveBackward();
}

void moveBackward() {
    motorCommand = "Moving Backward...\n";
    motorInterface(motorCommand);
}

void cleaningPower(char* power) {
    cleanerInterface(power);
}

void motorInterface(char* motorCommand) {
    printf("%s", motorCommand);
}

void cleanerInterface(char* power) {
    printf("Cleaning Power %s\n", power);
}

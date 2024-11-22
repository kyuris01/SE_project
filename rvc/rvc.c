#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // sleep 함수 사용
#include <string.h>
#define ITERATION_NUM 10
// 글로벌 변수로 센서 값을 저장
bool frontSensorValue = false;
bool leftSensorValue = false;
bool rightSensorValue = false;
bool dustSensorValue = false; // 기본값은 먼지가 있다고 가정

typedef struct {
    bool frontobstacle;
    bool leftobstacle;
    bool rightobstacle;
} Obstacle;

char* Power = "ON"; // ON, OFF, UP
char* motorCommand = "Moving forward...\n";

extern void tester();
extern bool positionSequence[ITERATION_NUM][4];

bool frontSensor();
bool leftSensor();
bool rightSensor();
bool dustSensor();

Obstacle determineObstacleLocation();
bool determineDustExistence();

// 모터 동작
void moveForward();
void turnLeft();
void turnRight();
void moveBackward();
void stop();

// 클리닝 파워 제어
void cleaningPower(char* power);

// 메인 컨트롤러
void Controller();
void* powerUp(void* arg);
//output Interface
void motorInterface(char* motorCommand);
void cleanerInterface(char* power);

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // 버퍼에 남아 있는 데이터 제거
}

int main() {
    // for (int i = 0; i < sizeof positionSequence) ;i++) {
    //     for(int j = 0;j < 4 ; j++) {
    //         printf()
    //     }
        
    // }
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
        // 사용자 입력을 통해 센서 값 설정
        // printf("Enter Front Sensor (0 or 1): ");
        // scanf("%d", (int*)&frontSensorValue); // 값을 0 또는 1로 입력받아 설정
        // clearBuffer(); // 버퍼 비우기

        // printf("Enter Left Sensor (0 or 1): ");
        // scanf("%d", (int*)&leftSensorValue);
        // clearBuffer(); // 버퍼 비우기

        // printf("Enter Right Sensor (0 or 1): ");
        // scanf("%d", (int*)&rightSensorValue);
        // clearBuffer(); // 버퍼 비우기

        // printf("Enter Dust Sensor (0 or 1): ");
        // scanf("%d", (int*)&dustSensorValue);
        // clearBuffer(); // 버퍼 비우기
        frontSensorValue = positionSequence[i][0];
        leftSensorValue = positionSequence[i][1];
        rightSensorValue = positionSequence[i][2];
        dustSensorValue = positionSequence[i][3];

        // 장애물 감지
        Obstacle obstacleDetected = determineObstacleLocation();
        bool F = obstacleDetected.frontobstacle;
        bool L = obstacleDetected.leftobstacle;
        bool R = obstacleDetected.rightobstacle;
        bool Dust = determineDustExistence();

        if (strcmp(motorCommand, "Moving Backward...\n") == 0) {
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
                    cleaningPower(Power); //다시 돌아올 때 power on이 2번이 출력됨. 걍 냅둘지 말지...
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

        sleep(1); // 1초 대기
        i++;
    }
}

Obstacle determineObstacleLocation() {
    Obstacle obstacle;
    obstacle.frontobstacle = frontSensor();
    obstacle.leftobstacle = leftSensor();
    obstacle.rightobstacle = rightSensor();
    return obstacle;
}

bool determineDustExistence() {
    return dustSensorValue; // 먼지 센서 값
}

bool frontSensor() {
    return frontSensorValue; // 입력받은 값을 반환
}

bool leftSensor() {
    return leftSensorValue; // 입력받은 값을 반환
}

bool rightSensor() {
    return rightSensorValue; // 입력받은 값을 반환
}

bool dustSensor() {
    return dustSensorValue; // 먼지 센서 값
}

void moveForward() {
    motorCommand = "Moving forward...\n";
    motorInterface(motorCommand);
}

void turnLeft() {
    motorCommand = "Turn Left for 5 Tick...\n";
    motorInterface(motorCommand);
    sleep(5);
    
}

void turnRight() {
    motorCommand = "Turn Right for 5 Tick...\n";
    motorInterface(motorCommand);
    sleep(5);
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

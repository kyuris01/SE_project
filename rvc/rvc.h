#ifndef RVC_H
#define RVC_H

#include <stdbool.h>

// 상수 정의
#define ITERATION_NUM 10

// 전역 변수 선언
extern bool frontSensorInput;
extern bool leftSensorInput;
extern bool rightSensorInput;
extern bool dustSensorInput;

extern char* Power; // 전역 변수 초기화는 .c 파일에서 수행
extern char* motorCommand;

// positionSequence 선언
extern bool positionSequence[ITERATION_NUM][4];

// 구조체 선언
typedef struct {
    bool frontobstacle;
    bool leftobstacle;
    bool rightobstacle;
} Obstacle;

// 외부에서 호출 가능한 함수 프로토타입
void clearBuffer();
bool frontSensor();
bool leftSensor();
bool rightSensor();
bool dustSensor();

Obstacle ObstacleLocation();
bool DustExistence();

// Direction
void moveForward();
void turnLeft();
void turnRight();
void moveBackward();
void stop();

// Cleaning Power
void cleaningPower(char* power);

// Controller
void Controller();

// Interface
void motorInterface(char* motorCommand);
void cleanerInterface(char* power);

#endif // RVC_H

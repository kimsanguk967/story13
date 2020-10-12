#include <wiringPi.h>
#include <softPwm.h>  // Software PWM library 헤더파일 선언

#define LED_PIN_1 5  //LED 포트 RED 핀 정의
#define LED_PIN_2 6
#define LED_PIN_3 13

#define KEYPAD_PB1 18   //KEYPAD 포트 BT 핀 정의
#define KEYPAD_PB2 23 
#define KEYPAD_PB3 24
#define KEYPAD_PB4 25
#define KEYPAD_PB5 8

#define LED_ON 1
#define LED_OFF 0                  //LED ON/OFF 정의 

#define MAX_LED_NUM 3
#define MAX_KEY_BT_NUM 5   // LED 개수 및 KEYPAD 버튼 수 정의

#define MOTOR_MT_P_PIN 4       // MOTOR 포트 MT_P 핀 정의
#define MOTOR_MT_N_PIN 17      // MOTOR 포트 MT_N 핀 정의

#define LEFT_ROTATE  1     //반시계방향 회전 상수 정의
#define RIGHT_ROTATE 2    //시계방향 회전 상수 정의

void MotorStop(void);              //모터 제어 관련 함수 프로토타입 정의
void MotorControl(unsigned char speed, unsigned char rotate);

const int LedPinTable[3] = {         // LED 핀 테이블 선언

LED_PIN_1, LED_PIN_2, LED_PIN_3,  };          
const int KeypadTable[5]= {       // KEYPAD 핀 테이블 선언

KEYPAD_PB1, KEYPAD_PB2, KEYPAD_PB3, KEYPAD_PB4, KEYPAD_PB5 };

int KeypadRead(void)
{
int i,nKeypadstate;                              //KEYPAD 버튼 눌림을 확인하여 nKeypadstate 상태 변수에 값을 저장
nKeypadstate = 0;
for(i =0; i<MAX_KEY_BT_NUM; i++) {
        if(!digitalRead(KeypadTable[i])) {
                nKeypadstate |= (4<<i);
                }
        }
        return nKeypadstate;
        }
        void LedControl(int LedNum, int Cmd)   // 해당하는 LED번호와 ON/OFF명령 변수를 확인하여 LED판에 신호 출력
        {
             int i;
                for(i=0; i<MAX_LED_NUM;i++) {
                        if(i==LedNum) {
                         if(Cmd == LED_ON) {
                        digitalWrite(LedPinTable[i],HIGH);
}
                        else {
                        digitalWrite(LedPinTable[i],LOW);
}
}
}
}
int main(void)

{
  if (wiringPiSetupGpio() == -1)    //Wiring Pi의 GPIO를 사용하기 위한 설정
     return 1;
         pinMode(MOTOR_MT_N_PIN, OUTPUT);
         pinMode(MOTOR_MT_P_PIN, OUTPUT);      //  MT_N / MT_P 핀 출력 설정

         softPwmCreate(MOTOR_MT_N_PIN, 0, 100);
         softPwmCreate(MOTOR_MT_P_PIN, 0, 100);          // MT_N / MT_P 핀 PWM 설정
while(1) {

  MotorControl(30, RIGHT_ROTATE);       //  모터 제어
      delay(2000);                 //  - 듀티비 30% / 시계 방향 회전
      MotorStop();                //  모터 정지
      delay(5000);  

    MotorControl(50, RIGHT_ROTATE);     //모터 제어
       delay(2000);           //듀티비 50% / 시계 방향 회전
       MotorStop();         //모터 정지
       delay(5000);

        MotorControl(80, RIGHT_ROTATE);       //  모터 제어
      delay(2000);                 //  - 듀티비 80% / 시계 방향 회전
      MotorStop();                //  모터 정지
      delay(5000);  
      
      MotorControl(80, LEFT_ROTATE);       //  모터 제어
      delay(2000);                 //   시계반대 방향 회전
      MotorStop();                //  모터 정지
      delay(5000);  
}
return 0;
}
void MotorStop()
{
    softPwmWrite(MOTOR_MT_N_PIN, 0);
    softPwmWrite(MOTOR_MT_P_PIN, 0);
}
void MotorControl(unsigned char speed, unsigned char rotate)
{
    if(rotate == LEFT_ROTATE) {
                        digitalWrite(MOTOR_MT_P_PIN, LOW);
                        softPwmWrite(MOTOR_MT_N_PIN, speed);
}
else if(rotate == RIGHT_ROTATE) {
                   digitalWrite(MOTOR_MT_N_PIN, LOW);
                   softPwmWrite(MOTOR_MT_P_PIN, speed);
   }
}
{
if(wiringPiSetupGpio() == -1)          // Wiring Pi의 GPIO를 사용하기 위한 설정
return 1;
int i;
int nKeypadstate;
for(i = 0; i<MAX_LED_NUM; i++) {
pinMode(LedPinTable[i],OUTPUT);
}
//LED 핀 출력 설정
for(i =0; i<MAX_KEY_BT_NUM; i++) {
pinMode(KeypadTable[i],INPUT);
}
// KEYPAD 핀 입력 설정
while(1)
{
nKeypadstate = KeypadRead();  //KEYPAD로부터 버튼 입력을 읽어 상태를 변수에 저장
for(i = 0; i<MAX_KEY_BT_NUM; i++) {    //KEYPAD 상태 변수를 확인하여 LED ON/OFF 제어
if((nKeypadstate & (1<<i))) {
LedControl(i,LED_ON);
}
else {
LedControl(i,LED_OFF);
 }
}
 }
return 0;
}  

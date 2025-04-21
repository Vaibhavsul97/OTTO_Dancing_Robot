#include <Otto.h>
Otto Otto;
#include <Servo.h>
Servo AL, AR;

int adj[]={ 0, 0,};
int pos[]={ 90,90};
int shift = 60;
int shift_inc = 10;
int shift_delay = 50;

const char data[] = "VARIABLE#";
unsigned long int matrix;

#define LeftLeg 2 // left leg pin, servo[0]
#define RightLeg 3 // right leg pin, servo[1]
#define LeftFoot 4 // left foot pin, servo[2]
#define RightFoot 5 // right foot pin, servo[3]
#define Buzzer 13 //buzzer pin

#define PIN_AL 6 // left arm
#define PIN_AR 7 // right arm
void move_servo(){ AL.write(pos[1]+adj[1]); AR.write(pos[2]+adj[2]);}
long ultrasound_distance_simple() {
   long duration, distance;
   digitalWrite(8,LOW);
   delayMicroseconds(2);
   digitalWrite(8, HIGH);
   delayMicroseconds(10);
   digitalWrite(8, LOW);
   duration = pulseIn(9, HIGH);
   distance = duration/58;
   return distance;
}

#define CLK A1 // Clock pin
#define CS A2  // Chip Select pin
#define DIN A3 // Data In pin
#define Orientation 0// 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4

void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
Otto.home();

  AL.attach(PIN_AR);
AR.attach(PIN_AL);
move_servo();
delay(100);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  Otto.initMATRIX( DIN, CS, CLK, Orientation);
    Otto.writeText ( "IAM BIPED",80); // limited to CAPITAL LETTERS NUMBERS : ; < >  = @, MAX.9 characters
  Otto.playGesture(OttoSuperHappy);
  AL.write(90);
  AR.write(90);
  delay(shift_delay);
}

void loop() {
    Otto.walk(1,750,1); // FORWARD
    if (ultrasound_distance_simple() < 30) {
      Otto.playGesture(OttoConfused);
      Otto.moonwalker(1, 750, 25, 1);
      AL.write(160);
      AR.write(20);
      delay(shift_delay);Otto.moonwalker(1, 750, 25, -1);
      AL.write(20);
      AR.write(160);
      delay(shift_delay);Otto.putMouth(happyOpen);
      Otto.flapping(1, 750, 25, -1);
      Otto.putMouth(happyOpen);
      Otto.flapping(1, 750, 25, 1);
      Otto.putMouth(happyOpen);
      for (int count=0 ; count<4 ; count++) {
        Otto.swing(1, 750, 25);
        Otto.jitter(1, 750, 25);
        Otto.putMouth(heart);
        for(int angle=90; angle<90+shift; angle+=shift_inc){  pos[2] = angle;    move_servo();  delay(shift_delay);}
        for(int angle=90+shift; angle>90-shift; angle-=shift_inc) { pos[2] = angle;  move_servo(); delay(shift_delay); }
        for(int angle=90-shift; angle<90; angle+=shift_inc) {pos[2] = angle;  move_servo();   delay(shift_delay); }
      }
      for (int count=0 ; count<4 ; count++) {
        Otto.tiptoeSwing(1, 750, 25);
        AL.write(160);
        AR.write(20);
        delay(shift_delay);Otto.putMouth(culito);
      }
      for (int count=0 ; count<4 ; count++) {
        Otto.moonwalker(1, 750, 25, -1);
        for(int angle=90; angle<90+shift; angle+=shift_inc){  pos[1] = angle;    move_servo();  delay(shift_delay);}
        for(int angle=90+shift; angle>90-shift; angle-=shift_inc) { pos[1] = angle;  move_servo(); delay(shift_delay); }
        for(int angle=90-shift; angle<90; angle+=shift_inc) {pos[1] = angle;  move_servo();   delay(shift_delay); }
        Otto.putMouth(smile);
      }
      for (int count=0 ; count<4 ; count++) {
        Otto.flapping(1, 750, 25, 1);
      }
      for (int count=0 ; count<2 ; count++) {
        Otto.walk(1,750,1); // FORWARD
        Otto.walk(1,750,-1); // BACKWARD
        AL.write(160);
        AR.write(20);
        delay(shift_delay);Otto.putMouth(bigSurprise);
      }
      for (int count=0 ; count<2 ; count++) {
        Otto.flapping(1, 750, 25, 1);
        Otto.turn(1,2000,1); // LEFT
        AL.write(20);
        AR.write(160);
        delay(shift_delay);Otto.putMouth(heart);
      }
    }

}
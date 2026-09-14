//Rifat Ahmmed

#include<EEPROM.h>
#define left_motor_forward 8
#define left_motor_backward 7
#define right_motor_forward 10
#define right_motor_backward 9
#define left_motor_speed 6
#define right_motor_speed 11
#define light 13
#define spl 6 //21 //left motor speed coeficient
#define spr 6//21 //right motor speed coeficient
#define sw 5
#define node_delay 29
#define stop_timer 600
#define u_turn_delay 40 //40
#define turn_brake 17
#define  brake_time 20 //130
#define  Ubrake_time 1
char side = 'r';
char flag = 's';
int pos;
char cross = 's';
byte path[50];
byte counter = 0;

uint32_t m1, m2;


int s[6];
int mid[6], maximum[6], minimum[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 6) * 4;
    minimum[i] = EEPROM.read(i + 12) * 4;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
}

void loop() {
  int r = button_read();
  if (r == 1) line_follow();
  else if (r == 9) maze_scan(0); //scan the maze and stop at the ending point
  else if (r == 8) maze_scan(1); //scan the maze and start solving from ending point
  else if (r == 10) maze_solving(0); //solve maze from start
  else if (r == 5) maze_solving(1); //solve maze from ending point
  else if (r == 2) cal();
  else if (r == 7) bluetooth();
  else if (r == 3) motor(10 * spl, 10 * spr); //to test out if the robot is moving perfectly straight forward
  else if (r == 2) analog_reading(); //first connect robot with pc and open serial monitor in arduino. and then press the button accordingly to see analog reading of all sensors
  else if (r == 4) digital_reading(); //first connect robot with pc and open serial monitor in arduino. and then press the button accordingly to see digital reading of all sensors
  else if (r == 11) for (byte i = 0; EEPROM.read(i + 30) != 5; i++) Serial.println(EEPROM.read(i + 30));
  }
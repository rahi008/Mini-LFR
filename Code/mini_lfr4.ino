/*Created by Md. Kaiser Raihan
 * Line Follower 
 * normal stable (40,44) turn delay 120 turn forward 10
 * 
 */
#include <LiquidCrystal.h>
#define INCR_SIZE 0.01
const int startPin = 4;
const int APin = 8;
const int BPin = 7;
const int rghtLed=11;
const int mdlrLed=10;
const int mdllLed=13;
const int lftLed=12;
unsigned int Reff[]={400,400,400,400};
int x=1;
int buttonState=0;
int lft=0,mdll=0,mdlr=0,rght=0;
#define MLA 5
#define MLB 3
#define MRA 6
#define MRB 9
#define STBY 2
#define numberOfSensors 4
#define THRESHOLD 400
boolean botRun=true;

void motorDrive(int x, int y){
  if (x>=0){
  analogWrite(MLA, x); 
  analogWrite(MLB, 0);  
  }
  else{
  x=-1*x;
  analogWrite(MLA, 0); 
  analogWrite(MLB, x);
  }
  if (y>=0){
  analogWrite(MRA, y); 
  analogWrite(MRB, 0);  
  }
  else{
  y=-1*y;
  analogWrite(MRA, 0); 
  analogWrite(MRB, y);
  }
}
int maxSpeed = 100;
float error = 0;
float previousError = 0;
float power = 0;
int totalError = 0;
int leftSpeed = 0;
int rightSpeed = 0;
int setPoint = 2500; //Let’s assume set point is 3500
float kp = 0.089;
float ki = 0;
float kd = 6;
int digitalReading[numberOfSensors];
int sensors[] = {0, 1, 2, 3};
int activeSensors = 0;
void readLine(void)
{
  int p=3;
activeSensors = 0;
for (int i = 0; i < numberOfSensors; i++)
{
if (analogRead(sensors[i]) > THRESHOLD)
{
activeSensors++;
digitalReading[p] = 1;
}
else {
  digitalReading[p] = 0;
}

p--;
} 
}
int getPosition(void)
{
readLine();
int totalWeight = 0;
for (int i = 0; i < numberOfSensors; i++)
{
totalWeight += (i + 1) * 1000 * digitalReading[i];
}
return totalWeight / activeSensors;
}
void PIDLineFollow(void)
{
int currentPosition = getPosition();
previousError = error;
error = currentPosition - setPoint;
totalError += error;
power = (kp * error) + (kd * (error - previousError)) + (ki *
totalError);
if (power > maxSpeed) power = maxSpeed;
else if (power < -1 * maxSpeed) power = -1 * maxSpeed;
if (power < 0)
{
leftSpeed = maxSpeed - abs((int)power);
rightSpeed = maxSpeed;
}
else
{
leftSpeed = maxSpeed;
rightSpeed = maxSpeed - int(power);
}
motorDrive(leftSpeed, rightSpeed);
}
int buttons[] = {4, 8, 7}; //For Kp, Ki and Kd
void increasePIDByButton(void)
{
if (digitalRead(buttons[0]) == LOW)
{
kp -= INCR_SIZE;
delay(250);
}
if (digitalRead(buttons[1]) == LOW)
{
ki += INCR_SIZE;
delay(250);
}
if (digitalRead(buttons[2]) == LOW)
{
kd += INCR_SIZE;
delay(250);
}
}

void setup() {
  pinMode(startPin,INPUT_PULLUP);
  pinMode(APin,INPUT_PULLUP);
  pinMode(BPin,INPUT_PULLUP);
  pinMode(MLA, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(MRA, OUTPUT);
  pinMode(MRB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY,HIGH);
  pinMode(rghtLed,OUTPUT);
  pinMode(mdlrLed,OUTPUT);
  pinMode(mdllLed,OUTPUT);
  pinMode(lftLed,OUTPUT);
  const int lftLed=12;
  Serial.begin(57600);

  
}

void loop() {
  increasePIDByButton();
  rght=analogRead(A0);
  mdlr=analogRead(A1);
  mdll=analogRead(A2);
  lft=analogRead(A3);
  Serial.print("Kp:");
  Serial.print(kp);
  Serial.print("\t");
  Serial.print("Ki:");
  Serial.print(ki);
  Serial.print("\t");
  Serial.print("Kd:");
  Serial.print(kd);
  Serial.print("\t");
  Serial.print("\n");
  if(lft>Reff[0])
  {
    digitalWrite(lftLed,HIGH);
  }
  else
  {
    digitalWrite(lftLed,LOW);
  }
  if(rght>Reff[3])
  {
    digitalWrite(rghtLed,HIGH);
  }
  else
  {
    digitalWrite(rghtLed,LOW);
  }
  if(mdll>Reff[1])
  {
    digitalWrite(mdllLed,HIGH);
  }
  else
  {
    digitalWrite(mdllLed,LOW);
  }
  if(mdlr>Reff[2])
  {
    digitalWrite(mdlrLed,HIGH);
  }
  else
  {
    digitalWrite(mdlrLed,LOW);
  }
  if(lft<Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght>Reff[3])
  {
  motorDrive(40,44); //turn right
  delay(10);
  motorDrive(40,-44);
  delay(120);
  }
  
  else if(lft>Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght<Reff[3])
  {
  motorDrive(40,44); //turn left
  delay(5);
  motorDrive(-40,44);
  delay(120);
  }
  else if PIDLineFollow();
  
  
  
  
  }

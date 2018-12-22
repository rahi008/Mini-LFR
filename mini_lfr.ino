/*Created by Md. Kaiser Raihan
 * Line Follower 
 */
#include <LiquidCrystal.h>
const int startPin = 4;
const int APin = 8;
const int BPin = 7;
const int rghtLed=11;
const int mdlrLed=10;
const int mdllLed=13;
const int lftLed=12;
int x=1;
int buttonState=0;
int lft=0,mdll=0,mdlr=0,rght=0;
#define MLA 5
#define MLB 3
#define MRA 6
#define MRB 9
#define STBY 2
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
unsigned int Reff[]={400,400,400,400};
void setup() {
  pinMode(startPin,INPUT);
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
  Serial.begin(115200);

  
}

void loop() {
  
  rght=analogRead(A0);
  mdlr=analogRead(A1);
  mdll=analogRead(A2);
  lft=analogRead(A3);
  Serial.print(lft);
  Serial.print("\t");
  Serial.print(mdll);
  Serial.print("\t");
  Serial.print(mdlr);
  Serial.print("\t");
  Serial.print(rght);
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
  buttonState = digitalRead(startPin);
  if (buttonState ==LOW)
  {
    x=x+1;
  }
  if(x%2==0){
  
  
  
  if(lft<Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght<Reff[3])
  {
  /*analogWrite(MLA, 90); 
  analogWrite(MLB, 0);    //forward   
  analogWrite(MRA, 90);   
  analogWrite(MRB, 0);  */
  motorDrive(40,44); 
  }
  else if(lft>Reff[0]&&mdll<Reff[1]&&mdlr<Reff[2]&&rght<Reff[3])
  {
  /*  analogWrite(MLA, 0);    //left
  analogWrite(MLB, 0);   
  analogWrite(MRA, 90);   
  analogWrite(MRB, 0);*/
  motorDrive(0,44);
  }
  else if(lft<Reff[0]&&mdll>Reff[1]&&mdlr<Reff[2]&&rght<Reff[3])
  {/*
  analogWrite(MLA, 0); 
  analogWrite(MLB, 0);    //left   
  analogWrite(MRA, 90);   
  analogWrite(MRB, 0);*/
  motorDrive(0,44);
  }
  else if(lft>Reff[0]&&mdll>Reff[1]&&mdlr<Reff[2]&&rght<Reff[3])
  {/*
    analogWrite(MLA, 0); //left
  analogWrite(MLB, 0);   
  analogWrite(MRA, 90);   
  analogWrite(MRB, 0);*/
  motorDrive(0,44);
  }
  else if(lft<Reff[0]&&mdll<Reff[1]&&mdlr>Reff[2]&&rght<Reff[3])
  {/*
  analogWrite(MLA, 90); 
  analogWrite(MLB, 0);//right   
  analogWrite(MRA, 0);   
  analogWrite(MRB, 0);*/
  motorDrive(40,0);
  }
  else if(lft<Reff[0]&&mdll<Reff[1]&&mdlr>Reff[2]&&rght>Reff[3])
  {/*
  analogWrite(MLA, 90); 
  analogWrite(MLB, 0);//right   
  analogWrite(MRA, 0);   
  analogWrite(MRB, 0);*/
  motorDrive(40,0);
  }
  else if(lft<Reff[0]&&mdll<Reff[1]&&mdlr<Reff[2]&&rght>Reff[3])
  {/*
   analogWrite(MLA, 90); 
  analogWrite(MLB, 0);//right   
  analogWrite(MRA, 0);   
  analogWrite(MRB, 0);*/
  motorDrive(40,0);
  
  }
  else if(lft<Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght>Reff[3])
  {/*
  analogWrite(MLA, 90); 
  analogWrite(MLB, 0);//turn right   
  analogWrite(MRA, 0);   
  analogWrite(MRB, 90);*/
  motorDrive(40,44);
  delay(10);
  motorDrive(40,-44);
  delay(100);
  }
  
  else if(lft>Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght<Reff[3])
  {/*
  analogWrite(MLA, 0); 
  analogWrite(MLB, 90);//turn left   
  analogWrite(MRA, 90);   
  analogWrite(MRB, 0);*/
  motorDrive(40,44);
  delay(10);
  motorDrive(-40,44);
  delay(100);
  }
 
  else if(lft>Reff[0]&&mdll>Reff[1]&&mdlr>Reff[2]&&rght>Reff[3])
  {
  motorDrive(0,0);
  
  }
  }
  
  
  }

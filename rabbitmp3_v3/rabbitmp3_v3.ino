/*
**************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example is a modification of the basic function of library for DFPlayer.


 Original demo:
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution

 Modification:
 Created 04APR2021
 By [Repeated Failure]  [https://github.com/RepeatedFailure]
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//Pin connected to read connection to ground
int earPin = 2;
int tailPin = 6;
int headPin = 4;

//states of rabbit parts.  0 = not bitten, 1 = bitten 
int ear = 0;
int tail = 0;
int head = 0;


void setup()
{
  //Use pullup resistors to check connection of pins to ground
  pinMode(earPin, INPUT_PULLUP); 
  pinMode(tailPin, INPUT_PULLUP);
  pinMode(headPin, INPUT_PULLUP);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop()
{
  
  if (digitalRead(earPin ) == HIGH && ear == 0){
    Serial.write('H');
    ear = 1;
    myDFPlayer.play(1);}
    
   if (digitalRead(tailPin ) == HIGH && tail == 0){
    Serial.write('H');
    tail = 1;
    myDFPlayer.play(2);}
    
    if (digitalRead(headPin ) == HIGH && head == 0){
    Serial.write('H');
    ear = 1;
    tail = 1;
    head = 1;
    myDFPlayer.play(3);}
  

}

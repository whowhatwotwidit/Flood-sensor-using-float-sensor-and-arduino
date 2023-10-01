//FLOOD WATER LEVEL SENSOR CODE

#include <SoftwareSerial.h>

SoftwareSerial sim800(10,11);   //connect sim800 tx/rx pins to arduino pin 10, 11

const int floodSensor = 8;     //connect flood sensor to arduino pin 8
byte oldSensorState = HIGH;   //initialize flood level to no flood

void setup() 
{
Serial.begin (19200);                     //set baud rate of arduino
pinMode (floodSensor, INPUT_PULLUP);     //set flood sensor pin8 as input with pullup resistor
pinMode (LED_BUILTIN, OUTPUT);           //set built in led as output 
sim800.begin(19200);                  //set baud rate of gsm module
delay(20000);            //set 20 secs delay to wait for sim card to connect to network
}

void loop() 
{
  byte sensorState = digitalRead (floodSensor);   //read sensor
  if (sensorState != oldSensorState)  //if there is change in status
  {
    oldSensorState = sensorState;    //set the previous status to current status
    if (sensorState == LOW)          //if there is flood
    {
      digitalWrite (LED_BUILTIN, HIGH);  //led will light up 
      delay(500);                  
      sendTxt();                   //send text
    }
    else                            // there is no flood
    {
      digitalWrite (LED_BUILTIN, LOW);   // led is not lit up
      delay(1000);                 
    }
  }
}

void sendTxt()
{
  sim800.println("AT+CMGF=1");                     //set gsm module to text mode
  delay(100);
  sim800.println("AT+CMGS=\"+639171111111\"");   //set phone number to receive text
  delay(100);
  sim800.println("WARNING! FLOOD ALERT!");        //set flood alert message
  delay(100);
  sim800.println((char)26);                        //send the message
  delay(100);
  sim800.println();                                //send the message
  delay(5000);
}

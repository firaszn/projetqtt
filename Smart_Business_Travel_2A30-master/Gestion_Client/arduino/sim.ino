#include "SoftwareSerial.h"
#include "Sim800l.h"
Sim800l Sim800l;
String text;
String cmd = "";
uint8_t index;
uint8_t lastindex = 1;
bool finished = false;
void setup()
{
Serial.begin(9600);          // only for debug the results .
    Sim800l.begin();
  text=Sim800l.readSms(1);             // initializate the library.


}

void loop()
{
updateSerial();

}
void updateSerial()
{
   delay(500);
  while (Serial.available()) 
  {

    cmd=Serial.readString();
 
    if(cmd!=""){
      cmd.trim();  // Remove added LF in transmit
      if (cmd.substring(0,1)=="S") {
        if(Sim800l.sendSms(cmd.substring(1,13),cmd.substring(13,cmd.length()))) Serial.print("W");
        else Serial.print("F");
        //Serial.println("The string that you wrote is"+cmd.substring(1,13)+cmd.substring(13,cmd.length()));
      }
      if (cmd.substring(0,1)=="V") {
        Verify(cmd.substring(1,13));
      }
    }
    cmd="";
  }


}
void lasttindex()
{
  finished=false;
  while (text!="")
  {
      lastindex=lastindex+1;
text=Sim800l.readSms(lastindex);
  Serial.println(lastindex);
  if(text=="")
  lastindex--;
  }
  finished=true;
}

void Verify(String number)
{
  uint8_t i=0;
  bool V=false;
      Serial.print("W");

    do
  {

    i=i+1;
text=Sim800l.readSms(i);
Serial.println(text);
  if(text.indexOf(number)>0)
  V=true;
  }
while (text!="");
  if(V)
    Serial.print("Y");
    else
    Serial.print("N");
  Sim800l.delAllSms();
}
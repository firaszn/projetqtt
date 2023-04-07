#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
char keys[ROW_NUM][COLUMN_NUM] = {
{'1','2','3', 'A'},
{'4','5','6', 'B'},
{'7','8','9', 'C'},
{'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
unsigned long timePress = 0;
unsigned long timePressLimit = 0;
int clicks = 0;
void setup() {
 Serial.begin(9600);
}

void loop() {
char key = keypad.getKey();
if(key) // On appuie sur une touche du clavier matriciel
{
if(key=='#')
{
//delay(200);
    if (clicks == 0) {
    timePress = millis();
    timePressLimit = timePress + 1000;    
    clicks = 1;
    Serial.print('#'); 
    }
    else if (clicks == 1 && millis() < timePressLimit){
      Serial.print("##"); 
      //set variables back to 0
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;
}}
else Serial.print(key); 
}
if ((clicks == 1) && (timePressLimit != 0) && (millis() > timePressLimit)){ 
     timePress = 0;
     timePressLimit = 0;
     clicks =0;}
}

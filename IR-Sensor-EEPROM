/**
* Receives signal from IR remote control on pin 10 
* Displays the function to the serial monitor
* Writes state of control to EEPROM for recall when power is turned off
* Reads state of control from EEPROM when power is turned on
* Uses the UP, DOWN, LEFT, and RIGHT button as well as MUTE and POWER
* Channels go up or down
* Volume changes serveral numbers between 0 to 255 
* Mute and Power turn on or off
* adapted from http://forum.arduino.cc/index.php/topic,17965.0.html 
**/

#include <EEPROM.h>

//CONSTANTS
#define btnPower   149          //Power button
#define btnMute    148          //Mute button
#define btnLeft    147          //Left channel button
#define btnRight   146          //Right channel button
#define btnUp      144          //Volume up button  
#define btnDown    145          //Volume down button
#define rate       4            
#define start_bit  2000         //Start bit threshold (Microseconds)
#define bin_1      1000         //Binary 1 threshold (Microseconds)
#define bin_0      400          //Binary 0 threshold (Microseconds)
#define ir_pin     10           //Sensor pin 1 wired through a 220 ohm resistor
#define debug      0            //Serial connection must be started to debug

//VARIABLES
//Store values in EEPROM 1 to 3
int power    = EEPROM.read(0);    
int mute     = EEPROM.read(1);  
int volume   = EEPROM.read(2);
int channel  = EEPROM.read(3);
int i        = 0;                 //General purpose counter 

void setup() 
{
 pinMode(ir_pin, INPUT);
 Serial.begin(9600);
 if(volume == 255) volume = 0;    //Don't start up at full volume
}

void loop() 
{
 //Fetch the key  
 int key = getIRKey();
 
 //Switch Case used to print insructions to Serial Monitor
  switch (key) {
  
  //Power button
   case btnPower:
     if(power == 0){
       power = 1;
       Serial.println("Turn On");
     } else {
       power = 0;
       Serial.println("Turn Off");
     }
     EEPROM.write(0, power);
     delay (500); //Debounce switch
     break;
   
  //Mute button   
  case btnMute:    
     if(mute == 0){
       mute = 1;
       Serial.println("Mute On");
     } else {
       mute = 0;
       Serial.println("Mute Off");
     }
     EEPROM.write(1, mute);
     delay (500); //Debounce switch
     break;
  
  // Left channel button   
  case btnLeft:
     if(volume > 0 && volume - rate > 0) {
       volume -= rate;
     } else {
       volume = 0;
     }
     Serial.print("Volume: ");
     Serial.println(volume);
     EEPROM.write(2, volume);
     break;   
  
  //Right channel button   
  case btnRight:
     if(volume < 255 && volume + rate <= 255) {
       volume += rate;
     } else {
       volume = 255;
     }
     Serial.print("Volume: ");
     Serial.println(volume);
     EEPROM.write(2, volume);
     break; 
     
  //Down volume button
  case btnDown:
     if(channel == 0){
       channel = 1;
       Serial.println("Click Down");
     } else {
       channel = 0;
       Serial.println("Click Down");
     }
     EEPROM.write(3, channel);
     delay (500); //Debounce switch
     break;
  
  //Up volume button   
  case btnUp:
    if(channel == 0){
         channel = 1;
         Serial.println("Click Up");
       } else {
         channel = 0;
         Serial.println("Click Up");
       }
       EEPROM.write(3, channel);
       delay (500); //Debounce switch
       break;
 } 
}


int getIRKey() {
 int data[12];
 while(pulseIn(ir_pin, LOW) < 2200) { 
   //Wait for a start bit
 }
 
 for(i=0;i<11;i++){
   data[i] = pulseIn(ir_pin, LOW); //Start measuring bits, I only want low pulses
 }
 
 if(debug == 1) {
   Serial.println("-----");
 }
 
 for(int i=0;i<11;i++) {          //Parse them
   
   if (debug == 1) {
     Serial.println(data[i]);
   }
   
   if(data[i] > bin_1) {          //is it a 1?
     data[i] = 1;
   } else {
     if(data[i] > bin_0) {        //is it a 0?
       data[i] = 0;
     } else {
       data[i] = 2;               //Flag the data as invalid; I don't know what it is!
     }
   }
   
 }

 for(i=0;i<11;i++) {            //Pre-check data for errors
   if(data[i] > 1) {
     return -1;                //Return -1 on invalid data
   }
 }

 int result = 0;
 int seed = 1;
 for(int i=0;i<11;i++) {      //Convert bits to integer
   if(data[i] == 1) {
     result += seed;
   }
   seed = seed * 2;
 }
 return result;             //Return key number
}

/**********************************************
 * Electronics 2 Project MTE 200
 * 
 * Code Edited by: Hany Elesawy 2022.03.19
 *    Fixed Some Bugs
 *********************************************/
 
#include <RCSwitch.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(11,10);
RCSwitch mySwitch = RCSwitch();

int SonicDistance;                                  /*Distance read by ultrasonic sensor*/

void setup() {
  mySwitch.enableTransmit(4);  
  Serial.begin(9600);
}

void loop() {  
  SonicDistance = ultrasonic.read(CM);
  mySwitch.send(SonicDistance, 24);
  delay(100);
  Serial.println(SonicDistance);
}

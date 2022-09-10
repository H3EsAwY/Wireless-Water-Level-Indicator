/**********************************************
 * Electronics 2 Project MTE 200
 * 
 * Code Edited by: Hany Elesawy 2022.03.19
 *    Added Comments
 *    Fixed Level Equation
 *    Added Volume Equation
 *    Fixed Some Bugs
 *********************************************/




/****************************************************************** General Stuff ******************************************************************/
#include <RCSwitch.h>
#include <LiquidCrystal.h>

/*LCD Pins(-6- RS, E, D4, D5, D6, D7*/
LiquidCrystal lcd(4, 6, 12, 11, 10, 9);

RCSwitch mySwitch = RCSwitch();

int SonicRx;                                                /* UltraSonic Reading Recieved from transmitter*/

int Hval=2;                                                 /*Distance (CentiMeter) between Ultrasonic and water when Tank is Full*/
int Lval=15;                                                /*Distance (CentiMeter) between Ultrasonic and water when Tank is Empty*/
int rangeLength=(Lval - Hval);                               /* The Range (CentiMeter) at which water changes*/
int waterLength;
float level;                                                /*The actual water level in % (100% -> tank is full)*/

/*For calculating folume*/
int volume;
int rad=8;

#define BUZZER A0                                          /*Buzzer Arduino Pin*/


/****************************************************************** Setup ******************************************************************/

void setup() {
  mySwitch.enableReceive(0);

  lcd.begin(16, 2);
  
  pinMode(BUZZER,OUTPUT);

  Serial.begin(9600);
}


/****************************************************************** Main logic ******************************************************************/
void loop() {
  
  if (mySwitch.available()) {
    
    SonicRx = mySwitch.getReceivedValue();
    waterLength= Lval - SonicRx;
    level = (float)waterLength/rangeLength;
    level = level*100;

    volume = 3.1416*rad*rad*waterLength;
    
    /*quick fix for negative readings*/
    if (level<0){
    level=0;
    }
    /*quick fix for +100 readings*/
    if (level>100){
    level=100;
    }
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("WaterLvl: ");
    Serial.println(SonicRx);
    lcd.print(level);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("WaterVol: ");
    lcd.print(volume);
    lcd.print("cc");
    
    mySwitch.resetAvailable();
    
  }   
  
  if (level > 79){
    digitalWrite(BUZZER,HIGH);
   

    delay(100);
    digitalWrite(BUZZER,LOW);

    delay(100);
    }
  else{
    digitalWrite(BUZZER,LOW);
   
    }

}

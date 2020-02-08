#include "TEMPERATURE.H" // GITAWAG ANG TEMPERATURE NGA HEADER
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h> // Para sa LCD nga 4 Wires Ra

//---------Mga Initialization ---------
TemperatureDetect td;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

int FanSpeed=0;int TemperaturePin=22;
int speed1=5;int speed2=6;int speed3=7;
int claptime1;int claptime2;int claptime3;
int valid_clap=0;int reading=0;int runtime=0;

  void lcds(){
      lcd.clear();lcd.setCursor(0,0); //Start at character 4 on line 0
      lcd.print("FanSpeed: ");lcd.print(FanSpeed);lcd.setCursor(0,1); //Start at character 4 on line 0
      lcd.print("Temp = ");lcd.print(td.temperatureselect_loop()); lcd.print("C");
    }   
  void on(){ 
    lcd.setCursor(0,0);lcd.print("System is OFF");lcd.setCursor(0,1);lcd.print("4Claps to TURN ON"); // display First
    valid_clap=0;
      for(;;){
          if(valid_clap==3){
                digitalWrite(TemperaturePin,HIGH);FanSpeed = 1; //ON the thermometer, set FAN speed to 1
                lcd.clear();lcd.setCursor(0,0);lcd.print("WELCOME 2 TCEFUS");     // OFFICIALLY SYSTEM IS TURN ON DELAY 2s display to read LCD
                lcd.setCursor(0,1);lcd.print("STARTING THERMOMETER");delay(2000); // OFFICIALLY SYSTEM IS TURN ON DELAY 2s display to read LCD
                lcd.clear();lcd.setCursor(0,0);lcd.print("Setting FANSPD");lcd.setCursor(0,1);lcd.print("FAN SPEED: ");lcd.print(FanSpeed);
                digitalWrite(speed3, LOW);digitalWrite(speed2, LOW);analogWrite(speed1, 255);delay(2000);// ON THE FAN TO #1, delay 2s to READ LCD
                valid_clap=0; //SYSTEM is ON set clap to zero for off
                break; //go to LOOP()
          }else{
               checkClap();
              }   
        }    
    }//end of argument, power on
 void off(){
    valid_clap=0;
     for(;;){
           if(valid_clap==3){
              lcd.clear();lcd.setCursor(0,0);lcd.print("FAN SHUT DOWN"); 
              digitalWrite(speed3, LOW);digitalWrite(speed2, LOW);analogWrite(speed1, 0); delay(2000); // off the FAN
              lcd.setCursor(4,1);lcd.print("OFF IN ");lcd.print("3 ");lcd.print("2 ");lcd.print("1");delay(2000); 
              digitalWrite(TemperaturePin,LOW); // OFF TEMPERATURE
              valid_clap=0; FanSpeed = 0;break; //back to Loop()
            }else{
               checkClap();
              }
          }
    }//end of argument, power off
    
    void checkClap(){
      reading=analogRead(1);Serial.println(reading); Serial.println(runtime); Serial.println(); //Read Sounds,print data in serial monitor
                if(reading>=100){
                      if(valid_clap==0){
                          claptime1=millis(); valid_clap++; Serial.println("CHECKED");
                      }else if(valid_clap==1){
                          claptime2=millis();
                             if((claptime2-claptime1)<=3000){ //if next clap is late 3 seconds reset
                                valid_clap++;Serial.println("CHECKED");
                              }else{
                                valid_clap=0;Serial.println("RESET");
                              }
                      }else if(valid_clap==2){
                           claptime3=millis();
                              if((claptime3-claptime2)<=3000){ //if next clap is late 3 seconds reset
                                  valid_clap++;Serial.println("CHECKED");
                              }else{
                                  valid_clap=0;Serial.println("RESET");
                              }
                      }
                  }delay(100);
      }
      
    void setup() {
      td.temperatureselect_setup();
      pinMode(TemperaturePin, OUTPUT);
      lcd.begin(16,2);
      lcd.backlight();
      runtime=millis();
      on(); 
    }
    
    void loop() {
        lcds();
        if(td.temperatureselect_loop()>=35.00){
          digitalWrite(speed2, LOW);digitalWrite(speed1, LOW);analogWrite(speed3, 255);
          FanSpeed=3;lcds();off();on();
        }else if(td.temperatureselect_loop()<35.00 && td.temperatureselect_loop()>=31.00){ 
          digitalWrite(speed3, LOW);digitalWrite(speed1, LOW);analogWrite(speed2, 255);
          FanSpeed=2;lcds();off();on();
        }else {
          digitalWrite(speed3, LOW);digitalWrite(speed2, LOW);analogWrite(speed1, 255);
          lcds();off();on();
          }
    }

#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
//double temp;
class TemperatureDetect{
   public:
        void temperatureselect_setup();
        float temperatureselect_loop();

 };
 
void TemperatureDetect::temperatureselect_setup(){
 
  Serial.begin(9600);
  // delay(500);//Delay to let system boot
 // Serial.println("DHT11 Humidity & temperature Sensor\n\n");
 // delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
float TemperatureDetect::temperatureselect_loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    
    //Serial.print("Current humidity = ");
    //Serial.print(DHT.humidity);
    //Serial.print("%  ");
    //Serial.print("temperature = ");
    //Serial.print(DHT.temperature); 
    //Serial.println("C  ");
    delay(1000);//Wait 1 second before accessing sensor again.
    return DHT.temperature;
}

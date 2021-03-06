// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

                  // Include Emon Library
#include "./CTContainer.h"
#include <dht.h>
dht DHT;
#define DHT11_PIN 6         
      
CTContainer ctClamps=  CTContainer();
boolean throwAwayFirst = false;
/*
 * 200 * 0.1 seconds = ~ 20 seconds.
rougly  
*/
float delayTime = 0.1;
int numberOfIterations = 200;
void setup()
{  
  analogReference (EXTERNAL) ;
  analogRead(0);
  Serial.begin(115200);
}

void loop()
{
  ctClamps.resetClamps();
  int i = 0;
  for(i;i < numberOfIterations; i++){
    ctClamps.readClamps();
    delay(delayTime);
  }
  
  
  // throw away first go through
  if(throwAwayFirst == true){
    int chk = DHT.read11(DHT11_PIN);
    Serial.println("{\"temperature\": " + String(DHT.temperature) + 
                     ",\"humidity\": " + String(DHT.humidity) + "  }");
    ctClamps.calculateAverages();
  }
  else{
    throwAwayFirst = true;
  }
  
  
}


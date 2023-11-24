/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6pcC4rN-O"
#define BLYNK_TEMPLATE_NAME "LED test CHY9"
//#define BLYNK_AUTH_TOKEN "nQX7WW4f79UrBo2aI9uADbB4sg2vOpF6"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

void setup()
{
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  Serial.begin(9600);
  delay(100);

  BlynkEdgent.begin();
}

BLYNK_WRITE(V0)
{
   if(param.asInt()==1){
    digitalWrite(D2,HIGH);
   }
   else{
    digitalWrite(D2,LOW);
   }
}
BLYNK_WRITE(V1)
{
   if(param.asInt()==1){
    digitalWrite(D3,HIGH);
   }
   else{
    digitalWrite(D3,LOW);
   }
}



void loop() {
  BlynkEdgent.run();
}

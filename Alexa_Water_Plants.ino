#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include "Esp8266AWSImplementations.h"

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;


//Pump pin
#define pump 5 //D9

//Limit switch
#define limitSwitch 4 //D10

 int timerState1 = 0 ;
int pumpPower = 0 ;

int limitSwitchState = 0 ;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WAP
  Serial.print("Connecting to ");
  Serial.println("Senthil Nayagam);
  WiFi.begin("Senthil Nayagam","pappubangalore");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("ap-northeast-2");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("a3cuyda4whvip9.iot.ap-northeast-2.amazonaws.com");
  iotClient.setAWSPath("/things/Garden_System/shadow");
  iotClient.setAWSKeyID("AKIAJK5UCIZGWEBYFILQ");
  iotClient.setAWSSecretKey("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");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);

  //Pump
  pinMode(pump, OUTPUT);

  pinMode(limitSwitch, INPUT);
  
}

void loop(){
  char* shadow = "{\"state\":{\"reported\": {\"Mode\": pumpPower}{\"Timer\": timerState1} }}";
   

  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);
    
    if (timerState1 == 1 ){
      limitSwitchState = 1;
      standbyLed.off();
      workingLed.on();   
      pumpPower = digitalRead(pumpPower);
      analogWrite(pump, pumpPower*500);
    }

  delay(60000);
}


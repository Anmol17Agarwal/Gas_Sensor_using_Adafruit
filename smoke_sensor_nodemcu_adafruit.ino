#include <ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>
#define smoke A0
#define wifi "ANMOL HOME"
#define password "12345678"
#define server "io.adafruit.com"
#define port 1883
#define username "_anmol_17"
#define key "aio_pesw65m10lipKR24jrWQXP45cqtC"

WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
 Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt,username"/feeds/Gas Sensor");


void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println("Adafruit MQTT demo");
    Serial.println("Connecting to Wifi....");

    WiFi.begin(wifi,password);
    while(WiFi.status()!=WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("WiFi IP Address");
    Serial.println(WiFi.localIP());
    Serial.println("Connecting MQTT");

    while(mqtt.connect()){
      Serial.print(".");
    }

}

void loop()
{
    if(mqtt.connected())
    {
      int data=analogRead(smoke);
      Serial.println("Sending gas data");
      Serial.print(data);
      Serial.print("....");
      if(feed.publish(data))
      {
        Serial.println("success");
      }
      else
      {
        Serial.println("Fail!");
      }

      delay(800);
    
    }
}
    

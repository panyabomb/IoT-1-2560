#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            12    
#define DHTTYPE           DHT22 // ตรวจสอบก่อนว่าของเรารุ่นอะไร

DHT_Unified dht(DHTPIN, DHTTYPE);

char auth[] = "c470ec9d86ef47028bc0c53651d67eb9"; // เปลี่ยนค่านี้เป็นของตนเอง

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "itfitm",""); // เปลี่ยนค่า ssid

  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V5, millis() / 1000);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V1, event.temperature);
  }
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V2, event.relative_humidity);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}

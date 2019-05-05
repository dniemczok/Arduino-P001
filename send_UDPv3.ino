#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <DHT.h>
#include "DHT.h"

DHT dht;


unsigned int UDPPort = 5000;      // local port to listen on

const char* ssid = "Nazwa WIFI";
const char* password = "haslo";

WiFiUDP Udp;

void setup() {
  dht.setup(5);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Wait for WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

}

void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:

  delay(dht.getMinimumSamplingPeriod());
  float t = dht.getTemperature();
  float w = dht.getHumidity();

  String tv = String(voltage);
  String tt = String(t);
  String ww = String(w);

  char ttBuf[6];
  tt.toCharArray(ttBuf, 6);
  char wwBuf[6];
  ww.toCharArray(wwBuf, 6);
  char tvBuf[4];
  tv.toCharArray(tvBuf, 4);

  Udp.begin(UDPPort);
  Udp.beginPacket("10.222.60.9", UDPPort);//send ip to server
  Udp.write(ttBuf);
  Udp.write(wwBuf);
  Udp.write(tvBuf);
  Udp.endPacket();
  Serial.println("Temperatura");
  Serial.println(tt);
  Serial.println("Wilgotność");
  Serial.println(ww);
  Serial.println("Napięcie");
  Serial.println(tv);

  delay(3000);
}

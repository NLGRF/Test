#include <AntoIO.h>
#define LED_D1 23
#define LDR 15
int Counter;
const char *ssid = "DevTech";
const char *pass = "Alonesnon0";
const char *user = "Alones0";
const char *token = "JfmECq0p0c3LOD8JKPNDcUUWz33LaZA1CUVK03aI";
const char *thing = "ESP32";
const char *channel_D1 = "LED_D1";
const char *channel_LDR = "LDR";


/* create AntoIO instance */
AntoIO anto(user, token, thing);
void setup() {
 pinMode(LED_D1, OUTPUT);
 
  pinMode(4, INPUT_PULLUP);
  pinMode(LDR, INPUT);
 
 Serial.begin(115200);
 Serial.print("\nTrying to connect ");
 Serial.print(ssid);
 Serial.println("...");
 while (!anto.wifi.begin(ssid, pass));
 Serial.println("-- Connected, trying to connect to broker...");
 while (!anto.mqtt.connect(user, token, true));
 Serial.println("-- Connected");
 /* change "digital-channel" to your channel in switch type */
 anto.mqtt.sub(channel_D1);
 anto.mqtt.sub(channel_LDR);

}
void loop() {
 anto.mqtt.loop();
 /*
 for proper functionality,
 10-second delay should be added after loop()
 */
 delay(10); 
 
  if (digitalRead(4) == 0) {
    while (digitalRead(4) == LOW);
    digitalWrite(LED_D1, !digitalRead(LED_D1));
  }

  if ((Counter % 200) == 0)
 {
 Serial.print(" LDR = ");
 Serial.print(analogRead(LDR)/4);

 anto.mqtt.pub(channel_LDR, analogRead(LDR)/4); delay(200);
 }

 Counter++;
 
}




void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
 Serial.print("incoming: ");
 Serial.print(topic);
 Serial.print(" - ");
 Serial.print(payload);
 Serial.println();
 
 if (topic.indexOf(channel_D1) != -1)
 if (payload.toInt() == 1) {
 digitalWrite(LED_D1, HIGH);
 Serial.println("HIGH");
 } else {
 digitalWrite(LED_D1, LOW);
 Serial.println("LOW");
 };

} 

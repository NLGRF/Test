#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

//------- Replace the following! ------
char ssid[] = "DevTech";
char password[] = "Alonesnon0";
#define KEY "t8uOb6sUxtEIJZfi_M7eY"
#define EVENT_NAME "SUT_Noodle"
WiFiClientSecure client;
IPAddress ip;
IFTTTMaker ifttt(KEY, client);
void setup() {
  Serial.begin(115200);
  // Set Pin LED
  pinMode(18, OUTPUT);
  pinMode(23, OUTPUT);

  // Set Pin Switch
  pinMode(26, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  ip = WiFi.localIP();
  Serial.println(ip);
}
void loop() {

  // Open

  if (digitalRead(26) == 0) {
    digitalWrite(18, HIGH);
    digitalWrite(23, LOW);
    if (ifttt.triggerEvent(EVENT_NAME, "PC06", "B5722044_Nonpavit", "Open"))
      Serial.println(" Successfully sent Open");
    else
      Serial.println(" Failed!");
    Serial.println("---------------------------------------");
  }

  if (digitalRead(25) == 0) {
    digitalWrite(23, HIGH);
    digitalWrite(18, LOW);
    if (ifttt.triggerEvent(EVENT_NAME, "PC06", "B5722044_Nonpavit", "Close"))
      Serial.println(" Successfully sent Close");
    else
      Serial.println(" Failed!");
    Serial.println("---------------------------------------");
  }

}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RAIN_SENSOR A0
#define LED D5
#define BUZZER D6

const char* ssid = "Sadhana";
const char* password = "123456789";

ESP8266WebServer server(80);

void handleRoot() {

  int rainValue = analogRead(RAIN_SENSOR);

  String statusText;
  String color;

  if (rainValue < 600) {
    statusText = "RAIN DETECTED";
    color = "red";
  } else {
    statusText = "NO RAIN";
    color = "green";
  }

  String page = "<!DOCTYPE html><html><head>";
  page += "<meta http-equiv='refresh' content='2'>";
  page += "<title>Rain Monitoring System</title>";
  page += "</head><body style='text-align:center;font-family:Arial'>";
  page += "<h1>IoT Rain Monitoring System</h1>";
  page += "<h2>Sensor Value: " + String(rainValue) + "</h2>";
  page += "<h2 style='color:" + color + "'>" + statusText + "</h2>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {

  int rainValue = analogRead(RAIN_SENSOR);

  if (rainValue < 600) {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  server.handleClient();
}
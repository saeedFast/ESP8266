//Voltage Sensor with NodeMCU8266 and taking value on Thingsboard Cloud
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// WiFi Configuration
const char* WIFI_SSID = "NiaziPC";        // Replace with your WiFi SSID
const char* WIFI_PASSWORD = "saeed321123"; // Replace with your WiFi password

// ThingsBoard Configuration
const char* THINGSBOARD_SERVER = "thingsboard.cloud"; // Replace with your ThingsBoard server address
const char* ACCESS_TOKEN = "sGvZyfqD8UjbM0bOVnNf";    // Replace with your device's access token

// Analog Pin for Voltage Sensor
const int VOLTAGE_SENSOR_PIN = A0; // Connect your voltage sensor to this analog pin

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging

  connectToWiFi(); // Connect to the local WiFi network

  // Set up ThingsBoard MQTT client
  client.setServer(THINGSBOARD_SERVER, 1883);
  client.setCallback(callback);

  String attributesTopic = "v1/devices/me/attributes/response/+";
  client.subscribe(attributesTopic.c_str());

  reportVoltageSensor(); // Report the voltage sensor reading to ThingsBoard
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Reconnect to ThingsBoard if not connected
  }

  client.loop();         // Maintain MQTT connection
  reportVoltageSensor(); // Report voltage sensor reading to ThingsBoard
  delay(1000);           // Adjust the delay as needed
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Connect to the specified WiFi network

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Wait for WiFi connection
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to ThingsBoard...");
    if (client.connect("ESP8266 Device", ACCESS_TOKEN, NULL)) {
      Serial.println("Connected to ThingsBoard");
      // Resubscribe to attribute changes if needed
      // client.subscribe("v1/devices/me/attributes/response/+");
    } else {
      Serial.print("Failed to connect to ThingsBoard, rc=");
      Serial.print(client.state());
      Serial.println(" - Retrying in 5 seconds...");
      delay(5000); // Retry connection after 5 seconds
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Received attribute response");
  // Handle attribute response here if needed
}

void reportVoltageSensor() {
  // Read voltage from the analog pin
  int volt = analogRead(VOLTAGE_SENSOR_PIN);
   double voltageValue = map(volt,0,1023, 0, 900); //map 0-1023
   voltageValue /=100; //to get decimal value
 
  // Create JSON payload
  StaticJsonDocument<256> jsonDocument;
  jsonDocument["voltage"] = voltageValue;

  char payload[256];
  serializeJson(jsonDocument, payload);

  // Publish to ThingsBoard
  String telemetryTopic = "v1/devices/me/telemetry";
  client.publish(telemetryTopic.c_str(), payload);
}

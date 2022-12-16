#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "eduroam";
const char* password = "your_wifi_password";

// Mosquitto MQTT broker information
const char* broker_host = "your_broker_hostname";
const int broker_port = 1883;

// Create a WiFiClient object
WiFiClient wifiClient;

// Create a PubSubClient object
PubSubClient client(wifiClient);

void setup() {
  // Initialize the ESP32 WiFi module
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  // Print the ESP32 IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the broker host and port for the PubSubClient
  client.setServer(broker_host, broker_port);
}

void loop() {
  // Connect to the Mosquitto MQTT broker
  if (client.connect("ESP32Client")) {
    // Subscribe to a topic
    client.subscribe("esp32/topic");

    // Publish a message to a topic
    client.publish("esp32/topic", "Hello from ESP32!");
  }

  // Disconnect from the broker
  client.disconnect();
  delay(5000);
}
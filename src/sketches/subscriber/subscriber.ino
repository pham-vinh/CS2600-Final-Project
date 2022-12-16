#include <WiFi.h>
#include <PubSubClient.h>

int latchPin = 2;
int clockPin = 4;
int dataPin = 15;

const int tictactoe[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // " | | "

  // Rows
  0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "X| | "
  0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00,  // " |X| "
  0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00,  // " | |X"
};


// WiFi credentials
const char* ssid = "viPhone";
const char* password = "12345678";

// Mosquitto MQTT broker information
const char* broker_host = "test.mosquitto.org";
const int broker_port = 1883;

// Create a WiFiClient object
WiFiClient wifiClient;

// Create a PubSubClient object
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);
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

  // Set up pins to the led matrix
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // Connect to the Mosquitto MQTT broker
  if (client.connect("ESP32Client")) {
    // Subscribe to a topic
    client.subscribe("ESP32/input");
    
    int cols = 0x01;                                     // Assign binary 00000001. Means the first column is selected.
    for (int j = 0; j < 8; j++) {                        // display image of each frame
      matrixRowsVal(pgm_read_word_near(tictactoe + j));  // display the data in this column
      matrixColsVal(~cols);                              // select this column
      cols <<= 1;                                        // shift"cols" 1 bit left to select the next column
    }

    // Publish a message to a topic
    client.publish("ESP32/input", "Hello from ESP32!");
  }

  // Disconnect from the broker
  client.disconnect();
  delay(5000);
}


void matrixRowsVal(int value) {
  // make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  // make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}

void matrixColsVal(int value) {
  // make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, MSBFIRST, value);
  // make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}
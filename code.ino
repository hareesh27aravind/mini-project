//final
#include <WiFi.h>
#include <ThingSpeak.h>

// Replace with your Wi-Fi network credentials
const char* ssid = "hhhhh";
const char* password = "123456789";

// Replace with your ThingSpeak channel ID and API key
unsigned long channelID = 2114497;
const char* apiKey = "S72JKB8O9567DD32";

// Replace with the pin number to which the IR sensor is connected
const int irSensorPin = 14;

WiFiClient client;
int irSensorCount = 0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  pinMode(irSensorPin, INPUT);
  // Connect to ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read the IR sensor
  int irSensorReading = digitalRead(irSensorPin);

  // Increment the count if the sensor reading is HIGH
  if (irSensorReading ==  0) {
    irSensorCount++;
  }

  // Send the count to ThingSpeak
  ThingSpeak.writeField(channelID, 1, irSensorCount, apiKey);

  Serial.print("IR Sensor Count: ");
  Serial.println(irSensorCount);

  delay(20000); // Wait for one second before taking the next reading
}

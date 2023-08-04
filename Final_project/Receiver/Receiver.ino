#include <Wire.h>
#include <DHT.h>
#define DHTPIN 2      // Pin connected to DHT11 data pin
#define DHTTYPE DHT11 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Wire.begin(8); // Initialize I2C communication with the receiver's address (change if needed)
  Wire.onReceive(receiveEvent);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // Your code to process the received data goes here
}

void receiveEvent(int byteCount) {
  float temperature;
  float photoValue;
  
  if (byteCount == sizeof(temperature) + sizeof(photoValue)) {
    Wire.readBytes((byte*)&temperature, sizeof(temperature));
    Wire.readBytes((byte*)&photoValue, sizeof(photoValue));

    // Print received data
    //Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(photoValue);
    //Serial.println("%");
  }
}

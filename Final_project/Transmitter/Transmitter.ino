#include <Wire.h>
#include <DHT.h>
# include <LiquidCrystal_I2C.h>

//Variable to Store humidity and temperature value
LiquidCrystal_I2C LCD1(0x27,16,2);
#define PHOTO_PIN A0
#define DHTPIN 2      // Pin connected to DHT11 data pin
#define DHTTYPE DHT11 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Wire.begin();  // Initialize I2C communication
  dht.begin();
  LCD1.init();
  LCD1.backlight();
  LCD1.display();
  //Serial.println(F("DHT11 test!"));
  LCD1.setCursor(2,0);
  LCD1.print(":DHT11 test!:");
  delay(1000);
  LCD1.clear();
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature from DHT11
  float humidity = dht.readHumidity();       // Read humidity from DHT11
 // Read the value of the photoresistor
  float photoValue = analogRead(PHOTO_PIN);
  // Send temperature and humidity data to the receiver Arduino over I2C
  Wire.beginTransmission(8); // Address of the receiver Arduino (change if needed)
  Wire.write((byte*)&temperature, sizeof(temperature));
  Wire.write((byte*)&photoValue, sizeof(photoValue));
  Wire.endTransmission();

  LCD1.setCursor(0,0);
  LCD1.print("Intensity: ");
  LCD1.setCursor(11,0);
  LCD1.print(photoValue);
  LCD1.setCursor(0,1);
  LCD1.print("Temp:");
  LCD1.setCursor(6,1);
  LCD1.print(temperature);
  delay(2000); // Wait for a second before sending the next data
}

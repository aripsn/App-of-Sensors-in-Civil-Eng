#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//DHT11
#define DHTPIN 2           // data pin we're connected to
#define DHTTYPE DHT11      // or DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);  //// Initialize DHT sensor
//Variable to Store humidity and temperature value
float hum, temp;

//Ultrasound
const int trigPin = 6;
const int echoPin = 5;
long duration;
int FirstDistance = 0;
int SecondDistance = 0;
double speed = 0;
int distance = 1;
float Time = 2.0;
float delayedtime = 1000 * Time;

void setup() {
  pinMode(13, OUTPUT);
  //LCD
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  //DHT11
  dht.begin();
  //Ultrasound
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //Calculate temperature to adjust speed of sound
  CalcTemp();
  //Measure distance of vehicle
  //Max range = 4 meter, Min range = 2 cm
  CalcDistance();
  if (distance < 350) {
    CalcSpeed();    
    Serial.println("within range");
    if (speed > 10 && distance <50){
      lcd.setCursor(1,0);
      lcd.print("Slow down!!!");
      Serial.println("Slow down!!");
      delay(2000);
      lcd.clear();
    }
    if (speed <5 && distance <50){
      lcd.setCursor(1,0);
      lcd.print("Kick the gas!!!");
      Serial.println("Kick the gas!!!");
      delay(2000);
      lcd.clear();
    }        
  }  
}

//Function for calculate temperature and humidity
float CalcTemp() {
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Delay 2 sec, this is important to maintain that much delay in each reading
  delay(2000);
}

//Function for calculate distance
float CalcDistance() {
  // Clears  trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets  trigPin HIGH  for 10 microsec
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads  echoPin, returns the wave travel time in microsec
  duration = pulseIn(echoPin, HIGH);
  //calcdistance
  distance = duration * (0.0331 + (0.61 * temp * 0.0001)) / 2;  //caliberated with temperature
  // Prints distance on Serial Monitor
  Serial.print("Distance in cm : ");
  Serial.println(distance);
  return distance;
}
void CalcSpeed() {

  FirstDistance = CalcDistance();                   //get the first distance
  delay(delayedtime);                               //waits 2 seconds depending on the time declared above ,, feel free to change the value dependng on the resolution of your sensor
  SecondDistance = CalcDistance();                  //gets the second distance
  speed = abs((FirstDistance - SecondDistance) / Time);  // now calculating the difference
  // print speed on  serial monitor
  Serial.print("the speed (cm/s) is  :  ");
  Serial.println(speed);
}
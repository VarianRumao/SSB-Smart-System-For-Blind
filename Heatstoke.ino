#include <Adafruit_Sensor.h>
#define sensorPin A0                    // Get a reading from the temperature sensor:
#include "TinyDHT.h"
#include <SoftwareSerial.h> 
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
#define DHTPIN 5
#define DHTTYPE DHT11
#define LED_TOO_COLD A0
#define LED_PERFECT A1
#define LED_TOO_HOT A2
DHT dht(DHTPIN, DHTTYPE);
int speakerPin = 9;
int length = 1;
int reading = analogRead(sensorPin);
SoftwareSerial MyBlue(1,0); // RX | TX 
int flag = 0; 
int LED = 8;
void setup() {
  // start working...
  Serial.begin(9600);
  MyBlue.begin(9600); 
 pinMode(LED, OUTPUT); 
 Serial.println("Ready to connect\nDefualt password is 1234 or 000");
  Serial.println("DHT11 test!");

  dht.begin();
}

void loop() {
  pinMode(speakerPin, OUTPUT);
  pinMode (A0 , OUTPUT);
  pinMode (A1 , OUTPUT);
  pinMode (A2 , OUTPUT);
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
 
  
    // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);
  // Convert the voltage into the temperature in degree Celsius:
  float temperature = voltage / 10;
  // Print the temperature in the Serial Monitor:


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  if (t <= 10) {
    Serial.println("Too cold!");
    digitalWrite(A0, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);                                   // Adding a delay of one second.

    digitalWrite(speakerPin, LOW);
    digitalWrite(A0, LOW);
  }
  if (11 < t < 44)
  {
    Serial.println("Perfect temperature!");
    digitalWrite(A1, HIGH);
    delay (2000);
    digitalWrite(A1, LOW);
  }
  if (t >= 45) {
    Serial.println("Too hot!");
    digitalWrite(A0, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);
    digitalWrite(speakerPin, LOW);
    digitalWrite(A0, LOW);
  }
  analogWrite(speakerP5in, 0);
  // Get a reading from the temperature sensor:
  if (MyBlue.available()) 
   flag = MyBlue.read(); 
 if (flag == 1) 
 { 
   digitalWrite(LED, HIGH); 
   Serial.println("LED On"); 
 } 
 else if (flag == 0) 
 { 
   digitalWrite(LED, HIGH); 
   Serial.println("LED Off"); 
 } 
  
 }
  

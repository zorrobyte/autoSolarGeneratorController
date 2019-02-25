#include "Arduino.h"
#include "DHT.h"

//This project is to use an Arduino to automatically control my Solar/Generator system. No warranties expressed or implied, use at your OWN RISK!
//This could use some monitoring and failsafes, for example, if the generator never starts due to any reason. May be easy to just monitor battery voltage and set a hard cutoff to catch many errors.
//Could do a ton of other fun stuff if I were to connect to the BMS via RS232. We'll see.

const int relayPin1 = 2;
const int relayPin2 = 3;
const int relayPin3 = 4;
const int relayPin4 = 5;
const int DHTPIN = 6;
const int venusRelay = 7;

// Uncomment whatever DHT Sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);// Initialize DHT sensor

//inputs (buttons, switches)

//state tracking
int fanState = 0;
int genState = 0;
int socState = 0;

int fanStart(){
  fanState = 1;
  digitalWrite(relayPin1, LOW);
}

int fanStop(){
  fanState = 0;
  digitalWrite(relayPin1, HIGH);
}

int genStart(){
  delay(5000);
  genState = 1;
  digitalWrite(relayPin2, LOW);
  delay(3000);
  digitalWrite(relayPin2, HIGH);
  //Connect relay for 3 seconds (start button)
  //check genRunning to see if the generator is actually outputting power! If not, maybe retry, and if it fails, disconnect inverter and throw error on LCD (by setting genFailure = 1)
}

int genStop(){
  delay(5000);
  genState = 0;
  digitalWrite(relayPin3, LOW);
  delay(3000);
  digitalWrite(relayPin3, HIGH);
  //connect relay for three seconds (stop button)
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  dht.begin();
  pinMode(venusRelay, INPUT);
  //stop generator if running
  genStop();
  //Startup delay to wait for Pi
  delay(60000);

  
}

void loop() {

  //test functions
  //genStart();
  //genStop();
  //fanStart();
  //fanStop();
  

//Cooling Fans
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (f >= 100) {// you can change temperature value here - t>= 30 to your preferred number or change from Celsius to Fahrenheit readings
    fanStart();
  }
  else {
    fanStop();
  }

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Temperature = ");
  Serial.print(f);
  Serial.print(" *F ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.print(" %\t ");
  Serial.println();

  delay(1000);// 1 second delay between measurements
      // Check if any reads failed and trigger fans if failed.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    fanStart();
  }

socState = digitalRead(venusRelay);
Serial.print(socState);

if (genState == 0 && socState == HIGH) {
  genStart();
} 
if (genState == 1 && socState == LOW) {
  genStop();
}

}
